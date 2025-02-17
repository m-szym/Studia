<?php


use MongoDB\BSON\ObjectID;




function get_db()
{
    $mongo = new MongoDB\Client(
        "mongodb://localhost:27017/wai",
        [
            'username' => 'wai_web',
            'password' => 'w@i_w3b',
        ]);

    $db = $mongo->wai;

    return $db;
}


function delete_image_record($id)
{
    $db = get_db();
    $image_record = $db->images->findOne(['_id' => new ObjectID($id)]);

    unlink($image_record['og-src']);
    unlink($image_record['thl-src']);
    unlink($image_record['wm-src']);

    $db->images->deleteOne(['_id' => new ObjectID($id)]);

}


function get_images()
{
    $db = get_db();
    return $db->images->find()->toArray();
}


function get_images_by_category($cat)
{
    $db = get_db();
    $images = $db->images->find(['cat' => $cat]);
    return $images;
}

function get_images_by_title_substr($substr)
{
    $db = get_db();
    $images_by_title = [];
    $images = $db->images->find()->toArray();
    foreach ($images as $img)
    {
        if (strpos($img['title'], $substr) !== false)
        {
            $images_by_title[] = $img;
        }
    }
    return $images_by_title;
}


function get_image($id)
{
    $db = get_db();
    return $db->images->findOne(['_id' => new ObjectID($id)]);
}


function save_image($id, $image, $image_file)
{
    $db = get_db();

    if ($id === null) 
    {
        if ($image_file["error"] == UPLOAD_ERR_OK) 
        {
            $uploaddir = $_SERVER['DOCUMENT_ROOT'];

            $path = '/imgs/';
            $uploadfile = $uploaddir . $path . date("Y.m.d.H.i") . '-' . basename($image_file['name']);

            if (move_uploaded_file($image_file['tmp_name'], $uploadfile)) 
            {
                $image['og-src'] = $uploadfile;
                generate_thumbnail($image, $uploadfile);
                generate_watermark($image, $uploadfile, $_POST['watermark_text']);

                $db->images->insertOne($image);
            }

        }
    } 
    else if ($id != null)
    {
        $old_image = $db->images->findOne(['_id' => new ObjectID($id)]);

        $image['og-src'] = $old_image['og-src'];                                    //przepisanie org obrazka
        $image['thl-src'] = $old_image['thl-src'];                                  //przepisanie miniaturki
        generate_watermark($image, $image['og-src'], $_POST['watermark_text']);     //nowy watermark
        
        $db->images->replaceOne(['_id' => new ObjectID($id)], $image);
    }

    return true;
}

function generate_thumbnail(&$image, $filepath)
{
    $file_info = pathinfo($filepath);

    $newfp = $file_info['dirname'] . '/' . $file_info['filename'] . "-thl." . $file_info['extension'];

    $new_width = 200;
    $new_height = 125;
    list($old_width, $old_height) = getimagesize($filepath);
  
    $new_image = imagecreatetruecolor($new_width, $new_height);

    if ($file_info['extension'] === 'jpg')
    {
        $old_image = imagecreatefromjpeg($filepath);
        imagecopyresampled($new_image, $old_image, 0, 0, 0, 0, $new_width, $new_height, $old_width, $old_height);
        imagejpeg($new_image, $newfp);
    } 
    else if ($file_info['extension'] === 'png')
    {
        $old_image = imagecreatefrompng($filepath);
        imagecopyresampled($new_image, $old_image, 0, 0, 0, 0, $new_width, $new_height, $old_width, $old_height);
        imagepng($new_image, $newfp);
    }

    $image['thl-src'] = $newfp;

    imagedestroy($old_image);
    imagedestroy($new_image);
}

function generate_watermark(&$image, $filepath, $wm_text)
{
    $file_info = pathinfo($filepath);

    $newfp = $file_info['dirname'] . '/' . $file_info['filename'] . "-wm." . $file_info['extension'];

    list($old_width, $old_height) = getimagesize($filepath);
  

    if ($file_info['extension'] === 'jpg')
    {
        $old_image = imagecreatefromjpeg($filepath);
        $whitecolor = imagecolorallocate($old_image, 0, 0, 0);
        imagestring($old_image, 5, 25, 25, $wm_text, $whitecolor);
        imagejpeg($old_image, $newfp);
    } 
    else if ($file_info['extension'] === 'png')
    {
        $old_image = imagecreatefrompng($filepath);
        $whitecolor = imagecolorallocate($old_image, 0, 0, 0);
        imagestring($old_image, 5, 25, 25, $wm_text, $whitecolor);
        imagepng($old_image, $newfp);
    }

    $image['wm-src'] = $newfp;

    imagedestroy($old_image);
    //imagedestroy($new_image);
}

function get_page_cont($page)
{
    $per_page = 3;

    $db = get_db();

    return $db->images->find(['author' => 'picsum'], ['skip' => ($page-1) * $per_page, 'limit' => $per_page])->toArray();
}

function get_notpv_page_cont($page)
{
    $per_page = 3;

    $db = get_db();

    return $db->images->find(['private' => false], ['skip' => ($page-1) * $per_page, 'limit' => $per_page])->toArray();
}

function get_page_cont_for_user($page, $per_page)
{
    $db = get_db();
    return $db->images->find(['$or' => [['author' => $_SESSION['login']], ['private' => false] ,] ], ['skip' => ($page-1) * $per_page, 'limit' => $per_page])->toArray();
}

function count_images_visible_to_user($login)
{
    $db = get_db();
    return count($db->images->find(['$or' => [['author' => $_SESSION['login']], ['private' => false] ,] ])->toArray());
}



// -------------- ------------ ----------
function LoginExists($login){
	$db=get_db();
	$query = ['login' => $login];
	//dokument jeśli jest, null jeśli nie znaleziony
	$user = $db->users->findOne($query);
	if ($user) {return true; }
	 else { return false;}
}

function AddNewUser($log, $pass, $rank, $email){
	$db = get_db();
	$wynik =$db->users->insertOne([ 'login' => $log, 'password' => $pass, 'rank' => $rank , 'email' => $email]);
	return $wynik;	 
}

function ReadUser($login, $password) {
	try 
    {
		$db = get_db();
		$user = $db->users->findOne(['login' => $login]);
		// sprawdzenie hasła
		if($user !== null && 
			password_verify($password, $user['password']))
            {  
			//hasło poprawne
			session_regenerate_id();
			$_SESSION['user_id'] = $user['_id'];
			$_SESSION['user'] = $user;
            $_SESSION['login'] = $user['login'];
            
			return true;
			}
		else 
        {
			return false;
		}
	}
	catch ( Exception $e) { return $e; }
}



function already_exists($collection, $parameter_name, $parameter_value)
{
	$db=get_db();
	$query = [$parameter_name => $parameter_value];

	$user = $db->$collection->findOne($query);
	if ($user) 
        return true; 
	else 
        return false;
}

function add_user($user){
	$db=get_db();
	$wynik =$db->users->insertOne($user);
	return $wynik;	 
}

function read_user(&$user) {
	try {
		$db = get_db();
		$db_user = $db->users->findOne(['login' => $user['login']]);
		// sprawdzenie hasła
		if($db_user !== null && 
			password_verify($user['password'], $db_user['password'])){
            /*
			//hasło poprawne
			session_regenerate_id();
			$_SESSION['user_id'] = $user['_id'];
			$_SESSION['rule'] = $user['rule'];
            */
			return true;
			}
		else {
			return false;
		}
	}
	catch ( Exception $e) { return $e; }
}


function clear_users ()
{
    $db = get_db();
    $db->users->deleteMany([]);
}

function clear_images ()
{
    $db = get_db();
    $db->images->deleteMany([]);
}
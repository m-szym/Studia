<?php
require_once 'business.php';



function images(&$model)    //OK - all images, inc private
{
    $images = get_images();

    $model['images'] = $images;

    return 'images_view';           
}


function image(&$model)     //OK - one image
{
    if (!empty($_GET['id'])) {
        $id = $_GET['id'];

        if ($image = get_image($id)) {
            $model['image'] = $image;

            return 'image_view';      
        }
    }

    http_response_code(404);
    exit;
}


function edit_image(&$model)    //raczej OK - ograniczenia - zrobione
{
    $image = [
        'author' => null,
        'title' => null,
        'og-src' => null,
        'thl-src' => null,
        'wm-src' => null,
        'private' => false,
    ];
    $user_msg = "";

    if ($_SERVER['REQUEST_METHOD'] === 'POST') 
    {
        if ( isset($_FILES['ImageFile']) )
        {
            $fimage = $_FILES['ImageFile'];
            $allowed_ext = array('89504E47', 'FFD8FFE0', 'FFD8FFE1');   // png , jpg1, jpg2
            $f = fopen($fimage['tmp_name'], 'r');
            $magic_n = strtoupper(bin2hex(fread($f, 4)));
            fclose($f);

            if (in_array($magic_n, $allowed_ext))
            {
                if ($fimage['size'] < 1000000)
                {
                    $image['author'] = $_POST['author'];
                    $image['title'] = $_POST['title'];

                    if (isset($_POST['private']) )  
                        $image['private'] = true;

                    if (save_image(null, $image, $_FILES['ImageFile'])) 
                    {
                        return 'redirect:gallery';
                    }
                }
                else
                    $user_msg = "Zbyt duży plik";
            }
            else
            {
                $user_msg = "Nieprawidłowy format pliku";
            }
        }
        else if (isset($_POST['id']))
        {
            $image['author'] = $_POST['author'];
            $image['title'] = $_POST['title'];
            //$image['_id'] = $_POST['id'];

            if (isset($_POST['private']) )  
                $image['private'] = true;

            if (save_image($_POST['id'], $image, null)) 
            {
                return 'redirect:gallery';
            }
        }
    } 
    elseif (!empty($_GET['id'])) {
        $image = get_image($_GET['id']);
    }


    $model['image'] = $image;
    $model['user_msg'] = $user_msg;


    return 'edit_image_view';           
}


function gallery(&$model)       //raczej OK
{
    if (!empty($_REQUEST['page'])) 
        $page = $_REQUEST['page'];
    else 
        $page = 1;

    if (isset($_SESSION['login']) )
    {    
        $images_visible = count_images_visible_to_user($_SESSION['login']);
        $pages_n = ($images_visible / 3) + 1;
        $model['page_cont'] = get_page_cont_for_user($page, 3);
    }
    else 
    {
        $model['page_cont'] = get_notpv_page_cont($page);
        $db = get_db();
        //$av = $db->images->find(['private' => false])->toArray();
        $pages_n = (count($db->images->find(['private' => false])->toArray()) / 3) + 1;
    }

    $model['pages_n'] = $pages_n;

    return 'gallery_view'; 
}


function delete_image(&$model)  //OK
{
    if (!empty($_REQUEST['id'])) {
        $id = $_REQUEST['id'];

        if ($_SERVER['REQUEST_METHOD'] === 'POST') {
            delete_image_record($id);
            return 'redirect:images';

        } else {
            if ($image = get_image($id)) {
                $model['image'] = $image;
                return 'delete_image_view';     
            }
        }
    }

    http_response_code(404);
    exit;
}


function session_remember (&$model)     //raczej OK
{
    if ($_SERVER['REQUEST_METHOD'] === 'POST') 
    {
        if (isset($_SESSION['chosen_images']))
        {
            $decoded = json_decode(file_get_contents('php://input'));
            foreach ($decoded as $id)
            {
                if (!in_array($id, $_SESSION['chosen_images']))
                {
                    $_SESSION['chosen_images'][] = $id;
                }  
                else
                {
                    array_splice($_SESSION['chosen_images'], array_search($id, $_SESSION['chosen_images']), 1);
                }
            }
        }
        else
        {
            $_SESSION['chosen_images'] = json_decode(file_get_contents('php://input'));
        }

    }
    return 'redirect:gallery';
}

function session_preview (&$model)      //działa
{
    if ($_SERVER['REQUEST_METHOD'] === 'POST') 
    {
        if (isset($_SESSION['chosen_images']))
        {
            $decoded = json_decode(file_get_contents('php://input'));
            foreach ($decoded as $id)
            {
                if (in_array($id, $_SESSION['chosen_images']))
                    array_splice($_SESSION['chosen_images'], array_search($id, $_SESSION['chosen_images']), 1);
            }
        }
    }

    $model['images'] = get_images();

    return "session_preview_view";
}

function search (&$model)       //działa
{
    if (isset($_GET['q']))
    {
        //echo "mam q";
        //$phrase = json_decode($_GET['q']);
        $phrase = $_GET['q'];
        $model['search_results'] = get_images_by_title_substr($phrase);
        //echo $model['search_results'][0];
        //echo json_encode(get_images_by_title_substr($phrase));
        return 'partial/search_res_view';
    }
    else
    {
        //echo "nie amam q";
        return "search_view";
    }

    
}

//---------------------------------------------------------------------------------------------------------

function register(&$model)
{
    $user = [
        'login' => null,
        'password' => null,
        'rank' => 0,
        '_id' => null
    ];

    $user_msg = "";

    if ($_SERVER['REQUEST_METHOD'] === 'POST' &&
        isset($_POST['login']) &&
        isset($_POST['pass']) &&
        isset($_POST['repeat_pass']) &&
        isset($_POST['email']) )
    {
        $login = $_POST['login'];
        $email = $_POST['email'];
        $password = $_POST['pass'];
        $repeat_password = $_POST['repeat_pass'];
        $rank = 0;

        if ($password === $repeat_password)
        {
            if (!LoginExists($login))
            {
                $h_password = password_hash($password, PASSWORD_DEFAULT);

                if (AddNewUser($login, $h_password, $rank, $email) )
                {
                    header("Location: login");
                        exit;
                }
                else { $user_msg ="problem z bazą na etapie dodawania użytkownika"; }
            }
            else { $user_msg = "login zajęty "; }
        } 
        else { $user_msg = "hasła nie są zgodne "; }
    }


    $model['user_msg'] = $user_msg;

    return 'register_view';
}

function login(&$model)
{
    if (($_SERVER['REQUEST_METHOD'] === 'POST') &&
        isset($_POST['login']) && 
        isset($_POST['pass']) ) 
        {

        $login = $_POST['login'];
        $password = $_POST['pass'];

        $done = ReadUser($login, $password);

        if ($done !== true) 
        {
            $model['user_msg'] = "Problem z logowaniem";
            return 'login_view';
        }
        else {           
            header("Location: gallery");
            exit;
        }
    }

    return 'login_view';
}

function logout(&$model)
{
    session_destroy();
    session_unset();

    //usunięcie cookies ustawianych na określony czas
    // (jeśli były ustawiane jakieś ciasteczka niesesyjne)
    return 'redirect:gallery';
}


function purge ()
{
    clear_users();
    clear_images();

    return 'redirect:gallery';
}
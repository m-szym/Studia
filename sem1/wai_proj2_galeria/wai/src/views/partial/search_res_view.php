<?php 
$to_json = [];
if(isset($search_results))
{
    foreach ($search_results as $img)
    {
        $to_json[] = '<img src="' . substr($img['thl-src'], strlen('/var/www/dev/src/web/')) . '" />';
    }
}

echo json_encode($to_json);

?>

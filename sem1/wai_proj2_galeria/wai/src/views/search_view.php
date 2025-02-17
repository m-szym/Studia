<!DOCTYPE html>
<html lang="pl">
<head>
<?php include "includes/head.inc.php"; ?>
    <meta charset="utf-8">
    <title>Wyszukiwarka zdjęć</title>
</head>
<body> 

    <label for="search_phrase">Wuszukaj:</label><br>
    <input id="query" type="text" name="search_phrase" onkeyup="start_search();"/><br />

    <div id="search_res" >
        <div id="search_results"></div>
    </div>
</body>
</html>
<hr>
<?php
    if (!empty($_SESSION['user_id'])) {
        echo '<a href="logout">Wylogowanie</a>';
    }
    else 
        echo '<a href="login">Logowanie</a> | <a href="register">Rejestracja</a>';
?>
<hr>
    <a href="gallery">Galeria</a> | 
    <a href="session_preview">Stan sesji</a> | 
    <a href="edit_image">Dodaj obrazek</a> | 
    <a href="search">Wyszukiwarka</a> 
<hr>


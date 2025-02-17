<!doctype html>
<html lang="pl">
    <head>
        <meta charset="utf-8">
        <title>Login</title>
    </head>
    <body>
        <form method="POST">
            <label for="login">Login:</label><br>
            <input type="text" name="login" required /><br />

            <label for="pass">Password:</label><br>
            <input type="password" name="pass" required /><br />

            <input type="submit" value="Submit">
        </form>
        <a href="gallery">Anuluj</a>

        <?php if(isset($user_msg)): ?>
            <?= "<p style='color:red'>". $user_msg . "</p >" ?> 
        <?php endif ?>
    </body>
</html>
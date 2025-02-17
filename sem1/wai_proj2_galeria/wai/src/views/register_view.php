<!doctype html>
<html lang="pl">
<head>
    <meta charset="utf-8">
    <title>Rejestracja</title>
</head>
<body> 
    <form  method="POST">
        <label for="login">Login:</label><br>
        <input type="text" name="login" required /><br />

        <label for="pass">Email:</label><br>
        <input type="email" name="email" required /><br />

        <label for="pass">Hasło:</label><br>
        <input type="password" name="pass" required /><br />

        <label for="repeat_pass">Powtórz hasło:</label><br>
        <input type="password" name="repeat_pass" required /><br />
        
        <input type="submit" value="Submit">
    </form>
    
    <?php if(isset($user_msg)): ?>
            <?= "<p style='color:red'>". $user_msg . "</p >" ?> 
    <?php endif ?>
</body>
</html>
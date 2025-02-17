<!DOCTYPE html>
<html>
<head>
    <title>Edycja</title>
    <?php include "includes/head.inc.php"; ?>
</head>
<body>

<form method="post" enctype="multipart/form-data">

    <?php if ($image['wm-src'] != null): ?>
        <img src="<?= substr($image['wm-src'], strlen('/var/www/dev/src/web/')) ?>" >
    <?php endif ?>

    <label>
        <span>Autor:</span>

        <?php if ( $image['author'] === null && isset($_SESSION['login']) ): ?>
            <input type="text" name="author" value="<?= $_SESSION['login'] ?>" required/>
        <?php else: ?>
            <input type="text" name="author" value="<?= $image['author'] ?>" required/>
        <?php endif ?>
        
    </label>
    <label>
        <span>Tytuł:</span>
        <input type="text" name="title" value="<?= $image['title'] ?>" required/>
    </label>

    <label>
        <span>Znak wodny:</span>
        <input type="text" name="watermark_text" placeholder="Twój własny znak wodny..." required/>
    </label>

    <?php if(isset($_SESSION['login'])): ?>
        Prywatne:
        <input type="checkbox" name="private" />
        </br>
    <?php endif ?>

    <?php if( $image['og-src'] === null ): ?>
        Wskaż plik: <input name="ImageFile" type="file" />
    <?php endif ?>

    <input type="hidden" name="id" value="<?= $image['_id'] ?>">

    <div>
        <a href="images" class="cancel">Anuluj</a>
        <input type="submit" value="Zapisz"/>
    </div>
</form>
<?= $user_msg ?>

</body>
</html>

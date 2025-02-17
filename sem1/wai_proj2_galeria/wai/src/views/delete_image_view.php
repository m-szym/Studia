<!DOCTYPE html>
<html>
<head>
    <title>Usuwanie obrazka z galerii</title>
    <?php include "includes/head.inc.php"; ?>
</head>
<body>

<form method="post">
    Czy usunąć obrazek: <?= $image['author'] ?>?

    <input type="hidden" name="id" value="<?= $image['_id'] ?>">

    <div>
        <a href="images" class="cancel">Anuluj</a>
        <input type="submit" value="Potwierdź"/>
    </div>
</form>

</body>
</html>

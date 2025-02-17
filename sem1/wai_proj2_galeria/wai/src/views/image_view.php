<!DOCTYPE html>
<html>
<head>
    <title>Produkt</title>
    <?php include "includes/head.inc.php"; ?>
</head>
<body>

<h1>Tytuł: <?= $image['title'] ?></h1>

<p>Autor: <?= $image['author'] ?></p>

<?php if ($image['wm-src'] != null): ?>
    <img src="<?= substr($image['wm-src'], strlen('/var/www/dev/src/web/')) ?>" >
<?php else: ?>
    <img src="<?= substr($image['og-src'], strlen('/var/www/dev/src/web/')) ?>" >
<?php endif ?>



</body>
</html>

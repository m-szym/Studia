<!DOCTYPE html>
<html>
<head>
    <title>Obrazki</title>
    <?php include "includes/head.inc.php"; ?>
</head>
<body>



<table>
    <thead>
    <tr>
        <th></th>
        <th>Autor</th>
        <th>Tytuł</th>
        <th>Operacje</th>
    </tr>
    </thead>

    <tbody>
    <?php if (count($images)): ?>
        <?php foreach ($images as $image): ?>
            <?php if (in_array($image['_id'],$_SESSION['chosen_images'])): ?>
                <tr>
                    <td>
                        <img src="<?= substr($image['og-src'], strlen('/var/www/dev/src/web/')) ?>" style="height:100px;width:100px;">
                    </td>

                    <td>
                        <a href="view_image?id=<?= $image['_id'] ?>"><?= $image['author'] ?></a>
                    </td>

                    <td>
                        <a href="view_image?id=<?= $image['_id'] ?>"><?= $image['title'] ?></a>
                    </td>

                    <td>
                        <a href="edit_image?id=<?= $image['_id'] ?>">Edytuj</a> 
                        <a href="delete_image?id=<?= $image['_id'] ?>">Usuń</a>
                        <input type="checkbox" onclick="add_or_del('<?= $image['_id'] ?>');"/>
                    </td>
                </tr>
            <?php endif ?>
        <?php endforeach ?>
    <?php else: ?>
        <tr>
            <td colspan="3">Brak obrazków</td>
        </tr>
    <?php endif ?>
    </tbody>

    <tfoot>
    <tr>
        <td colspan="3">Łącznie: <?= count($images) ?></td>
        <td>
            <input type="button" value="Usuń z zapamiętanych" onclick="send_post(chosen_images);" />
        </td>
    </tr>
    </tfoot>
</table>


</body>
</html>

<!DOCTYPE html>
<html>
<head>
    <title>Obrazki</title>
    <?php include "includes/head.inc.php"; ?>
</head>
<body>

<?php include "includes/user_panel.php"; ?>



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
    <?php if (count($page_cont)): ?>
        <?php foreach ($page_cont as $image): ?>
            <tr>
                <td>
                    <a href="view_image?id=<?= $image['_id'] ?>" a>
                        <img src="<?= substr($image['thl-src'], strlen('/var/www/dev/src/web/')) ?>" >
                    </a>
                </td>

                <td>
                    <a href="view_image?id=<?= $image['_id'] ?>"><?= $image['author'] ?></a>
                </td>

                <td>
                    <a href="view_image?id=<?= $image['_id'] ?>"><?= $image['title'] ?></a>
                </td>

                <td>
                    <a href="edit_image?id=<?= $image['_id'] ?>">Edytuj</a> |
                    <a href="delete_image?id=<?= $image['_id'] ?>">Usuń</a> |
                    <input type="checkbox" onclick="add_or_del('<?= $image['_id'] ?>');" 
                        <?php 
                            if (isset($_SESSION['chosen_images']))
                            {
                                if(in_array($image['_id'], $_SESSION['chosen_images'])) 
                                    echo "checked";
                            }
                        ?>
                    />
                    <?php if($image['private'] === true): ?>
                        <strong>P</strong>
                    <?php endif ?>
                </td>
            </tr>
        <?php endforeach ?>
        <tr>
            <td colspan="4">
                <?php
                    if ($pages_n <= 1)
                        {}
                    else
                    {
                        for ($i = 1; $i < $pages_n ; $i++)
                        {
                            echo "<a href='gallery?page=$i'>[$i]</a> ";
                        }
                    }
                ?>
            </td>
        </tr>
    <?php else: ?>
        <tr>
            <td colspan="3">Brak obrazków</td>
        </tr>
    <?php endif ?>
    </tbody>

    <tfoot>
    <tr>
        <td colspan="3">Łącznie: <?= count($page_cont) ?></td>
        <td>
            <a href="edit_image">Dodaj nowe zdjęcie</a>
            <input type="button" value="Zapamiętaj wybrane" onclick="send_post(chosen_images);" />
        </td>
    </tr>
    </tfoot>
</table>


</body>
</html>

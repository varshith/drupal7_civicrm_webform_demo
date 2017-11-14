<?php

/**
 * @file
 * Default simple view template to display a list of rows.
 *
 * @ingroup views_templates
 */
?>
<div id="myCarousel" class="carousel slide" data-interval="3000" data-ride="carousel">
    <div class="carousel-inner">
        <?php
            $first = true;
        ?>
        <?php foreach ($rows as $id => $row): ?>
            <?php
                $bclasses = 'item';
                if($first){
                    $first = false;
                    $bclasses .= ' active';
                }
            ?>
        <div class="<?php print $bclasses; ?>">

            <div<?php if ($classes_array[$id]) { print ' class="' . $classes_array[$id] .'"';  } ?>>
                <?php print $row; ?>
            </div>
        </div>
        <?php endforeach; ?>
    </div>
    <a class="carousel-control left" href="#myCarousel" data-slide="prev">
        <span class="glyphicon glyphicon-chevron-left"></span>
    </a>
    <a class="carousel-control right" href="#myCarousel" data-slide="next">
        <span class="glyphicon glyphicon-chevron-right"></span>
    </a>
</div>

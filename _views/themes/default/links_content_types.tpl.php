<?php foreach($types as $key => $child){ ?>
<?php echo '<a href="' .
    (isset($child['path']) ? $child['path'] . '"' : '').
    (isset($css_id) ? ' id="'. $css_id . '"' : '').
    (isset($css_class) ? ' class="' .implode(' ', $css_class). '"' : '') .'>' .
    (isset($child['text']) ? $child['text'] : 'link').
    '</a>';
    ?>
<?php echo (isset($child['description']) ? '<p>'. $child['description'] . '</p>' : ''); ?>
<?php } ?>
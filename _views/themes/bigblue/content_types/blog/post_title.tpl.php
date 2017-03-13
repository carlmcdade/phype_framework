<?php $output = "\n" . '<h2'.
    (isset($id) ? ' id="'. $id .'"': '').
    (isset($class) ? ' class="'. $class .'"': '').
    (isset($alt) ? ' title="' .$alt . '"': ' alt=""').
    (isset($height) ? ' height="' .$height . '"': '').
    (isset($width) ? ' width="' . $width . '"': '').
    '>' . "\n" .
    (isset($post_title) ? $post_title  : '').
    '</h2>' . "\n";

    echo $output;
?>

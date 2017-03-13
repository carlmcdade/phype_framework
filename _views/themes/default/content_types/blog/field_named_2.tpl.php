<?php $output = "\n" . '<img'.
    (isset($id) ? ' id="'. $id .'"': '').
    (isset($class) ? ' class="'. $class .'"': '').
    (isset($alt) ? ' alt="' .$alt . '"': ' alt=""').
    (isset($height) ? ' height="' .$height . '"': '').
    (isset($width) ? ' width="' . $width . '"': '').
    (isset($src) ? ' src="' . $field_named_2 . '"': '').
    (isset($title) ? ' title="' .$title . '"': '').
    '/>' . "\n";
    $output .= (isset($checkbox) ? $checkbox  : '');
    echo $output;
?>

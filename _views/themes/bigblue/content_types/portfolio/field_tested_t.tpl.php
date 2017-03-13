<?php $output = "\n" . '<h2'.
    (isset($id) ? ' id="'. $id .'"': '').
    (isset($class) ? ' class="'. $class .'"': '').
    (isset($alt) ? ' title="' .$alt . '"': ' alt=""').
    (isset($height) ? ' height="' .$height . '"': '').
    (isset($width) ? ' width="' . $width . '"': '').
    '>' . "\n" .
    (isset($field_tested_t) ? $field_tested_t  : '').
    '</h2>' . "\n";

    echo $output;
?>

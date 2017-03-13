<?php $output = "\n" . '<div' .
    (isset($id) ? ' id="wrap-'. $id .'"': '').
    (isset($class) ? ' class="'. $class .'"': '').
    '><img'.
    (isset($id) ? ' id="'. $id .'"': '').
    (isset($class) ? ' class="'. $class .'"': '').
    (isset($alt) ? ' alt="' .$alt . '"': ' alt=""').
    (isset($height) ? ' height="' .$height . '"': '').
    (isset($width) ? ' width="' . $width . '"': '').
    (isset($field_named_2) ? ' src="' . $cck->_url($field_named_2, TRUE) . '"': '').
    (isset($title) ? ' title="' .$title . '"': '').
    '/></div>' .
    "\n";

    echo $output;
?>

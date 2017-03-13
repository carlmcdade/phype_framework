<?php $output = "\n" . '<img'.
    (isset($id) ? ' id="'. $id .'"': '').
    (isset($class) ? ' class="'. $class .'"': '').
    (isset($alt) ? ' alt="' .$alt . '"': ' alt=""').
    (isset($height) ? ' height="' .$height . '"': '').
    (isset($width) ? ' width="' . $width . '"': '').
    (isset($src) ? ' src="' . $cck->_url($src, TRUE) . '"': '').
    (isset($title) ? ' title="' .$title . '"': '').
    '/>' . "\n";
    $output .= (isset($checkbox) ? $checkbox  : '');
    echo $output;
?>

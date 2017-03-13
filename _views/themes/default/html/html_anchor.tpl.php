<?php echo '<a href="' .
    (isset($path) ? $cck->_url($path) . '"' : '').
    (isset($css_id) ? ' id="'. $css_id . '"' : '').
    (isset($css_class) ? ' class="' .implode(' ', $css_class). '"' : '') .'>' .
    (isset($text) ? $text : 'link').
    '</a>';
?>

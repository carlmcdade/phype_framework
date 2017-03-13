<?php
echo '<div id="'.$delta.'" class="blocks '.$delta.'">' .
     '<div class="block-title">' .(isset($title) ? $title : '') . "</div>\n" .
     '<div  class="block-content">' .(isset($content) ? $content : ''). "</div>\n" .
     '<div  class="block-footer">' .(isset($footer) ? $footer : ''). "</div>\n" .
     '</div>' ."\n";
 ?>
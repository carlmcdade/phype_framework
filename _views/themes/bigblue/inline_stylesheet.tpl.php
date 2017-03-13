<?php
   $output = "\n". (isset($code) && !empty($code) ? '<style>'. $code . '</style>' : '');
   echo $output;
?>
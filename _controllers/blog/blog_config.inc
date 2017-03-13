<?php

//Configuration File

//blog

//name
$settings['blog']['module']['name']['value'] = "Blog";
$settings['blog']['module']['name']['description'] = "module name";
//end name

//description
$settings['blog']['module']['description']['value'] = "Blog module used as an example of how to work with CCK. Designed to  work with the blog content type.";
$settings['blog']['module']['description']['description'] = "module purpose";
//end description

//version
$settings['blog']['module']['version']['value'] = "1.0";
$settings['blog']['module']['version']['description'] = "module version";
//end version

//dependancies
$settings['blog']['module']['dependencies']['value'] = "content";
$settings['blog']['module']['dependencies']['description'] = "comma delimited list of modules required by this module";
//end dependancies

return $settings['blog'];
?>






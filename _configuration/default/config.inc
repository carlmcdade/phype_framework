<?php 

//Configuration File

//site

//name
$settings['site']['name']['value'] = "Content Connection Kit";
$settings['site']['name']['description'] = "site name";
//end name

//description
$settings['site']['description']['value'] = "Web Architecture for web programmers";
$settings['site']['description']['description'] = "site purpose";
//end description

//frontpage
$settings['site']['frontpage']['value'] = "blog/blog_latest";
$settings['site']['frontpage']['description'] = "landing page url";
//end frontpage

//destination
$settings['site']['destination']['value'] = "admin/main";
$settings['site']['destination']['description'] = "default destination after log in";
//end destination

//theme
$settings['site']['theme']['value'] = "default";
$settings['site']['theme']['description'] = "templates and visual appearance";
//end theme

//files
$settings['site']['files']['value'] = "_files/";
$settings['site']['files']['description'] = "a directory set writable(chmod 777) by PHP";
//end files

//404_page
$settings['site']['404_page']['value'] = "cck/not_found";
$settings['site']['404_page']['description'] = "templates and visual appearance";
//end 404_page

//message_timeout
$settings['site']['message_timeout']['value'] = "3";
$settings['site']['message_timeout']['description'] = "flash messages stop appearing after this time in seconds";
//end message_timeout

//user_timeout
$settings['site']['user_timeout']['value'] = "3600";
$settings['site']['user_timeout']['description'] = "user is logged out automatically";
//end user_timeout

//content_title
$settings['site']['content_title']['value'] = "Content Connection Kit";
$settings['site']['content_title']['description'] = "default page title";
//end content_title

//timezone
$settings['site']['timezone']['value'] = "Europe/Berlin";
$settings['site']['timezone']['description'] = "time zone ex. Europe/Stockholm";
//end timezone

//content_footer
$settings['site']['content_footer']['value'] = " The PHyPe Framework software is owned and developed by &copy;2010 - Carl McDade - All rights reserved. Do you want to replace Drupal with something better  faster and easier to understand?";
$settings['site']['content_footer']['description'] = "footer message";
//end content_footer

//system

//version
$settings['system']['version']['value'] = "1.x";
$settings['system']['version']['description'] = "";
//end version

//base_url
$settings['system']['base_url']['value'] = "http://cck.fhqk.loc";
$settings['system']['base_url']['description'] = "http location all information is delivered from";
//end base_url

//approot
$settings['system']['approot']['value'] = DOCROOT;
$settings['system']['approot']['description'] = "";
//end approot


//controllers
$settings['system']['controllers']['value'] = "_controllers";
$settings['system']['controllers']['description'] = "directory containing controller modules";
//end controllers

//models
$settings['system']['models']['value'] = "_models";
$settings['system']['models']['description'] = "directory containing model classes";
//end models

//views
$settings['system']['views']['value'] = "_views";
$settings['system']['views']['description'] = "directory containing themes and templates";
//end views

//themes
$settings['system']['themes']['value'] = "_views/themes";
$settings['system']['themes']['description'] = "sub directory to views";
//end themes

//helpers
$settings['system']['helpers']['value'] = "_helpers";
$settings['system']['helpers']['description'] = "directory containing external libraries";
//end helpers

//owner

//name
$settings['owner']['name']['value'] = "carl";
$settings['owner']['name']['description'] = "username for the site owner";
$settings['owner']['id']['value'] = "1";
$settings['owner']['id']['description'] = "exclusive identification for owner in database";

//end name

//password
$settings['owner']['password']['value'] = "cck";
$settings['owner']['password']['description'] = "strong password fo thesite owner";
//end password

//email
$settings['owner']['email']['value'] = "carlmcdade@gmail.com";
$settings['owner']['email']['description'] = "the email address to be used by the site";
//end email

//developer

//modules
$settings['developer']['modules']['admin'] = "admin";
$settings['developer']['modules']['blog'] = "blog";
$settings['developer']['modules']['category'] = "category";
$settings['developer']['modules']['content'] = "content";
$settings['developer']['modules']['menu'] = "menu";
$settings['developer']['modules']['portfolio'] = "portfolio";
$settings['developer']['modules']['users'] = "users";
//end modules

//hooks
$settings['developer']['hooks']['hook_links'] = "hook_links";
$settings['developer']['hooks']['hook_forms'] = "hook_forms";
$settings['developer']['hooks']['hook_content'] = "hook_content";
$settings['developer']['hooks']['hook_blocks'] = "hook_blocks";
$settings['developer']['hooks']['hook_access'] = "hook_access";
$settings['developer']['hooks']['hook_permissions'] = "hook_permissions";
$settings['developer']['hooks']['hook_admin_links'] = "hook_admin_links";
$settings['developer']['hooks']['hook_module_links'] = "hook_module_links";
$settings['developer']['hooks']['hook_user_links'] = "hook_user_links";
$settings['developer']['hooks']['hook_debug'] = "hook_debug";
$settings['developer']['hooks']['hook_js'] = "hook_js";
$settings['developer']['hooks']['hook_css'] = "hook_css";
//end hooks

//module_files
$settings['developer']['module_files']['admin'] = "This file contains information and menus for the administration area of this module";
$settings['developer']['module_files']['form'] = "Forms used by this module should be described and variables info inputed  in this class file before rendering.";
$settings['developer']['module_files']['api'] = "Resources made available to services API in this class file per method";
//end module_files

//connections

//datasource_default
$settings['connections']['datasource_default']['resource'] = "cck.sqlite";
$settings['connections']['datasource_default']['hostname'] = "/var/vhosts/fhqk.com/www/informationtechnology/cck/_db/";
$settings['connections']['datasource_default']['username'] = "cck";
$settings['connections']['datasource_default']['pwd'] = "administrator";
$settings['connections']['datasource_default']['type'] = "sqlite3";
//end datasource_default

//datasource_0
$settings['connections']['datasource_0']['resource'] = "cck_development";
$settings['connections']['datasource_0']['hostname'] = "data.fhqk.com";
$settings['connections']['datasource_0']['username'] = "cck";
$settings['connections']['datasource_0']['pwd'] = "zZ_tofu8";
$settings['connections']['datasource_0']['type'] = "mysqli";
//end datasource_0

//localhost
$settings['connections']['localhost']['resource'] = "cck_development";
$settings['connections']['localhost']['hostname'] = "localhost";
$settings['connections']['localhost']['username'] = "root";
$settings['connections']['localhost']['pwd'] = "";
$settings['connections']['localhost']['type'] = "mysqli";
//end localhost

//api_keys
$settings['connections']['api_keys']['google'] = "";
$settings['connections']['api_keys']['facebook'] = "";
$settings['connections']['api_keys']['linkedin'] = "";
$settings['connections']['api_keys']['twitter'] = "";
//end api_keys

  return $settings; 
 ?>
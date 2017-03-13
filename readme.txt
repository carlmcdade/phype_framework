PHyPe Framework
========
created 2015-06-30
@author Carl McDade



    - Built and designed on PHP7 from scratch code.
    - Written in Pure PHP without a third party frameworks like Symfony
    - Content Types based system for ultimate flexibility in website creation
    - Field types are real HTML5 form elements
    - Templating is Pure PHP without any third party engine such as Twig or Smarty
    - No javascript or Javascript framework is used in Phype Framework.




Features:

      - content types
	  - field types
	  - default responsive design
	  - example microblog
	  - example portfolio
	  
Demo: http://demo.phype.net/

Requirements:

    - PHP version 7.0 or above.
	- SQLite3 enabled (included in PHP7)
	- JSON enabled
	- PDO enabled
    
    
Installation:

After meeting the requirements.

1. Create an instance by placing the archive contents in a directory or the root directory on the web server.
2. configure the instance 


Configuration:

    Go to the directory "_configuration" find the default directory and copy it. Rename the copy
	with the domain name ex. [www.myhost.com]

	Find the config.inc file and change the following line to match your domain or sub-domain

	$settings['system']['base_url']['value'] = "http://demo.phype.net";

	Once this has been set you can continue to do the configuration manually or web browse to
	http://your_domain.com/index.php?admin/main
	
	Tip: If you are going to develop simultaneously on a local PC then create a configuration copy for the local web server.
	

Architecture:

    _configuration
        [domain.name.com]
            config.inc
        [default]
            config.ini
    _controllers
        [module]
            [module].class.inc
            [module]_[type].class.inc
            [module]_config.inc
    _helpers
    _models
    _views
        themes
            [theme_name]
                [page]
                    page.tpl.php
                [html]

    _css
    _files
    _js
    cck.php
    index.php
    .htaccess


    
@TODO:

 - Web forms.



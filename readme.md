[![Phype](http://demo.phype.net/_views/themes/default/images/phype_logo_header.jpg)](http://demo.phype.net/)


PHP7 Framework
==============
created 2011-06-30
@author Carl McDade



    - Built and designed on PHP7 from scratch code in strict MVC format.
    - Written in Pure PHP without a third party frameworks like Symfony
    - Content Types based system for ultimate flexibility in website creation
    - Field types are real HTML5 form elements
    - Template creation in Pure PHP without any third party engine such as Twig or Smarty
    - CSS3 based mobile device ready and responsive theme system
    - No javascript or Javascript framework is used in Phype Framework. Instead Phype uses CSS pseudo-classes


## Table of Contents

* [Requirements](#requirements)
* [Installation](#installation)
* [Configuration](#configuration)
* [Architecture](#architecture)
* [MVC Routing](#mvc-routing)
    * [Overview](#overview)
    * [Examples](#examples)
* [Module Building](#module-building)
    * [Overview](#overview-1)
    * [Examples](#examples-1)
* [Template System](#template-system)
* [Themes](#thems)
* [Content Types](#content-types)
* [Forms](#forms)
* [Fields](#fields)



### Features

      - content types
	  - field types
	  - default responsive design
	  - example microblog
	  - example content types with image uploader, blog
	  - built-in inline documentation system for faster development
	  
Demo: http://demo.phype.net/

Contact Author : https://twitter.com/carlmcdade

### Requirements

    - PHP version 7.0 or above.
	- SQLite3 enabled (included in PHP7)
	- JSON enabled
	- PDO enabled
    
    
### Installation

After meeting the requirements the installation of Phype framework could not be easier.

1. Create an instance by placing the archive contents in a directory or the root directory on the web server.
2. configure the instance
3. browse to the directory or root directory of the instance.


### Configuration

Go to the directory "_configuration" find the default directory and copy it. Rename the copy with the domain name ex. [www.myhost.com]
Find the config.inc file and change the following line to match your domain or sub-domain   

```	
$settings['system']['base_url']['value'] = "http://demo.phype.net";
```
Once this has been set you can continue to do the configuration manually or web browse to http://your_domain.com/index.php?admin/main
	
```
Tip: If you are going to develop simultaneously on a local PC then create a configuration 
copy for the local web server.
```	

### Architecture

```    _configuration
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
```

## MVC Routing

### Overview

[![Phype](http://demo.phype.net/_views/themes/default/images/MVC.png)](http://demo.phype.net/)

The Phype framework interprets asked for URLs in a MVC pattern to output provided by PHP namespaces, classes and methods. The bootstrap of the index.php file detects the route and forwards the request to the controller/modules in a set order with options. Class and method in the request  the uri fo the request can be recieved in the following forms.
 
      
* default path selection: [class]/[method]/ example: blog/blog_list
* optional explicit path: [namespace]\[class]/[method][arguments] example: content\content_admin/content_types/[arguments]
* section path via naming convention : [suffix]/[namespace]/[method]  example;  [admin || form || api]/blog/blog_posts


### Examples

```

http://demo.phype.net/index.php?blog/blog_latest
 the above URL translates to http://demo.phype.net/index.php?[namespace || class]/[method]
 
http://demo.phype.net/index.php?admin/admin/module/blog
 the above URL translates to http://demo.phype.net/index.php?[[namespace || class]_[type]]/[method]/[argument]
 
 Using this you can trace the code being called.
  _controllers
          [module]
              [module].class.inc
              [module]_[type].class.inc
``` 
            
  Entering the proper strings from the above URL translates to demo.phype.net/index.php? [["admin"] OR ["admin_admin"]]/["module"]/["blog"].
  Which leads to the following method locate in the "admin" module directory in the "admin_admin".class.inc file.
  
```php
  function module()
      {
          global $cck;
          $args = $cck->_args();
          $output = '';
          // get all links from each class controller
          $main_menu = $cck->_hooks('hook_links');
          $admin_menu = $cck->_hooks('hook_admin_links', 'admin');
  
          $variables['page_title'] = 'system configuration';
          $variables['main_navigation'] = $cck->_menu_links($main_menu, 'links_main_menu');
          $set = $cck->_get_module_config($args[0]);
          //exit($cck->_debug($set));
          if(is_array($set) && $set !== FALSE)
          {
              $admin_form = new admin_form();
              $form = $admin_form->admin_form_view_settings($set,$args[0]);
          }
          else
          {
              $form = 'no settings file found';
          }
  
          $variables['content'] = $form ;
  
          print $cck->_view('page_admin', $variables);
  
      }

 
```

[view this](http://demo.phype.net/index.php?admin/admin/module/blog)

## Module Building

### Overview

Modules are a set of class declaration files, any desired helper classes and a configuration file. Contain them in a directory of the same name
as the modules main class file.

```
_controllers
        [module]
            [module].class.inc 
            [module]_[type].class.inc
            [module]_config.inc

```

### Examples

```
_controllers
        blog
            blog.class.inc; //required
            blog_admin.class.inc; // optional for hooking into admin GUI
            blog_api.class.inc; // optional for json service
            blog_form.class.inc; // 
            blog_config.inc

```
[view this](http://demo.phype.net/index.php?admin/admin/documentation/blog)


## Template System

### Views

## Themes

### CSS3

The developer needs to be familiar with CSS3 and pseudo-elements

### HTML5

Phype framework uses only HTML5 forms and elements

### Responsive

Out of the box responsive default themes. 

## Content Types

Content types are virtual containers for the forms and fields needed to create, update and delete user content. 

[view this](http://demo.phype.net/index.php?admin/content/content_type_list)

Building content types is easy. Just pick a name and start adding any number of HTML5 form elements to the content type.

[view this](http://demo.phype.net/index.php?admin/content/content_type_add)


## Forms

Phype uses HTML5 supported form elements. Form elements are listed in the administration and can be edited in the GUI.

[view this](http://demo.phype.net/index.php?admin/content/content_type_fields/1)

## Fields

Fields are virtual containers for HTML5 form elements

[view this](http://demo.phype.net/index.php?admin/content/content_type_fields/1)

Once a field has been added to a content type that field can then be edited further.

[view this](http://demo.phype.net/index.php?admin/content/content_type_field_edit/1/3)
    
@TODO:

 - Web forms.



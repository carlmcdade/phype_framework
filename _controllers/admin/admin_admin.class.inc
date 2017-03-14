<?php

/**
 *
 * @author Carl McDade
 * @copyright Carl McDade
 * @since 2011
 * @version 2.0
 * @license PHyPe Framework
 *
 * @link http://fhqk.com/cck
 * ==================================================================
 *  Copyright 2011 Carl Adam McDade Jr.
 * Licensed under the PHyPe Framework, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://demo.phype.net/license.txt
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

namespace admin;

use \SQLite3;
use \Exception;


class admin_admin{
	
	private $common;
	public  $menu;
	public  $section;
	public  $module;

    function __construct()
    {
        //Test the Common settings
        $this->section = __CLASS__;
        $this->module = __NAMESPACE__;
        
    }

    function hook_admin_links()
    {
        $link = 'links';
    	
    	$var[$link][1] = array(
        		'text' => 'Site settings',
        		'path' => 'admin/' . $this->module . '/site'
        		);
        $var[$link][2] = array(
        		'text' => 'System configuration',
        		'path' => 'admin/' . $this->module . '/configuration'
        		);


        return $var;
    }

    /**
     * @param int $index
     * @return mixed
     */
    function hook_sub_links($index = 0)
    {
        $link = 'links';

        $var[$link][1] = array(
            'text' => 'admin',
            'path' => 'admin/' . $this->module . '/site'
        );
        $var[$link][2] = array(
            'text' => 'admin settings',
            'path' => 'admin/' . $this->module . '/configuration'
        );

        $var[$link][3] = array(
            'text' => 'admin database',
            'path' => 'admin/' . $this->module . '/database'
        );

        return $var;
    }

    /**
     * @return array
     */
    function hook_access()
    {
        $authorize = array(
			'ConClass1/action_one' => array('access foo'),
			'ConClass1/action_two' => array('access baz'),
			'ConClass1/action_three' => array('access boo','access suisse'),
        );

        return $authorize;
    }


    /**
     *
     */
    function categories()
    {
        global $cck;
        // get all links from each class controller
    	$menu = $cck->_hooks('hook_links');
    	$variables['navigation'] = $cck->_menu_links($menu, 'links_main_menu',' | ');
    	
    	$form = new \form("GettingStarted", 300);
                $form->addElement(new \Element_Textbox("My Textbox:", "MyTextbox"));
                $form->addElement(new \Element_Button);
                $output = $form->render(true);
               
        $variables['content'] = $output;
    	
    	print $cck->_view('page_admin', $variables);
    }

    /**
     *   print the doc block for methods
     */
    function documentation()
    {
        global $cck;
        $args = $cck->_args();


        // get all links from each class controller
        $menu = $cck->_hooks('hook_links');
        if(strpos($args[0], '_'))
        {
            $namespaced = explode('_', $args[0]);
            $controller_list = $cck->_get_module_controllers($namespaced[0], $args[0]);
        }
        else
        {
            $namespaced[] = $args[0] ;
            $controller_list = $cck->_get_module_controllers($args[0]);
        }

//exit($cck->_debug($controller_list));
        // build sub menu
        $sub_menu = array();
        $sub_menu['links'][] = array(
            'text' => 'Core',
            'path' => 'admin/admin/documentation/core',
        );
        foreach($controller_list as $controller => $file)
        {
            $sub_menu['links'][] =
                array(
                    'text' => $controller,
                    'path' => 'admin/admin/documentation/'. $controller,
                );
        }


        $javascript = $cck->_hooks('hook_js');
        $css = $cck->_hooks('hook_css');

        $variables['navigation'] = $cck->_menu_links($menu, 'links_main_menu');
        $variables['sub_navigation'] = $cck->_module_links($sub_menu,
            array(
                'template'=>'links_sub_menu',
                'index' => $this->module
            ));
        $variables['page_title'] = 'Documentation';
        $variables['content_title'] = 'Documentation ::' . $args[0];


        //$output = $cck->_debug($args);
        if($args[0] == 'core')
        {
            $api = $cck;
        }
        else
        {
            $class = CLASS_SEPERATOR . $namespaced[0] . CLASS_SEPERATOR . $args[0];
            if(class_exists($class))
            {
                $api = new $class();
            }
            else
            {
                exit('configuration file access denied');
            }
        }

        $documentation = $cck->_get_file_documentation($api);
        //echo $api_name . ' (outside class):';
        //print '<pre>' . print_r($modules, 1) . '</pre>';
        //$output .= '<pre>' . print_r($documentation, 1) . '</pre>';
        $output = '<p>The documentation available in the  '. strtoupper($namespaced[0]) . '  Module  for the  '. strtoupper($args[0]). '  file </p>'  ."\n";
        $resources  = get_class_methods($api);
        // build links as content table

        foreach($resources as $endpoint)
        {
            // filter system functions and class magic methods

            $docblock = $cck->_get_file_documentation($api,$endpoint);
            $doc_build = array();
            $description = '';

            //clean the docblock of markers
            $doc_block_arr = explode("\n",$docblock);
            foreach($doc_block_arr as $string)
            {
                $comment_markers = array('/**','/*','*/','* ','*');
                foreach($comment_markers as $marker)
                {
                    $string = str_replace($marker,'',$string);
                }
                if(trim($string) == '')
                {
                    continue;
                }
                else
                {
                    $doc_build[] = trim($string);
                }

            }

            $docblock = implode("\n", $doc_build);

            // check for API section of module


            if(!empty($doc_build))
            {
                if(isset( $namespaced[1]) &&  $namespaced[1] == 'api' )
                {
                    $variables['path'] = 'api'. DIRECTORY_SEPARATOR . $namespaced[0]. '/'. $endpoint;
                    $variables['text'] = $endpoint;
                    $description = '' . $cck->_link('links',$variables) . '<br />'.'<pre>'. $docblock . '</pre>';


                }
                else
                {
                    $description = '' . $endpoint . '<br />'.'<pre>'. $docblock . '</pre>';
                }


            }

            else
            {
                $description = '' . $endpoint . '<br /><pre>Sorry, Nothing written for this item. Ask the developer to update and check back later. </pre>';
            }

            $output .= $description;

        }

         //$cck->_debug(get_declared_classes());

        $variables['content'] = $output;
        print $cck->_view('page_admin', $variables);
        return;

    }

    function site()
    {
        global $cck;
        if($cck->_user_access() == FALSE)
        {
            $form = new \users\users_form();
            $show_form = $form->users_login_form();
            $variables['content'] = $show_form ;
            print $cck->_view('page_login', $variables);
            return;
        }
        $output = '';
        // get all links from each class controller
        $main_menu = $cck->_hooks('hook_links');
        $admin_menu = $cck->_hooks('hook_admin_links', 'admin');

        $variables['page_title'] = 'site settings';
        $variables['main_navigation'] = $cck->_menu_links($main_menu, 'links_main_menu');
        $settings = $cck->_model('admin','settings','site');
        //exit($cck->_debug($settings));
        $admin_form = new admin_form();
        $form = $admin_form->admin_form_site_settings($settings,'site');
        $variables['content'] = $form ;

        print $cck->_view('page_admin', $variables);

    }

    function site_settings_save()
    {
        global $cck,$settings;
        if($cck->_user_access() == FALSE)
        {
            $form = new \users\users_form();
            $show_form = $form->users_login_form();
            $variables['content'] = $show_form ;
            print $cck->_view('page_login', $variables);
            return;
        }
        $output = '';
        // get all links from each class controller
        $main_menu = $cck->_hooks('hook_links');
        $admin_menu = $cck->_hooks('hook_admin_links', 'admin');

        $variables['page_title'] = 'site settings';
        $variables['main_navigation'] = $cck->_menu_links($main_menu, 'links_main_menu');
        //$settings = $cck->_model('admin','settings');
        //exit($cck->_debug($settings));

        //$output =  $cck->_debug($_POST['setting']);

        //$output=  $cck->_debug(array('site' => $settings['site']));

        $outputX =  array_replace_recursive($settings,$_POST['setting']);
        $section = 'Configuration File';
        $output =  $cck->_array_to_print('$settings',$outputX, $section);
        //$output2 =  $cck->_array_to_print('$developer',$developer);


        $content = "<?php \n" . $output . "\nreturn \$settings; \n?>";
        $output .=  $cck->_file_write(INI_FILENAME,$content);


        $variables['content'] = $cck->_debug($output);

        print $cck->_view('page_admin', $variables);

    }

    function configuration()
    {
        global $cck;

        $output = '';
        // get all links from each class controller
        $main_menu = $cck->_hooks('hook_links');
        $admin_menu = $cck->_hooks('hook_admin_links', 'admin');

        $variables['page_title'] = 'system configuration';
        $variables['main_navigation'] = $cck->_menu_links($main_menu, 'links_main_menu');
        $settings = $cck->_model('admin','settings','system');
        //exit($cck->_debug($settings));
        $admin_form = new admin_form();
        $form = $admin_form->admin_form_view_settings($settings,'system');
        $variables['content'] = $form ;

        print $cck->_view('page_admin', $variables);

    }

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

    function email_contact_categories()
    {
        global $cck;
        $output = '';
        //some variables to load into the view will appear as $[variable name]
    	$main_menu = $cck->_hooks('hook_links');
    	$sub_menu = $this->sub_links();

        $variables['main_navigation'] = $cck->_menu_links($main_menu, 'links_main_menu');
    	//$variables['sub_navigation'] = $cck->_menu_links($sub_menu, 'links_sub_menu', ' | ');
               
        $variables['content'] = $output;
    	
    	print $cck->_view('page_admin', $variables);
    }
    
    function admin_response()
    {
        global $cck;
    	$menu = $cck->_hooks('hook_links');
    	$variables['main_navigation'] = $cck->_menu_links($menu,'links_main_menu');
    	
    	$variables['content'] = 'admin response';
        print $cck->_view('page_admin', $variables);
    }

    /**
     *
     */
    function admin_controllers()
    {
        global $cck, $settings;

        $active_controllers = $settings['modules'];
        $class_suffix = array_flip($settings['module_files']);

        $existing_controllers = $settings['system']['controllers'];
        $dir = DOCROOT .  DIRECTORY_SEPARATOR . $existing_controllers;


        foreach(glob($dir.'/*', GLOB_ONLYDIR) as $key => $directory) {
            $name = basename($directory);
            $list = glob($directory . "/*.inc");
            $assoc_list = array();
            foreach($list as $item)
            {
                $parts = explode('/',$item);
                $parts = array_reverse($parts);
                $labels = explode('.',$parts[0]);
                $label = $labels[0];
                $assoc_list[$label] = $item;

            }

            //$list = $assoc_list;

            // gather list of controller classes available
            // start with main controller
            $list_active[$name][] =  $name;
            // create list of child controllers per module
            foreach($class_suffix as $tail)
            {
                $list_active[$name][] = $name . '_'. $tail;
            }

            $modules['in_directory'][$name] = $assoc_list;
            if(in_array($name, $active_controllers))
            {
                $modules['in_configuration_list'][$name] = $list;

            }

        }

        foreach($list_active as $item => $value )
        {
            //print '<pre>' . print_r($item, 1) . '</pre>';
            foreach($value as $key )
            {
                //print '<pre>' . print_r($key, 1) . '</pre>';
                if(isset($modules['in_directory'][$item][$key]) && in_array($item,$active_controllers)){
                    $autoload[$key] = $modules['in_directory'][$item][$key];
                }

            }
        }


        print '<pre>' . print_r($autoload, 1) . '</pre>';
        //print '<pre>' . print_r($active_controllers, 1) . '</pre>';
        //print '<pre>' . print_r($list_active, 1) . '</pre>';
       // print '<pre>' . print_r($modules['activated_list'], 1) . '</pre>';

    }

    /**
     *  A SQL ite database instance is needed for more advanced use such
     *  as the creation of content types and fields
     */
    function admin_database()
    {
        global $cck, $settings;

        //print '<pre>' . print_r(get_declared_classes(), 1) . '</pre>';

         // check for the existence of an SQLite Database

         //  login method for SQLIte
         // username > store
         // password > encycrypt
         // encrypted password  > encrypt database name
         //  create long file name unique_id to  [name 255 characters] . [extension name]
         try
         {
             //create or open the database
             $path = DOCROOT . DIRECTORY_SEPARATOR . '_db'. DIRECTORY_SEPARATOR .'cck.sqlite';
             $db = new SQLite3($path,SQLITE3_OPEN_CREATE);
             $db->close();
         }
         catch(Exception $e)
         {
             die($e);
         }
     }
}

?>

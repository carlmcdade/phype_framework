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


// classes used by the global $cck object from the globalspace
use \PDO;
use \PDOException;

// classes used by this module controller class

use \form;
use \Element_Textbox;
use \Element_Button;

class admin{
	
	public  $common;
	public  $menu;
	public  $title = 'Administration';
	public  $module;
	
	
    function __construct()
    {
        //Test the Common settings
        $this->module = __NAMESPACE__;
        $this->section = __CLASS__;
    }
    
    /**
     *   Navigation hook for all modules
     */
    
    function hook_links()
    {
    	$link = 'links';
    	
    	$var[$link][1] = array(
        		'text' => 'Administration', 
        		'path' => $this->module . '/main',
    			'alias' => 'index',
    			'controller' => $this->module,
    			'action' => 'main',
    			'css_class' => array($this->module, 'main_item'),
        		'css_id' => $this->module 
        		);
        
        return $var;
    }
  
    function hook_access()
    {
        $authorize = array(
			$this->module . '/main' => array('access foo'),
			$this->module . '/blocks' => array('access baz'),
			$this->module . '/themes' => array('access boo'),
        );

        return $authorize;
    }

    

    function main()
    {
        global $cck;
        $output = '';
        
        
    	// get all links from each class controller
        $main_menu = $cck->_hooks('hook_links');
    	$admin_menu = $cck->_hooks('hook_admin_links', 'admin');
    	
    	$variables['page_title'] = $this->title;
        $variables['content_title'] = 'Index';
    	$variables['navigation'] = $cck->_menu_links($main_menu, 'links_main_menu');


    	$variables['admin_navigation'] = $cck->_menu_links($admin_menu, 'links_admin_index_menu');


        $output .= 'Administration links to all active controller modules.';
               
        $variables['content'] = $output;
    	
    	print $cck->_view('page_admin_index', $variables);
    }

    function site()
    {
        global $cck, $settings;
        $output = '';
        // get all links from each class controller
        $main_menu = $cck->_hooks('hook_links');
        $admin_menu = $cck->_hooks('hook_admin_links', 'admin');

        $variables['page_title'] = 'site settings';
        $variables['main_navigation'] = $cck->_menu_links($main_menu, 'links_main_menu');
        $settings = $cck->_model('admin','settings');
        $admin_form = new admin_form();
        $form = $admin_form->admin_form_site_settings($settings);
        $variables['content'] = $form;

        print $cck->_view('page_admin', $variables);

    }

    function blocks()
    {
         global $cck;
        $output = '';
    	// get all links from each class controller
        $main_menu = $cck->_hooks('hook_links');
    	$admin_menu = $cck->_hooks('hook_admin_links', 'admin');
    	
    	$variables['page_title'] = $this->title;
    	$variables['main_navigation'] = $cck->_menu_links($main_menu, 'links_main_menu');
    	
    	$form = new form("GettingStarted", 300);
                $form->addElement(new Element_Textbox("New block:", "new_block_name"));
                $form->addElement(new Element_Button);
                $output .= $form->render(true);
               
        $variables['content'] = $output;
    	
    	print $cck->_view('page_admin', $variables);
    }
    
    function themes()
    {
        global $cck;
        // get all links from each class controller
        $main_menu = $cck->_hooks('hook_links');
    	$admin_menu = $cck->_hooks('hook_admin_links', 'admin');
    	
    	$variables['page_title'] = $this->title;
    	$variables['main_navigation'] = $cck->_menu_links($main_menu);
    	
    	$variables['content'] = 'admin form submit';
        print $cck->_view('page_admin', $variables);
    }
}

?>

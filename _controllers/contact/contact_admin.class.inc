<?php

/**
 * Content Connection Kit
 * @author Carl McDade
 * @copyright Carl McDade
 * @since 2011
 * @version 2.0
 * @license FHQK Universal
 *
 * @link http://fhqk.com/cck
 * ==================================================================
 *  Copyright 2011 Carl Adam McDade Jr.
 * Licensed under the FHQK Universal, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://cck.fhqk.com/license.txt
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

namespace contact;

use Common;

class contact_admin{
	
	private $common;
	public  $page_title = 'Contact Administration';
	public  $section;
	public  $module;
	public  $settings;



    function __construct()
    {
        //Test the Common settings
        $this->section = __CLASS__;
        $this->module = __NAMESPACE__;
        
    }
    
    /**
    *   Sub navigation is not a hook and displayed per call by section
    */
    
    function hook_sub_links($index = 0)
    {      
        $link = 'links';        
        $var = array();       
        $var[$link][2] = array(
        		'text' => 'Categories',
        		'path' => 'admin/' . $this->module . '/contact_list'
        );       
        $var[$link][1] = array(
        		'text' => 'Add Contact',
        		'path' => $this->section . '/contact_add'
        );
        return $var;      
    }
    

    function hook_admin_links()
    {
        $link = 'links';
        $var = array();
        $var[$link][1] = array(
        		'text' => 'Contacts lists', 
        		'path' => 'admin/' . $this->module . '/contacts'
        		);
        $var[$link][2] = array(
        		'text' => 'Categories', 
        		'path' => 'admin/' . $this->module . '/categories'
        		);

        return;// $var;
    }  
    
    function categories()
    {
    	global $cck, $settings;
    	
    	// get all links from each class controller
        $main_menu = $cck->_hooks('hook_links');
    	$sub_menu = $this->hook_sub_links();
    	
    	$output = '';
    	
    	$variables['page_title'] = $this->page_title; 	
    	$variables['main_navigation'] = $cck->_menu_links($main_menu, 'links_main_menu');
		$variables['sub_navigation'] = $cck->_module_links($sub_menu,
			array(
				'template'=>'links_sub_menu',
				'index' => $this->module
    			));
        $variables['content_title'] = ucfirst( __FUNCTION__);
    	$variables['content'] = 'example text for ' . $variables['content_title'];
    	print $cck->_view('page_admin', $variables);
    }
    
    function contacts()
    {
    	global $cck, $settings;
    	
    	// get all links from each class controller
        $main_menu = $cck->_hooks('hook_links');
    	$sub_menu = $this->hook_sub_links();
    	
    	$output = '';
    	
    	$variables['page_title'] = $this->page_title; 	
    	$variables['main_navigation'] = $cck->_menu_links($main_menu, 'links_main_menu');
		$variables['sub_navigation'] = $cck->_module_links($sub_menu,
			array(
				'template'=>'links_sub_menu',
				'index' => $this->module
    			));
        $variables['content_title'] = ucfirst( __FUNCTION__);
    	$variables['content'] = 'example text';
    	print $cck->_view('page_admin', $variables);
    }
    
 
    
}

?>

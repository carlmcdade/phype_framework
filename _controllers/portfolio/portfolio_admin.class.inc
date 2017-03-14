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

namespace portfolio;

class portfolio_admin{
	
	private $common;
	public  $menu;
	public  $page_title = "Portfolio Administration";
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
        		'text' => 'Portfolio', 
        		'path' => 'admin/'. $this->module.'/list_all'
        		);
        	$var[$link][2] = array(
        		'text' => 'Portfolio add',
        		'path' => 'admin/' . $this->module . '/add'
        		);
        	return;// $var;
    }

    function add()
    {
        global $cck;
        // get all links from each class controller
        $main_menu = $cck->_hooks("hook_links");
        $sub_menu = $this->hook_admin_links();


        $variables["navigation"] = $cck->_menu_links($main_menu, "links_main_menu");
        $variables['sub_navigation'] = $cck->_module_links($sub_menu,
            array(
                'template'=>'links_sub_menu',
                'index' => $this->module
            ));
        $variables["page_title"] = $this->page_title;
        $variables["content_title"] = "Add project";
        $variables['content'] = 'add content form for portfolio content type' ;
        print $cck->_view('page_admin', $variables);
    }
    function list_all()
    {
        global $cck;
        // get all links from each class controller
        $main_menu = $cck->_hooks("hook_links");
        $sub_menu = $this->hook_admin_links();


        $variables["navigation"] = $cck->_menu_links($main_menu, "links_main_menu");
        $variables['sub_navigation'] = $cck->_module_links($sub_menu,
            array(
                'template'=>'links_sub_menu',
                'index' => $this->module
            ));
        $variables["page_title"] = $this->page_title;
        $variables["content_title"] = "Project list";
        $variables['content'] = 'list of postings for portfolio content type' ;
        print $cck->_view('page_admin', $variables);
    }
}

?>

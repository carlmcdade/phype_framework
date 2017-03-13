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
namespace menu;

class menu_admin {

	public  $page_title = 'Menu Administration';
	public  $module;
	public  $section;
	


    function __construct()
    {
    	    //Test the Common settings
    	    $this->section = __CLASS__;
    	    $this->module = __NAMESPACE__;
    }

    /**
     * @return mixed
     *
     * Examples:
     * explicit path: using $this->section will output a url of content\content_admin/content_type_field_edit/3
     * note the use of a backslash to denote a section in the url
     *
     * implied path: using admin. '/' .$this->module will output a url of admin/content_admin/content_type_field_edit/3
     * this is the more common url format though the code is slightly more verbose
     *
     * both of the above examples point to the same page in the system.
     */
    function hook_admin_links()
    {
    	    $link = 'links';
    	    $var[$link][1] = array(
    	    	    'text' => 'Menu add',
    	    	    'path' =>  'admin/'. $this->module . '/view_menu'
    	    	    );
    	    $var[$link][2] = array(
    	    	    'text' => 'Menus',
    	    	    'path' => 'admin/'. $this->module . '/view_all_menus'
    	    	    );
    	    return; // $var;
    }
    
    /**
    *   Sub navigation is not a hook and displayed per call by section
    */
    
    function hook_sub_links($index = 0)
    {
    	    $link = 'links';
    	    $var[$link][1] = array(
    	    	    'text' => 'Menu add item', 
    	    	    'path' => 'admin/'. $this->module . '?admin/menu/menu_add_item'
    	    	    );
    	    $var[$link][2] = array(
    	    	    'text' => 'Menu remove item',
    	    	    'path' => 'admin/'. $this->module . '/menu_remove_item'
    	    	    );
    	    $var[$link][3] = array(
    	    	    'text' => 'Menu list items',
    	    	    'path' => 'admin/menu/menu_list_items'
    	    	    );
    	    return $var;
    }

    function view_menu()
    {
        global $cck;

        $variables['page_title'] = 'page title';

        $variables['content_title'] = 'content title';

        $output =  'view of a single menu';
        $variables['content'] = $output;
        print $cck->_view('default', $variables);
    }

    function view_all_menus()
    {
        global $cck;

        $variables['page_title'] = 'page title';

        $variables['content_title'] = 'content title';

        $output =  'view of all available menus';
        $variables['content'] = $output;

        print $cck->_view('default', $variables);
    }
	
}
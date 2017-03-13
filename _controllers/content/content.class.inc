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


namespace content;

// classes used by the global $cck object from the globalspace
use \PDO;
use \PDOException;
use \form;

class content{
	

	public  $section;
	public  $module;


    function __construct()
    {
    	// Common settings
    	$this->module = __NAMESPACE__;
        $this->section = __CLASS__;
    }

    function __destruct()
    {
        //
    }

    function hook_links()
    {

        $link = 'links';
        $var = array();


        return $var;

    }
    
    function hook_module_links($index = NULL)
    {
    	    $link = 'links';
    	    
            $var[$link][1] = array(
    	    	    'text' => 'Content',
    	    	    'path' => $this->module . '/content_user_list'
    	    	    );  	    
    	    $var[$link][2] = array(
    	    	    'text' => 'Content Add',
    	    	    'path' => $this->module . '/content_add'
    	    	    );
    	    return $var;
    }

    function hook_css()
    {
        $css = 'css';

        $var[$css][] = array(
            'link' => '_css/'.$this->module.'.css',
        );

        return $var;
    }

    /**
     * @return mixed
     * Hook Javascript file links or raw javascript to the page
     */
    function hook_js()
    {
        global $cck,$settings;
        $js = 'js';

        $var[$js][1] = array(
            'link' => '_js/wysihtml5/parser_rules/advanced.js',
            'inline' => '',
        );

        $var[$js][2] = array(
            'link' => '_js/wysihtml5/dist/wysihtml5-0.3.0.js',
            'inline' => '',
        );
        return $var;
    }
    


    function content_user_list()
    {
    	   
    	global $cck;
    	$output = 'A list of this users content';
    	   
    	   // get all links from each class controller
    	$menu = $cck->_hooks('hook_links');    	
    	$sub_menu = $cck->_hooks('hook_module_links');
    	
    	$variables['navigation'] = $cck->_menu_links($menu, 'links_main_menu');
    	$variables['sub_navigation'] = $cck->_module_links($sub_menu[$this->module],
    		array(
    			'template'=>'links_sub_menu',
    			'index' => $this->module
    			)); 
    	   $variables['page_title'] = 'Content';
    	   $variables['content_title'] = 'Content list';
    	   $variables['content'] = $output;
    	   print 'users';
    }
    

    
}

?>

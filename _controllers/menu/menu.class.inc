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


class menu{

	public  $section;
	public  $module;


    function __construct()
    {
        //Test the Common settings
        $this->section = __CLASS__;
        $this->module = __NAMESPACE__;
        
    }
    
    /**
    *   Navigation hook for all modules
    */

    function hook_links()
    {
        $link = 'links';

        $var[$link][1] = array(
            'text' => 'Start',
            'path' => '',
            'css_class' => array($this->module, 'main_item'),
            'css_id' => $this->module,
            'weight' => -1
        );
        return $var;
    }
    
    
    /**
    *   Sub navigation is not a hook and displayed per call by controller and action / class->method section
    */
    
    function hook_sub_links($index = 0)
    {
        $var = array();
    	
        $var[$this->section][$this->section . '_1'] = array(
        		'text' => 'archive',
        		'path' => '?' . $this->section . '/view'
                    );
        
    	$var[$this->section][$this->section . '_2'] = array( 
					'text' => 'archive', 
					'path' => '?' . $this->section . '/view_all'
					);
		$var[$this->section][$this->section . '_3'] = array(
					'text' => 'by category', 
					'path' => '?' . $this->section . '/add'
					);
		$var[$this->section][$this->section .'_4'] = array(
					'text' => 'latest', 
					'path' => '?' . $this->section . '/remove'
					);

        return $var;
    }

    function hook_admin_links()
    {
        $link = 'links';

        $var[$link][1] = array(
            'text' => 'New link',
            'path' => 'admin/'. $this->module.'/blog_links'
        );

        return $var;
    }

}

?>
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


class category_admin{

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
        $var['c5_1'] = array(
        		'text' => 'C5 Admin one', 
        		'path' => '?admin/ConClass5/action_one'
        		);
        $var['c5_2'] = array(
        		'text' => 'C5 Admin two', 
        		'path' => '?admin/ConClass5/action_two'
        		);

        return $var;
    }
    
    function hook_access()
    {
        $authorize = array(
			'ConClass1/action_one' => array('access foo'),
			'ConClass1/action_two' => array('access baz'),
			'ConClass1/action_three' => array('access boo','access suisse'),
        );

        return $authorize;
    }

    

    function action_one()
    {
        // get all links from each class controller
    	$menu = $this->common->get_hooks('hook_admin_links', 'Admin');
    	
    	$variables['title'] = $this->title;
    	$variables['navigation'] = $this->common->ber_links_menu($menu, 'links_admin_menu', $separater = ' | ');
    	
    	$form = new Form("GettingStarted", 300);
                $form->addElement(new Element_Textbox("My Textbox:", "MyTextbox"));
                $form->addElement(new Element_Button);
                $output .= $form->render(true);
               
        $variables['content'] = $output;
    	
    	print $this->common->ber_view('page_admin', $variables);
    }

    function action_two()
    {
        //some variables to load into the view will appear as $[variable name]      	
    	$menu = $this->common->get_hooks('hook_admin_links', 'Admin');
    	
    	$variables['title'] = $this->title;
    	$variables['navigation'] = $this->common->ber_links_menu($menu, 'links_admin_menu',$separater = ' = ');
    	
    	$form = new Form("GettingStarted", 300);
                $form->addElement(new Element_Textbox("My Textbox:", "MyTextbox"));
                $form->addElement(new Element_Button);
                $output .= $form->render(true);
               
        $variables['content'] = $output;
    	
    	print $this->common->ber_view('page_admin', $variables);
    }
    
    function action_three()
    {
        $menu = $this->common->get_hooks('hook_admin_links', 'Admin');
        
        $variables['title'] = $this->title;
    	$variables['navigation'] = $this->common->ber_links_menu($menu, 'links_admin_menu',$separater = ' - ');
    	
    	$variables['content'] = 'admin form submit';
        print $this->common->ber_view('page_admin', $variables);
    }
}

?>

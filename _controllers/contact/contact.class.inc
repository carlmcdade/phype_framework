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
//cannot do this when using ZF2, causes an error class not found

class contact {
	
	private $common;
	public  $menu;
	public  $section;
	public  $module;

	
	function __construct()
	{
		//Test the Common settings
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
		$var[$link][1] = array(
			'text' => 'Contact', 
        		'path' => 'contact/contact',
    			'alias' => 'contact_us',
    			'controller' => 'contact',
    			'action' => 'contact',
    			'css_class' => array($this->module, 'main_item'),
        		'css_id' => $this->module,
                'weight' => 8
        		);
        	return $var;
        }
        
        function contact()
        {
        	global $cck;
        	/// get all links from each class controller
        	$menu = $cck->_hooks('hook_links');

			$form = array();
			$form['name'] = 'contact';
			$form['id'] = 'contact';
			$form['method'] = 'POST';
			$form['action'] = '?'.$this->module.'/send/';
			$form['title'] = 'send a message';
			$form['enctype'] = 'text/plain';

			$form['elements']['firstname'] =
				array(
					'type' => 'text',
					'id'=> 'myfirstname',
					'class'=> 'myclassname',
					'title'=> 'first name',
					'label'=> 'name',
					'name'=> 'firstname',
					'value'=> '',
					'placeholder'=> 'firstname',
				);
			$form['elements']['lastname'] =
				array(
					'type' => 'text',
					'id'=> 'mylastname',
					'class'=> 'mylastname',
					'title'=> 'myname',
					'name'=> 'lastname',
					'label'=> 'last name',
					'value'=> '',
					'placeholder'=> 'lastname',
				);
			$form['elements']['address'] =
				array(
					'type' => 'text',
					'id'=> 'address',
					'class'=> 'address',
					'title'=> 'address',
					'name'=> 'address',
					'label'=> 'your address',
					'value'=> '',
					'placeholder'=> 'address',
				);
			$form['elements']['email'] =
				array(
					'type' => 'email',
					'id'=> 'email',
					'class'=> 'email',
					'title'=> 'email',
					'name'=> 'email',
					'label'=> 'email',
					'value'=> '',
					'placeholder'=> 'email@email.com',
				);
			$form['elements']['city'] =
				array(
					'type' => 'select',
					'label' => 'city',
					'id'=> 'mycityname',
					'class'=> 'mycityname',
					'name'=> 'cityname',
					'form'=> 'cityname',
					'options'=> array(
						array(
							'type' => 'option',
							'id'=> 'city_1',
							'class'=> 'city_1',
							'value'=> 'berlin',
							'description'=> 'berlin',
						),
						array(
							'type' => 'option',
							'id'=> 'city_2',
							'class'=> 'city_2',
							'value'=> 'stockholm',
							'description'=> 'stockholm',
						),
						array(
							'type' => 'option',
							'id'=> 'city_3',
							'class'=> 'city_3',
							'value'=> 'san francisco',
							'description'=> 'san francisco',
						),
					),
				);
			$form['elements']['send'] =
				array(
					'type' => 'submit',
					'id'=> 'send',
					'class'=> 'send',
					'title'=> 'send',
					'name'=> 'send',
					'label'=> 'send',
					'value'=> 'send',
					'before'=> '<div></div>',
				);




            $form_container = $cck->_form($form,'html_form');
            $form_content['content_left'] = $form_container;
            $output = $cck->_view('page_content_50_50',$form_content);
		
        $variables['navigation'] = $cck->_menu_links($menu, 'links_main_menu');
        $variables['page_title'] = 'Contact';
        $variables['content_title'] = 'Contact us';
		$variables['content'] = $output;
		print $cck->_view('default', $variables);
	}

	function send()
	{
		global $cck;
		$menu = $cck->_hooks('hook_links');
		$variables['navigation'] = $cck->_menu_links($menu, 'links_main_menu');
		$variables['page_title'] = 'Contact';
		$variables['content_title'] = 'Contact us';
		$output = 'sending contact form';
		$variables['content'] = $output;
		print $cck->_view('default', $variables);
	}
}

?>

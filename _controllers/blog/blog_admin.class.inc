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

/**
 *  This class is the administration controller for the Blog Module
 *  Links for the methods and functionality appear in the administration
 *  index
 *
 *  browsing to the API will show a list of  resources available in the API controller of this module
 *  ?admin/blog/blog_api maps to the method blog_api()
 *
 */

namespace blog;

use \PDO;
use \PDOException;



class blog_admin{
	
	private $common;
	public  $page_title = 'Blog Administration';
	public  $section;
	public  $module;
	public  $settings;
	
	
	function __construct()
	{
		//Test the Common settings
		$this->section = __CLASS__;
		$this->module = __NAMESPACE__;
		
		// Get configuration settings
    	}
    	
    function __destruct()
    {
    		//
    }

	function index()
	{
		return 'default method to every controller';
	}
    	
    function hook_sub_links()
    {
		$link = 'links';

    		$var[$link][0] = array(
        		'text' => 'Settings',
        		'path' => 'admin/'. $this->module.'/blog_settings'
        		);

			$var[$link][1] = array(
				'text' => 'Blog API',
				'path' => 'admin/'. $this->module.'/blog_api'
			);

        	return $var;
	}

        /**
        *  Sub navigation is not a hook and displayed per call by section
        */

	function hook_admin_links($index = 0)
	{
		$link = 'links';
		$var[$link][0] = array(
			'text' => 'Settings',
			'path' => 'admin/' . $this->module . '/blog_settings'
		);

		$var[$link][1] = array(
        		'text' => 'Data',
        		'path' => 'admin/' . $this->module . '/blog_list_all'
        		);
        $var[$link][2] = array(
        		'text' => 'Create',
        		'path' => 'admin/' . $this->module . '/blog_add'
        		);

		$var[$link][4] = array(
			'text' => 'API',
			'path' => 'admin/admin/documentation/blog_api'
		);
        	return $var;
        }
        
	function hook_access()
	{
		$authorize = array(
			$this->module . '/blog_add' => array('access foo'),
        	$this->module . '/blog_edit' => array('access baz'),
        	$this->module . '/blog_save' => array('access boo','access suisse'),
		);

		return $authorize;
	}
        
	function blog_form($form = array(), $values = array(), $sort = 'ASC')
	{
        return 'form array in json format';
	}
			
    

	function blog_add()
	{
		global $cck, $settings;
		$menu = $cck->_hooks('hook_links');
		$sub_menu = $this->hook_admin_links();


		$css = $cck->_hooks('hook_css');

		$variables['navigation'] = $cck->_menu_links($menu, 'links_main_menu');
		$variables['sub_navigation'] = $cck->_module_links($sub_menu,
			array(
				'template'=>'links_sub_menu',
				'index' => $this->section
			));

		$variables['page_title'] = $this->page_title;
		$variables['content_title'] = 'Add Blog';
		$output = $this->blog_form();
		$variables['content'] = $output;
		print $cck->_view('page_admin', $variables);
	}
	
	function blog_edit()
	{
		// get all links from each class controller
		$main_menu = $this->common->get_hooks('hook_links');
		$sub_menu = $this->sub_links();

		// Get the content for this id
		$content_id = ber_pathpart(3);

		// get the row values in an array with the column names ascii2ebcdic associative keys
		$query = 'SELECT * FROM content_blog WHERE id =' . $content_id;
		$result = $this->dbc->query($query);
		$values = $result->fetchAll(PDO::FETCH_ASSOC);
		
		// Editing configuration
		$form = array(
			"action" => "index.php?admin/blog/blog_save",
			"method" => "post",
			"resourcesPath" => "_helpers/PFBC/Resources"
			);

		// place the values in a form
        $configure = array(
            "action" => "?content/content_save/blog",
            "method" => "post",
            "resourcesPath" => "_helpers/Form/Resources");

		$output = $this->blog_form($configure, $values);
		$variables['content'] = $content_id . $output;
		$variables['page_title'] = $this->page_title;
		$variables['content_title'] = 'Edit post';
		$variables['main_navigation'] = $this->common->ber_links_menu($main_menu, 'links_main_menu');
		$variables['sub_navigation'] = $this->common->ber_links_menu($sub_menu, 'links_sub_menu');
		print $this->common->ber_view('page_admin', $variables);
	}
	
	function blog_save()
	{
		// get all links from each class controller
		$main_menu = $this->common->get_hooks('hook_links');
		$admin_menu = $this->hook_admin_links();
		
		$variables['page_title'] = $this->page_title;
		$variables['content_title'] = 'Blog Save';
		$variables['main_navigation'] = $this->common->ber_links_menu($main_menu, 'links_main_menu');      
		$variables['content'] = print_r($_POST, 1);
		print $this->common->ber_view('page_admin', $variables);
	}
	
	/**
	*    This is a user administration function where the main admin menu is not shown
	*    although the user is in the administration section they are not given the default
	*    admin menu
	*/
	
	function blog_list_all()
	{
		global $cck, $settings;
		$menu = $cck->_hooks('hook_links');
		$sub_menu = $this->hook_admin_links();
		$javascript = $cck->_hooks('hook_js');
		$css = $cck->_hooks('hook_css');

		$variables['navigation'] = $cck->_menu_links($menu, 'links_main_menu');
		$variables['sub_navigation'] = $cck->_module_links($sub_menu,
			array(
				'template'=>'links_sub_menu',
				'index' => $this->section
			));
		
		$variables['page_title'] = $this->page_title;
		$variables['content_title'] = 'Blog Data';

        // Get the content column values
		$connect = $cck->_dbconnect('datasource_default');
		
		// table header from database
		$result = $connect->prepare('SELECT * FROM content_containers WHERE content_type_id="1" ');
		$result->execute();
		$table_fields = $result->fetchAll(PDO::FETCH_COLUMN);
			
		for ($i = 0; $i < $result->columnCount(); $i++)
		{
			$col = $result->getColumnMeta($i);
			$columns[] = $col['name'];
		}
		
		$query = $connect->query("SELECT * FROM content_containers_data");
		$query->execute();
		$table_rows = $query->fetchAll();
		// validate content
			
		if(!empty($table_rows)) 	
		{
	    	// set table variables for view table template
			$table['header'] = $columns; 			
			$table['rows'] = $table_rows;
            $output = 'This listing is provided for use as a human readable reference for building a web service API in JSON or XML format' . "\n";
			$output .= $cck->_view('css_table', $table);
	    }
	    else
	    {
		    $output = 'Query incomplete or nothing found!';
	    }

		$variables['content'] = $output;
		print $cck->_view('page_admin', $variables);
	}

    function blog_feed()
    {
		global $cck, $settings;
		$menu = $cck->_hooks('hook_links');
		$sub_menu = $this->hook_admin_links();

		$javascript = $cck->_hooks('hook_js');
		$css = $cck->_hooks('hook_css');

		$variables['navigation'] = $cck->_menu_links($menu, 'links_main_menu');
		$variables['sub_navigation'] = $cck->_module_links($sub_menu,
			array(
				'template'=>'links_sub_menu',
				'index' => $this->section
			));

		$variables['page_title'] = $this->page_title;
		$variables['content_title'] = 'Blog Feed';
        $output = 'xml feed';
        $variables['content'] = $output;
        print $cck->_view('default', $variables);
    }
	
	function blog_settings()
	{   
		global $cck, $settings;
		$menu = $cck->_hooks('hook_links');
		$sub_menu = $this->hook_admin_links();

		$javascript = $cck->_hooks('hook_js');
		$css = $cck->_hooks('hook_css');

		$variables['navigation'] = $cck->_menu_links($menu, 'links_main_menu');
		$variables['sub_navigation'] = $cck->_module_links($sub_menu,
			array(
				'template'=>'links_sub_menu',
				'index' => $this->section
			));
		$variables['page_title'] = 'Blog Settings';
		$variables['content_title'] = 'Blog Settings';
		$variables['content'] = 'list of all blog pages with admin links';
		print $cck->_view('page_admin', $variables);
	}
        
    function blog_test()
    {
	     print 'tested';
    }


	function blog_api()
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

		 $api = new blog_api();
		 $documentation = $cck->_get_file_documentation($api);
		 //echo $api_name . ' (outside class):';
		 //print '<pre>' . print_r($modules, 1) . '</pre>';
		 $output = '<pre>' . print_r($documentation, 1) . '</pre>';
		 $output .= 'this is a list of resources available in the '. $this->module . ' API.' ."\n";
         $resources  = get_class_methods($api);
         // build links as content table
         $description = '<br />';
         foreach($resources as $endpoint)
         {
             // filter system functions and class magic methods
             if($endpoint[0] == '_')
             {
                 continue;
             }
             $docblock = $cck->_get_file_documentation($api,$endpoint);
             $variables['path'] = 'api'. DIRECTORY_SEPARATOR . $this->module. DIRECTORY_SEPARATOR .  $endpoint;
             $variables['text'] = $endpoint;
             $description .= '<pre>'.$docblock . '</pre><br />' . $cck->_link('links', $variables ) . '<br />';
         }

		 $variables["page_title"] = $this->page_title;
		 $variables["content_title"] = "Blog API";
		 $variables['content'] = $output. $description ;
		 print $cck->_view('page_admin', $variables);
	 }
}

/**
 * Content Connection Kit
 * @author Carl McDade
 * @copyright Carl McDade
 * @since 2011
 * @version 2.0
 * @license Apache 2.0
 *
 * @link http://fhqk.com/cck
 * ==================================================================
 *  Copyright 2011 Carl Adam McDade Jr.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
?>

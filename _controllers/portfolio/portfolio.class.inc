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

namespace portfolio;

use \PDO;
use \content\content_form;

class portfolio {
	
	private $common;
	public  $menu;
	public  $module;
    public  $section;
	
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
	
	/**
	 * Main menu hook
	 * @return multitype:string
	 */

    function hook_links()
    {
        
        $link = 'links';
    	
    	$var[$link][1] = array(
        		'text' => 'Portfolio', 
        		'path' => $this->module . '/list_all',
        		'css_class' => array($this->module, 'main_item'),
        		'css_id' => $this->module 
        		);
        return $var;
        
    }

    function hook_blocks()
    {

        $block = 'container';

        $var[] = array(
            'title' => 'Portfolio',
            'content' => $this->module . '/content',
            'css_class' => array($this->module, 'blocks '),
            'css_id' => $this->module
        );

        $var[] = array(
            'title' => 'gallery',
            'content' => $this->module . '/gallery',
            'css_class' => array($this->module, 'blocks '),
            'css_id' => $this->module
        );

        return $var;

    }
    
    /**
     *   Sub navigation is a hook and displayed per call by hook_links
     */
    
    function hook_module_links($index = 0)
    {
    
    	$link = 'links';
    	 
    	$var = array();
    	 
    	$var[$link][1] = array(
    			'text' => 'Projects',
    			'path' => $this->module . '/list_all'
    	);
    	$var[$link][2] = array(
    			'text' => 'Featured',
    			'path' => $this->module . '/featured'
    	);

    	return $var;
    }
    function hook_css()
    {
        $css = 'css';

        $var[$css][1] = array(
            'link' => '_css/'.$this->module.'.css',
        );


        return $var;
    }


    /**
     *  List of user blogs by id
     */
    function list_all()
    {
        global $cck;
        $args = $cck->_args(func_get_args());



        // get all links from each class controller
        $menu = $cck->_hooks('hook_links');

        // get sublinks just for this module
        $sub_menu = $cck->_hooks('hook_module_links');

        $variables['navigation'] = $cck->_menu_links($menu, 'links_main_menu');
        $variables['sub_navigation'] = $cck->_module_links($sub_menu[$this->module],
            array(
                'template'=>'links_sub_menu',
                'index' => $this->module
            ));
        $variables['page_title'] = 'Portfolio';
        $variables['content_title'] = 'all projects';

        $output = '';
        $message = '';

        // Get the content column values
        $connect = $cck->_dbconnect('datasource_default');

        // table header from database
        $table_name = 'content_containers';
        $container_result = $connect->query("PRAGMA table_info(" . $table_name . ")");
        $container_result->setFetchMode(PDO::FETCH_ASSOC);
        $table_fields = $container_result;

        // table rows and field values
        $result = $connect->prepare("SELECT cc.ccid,content_type_field_data as title,cc.author_id, cc.date_created FROM content_containers AS cc JOIN content_containers_data AS ccd ON cc.ccid=ccd.ccid WHERE cc.content_type_id = 2 AND ccd.content_type_field='field_tested_t'");
        $result->execute();
        $table_rows = $result->fetchAll();

        // validate content
        if(!empty($table_rows))
        {
            $columns = array();
            $user_columns = array('view');

            // table header
            foreach ($table_rows[0] as $key => $value)
            {
                if(!is_numeric($key))
                {
                    $columns[] = $key;
                }

            }


            foreach($user_columns as $extra)
            {
                array_push($columns, $extra);
            }


            foreach($table_rows as $key => $value)
            {
                $admin_links = array(
                    //'delete'=> 'admin/'. $this->module . DIRECTORY_SEPARATOR . 'content_delete' . DIRECTORY_SEPARATOR . $value['ccid'],
                    //'edit'=> 'admin/'. $this->module . DIRECTORY_SEPARATOR . 'content_edit' . DIRECTORY_SEPARATOR . $value['ccid'],
                    'view'=> $this->module . '/' . 'post' . '/' . 'view' . '/' . $value['ccid']
                );

                foreach($admin_links as $text => $path)
                {
                    $links['text'] = $text;
                    $links['path'] = $path;


                    array_push($table_rows[$key], $cck->_view('links',$links));
                }


                //echo $cck->_debug($value);
                unset($table_rows[$key][0],$table_rows[$key]['ccid']);
                $table_rows[$key][3] = $cck->_format_datetime($table_rows[$key][3]);
                $table_rows[$key]['date_created'] =  $cck->_format_datetime($table_rows[$key]['date_created']);
            }
            unset($columns[0]);
            $rows = $table_rows;

            // set table variables for view table template
            $table['header'] = $columns;
            $table['rows'] = $rows;
            $output = $cck->_view('css_table', $table);
        }
        else
        {
            $output = 'Query incomplete or nothing found!';
        }


        if(!empty($args))
        {
            $output .= '<pre>'. print_r($args,1) . '</pre>';
        }

        // final output variables for view page template
        $variables['content'] = $output;
        print $cck->_view('default', $variables);
    }
    
    function featured()
    {
        global $cck;
    	
    	// get all links from each class controller
    	$menu = $cck->_hooks('hook_links');
    	$sub_menu = $cck->_hooks('hook_module_links');
    	
    	
    	$variables['navigation'] = $cck->_menu_links($menu, 'links_main_menu');
    	$variables['sub_navigation'] = $cck->_module_links($sub_menu[$this->module],
    		array(
    			'template'=>'links_sub_menu',
    			'index' => $this->module
    			));
    	$variables['page_title'] = 'Portfolio';
    	$variables['content_title'] = 'Featured projects';
    	$variables['content'] = 'featured project';
    	print $cck->_view('default', $variables);
    }

    function post()
    {
        global $cck;
        $args = $cck->_args();
        $operation = (isset($args[0]) ? $args[0] : FALSE);
        $ccid = (isset($args[1]) ? $args[1] : FALSE);

        if($ccid != FALSE)
        {
            $container = $cck->_model('content','content_get_container', $ccid);
        }

        $operations = array('view','edit','delete','save','add','submit');
        $output = 'no operation';
        if(($operation != FALSE) && in_array($operation, $operations))
        {

            switch($operation)
            {
                case 'view':
                    $this->portfolio_post_view($container);
                    break;
                case 'edit':
                    $this->portfolio_post_edit($container);
                    break;
                case 'delete':
                    $this->portfolio_post_delete($container);
                    break;
                case 'save':
                    $this->portfolio_post_save();
                    break;
                case 'submit':
                    $this->portfolio_post_submit();
                    break;
                case 'add':
                    $this->portfolio_post_add(2);
                    break;
            }
        }
        else
        {
            exit($output);
        }


        return;

    }

    function portfolio_post_view()
    {
        global $cck;
        $args = $cck->_args();

        if(isset($args[1]))
        {

            $ccid = $args[1];
            $container = $cck->_model('content', 'content_get_container', $ccid);
            $data = $cck->_model('content', 'content_get_container_data', $ccid);
            $content_type_info = $cck->_model('content', 'content_type_get', $container['content_type_id']);

            //$output = $cck->_debug($container);
            //$output .= $cck->_debug($data);
            //$output .= $cck->_debug($form);
            //exit ($output);


            //$output = $cck->_debug($container);
            //$output .= $cck->_debug($data);
            //$output .= $cck->_debug($form);
            //exit ($output);
            if($container == FALSE)
            {
                $output = 'post not found';
            }
            else
            {
                //$form = new content_form();
                $output = $cck->_page_builder($container, $data);
                //$output = $cck->_page($container, $data);
                foreach($output['elements'] as $variable => $value)
                {
                    $variables['content'][$variable] = (isset($value['value']) ? $value['value'] : '');
                }
            }

        }
        else
        {
            $output = 'post not found';
        }

        $variables['page_title'] = $content_type_info['label'];
        $variables['content_title'] = $content_type_info['label'] .' view';
        $variables['content_type'] = $content_type_info['type'];

        // add a css stylesheet link to template
        $css = $cck->_hooks('hook_css');
        $style = $cck->_add_css($css[$this->module]['css']);
        $variables['stylesheets'] = $style;
        print $cck->_view('page', $variables);

    }
    
}

?>

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

namespace blog;

// classes used by the global $cck object from the globalspace
use \PDO;
use \content\content_form;

// classes used by this module controller class


class blog{
	
	private $common;
	public  $menu;
	public  $section;
	public  $module;

    /**
     *  set this modules constants
     */
    function __construct()
    {
        //Test the Common settings
        $this->module = __NAMESPACE__;
        $this->section = __CLASS__;
    }
    
    /**
    *   Navigation hook for all modules
    *   the array keys appear as $variables in the template file for links
    *   link.tpl.php, spaces will be replaced by underscores.
    */
    function __destruct()
    {
    	   //
    }

    /**
     *  Hook stylesheets links or raw styles to the page
     *
     */
    function hook_css()
    {
        $css = 'css';

        $var[$css][1] = array(
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

    /**
     * @return mixed
     */
    function hook_links()
    {       
        $link = 'links';
    	
    	$var[$link][1] = array(
        		'text' => 'Blog',
        		'path' => $this->module . '/blog_latest',
                'attach_menu' => array(), // attach a child menu
        		'css_class' => array($this->module, 'main_item'),
        		'css_id' => $this->module 
        		);
        return $var;
    }
    
    /**
    *   Sub navigation is a hook and displayed per call by hook_links
    */
    function hook_module_links($index = 0)
    {
        global $cck;
    	$link = 'links';
    	
    	$var = array();
    	
    	$var[$link][1] = array( 
					'text' => 'Recent',
					'path' => $this->module . '/blog_latest',
                    'weight' => -1
					);
		/*$var[$link][2] = array(
					'text' => 'Categories', 
					'path' => $this->module . '/blog_categories',
                    'weight' => 1
					);*/
		$var[$link][2] = array(
					'text' => 'List all',
					'path' => $this->module . '/blog_list',
                    'weight' => 0
					);
		$var[$link][3] = array(
                    'text' => 'New post',
                    'path' => $this->module . '/post/add',
                    'weight' => 2,
                    'access' => $cck->_user_access(),
		);
				
		
        
        return $var;
    }

    /**
     * @return array
     */
    function hook_access()
    {
    	    $authorize = array(
    	    	    $this->module . '/blog_post_add' => array('access foo'),
    	    	    $this->module . '/blog_post_edit' => array('access baz'),
    	    	    $this->module . '/blog_post_delete' => array('access boo'),
    	    	    );
    	    return $authorize;
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
                    $this->blog_post_view($container);
                    break;
                case 'edit':
                    $this->blog_post_edit($container);
                    break;
                case 'delete':
                    $this->blog_post_delete($container);
                    break;
                case 'save':
                    $this->blog_post_save();
                    break;
                case 'submit':
                    $this->blog_post_submit();
                    break;
                case 'add':
                    $this->blog_post_add(1);
                    break;
            }
        }
        else
        {
            exit($output);
        }


        return;

    }

    /**
     *  List of user blogs by id
     */
    function blog_list()
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
    	    $variables['page_title'] = 'Blog';
    	    $variables['content_title'] = 'All blog posts';

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
			$result = $connect->prepare("SELECT cc.ccid,content_type_field_data as title,cc.author_id, cc.date_created FROM content_containers AS cc JOIN content_containers_data AS ccd ON cc.ccid=ccd.ccid WHERE cc.content_type_id = 1 AND ccd.content_type_field='post_title'");
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
                        'view'=> $this->module . DIRECTORY_SEPARATOR . 'post' . DIRECTORY_SEPARATOR . 'view' . DIRECTORY_SEPARATOR . $value['ccid']
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

    function blog_categories()
    {
        global $cck;
    	
    	//some variables to load into the view will appear as $[variable name]
    	$menu = $cck->_hooks('hook_links');
    	$sub_menu = $cck->_hooks('hook_module_links');
    	
    	$variables['navigation'] = $cck->_menu_links($menu, 'links_main_menu');
        $variables['sub_navigation'] = $cck->_module_links($sub_menu[$this->module],
            array(
                'template'=>'links_sub_menu',
                'index' => $this->module
            ));
        $variables['page_title'] = 'Blog';
    	$variables['content_title'] = 'Categories';
    	$variables['content'] = 'Categories and taxonomy';
    	print $cck->_view('default', $variables);
    }
    
    function blog_latest()
    {
    	global $cck;
        $content_type_id = 1;
    	// get all links from each class controller
    	$menu = $cck->_hooks('hook_links');
    	$sub_menu = $cck->_hooks('hook_module_links');
        //$javascript = $cck->_hooks('hook_js');
        //$css = $cck->_hooks('hook_css');
    	
    	$variables['navigation'] = $cck->_menu_links($menu, 'links_main_menu');
    	$variables['sub_navigation'] = $cck->_module_links($sub_menu[$this->module],
    		array(
    			'template'=>'links_sub_menu',
    			'index' => $this->module
    			)); 
    	$variables['page_title'] = 'Blog';
    	$variables['content_title'] = 'Recent blog posts';


        //$posted['content_fields'] = $cck->_model('content','content_get_type_fields', array('content_type_id' => '1'));
        
        //connect to the database using the ini settings
        $connect = $cck->_dbconnect('datasource_default');

    	$ccid_query = $connect->prepare("SELECT ccid,administration_title,author_id, date_created FROM content_containers WHERE content_type_id='" . $content_type_id . "' ORDER BY strftime('%s', date_created) DESC");
    	$ccid_query->execute();
        $post_list = $ccid_query->fetchAll(PDO::FETCH_ASSOC);

        $output = '';
        if(is_array($post_list))
        {
                foreach ($post_list as $key => $post)
                {
                    // get post data
                    $post_data = $cck->_model('content','content_get_container_data', $post['ccid']);


                    // format split db  data fields and values into single data list


                    $posted[$post['ccid']]['container']['data'] = $post_data;


                    //container data
                    foreach($post as $con_key => $con_info)
                    {
                        $posted[$post['ccid']]['container'][$con_key] = $con_info;
                    }


                    // links



                }


	    		// set table variables for view table template

	    }
	    else
	    {
            $output = 'Query incomplete or not found! <a href="../cck/?content/view/1">test content</a>';
	    }

    	
    	// set page header
        //$variables['javascript'] = $cck->_add_js($this->module);
        //$variables['stylesheets'] = $cck->_add_css($css[$this->module]['css']);
        $content['posts'] = $posted;
        $variables['content'] = $cck->_view('page_content_blog_list', $content);
        print $cck->_view('default', $variables);

    }

    /**
     * @return string
     *
     * this method is protected to prevent direct access via the uri sent to the router
     */
    private function blog_post_view($container = NULL)
    {
        global $cck;

       //exit( $cck->_debug($container));

        $field_data = $cck->_model('content','content_get_container_data', $container['ccid']);
        $container = $cck->_model('content', 'content_get_container', $container['ccid']);

        if($field_data)
        {
            $data = array_merge($field_data, $container);
            $output = $cck->_view('page_content_blog_post', $data);
        }
        else
        {
            $variables['class'] = 'error';
            $variables['error_message'] = 'This content has been removed or cannot be found because of a system error. Check with site administrator';
            $output = $cck->_view('page_content_error_message', $variables);
        }


        //$output .= $cck->_debug($data);
        //$output .= $cck->_debug($data);


        // get all links from each class controller
        $menu = $cck->_hooks('hook_links');
        $sub_menu = $cck->_hooks('hook_module_links');

        $variables['navigation'] = $cck->_menu_links($menu, 'links_main_menu');
        $variables['sub_navigation'] = $cck->_module_links($sub_menu[$this->module],
            array(
                'template'=>'links_sub_menu',
                'index' => $this->module
            ));
        $variables['page_title'] = 'Blog';
        $variables['content_title'] = 'Post view';
        $variables['content'] = $output;
        // add a css stylesheet link to template
        $css = $cck->_hooks('hook_css');
        $style = $cck->_add_css($css[$this->module]['css']);
        $variables['stylesheets'] = $style;
        print $cck->_view('default', $variables);
    }
    


    private function blog_post_add($content_type_id = NULL)
    {
        global $cck, $settings;
        if($cck->_user_access() == FALSE)
        {
            $form = new \users\users_form();
            $show_form = $form->users_login_form();
            $variables['content'] = $show_form ;
            print $cck->_view('page_login', $variables);
            return;
        }
        $args = $cck->_args();




        // this page requires arguments so return nothing if not found;


        // get all links from each class controller
        $menu = $cck->_hooks('hook_links');
        $sub_menu = $cck->_hooks('hook_module_links');
        $javascript = $cck->_hooks('hook_js');
        $css = $cck->_hooks('hook_css');

        $variables['navigation'] = $cck->_menu_links($menu, 'links_main_menu');
        $variables['sub_navigation'] = $cck->_module_links($sub_menu[$this->module],
            array(
                'template'=>'links_sub_menu',
                'index' => $this->module
            ));
        $variables['page_title'] = 'Blog';
        $variables['content_title'] = 'Add blog posts';

        $content_type_info = $cck->_model('content','content_type_get',$content_type_id);



        // content container fields
        $connect = $cck->_dbconnect('datasource_default');
        $table_name = 'content_containers';
        $container_result = $connect->query("PRAGMA table_info(" . $table_name . ")");
        $container_result->setFetchMode(PDO::FETCH_ASSOC);


        foreach ($container_result as $conkey => $convalue)
        {

            $elements[$convalue['name']] = $convalue['name'];

        }

        //print $cck->_debug($elements);


        $field_result = $connect->prepare("SELECT ctf.field_id,ctf.field_type_id, ctf.label, ctf.name,ctf.required, ments.type as element_type FROM content_types_fields AS ctf JOIN content_types_fields_types AS ments ON ctf.field_type_id = ments.field_type_id WHERE ctf.content_type_id='" . $content_type_id . "'");
        $field_result->execute();
        $data_fields = $field_result->fetchALL(PDO::FETCH_ASSOC);

        // container data
        foreach ($data_fields as $datakey => $datavalue)
        {

            $elements['data'][$datavalue['field_id']] = $datavalue;

        }
        // add data section
        //print $cck->_debug($elements);

        $form = array();
        $form['name'] = 'content_type_'. $content_type_info['type'] .'_add';
        $form['id'] = 'content_type_'. $content_type_info['type'] .'_add';
        $form['method'] = 'POST';
        $form['action'] = $cck->_url($this->module .'/blog_post_submit/');
        $form['title'] = 'add blog post';
        $form['enctype'] = '';

        // check for any previous form submission
        $previous = (isset($_SESSION[$form['name'].'_'. session_id()]) ? $_SESSION[$form['name'].'_'. session_id()] : '');

        //print $cck->_debug($previous);

        foreach($elements as $key => $value)
        {
            switch($key)
            {
                case 'ccid':
                    if(isset($previous['form_elements'][$value]['value']))
                    {
                        $ccid = $previous['form_elements'][$value]['value'];
                    }
                    else
                    {
                        $ccid = uniqid('ccid-',TRUE);
                    }
                    $form['elements'][$key] =
                        array(
                            'type' => 'hidden',
                            'id' => 'id-' . $key,
                            'class' => 'class-' . $key,
                            'title' => $value,
                            'label' => $value,
                            'name' => 'container['. $value .']',
                            'value' => $ccid,
                            'readonly' => '',
                        );
                    break;
                case 'administration_title':
                    $form['elements'][$key] =
                        array(
                            'type' => 'hidden',
                            'id' => 'id-' . $key,
                            'class' => 'class-' . $key,
                            'title' => $value,
                            'label' => str_replace('_', ' ',$value),
                            'name' => 'container['.$value .']',
                            'value' => $ccid . '-title',
                            'placeholder'=> '',
                            'required' => TRUE,
                        );
                    break;

                case 'content_type_id':

                    $form['elements']['type'] =
                        array(
                            'type' => 'hidden',
                            'label' => 'type',
                            'id'=> $value,
                            'class'=> $value,
                            'name'=> 'container['. $value.']',
                            'form'=> 'content_type_'. $content_type_info['type'] .'_add',
                            'value'=> $content_type_id,

                        );

                    break;
                case 'author_id':
                    $user = (isset($_SESSION['login_user'][session_id()]) ? $_SESSION['login_user'][session_id()] : '');
                    $form['elements'][$key] =
                        array(
                            'type' => 'hidden',
                            'id' => 'id-' . $key,
                            'class' => 'class-' . $key,
                            'title' => $value,
                            'label' => str_replace('_', ' ',$value),
                            'name' => 'container['.$value .']',
                            'value' => $user['user_id'],
                            'placeholder'=> '',
                            'required' => TRUE,
                        );

                case 'date_created':

                    $form['elements']['datetime'] =
                        array(
                            'type' => 'datetime',
                            'id' => 'id-' . $value,
                            'class' => 'class-' .$value,
                            'title' => $value,
                            'label' => 'date created',
                            'name'=> 'container['. $value .']',
                            'form'=> 'content_type_'. $content_type_info['type'] .'_add',
                            'value'=> '',

                        );

                    break;
                case 'data':
                    foreach($value as $data_key => $data_element)
                    {
                        $form['elements']['data-'. $data_key ] =
                            array(
                                'type' => $data_element['element_type'],
                                'id' => 'id-' . $data_element['label'],
                                'class' => 'class-' .$data_element['label'],
                                'title' => $data_element['label'],
                                'label' => $data_element['label'],
                                'name' => 'data['.$data_element['name'] .']',
                                'value' => '',
                                'placeholder'=> '',
                                'required' => $data_element['required']

                            );

                    }

                default:
                    if(!is_array($value))
                    {
                        if(isset($previous['form_elements'][$value]['value']))
                        {
                            $default_value = $previous['form_elements'][$value]['value'];
                        }
                        else
                        {
                            $default_value = '';
                        }
                        $form['elements'][$key] =
                            array(
                                'type' => 'hidden',
                                'id' => 'id-' . $key,
                                'class' => 'class-' . $key,
                                'title' => $value,
                                'label' => str_replace('_', ' ',$value),
                                'name' => 'container['.$value .']',
                                'value' => $value,
                                'placeholder'=> '',
                                'required' => TRUE,
                            );

                    }

                    break;
            }

        }

        $form['elements']['send'] =
            array(
                'type' => 'submit',
                'id'=> 'save',
                'class'=> 'save',
                'title'=> 'save',
                'name'=> 'save',
                'label'=> 'save',
                'value'=> 'save',
                'before'=> '<div></div>',
            );


        // start tail recursion to pickup and process form elements
        $message = $cck->_form_get_message($form['name'], 'error');
        $content['content_right_title'] = 'List';
        $content['content_right'] = '';
        $content['content_left_title'] = 'Add';
        $content['content_left'] = $cck->_form($form,'html_form');
        $output = $cck->_view('page_content_50_50', $content);

        $variables['page_title'] = 'Add blog post';
        $variables['content_title'] = 'blog post';
        $variables['content'] = $message . $output;
        print $cck->_view('default', $variables);

    }
    
    private function blog_post_edit($ccid = NULL)
    {

        global $cck, $settings;

        $args = $cck->_args();

        if(isset($args[1]))
        {

            $ccid = $args[1];
            $container = $cck->_model('content', 'content_get_container', $ccid);
            $data = $cck->_model('content', 'content_get_container_data', $ccid);

            //$output = $cck->_debug($container);
            //$output .= $cck->_debug($data);
            //$output = $cck->_debug(get_declared_classes());
            //exit ($output);
            if($container == FALSE)
            {
                $output = 'post not found';
            }
            else
            {
                $form = new content_form();
                $action = $cck->_url($this->module  . '/post/save');
                $output = $form->content_form_content_edit($container, $data, $action);
            }

        }
        else
        {
            $output = 'post not found';
        }



        $variables['page_title'] = $container['content_type_info']['label']. ' edit';
        $variables['content_title'] = $container['content_type_info']['label']. ' edit';

        // add a js link to template
        $js = $cck->_hooks('hook_js');
        $script = $cck->_add_js($js[$this->module]);
        $variables['javascript'] = $script;

        $variables['content'] = $output;
        print $cck->_view('page_admin', $variables);

    }
    
    private function blog_post_delete()
    {
    	return 'blog post delete';
    }

	private function blog_post_submit()
	{
		global $cck, $settings;
        $output = '';

        $valid = $cck->_form_validate($_POST);
        $added = $cck->_model('content','content_add', $_POST);
        if($valid == TRUE && $added == TRUE)
        {
            header('location:' . $settings['frontpage']);
        }
        else
        {
            $output = 'submission halted check your input';
            //$cck->_message_set('notice', $message , 'success');
            $variables['page_title'] = 'Blog';
            $variables['content_title'] = 'Post added';
            $variables['content'] = $output;
            print $cck->_view('default', $variables);
        }
    }

    private function blog_post_save()
    {
        global $cck, $settings;
        $output = '';

        //$valid = $cck->_form_validate($_POST);
        $added = $cck->_model('content','content_save', $_POST);
        if($added == TRUE)
        {
            header('location:' . $settings['frontpage']);
        }
        else
        {
            $output = $cck->_debug($_POST);
            //$cck->_message_set('notice', $message , 'success');
            $variables['page_title'] = 'Blog';
            $variables['content_title'] = 'Post added';
            $variables['content'] = $output;
            print $cck->_view('default', $variables);
        }
    }

}

?>

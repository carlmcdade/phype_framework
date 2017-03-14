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

namespace content;

use \PDO;
use \PDOException;
use content\content_form;

class content_admin{

	public  $menu;
	public  $page_title = 'Content Administration';
	public  $section;
	public  $module;

    function __construct()
    {
        global $cck;

        //Test the Common settings
        // get the short name without namespace
        $this->section = __CLASS__;
		$this->module = __NAMESPACE__;
        
    }
    
    function __toString()
    {
    	return $this->section;
    }
    
    function hook_links()
    {
    	    $link = 'links';
    	     
    	    $var[$link][1] = array(
    	    	    'text' => 'Content connections',
    	    	    'path' => 'admin/'.$this->module.'/content_type_connection'
    	    	    );
            $var[$link][2] = array(
            	    'text' => 'Content fields', 
            	    'path' => 'admin/'.$this->module.'/content_type_fields'
        		);
            return $var;
    	    
    }

    function hook_admin_links()
    {
        $link = 'links';
        $var = array();

        $var[$link][1] = array(
                'text' => 'Content list',
                'path' => 'admin/'. $this->module . '/content_list'
            );

        $var[$link][2] = array(
        		'text' => 'Content Add',
        		'path' => 'admin/'. $this->module . '/content_add'
        		);

        $var[$link][3] = array(
            'text' => 'Content types',
            'path' => 'admin/'. $this->module . '/content_type_list'
        );

        $var[$link][4] = array(
        		'text' => 'Content add type', 
        		'path' => 'admin/'. $this->module . '/content_type_add'
        		);

        return $var;
    }

        

    /**
    *   Sub navigation is not a hook and displayed per call by section
    */
    
    function hook_sub_links($index = 0)
    {      
        $link = 'links';        
        $var = array();       
        $var[$link][2] = array(
        		'text' => 'Content types',
        		'path' => 'admin/' . $this->module . '/content_type_list'
        );       
        $var[$link][1] = array(
        		'text' => 'Add content type',
        		'path' => 'admin/' . $this->module . '/content_type_add'
        );        
        return $var;      
    }

    function content_type_quick_field_add_confirm()
    {
        global $cck;
        $args = $cck->_args();
        if($cck->_user_access() == FALSE)
        {
            $form = new \users\users_form();
            $show_form = $form->users_login_form();
            $variables['content'] = $show_form ;
            print $cck->_view('page_login', $variables);
            return;
        }
        $form = new content_form();
        $output = $form->content_form_quick_field_add_confirm();
        $variables['content'] = $output;
        print $cck->_view('page_admin', $variables);
    }


    function content_type_quick_field_add_submit()
    {
        global $cck;
        $args = $cck->_args();
        if($cck->_user_access() == FALSE)
        {
            $form = new \users\users_form();
            $show_form = $form->users_login_form();
            $variables['content'] = $show_form ;
            print $cck->_view('page_login', $variables);
            return;
        }

        $new_field = $cck->_model('content','content_type_quick_field_add', $args);

        $variables['content'] = 'adding new field to ' . $cck->_debug($args). $new_field;

        print $cck->_view('page_admin', $variables);
    }

    function content_type_field_add()
    {
        global $cck;
        $args = $cck->_args();
        $output = 'add field to content type';
    	// get all links from each class controller
        $main_menu = $cck->_hooks('hook_links');
        $sub_menu = $this->hook_admin_links();

        if(isset($args[1]))
        {
            $add_field = $cck->_plain_text($args[1]);
        }
        else
        {
            $add_field = '23';
        }


        $local_links = array(

            $var[] = array(
                'text' => 'fields',
                'path' => 'admin/'. $this->module . '/content_type_fields/' . $cck->_plain_text($args[0])
            ),

            $var[] = array(
                'text' => 'field add',
                'path' => 'admin/'. $this->module . '/content_type_field_add/' . $cck->_plain_text($args[0])
            ),

        );

        $connect = $cck->_dbconnect('datasource_default');

        try
        {
            $connect = $cck->_dbconnect('datasource_default');
            $result = $connect->prepare("SELECT type_id, label, type, description FROM content_types WHERE type_id='". $cck->_plain_text($args[0]) ."'");
            $result->execute();
            $data = $result->fetch(PDO::FETCH_ASSOC);
        }
        catch (Exception $e)
        {
            echo 'Data retrieval error: ',  $e->getMessage(), "\n";
        }

        $left = '';
        $form = new content_form();
        $right = $form->content_form_field_types();

        if(isset($add_field))
        {
            try
            {
                $field_result = $connect->prepare("SELECT * FROM content_types_field_defaults WHERE field_type_id='". $add_field ."'");
                $field_result->execute();
                $field = $field_result->fetch(PDO::FETCH_ASSOC);

                $field['content_type_id'] = $data['type_id'];
                $left = $form->content_form_field_form_builder($field, $data['type_id'], $this->section.'/content_type_field_add_submit');//$cck->_debug($field);
            }
            catch (Exception $e)
            {
                echo 'Data retrieval error: ',  $e->getMessage(), "\n";
            }

        }


        $content['content_left_title'] = $data['label'] . ' type' ;
        $content['content_left'] = $left;



        $content['content_right_title'] = 'Add field';
        $content['content_right'] = $right;

        // content output
        $output = $cck->_view('page_content_50_50', $content);

        $variables['page_title'] = $this->page_title;
    	$variables['content_title'] = 'Content Type ' . ARROW_RIGHT . ' ' . $data['label']  . ' ' .  ARROW_RIGHT . ' field add';
    	
    	$variables['navigation'] = $cck->_menu_links($main_menu, 'links_main_menu');
    	$variables['sub_navigation'] = $cck->_module_links($sub_menu, array(
            'template'=>'links_sub_menu',
            'index' => $this->module
        ), $local_links);

        //$form->content_form_add_type_field();
        $variables['content'] =  $output;

    	
    	print $cck->_view('page_admin', $variables);
    }

    function content_type_field_add_submit()
    {
        global $cck;
        $output = $cck->_debug($_POST);
        $output .= $cck->_debug('sql statement parts');
        $output .= $cck->_debug('sql statement');
        $variables['page_title'] = $this->page_title;
        $variables['content_title'] = 'submit';
        $new_field = $cck->_model('content','content_type_field_add', $_POST);
        $variables['content'] = $output . $new_field;
        print $cck->_view('page_admin', $variables);
    }


    function content_list()
    {
        global $cck, $settings;
        $args = $cck->_args();

        // get all links from each class controller
        $main_menu = $cck->_hooks('hook_links');
        $sub_menu = $this->hook_admin_links();

        $variables['navigation'] = $cck->_menu_links($main_menu, 'links_main_menu');
        $variables['sub_navigation'] = $cck->_module_links($sub_menu,
            array(
                'template'=>'links_sub_menu',
                'index' => $this->module
            )
        );


        $connect = $cck->_dbconnect('datasource_default');

        if(isset($args[0]))
        {
            $content_type_id = $cck->_plain_text($args[0]);
            $content_type_info = $cck->_model('content','content_type_get',$content_type_id);
            $result = $connect->prepare("SELECT ccid, administration_title, ct.type, author_id, date_created FROM content_containers AS cc JOIN content_types AS ct ON cc.content_type_id = ct.type_id WHERE ct.type_id='". $content_type_id."'");
        }
        else
        {
            $result = $connect->prepare("SELECT ccid, administration_title, ct.type, author_id, date_created FROM content_containers AS cc JOIN content_types AS ct ON cc.content_type_id = ct.type_id");
            $type = 'All';
        }
        // Get the content column values


        // table header from database

        // table rows and field values


        $result->execute();

        $table_rows = $result->fetchAll();

        // validate content

        if(!empty($table_rows))
        {
            $columns = array();
            $user_columns = array('delete', 'edit','view');

            // table header
            foreach ($table_rows[0] as $key => $value)
            {
                if(!is_numeric($key))
                {
                    $columns[] = str_replace('_',' ', $key);
                }



            }



            foreach($user_columns as $extra)
            {
                array_push($columns, $extra);
            }

            // table rows

            foreach($table_rows as $key => $value)
            {
                $admin_links = array(
                    'delete'=> 'admin/'. $this->module . '/' . 'content_delete' . '/' . $value['ccid'],
                    'edit'=> 'admin/'. $this->module . '/' . 'content_edit' . '/' . $value['ccid'],
                    'view'=> 'admin/'. $this->module . '/' . 'content_view' . '/' . $value['ccid']
                );

                foreach($admin_links as $text => $path)
                {
                    $links['text'] = $text;
                    $links['path'] = $path;


                    array_push($table_rows[$key], $cck->_view('links',$links));
                }

                //echo $cck->_debug($value);
                unset($table_rows[$key][0],$table_rows[$key]['ccid']);
                $table_rows[$key][4] = $cck->_format_datetime($table_rows[$key][4]);
                $table_rows[$key]['date_created'] =  $cck->_format_datetime($table_rows[$key]['date_created']);
            }

            unset($columns[0]);
            // set table variables for view table template
            $table['header'] = $columns;
            $table['rows'] = $table_rows;
            $output = $cck->_view('css_table', $table);
        }
        else
        {
            $output = ' Query incomplete or nothing found!';
        }


        $variables['page_title'] = $this->page_title;
        $variables['content_title'] = (isset($content_type_info['label'])? $content_type_info['label'] : 'all') . ' content';
        $variables['content'] = $output;
        print $cck->_view('page_admin', $variables);

    }

    function content_add($content_type = NULL)
    {
        global $cck, $settings;

        $args = $cck->_args();
        if(isset($args[0]))
        {
            $content_type = $args[0];
        }
        elseif(!isset($args[0]) && !$content_type)
        {
            $content_type = '1';
        }


        // this page requires arguments so return nothing if not found;


        // get all links from each class controller
        $main_menu = $cck->_hooks('hook_links');
        $sub_menu = $this->hook_admin_links();
        $content_title = 'Content Add';


        $variables['navigation'] = $cck->_menu_links($main_menu, 'links_main_menu');
        $variables['sub_navigation'] = $cck->_module_links($sub_menu,
            array(
                'template'=>'links_sub_menu',
                'index' => $this->module
            )
        );

        $connect = $cck->_dbconnect('datasource_default');

        // list values
        $get_types = $connect->prepare("SELECT type_id, type, label, description FROM content_types");

        $get_types->execute();

        $content_types = $get_types->fetchAll();

        // build list of links to content types if arguments not found
        if(!empty($content_types))
        {
            $type_links='';
            foreach($content_types as $atype)
            {
                $link['text']= $atype['label'];
                $link['path']= $cck->_url('admin/content/content_add/' . $atype['type_id']);
                $link['description'] = $atype['description'];

                $linked['types'][] = $link;

                if($content_type ==  $atype['type_id'])
                {
                    $content_type_inuse['id'] = $atype['type_id'];
                    $content_type_inuse['label'] = $atype['label'];
                }

            }
            $type_links = $cck->_view('links_content_types', $linked);
        }
        //print $cck->_debug($content_types);
        // container data

        $field_result = $connect->prepare("SELECT ctf.field_id,ctf.field_type_id, ctf.label,ctf.multiple, ctf.name, ctf.required, ments.type as element_type FROM content_types_fields AS ctf JOIN content_types_fields_types AS ments ON ctf.field_type_id = ments.field_type_id WHERE ctf.content_type_id='". $content_type ."'");
        $field_result->execute();
        $data_fields = $field_result->fetchALL(PDO::FETCH_ASSOC);

        if(empty($data_fields))
        {
            $admin_link['text'] = 'create a field';
            $admin_link['path'] = 'admin/content/content_type_field_add/'. $content_type_inuse['id'];
            $elements['data']['no_fields'] =
                array(
                'field_id' => NULL,
                'field_type_id' => '11',
                'label' => 'NO FIELDS',
                'name' => 'no_fields',
                'required' => '',
                'element_type' => 'html',
                'value' => 'No content fields for this type have been created. You may create a container for later  use or '. $cck->_link('links',$admin_link),
                );
        }
        else
        {
            foreach ($data_fields as $datakey => $datavalue)
            {
                $elements['data'][$datavalue['field_id']] = $datavalue;

            }

        }


        // container
        $output = 'Type does not exist in list of types. retrieving list' ;
        $table_name = 'content_containers';
        $container_result = $connect->query("PRAGMA table_info(" . $table_name . ")");
        $container_result->setFetchMode(PDO::FETCH_ASSOC);


        foreach ($container_result as $conkey => $convalue)
        {

            $elements[$convalue['name']] = $convalue['name'];

        }

        // add data section

            $form = array();
            $form['name'] = 'add_'. $content_type_inuse['label'].'_content';
            $form['id'] = 'add_' . $content_type_inuse['label'].'_content';
            $form['method'] = 'POST';
            $form['action'] = $cck->_url($this->section .'/content_add_submit/'. $content_type_inuse['id']);
            $form['title'] = 'add content for this type';
            $form['enctype'] = 'multipart/form-data';

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
                                'type' => 'text',
                                'id' => 'id-' . $key,
                                'class' => 'class-' . $key,
                                'title' => $value,
                                'label' => $value,
                                'name' => 'container['. $value .']',
                                'value' => $ccid,
                                'readonly' => '',
                                'before' => '<div class="meta-group"><h4>Meta</h4>'

                            );

                        break;

                    case 'content_type_id':


                        $form['elements']['content_type_id'] =
                            array(
                                'type' => 'hidden',
                                'label' => 'type',
                                'id'=> 'mytype',
                                'class'=> 'mytype',
                                'name'=> 'container[content_type_id]',
                                'form'=> $form['name'],
                                'value'=> $content_type_inuse['id'],

                            );
                        $form['elements']['content_type_label'] =
                            array(
                                'type' => 'text',
                                'label' => 'type',
                                'id'=> 'mytype',
                                'class'=> 'mytype',
                                'name'=> 'container[content_type_label]',
                                'form'=> $form['name'],
                                'value'=> $content_type_inuse['label'],
                                'readonly' => true

                            );
                        break;
                    case 'administration_title':
                        $form['elements'][$key] =
                            array(
                                'type' => 'text',
                                'id' => 'id-' . $key,
                                'class' => 'class-' . $key,
                                'title' => $value,
                                'label' => str_replace('_', ' ',$value),
                                'name' => 'container['.$value .']',
                                'value' => $ccid . '-title',
                                'placeholder'=> $ccid . '-title',

                            );
                        break;
                    case 'author_id':
                        $form['elements'][$key] =
                            array(
                                'type' => 'text',
                                'id' => 'id-' . $key,
                                'class' => 'class-' . $key,
                                'title' => $value,
                                'label' => str_replace('_', ' ',$value),
                                'name' => 'container['.$value .']',
                                'value' => $settings['owner']['id']['value'],
                                'placeholder'=> $settings['owner']['id']['value'],

                            );
                        break;
                    case 'date_created':
                        $form['elements'][$key] =
                            array(
                                'type' => 'text',
                                'id' => 'id-' . $key,
                                'class' => 'class-' . $key,
                                'title' => $value,
                                'label' => str_replace('_', ' ',$value),
                                'name' => 'container['.$value .']',
                                'value' => $cck->_format_datetime(time()),
                                'placeholder'=> $cck->_format_datetime(time()),

                            );
                        break;
                    case 'data':
//exit($cck->_debug($value));
                        if(!empty($value))
                        {
                            // get data field count
                            $data_field_count = count($value);
                            $count_down = $data_field_count;
                            foreach($value as $data_key => $data_element)
                            {
                                switch($data_element['element_type'])
                                {

                                    case 'file':

                                        $form['elements']['data-'. $data_key ] =
                                            array(
                                                'type' => $data_element['element_type'],
                                                'id' => 'id-' . $data_element['label'],
                                                'class' => 'class-' .$data_element['label'],
                                                'title' => $data_element['label'],
                                                'name' => $data_element['name'],
                                                'label' => $data_element['label'],
                                                'multiple' => $data_element['multiple'],
                                                'value' => (isset($field_data[$data_key]) ? $field_data[$data_key] : '' ),
                                                'placeholder'=> '',

                                            );
                                        break;
                                    default:
                                        $form['elements']['data-'. $data_key ] =
                                            array(
                                                'type' => $data_element['element_type'],
                                                'id' => 'id-' . $data_element['label'],
                                                'class' => 'class-' .$data_element['label'],
                                                'title' => $data_element['label'],
                                                'label' => $data_element['label'],
                                                'name' => 'data['.$data_element['name'] .']',
                                                'value' => (isset($field_data[$data_key]) ? $field_data[$data_key] : $data_element['value']),
                                                'placeholder'=> '',
                                                'required' => $data_element['required'],

                                            );
                                        break;
                                }

                                // start grouping of data fields with count
                                if($data_field_count == $count_down)
                                {
                                    $form['elements']['data-'. $data_key ]['before'] = '<div class="data-group"><h4>Content</h4>';
                                }

                                $count_down--;

                                // end grouping of data fields with count
                                if($count_down === 0)
                                {
                                    $form['elements']['data-'. $data_key ]['after'] = '</div>';
                                }

                            }
                        }


                        break;
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
                                    'type' => 'text',
                                    'id' => 'id-' . $key,
                                    'class' => 'class-' . $key,
                                    'title' => $value,
                                    'label' => str_replace('_', ' ',$value),
                                    'name' => 'container['.$value .']',
                                    'value' => $default_value,
                                    'placeholder'=> '',

                                );

                        }


                        break;


                }



            }
             //echo $key . $count_all;
             // last element closer
            $form['elements'][$key]['after'] = '</div>';
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
        $content['content_right'] = $type_links;
        $content['content_left_title'] = 'Add ' . $content_type_inuse['label'];

        $content['content_left'] = $cck->_form($form,'html_form');
        $output = $cck->_view('page_content_50_50', $content);

        $variables['page_title'] = $this->page_title;
        $variables['content_title'] = $content_title;
        $variables['content'] = $message . $output ;//. $cck->_debug($elements) .$cck->_debug($_SESSION);
        print $cck->_view('page_admin', $variables);

    }


    function content_add_submit()
    {
        global $cck;
        $added = '';

        if($cck->_user_access() == FALSE)
        {
            $form = new \users\users_form();
            $show_form = $form->users_login_form();
            $variables['content'] = $show_form ;
            print $cck->_view('page_login', $variables);
            return;
        }




        // if the validation fails th user will be sent back to the form page (referer)
        $valid = $cck->_form_validate($_POST);

        if($valid)
        {
            $added = $cck->_model('content','content_add', $_POST);
            if($_FILES && $added == TRUE)
            {
                $data['files'] = $_FILES;
                $data['container'] = $_POST['container'];
                $upload = $cck->_model('content','content_add_files', $data);
            }

        }


        $output = $cck->_debug($added);
        $output .= $cck->_debug($upload);
        //$output .= $cck->_debug($added);

        $variables['page_title'] = $this->page_title;
        $variables['content_title'] = 'submit';
        $variables['content'] = $output;
        print $cck->_view('page_progress_indicator', $variables);
    }

    function content_delete()
    {
        global $cck;
        $args = $cck->_args();

        $output = 'remove (container and filed data) or (only field data  leaving an empty container)';

        if(isset($args[0]))
        {

            $ccid = $args[0];
            $container = $cck->_model('content', 'content_get_container', $ccid);
            $data = $cck->_model('content', 'content_get_container_data', $ccid);

            //$output = $cck->_debug($container);
            //$output .= $cck->_debug($data);
            //$output .= $cck->_debug($form);
            //exit ($output);
            if($container == FALSE)
            {
                $output .= 'post not found';
            }
            else
            {
                $form = new content_form();
                $output .= $form->content_form_content_delete($container, $data);
            }

        }
        else
        {
            $output .= 'id not found';
        }


        $variables['page_title'] = $this->page_title;
        $variables['content_title'] = 'delete';
        $variables['content'] = $output;
        print $cck->_view('page_admin', $variables);

    }

    function content_delete_submit()
    {

        global $cck;

        if($cck->_user_access() == FALSE)
        {
            $form = new \users\users_form();
            $show_form = $form->users_login_form();
            $variables['content'] = $show_form ;
            print $cck->_view('page_login', $variables);
            return;
        }

        if(!isset($_POST['delete']))
        {

            $posted = (isset($_POST['posted']) ? json_decode($_POST['posted'],true): '');
            $operation = $posted['delete'];
            //echo $cck->_debug($posted);
        }
        else
        {
            $operation = $_POST['delete'];
        }


        $args = $cck->_args();

        if(isset($args[0]))
        {

            $ccid = $args[0];
        }


        switch($operation)
        {
            case 'delete data':

                if(isset($_POST['verify']) && $_POST['verify'] == 'confirm')
                {

                    $data = $cck->_model('content', 'content_delete_container_data', $posted['container']['ccid']);
                    $output = 'Confirmed process data deleted : '. $posted['container']['ccid'];
                }
                else
                {
                    $message = "Removing the data leaving the empty container.";
                    $form = new content_form();
                    $output = $form->content_form_confirm($_POST, $message);
                }
                break;
            case 'delete container':
                //$output = $cck->_debug($_POST['container']['ccid']);
                //$output .= $cck->_debug($_POST['delete']);
                if(isset($_POST['verify']) && $_POST['verify'] == 'confirm')
                {

                    $container = $cck->_model('content', 'content_delete_container', $posted['container']['ccid']);
                    $output = 'Confirmed process container deleted : '. $posted['container']['ccid'];
                }
                else
                {
                    $message = 'Deleting only the container will create orphaned data in the database.';
                    $form = new content_form();
                    $output = $form->content_form_confirm($_POST, $message);

                }



                //$data = $cck->_model('content', 'content_get_container_data', $ccid);
                break;
            case 'delete all':
                if(isset($_POST['verify']) && $_POST['verify'] == 'confirm')
                {

                    $data = $cck->_model('content', 'content_delete_container_data', $posted['container']['ccid']);
                    $container = $cck->_model('content', 'content_delete_container', $posted['container']['ccid']);
                    $output = 'Confirmed process container and all data deleted : '. $posted['container']['ccid'];
                }
                else
                {
                    $message = "Permanently deleting the container and all data in the database.";
                    $form = new content_form();
                    $output = $form->content_form_confirm($_POST, $message);

                }


                break;
        }

        $variables['page_title'] = $this->page_title;
        $variables['content_title'] = 'delete submit';

        $variables['content'] = $output ;
        print $cck->_view('page_admin', $variables);

    }

    function content_edit()
    {
        global $cck, $settings;

        $args = $cck->_args();

        /*if(isset($args[0]))
        {

            $ccid = $args[0];
        }
*/

        if(isset($args[0]))
        {

            $ccid = $args[0];
            $container = $cck->_model('content', 'content_get_container', $ccid);
            $data = $cck->_model('content', 'content_get_container_data', $ccid);

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
                $form = new content_form();
                $output = $form->content_form_content_edit($container, $data);
            }

        }
        else
        {
            $output = 'post not found';
        }

        $variables['page_title'] = 'content edit';
        $variables['content_title'] = $container['content_type_info']['label'];

        // add a js link to template
        $js = $cck->_hooks('hook_js');
        $script = $cck->_add_js($js[$this->module]);
        $variables['javascript'] = $script;

        $variables['content'] = $output;
        print $cck->_view('page_admin', $variables);
    }

    function content_edit_submit()
    {
        global $cck, $settings;
        $update ='';
        $added ='';



        if($cck->_user_access() == FALSE)
        {
            $form = new \users\users_form();
            $show_form = $form->users_login_form();
            $variables['content'] = $show_form ;
            print $cck->_view('page_login', $variables);
            return;
        }

        $valid = $cck->_form_validate($_POST);
        $added = 'could not post';
        if($valid)
        {
            $added = $cck->_model('content','content_save', $_POST);
            //if($added == TRUE)
            //{
                $data['files'] = $_FILES;
                $data['post'] = $_POST;
                if(!empty($data['files']))
                {
                    $update = $cck->_model('content','content_update_files', $data);
                }

            //}
        }


        //$output = $cck->_debug($_POST);
        $variables['page_title'] = $this->page_title;
        $variables['content_title'] = 'submit';
        $variables['content'] = 'process completing';//$added . $update;

        header("Location:". $cck->_url($settings['site']['frontpage']['value']));

    }

    function content_view()
    {
        global $cck, $settings;
        $args = $cck->_args();



        $output = '';

        // get the  content type

        // get the fields for the content type


        // load all into array and

        if(isset($args[0]))
        {

            $ccid = $args[0];
            $container = $cck->_model('content', 'content_get_container', $ccid);
            $data = $cck->_model('content', 'content_get_container_data', $ccid);
            $content_type_info = $cck->_model('content', 'content_type_get', $container['content_type_id']);

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

        $variables['page_title'] = $this->page_title;
        $variables['content_title'] = 'view';
        $variables['content_type'] = $content_type_info['type'];

        $css = $cck->_hooks('hook_css');
        $variables['stylesheets'] = '<!--'.$cck->_debug($css).'-->';
        print $cck->_view('page', $variables);
    }

    function content_type_fields($type_info = NULL)
    {
        global $cck, $settings;
        $args = $cck->_args();

        // get all links from each class controller
        $main_menu = $cck->_hooks('hook_links');
        $sub_menu = $this->hook_admin_links();

        $local_links = array(

            $var[] = array(
                'text' => 'fields',
                'path' => 'admin/'. $this->module . '/content_type_fields/'. $args[0]
            ),

            $var[] = array(
                'text' => 'field add',
                'path' => 'admin/'. $this->module . '/content_type_field_add/'. $args[0]
            ),

        );

        $variables['navigation'] = $cck->_menu_links($main_menu, 'links_main_menu');
        $variables['sub_navigation'] = $cck->_module_links($sub_menu,
            array(
                'template'=>'links_sub_menu',
                'index' => $this->module
            ), $local_links);


        $connect = $cck->_dbconnect('datasource_default');

        // table header from database

        // content type values
        $result = $connect->prepare("SELECT type_id, type, label, description FROM content_types WHERE type_id='".$args[0]."' LIMIT 1");

        $result->execute();

        $row = $result->fetch(PDO::FETCH_ASSOC);

        $output = 'View the content type fields in a form for [ '.  $row['label'] . ' ] type.';

        // content  type fields
        $field_result = $connect->prepare("SELECT field_id, label, name FROM content_types_fields WHERE content_type_id='". $row['type_id']."'");
        $field_result->execute();

        $table_all = $field_result->fetchALL();


        if(!empty($table_all))
        {
            $columns = array();
            $user_columns = array('edit', 'delete');

            // table header take just the first resutl row at key=0
            foreach ($table_all[0] as $key => $value)
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

            // table rows
            foreach($table_all as $key => $value)
            {
                    $admin_links = array(
                        'edit' => 'admin' . DIRECTORY_SEPARATOR . $this->module . DIRECTORY_SEPARATOR . 'content_type_field_edit' . DIRECTORY_SEPARATOR . $row['type_id'] . DIRECTORY_SEPARATOR . $value['field_id'],
                        'delete' => 'admin' . DIRECTORY_SEPARATOR . $this->module . DIRECTORY_SEPARATOR . 'content_type_field_delete' . DIRECTORY_SEPARATOR .  $row['type_id'] . DIRECTORY_SEPARATOR . $value['field_id'],
                    );

                foreach($admin_links as $text => $path)
                {
                    $links['text'] = $text;
                    $links['path'] = $path;

                    array_push($table_all[$key], $cck->_view('links',$links));
                }
            }

            // set table variables for view table template
            $table['header'] = $columns;
            $table['rows'] = $table_all;
            // override the default table classes
            //$table['classes'] = 'none';

            //inner content $variables
            $content['content_left_title'] = 'List';
            $content['content_left'] = $cck->_view('css_table', $table);

        }
        else
        {
            $content['content_left_title'] = 'Content fields';
            $admin_link['text'] = 'create a field';
            $admin_link['path'] = 'admin/content/content_type_field_add/'. $args[0];
            $content['content_left'] = '<div class="data-group">' . 'No content fields for this type have been created. You may use the quick field add or '. $cck->_link('links',$admin_link) . '</div>';

        }

        $form = new content_form();
        $content['content_right_title'] = 'Quick field add';
        $content['content_right'] = $form->content_form_field_types(true);

        // content output
        $output = $cck->_view('page_content_50_50', $content);

        $variables['page_title'] = $this->page_title;
        $variables['content_title'] = 'Content type ' . ARROW_RIGHT . ' ' . $row['label'] .' ' . ARROW_RIGHT . ' fields';
        $variables['preprocessed'] = $output;
        print $cck->_view('page_admin', $variables);

	}

    function content_type_field_edit()
    {
        global $cck;

        // get uri arguments
        $args = $cck->_args();
        //$output = $cck->_debug($_SESSION);
        //$output .= $cck->_debug($_POST);

        // get data from source
        $connect = $cck->_dbconnect('datasource_default');

        // content type values
        $form = new content_form();

        $result = $connect->prepare("SELECT ctf.*, ct.label as content_type, ct.type_id AS content_type_id FROM content_types_fields AS ctf JOIN content_types AS ct ON ctf.content_type_id=ct.type_id WHERE ctf.field_id='".$args[1]."' LIMIT 1");
        $result->execute();
        $data = $result->fetch(PDO::FETCH_ASSOC);


        if(isset($args[1]))
        {
            try
            {
                // content type field settings and values
                $field_result = $connect->prepare("SELECT * FROM content_types_fields WHERE field_id='". $args[1] ."'");
                $field_result->execute();
                $content_type_field = $field_result->fetch(PDO::FETCH_ASSOC);

                // empty form by field type
                $field_defaults = $connect->prepare("SELECT * FROM content_types_field_defaults WHERE field_type_id='". $content_type_field['field_type_id'] ."'");
                $field_defaults->execute();
                $field_form = $field_defaults->fetch(PDO::FETCH_ASSOC);

                $field_form['field_id'] = $content_type_field['field_id'];
                $field_form['content_type_id'] = $content_type_field['content_type_id'];
                $field_form['existing_field_name'] = $content_type_field['name'];

                $left = $form->content_form_field_editor($field_form, $content_type_field);//$cck->_debug($field);
            }
            catch (Exception $e)
            {
                echo 'Data retrieval error: ',  $e->getMessage(), "\n";
            }

        }

        //get form and send data to form

        $content['content_left_title'] = $data['content_type']. ' field edit';
        $content['content_left'] = $left;

        // list fields content output
        // content  type fields
        $field_list = $connect->prepare("SELECT ct.field_id, ct.label, ft.type AS type, ct.name FROM content_types_fields  AS ct JOIN content_types_fields_types AS ft ON  ft.field_type_id = ct.field_type_id WHERE ct.content_type_id='". $data['content_type_id']."'");
        $field_list->execute();

        $table_all = $field_list->fetchALL();

        if(!empty($table_all))
        {
            $columns = array();
            $user_columns = array('edit', 'delete');
            $content_field_types = $cck->_model('content','content_get_field_types');

            // table header take just the first resutl row at key=0
            foreach ($table_all[0] as $key => $value)
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

            // table rows
            foreach($table_all as $key => $value)
            {

                $admin_links = array(
                    'edit' => 'admin'. '/' . $this->module . '/' . 'content_type_field_edit' . '/' . $data['content_type_id'] . '/' . $value['field_id'],
                    'delete' => 'admin'. '/' . $this->module . '/'  .'content_type_field_delete' . '/' .$data['content_type_id'].'/' . $value['field_id'],
                );


                foreach($admin_links as $text => $path)
                {
                    $links['text'] = $text;
                    $links['path'] = $path;

                    array_push($table_all[$key], $cck->_view('links',$links));
                }
            }


            // set table variables for view table template
            $table['header'] = $columns;
            $table['rows'] = $table_all;

            // override the default table classes
            //$table['classes'] = 'none';

            //inner content $variables
            $content['content_right_title'] = 'field list';
            $content['content_right'] = $cck->_view('css_table', $table);

        }
        else
        {
            $content['content_right_title'] = 'List';
            $content['content_right'] = 'No fields found for this type!';

        }

        $output = $cck->_view('page_content_50_50', $content);

        // get all links from each class controller
        $main_menu = $cck->_hooks('hook_links');
        $sub_menu = $this->hook_admin_links();

        $local_links = array(

            $var[] = array(
                'text' => 'fields',
                'path' => 'admin/'. $this->module . '/content_type_fields/' . $data['content_type_id']
            ),

            $var[] = array(
                'text' => 'field add',
                'path' => 'admin/'. $this->module . '/content_type_field_add/' . $data['content_type_id']
            ),

        );

        $variables['page_title'] = $this->page_title;
        $variables['content_title'] = 'Content type '. ARROW_RIGHT . ' '. $data['content_type'] .' '. ARROW_RIGHT . ' field ' . ARROW_RIGHT . ' edit' ;

        $variables['navigation'] = $cck->_menu_links($main_menu, 'links_main_menu');
        $variables['sub_navigation'] = $cck->_module_links($sub_menu, array(
            'template'=>'links_sub_menu',
            'index' => $this->module
        ), $local_links);

        $variables['content'] = $output;
        //echo $cck->_debug($content_field_types);

        print $cck->_view('page_admin', $variables);
    }

    function content_type_field_edit_submit()
    {
        global $cck;
        $output = $cck->_debug($_POST);
        $output = $cck->_model('content','content_type_field_save', $_POST);
        $variables['page_title'] = $this->page_title;
        $variables['content_title'] = 'submit';
        $variables['content'] = $output;
        print $cck->_view('page_admin', $variables);
    }

    function content_type_field_delete()
    {
        global $cck;
        $args = $cck->_args();

        // get the content type for the field

        $content['content_left_title'] = 'View content type';
        $content['content_left'] = $this->content_type_viewer();


        $form = new content_form();
        $output = $form->content_form_field_delete($args);

        $content['content_right_title'] = 'Deletion type';
        $content['content_right'] = $output;

        $output = $cck->_view('page_content_50_50', $content);

        $variables['page_title'] = $this->page_title;
        $variables['content_title'] = 'delete field ';
        $variables['preprocessed'] = $output;
        print $cck->_view('page_admin', $variables);

    }

    function content_type_field_delete_submit()
    {
        global $cck;
        $args = $cck->_args();

        if($cck->_user_access() == FALSE)
        {
            $variables['content'] = 'login please';
            print $cck->_view('page_login', $variables);
            return;
        }

        switch($_POST['delete'])
        {
            case 'only field':
                $operation_1 =$cck->_model('content','content_type_field_delete',$args);
                $output = 'deleted field';
                break;
            case 'field and data':
                $operation_1 = $cck->_model('content','content_type_field_delete',$args);
                $operation_2 = $cck->_model('content','content_type_field_data_delete',$args);
                $output = 'deleted field and associated data';
                break;
            default:
                $output = 'deletion  failed.';
        }

        $content['content_left_title'] = 'View content type';
        $content['content_left'] = $this->content_type_viewer();





        $content['content_right_title'] = 'Confirmed Delete';
        $content['content_right'] = $output;

        $output = $cck->_view('page_content_50_50', $content);

        $variables['page_title'] = $this->page_title;
        $variables['content_title'] = 'delete field ';
        $variables['preprocessed'] = $output;
        print $cck->_view('page_admin', $variables);

    }


    
    function content_type_template_viewer()
    {
        global $cck, $settings;
        $args = $cck->_args();

        if(isset($args[0]))
        {
            $content_type = $args[0];
        }
        elseif(!isset($args[0]))
        {
            $content_type = '1';
        }


        // this page requires arguments so return nothing if not found;


        // get all links from each class controller
        $main_menu = $cck->_hooks('hook_links');
        $sub_menu = $this->hook_admin_links();




        $variables['navigation'] = $cck->_menu_links($main_menu, 'links_main_menu');
        $variables['sub_navigation'] = $cck->_module_links($sub_menu,
            array(
                'template'=>'links_sub_menu',
                'index' => $this->module
            )
        );

        $content_type_info = $cck->_model('content', 'content_type_get', $content_type);

        $connect = $cck->_dbconnect('datasource_default');

        $field_result = $connect->prepare("SELECT ctf.field_id,ctf.field_type_id, ctf.label, ctf.name, ctf.required, ments.type as element_type FROM content_types_fields AS ctf JOIN content_types_fields_types AS ments ON ctf.field_type_id = ments.field_type_id WHERE ctf.content_type_id='". $content_type ."'");
        $field_result->execute();
        $data_fields = $field_result->fetchALL(PDO::FETCH_ASSOC);

        if(empty($data_fields))
        {
            $admin_link['text'] = 'create a field';
            $admin_link['path'] = 'admin/content/content_type_field_add/'. $content_type;

            $output = 'No content fields for this type have been created. '. $cck->_link('links',$admin_link);

        }
        elseif($data_fields)
        {


            $output = 'Template name: page_'. $content_type_info['type'] . ".tpl.php<br />\n";

            $output .= 'Template variables:'. "<br />\n";

            foreach ($data_fields as $datakey => $datavalue)
            {
                $output .= '$' . $datavalue['name'] . "<br />\n";
            }

            $output .= $cck->_debug($data_fields);

        }

        else
        {
            $output = 'post not found';
        }

        //$template['variables'] = '';
        //$show = $cck->_view('page_template_view', $template);

        $variables['page_title'] = $this->page_title;
        $variables['content_title'] = ' template view';
        $variables['content'] = $output;
        print $cck->_view('page_admin', $variables);
    }
    
    /**
    *   Content types list available
    */
    
    function content_type_list($dir = NULL, $exclude = array())
    {
    	global $cck, $settings;
    	
    	// get all links from each class controller
        $main_menu = $cck->_hooks('hook_links');
    	$sub_menu = $this->hook_admin_links();

    	$variables['navigation'] = $cck->_menu_links($main_menu, 'links_main_menu');
    	$variables['sub_navigation'] = $cck->_module_links($sub_menu,
			array(
				'template'=>'links_sub_menu',
				'index' => $this->module
				)
			); 
    	
    	$variables['page_title'] = $this->page_title;
    	$variables['content_title'] = 'Content types';	
    	
    	// Get the content column values
    	$connect = $cck->_dbconnect('datasource_default');
    	    
    	// table header from database
		
    	// table rows and field values
		$result = $connect->prepare("SELECT type_id, type, description FROM content_types");
			
		$result->execute();
			
		$table_rows = $result->fetchAll();
			
		// validate content
			
		if(!empty($table_rows))
	    	{
	    		$columns = array();
	    		$user_columns = array('manage', 'edit','template', 'create','list');
	    		
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
	    		
	    		// table rows

				foreach($table_rows as $key => $value)
				{
                    $admin_links = array(
                        'fields'=> 'admin/'. $this->module . DIRECTORY_SEPARATOR . 'content_type_fields' . DIRECTORY_SEPARATOR . $value['type_id'],
                        'settings'=> 'admin/'. $this->module . DIRECTORY_SEPARATOR . 'content_type_edit' . DIRECTORY_SEPARATOR . $value['type_id'],
                        'view'=> 'admin/'. $this->module . DIRECTORY_SEPARATOR . 'content_type_template_viewer' . DIRECTORY_SEPARATOR . $value['type_id'],
                        'post'=> 'admin/'. $this->module . DIRECTORY_SEPARATOR . 'content_add' . DIRECTORY_SEPARATOR . $value['type_id'],
                        'all'=> 'admin/'. $this->module . DIRECTORY_SEPARATOR . 'content_list' . DIRECTORY_SEPARATOR . $value['type_id']
                    );

                    foreach($admin_links as $text => $path)
					{					
						$links['text'] = $text;
						$links['path'] = $path;


						array_push($table_rows[$key], $cck->_view('links',$links));
					}					
				}
	    		    		
	    		// set table variables for view table template
				$table['header'] = $columns; 			
				$table['rows'] = $table_rows;	
				$output = $cck->_view('css_table', $table);
	    	}
	    	else
	    	{
		    	$output = 'Query incomplete or nothing found!';
	    	}
        $variables['content'] = $output;
        print $cck->_view('page_admin', $variables);
	 	 

    }

    function content_type_viewer($content_type = NULL)
    {
        global $cck, $settings;

        $args = $cck->_args();
        if(isset($args[0]))
        {
            $content_type = $args[0];
        }
        elseif(!isset($args[0]) && !$content_type)
        {
            $content_type = '1';
        }


        // this page requires arguments so return nothing if not found;


        // get all links from each class controller
        $main_menu = $cck->_hooks('hook_links');
        $sub_menu = $this->hook_admin_links();
        $content_title = 'Content Add';


        $variables['navigation'] = $cck->_menu_links($main_menu, 'links_main_menu');
        $variables['sub_navigation'] = $cck->_module_links($sub_menu,
            array(
                'template'=>'links_sub_menu',
                'index' => $this->module
            )
        );

        $connect = $cck->_dbconnect('datasource_default');

        $field_result = $connect->prepare("SELECT ctf.field_id,ctf.field_type_id, ctf.label, ctf.name, ctf.required, ments.type as element_type FROM content_types_fields AS ctf JOIN content_types_fields_types AS ments ON ctf.field_type_id = ments.field_type_id WHERE ctf.content_type_id='". $content_type ."'");
        $field_result->execute();
        $data_fields = $field_result->fetchALL(PDO::FETCH_ASSOC);

        if(empty($data_fields))
        {
            $admin_link['text'] = 'create a field';
            $admin_link['path'] = 'admin/content/content_type_field_add/'. $content_type;
            $elements['data'] = array(
                array(
                    'field_id' => NULL,
                    'field_type_id' => '11',
                    'label' => 'NO FIELDS',
                    'name' => 'no_fields',
                    'required' => '',
                    'element_type' => 'html',
                    'value' => 'No content fields for this type have been created. You may create a container for later  use or '. $cck->_link('links',$admin_link),
                ));
        }
        else
        {
            foreach ($data_fields as $datakey => $datavalue)
            {
                $elements['data'][$datavalue['field_id']] = $datavalue;

            }

        }

        /*
         * Array
            (
                'field_id' => NULL
                'field_type_id' => 11
                'label' => 'NO FIELDS'
                'name' => 'no_fields'
                'required' => ''
                'element_type' => 'html'
            )
        */

        // container
        $output = 'Type does not exist in list of types. retrieving list' ;
        $table_name = 'content_containers';
        $container_result = $connect->query("PRAGMA table_info(" . $table_name . ")");
        $container_result->setFetchMode(PDO::FETCH_ASSOC);


        foreach ($container_result as $conkey => $convalue)
        {

            $elements[$convalue['name']] = $convalue['name'];

        }

        // add data section

        $form = array();
        $form['name'] = 'add_'. $content_type.'_content';
        $form['id'] = 'add_' . $content_type.'_content';
        $form['method'] = 'POST';
        $form['action'] = $cck->_url($this->section .'/content_add_submit/'. $content_type);
        $form['title'] = 'add content for this type';
        $form['enctype'] = 'text/plain'; // viewer cannot be posted

        // check for any previous form submission
        $previous = (isset($_SESSION[$form['name'].'_'. session_id()]) ? $_SESSION[$form['name'].'_'. session_id()] : '');

        //print $cck->_debug($previous);

        foreach($elements as $key => $value)
        {
            switch($key)
            {

                case 'data':
//exit($cck->_debug($value));
                    $form['elements']['datastart'] =
                        array(
                            'type' => 'html',
                            'value' => '<div class="data-group"><h4>Fields</h4>',
                        );
                    if(!empty($value))
                    {
                        // get data field count
                        $data_field_count = count($value);
                        $count_down = $data_field_count;
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
                                    'value' => (isset($data_element['value'])? $data_element['value'] : ''),
                                    'placeholder'=> 'database field_id_'.  $data_element['field_id'],
                                    'required' => $data_element['required'],

                                );
                            if($data_element['field_id'] == $args[1])
                            {
                                $form['elements']['data-'. $data_key ]['before'] = '<div style="background-color:rgba(255, 139, 139, 0.62); padding:2px; border-radius: 4px">';
                                $form['elements']['data-'. $data_key ]['after'] = '</div>';
                            }
                            // start grouping of data fields with count

                        }
                    }
                    $form['elements']['dataend'] =
                        array(
                            'type' => 'html',
                            'value'=> '</div>',
                        );


                    break;


            }



        }
        //echo $key . $count_all;
        // last element closer
/*
        $form['elements']['end'] =
            array(
                'type' => 'html',
                'value'=> 'Field to be deleted is highlighted in red',
                'before' => '<div class="meta-group">',
                'after'=> '</div>',
            );

*/

        $output = $cck->_form($form,'html_form');
        return $output;

    }

    
    /**
    *   Content types add form
    */
    
    function content_type_add()
    {
    	global $cck;

        $content_title = 'Content Add Type';

    	// get all links from each class controller
    	$menu = $cck->_hooks('hook_links');
    	    
    	// get sublinks just for this module
    	$sub_menu = $this->hook_admin_links();
    	    
    	$variables['navigation'] = $cck->_menu_links($menu, 'links_main_menu');
    	$variables['sub_navigation'] = $cck->_module_links($sub_menu,
            array(
                'template'=>'links_sub_menu',
                'index' => $this->module
            ));
    	$variables['page_title'] = $this->page_title;
    	$variables['content_title'] = 'Content add type ';
    	
        $form = new content_form();
        $output = $form->content_form_add_type();

        $variables['page_title'] = $this->page_title;
        $variables['content_title'] = $content_title;
        $variables['content'] = $output;
        print $cck->_view('page_admin', $variables);
    	
    }

    function content_type_add_submit()
    {
        global $cck;
        $output = $cck->_debug($_POST);
        $variables['page_title'] = $this->page_title;
        $variables['content_title'] = 'submit';
        $variables['content'] = $output;
        print $cck->_view('page_admin', $variables);
    }
    
    /**
    *   Content types edit fields and settings
    */
    
    function content_type_edit($type = NULL)
    {
        global $cck, $settings;
        $args = $cck->_args();

        // get all links from each class controller
        $main_menu = $cck->_hooks('hook_links');
        $sub_menu = $this->hook_admin_links();

        $variables['navigation'] = $cck->_menu_links($main_menu, 'links_main_menu');
        $variables['sub_navigation'] = $cck->_module_links($sub_menu,
            array(
                'template'=>'links_sub_menu',
                'index' => $this->module
            )
        );
        try
        {
            $connect = $cck->_dbconnect('datasource_default');
            $result = $connect->prepare("SELECT type_id, label, type, description, template FROM content_types WHERE type_id='". $args[0] ."'");
            $result->execute();
            $data = $result->fetch(PDO::FETCH_ASSOC);
         }
        catch (Exception $e)
        {
            echo 'Data retrieval error: ',  $e->getMessage(), "\n";
        }

        $form = new content_form();
        $output = $form->content_form_content_type($data);

        $variables['page_title'] = $this->page_title;
        $variables['content_title'] = 'Content type '. ARROW_RIGHT. ' ' . $data['label'];
        $variables['content'] = $output;
        print $cck->_view('page_admin', $variables);
    }

    function content_type_edit_submit()
    {
        global $cck;
        $output = $cck->_debug($_POST);
        //$updated = $cck->_model('content','content_type_field_save', $_POST);

        $variables['page_title'] = $this->page_title;
        $variables['content_title'] = 'submit';
        $variables['content'] = $output;
        print $cck->_view('page_admin', $variables);
    }
    

    



}


?>

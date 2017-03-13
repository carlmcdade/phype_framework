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

// Define a class
namespace content;

use \PDO;
use \PDOException;

class content_form
{

    public $section;
    public $module;

    function __construct()
    {
        $this->section = __CLASS__;
        $this->module = __NAMESPACE__;
    }


    function content_form_content_edit($elements = array(), $field_data = array(), $action = NULL)
    {
        // add data section
        global $cck;

        $form = array();
        $form['name'] = 'edit_'. $elements['content_type_info']['label'] .'_content';
        $form['id'] = 'edit_' . $elements['content_type_info']['label'] .'_content';
        $form['method'] = 'POST';
        $form['action'] = $cck->_url('admin/'. $this->module .'/content_edit_submit/');
        $form['title'] = 'edit content for this type';
        $form['enctype'] = 'multipart/form-data';

        // check for any previous form submission

        foreach($elements as $key => $value)
        {
            switch($key)
            {
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

                                    $files['files'] = $field_data[$data_key];
                                    $files['field'] = $data_element['name'];
                                    $form['elements']['data-existing-'. $data_key ] =
                                        array(
                                            'type' => 'html',
                                            'label' => $data_element['label'],
                                            'value' => (isset($field_data[$data_key]) ? $cck->_model('content','content_format_files',$files) : '')."",

                                        );
                                    $form['elements']['data-'. $data_key ] =
                                        array(
                                            'type' => $data_element['element_type'],
                                            'id' => 'id-' . $data_element['label'],
                                            'class' => 'class-' .$data_element['label'],
                                            'title' => $data_element['label'],
                                            'name' => 'data['.$data_element['name'] .']',
                                            'multiple' => $data_element['multiple'],
                                            'required' => $data_element['required'],
                                            'description' => 'existing files with same name will be over-written. '

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
                                            'html' => (isset($data_element['html']) ? $data_element['html'] : ''),
                                            'name' => 'data['.$data_element['name'] .']',
                                            'value' => (isset($field_data[$data_key]) ? $field_data[$data_key] : ''),
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
                                //$form['elements']['data-existing-'. $data_key ]['after'] = '</div>';
                                //$form['elements']['data-new-'. $data_key ]['after'] = '</div>';
                            }

                        }
                    }


                    break;
                case 'ccid':

                $form['elements'][$key] =
                    array(
                        'type' => 'text',
                        'id' => 'id-' . $key,
                        'class' => 'class-' . $key,
                        'title' => $value,
                        'label' => $key,
                        'name' => 'container['. $key .']',
                        'value' => $value,
                        'readonly' => true,
                        'before' => '<div class="meta-group"><h4>Meta</h4>'

                    );

                break;
                case 'last_update':

                    $form['elements'][$key] =
                        array(
                            'type' => 'text',
                            'id' => 'id-' . $key,
                            'class' => 'class-' . $key,
                            'title' => $value,
                            'label' => str_replace('_', ' ',$key),
                            'name' => 'container['. $key .']',
                            'value' => date( 'Y-m-d H:m:s', (!empty($value) ? $value : time())),
                            );

                    break;
                case 'date_created':

                    $form['elements'][$key] =
                        array(
                            'type' => 'text',
                            'id' => 'id-' . $key,
                            'class' => 'class-' . $key,
                            'title' => $value,
                            'label' => str_replace('_', ' ',$key),
                            'name' => 'container['. $key .']',
                            'readonly' => true,
                            'value' => date( 'Y-m-d H:m:s', $value),


                        );

                    break;

                case 'content_type_id':


                    $form['elements']['content_type_id'] =
                        array(
                            'type' => 'hidden',
                            'label' => 'type',
                            'id'=> 'hidden-'.$elements['content_type_info']['type'],
                            'class'=> 'hidden-'.$elements['content_type_info']['type'],
                            'name'=> 'container[content_type_id]',
                            'form'=> $form['name'],
                            'value'=> $elements['content_type_id'],

                        );
                    $form['elements']['content_type_label'] =
                        array(
                            'type' => 'text',
                            'label' => 'type',
                            'id'=> $elements['content_type_info']['type'],
                            'class'=> $elements['content_type_info']['type'],
                            'name'=> 'container[content_type_label]',
                            'form'=> $form['name'],
                            'value'=> $elements['content_type_info']['label'],
                            'readonly' => true

                        );
                    break;

                default:
                    if(!is_array($value))
                    {

                        $form['elements'][$key] =
                            array(
                                'type' => 'text',
                                'id' => 'id-' . $key,
                                'class' => 'class-' . $key,
                                'title' => $value,
                                'label' => str_replace('_', ' ',$key),
                                'name' => 'container['.$key .']',
                                'value' => $value,
                                'placeholder'=> '',

                            );

                    }


                    break;


            }



        }
        //echo $key . $count_all;
        // last element closer
        //$form['elements'][$key]['after'] = '</div></div>';
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
                'after' => '</div>'
            );

        //$output = $cck->_debug($form);
        //exit($output);
        return $cck->_form($form,'html_form');
    }

    function content_form_content_delete($elements = array(), $fielddata = array(), $action = NULL)
    {
        // add data section
        global $cck;

        $form = array();
        $form['name'] = 'edit_'. $elements['content_type_info']['label'] .'_content';
        $form['id'] = 'edit_' . $elements['content_type_info']['label'] .'_content';
        $form['method'] = 'POST';
        $form['action'] = $cck->_url('admin/'. $this->module .'/content_delete_submit/'.$elements['ccid']);
        $form['title'] = 'delete content for this type';
        $form['enctype'] = '';

        // check for any previous form submission

        //print $cck->_debug($previous);

        foreach($elements as $key => $value)
        {
            switch($key)
            {
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
                                            'type' => 'text',
                                            'id' => 'id-' . $data_element['label'],
                                            'class' => 'class-' .$data_element['label'],
                                            'title' => $data_element['label'],
                                            'name' => $data_element['name'],
                                            'label' => $data_element['label'],
                                            'value' => (isset($field_data[$data_key]) ? $field_data[$data_key] : ''),
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
                                            'value' => (isset($field_data[$data_key]) ? $field_data[$data_key] : ''),
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
                        $form['elements']['data-delete'] =
                            array(
                                'type' => 'submit',
                                'id'=> 'delete-data',
                                'class'=> 'delete-data',
                                'title'=> 'delete data and keep container',
                                'name'=> 'delete',
                                'label'=> 'save',
                                'value'=> 'delete data',
                                'formaction'=> $cck->_url('admin/'. $this->module .'/content_delete_submit/'. $elements['ccid']) ,
                            );
                    }


                    break;
                case 'ccid':

                    $form['elements'][$key] =
                        array(
                            'type' => 'text',
                            'id' => 'id-' . $key,
                            'class' => 'class-' . $key,
                            'title' => $value,
                            'label' => $key,
                            'name' => 'container['. $key .']',
                            'value' => $value,
                            'readonly' => '',
                            'before' => '<div class="meta-group"><h4>Meta</h4>'

                        );

                    break;
                case 'date_created':

                    $form['elements'][$key] =
                        array(
                            'type' => 'text',
                            'id' => 'id-' . $key,
                            'class' => 'class-' . $key,
                            'title' => $value,
                            'label' => str_replace('_', ' ',$key),
                            'name' => 'container['. $key .']',
                            'value' => $cck->_format_datetime($elements['date_created']),


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
                            'value'=> $elements['content_type_id'],

                        );
                    $form['elements']['content_type_label'] =
                        array(
                            'type' => 'text',
                            'label' => 'type',
                            'id'=> 'mytype',
                            'class'=> 'mytype',
                            'name'=> 'container[content_type_label]',
                            'form'=> 'content_type_'.$elements['content_type_info']['label'] . '_edit',
                            'value'=> $elements['content_type_info']['label'],
                            'readonly' => true

                        );
                    break;

                default:
                    if(!is_array($value))
                    {

                        $form['elements'][$key] =
                            array(
                                'type' => 'text',
                                'id' => 'id-' . $key,
                                'class' => 'class-' . $key,
                                'title' => $value,
                                'label' => str_replace('_', ' ',$key),
                                'name' => 'container['.$key .']',
                                'value' => $value,
                                'placeholder'=> '',

                            );

                    }


                    break;


            }



        }
        //echo $key . $count_all;
        // last element closer
        $form['elements'][$key]['after'] = '</div>';

        $form['elements']['delete_container'] =
            array(
                'type' => 'submit',
                'id'=> 'delete-container',
                'class'=> 'delete-container',
                'title'=> 'delete container and orphan data',
                'name'=> 'delete',
                'label'=> 'save',
                'value'=> 'delete container',
                'before'=> '<div></div>',
            );

        $form['elements']['delete_all'] =
            array(
                'type' => 'submit',
                'id'=> 'delete-all',
                'class'=> 'delete-all',
                'title'=> 'delete all',
                'name'=> 'delete',
                'label'=> 'save',
                'value'=> 'delete all',
            );

        //$output = $cck->_debug($form);
        //exit($output);
        return $cck->_form($form,'html_form');

    }

    function content_form_field_delete($args = array())
    {
        // add data section
        global $cck;

        $form = array();
        $form['name'] = 'delete_field_content';
        $form['id'] = 'delete_field_content';
        $form['method'] = 'POST';
        $form['action'] = $cck->_url('admin/'. $this->module .'/content_type_field_delete_submit/'. $args[0]. '/' . $args[1]);
        $form['title'] = 'delete field for this type';
        $form['enctype'] = '';

        // check for any previous form submission

        //print $cck->_debug($previous);

        $form['elements']['delete_instructions'] =
            array(
                'type' => 'html',
                'value'=> '<div class="instructions"><p> Deleting only the fields leaves the data created by them in the database to be used by
                           other systems like a web services or module API.</p></div>',
            );

        $form['elements']['delete_container'] =
            array(
                'type' => 'submit',
                'id'=> 'delete-container',
                'class'=> 'delete-container',
                'title'=> 'delete field and orphan data',
                'name'=> 'delete',
                'label'=> 'save',
                'value'=> 'only field',
            );

        $form['elements']['delete_all'] =
            array(
                'type' => 'submit',
                'id'=> 'delete-all',
                'class'=> 'delete-all',
                'title'=> 'delete field and all data',
                'name'=> 'delete',
                'label'=> 'save',
                'value'=> 'field and data',
            );

        //$output = $cck->_debug($form);
        //exit($output);
        return $cck->_form($form,'html_form');

    }


    // Method of the class
    function content_form_add_type_field($data = NULL)
    {
        global $cck, $settings;
        $args = $cck->_args();

        // content type values
        $connect = $cck->_dbconnect('datasource_default');
        $result = $connect->prepare("SELECT field_type_id, type FROM content_types_fields_types");
        $result->execute();
        $list = $result->fetchALL(PDO::FETCH_ASSOC);
        //print $cck->_debug($list);
        //exit;

        foreach ($list as $key => $line) {

            if (isset($data['field_type_id']) && $data['field_type_id'] == $line['field_type_id']) {
                $options[] = array(
                    'type' => 'option',
                    'id' => $line['type'] . '-' . $line['field_type_id'],
                    'class' => $line['type'] . '-' . $line['field_type_id'],
                    'value' => $line['field_type_id'],
                    'description' => $line['type'],
                    'selected' => '');
            } else {
                $options[] = array(
                    'type' => 'option',
                    'id' => $line['type'] . '-' . $line['field_type_id'],
                    'class' => $line['type'] . '-' . $line['field_type_id'],
                    'value' => $line['field_type_id'],
                    'description' => $line['type']);
            }
            if ($line['type'] != '') {
                $link['path'] = 'admin/' . $this->module . '/content_type_field_add/' . $args[0] . '/' . $line['field_type_id'];
                $link['text'] = $line['type'];
                $types[$line['type']] = $cck->_link('links', $link);
            }

        }


        $form = array();
        $form['name'] = 'content_type_field_add';
        $form['id'] = 'content_type_add';
        $form['method'] = 'POST';
        $form['action'] = $cck->_url('admin/' . $this->module . '/content_type_field_add_submit');
        $form['title'] = 'send a message';
        $form['enctype'] = '';

        // field element types
        /*
        $form['elements']['field_types_links'] =
            array(
                'name' => 'types_list',
                'type' => 'html',
                'value'=> $type_list,
            );*/
        $form['elements']['field_types'] =
            array(
                'type' => 'select',
                'label' => 'Field type',
                'id' => 'field_types',
                'class' => 'field_types',
                'name' => 'Types',
                'form' => $form['name'],
                'options' => $options,
            );

        $form['elements']['content_field_label'] =
            array(
                'type' => 'text',
                'id' => 'content_field_label',
                'class' => 'content_field_label',
                'title' => 'content_field_label',
                'label' => 'Label',
                'name' => 'content_field_label',
                'value' => (isset($data['label']) ? '' . $data['label'] . '' : ''),
                'placeholder' => 'label',
            );
        $form['elements']['content_field_name'] =
            array(
                'type' => 'text',
                'id' => 'content_field_name',
                'class' => 'content_field_name',
                'title' => 'content_field_name',
                'name' => 'content_field_name',
                'label' => 'Name',
                'value' => (isset($data['name']) ? '' . $data['name'] . '' : ''),
                'placeholder' => 'field name',
            );
        $form['elements']['content_field_id'] =
            array(
                'type' => 'text',
                'id' => 'content_field_id',
                'class' => 'content_field_id',
                'title' => 'content_field_id',
                'name' => 'content_field_id',
                'label' => 'CSS ID',
                'value' => '',
                'placeholder' => 'style sheet id',
            );
        $form['elements']['content_field_class'] =
            array(
                'type' => 'text',
                'id' => 'content_field_class',
                'class' => 'content_field_class',
                'title' => 'content_field_class',
                'name' => 'content_field_class',
                'label' => 'CSS Class',
                'value' => '',
                'placeholder' => 'style sheet class',
            );

        $form['elements']['content_field_autocomplete'] =
            array(
                'type' => 'checkbox',
                'id' => 'content_field_autocomplete',
                'class' => 'content_field_autocomplete',
                'title' => 'content_field_autocomplete',
                'name' => 'content_field_autocomplete',
                'label' => 'Autocomplete',
                'description' => 'will show users previous choice for field',
                'checked' => (isset($data['checked']) ? $data['checked'] : ''),
                'value' => '',
                'placeholder' => '',

            );
        $form['elements']['content_field_disabled'] =
            array(
                'type' => 'checkbox',
                'id' => 'content_field_disabled',
                'class' => 'content_field_disabled',
                'title' => 'content_field_disabled',
                'name' => 'content_field_disabled',
                'label' => 'Disabled',
                'description' => 'disabled fields send no data',
                'checked' => (isset($data['checked']) ? $data['checked'] : ''),
                'value' => '',
                'placeholder' => '',

            );
        $form['elements']['content_field_readonly'] =
            array(
                'type' => 'checkbox',
                'id' => 'content_field_readonly',
                'class' => 'content_field_readonly',
                'title' => 'content_field_readonly',
                'name' => 'content_field_readonly',
                'label' => 'Read only',
                'description' => 'user cannot edit data sent',
                'checked' => (isset($data['checked']) ? $data['checked'] : ''),
                'value' => '',
                'placeholder' => '',

            );
        $form['elements']['content_field_required'] =
            array(
                'type' => 'checkbox',
                'id' => 'content_field_required',
                'class' => 'content_field_required',
                'title' => 'content_field_required',
                'name' => 'content_field_required',
                'label' => 'Required',
                'description' => 'required fields are input validated',
                'checked' => (isset($data['checked']) ? $data['checked'] : ''),
                'value' => '1',
                'placeholder' => '',
            );

        $templates = array(
            'options' =>
                array(
                    'type' => 'option',
                    'id' => 'default-template',
                    'class' => 'default-template',
                    'value' => 'default',
                    'description' => 'default')
        );
        $form['elements']['templates'] =
            array(
                'type' => 'select',
                'id' => 'template',
                'class' => 'template',
                'title' => 'Template',
                'name' => 'template',
                'label' => 'template',
                'options' => $templates,
            );

        $form['elements']['save'] =
            array(
                'type' => 'submit',
                'id' => 'save-field',
                'class' => 'save-field',
                'title' => 'save field',
                'name' => 'save_field',
                'label' => 'save',
                'value' => 'save',
                'before' => '<div></div>',
            );

        $variables['content'] = $cck->_form($form, 'html_form');
        $variables['root'] = 'Types';
        $variables['levels'] = $types;
        $output = $cck->_view('links_drop_menu', $variables);

        //$output .= $cck->_debug($data);

        return $output;
    }


    // Method of the class
    function content_form_edit_type_field($data = NULL)
    {
        global $cck, $settings;
        $args = $cck->_args();

        // content type values
        $connect = $cck->_dbconnect('datasource_default');
        $result = $connect->prepare("SELECT field_type_id, type FROM content_types_fields_types");
        $result->execute();
        $list = $result->fetchALL(PDO::FETCH_ASSOC);
        //print $cck->_debug($list);
        //exit;

        foreach ($list as $key => $line) {

            if (isset($data['field_type_id']) && $data['field_type_id'] == $line['field_type_id']) {
                $options[] = array(
                    'type' => 'option',
                    'id' => $line['type'] . '-' . $line['field_type_id'],
                    'class' => $line['type'] . '-' . $line['field_type_id'],
                    'value' => $line['field_type_id'],
                    'description' => $line['type'],
                    'selected' => '');
            } else {
                $options[] = array(
                    'type' => 'option',
                    'id' => $line['type'] . '-' . $line['field_type_id'],
                    'class' => $line['type'] . '-' . $line['field_type_id'],
                    'value' => $line['field_type_id'],
                    'description' => $line['type']);
            }
            if ($line['type'] != '') {
                $link['path'] = 'admin/' . $this->module . '/content_type_field_add/' . $args[0] . '/' . $line['field_type_id'];
                $link['text'] = $line['type'];
                $types[$line['type']] = $cck->_link('links', $link);
            }

        }


        $form = array();
        $form['name'] = 'content_type_field_edit';
        $form['id'] = 'content_type_edit';
        $form['method'] = 'POST';
        $form['action'] = $cck->_url('admin/' . $this->module . '/content_type_field_edit_submit/');
        $form['title'] = 'send a message';
        $form['enctype'] = '';

        // field element types
        /*
        $form['elements']['field_types_links'] =
            array(
                'name' => 'types_list',
                'type' => 'html',
                'value'=> $type_list,
            );*/
        $form['elements']['field_types'] =
            array(
                'type' => 'select',
                'label' => 'Field type',
                'id' => 'field_types',
                'class' => 'field_types',
                'name' => 'Types',
                'form' => $form['name'],
                'options' => $options,
            );

        $form['elements']['content_field_label'] =
            array(
                'type' => 'text',
                'id' => 'content_field_label',
                'class' => 'content_field_label',
                'title' => 'content_field_label',
                'label' => 'Label',
                'name' => 'content_field_label',
                'value' => (isset($data['label']) ? '' . $data['label'] . '' : ''),
                'placeholder' => 'label',
            );
        $form['elements']['content_field_name'] =
            array(
                'type' => 'text',
                'id' => 'content_field_name',
                'class' => 'content_field_name',
                'title' => 'content_field_name',
                'name' => 'content_field_name',
                'label' => 'Name',
                'value' => (isset($data['name']) ? '' . $data['name'] . '' : ''),
                'placeholder' => 'field name',
            );
        $form['elements']['content_field_id'] =
            array(
                'type' => 'text',
                'id' => 'content_field_id',
                'class' => 'content_field_id',
                'title' => 'content_field_id',
                'name' => 'content_field_id',
                'label' => 'CSS ID',
                'value' => '',
                'placeholder' => 'style sheet id',
            );
        $form['elements']['content_field_class'] =
            array(
                'type' => 'text',
                'id' => 'content_field_class',
                'class' => 'content_field_class',
                'title' => 'content_field_class',
                'name' => 'content_field_class',
                'label' => 'CSS Class',
                'value' => '',
                'placeholder' => 'style sheet class',
            );

        $form['elements']['content_field_autocomplete'] =
            array(
                'type' => 'checkbox',
                'id' => 'content_field_autocomplete',
                'class' => 'content_field_autocomplete',
                'title' => 'content_field_autocomplete',
                'name' => 'content_field_autocomplete',
                'label' => 'Autocomplete',
                'description' => 'will show users previous choice for field',
                'checked' => (isset($data['checked']) ? $data['checked'] : ''),
                'value' => '',
                'placeholder' => '',

            );
        $form['elements']['content_field_disabled'] =
            array(
                'type' => 'checkbox',
                'id' => 'content_field_disabled',
                'class' => 'content_field_disabled',
                'title' => 'content_field_disabled',
                'name' => 'content_field_disabled',
                'label' => 'Disabled',
                'description' => 'disabled fields send no data',
                'checked' => (isset($data['checked']) ? $data['checked'] : ''),
                'value' => '',
                'placeholder' => '',

            );
        $form['elements']['content_field_readonly'] =
            array(
                'type' => 'checkbox',
                'id' => 'content_field_readonly',
                'class' => 'content_field_readonly',
                'title' => 'content_field_readonly',
                'name' => 'content_field_readonly',
                'label' => 'Read only',
                'description' => 'user cannot edit data sent',
                'checked' => (isset($data['checked']) ? $data['checked'] : ''),
                'value' => '',
                'placeholder' => '',

            );
        $form['elements']['content_field_required'] =
            array(
                'type' => 'checkbox',
                'id' => 'content_field_required',
                'class' => 'content_field_required',
                'title' => 'content_field_required',
                'name' => 'content_field_required',
                'label' => 'Required',
                'description' => 'required fields are input validated',
                'checked' => (isset($data['checked']) ? $data['checked'] : ''),
                'value' => '1',
                'placeholder' => '',
            );

        $templates = array(
            'options' =>
                array(
                    'type' => 'option',
                    'id' => 'default-template',
                    'class' => 'default-template',
                    'value' => 'default',
                    'description' => 'default')
        );
        $form['elements']['templates'] =
            array(
                'type' => 'select',
                'id' => 'template',
                'class' => 'template',
                'title' => 'Template',
                'name' => 'template',
                'label' => 'template',
                'options' => $templates,
            );

        $form['elements']['save'] =
            array(
                'type' => 'submit',
                'id' => 'save-field',
                'class' => 'save-field',
                'title' => 'save field',
                'name' => 'save_field',
                'label' => 'save',
                'value' => 'save',
                'before' => '<div></div>',
            );

        $variables['content'] = $cck->_form($form, 'html_form');
        $variables['root'] = 'Types';
        $variables['levels'] = $types;
        $output = $cck->_view('links_drop_menu', $variables);

        //$output .= $cck->_debug($data);

        return $output;
    }

    function content_form_content_type($data = NULL)
    {
        global $cck, $settings;
        $args = $cck->_args();
        $action = '';

        switch (true) {
            case $data != NULL:
                $action = 'edit';
                break;
            default:
                $action = 'add';
                break;

        }

        $form = array();
        $form['name'] = 'content_type_add';
        $form['id'] = 'content_type_add';
        $form['method'] = 'POST';
        $form['action'] = $cck->_url('admin/' . $this->module . '/content_type_submit/' . $action);
        $form['title'] = 'save a content type';
        $form['enctype'] = '';
        $form['elements']['type'] =
            array(
                'type' => 'text',
                'id' => 'id-' . 'type',
                'class' => 'class-' . 'type',
                'title' => 'type',
                'label' => 'Type',
                'name' => 'type-name',
                'value' => (isset($data['type']) ? $data['type'] : ''),
                'placeholder' => 'type name'
            );

        $form['elements']['label'] =
            array(
                'type' => 'text',
                'id' => 'id-' . 'label',
                'class' => 'class-' . 'label',
                'title' => 'label',
                'label' => 'Label',
                'name' => 'type-label',
                'value' => (isset($data['label']) ? $data['label'] : ''),
                'placeholder' => 'type label'
            );

        $form['elements']['description'] =
            array(
                'type' => 'text',
                'id' => 'id-' . 'description',
                'class' => 'class-' . 'description',
                'title' => 'description',
                'label' => 'Description',
                'description' => ' write as description of the purpose of this content type.',
                'name' => 'type-description',
                'value' => (isset($data['description']) ? $data['description'] : ''),
                'placeholder' => 'type description'
            );


        $form['elements']['submit'] =
            array(
                'type' => 'submit',
                'id' => 'save',
                'class' => 'save',
                'title' => 'save',
                'name' => 'save',
                'label' => 'save',
                'value' => 'save',
                'before' => '<div></div>',
            );

        return $cck->_form($form, 'html_form');

    }

    function content_form_add_type($data = NULL)
    {
        //
        global $cck, $settings;

        $args = $cck->_args();

        $connect = $cck->_dbconnect('datasource_default');

        // table rows and field values
        if (isset($args[0])) {
            $get_types = $connect->prepare("SELECT type, label, description FROM content_types WHERE type_id='" . $args[0] . "'");

        } else {
            $get_types = $connect->prepare("SELECT type, label, description FROM content_types");

        }

        $get_types->execute();


        $columns = $get_types->fetchAll();

        // table header
        foreach ($columns[0] as $key => $value) {
            if (!is_numeric($key)) {
                $elements[] = $key;
            }
        }

        $form = array();
        $form['name'] = 'content_type_add';
        $form['id'] = 'content_type_add';
        $form['method'] = 'POST';
        $form['action'] = $cck->_url($this->section . '/content_type_submit/');
        $form['title'] = 'send a message';
        $form['enctype'] = '';
        $form['elements']['new_type'] =
            array(
                'type' => 'text',
                'id' => 'id-' . 'type',
                'class' => 'class-' . 'type',
                'title' => 'type',
                'label' => 'Type',
                'name' => 'type',
                'value' => '',
                'placeholder' => 'type name'
            );

        foreach ($elements as $key => $value) {

            switch ($value) {

                case 'type':

                    $disabled = FALSE;

                    foreach ($columns as $a => $type) {
                        if (isset($args[0]) && $args[0] == $type['type']) {
                            $list[] = array(
                                'type' => 'option',
                                'id' => 'type_' . $a,
                                'class' => 'type_' . $a,
                                'value' => $type['type'],
                                'description' => $type['label'],
                                'selected' => 'selected',
                            );

                        } else {
                            $list[] = array(
                                'type' => 'option',
                                'id' => 'type_' . $a,
                                'class' => 'type_' . $a,
                                'value' => $type['type'],
                                'description' => $type['label'],
                            );
                        }

                    }
                    $form['elements']['existing_types'] =
                        array(
                            'type' => 'select',
                            'label' => 'existing types',
                            'id' => 'mytype',
                            'class' => 'mytype',
                            'name' => 'nametype',
                            'form' => 'content_type_add',
                            'options' => $list,
                            'disabled' => $disabled,
                        );
                    break;
                default:
                    $form['elements'][$key] =
                        array(
                            'type' => 'text',
                            'id' => 'id-' . $key,
                            'class' => 'class-' . $key,
                            'title' => $value,
                            'label' => $value,
                            'name' => $value,
                            'value' => '',
                            'placeholder' => ''
                        );
                    break;
            }

        }

        $form['elements']['send'] =
            array(
                'type' => 'submit',
                'id' => 'send',
                'class' => 'send',
                'title' => 'send',
                'name' => 'send',
                'label' => 'send',
                'value' => 'save',
                'before' => '<div></div>',
            );

        return $cck->_form($form, 'html_form');
    }

    function content_form_field_types($quick_edit = FALSE)
    {
        global $cck, $settings;
        $types = array();
        $args = $cck->_args();

        $connect = $cck->_dbconnect('datasource_default');
        $result = $connect->prepare("SELECT field_type_id, type FROM content_types_fields_types");
        $result->execute();
        $list = $result->fetchALL(PDO::FETCH_ASSOC);

        foreach ($list as $key => $line) {

            if ($quick_edit == TRUE) {
                $link['path'] = 'admin/' . $this->module . '/content_type_quick_field_add_submit/' . $args[0] . '/' . $line['field_type_id'];
                $variables['content'] = 'Add a new field without configuration dialog';
            } else {
                $link['path'] = 'admin/' . $this->module . '/content_type_field_add/' . $args[0] . '/' . $line['field_type_id'];
                $variables['content'] = 'Click the add button and select then configure new fields for this content type';
            }
            if ($line['type'] != '') {

                $link['text'] = $line['type'];
                $types[$line['type']] = $cck->_link('links', $link);
            }

        }

        $variables['root'] = 'Types';
        $variables['levels'] = $types;
        $output = $cck->_view('links_drop_menu', $variables);

        return $output;

    }

    function content_form_field_form_builder($element = array(), $content_type = NULL, $action = NULL)
    {
        global $cck, $settings;
        $output = '';

        $field_count = $cck->_model('content', 'content_type_fields_count', $content_type);
        $content_type_info = $cck->_model('content', 'content_type_get', $content_type);
        //$field_type = $cck->_model('content','content_type_fields_count', $content_type);
        //exit($cck->_debug($content_type));

        $form = array();
        $form['name'] = 'content_type_' . $content_type_info['label'] . '_field_add';
        $form['id'] = 'content_type_' . $content_type_info['label'] . '_field_add';
        $form['method'] = 'POST';
        $form['action'] = $cck->_url($action);
        $form['title'] = 'create a field';
        $form['enctype'] = '';
        $form['before'] = '<h2 style="clear: both;">' . $element['type'] . '</h2>';


        foreach ($element as $key => $attribute) {

            if ($attribute === 'false') {
                continue;
            }
            $element['label'] = $key;
            $element['value'] = $attribute;
            $element['name'] = $key;
            switch ($key) {
                case 'setdefault' :
                    $form['elements']['hidden-'.$key] =
                        array(
                            'type' => 'hidden',
                            'id' => 'hidden-' . $key,
                            'class' => 'hidden-' . $key,
                            'name' => 'chk-' . $key,
                            'value' => 'off',
                        );
                    $form['elements']['visible-'.$key] =
                        array(
                            'type' => 'checkbox',
                            'id' => 'chk-' . $key,
                            'class' => 'chk-' . $key,
                            'title' => $key,
                            'name' => 'chk-' . $key,
                            'label' => 'set as default',
                            'value' => 'on',
                            'description' => 'fill in the field with these values when element is presented to user'
                        );
                    break;
                case 'checked' :
                    $form['elements']['hidden-'.$key] =
                        array(
                            'type' => 'hidden',
                            'id' => 'hidden-' . $key,
                            'class' => 'hidden-' . $key,
                            'name' => 'chk-' . $key,
                            'value' => 'off',
                        );
                    $form['elements']['visible-'.$key] =
                        array(
                            'type' => 'checkbox',
                            'id' => 'chk-' . $key,
                            'class' => 'chk-' . $key,
                            'title' => $key,
                            'name' => 'chk-' . $key,
                            'label' => $cck->_plain_text($key),
                            'value' => 'on',
                            'placeholder' => '',
                            'description' => 'mark as selected from previous submission or required'
                        );
                    break;
                case 'html' :
                    $form['elements']['hidden-'.$key] =
                        array(
                            'type' => 'hidden',
                            'id' => 'hidden-' . $key,
                            'class' => 'hidden-' . $key,
                            'name' => 'chk-' . $key,
                            'value' => 'off',
                        );
                    $form['elements']['visible-'.$key] =
                        array(
                            'type' => 'checkbox',
                            'id' => 'chk-' . $key,
                            'class' => 'chk-' . $key,
                            'title' => $key,
                            'name' => 'chk-' . $key,
                            'label' => $cck->_plain_text($key),
                            'value' => 'on',
                            'placeholder' => '',
                            'description' => ' show HTML5 editor for this field'
                        );
                    break;
                case 'wrap' :
                    $form['elements']['hidden-'.$key] =
                        array(
                            'type' => 'hidden',
                            'id' => 'hidden-' . $key,
                            'class' => 'hidden-' . $key,
                            'name' => 'chk-' . $key,
                            'value' => 'off',
                        );
                    $form['elements']['visible-'.$key] =

                        array(
                            'type' => 'checkbox',
                            'id' => 'chk-' . $key,
                            'class' => 'chk-' . $key,
                            'title' => $key,
                            'name' => 'chk-' . $key,
                            'label' => $cck->_plain_text($key),
                            'value' => 'on',
                            'placeholder' => '',
                            'description' => 'hard wrap field text requires setting cols attribute. default is soft wrap'
                        );
                    break;
                case 'required' :
                    $form['elements']['hidden-'.$key] =
                    array(
                        'type' => 'hidden',
                        'id' => 'hidden-' . $key,
                        'class' => 'hidden-' . $key,
                        'name' => 'chk-' . $key,
                        'value' => 'off',
                    );
                    $form['elements']['visible-'.$key] =

                        array(
                            'type' => 'checkbox',
                            'id' => 'chk-' . $key,
                            'class' => 'chk-' . $key,
                            'title' => $key,
                            'name' => 'chk-' . $key,
                            'label' => $cck->_plain_text($key),
                            'value' => 'on',
                            'placeholder' => '',
                            'description' => 'a browser generated message will appear for empty field'
                        );
                    break;
                case 'multiple' :
                    $form['elements']['hidden-'.$key] =
                    array(
                        'type' => 'hidden',
                        'id' => 'hidden-' . $key,
                        'class' => 'hidden-' . $key,
                        'name' => 'chk-' . $key,
                        'value' => 'off',
                    );
                    $form['elements']['visible-'.$key] =

                        array(
                            'type' => 'checkbox',
                            'id' => 'chk-' . $key,
                            'class' => 'chk-' . $key,
                            'title' => $key,
                            'name' => 'chk-' . $key,
                            'label' => $cck->_plain_text($key),
                            'value' => 'on',
                            'description' => 'a user may make several selections from list'
                        );
                    break;
                case 'autofocus' :
                    $form['elements']['hidden-'.$key] =
                    array(
                        'type' => 'hidden',
                        'id' => 'hidden-' . $key,
                        'class' => 'hidden-' . $key,
                        'name' => 'chk-' . $key,
                        'value' => 'off',
                    );
                    $form['elements']['visible-'.$key] =

                        array(
                            'type' => 'checkbox',
                            'id' => 'chk-' . $key,
                            'class' => 'chk-' . $key,
                            'title' => $key,
                            'name' => 'chk-' . $key,
                            'label' => $cck->_plain_text($key),
                            'value' => 'on',
                            'placeholder' => '',
                            'description' => 'field should automatically get focus when the page loads'
                        );
                    break;
                case 'autocomplete' :
                    $form['elements']['hidden-'.$key] =
                        array(
                            'type' => 'hidden',
                            'id' => 'hidden-' . $key,
                            'class' => 'hidden-' . $key,
                            'name' => 'chk-' . $key,
                            'value' => 'off',
                        );
                    $form['elements']['visible-'.$key] =
                        array(
                            'type' => 'checkbox',
                            'id' => 'chk-' . $key,
                            'class' => 'chk-' . $key,
                            'title' => $key,
                            'name' => 'chk-' . $key,
                            'label' => $cck->_plain_text($key),
                            'value' => 'on',
                            'placeholder' => '',
                            'description' => 'use the browser to suggest previous choices made by user'
                        );
                    break;
                case 'disabled' :
                    $form['elements']['hidden-'.$key] =
                        array(
                            'type' => 'hidden',
                            'id' => 'hidden-' . $key,
                            'class' => 'hidden-' . $key,
                            'name' => 'chk-' . $key,
                            'value' => 'off',
                        );
                    $form['elements']['visible-'.$key] =
                        array(
                            'type' => 'checkbox',
                            'id' => 'chk-' . $key,
                            'class' => 'chk-' . $key,
                            'title' => $key,
                            'name' => 'chk-' . $key,
                            'label' => $cck->_plain_text($key),
                            'value' => 'on',
                            'placeholder' => '',
                            'description' => 'information in a disabled field is not submitted'
                        );
                    break;
                case 'readonly' :
                    $form['elements']['hidden-'.$key] =
                        array(
                            'type' => 'hidden',
                            'id' => 'hidden-' . $key,
                            'class' => 'hidden-' . $key,
                            'name' => 'chk-' . $key,
                            'value' => 'off',
                        );
                    $form['elements']['visible-'.$key] =
                        array(
                            'type' => 'checkbox',
                            'id' => 'chk-' . $key,
                            'class' => 'chk-' . $key,
                            'title' => $key,
                            'name' => 'chk-' . $key,
                            'label' => $cck->_plain_text($key),
                            'value' => 'on',
                            'placeholder' => '',
                            'description' => 'field information is submitted but cannot be changed by user'
                        );
                    break;
                case 'options' :
                    $form['elements'][$key] =
                        array(
                            'type' => 'textarea',
                            'id' => $key,
                            'class' => $key,
                            'title' => $key,
                            'name' => $key,
                            'label' => $cck->_plain_text($key),
                            'value' => '',
                            'description' => 'each option is formatted [value] | [description] seperate options with newline group with {[group]:[value] | [description],[value] | [description]}',
                            'placeholder' => '{[group]:[value] | [description],[value] | [description]}' . "\n" . '[value] | [description]',
                        );
                    break;

                case 'html' :
                case 'html_before' :
                case 'html_after' :
                    $form['elements'][$key] =
                        array(
                            'type' => 'textarea',
                            'id' => $key,
                            'class' => $key,
                            'title' => $key,
                            'name' => $key,
                            'label' => $cck->_plain_text($key),
                            'value' => '',
                            'placeholder' => '',
                        );
                    break;
                case 'type':
                case 'content_type_id':
                case 'field_type_id':

                    $form['elements'][$key] =
                        array(
                            'type' => 'hidden',
                            'id' => $key,
                            'class' => $key,
                            'name' => $key,
                            'value' => $attribute,
                        );
                    break;
                case 'label':

                    $form['elements'][$key] =
                        array(
                            'type' => 'text',
                            'id' => $key,
                            'class' => $key,
                            'title' => $key,
                            'name' => $key,
                            'label' => $cck->_plain_text($key),
                            'value' => '',
                            'placeholder' => $content_type_info['label'] . '_field_' . ($field_count + 1) . '_' . $element['type'],
                        );
                    break;
                case 'name':

                    $form['elements'][$key] =
                        array(
                            'type' => 'text',
                            'id' => $key,
                            'class' => $key,
                            'title' => $key,
                            'name' => $key,
                            'label' => $cck->_plain_text($key),
                            'value' => '',
                            'placeholder' => $content_type_info['label'] . '_field_' . ($field_count + 1) . '_' . $element['type'],
                        );
                    break;
                case 'support':
                    $form['elements'][$key] =
                        array(
                            'type' => 'text',
                            'id' => $key,
                            'class' => $key,
                            'title' => $key,
                            'name' => $key,
                            'label' => $cck->_plain_text($key),
                            'value' => $attribute,
                            'readonly' => '',
                        );
                    break;
                case 'form':
                    $form['elements'][$key] =
                        array(
                            'type' => 'text',
                            'id' => $key,
                            'class' => $key,
                            'title' => $key,
                            'name' => $key,
                            'label' => $cck->_plain_text($key),
                            'value' => 'content_type_' . $content_type_info['label'] . '_add',
                            'readonly' => '',
                            'description' => 'the name of the form containing the field'
                        );
                    break;
                case 'defvalue':
                    switch ($element['type']) {
                        case 'radio';
                            $form['elements'][$key] =
                                array(
                                    'type' => 'text',
                                    'id' => $key,
                                    'class' => $key,
                                    'title' => $key,
                                    'name' => $key,
                                    'label' => 'value',
                                    'value' => '',
                                    'description' => 'the first option is formatted [value] | [description] add more to options field',
                                    'placeholder' => '[value] | [description]',
                                );
                            break;
                        case 'select';
                            $form['elements'][$key] =
                                array(
                                    'type' => 'text',
                                    'id' => $key,
                                    'class' => $key,
                                    'title' => $key,
                                    'name' => $key,
                                    'label' => $cck->_plain_text('selected'),
                                    'value' => '',
                                    'description' => 'the selected option is formatted [value] | [description]',
                                    'placeholder' => '[value] | [description]',
                                );
                            break;
                        case 'hidden';
                            $form['elements'][$key] =
                                array(
                                    'type' => 'textarea',
                                    'id' => $key,
                                    'class' => $key,
                                    'title' => $key,
                                    'name' => $key,
                                    'label' => $cck->_plain_text('code'),
                                    'value' => '',
                                    'readonly' => 'true',
                                    'description' => 'the value for this field is evaluated by a php function of the same name',
                                    'placeholder' => '<?php $' . $content_type_info['label'] . '_field_' . ($field_count + 1) . '_' . $element['type'] . ' =  function(){} ?>',
                                );
                            break;
                        default:
                            $form['elements'][$key] =
                                array(
                                    'type' => 'text',
                                    'id' => $key,
                                    'class' => $key,
                                    'title' => $key,
                                    'name' => $key,
                                    'label' => 'value',
                                    'value' => '',
                                    'placeholder' => '',
                                );
                            break;

                    }

                    break;
                case 'maxlength':

                    $description = '';
                    $placeholder = '';
                    $label = $key;

                    switch ($element['type']) {
                        case 'select':
                            $description = 'maximum number of options user may choose from list';
                            $label = 'number of options';
                            break;

                    }

                    $form['elements'][$key] =
                        array(
                            'type' => 'text',
                            'id' => $key,
                            'class' => $key,
                            'title' => $key,
                            'name' => $key,
                            'label' => $cck->_plain_text($label),
                            'value' => '',
                            'placeholder' => $placeholder,
                            'description' => $description
                        );
                    break;
                default:

                    $description = '';
                    $placeholder = '';

                    switch ($key) {


                        case 'description':
                            $description = 'write some help text for the user';
                            break;
                        case 'id':
                            $description = 'css id selector';
                            $placeholder = '#id';
                            break;
                        case 'class':
                            $description = 'css class selector';
                            $placeholder = '.class';
                            break;
                    }
                    $form['elements'][$key] =
                        array(
                            'type' => 'text',
                            'id' => $key,
                            'class' => $key,
                            'title' => $key,
                            'name' => $key,
                            'label' => $cck->_plain_text($key),
                            'value' => '',
                            'placeholder' => $placeholder,
                            'description' => $description
                        );

                    break;
            }


        }
        $form['elements']['send'] =
            array(
                'type' => 'submit',
                'id' => 'send',
                'class' => 'send',
                'title' => 'send',
                'name' => 'send',
                'label' => 'send',
                'value' => 'save',
                'before' => '<div></div>',
            );
        // $form_output = '<h2>' . $element['type'] . '</h2>';
        $form_output = $cck->_form($form, 'html_form');

        return $form_output;
    }

    function content_form_field_editor($element = array(), $content_type_values = array(), $action = '')
    {
        global $cck, $settings;
        $output = '';


        //exit($cck->_debug($content_type_values) . 'elements ========' .$cck->_debug($element));
        $content_type_info = $cck->_model('content', 'content_type_get', $content_type_values['content_type_id']);
        $content_field_types = $cck->_model('content', 'content_get_field_types');

        $form = array();
        $form['name'] = 'content_type_' . $content_type_values['content_type_id'] . '_field_' . $content_type_values['field_id'] . '_edit';
        $form['id'] = 'content_type_' . $content_type_values['content_type_id'] . '_field_' . $content_type_values['field_id'] . '_edit';
        $form['method'] = 'POST';
        $form['action'] = $cck->_url('admin/' . $this->module . '/content_type_field_edit_submit/');
        $form['title'] = 'create a field';
        $form['enctype'] = '';
        $form['before'] = '<h2 style="clear: both;">' . $element['type'] . '</h2>';

        $check_attributes = array('readonly','disabled','autofocus','autocomplete','checked','required','multiple');
        foreach ($element as $key => $attribute) {

            if ($attribute === 'false') {
                continue;
            }
            $element['label'] = $key;
            $element['value'] = $attribute;
            $element['name'] = $key;
            switch ($key) {
                case 'setdefault' :
                    $form['elements']['hidden-'.$key] =
                        array(
                            'type' => 'hidden',
                            'id' => 'hidden-' . $key,
                            'class' => 'hidden-' . $key,
                            'name' => 'chk-' . $key,
                            'value' => 'off',
                        );
                    $form['elements']['visible-'.$key] =
                        array(
                            'type' => 'checkbox',
                            'id' => 'chk-' . $key,
                            'class' => 'chk-' . $key,
                            'title' => $key,
                            'name' => 'chk-' . $key,
                            'label' => 'set as default',
                            'value' => 'on',
                            'checked' =>($content_type_values[$key] == 'on' ? $content_type_values[$key] : ''),
                            'description' => 'fill in the field with these values when element is presented to user'
                        );
                    break;
                case 'checked' :
                    // this default off hidden is overwritten if the checkbox is set. If not set then a default value is set via this element
                    $form['elements']['hidden-'.$key] =
                        array(
                            'type' => 'hidden',
                            'id' => 'hidden-' . $key,
                            'class' => 'hidden-' . $key,
                            'name' => 'chk-' . $key,
                            'value' => 'off',
                        );
                    $form['elements']['visible-'.$key] =
                        array(
                            'type' => 'checkbox',
                            'id' => 'chk-' . $key,
                            'class' => 'chk-' . $key,
                            'title' => $key,
                            'name' => 'chk-' . $key,
                            'label' => $cck->_plain_text($key),
                            'value' => 'on',
                            'checked' => $content_type_values[$key],
                            'description' => 'mark as selected from previous submission or required'
                        );
                    break;
                case 'html' :
                    // this default off hidden is overwritten if the checkbox is set. If not set then a default value is set via this element
                    $form['elements']['hidden-'.$key] =
                        array(
                            'type' => 'hidden',
                            'id' => 'hidden-' . $key,
                            'class' => 'hidden-' . $key,
                            'name' => 'chk-' . $key,
                            'value' => 'off',
                        );
                    $form['elements']['visible-'.$key] =
                        array(
                            'type' => 'checkbox',
                            'id' => 'chk-' . $key,
                            'class' => 'chk-' . $key,
                            'title' => $key,
                            'name' => 'chk-' . $key,
                            'label' => $cck->_plain_text($key),
                            'value' => 'on',
                            'checked' => $content_type_values[$key],
                            'description' => 'show HTML5 mark-up editor'
                        );
                    break;
                case 'wrap' :
                    $form['elements']['hidden-'.$key] =
                        array(
                            'type' => 'hidden',
                            'id' => 'hidden-' . $key,
                            'class' => 'hidden-' . $key,
                            'name' => 'chk-' . $key,
                            'value' => 'off',
                        );
                    $form['elements']['visible-'.$key] =

                        array(
                            'type' => 'checkbox',
                            'id' => 'chk-' . $key,
                            'class' => 'chk-' . $key,
                            'title' => $key,
                            'name' => 'chk-' . $key,
                            'label' => 'hard wrap text',
                            'value' => 'on',
                            'placeholder' => '',
                            'description' => 'hard wrap field text requires setting cols attribute. default is soft wrap'
                        );
                    break;
                case 'required' :
                    // this default off hidden is overwritten if the checkbox is set. If not set then a default value is set via this element
                    $form['elements']['hidden-'.$key] =
                        array(
                            'type' => 'hidden',
                            'id' => 'hidden-' . $key,
                            'class' => 'hidden-' . $key,
                            'name' => 'chk-' . $key,
                            'value' => 'off',
                        );
                    $form['elements']['visible-'.$key] =
                        array(
                            'type' => 'checkbox',
                            'id' => 'chk-' . $key,
                            'class' => 'chk-' . $key,
                            'title' => $key,
                            'name' => 'chk-' . $key,
                            'label' => $cck->_plain_text($key),
                            'value' => 'on',
                            'checked' =>($content_type_values[$key] == 'on' ? $content_type_values[$key] : ''),
                            'description' => 'a browser generated message will appear for empty field'
                        );
                    break;
                case 'multiple' :
                    // this default off hidden is overwritten if the checkbox is set. If not set then a default value is set via this element
                    $form['elements']['hidden-'.$key] =
                        array(
                            'type' => 'hidden',
                            'id' => 'hidden-' . $key,
                            'class' => 'hidden-' . $key,
                            'name' => 'chk-' . $key,
                            'value' => 'off',
                        );
                    $form['elements']['visible-'.$key] =
                        array(
                            'type' => 'checkbox',
                            'id' => 'chk-' . $key,
                            'class' => 'chk-' . $key,
                            'title' => $key,
                            'name' => 'chk-' . $key,
                            'label' => $cck->_plain_text($key),
                            'value' => 'on',
                            'checked' =>($content_type_values[$key] == 'on' ? $content_type_values[$key] : ''),
                            'description' => 'a user may make several selections from list'
                        );
                    break;
                case 'autofocus' :
                    // this default off hidden is overwritten if the checkbox is set. If not set then a default value is set via this element
                    $form['elements']['hidden-'.$key] =
                        array(
                            'type' => 'hidden',
                            'id' => 'hidden-' . $key,
                            'class' => 'hidden-' . $key,
                            'name' => 'chk-' . $key,
                            'value' => 'off',
                        );
                    $form['elements']['visible-'.$key] =
                        array(
                            'type' => 'checkbox',
                            'id' => 'chk-' . $key,
                            'class' => 'chk-' . $key,
                            'title' => $key,
                            'name' => 'chk-' . $key,
                            'label' => $cck->_plain_text($key),
                            'value' => 'on',
                            'checked' =>($content_type_values[$key] == 'on' ? $content_type_values[$key] : ''),
                            'description' => 'field should automatically get focus when the page loads'
                        );
                    break;
                case 'autocomplete' :
                    // this default off hidden is overwritten if the checkbox is set. If not set then a default value is set via this element
                    $form['elements']['hidden-'.$key] =
                        array(
                            'type' => 'hidden',
                            'id' => 'hidden-' . $key,
                            'class' => 'hidden-' . $key,
                            'name' => 'chk-' . $key,
                            'value' => 'off',
                        );
                    $form['elements']['visible-'.$key] =
                        array(
                            'type' => 'checkbox',
                            'id' => 'chk-' . $key,
                            'class' => 'chk-' . $key,
                            'title' => $key,
                            'name' => 'chk-' . $key,
                            'label' => $cck->_plain_text($key),
                            'value' => 'on',
                            'checked' =>($content_type_values[$key] == 'on' ? $content_type_values[$key] : ''),
                            'description' => 'use the browser to suggest previous choices made by user'
                        );
                    break;
                case 'disabled' :
                    // this default off hidden is overwritten if the checkbox is set. If not set then a default value is set via this element
                    $form['elements']['hidden-'.$key] =
                        array(
                            'type' => 'hidden',
                            'id' => 'hidden-' . $key,
                            'class' => 'hidden-' . $key,
                            'name' => 'chk-' . $key,
                            'value' => 'off',
                        );
                    $form['elements']['visible-'.$key] =
                        array(
                            'type' => 'checkbox',
                            'id' => 'chk-' . $key,
                            'class' => 'chk-' . $key,
                            'title' => $key,
                            'name' => 'chk-' . $key,
                            'label' => $cck->_plain_text($key),
                            'value' => 'on',
                            'checked' =>($content_type_values[$key] == 'on' ? $content_type_values[$key] : ''),
                            'description' => 'information in a disabled field is not submitted'
                        );
                    break;
                case 'readonly' :
                    // this default off hidden is overwritten if the checkbox is set. If not set then a default value is set via this element
                    $form['elements']['hidden-'.$key] =
                        array(
                            'type' => 'hidden',
                            'id' => 'hidden-' . $key,
                            'class' => 'hidden-' . $key,
                            'name' => 'chk-' . $key,
                            'value' => 'off',
                        );
                    $form['elements']['visible-'.$key] =
                        array(
                            'type' => 'checkbox',
                            'id' => 'chk-' . $key,
                            'class' => 'chk-' . $key,
                            'title' => $key,
                            'name' => 'chk-' . $key,
                            'label' => $cck->_plain_text($key),
                            'value' => 'on',
                            'checked' =>($content_type_values[$key] == 'on' ? $content_type_values[$key] : ''),
                            'description' => 'field information is submitted but cannot be changed by user'
                        );
                    break;
                case 'options' :
                    $form['elements'][$key] =
                        array(
                            'type' => 'textarea',
                            'id' => $key,
                            'class' => $key,
                            'title' => $key,
                            'name' => $key,
                            'label' => $cck->_plain_text($key),
                            'value' => $content_type_values[$key],
                            'description' => 'each option is formatted [value] | [description] seperate options with newline group with {[group]:[value] | [description],[value] | [description]}',
                            'placeholder' => '{[group]:[value] | [description],[value] | [description]}' . "\n" . '[value] | [description]',
                        );
                    break;

                case 'html_before' :
                case 'html_after' :
                    $form['elements'][$key] =
                        array(
                            'type' => 'textarea',
                            'id' => $key,
                            'class' => $key,
                            'title' => $key,
                            'name' => $key,
                            'label' => $cck->_plain_text($key),
                            'value' => $content_type_values[$key],
                            'description' => ' add html tags before or after rendered element',
                            'placeholder' => '',
                        );
                    break;
                case 'type':
                case 'field_type_id':
                case 'field_id':
                case 'content_type_id':
                case 'existing_field_name':


                    $form['elements'][$key] =
                        array(
                            'type' => 'hidden',
                            'id' => $key,
                            'class' => $key,
                            'name' => $key,
                            'value' => $attribute,
                        );
                    break;
                case 'name':
                case 'label':

                    $form['elements'][$key] =
                        array(
                            'type' => 'text',
                            'id' => $key,
                            'class' => $key,
                            'title' => $key,
                            'name' => $key,
                            'label' => $cck->_plain_text($key),
                            'value' => $content_type_values[$key],
                            'placeholder' => $key,
                        );
                    break;
                case 'support':
                    $form['elements'][$key] =
                        array(
                            'type' => 'text',
                            'id' => $key,
                            'class' => $key,
                            'title' => $key,
                            'name' => $key,
                            'label' => $cck->_plain_text($key),
                            'value' => $attribute,
                            'readonly' => '',
                            'description' => 'form element support in browsers ',
                        );
                    break;
                case 'limit':
                    $form['elements'][$key] =
                        array(
                            'type' => 'text',
                            'id' => $key,
                            'class' => $key,
                            'title' => $key,
                            'name' => $key,
                            'label' => $cck->_plain_text($key),
                            'value' => $content_type_values[$key],
                            'description' => 'number of user entries or file uploads limit, 0 is unlimited',
                        );
                    break;
                case 'form':
                    $form['elements'][$key] =
                        array(
                            'type' => 'text',
                            'id' => $key,
                            'class' => $key,
                            'title' => $key,
                            'name' => $key,
                            'label' => $cck->_plain_text($key),
                            'value' => 'add_' . $content_type_info['label'] . '_content',
                            'readonly' => '',
                            'description' => 'the name of the form containing the field'
                        );
                    break;
                case 'defvalue':
                    switch ($element['type']) {
                        case 'radio';
                            $form['elements'][$key] =
                                array(
                                    'type' => 'text',
                                    'id' => $key,
                                    'class' => $key,
                                    'title' => $key,
                                    'name' => $key,
                                    'label' => 'value',
                                    'value' => $content_type_values[$key],
                                    'description' => 'the first option is formatted [value] | [description] add more to options field',
                                    'placeholder' => '[value] | [description]',
                                );
                            break;
                        case 'select';
                            $form['elements'][$key] =
                                array(
                                    'type' => 'text',
                                    'id' => $key,
                                    'class' => $key,
                                    'title' => $key,
                                    'name' => $key,
                                    'label' => $cck->_plain_text('selected'),
                                    'value' => $content_type_values[$key],
                                    'description' => 'the selected option is formatted [value] | [description]',
                                    'placeholder' => '[value] | [description]',
                                );
                            break;
                        default:
                            $form['elements'][$key] =
                                array(
                                    'type' => 'text',
                                    'id' => $key,
                                    'class' => $key,
                                    'title' => $key,
                                    'name' => $key,
                                    'label' => 'value',
                                    'value' => $content_type_values[$key],
                                    'placeholder' => 'default values',
                                );
                            break;

                    }

                    break;
                case 'maxlength':

                    $description = '';
                    $placeholder = '';
                    $label = $key;

                    switch ($element['type']) {
                        case 'select':
                            $description = 'maximum number of options user may choose from list';
                            $label = 'number of options';
                            break;

                    }

                    $form['elements'][$key] =
                        array(
                            'type' => 'text',
                            'id' => $key,
                            'class' => $key,
                            'title' => $key,
                            'name' => $key,
                            'label' => $cck->_plain_text($label),
                            'value' => $content_type_values[$key],
                            'placeholder' => $placeholder,
                            'description' => $description
                        );
                    break;
                default:

                    $description = '';
                    $placeholder = '';

                    switch ($key) {


                        case 'description':
                            $description = 'write some help text for the user';
                            break;
                        case 'id':
                            $description = 'css id selector';
                            $placeholder = '#id';
                            break;
                        case 'class':
                            $description = 'css class selector';
                            $placeholder = '.class';
                            break;
                    }
                    $form['elements'][$key] =
                        array(
                            'type' => 'text',
                            'id' => $key,
                            'class' => $key,
                            'title' => $key,
                            'name' => $key,
                            'label' => $cck->_plain_text($key),
                            'value' => $content_type_values[$key],
                            'placeholder' => $placeholder,
                            'description' => $description
                        );

                    break;
            }


        }
        $form['elements']['send'] =
            array(
                'type' => 'submit',
                'id' => 'save',
                'class' => 'save',
                'title' => 'save',
                'name' => 'save',
                'label' => 'save',
                'value' => 'save',
                'before' => '<div></div>',
            );
        $form['elements']['copy'] =
            array(
                'type' => 'submit',
                'id' => 'copy',
                'class' => 'copy',
                'title' => 'copy',
                'name' => 'copy',
                'value' => 'copy',
                'formaction' => '?content/content_type_field_copy',

            );
        // $form_output = '<h2>' . $element['type'] . '</h2>';
        $form_output = $cck->_form($form, 'html_form');

        return $form_output;
    }

    function content_form_quick_field_add_confirm()
    {
         global $cck;

         $caller = $cck->_get_calling_method();
         $action = $cck->_set_action($caller);
         $args = $cck->_args();

         $form = array();
         $form['name'] = 'content_type_field_add_confirm';
         $form['id'] = 'content_type_field_add_confirm';
         $form['method'] = 'POST';
         $form['action'] = '?' . '/send/';
         $form['title'] = 'create a field';
         $form['enctype'] = 'text/plain';
         $form['before'] = '<h2 style="clear: both;">' .'Confirm'. '</h2>';

         $form['elements']['deny'] =
             array(
                 'type' => 'submit',
                 'id' => 'deny',
                 'class' => 'deny',
                 'title' => 'deny',
                 'name' => 'deny',
                 'label' => 'deny',
                 'value' => 'Deny',
                 'before' => '<div></div>',
                 'formaction' => $_SERVER['HTTP_REFERER'],
             );

         $form['elements']['confirm'] =
             array(
                 'type' => 'submit',
                 'id' => 'confirm',
                 'class' => 'confirm',
                 'title' => 'confirm',
                 'name' => 'confirm',
                 'label' => 'send',
                 'value' => 'Confirm',
                 'formaction' => '?admin/content/'. $action,
             );
         // $form_output = '<h2>' . $element['type'] . '</h2>';
         $form_output = $cck->_form($form, 'html_form');

         return $form_output;

    }

    function content_form_confirm($confirm = array(), $message = NULL)
    {
        global $cck;

        $caller = $cck->_get_calling_method();
        $action = $cck->_set_action($caller);
        $args = $cck->_args();

        $form = array();
        $form['name'] = 'content_confirm';
        $form['id'] = 'content_confirm';
        $form['method'] = 'POST';
        $form['action'] = '?' . '/send/';
        $form['title'] = 'create a field';
        $form['enctype'] = '';
        $form['before'] = '<h2 style="clear: both;">' .'Confirm'. '</h2>';

        $form['elements']['message'] =
            array(
                'type' => 'html',
                'value' => '<div>'. $message . '</div>',
            );
        $form['elements']['posted'] =
            array(
                'type' => 'hidden',
                'id' => 'deny',
                'class' => 'deny',
                'title' => 'deny',
                'name' => 'posted',
                'label' => 'deny',
                'value' => json_encode($confirm),
                'json' => ''
            );

        $form['elements']['deny'] =
            array(
                'type' => 'submit',
                'id' => 'deny',
                'class' => 'deny',
                'title' => 'deny',
                'name' => 'deny',
                'label' => 'deny',
                'value' => 'Deny',
                'before' => '<div></div>',
                'formaction' => $_SERVER['HTTP_REFERER'],
            );

        $form['elements']['confirm'] =
            array(
                'type' => 'submit',
                'id' => 'confirm',
                'class' => 'confirm',
                'title' => 'confirm',
                'name' => 'verify',
                'label' => 'send',
                'value' => 'confirm',
                'formaction' => $_SERVER['REQUEST_URI'],
            );
        // $form_output = '<h2>' . $element['type'] . '</h2>';
        $output = $cck->_form($form, 'html_form');


        return  $output;


    }
}

?>
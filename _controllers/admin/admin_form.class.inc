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

// Define a class
namespace admin;

use \PDO;
use \PDOException;

class admin_form {

    public  $section;
    public  $module;
  
    function __construct()
    {
        $this->section = __CLASS__;
        $this->module = __NAMESPACE__;
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

      foreach($list as $key => $line)
      {

              if(isset($data['field_type_id']) && $data['field_type_id'] == $line['field_type_id'])
              {
                  $options[] =   array(
                      'type' => 'option',
                      'id'=> $line['type'].'-' . $line['field_type_id'],
                      'class'=> $line['type'].'-' . $line['field_type_id'],
                      'value'=> $line['field_type_id'],
                      'description' => $line['type'],
                      'selected' => '');
              }
              else
              {
                  $options[] =  array(
                      'type' => 'option',
                      'id'=> $line['type'].'-' . $line['field_type_id'],
                      'class'=> $line['type'].'-' . $line['field_type_id'],
                      'value'=> $line['field_type_id'],
                      'description' => $line['type']);
              }
          if($line['type'] != '')
          {
              $link['path'] = 'admin/'. $this->module . '/content_type_field_add/'. $args[0].'/'. $line['field_type_id'];
              $link['text'] = $line['type'];
              $types[$line['type']] = $cck->_link('links', $link);
          }

      }




      $form = array();
      $form['name'] = 'content_type_field_add';
      $form['id'] = 'content_type_add';
      $form['method'] = 'POST';
      $form['action'] = $cck->_url('admin/'. $this->module.'/content_type_field_add_submit');
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
              'id'=> 'field_types',
              'class'=> 'field_types',
              'name'=> 'Types',
              'form'=> $form['name'],
              'options'=> $options,
          );

      $form['elements']['content_field_label'] =
          array(
              'type' => 'text',
              'id'=> 'content_field_label',
              'class'=> 'content_field_label',
              'title'=> 'content_field_label',
              'label'=> 'Label',
              'name'=> 'content_field_label',
              'value'=> (isset($data['label']) ? ''. $data['label'] . '': ''),
              'placeholder'=> 'label',
          );
      $form['elements']['content_field_name'] =
          array(
              'type' => 'text',
              'id'=> 'content_field_name',
              'class'=> 'content_field_name',
              'title'=> 'content_field_name',
              'name'=> 'content_field_name',
              'label'=> 'Name',
              'value'=> (isset($data['name']) ? ''. $data['name'] . '': ''),
              'placeholder'=> 'field name',
          );
      $form['elements']['content_field_id'] =
          array(
              'type' => 'text',
              'id'=> 'content_field_id',
              'class'=> 'content_field_id',
              'title'=> 'content_field_id',
              'name'=> 'content_field_id',
              'label'=> 'CSS ID',
              'value'=> '',
              'placeholder'=> 'style sheet id',
          );
      $form['elements']['content_field_class'] =
          array(
              'type' => 'text',
              'id'=> 'content_field_class',
              'class'=> 'content_field_class',
              'title'=> 'content_field_class',
              'name'=> 'content_field_class',
              'label'=> 'CSS Class',
              'value'=> '',
              'placeholder'=> 'style sheet class',
          );

      $form['elements']['content_field_autocomplete'] =
          array(
              'type' => 'checkbox',
              'id'=> 'content_field_autocomplete',
              'class'=> 'content_field_autocomplete',
              'title'=> 'content_field_autocomplete',
              'name'=> 'content_field_autocomplete',
              'label'=> 'Autocomplete',
              'description' => 'will show users previous choice for field',
              'checked' => (isset($data['checked']) ? $data['checked'] : ''),
              'value'=> '',
              'placeholder'=> '',

          );
      $form['elements']['content_field_disabled'] =
          array(
              'type' => 'checkbox',
              'id'=> 'content_field_disabled',
              'class'=> 'content_field_disabled',
              'title'=> 'content_field_disabled',
              'name'=> 'content_field_disabled',
              'label'=> 'Disabled',
              'description' => 'disabled fields send no data',
              'checked' => (isset($data['checked']) ? $data['checked'] : ''),
              'value'=> '',
              'placeholder'=> '',

          );
      $form['elements']['content_field_readonly'] =
          array(
              'type' => 'checkbox',
              'id'=> 'content_field_readonly',
              'class'=> 'content_field_readonly',
              'title'=> 'content_field_readonly',
              'name'=> 'content_field_readonly',
              'label'=> 'Read only',
              'description' => 'user cannot edit data sent',
              'checked' => (isset($data['checked']) ? $data['checked'] : ''),
              'value'=> '',
              'placeholder'=> '',

          );
      $form['elements']['content_field_required'] =
          array(
              'type' => 'checkbox',
              'id'=> 'content_field_required',
              'class'=> 'content_field_required',
              'title'=> 'content_field_required',
              'name'=> 'content_field_required',
              'label'=> 'Required',
              'description' => 'required fields are input validated',
              'checked' => (isset($data['checked']) ? $data['checked'] : ''),
              'value'=> '1',
              'placeholder'=> '',
          );

      $templates = array(
            'options' =>
                array(
                    'type' => 'option',
                    'id'=> 'default-template',
                    'class'=> 'default-template',
                    'value'=> 'default',
                    'description' => 'default')
      );
      $form['elements']['templates'] =
          array(
              'type' => 'select',
              'id'=> 'template',
              'class'=> 'template',
              'title'=> 'Template',
              'name'=> 'template',
              'label'=> 'template',
              'options' => $templates,
          );

      $form['elements']['save'] =
          array(
              'type' => 'submit',
              'id'=> 'save-field',
              'class'=> 'save-field',
              'title'=> 'save field',
              'name'=> 'save_field',
              'label'=> 'save',
              'value'=> 'save',
              'before'=> '<div></div>',
          );

      $variables['content'] = $cck->_form($form,'html_form');
      $variables['root'] = 'Types';
      $variables['levels'] = $types;
      $output =  $cck->_view('links_drop_menu', $variables);

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

        foreach($list as $key => $line)
        {

            if(isset($data['field_type_id']) && $data['field_type_id'] == $line['field_type_id'])
            {
                $options[] =   array(
                    'type' => 'option',
                    'id'=> $line['type'].'-' . $line['field_type_id'],
                    'class'=> $line['type'].'-' . $line['field_type_id'],
                    'value'=> $line['field_type_id'],
                    'description' => $line['type'],
                    'selected' => '');
            }
            else
            {
                $options[] =  array(
                    'type' => 'option',
                    'id'=> $line['type'].'-' . $line['field_type_id'],
                    'class'=> $line['type'].'-' . $line['field_type_id'],
                    'value'=> $line['field_type_id'],
                    'description' => $line['type']);
            }
            if($line['type'] != '')
            {
                $link['path'] = 'admin/'. $this->module . '/content_type_field_add/'. $args[0].'/'. $line['field_type_id'];
                $link['text'] = $line['type'];
                $types[$line['type']] = $cck->_link('links', $link);
            }

        }




        $form = array();
        $form['name'] = 'content_type_field_edit';
        $form['id'] = 'content_type_edit';
        $form['method'] = 'POST';
        $form['action'] = $cck->_url('admin/'. $this->module.'/content_type_field_edit_submit/');
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
                'id'=> 'field_types',
                'class'=> 'field_types',
                'name'=> 'Types',
                'form'=> $form['name'],
                'options'=> $options,
            );

        $form['elements']['content_field_label'] =
            array(
                'type' => 'text',
                'id'=> 'content_field_label',
                'class'=> 'content_field_label',
                'title'=> 'content_field_label',
                'label'=> 'Label',
                'name'=> 'content_field_label',
                'value'=> (isset($data['label']) ? ''. $data['label'] . '': ''),
                'placeholder'=> 'label',
            );
        $form['elements']['content_field_name'] =
            array(
                'type' => 'text',
                'id'=> 'content_field_name',
                'class'=> 'content_field_name',
                'title'=> 'content_field_name',
                'name'=> 'content_field_name',
                'label'=> 'Name',
                'value'=> (isset($data['name']) ? ''. $data['name'] . '': ''),
                'placeholder'=> 'field name',
            );
        $form['elements']['content_field_id'] =
            array(
                'type' => 'text',
                'id'=> 'content_field_id',
                'class'=> 'content_field_id',
                'title'=> 'content_field_id',
                'name'=> 'content_field_id',
                'label'=> 'CSS ID',
                'value'=> '',
                'placeholder'=> 'style sheet id',
            );
        $form['elements']['content_field_class'] =
            array(
                'type' => 'text',
                'id'=> 'content_field_class',
                'class'=> 'content_field_class',
                'title'=> 'content_field_class',
                'name'=> 'content_field_class',
                'label'=> 'CSS Class',
                'value'=> '',
                'placeholder'=> 'style sheet class',
            );

        $form['elements']['content_field_autocomplete'] =
            array(
                'type' => 'checkbox',
                'id'=> 'content_field_autocomplete',
                'class'=> 'content_field_autocomplete',
                'title'=> 'content_field_autocomplete',
                'name'=> 'content_field_autocomplete',
                'label'=> 'Autocomplete',
                'description' => 'will show users previous choice for field',
                'checked' => (isset($data['checked']) ? $data['checked'] : ''),
                'value'=> '',
                'placeholder'=> '',

            );
        $form['elements']['content_field_disabled'] =
            array(
                'type' => 'checkbox',
                'id'=> 'content_field_disabled',
                'class'=> 'content_field_disabled',
                'title'=> 'content_field_disabled',
                'name'=> 'content_field_disabled',
                'label'=> 'Disabled',
                'description' => 'disabled fields send no data',
                'checked' => (isset($data['checked']) ? $data['checked'] : ''),
                'value'=> '',
                'placeholder'=> '',

            );
        $form['elements']['content_field_readonly'] =
            array(
                'type' => 'checkbox',
                'id'=> 'content_field_readonly',
                'class'=> 'content_field_readonly',
                'title'=> 'content_field_readonly',
                'name'=> 'content_field_readonly',
                'label'=> 'Read only',
                'description' => 'user cannot edit data sent',
                'checked' => (isset($data['checked']) ? $data['checked'] : ''),
                'value'=> '',
                'placeholder'=> '',

            );
        $form['elements']['content_field_required'] =
            array(
                'type' => 'checkbox',
                'id'=> 'content_field_required',
                'class'=> 'content_field_required',
                'title'=> 'content_field_required',
                'name'=> 'content_field_required',
                'label'=> 'Required',
                'description' => 'required fields are input validated',
                'checked' => (isset($data['checked']) ? $data['checked'] : ''),
                'value'=> '1',
                'placeholder'=> '',
            );

        $templates = array(
            'options' =>
                array(
                    'type' => 'option',
                    'id'=> 'default-template',
                    'class'=> 'default-template',
                    'value'=> 'default',
                    'description' => 'default')
        );
        $form['elements']['templates'] =
            array(
                'type' => 'select',
                'id'=> 'template',
                'class'=> 'template',
                'title'=> 'Template',
                'name'=> 'template',
                'label'=> 'template',
                'options' => $templates,
            );

        $form['elements']['save'] =
            array(
                'type' => 'submit',
                'id'=> 'save-field',
                'class'=> 'save-field',
                'title'=> 'save field',
                'name'=> 'save_field',
                'label'=> 'save',
                'value'=> 'save',
                'before'=> '<div></div>',
            );

        $variables['content'] = $cck->_form($form,'html_form');
        $variables['root'] = 'Types';
        $variables['levels'] = $types;
        $output =  $cck->_view('links_drop_menu', $variables);

        //$output .= $cck->_debug($data);

        return $output;
    }

    function content_form_content_type($data=NULL)
    {
        global $cck, $settings;
        $args = $cck->_args();
        $action = '';

        switch(true)
        {
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
        $form['action'] = $cck->_url('admin/'. $this->module .'/content_type_submit/'. $action);
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
                'value' => (isset($data['type']) ? $data['type'] : '' ),
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
                'value' => (isset($data['label']) ? $data['label'] : '' ),
                'placeholder'=> 'type label'
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
                'value' => (isset($data['description']) ? $data['description'] : '' ),
                'placeholder'=> 'type description'
            );


        $form['elements']['submit'] =
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

        return $cck->_form($form,'html_form');

    }

    function content_form_add_type($data=NULL)
    {
        //
        global $cck, $settings;

        $args = $cck->_args();

        $connect = $cck->_dbconnect('datasource_default');

        // table rows and field values
        if(isset($args[0]))
        {
            $get_types = $connect->prepare("SELECT type, label, description FROM content_types WHERE type_id='" . $args[0]. "'");

        }
        else
        {
            $get_types = $connect->prepare("SELECT type, label, description FROM content_types");

        }

        $get_types->execute();


        $columns = $get_types->fetchAll();

        // table header
        foreach ($columns[0] as $key => $value)
        {
            if(!is_numeric($key))
            {
                $elements[] = $key;
            }
        }

        $form = array();
        $form['name'] = 'content_type_add';
        $form['id'] = 'content_type_add';
        $form['method'] = 'POST';
        $form['action'] = $cck->_url($this->section .'/content_type_submit/');
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
                'placeholder'=> 'type name'
            );

        foreach($elements as $key => $value)
        {

            switch($value)
            {

                case 'type':

                    $disabled = FALSE;

                    foreach($columns as $a => $type)
                    {
                        if(isset($args[0]) && $args[0] == $type['type'])
                        {
                            $list[] = array(
                                'type' => 'option',
                                'id'=> 'type_'. $a,
                                'class'=> 'type_'. $a,
                                'value'=> $type['type'],
                                'description'=> $type['label'],
                                'selected' => 'selected',
                            );

                        }
                        else
                        {
                            $list[] = array(
                                'type' => 'option',
                                'id'=> 'type_'. $a,
                                'class'=> 'type_'. $a,
                                'value'=> $type['type'],
                                'description'=> $type['label'],
                            );
                        }

                    }
                    $form['elements']['existing_types'] =
                        array(
                            'type' => 'select',
                            'label' => 'existing types',
                            'id'=> 'mytype',
                            'class'=> 'mytype',
                            'name' => 'nametype',
                            'form'=> 'content_type_add',
                            'options'=> $list,
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
                            'placeholder'=> ''
                        );
                    break;
            }

        }

        $form['elements']['send'] =
            array(
                'type' => 'submit',
                'id'=> 'send',
                'class'=> 'send',
                'title'=> 'send',
                'name'=> 'send',
                'label'=> 'send',
                'value'=> 'save',
                'before'=> '<div></div>',
            );

        return $cck->_form($form,'html_form');
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

        foreach($list as $key => $line)
        {

            if($quick_edit == TRUE)
            {
                $link['path'] = 'admin/'. $this->module . '/content_type_quick_field_add/'. $args[0].'/'. $line['field_type_id'];
                $variables['content'] = 'Add a new field without configuration dialog';
            }
            else
            {
                $link['path'] = 'admin/'. $this->module . '/content_type_field_add/'. $args[0].'/'. $line['field_type_id'];
                $variables['content'] = 'Click the add button and select then configure new fields for this content type';
            }
            if($line['type'] != '')
            {

                $link['text'] = $line['type'];
                $types[$line['type']] = $cck->_link('links', $link);
            }

        }

        $variables['root'] = 'Types';
        $variables['levels'] = $types;
        $output =  $cck->_view('links_drop_menu', $variables);

        return $output;

    }

    function admin_form_site_settings($listed=array(),$title = NULL)
    {
        global $cck, $settings;
        $output = '';


        $form = array();
        $form['name'] = 'site_settings';
        $form['id'] = 'site_settings';
        $form['method'] = 'POST';
        $form['action'] = $cck->_url( 'admin/'. $this->module . '/site_settings_save');
        $form['title'] = 'create a field';
        $form['enctype'] = '';
        $form['before']= '<h2 style="clear: both;">'. $title .'</h2>';

            foreach($listed as $key => $element)
            {

                foreach($element as $attribute => $value)
                {
                    $form['elements'][$attribute] =
                        array(
                            'type' => 'text',
                            'id' => 'setting-' . $attribute,
                            'class' => 'setting-' . $attribute,
                            'title' => $attribute,
                            'name' => 'setting[' .$key . '][' . $attribute . '][' . 'value' . ']' ,
                            'label' => $cck->_plain_text($attribute),
                            'value' => $value['value'],
                            'placeholder' => '',
                            'description' => $value['description']
                        );
                }
            }
            $form['elements']['save'] =
                array(
                    'type' => 'submit',
                    'id' => 'settings-save',
                    'class' => 'settings-save',
                    'title' => 'Save settings',
                    'name' => 'settings-save' ,
                    'label' => $cck->_plain_text($attribute,'_'),
                    'value' => 'save',
                    'description' => ''
                );


        $form_output = $cck->_form($form,'html_form');

        return $form_output;
    }

    function admin_form_view_settings($listed=array(),$title = NULL)
    {
        global $cck, $settings;
        $output = '';


        $form = array();
        $form['name'] = $title .'_settings';
        $form['id'] = $title . '_settings';
        $form['method'] = 'POST';
        $form['action'] = $cck->_url( 'admin/'. $this->module . '/site_settings_save');
        $form['title'] = 'create a field';
        $form['enctype'] = '';
        $form['before']= '<h2 style="clear: both;">'. $title .'</h2>';

        foreach($listed as $key => $element)
        {

            foreach($element as $attribute => $value)
            {
                $form['elements'][$attribute] =
                    array(
                        'type' => 'text',
                        'id' => 'setting-' . $attribute,
                        'class' => 'setting-' . $attribute,
                        'title' => $attribute,
                        'name' => 'setting[' .$key . '][' . $attribute . '][' . 'value' . ']' ,
                        'label' => $cck->_plain_text($attribute,'_'),
                        'value' => $value['value'],
                        'disabled' => '',
                        'description' => $value['description']
                    );
            }
        }
        /*
         *
         $form['elements']['save'] =
            array(
                'type' => 'submit',
                'id' => 'settings-save',
                'class' => 'settings-save',
                'title' => 'Save settings',
                'name' => 'settings-save' ,
                'label' => $cck->_plain_text($attribute),
                'value' => 'save',
                'description' => ''
            );
        */

        $form_output = $cck->_form($form,'html_form');

        return $form_output;
    }

    function content_form_field_editor($element=array(),$content_type_values = array(),$action = '')
    {
        global $cck, $settings;
        $output = '';


        //exit($cck->_debug($content_type_values) . 'elements ========' .$cck->_debug($element));
        $content_type_info = $cck->_model('content','content_type_get', $content_type_values['content_type_id']);
        $content_field_types = $cck->_model('content','content_get_field_types');

        $form = array();
        $form['name'] = 'content_type_'. $content_type_values['content_type_id'] .'_field_'.$content_type_values['field_id'].'edit';
        $form['id'] = 'content_type_'. $content_type_values['content_type_id'] .'_field_'.$content_type_values['field_id'].'edit';
        $form['method'] = 'POST';
        $form['action'] = '?'.$action.'/send/';
        $form['title'] = 'create a field';
        $form['enctype'] = 'text/plain';
        $form['before']= '<h2 style="clear: both;">' . $element['type'] .'</h2>';


        foreach($element as $key => $attribute)
        {

            if($attribute === 'false')
            {
                continue;
            }
            $element['label'] = $key;
            $element['value'] = $attribute;
            $element['name'] = $key;
            switch($key)
            {
                case 'default' :
                    $form['elements'][$key] =
                        array(
                            'type' => 'checkbox',
                            'id'=> 'chk-'.$key,
                            'class'=> 'chk-'.$key,
                            'title'=> $key,
                            'name'=> 'chk-'.$key,
                            'label'=> 'set as '. $cck->_plain_text($key),
                            'value'=> $content_type_values[$key],
                            'placeholder'=> '',
                            'description' => 'fill in the field with these values when element is presented to user'
                        );
                    break;
                case 'checked' :
                    $form['elements'][$key] =
                        array(
                            'type' => 'checkbox',
                            'id'=> 'chk-'.$key,
                            'class'=> 'chk-'.$key,
                            'title'=> $key,
                            'name'=> 'chk-'.$key,
                            'label'=> $cck->_plain_text($key),
                            'value'=> $content_type_values[$key],
                            'placeholder'=> '',
                            'description' => 'mark as selected from previous submission or required'
                        );
                    break;

                case 'required' :
                    $form['elements'][$key] =
                        array(
                            'type' => 'checkbox',
                            'id'=> 'chk-'.$key,
                            'class'=> 'chk-'.$key,
                            'title'=> $key,
                            'name'=> 'chk-'.$key,
                            'label'=> $cck->_plain_text($key),
                            'value'=> $content_type_values[$key],
                            'placeholder'=> '',
                            'description' => 'a browser generated message will appear for empty field'
                        );
                    break;
                case 'multiple' :
                    $form['elements'][$key] =
                        array(
                            'type' => 'checkbox',
                            'id'=> 'chk-'.$key,
                            'class'=> 'chk-'.$key,
                            'title'=> $key,
                            'name'=> 'chk-'.$key,
                            'label'=> $cck->_plain_text($key),
                            'value'=> $content_type_values[$key],
                            'placeholder'=> '',
                            'description' => 'a user may make several selections from list'
                        );
                    break;
                case 'autofocus' :
                    $form['elements'][$key] =
                        array(
                            'type' => 'checkbox',
                            'id'=> 'chk-'.$key,
                            'class'=> 'chk-'.$key,
                            'title'=> $key,
                            'name'=> 'chk-'.$key,
                            'label'=> $cck->_plain_text($key),
                            'value'=> $content_type_values[$key],
                            'placeholder'=> '',
                            'description' => 'field should automatically get focus when the page loads'
                        );
                    break;
                case 'autocomplete' :
                    $form['elements'][$key] =
                        array(
                            'type' => 'checkbox',
                            'id'=> 'chk-'.$key,
                            'class'=> 'chk-'.$key,
                            'title'=> $key,
                            'name'=> 'chk-'.$key,
                            'label'=> $cck->_plain_text($key),
                            'value'=> $content_type_values[$key],
                            'placeholder'=> '',
                            'description' => 'use the browser to suggest previous choices made by user'
                        );
                    break;
                case 'disabled' :
                    $form['elements'][$key] =
                        array(
                            'type' => 'checkbox',
                            'id'=> 'chk-'.$key,
                            'class'=> 'chk-'.$key,
                            'title'=> $key,
                            'name'=> 'chk-'.$key,
                            'label'=> $cck->_plain_text($key),
                            'value'=> $content_type_values[$key],
                            'placeholder'=> '',
                            'description' => 'information in a disabled field is not submitted'
                        );
                    break;
                case 'readonly' :
                    $form['elements'][$key] =
                        array(
                            'type' => 'checkbox',
                            'id'=> 'chk-'.$key,
                            'class'=> 'chk-'.$key,
                            'title'=> $key,
                            'name'=> 'chk-'.$key,
                            'label'=> $cck->_plain_text($key),
                            'value'=> $content_type_values[$key],
                            'placeholder'=> '',
                            'description' => 'field information is submitted but cannot be changed by user'
                        );
                    break;
                case 'options' :
                    $form['elements'][$key] =
                        array(
                            'type' => 'textarea',
                            'id'=> $key,
                            'class'=> $key,
                            'title'=> $key,
                            'name'=> $key,
                            'label'=> $cck->_plain_text($key),
                            'value'=> $content_type_values[$key],
                            'description' => 'each option is formatted [value] | [description] seperate options with newline group with {[group]:[value] | [description],[value] | [description]}',
                            'placeholder'=> '{[group]:[value] | [description],[value] | [description]}'."\n". '[value] | [description]',
                        );
                    break;

                case 'html' :
                case 'html_before' :
                case 'html_after' :
                    $form['elements'][$key] =
                        array(
                            'type' => 'textarea',
                            'id'=> $key,
                            'class'=> $key,
                            'title'=> $key,
                            'name'=> $key,
                            'label'=> $cck->_plain_text($key),
                            'value'=> $content_type_values[$key],
                            'placeholder'=> '',
                        );
                    break;
                case 'type':
                case 'field_type_id':

                    $form['elements'][$key] =
                        array(
                            'type' => 'hidden',
                            'id'=> $key,
                            'class'=> $key,
                            'name'=> $key,
                            'value'=> $attribute,
                        );
                    break;
                case 'name':
                case 'label':

                    $form['elements'][$key] =
                        array(
                            'type' => 'text',
                            'id'=> $key,
                            'class'=> $key,
                            'title'=> $key,
                            'name'=> $key,
                            'label'=> $cck->_plain_text($key),
                            'value'=> $content_type_values[$key],
                            'placeholder'=> $key,
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
                            'value' => 'add_'. $content_type_info['label'] . '_content',
                            'readonly' => '',
                            'description' => 'the name of the form containing the field'
                        );
                    break;
                case 'values':
                    switch($element['type'])
                    {
                        case 'radio';
                            $form['elements'][$key] =
                                array(
                                    'type' => 'text',
                                    'id'=> $key,
                                    'class'=> $key,
                                    'title'=> $key,
                                    'name'=> $key,
                                    'label'=> $cck->_plain_text($key),
                                    'value'=> $content_type_values[$key],
                                    'description' => 'the first option is formatted [value] | [description] add more to options field',
                                    'placeholder'=> '[value] | [description]',
                                );
                            break;
                        case 'select';
                            $form['elements'][$key] =
                                array(
                                    'type' => 'text',
                                    'id'=> $key,
                                    'class'=> $key,
                                    'title'=> $key,
                                    'name'=> $key,
                                    'label'=> $cck->_plain_text('selected'),
                                    'value'=> $content_type_values[$key],
                                    'description' => 'the selected option is formatted [value] | [description]',
                                    'placeholder'=> '[value] | [description]',
                                );
                            break;
                        default:
                            $form['elements'][$key] =
                                array(
                                    'type' => 'text',
                                    'id'=> $key,
                                    'class'=> $key,
                                    'title'=> $key,
                                    'name'=> $key,
                                    'label'=> $cck->_plain_text($key),
                                    'value'=> $content_type_values[$key],
                                    'placeholder'=> '',
                                );
                            break;

                    }

                    break;
                case 'maxlength':

                    $description = '';
                    $placeholder = '';
                    $label = $key;

                    switch($element['type'])
                    {
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

                    switch($key)
                    {


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
                            'id'=> $key,
                            'class'=> $key,
                            'title'=> $key,
                            'name'=> $key,
                            'label'=> $cck->_plain_text($key),
                            'value'=> $content_type_values[$key],
                            'placeholder'=> $placeholder,
                            'description' => $description
                        );

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
        $form['elements']['copy'] =
            array(
                'type' => 'submit',
                'id'=> 'copy',
                'class'=> 'copy',
                'title'=> 'copy',
                'name'=> 'copy',
                'value'=> 'copy',
                'formaction'=> '?content/content_type_field_copy',

            );
        // $form_output = '<h2>' . $element['type'] . '</h2>';
        $form_output = $cck->_form($form,'html_form');

        return $form_output;
    }
}

?>
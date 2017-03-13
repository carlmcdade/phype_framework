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
 *  Development Documentation outside of scope set by namespace is not visible to the
 *  documentation function used in CCK
 */

namespace users;

/**
 *  Documentation and usage example for this controller users_api
 *  Developers should document code by writing in the comment blocks
 *  of the Class file. The text will show in the list of methods made available
 *  as public and to pages.
 */

class users_form{


    public  $section;
    public  $module;
    public  $access;

    function __construct()
    {
        global $cck;
        //Test the Common settings
        $this->module = __NAMESPACE__;
        $this->section = __CLASS__;



    }


    function __destruct()
    {
    		//
    }

    /**
     *  Usage example  api/user/users_add_user/name/email
     */
    function users_login_form()
    {
        global $cck, $settings;
        $form = array();
        $form['name'] = 'login_user_form';
        $form['id'] = 'login_user';
        $form['method'] = 'POST';
        $form['action'] = $cck->_url($this->module. '/users_login_submit/');
        $form['title'] = 'sign in to your account';
        $form['enctype'] = '';

        $form['elements']['username'] =
            array(
                'type' => 'text',
                'id' => 'id-' . 'type',
                'class' => 'class-' . 'type',
                'title' => 'username',
                'label' => 'Name',
                'name' => 'user-name',
                'value' => '',
                'placeholder' => 'type name',
                'required' => ''
            );

        $form['elements']['password'] =
            array(
                'type' => 'password',
                'id' => 'id-' . 'password',
                'class' => 'class-' . 'password',
                'title' => 'password',
                'label' => 'Password',
                'name' => 'user-password',
                'value' => '',
                'placeholder'=> 'type password',
                'required' => ''
            );

        $form['elements']['submit'] =
            array(
                'type' => 'submit',
                'id'=> 'signin',
                'class'=> 'signin',
                'title'=> 'signin',
                'name'=> 'signin',
                'label'=> 'signin',
                'value'=> 'Sign in',
                'before'=> '<div></div>',
            );

        return $cck->_form($form,'html_form');
    }

    /**
     *  Usage example  api/user/users_delete_users/id
     */
    function users_register_form()
    {

    }

    /**
     *  Usage example  api/user/users_list_users/all
     *  api/user/users_list_users/1/45/89
     */

    function users_list_users()
    {
        print 'tested api show info for web service  in JSON format';
        exit;
    }
}

?>
<?php
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
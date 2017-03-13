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

 * ==================================================================
 * 
 *                        users.class.inc
 * 
 * ==================================================================
 *
 * @todo 
 * 
 */

namespace users;

class users{
	
	private $common;
	public  $menu;
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
    
    /**
     *
     * @return multitype:multitype:string
     */
    
    function hook_access()
    {
    	$authorize = array(
    			$this->module . '/users_profile' => array('users profile'),
    			$this->module . '/users_settings' => array('users settings'),
    			$this->module . '/users_control_panel' => array('users control panel'),
    			$this->module . '/users_history' => array('users history'),
    	);   
    	return $authorize;
    }
    
    /**
    *   Navigation hook for all modules
    */

    function hook_links()
    {
    	global $cck;

        $link = 'links';
    	
    	$var[$link][1] = array(
        	'text' => 'My Account',
        	'path' => $this->module . '/users_control_panel',
        	'controller' => 'users',
        	'action' => 'users_control_panel',
        	'css_class' => array($this->module, 'main_item'),
        	'css_id' => $this->module,
            'access' => $cck->_user_access(),
            'weight' => 15
        );

        $var[$link][2] = array(
            'text' => 'Sign out',
            'path' => $this->module . '/users_logout',
            'controller' => 'users',
            'action' => 'users_control_panel',
            'css_class' => array($this->module, 'main_item'),
            'css_id' => $this->module,
            'access' => $cck->_user_access(),
            'weight' => 16
        );
        $var[$link][3] = array(
            'text' => 'Sign in',
            'path' => $this->module . '/users_login',
            'controller' => 'users',
            'css_class' => array($this->module, 'main_item'),
            'css_id' => $this->module,
            'access' => ($cck->_user_access() == TRUE ? FALSE : TRUE),
            'weight' => 17
        );
        return $var;
    }
    
    /**
    *   Sub navigation is a hook and displayed per call by hook_links
    */
    
    function hook_module_links()
    {
    	$link = 'links';
    	
    	$var[$link][1] = array(
					'text' => 'control panel', 
					'path' => $this->module . '/users_control_panel'
					);
    	$var[$link][2] = array( 
					'text' => 'profile', 
					'path' => $this->module . '/users_profile',
					'alias' => 'index',
					'controller' => $this->module,
					'action' => 'users_profile',
					'css_class' => array($this->module, 'main_item'),
					'css_id' => $this->module 
						);
		$var[$link][3] = array(
					'text' => 'settings', 
					'path' => $this->module . '/users_settings'
					);
		$var[$link][4] = array(
				'text' => 'history',
				'path' => $this->module . '/users_history'
		);
        $var[$link][5] = array(
            'text' => 'content',
            'path' => $this->module . '/users_content'
        );

        return $var;
    }

    function hook_blocks()
    {

        $block = 'container';

        $var[] = array(
            'title' => 'Users',
            'content' => $this->module . '/content',
            'css_class' => array($this->module, 'main_item'),
            'css_id' => $this->module
        );

        return $var;

    }
    
    /**
     * 
     * 
     */

    function users_profile()
    {
    	global $cck;

    	//$connect = $cck->_dbconnect('datasource_default');

    	// get all links from each class controller
    	$menu = $cck->_hooks('hook_links');
    	$sub_menu = $cck->_hooks('hook_module_links');

    	$variables['navigation'] = $cck->_menu_links($menu, 'links_main_menu');
    	$variables['sub_navigation'] = $cck->_module_links($sub_menu[$this->module],
    		array(
    			'template'=>'links_sub_menu',
    			'index' => $this->module
    			));
    	$variables['page_title'] = 'User';
    	$variables['content_title'] = 'User profile';
    	
    	// Get the content column values
        
    	//$query = $connect->query("SELECT * FROM users WHERE id = 1");
    	//$information = $query->fetchAll();

        $output = $cck->_debug(isset($_SESSION['login_user']) ? $_SESSION['login_user']: 'not logged in');
        //$output .= $cck->_debug(isset($_SESSION) ? $_SESSION: 'no session found');
    	
    	$variables['content'] = $output;
        print $cck->_view('users', $variables);         
    }
    
    /**
     * 
     * 
     */
    
    function users_control_panel()
    {
    	// set links
    	global $cck;
    	$args = $cck->_args();
        if(isset($args['name']))
        {
            $name = $args['name'];
        }
        else
        {
            $name = 'User';
        }
    	// get all links from each class controller
    	$menu = $cck->_hooks('hook_links');
    	$sub_menu = $cck->_hooks('hook_module_links');
    	$user_menu = $cck->_hooks('hook_user_links');
    	
    	$variables['navigation'] = $cck->_menu_links($menu, 'links_main_menu');
    	$variables['sub_navigation'] = $cck->_module_links($sub_menu[$this->module],
    		array(
    			'template'=>'links_sub_menu',
    			'index' => $this->module
    			)); 
    	$variables['page_title'] = 'User';
    	$variables['content_title'] = $name . "'s" . ' Control Panel';
    	//$variables['content'] = $cck->_menu_links($user_menu, 'links_admin_index_menu');
    	print $cck->_view('users', $variables);
    }

    /**
     *
     */
    function users_settings()
    {
    	// get all links from each class controller
    	global $cck; 
    	$menu = $cck->_hooks('hook_links');
        $sub_menu = $cck->_hooks('hook_module_links');
    	
    	$variables['navigation'] = $cck->_menu_links($menu, 'links_main_menu');
    	$variables['sub_navigation'] = $cck->_module_links($sub_menu[$this->module],
    		array(
    			'template'=>'links_sub_menu',
    			'index' => $this->module
    			)); 
    	$variables['page_title'] = 'User';
    	$variables['content_title'] = 'User settings';
    	
    	// Get the content column values
        //$connect = $cck->_dbconnect('datasource_0');
    	//$query = $connect->prepare("SELECT * FROM users WHERE id = 1");
    	//$information = $query->fetchAll();
    	
    	$variables['content'] = '';
        print $cck->_view('users', $variables);
    }

    function users_content()
    {
        // get all links from each class controller
        global $cck;
        $menu = $cck->_hooks('hook_links');
        $sub_menu = $cck->_hooks('hook_module_links');

        $variables['navigation'] = $cck->_menu_links($menu, 'links_main_menu');
        $variables['sub_navigation'] = $cck->_module_links($sub_menu[$this->module],
            array(
                'template'=>'links_sub_menu',
                'index' => $this->module
            ));
        $variables['page_title'] = 'User';
        $variables['content_title'] = 'User content';

        $variables['content'] = 'show users content';
        print $cck->_view('users', $variables);
    }

    /**
     *
     */
    function users_history()
    {
    	// get all links from each class controller
		global $cck;
    	$menu = $cck->_hooks('hook_links');
    	$sub_menu = $cck->_hooks('hook_module_links');
    	
    	$variables['navigation'] = $cck->_menu_links($menu, 'links_main_menu');
    	$variables['sub_navigation'] = $cck->_module_links($sub_menu[$this->module],
    		array(
    			'template'=>'links_sub_menu',
    			'index' => $this->module
    			));  
    	$variables['page_title'] = 'User';
    	$variables['content_title'] = 'User history';
    	
    	$variables['content'] = 'show users history and stats';
    	print $cck->_view('users', $variables);
    }
    
    /**
     * 
     * 
     */
    
    function users_login_submit($form_submission = array())
    {
        global $cck, $settings;
        $form_submission = $_POST;
        $output =  $cck->_debug($form_submission);
        $output .=  $cck->_debug($_SESSION);

        $valid = $cck->_form_validate($form_submission, 'Your credentials were submitted.');
        if($valid)
        {
            $loggedin = $this->users_access_check($form_submission['user-name'], $form_submission['user-password']);
            if($loggedin == TRUE)
            {
                $cck->_message_set( $name = 'notice', 'Logged in', 'success');
                header('location:' . $cck->_url($settings['site']['destination']['value']));
            }
        }


        //'show users logged in and redirect'
        $variables['content'] = $output;
        print $cck->_view('users', $variables);


    }
    
    /**
     * 
     * 
     */

    function users_access_check($username = NULL, $password = NULL)
    {
        global $cck, $settings;//
        if($settings['owner']['name']['value'] == $username  && $settings['owner']['password']['value'] == $password)
        {

            // remove previous tries


            $id = session_id();
            $cck->_end_sessions('login_user', $id);
            $_SESSION['login_user'][$id] = array();
            $_SESSION['login_user'][$id]['user'] = $username;
            $_SESSION['login_user'][$id]['user_id'] = '1';
            $_SESSION['login_user'][$id]['valid'] = TRUE;
            $_SESSION['login_user'][$id]['timeout'] = 10;

            return TRUE;
        }
        else
        {
            $cck->_message_set( $name = 'notice', 'Login credentials incorrect, try again.', 'error');
        }
        return FALSE;

    }
    
    function users_login_form()
    {
    	global $cck;

        $form = array();
        $form['name'] = 'user_login';
        $form['id'] = 'user_login';
        $form['method'] = 'POST';
        $form['action'] = $cck->_url($this->section.'/login/');
        $form['title'] = 'send a message';
        $form['enctype'] = 'text/plain';

        $form['elements']['username'] =
            array(
                'type' => 'text',
                'id'=> 'myusername',
                'class'=> 'myusername',
                'title'=> 'username',
                'label'=> 'user name',
                'name'=> 'username',
                'value'=> '',
                'placeholder'=> 'username',
            );
        $form['elements']['password'] =
            array(
                'type' => 'password',
                'id'=> 'mypassword',
                'class'=> 'mypassword',
                'title'=> 'password',
                'name'=> 'password',
                'label'=> 'password',
                'value'=> '',
                'placeholder'=> 'password',
            );

        $form['elements']['send'] =
            array(
                'type' => 'submit',
                'id'=> 'send',
                'class'=> 'send',
                'title'=> 'send',
                'name'=> 'send',
                'label'=> 'send',
                'value'=> 'sign in',
                'before'=> '<div></div>',
            );

        $output = $cck->_form($form,'html_form');

    	return $output;
    }

    /**
     * 
     * 
     */
    
    function users_logout($user = NULL , $all = FALSE)
    {
        global $cck, $settings;

        // logout user by name find user
        if($user && isset($_SESSION['login_user']))
        {
            foreach($_SESSION['login_user'] as $find => $info)
            {
                if($info[$user] == $user)
                {
                    unset($_SESSION['login_user'][$find]);
                }
            }
        }

        // logout all users
        if(isset($_SESSION['login_user']) && is_array($_SESSION['login_user']) && $all === TRUE)
        {
            foreach($_SESSION['login_user'] as $name)
            {
                unset($_SESSION['login_user'][$name]);
            }
            return;
        }

        //logout this user
        $user_session = session_id();
        unset($_SESSION['login_user'][$user_session]);
        unset($_SESSION['messages']
        );

        $cck->_message_set( $name = 'notice', 'Logged out', 'notice');
        header('location:' . $cck->_url($settings['site']['frontpage']['value']));
    }

    function users_login($user = NULL , $all = FALSE)
    {
        global $cck;

        if($cck->_user_access() == FALSE)
        {
            $form = new \users\users_form();
            $show_form = $form->users_login_form();
            $variables['content'] = $show_form ;

        }
        else
        {
            $variables['content'] = 'logged in' ;
        }

        print $cck->_view('page_login', $variables);
        return;
    }


}

?>

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

/**
 * ==================================
 * Bootstrap CCK
 *
 * @todo Define some constants and globals that can be easily changed. Done here because there maybe multiple modules.
 * taking care of different application sets. Start bootstrapping here.
 *
 * @todo create a more structured bootstrap file that can be used in other
 * situations
 *
*/




/*
* These global variables are necessary to carry values to the Classes nested
* in the module functions.
*
* @todo Module_list and hook_list should come from a configuration data source
* loaded by a Singleton Class
*
*/
$settings = include(INI_FILENAME);

class CCK
{

	static private $_instance;
    public  $default_main_menu = 'links_main_menu';
    public  $default_admin_menu = 'links_admin_menu';
    public  $_modules_list;
    public  $hooks_list;
    public  $moduleName;
    public  $section;
    public  $dbc;
    public  $blocks;



    private function __construct()
	{
		global $cck,$settings;
		spl_autoload_register(array($this, '_autoload'));
		spl_autoload_register(array($this, '_helpers_autoload'));
        register_shutdown_function(array(&$this, '_fatal_error_handler'));
		
		if(file_exists( INI_FILENAME ))
        {

			//$this->ini_settings = $settings;
            $this->_modules_list = $settings['developer']['modules'];
            $this->hooks_list = $settings['developer']['hooks'];
            
        }

        // Make a call to global objects or variables ie. Hooks, blocks, users
        $this->blocks = '';

		
	}

    /**
     * @return string
     *
     * Show information. Version, TODO list, Licensing
     * if the CCK variable is every called as a string.
     */
	function __tostring()
	{
		//
        return 'Content Connection Kit information. Version, TODO list, Licensing';
	}

    /**
     * @throws Exception
     * Only one instance of the core CCK class allowed. Please extend this CCK class for new functionality
     */
	private function __clone()
	{
		throw new Exception('Only one instance of the core CCK class allowed. Please extend this CCK class for new functionality');
	}

    /**
     * @return CCK
     *
     *  The CCK Core Class is locked as much as possible to a singleton that
     *  is callable via this method.
     *  example:
     *  $cck = CCK::get_instance();
     *
     *  This should only be called once per page load in the document root index.php file.
     */
	final public static function get_instance()
	{
		return isset(self::$_instance) ? self::$_instance : self::$_instance = new self();
	}

    /**
     * @param null $class
     *
     *  The registered autoloader for controllers in the Modules directory
     */
	function _autoload($class = NULL)
	{
		global $settings;
		
		//CCK


		// directories
		$modules = $this->_modules();

		//load all controllers
		foreach($modules as $file)
		{
			if(file_exists($file))
			{
				include_once($file);
			}
		}

	}
	
	function _helpers_autoload($class)
	{
		global $cck, $settings;

        $helpers = $settings['system']['helpers']['value'];
		$class = strtolower($class);
		$path = DOCROOT . DIRECTORY_SEPARATOR . $helpers. DIRECTORY_SEPARATOR . $class . DIRECTORY_SEPARATOR . $class . '.php';
		$path = str_replace("\\", "/", $path);
		
		if(file_exists($path))
		{
			require_once($path);
		}
		return;
	}

    /**
     * @param null $inclass
     * @param null $foraction
     * @param bool $asobject
     * @return mixed
     *
     *  The  bootstrap detects the route  and forwards the request to the controller/modules
     *  class and method in the request  the uri fo the request can be recieved in two forms
     *  1.)  explicit section class called: [namespace]\[class]/[method][arguments] example; content\content_admin/content_types/[arguments]
     *  2.)  main class called: [class]/[method]/ example: blog/blog_list
     *  3.)  section class call via naming convention : [suffix]/[namespace]/[method]  example;  [admin || form || api]/blog/blog_posts
     */
	function _bootstrap($inclass = NULL, $foraction = NULL, $asobject = FALSE )
	{
		global $cck,$settings;
		$controller = NULL;
		$action = NULL;

        // gather primary navigation links for system
        $menu = $cck->_hooks('hook_links');
        //$access = $cck->_hooks('hook_access');

        //default primary navigation to inject to page templates as variable
        $variables['navigation'] = $cck->_menu_links($menu, 'links_main_menu');

        // set an array of arguments from the url
        $arguments = $this->_args();


		// $allow alias to load    [controller]/[action] directly using bootstrap to avoid HTTP redirects
		if($inclass && $foraction)
		{
			//$resource = $this->_get_controller();
			$class = $inclass;
			$action = $foraction;
			$namespaced = $class. CLASS_SEPERATOR . $class;

		}

		else
		{
			$controller = $this->_get_controller();

			if($controller['suffix'] != '')
			{
				$namespace = $controller['namespace'];
				$class = $controller['class'];
				$action = $controller['method'];
				$namespaced = $namespace. CLASS_SEPERATOR . $class;

			}
			else
			{
				$class = $controller['class'];
				$action = $controller['method'];
				$namespaced = $controller['class']. CLASS_SEPERATOR .$class;
			}

		}		


		if(class_exists($namespaced) == TRUE)
		{
			// if not in a namespace then go to root class
			/*if(class_exists($class) == TRUE)
			{
				$controller = new $class();
				if($this->is_class_method("public",$action, $controller))
				{
					return $controller->$action($arguments); // send string of arguments
				}
				else
				{
					$class = str_replace('_','/',$class);				
					$output = 'The address requested '. $class .'/'. $action.' does not exist. 1001' ;
					$variables['content'] = $output;
					print $cck->_view('page_404', $variables);
					exit('');
				}
			}*/
			if(class_exists($namespaced) == TRUE)
			{
				$controller = new $namespaced();
				if($this->is_class_method("public",$action, $controller))
				{

                        return $controller->$action($arguments); // send string of arguments

				}
                else
                {
                    $output = 'The address requested '. $class .'/'. $action.' does not exist. 1002' ;
                    $variables['content'] = $output;
                    print $cck->_view('page_404', $variables);
                    exit();
                }

			}
			else
			{
				$output = 'The site address requested does not exist. 1003'. $action ;
				$variables['content'] = $output;
				print $cck->_view('page_404', $variables);
				exit('');
			}
		}
		else
		{
			//================= Aliased Menu Url Search =======================//
			
			$alias = $_SERVER['QUERY_STRING'];

			foreach($menu as $module)
			{
				foreach($module['links'] as $link)
				{
					if(array_key_exists('alias', $link))
					{
						if($link['alias'] === $alias)
						{
							$controller = $link['controller'];
							$action = $link['action'];
							$cck->_bootstrap($controller, $action);
							exit('');
							break;	
						}
							
					}					
				}
			}

			//===========================================//

            if($this->is_class_method("public",$action, $controller))
            {
                return $controller->$action($arguments);
            }
            else
            {
                $variables['navigation'] = $cck->_menu_links($menu, 'links_main_menu');
                $output = 'The URL requested ('.$namespaced. '/' . $class . '/' . $action .') does not exist. error:103';
                $variables['content'] = $output;
                print $cck->_view('page_404', $variables);
                exit('');
            }



		}

	}

    /**
     *  Call a method after page renders
     */
    function _end_sessions($tree = NULL, $branch = NULL)
    {
        global $cck,$settings;

        // clear explicitly set sessions in hit list

        if(isset($_SESSION['kill_messages']) && is_array($_SESSION['kill_messages']))
        {
            foreach($_SESSION['kill_messages'] as $name) {
                // timing out with PHP rather than javascript concealment
                if(isset($_SESSION['messages'][$name]['started']) && isset($_SESSION['messages'][$name]['timeout']))
                {
                    if((time() - $_SESSION['messages'][$name]['started']) > $settings['site']['message_timeout']['value']) {
                        unset($_SESSION['messages'][$name]);
                    }
                }


            }
            unset($_SESSION['kill_messages']);
        }

        // clear sessions as parameters
        if($tree && isset($_SESSION[$tree]) && is_array($_SESSION[$tree]))
        {
            if(isset($_SESSION[$tree][$branch]) && is_array($_SESSION[$tree][$branch]))
            {
                unset($_SESSION[$tree][$branch]);
            }

            unset($_SESSION[$tree]);
        }


    }

	/**
	 * This function is used to gather and filter files used as controllers into
	 * module groups. The availability and naming conventions of the files is set in the configuration file
	 * based on the following lists
	 *
	 * Directories = modules as parent, other are ignored
	'modules' => array(
	"common",
	"blog",
	"portfolio",
	"contact",
	"content",
	"install",
	"menu",
	"users",
	"admin",
	"example",
	),
	 Files within the directories as siblings, others are ignored
	'suffixes' => array(
	"admin",
	"form",
	"api",

	),
     * main controller file name and namespace match example of module with controller [blog]\[blog]
     * further files can be added using allowable suffixes/sections in configuration file
     * example of module section file names :  blog_admin, blog_form, blog_api
	 *
	 * @return mixed
     *
     * The active modules being used are in the $settings['developer']['modules'] array
     * to de-activate a module empty the array value e.g. $settings['developer']['modules']['contact'] = "";
     * the contact module is not active and no hooks contained are called. $settings['developer']['modules']['contact'] = "contact"; the contact module is now active.
     *
	 */
	function _modules()
	{
		global $cck, $settings;

		$active_modules = $settings['developer']['modules'];
		$class_suffix = $settings['developer']['module_files'];

		//exit($cck->_debug($settings));
        $modules_directory_name = $settings['system']['controllers']['value'];
		$modules_directory_path = DOCROOT .  DIRECTORY_SEPARATOR . $modules_directory_name;


		foreach(glob($modules_directory_path.'/*', GLOB_ONLYDIR) as $key => $directory) {
			$name = basename($directory);
			$list = glob($directory . "/*.inc");
			$assoc_list = array();
			foreach($list as $item)
			{
				$parts = explode('/',$item);
				$parts = array_reverse($parts);
				$labels = explode('.',$parts[0]);
				$label = $labels[0];
				$assoc_list[$label] = $item;

			}

			//$list = $assoc_list;

			// gather list of controller classes available

			// start with main controller file at top of list, no suffix needed
			$list_active[$name][] =  $name;

			// create list of sibling to main controller by adding suffix
			foreach($class_suffix as $tail => $desc)
			{
				$list_active[$name][] = $name . '_'. $tail;
			}

			// array of existing module directories and the file they contain
            $modules['in_directory'][$name] = $assoc_list;
			if(in_array($name, $active_modules))
			{
				// array of possible allowed module directories and file list they can contain
                $modules['in_configuration_list'][$name] = $list;
			}

		}

        // iterate through the existing directories and file and compare to the settings directories and files
		foreach($list_active as $item => $value )
		{
			//print '<pre>' . print_r($item, 1) . '</pre>';

            // compare the file list to actual existing files in the modules directory
			foreach($value as $key )
			{
				// print '<pre>' . print_r($key, 1) . '</pre>';
                // if the module directory exists and the main or any sibling file exists then set for autoloading
                // array: path
				if(isset($modules['in_directory'][$item][$key]) && in_array($item,$active_modules)){
					$autoload[$key] = $modules['in_directory'][$item][$key];
				}
			}
		}


		//print '<pre>' . print_r($autoload, 1) . '</pre>';
		//print '<pre>' . print_r($active_controllers, 1) . '</pre>';
		//print '<pre>' . print_r($list_active, 1) . '</pre>';
		// print '<pre>' . print_r($modules['activated_list'], 1) . '</pre>';

		return $autoload;

	}

    /**
     * @param null $model
     * @param null $method
     * @param array $bind
     * @param null $type
     * @return mixed
     *
     * Models are Classes that are called from within Controller methods.  The methods in a Model have the objectives
     * of extraction insertion and manipulation of data/information from the internal system. Classes are loaded via
     * a separate file system loader here. This maintains loose coupling and insulates them from request to response flow used
     * by the Controllers.
     *
     * When calling a model the syntax for the  class name may vary but the method will allways look for th "_model" suffix
     * or add it if missing. So using "content"  in $cck->_model('content','content_update_files', $data); will automatically
     * look for the classname "content_model" in the class file "content". The suffix default is "model" but can be changed
     * in the method call. this is to increase flexibility and help prevent name collision/hijacking in the global namespace.
     *
     *
     */
	function _model($model = NULL,$method = NULL,$bind = array(), $suffix = 'model' )
	{

		$variables = array();
        $model_path = DOCROOT . DIRECTORY_SEPARATOR . '_models' . DIRECTORY_SEPARATOR . $model . '.model.inc';

        //check for the use of the proper "_model" suffix in the class name to prevent collision in the global space
        if(strtolower(strrchr($model, '_') != '_' . $suffix))
        {
            $model = $model. '_' . $suffix;
        }

        /*if(class_exists($model, false))
        {
            $content = new $model();
            return $content->$method($bind);
        }*/
        if(file_exists($model_path))
        {
            $variables['class'] = $model;
            $variables['method'] = $method;
            $variables['arguments'] = $bind;
            include_once($model_path);
            $content = new $model();
            return $content->$method($bind);

        }
        else
        {
            exit('model file not not found in location:' . $model_path);
        }




	}

    /**
     * @param string $view
     * @param null $variables
     * @param bool $template
     * @param null $output
     * @return bool|null|string
     *
     * This is the main method for determining the visual output of the website. Views are
     * files that contain the presentation html and content variables. Controllers should
     * should only output clean data as a string, array or object. These are sent to this
     * method via the $variables parameter.
     */
	function _view($view = '', $variables = NULL, $template = true, $output = NULL)
	{
		global $cck,$settings;

        $directories = array('html','page');
        $parts = explode('_', $view);
        if(in_array($parts[0],$directories))
        {
              $template_path = DOCROOT . DIRECTORY_SEPARATOR .
                  $settings['system']['themes']['value'] .  DIRECTORY_SEPARATOR .
                  $settings['site']['theme']['value'] .DIRECTORY_SEPARATOR .
                  $parts[0] .  DIRECTORY_SEPARATOR .
                  $view . '.tpl.php';
        }
        else
        {
            $template_path = DOCROOT . DIRECTORY_SEPARATOR .
                $settings['system']['themes']['value'] .  DIRECTORY_SEPARATOR . $settings['site']['theme']['value'] .
                DIRECTORY_SEPARATOR . $view . '.tpl.php';
        }







        //
        $site_variables['page'] =  $cck->_get_calling_method();
        $site_variables['site_messages']  = $cck->_message_get('notice');
        $site_variables['site_blocks_left']  = 'global blocks left';
        $site_variables['site_blocks_right']  = 'global blocks right';
        $site_variables['site_root']  = $settings['system']['base_url']['value'];


        // trun site settings into variables
        foreach($settings['site'] as $key => $site)
        {
            $site_variables[$key] = $site['value'];
        }
        $site_variables['site_name']  = $settings['site']['name']['value'];
        $site_variables['site_description']  = $settings['site']['description']['value'];
        $site_variables['site_frontpage']  = $cck->_url($settings['site']['frontpage']['value']);
        $site_variables['site_logo']  = $cck->_url($settings['system']['themes']['value'].'/'.$settings['site']['theme']['value'].'/images/'.$settings['site']['site_logo']['value'],TRUE);

        //$form = new \users\users_form();
        //$show_form = $form->users_login_form();
        $site_variables['site_blocks_access']  = ''; //$show_form;

        if(!is_array($variables))
        {

            $variables = (array)$variables;
            $template_path = DOCROOT . DIRECTORY_SEPARATOR .
                $settings['system']['themes']['value'] .  DIRECTORY_SEPARATOR . $settings['site']['theme']['value'] .
                DIRECTORY_SEPARATOR . 'page_content_error_message.tpl.php';

            $variables['class'] = 'error';

            $variables['error_message'] = 'This content has been removed or cannot be found because of a system error. Check with site administrator';

            $output = $cck->_template($template_path, $variables);
            return $output;

        }else
        {
            $variables = array_merge($site_variables,$variables);
        }


    	if (file_exists($template_path) == false)
    	{
    		trigger_error("Template {$view} not found in ". $template_path);
    		return false;
    	}
    
    	if(is_array($variables))
    	{
    		// Load variables here because they become part of the module not the theme template.php file.
    		$output .= $cck->_template($template_path, $variables);
    	}   
    	return $output;
	}

    /**
     * @param $template_file
     * @param $variables
     * @return string
     *
     *
     *  global template site_variable are declared here.
     *  there content can be overriden if called directly by a method
     *  Site variables keys:
     *  site_name, site_root, site_description, site_frontpage, site_blocks_access,
     *  site_blocks_left, site_blocks_right
     *
     */
	function _template($template_file, $variables)
	{

		// add in some of the system variables from the settings
        // as default to every template file.
		global $cck, $settings;

        /* second array overrride like keys
         * so methods can call the site variable and override the default set here.
         * but those that do not get the default
        */
        //$variables = array_merge($site_variables,$variables);


		ob_start();
		extract($variables, EXTR_SKIP); // Extract the variables to a local namespace
        include $template_file; // Include the template file
		return ob_get_clean(); // End buffering and return its contents

	}

    function _get_calling_method()
    {
        $trace=debug_backtrace();
        $caller=$trace[2];

        /*echo "Called by {$caller['function']}";
        if (isset($caller['class']))
            echo " in {$caller['class']}";
        */
        return $caller['function'];
    }

    /**
     * @param $template_file
     * @param $variables
     * @return string
     *
     * This is a separate template output function for forms
     * and blocks for parallel processing. Using only the _template()
     * function would cause a tail recursion loop  when content needs to be
     * processed within the main cck template and variables stream.
     */
    function _form_process($template_file, $variables)
    {

        // add in some of the system variables from the settings
        // as default to every template file.
        global $cck, $settings;


        /* second array overrride like keys
         * so methods can call the site variable and override the default set here.
         * but those that do not get the default
        */


        ob_start();
        extract($variables, EXTR_SKIP); // Extract the variables to a local namespace
        include $template_file; // Include the template file
        return ob_get_clean(); // End buffering and return its contents

    }
	
	function _path_segment($index = NULL)
	{
		//
		global $settings;

		$path = $_SERVER['QUERY_STRING'];


		if($path == '')
		{
			return;
		}
		else
		{
			$parts[$path] = explode('/', $_SERVER['QUERY_STRING']);
		}
		
		$parameters = $this->_query_segment();
	
		foreach($parts[$path] as $key => $segment)
		{
			$cleaned = explode('&', $segment);
			$parts[$path][$key] = $cleaned[0];
		}

		// if the  segment is a suffix then take the next segment to write class name.
		foreach($settings['suffixes'] as $suffix){

		}
		
		if(isset($parts[$path][$index]))
		{
			return $parts[$path][$index];
		}
	}

    /**
     * set an array of arguments from the url after class/method/[arguments]
     * example: ?blog/blog_list/only/one/fun&one=that&none=this
     *
     * retrieval code:
     * $args = $cck->_args(func_get_args());
     *
     * page output for example:
     * $arg = Array
     *  (
     *    [0] => only
     *    [1] => one
     *    [2] => fun
     *    [one] => that
     *    [none] => this
     *  )
     * @return array
     */
    function _args($index=null)
    {

        global $cck, $settings;

        $path= explode('/', $_SERVER['QUERY_STRING']);
        $arguments = array();
        $params = array();

        // shift uri for main controllers or sub controllers
        if (array_key_exists($path[0], $settings['developer']['module_files']))
        {
            $path = array_slice($path,3);
        }
        else{
            $path = array_slice($path,2);
        }

        foreach ($path as $key => $val)
        {

            if (strpos($val, '&') !== FALSE)
            {
                $end = strpos($val, '&');
                $var = substr($val, 0, $end);
                $sub_var = substr($val, $end);
                parse_str($sub_var, $params);
                if(!empty($var))
                {
                    $arguments[$key] = $var;
                }

            }
            else
            {
                if(!empty($val))
                {
                    $arguments[$key] = $val;
                }

            }



        }
        $arguments = array_merge($arguments, $params);
        return $arguments;
    }
	
	function _translate()
	{
		//
	}

    /**
     * @param $data
     * @return mixed|string
     *
     */
    function _xss_clean($data)
    {
        // Fix &entity\n;
        $data = str_replace(array('&amp;','&lt;','&gt;'), array('&amp;amp;','&amp;lt;','&amp;gt;'), $data);
        $data = preg_replace('/(&#*\w+)[\x00-\x20]+;/u', '$1;', $data);
        $data = preg_replace('/(&#x*[0-9A-F]+);*/iu', '$1;', $data);
        $data = html_entity_decode($data, ENT_COMPAT, 'UTF-8');

        // Remove any attribute starting with "on" or xmlns
        $data = preg_replace('#(<[^>]+?[\x00-\x20"\'])(?:on|xmlns)[^>]*+>#iu', '$1>', $data);

        // Remove javascript: and vbscript: protocols
        $data = preg_replace('#([a-z]*)[\x00-\x20]*=[\x00-\x20]*([`\'"]*)[\x00-\x20]*j[\x00-\x20]*a[\x00-\x20]*v[\x00-\x20]*a[\x00-\x20]*s[\x00-\x20]*c[\x00-\x20]*r[\x00-\x20]*i[\x00-\x20]*p[\x00-\x20]*t[\x00-\x20]*:#iu', '$1=$2nojavascript...', $data);
        $data = preg_replace('#([a-z]*)[\x00-\x20]*=([\'"]*)[\x00-\x20]*v[\x00-\x20]*b[\x00-\x20]*s[\x00-\x20]*c[\x00-\x20]*r[\x00-\x20]*i[\x00-\x20]*p[\x00-\x20]*t[\x00-\x20]*:#iu', '$1=$2novbscript...', $data);
        $data = preg_replace('#([a-z]*)[\x00-\x20]*=([\'"]*)[\x00-\x20]*-moz-binding[\x00-\x20]*:#u', '$1=$2nomozbinding...', $data);

        // Only works in IE: <span style="width: expression(alert('Ping!'));"></span>
        $data = preg_replace('#(<[^>]+?)style[\x00-\x20]*=[\x00-\x20]*[`\'"]*.*?expression[\x00-\x20]*\([^>]*+>#i', '$1>', $data);
        $data = preg_replace('#(<[^>]+?)style[\x00-\x20]*=[\x00-\x20]*[`\'"]*.*?behaviour[\x00-\x20]*\([^>]*+>#i', '$1>', $data);
        $data = preg_replace('#(<[^>]+?)style[\x00-\x20]*=[\x00-\x20]*[`\'"]*.*?s[\x00-\x20]*c[\x00-\x20]*r[\x00-\x20]*i[\x00-\x20]*p[\x00-\x20]*t[\x00-\x20]*:*[^>]*+>#iu', '$1>', $data);

        // Remove namespaced elements (we do not need them)
        $data = preg_replace('#</*\w+:\w[^>]*+>#i', '', $data);

        do
        {
            // Remove really unwanted tags
            $old_data = $data;
            $data = preg_replace('#</*(?:applet|b(?:ase|gsound|link)|embed|frame(?:set)?|i(?:frame|layer)|l(?:ayer|ink)|meta|object|s(?:cript|tyle)|title|xml)[^>]*+>#i', '', $data);
        }
        while ($old_data !== $data);

        // we are done...
        return $data;
    }

    function _url($url_string = NULL, $base = FALSE)
    {
        global $cck, $settings;
        if(isset($settings['system']['base_url']['value']) && !empty($settings['system']['base_url']['value']))
        {
            $base_url = $settings['system']['base_url']['value'];
            $approot = $base_url . substr(dirname(__FILE__),strlen($_SERVER['DOCUMENT_ROOT']));
        }
        else
        {
            $base_url = 'http://'.$_SERVER['SERVER_NAME'];
            $approot = $base_url . '/' . substr(dirname(__FILE__),strlen($_SERVER['DOCUMENT_ROOT']));
        }

        // fix url paths created in windows
        $url_string = str_replace("\\", "/", $url_string);

        if($base == TRUE)
        {
            return $approot  . '/' . $url_string;
        }
        else
        {
            $url = $approot  . '/index.php' . '?' . $url_string;
            return $url;
        }

    }

	
	function _url_alias($alias = NULL, $menu = array())
	{
		//
        global $cck;
		$alias = $_SERVER['QUERY_STRING'];
					
			foreach($menu as $module)
			{
				foreach($module['links'] as $link)
				{
					if(array_key_exists('alias', $link))
					{
						if($link['alias'] === $alias)
						{
                            $controller = $link['controller'];
							$action = $link['action'];
							$cck->_bootstrap($controller, $action);
							exit('');
							break;	
						}
							
					}					
				}
			}
	}

	function _get_object($namespace,$class)
	{
		$object = new $namespace .'\\'.$class();
		return $object;
	}

    /**
     * @param null $module
     * @return array
     * get a list of controllers present in a modules directory
     *
     * filtered by the list of names in the settings file
     * others are ignored.
     *
        'suffixes' => array(
        "admin",
        "form",
        "forms",
        "api",
        ),
     *
     */
    function _get_module_controllers($module = NULL)
    {
        global $cck, $settings;
        $existing_controllers = $settings['system']['controllers']['value'];
        $module_path =  DOCROOT .  DIRECTORY_SEPARATOR . $existing_controllers . DIRECTORY_SEPARATOR . $module;


            $name = basename($module_path);
            $list = glob($module_path . "/*.inc");
            $assoc_list = array();
            foreach ($list as $item) {
                $parts = explode('/', $item);
                $parts = array_reverse($parts);
                $labels = explode('.', $parts[0]);
                $label = $labels[0];
                $assoc_list[$label] = $item;

            }

        return $assoc_list;
    }

    function _get_module_config($module = NULL)
    {
        global $cck,$settings;

        // get information from main system settings file
        $existing_controllers = $settings['system']['controllers']['value'];

        // remove usage of $settings variable in system or previous configuration call array
        unset($settings);

        $module_path =  DOCROOT .  DIRECTORY_SEPARATOR . $existing_controllers . DIRECTORY_SEPARATOR . $module;

        $name = basename($module_path);
        $file = $module_path . '/' . $module .  "_config.inc";

        if(file_exists($file))
        {
            $module_settings = include($file);
            return $module_settings;
        }

        return FALSE;
    }

	function _get_controller()
	{
		global $settings;
		$path = $_SERVER['QUERY_STRING'];
		$path_parts = explode('/', $path);

        // check length
        $path_part_count = count($path_parts);
		$suffix = '';

            $suffixes = array_flip($settings['developer']['module_files']);
			if(in_array($path_parts[0], $suffixes) && $path_part_count > 2)
			{
				$controller['suffix'] = (isset($path_parts[0]) ? $path_parts[0] : '');
				$controller['namespace'] = (isset($path_parts[1]) ? $path_parts[1] : '');
				$controller['class'] = (isset($path_parts[1]) && isset($path_parts[0])? $path_parts[1] . '_' . $path_parts[0] : '');
				$controller['method'] = (isset($path_parts[2]) ? $path_parts[2] : '');

			}
			else{
				$controller['suffix'] = $suffix;
				$controller['class'] = (isset($path_parts[0]) ? $path_parts[0] : '');
				$controller['method'] = (isset($path_parts[1]) ? $path_parts[1] : '');
			}
		foreach ($path_parts as $word)
		{
		}

		return $controller;
	}


    function _get_name_controller($classname)
    {
        $controller = (new ReflectionClass($classname))->getShortName();
        $segments = explode('_', $controller);
        $realname = implode('/', array_reverse($segments));

        return $realname;
    }

	function _query_segment()
	{
			$path = $_SERVER['QUERY_STRING'];
			$query[$path] = explode('/', $path);
			$get_last = array_reverse($query[$path]);
			$queryParts = explode('&', $get_last[0]);
			$params = array();
		
		    
			foreach ($queryParts as $param)
			{				
				$pos = strpos($param, '=');

				// Note our use of ===.  Simply == would not work as expected
				// because the position of 'a' was the 0th (first) character.
				if ($pos === false) {
				    //
				} else {
				    $item = explode('=', $param);
					$params[$item[0]] = $item[1];
				}
				
			}
			
			if(!empty($parameter) && isset($parameter))
			{
				return $params[$parameter];
			}
			else
			{
				return $params;
			}
	}

    function _set_action($caller, $reciever = 'submit')
    {
        global $cck;
        $method = explode('_', $caller);
        $suffix = array_pop($method);
        $method[] = $reciever;
        $action = implode('_', $method);

        return $action;
    }
	
	function _add_css($links, $template = NULL)
	{
		global $settings;
		global $cck;

        $output = '';
        $section_sort_key = 1;
        $section_sort_array = array();

        // add links to external  stylesheets
        // since this is an array the links are added in the sort order set by the keys

        foreach($links as $section => $css)
        {
            //print $section;
            $variables['path'] = $css['link'];
            $output .= $cck->_view('link_stylesheet', $variables) . "\n";

        }

        // add styles via the  on page HTML tag
        // since this is an array the HTML tag sets are added in the sort order set by the keys

        foreach($links as $section => $css)
        {
            //print $section;

            $variables['code'] = (isset($css['inline']) ? $css['inline'] : '');
            $output .= $cck->_view('inline_stylesheet', $variables) ."\n";
        }

        return $output;
	}
	
	function _add_js($links=null, $template = NULL)
	{
        global $settings;
		global $cck;

        $javascript = $cck->_hooks('hook_js');

        $output = '';
        $section_sort_key = 1;
        $section_sort_array = array();

        //exit($cck->_debug($links));

        foreach($links['js'] as $js)
        {
            //print $section;
            if(isset($js['link']) && !empty($js['link']))
            {
                $variables['path'] = $js['link'];
                $output .= $cck->_view('link_javascript', $variables) . "\n";
            }

        }

        // add javascript via the  on page HTML tag
        // since this is an array the HTML tag sets are added in the sort order set by the keys

        foreach($links['js'] as  $js)
        {
            //print $section;
            if(isset($js['inline']) && !empty($js['inline']))
            {
                $variables['code'] = $js['inline'];
                $output .= $cck->_view('inline_javascript', $variables) . "\n";
            }


        }

        return $output;
	}
	
	function _dbconnect($datasource = NULL)
	{
		global $settings;

        if(!$datasource )
        {
            $datasource = 'datasource_default';
        }

        $connect = $settings['connections'][$datasource];
        $connect_type = $settings['connections'][$datasource]['type'];

        switch($connect_type)
        {
            case 'sqlite3':

                $hostname = $connect['hostname'];
                $dbname = $connect['resource'];

                try
                {

                    $pdo = new PDO('sqlite:' . $hostname . $dbname);
                    return $pdo;
                }
                catch (PDOException $e) {
                    echo "Failed to get DB handle: " . $e->getMessage() . "\n";
                    exit;
                }
                break;
            case 'mysqli':

                $connect = $settings['connections'][$datasource];

                try
                {
                    $hostname = $connect['hostname'];
                    $username = $connect['username'];
                    $pw = $connect['pwd'];
                    $dbname = $connect['resource'];

                    $pdo = @new PDO ("mysql:host=$hostname;dbname=$dbname","$username","$pw");
                    return $pdo;
                }
                catch (PDOException $e) {
                    echo "Failed to get DB handle: " . $e->getMessage() . "\n";
                    echo "opening default @ localhost \n";
                    $connect = $settings['connections']['localhost'];
                    $hostname = $connect['hostname'];
                    $username = $connect['username'];
                    $pw = $connect['pwd'];
                    $dbname = $connect['resource'];
                    $pdo = new PDO ("mysql:host=$hostname;dbname=$dbname", "$username", "$pw");
                    return $pdo;
                }
                break;
            case 'mysql':
                $connect = $settings['connections'][$datasource];

                try
                {
                    $hostname = $connect['hostname'];
                    $username = $connect['username'];
                    $pw = $connect['pwd'];
                    $dbname = $connect['resource'];

                    $pdo = @new PDO ("mysql:host=$hostname;dbname=$dbname","$username","$pw");
                    return $pdo;
                }
                catch (PDOException $e) {
                    echo "Failed to get DB handle: " . $e->getMessage() . "\n";
                    echo "opening default @ localhost \n";
                    $connect = $settings['connections']['localhost'];
                    $hostname = $connect['hostname'];
                    $username = $connect['username'];
                    $pw = $connect['pwd'];
                    $dbname = $connect['resource'];
                    $pdo = new PDO ("mysql:host=$hostname;dbname=$dbname", "$username", "$pw");
                    return $pdo;
                }
                break;
        }


		//print_r($connect);
		//



	}


    /**
     * @param null $hook
     * @param null $type
     * @return array
     *
     *  Build an array from the result of each method called by controller
     *  by default the main controller for each module is called. A section or "controller type"
     *  can be used to call hooks in that section ie. Setting the $type parameeter to [admin] will
     *  call the hook in all modules with a controller named [controller name]_[admin]. Look in the
     *  code for admin.class.inc method main() for an example.
     */
	function _hooks($hook = NULL, $type = NULL)
	{
        global $cck, $settings;

        if(isset($settings['developer']['hooks'][$hook]) && $settings['developer']['hooks'][$hook]== TRUE) {


            $output = array();

            foreach ($this->_modules_list as $module) {
                try {


                    if ($type != NULL) {
                        //$module = explode('/', $module);
                        $namespace = $module . '_' . $type;
                    } else {
                        $namespace = $module . '\\' . $module;
                    }

                    if (class_exists($module) == TRUE) {
                        $Class = new ReflectionClass($module);
                    } elseif (class_exists($namespace) == TRUE) {
                        $Class = new ReflectionClass($namespace);
                    } elseif (class_exists($module . '\\' . $module . '_' . $type) == TRUE) {
                        $Class = new ReflectionClass($module . '\\' . $module . '_' . $type);
                    }

                    if (isset($Class) && $Class->hasMethod($hook)) {
                        $Method = new ReflectionMethod($Class->getName(), $hook);
                        if ($Method->isStatic()) {
                            continue;
                        } else {
                            $Instance = $Class->newInstance();
                            $item[$module] = $Method->invoke($Instance);
                            $output = array_merge($output, $item);
                        }
                    } else {
                        //exit('[' .$hook . '] hook not found in  '.$Class.' check configuration');
                        continue;
                    }

                } catch (Exception $e) {
                    exit('[' .$hook . '] hook not found in  '.$e->getMessage().' check configuration');
                    continue;
                }

            }
        }
        else
        {
            exit('[' .$hook . '] hook not found check configuration');
        }
		
		return $output;
	}

    /**
     * @param null $method
     * @param array $output
     * @return array
     * gather hooks by a common existing method name
     */
    function _userhooks($method = NULL, $output = array())
	{
		return $output;
	}

    /**
     * @param null $user_id
     * @param array $permissions
     * @return bool
     *
     *  Place  this function in the method/action that will be access protected
     *  To protect all methods of the controller place it in the __construct of
     *  that controller.
     *
     *  This method only looks for the logged in users session list.  Another modules controllers
     *  has to be responsible for the creation and placement of the permissions list
     *  This can be changed in the config.inc settings file.
     *
     *
     *
     */
    function _user_access()
    {
        global $cck,$settings;

        // look for the ACL settings in the config.inc file
        $user = session_id();
        if
        (   isset($_SESSION['login_user']) &&
            isset($_SESSION['login_user'][$user]['valid']) &&
            $_SESSION['login_user'][$user]['valid'] == TRUE)
        {
            return TRUE;
        }
        else
        {
            //
            //$form = new \users\users_form();
            //$show_form = $form->users_login_form();
            //$variables['page_title'] = 'Sign in' ;
            //$variables['content'] = $show_form ;
            //print $cck->_view('page_login', $variables);
            //return;

        }
        return FALSE;
    }

    function _user_access_denied()
    {
        global $cck;


            $variables['content'] = 'login please';
            print $cck->_view('page_login', $variables);
            exit;



    }

    /**
     * Function to create and display error and success messages
     * @access public
     * @param string session name
     * @param string message
     * @param string display class
     * @return string message
     *
     *  CSS classes are used to set message type.  Default types are success, notice and error
     */
    function _message_set( $name = 'notice', $message = NULL, $class = NULL)
    {
        global $cck, $settings;

        if ($message) {
            if (!isset($_SESSION ['messages'][$name])) {
                $_SESSION ['messages'][$name]['text'] = array();
                $_SESSION ['messages'][$name]['class'] = '';
                $_SESSION ['messages'][$name]['started'] = time();
                $_SESSION ['messages'][$name]['timeout'] = $settings['site']['message_timeout']['value'];
            }

            if (!in_array($message, $_SESSION ['messages'][$name])) {
                $_SESSION ['messages'][$name]['text'][] = array('message' => $message);
                $_SESSION ['messages'][$name]['class'] = $class;
                $_SESSION ['messages'][$name]['started'] = time();
                $_SESSION ['messages'][$name]['timeout'] = $settings['site']['message_timeout']['value'];
            }

        }

        // return all
    }

    /**
     * @param null $name
     * @param null $message
     * @param null $clear
     * @return string
     *
     *
     */
    function _message_get( $name = NULL, $message = NULL, $clear = NULL )
    {
        global $cck, $settings;
        //We can only do something if the name isn't empty

        $view = 'messages';
        //$template_path = DOCROOT . DIRECTORY_SEPARATOR . '_views' . DIRECTORY_SEPARATOR  . 'messages' . '.tpl.php';

        $template_path = DOCROOT . DIRECTORY_SEPARATOR .
            $settings['system']['themes']['value'] .  DIRECTORY_SEPARATOR . $settings['site']['theme']['value'] .
            DIRECTORY_SEPARATOR . $view . '.tpl.php';

        if($name)
        {
            $messages = (isset($_SESSION ['messages'][$name]) ? $_SESSION ['messages'][$name] : NULL);
            $variables['name'] = $name;
            $variables['messages'] = $messages;
            $output = $cck->_form_process($template_path, $variables);
            $_SESSION['kill_messages'] = array($name);
        }
        else
        {
            $messages = (isset($_SESSION ['messages']) ? $_SESSION ['messages'] : NULL);
            $variables['css_class'] = (isset($messages[$name]['class']) ? $messages[$name]['class'] : 'notice');
            $variables['messages'] = $messages;
            $output = $cck->_form_process($template_path, $variables);
            $_SESSION['kill_messages'] = array();

        }

        return $output;


    }

    /**
     * @param null $text
     * @param null $character
     * @return mixed|null|string
     *
     *  Over kill cleaner: remove the user input text and replace underscore character with space
     *
     */
	function _plain_text($text = NULL, $exception = NULL)
	{
		global $cck;

        // remove tags
        $text = $cck->_xss_clean($text);

        // strip normal tags
        $text = strip_tags($text);

        // remove and replace underscore
        $text = preg_replace('/[^a-zA-Z0-9 _\/?&\.@:]/s', '', $text);

        // remove an exception to allowed characters replace with space
        $text = preg_replace('/[^a-zA-Z0-9'.$exception.']/s', ' ', $text);

        // remove any hex dex character interpretations
        $text = preg_replace('/0x[0-9a-fA-F]{6}/', '', $text);

        // again remove special characters
        $text = filter_var($text, FILTER_SANITIZE_STRING);

        //trim whitespace
        $text = trim($text);

        return $text;
	}

    /**
     * Remove HTML tags, including invisible text such as style and
     * script code, and embedded objects.  Add line breaks around
     * block-level tags to prevent word joining after tag removal.
     */
    function _strip_html_tags($text = NULL)
    {
        // Remove invisible content
        $text = preg_replace(
            array(
                //ADD a (') before @<head ON NEXT LINE. Why? see below
                '#<head[^>]*?>.*?</head>#siu',
                '#<style[^>]*?>.*?</style>#siu',
                '#<script[^>]*?.*?</script>#siu',
                '#<object[^>]*?.*?</object>#siu',
                '#<embed[^>]*?.*?</embed>#siu',
                '#<applet[^>]*?.*?</applet>#siu',
                '#<noframes[^>]*?.*?</noframes>#siu',
                '#<noscript[^>]*?.*?</noscript>#siu',
                '#<noembed[^>]*?.*?</noembed>#siu',
                // Add line breaks before and after blocks
                '@</?((address)|(blockquote)|(center)|(del))@iu',
                '@</?((div)|(h[1-9])|(ins)|(isindex)|(p)|(pre))@iu',
                '@</?((dir)|(dl)|(dt)|(dd)|(li)|(menu)|(ol)|(ul))@iu',
                '@</?((table)|(th)|(td)|(caption))@iu',
                '@</?((form)|(button)|(fieldset)|(legend)|(input))@iu',
                '@</?((label)|(select)|(optgroup)|(option)|(textarea))@iu',
                '@</?((frameset)|(frame)|(iframe))@iu',
            ),
            array(
                ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
                "\n\$0", "\n\$0", "\n\$0", "\n\$0", "\n\$0", "\n\$0",
                "\n\$0", "\n\$0",
            ),
            $text );
        return strip_tags( $text );
    }

    function _normalize_string($s = NULL)
    {
        // Normalize line endings
        // Convert all line-endings to UNIX format
        $s = str_replace("\r\n", "\n", $s);
        $s = str_replace("\r", "\n", $s);
        // Don't allow out-of-control blank lines
        $s = preg_replace("/\n{2,}/", "\n\n", $s);

        return $s;
    }

    /**
     * @param null $string
     * @return mixed|null|string
     *
     * This is a helper function make text that is unformatted via HTML but has line break formatting from
     * textareas to become readable after retrieval from the database
     */
    function _readable_string($string = NULL)
    {
        $string = $this->_normalize_string($string);
        $string = preg_replace('/\n{2,}/', "</p><p>", trim($string));
        $string = preg_replace('/\n/', '<br>',$string);
        $string = "<p>{$string}</p>";

        return $string;
    }

    /**
     * @param $var
     * @return string
     * utility method used in development and debugging
     * breaks the rule of not using HTML within the controller
     * @TODO change to use $cck->_view() and HTML template
     */
    function _debug($var)
    {
        if(isset($var))
        {
            return '<pre style="clear:both" class="debug errors data">'. print_r($var,1) . '</pre>';
        }
        return FALSE;
    }

    function _convert_bytes($size)
    {
        $unit=array('b','kb','mb','gb','tb','pb');
        return @round($size/pow(1024,($i=floor(log($size,1024)))),2).' '.$unit[$i];
    }

    function _global_info()
    {
        return 'add to this global object ';
    }

    /**
     * @param null $template
     * @param array $variables
     * @return bool|null|string
     *
     */
	function _link($template = NULL, $variables = array())
	{
        global $cck, $settings;

        // set the base url and directory for links
        $variables['base_url'] = $settings['system']['base_url']['value'];
		$approot = substr(dirname(__FILE__),strlen($_SERVER['DOCUMENT_ROOT']));
		$variables['directory'] = $approot  ;//. $ini_settings['url']['directory'];
		$output =  $this->_view($template, $variables);

		return $output;
	}

    /**
     * @param $menu
     * @param null $template
     * @param array $other
     * @return bool|null|string
     *
     */
	function _menu_links($menu, $template = NULL, $other = array())
    {
        global $cck, $settings;
        //
        $section_sort_key = 1;
        $section_sort_array = array();

        foreach($menu as $section => $group)
        {
            //print $section;
            if(isset($group['links']) && is_array($group['links']))
            {
                foreach($group['links'] as $key => $value)
                {

                    // Base url and directory
                    // check for  access
                    if(array_key_exists('access', $value))
                    {
                        if($value['access'] == FALSE)
                        {
                            continue;
                        }
                    }

                    if(array_key_exists('weight', $value))
                    {

                        $list[$section]['weight'] = $value['weight'];
                        $list[$section]['section'] = $section;
                        $list[$section][] = $this->_link('links', $value);
                        $section_sort_array[$list[$section]['weight']] = $list[$section];


                    }
                    else
                    {
                        $list[$section]['weight'] = 0;
                        $list[$section]['section'] = $section;
                        $list[$section][] = $this->_link('links', $value);
                        $section_sort_array[$section_sort_key] = $list[$section];


                    }

                    $section_sort_key++;
                }
            }


        }
        //$variables['menu_index'] = $index;
        ksort($section_sort_array);

        foreach($section_sort_array as $weight => $sorted)
        {
            $sorted_list[$sorted['section']] = $sorted;

            // clean out sorting tools from array
            unset($sorted_list[$sorted['section']]['section']);
            unset($sorted_list[$sorted['section']]['weight']);
        }

        //check for additional variables list in $other
        if(!empty($other))
        {
            foreach($other as $var => $val)
            {
                $variables[$var] = $val;
            }
        }

        $variables['links'] = $sorted_list;
        //$variables['separator'] = $separator;

        //print '<pre>'. print_r($sorted_list,1) . '</pre>';
        $output =  $this->_view($template, $variables);

        return $output;
}

    /**
     * @param $menu
     * @param array $attributes
     * @param array $local
     * @return bool|null|string
     *
     * $local parameter is to add local links to the sub menu that are visible only while inside of a controller
     * methods area
     */
	function _module_links($menu, $attributes = array(), $local = array())
	{
		$list = array();
        if(!empty($local))
        {
            $menu['links'] = array_merge($menu['links'], $local);
        }
    	//print '<pre>' . print_r($links, 1) . '</pre>';
            foreach($menu['links'] as $link)
            {
                // Base url and directory
                // check for  access
                if(array_key_exists('access', $link))
                {
                    if($link['access'] == FALSE)
                    {
                        continue;
                    }
                }
                if(array_key_exists('weight', $link))
                {
                    $list[$link['weight']] = $this->_link('links', $link);
                }
                else
                {
                    $list[] = $this->_link('links', $link);

                }
            }

        ksort($list);
        //print '<pre>'. print_r($list,1) . '</pre>';
    	$variables['menu_index'] = $attributes['index'];
    	$variables['links'] = $list;
    	$output =  $this->_view($attributes['template'], $variables);
    	 
    	return $output;
	}


    /**
     * @param $blocks
     * @param null $template
     * @param null $index
     * @return bool|string
     *
     *  Process the  hook_blocks() function in all activated modules
     *  returns html from the designated template file asked for by the calling
     *  method. All blocks are returned. To get the block set from an individual module
     *  set the index to that modules name.
     *
     *  example:
     *  $blocks = $cck->_hooks('hook_blocks');// call blocks from controllers
     *  $variables['site_blocks_left'] = $cck->_blocks($blocks, 'block'). 'override in portfolio'; // set called content
     *  array into _block() function then to page variable for presentation
     */
    function _blocks($blocks = array(), $template = NULL, $index = NULL)
    {

        global $cck;
        $list = array();
        $template_path = DOCROOT . DIRECTORY_SEPARATOR . '_views' . DIRECTORY_SEPARATOR . 'blocks' . DIRECTORY_SEPARATOR . $template . '.tpl.php';

        if (file_exists($template_path) == false)
        {
            trigger_error("Template {$template} not found in ". $template_path);
            return false;
        }

        //print '<pre>' . print_r($blocks, 1) . '</pre>';
        foreach($blocks as $delta => $module_blocks)
        {
            foreach($module_blocks as $key => $block)
            {
                //print '<pre>' . print_r($block, 1) . '</pre>';
                $block['delta'] = $delta.'-'. $key;
                if(array_key_exists('weight', $block))
                {
                    $list[$block['weight']] = $cck->_template($template_path, $block);
                }
                else
                {
                    $list[] = $cck->_template($template_path, $block);

                }
            }

        }

        ksort($list);
        $output = implode("\n", $list);

        return $output;
    }

    /**
     * @param null $form
     * @param null $template
     * @return bool|string
     *  this function works by using tail recursion in a switch statement
     *  any additional output added to the loop will appear after each form element
     *
     *  This method adds a security csrf token field and matching session token to all forms.
     *
     *  Required fields are marked via the existence of variable creted for the template for that field
     *  the variable can also contain a boolean but it is not necessary. This logic is to
     *  make it easy for developers to match both the code and database generated field attributes
     */

	function _form($form = NULL, $template = NULL)
	{
		global $cck,$settings;

        $token = '';
        $output = '';
		$options = '';
		$group = '';
		$grps = '';
		$in_fieldset = array();



		$template_path =
            DOCROOT .
            DIRECTORY_SEPARATOR . $settings['system']['themes']['value'].
            DIRECTORY_SEPARATOR .$settings['site']['theme']['value'] .
            DIRECTORY_SEPARATOR . 'html' .
            DIRECTORY_SEPARATOR . $template . '.tpl.php';

		if (file_exists($template_path) == false)
		{
			trigger_error("Template {$template} not found in ". $template_path);
			return false;
		}


		if(!empty($form['elements']))
		{
			// add security element
			$attributes = array();

            $form['elements']['formname'] =
                array(
                    'type' => 'hidden',
                    'name' => 'formname',
                    'value' => $form['name'],
                );
            $form['elements']['errors'] =
                array(
                    'type' => 'hidden',
                    'value' => '',
                    'name'=> 'errors',
                );
            /*$form['elements']['security'] =
                array(
                    'type' => 'hidden',
                    'name' => 'security',
                    'value' => $token
                );*/

            // lookup required elements for validation on submission
            $require_these = array();
            foreach($form['elements'] as $key => $element)
            {
                if(isset($element['required']))
                {
                    $require_these[]= $element['name'];
                }
            }

            $form['elements']['validation'] =
                array(
                    'type' => 'hidden',
                    'value' => implode(',',$require_these),
                    'name'=> 'validation',
                );

			// search for fieldset items
			foreach($form['elements'] as $type)
			{
                if(isset($type['type']))
                {
                    $attributes['type'] = $type['type'];
                    if($type['type'] == 'fieldset')
                    {

                        $in_fieldset[] = key($form['elements']);

                    }
                }


			}

            // Write the generated token to the session variable to check it against the hidden field when the form is sent
            //$element_info['token'] = $token;


            // previous submission of  from fill in values
            // Write list of acceptable post variable names
            //unset($_SESSION[$form['name'].'_'. session_id()]);



			foreach($form['elements'] as $key => $element)
			{
                // skip items in fieldsets
				if(in_array($key, $in_fieldset) || !isset($element['type'])){

					continue;
				}


				switch($element['type'])
				{
					case 'text':
						$output .= $cck->_form_element($element, 'html_form_text');
						break;
					case 'textarea':
						$output .= $cck->_form_element($element, 'html_form_textarea');
						break;
					case 'password':
						$output .= $cck->_form_element($element, 'html_form_password');
						break;
					case 'radio':
						$output .= $cck->_form_element($element, 'html_form_radio');
						break;
					case 'checkbox':
						$output .= $cck->_form_element($element, 'html_form_checkbox');
						break;
					case 'select':
						$list = '';
						foreach($element['options'] as $item)
						{
							if(isset($item['group']) && $item['group'] !=='')
							{
								$options[$item['group']][] = $cck->_form_element($item,'html_form_select_option');
							}
							else
							{
								$options['nogroup'][] = $cck->_form_element($item,'html_form_select_option');
							}

						}
						if(isset($element['optgrp']))
						{
							foreach($element['optgrp'] as $section => $grp)
							{
								foreach($options[$section] as $value)
								{
									$grp['options'] .= $value;
								}

								$grps[$section][] = $cck->_form_element($grp,'html_form_select_group_option');

								//print $section;
							}
							foreach($grps as $listitem)
							{
								$list .= $listitem[0];
							}
						}


						//merge list
						foreach($options['nogroup'] as $listoption)
						{
							$list .= $listoption;
						}

						//print '<pre>' .print_r($grps,1) . '</pre>';
						//print '<pre>' .print_r($options,1) . '</pre>';

						// set new value to string
						$element['options'] = $list;
						$output .= $cck->_form_element($element, 'html_form_select');
                        // unset variable to be used by next list
                        unset($element['options'],$options);
						break;
					case 'fieldset':
						foreach ($element['grouped'] as $groupitem)
						{
							$group .= $cck->_form_element($groupitem, 'html_form_'. $groupitem['type']);

						}

						$element['grouped'] = $group;
						$output .= $cck->_form_element($element, 'html_form_fieldset');

						break;
					case 'optgrp':
						$output .= $cck->_form_element($element, 'html_form_select_group_option');
						break;
					case 'option':
						$output .= $cck->_form_element($element, 'html_form_select_option');
						break;

					case 'hidden':

						$output .= $cck->_form_element($element, 'html_form_hidden');
						break;

					case 'image':
						$output .= $cck->_form_element($element, 'html_form_image');
						break;
					case 'reset':
						$output .= $cck->_form_element($element, 'html_form_reset');
						break;
					case 'button':
						$output .= $cck->_form_element($element, 'html_form_button');
						break;
					case 'submit':
						$output .= $cck->_form_element($element, 'html_form_submit');
						break;
					case 'file':
						$output .= $cck->_form_element($element, 'html_form_file');
						break;
					case 'number':
						$output .= $cck->_form_element($element, 'html_form_number');
						break;
					case 'date':
						$output .= $cck->_form_element($element, 'html_form_date');
						break;
					case 'color':
						$output .= $cck->_form_element($element, 'html_form_color');
						break;
					case 'range':
						$output .= $cck->_form_element($element, 'html_form_range');
						break;
					case 'month':
						$output .= $cck->_form_element($element, 'html_form_month');
						break;
					case 'week':
						$output .= $cck->_form_element($element, 'html_form_week');
						break;
					case 'time':
						$output .= $cck->_form_element($element, 'html_form_time');
						break;
					case 'datetime':
						$output .= $cck->_form_element($element, 'html_form_datetime');
						break;
					case 'datetime-local':
						$output .= $cck->_form_element($element, 'html_form_datetime_local');
						break;
					case 'email':
						$output .= $cck->_form_element($element, 'html_form_email');
						break;
					case 'search':
						$output .= $cck->_form_element($element, 'html_form_search');
						break;
					case 'tel':
						$output .= $cck->_form_element($element, 'html_form_tel');
						break;
					case 'url':
						$output .= $cck->_form_element($element, 'html_form_url');
						break;
                    case 'html':
                        $output .= $cck->_form_element($element, 'html_form_html');
                        break;
				}





			}
            //echo  $form['elements']['formname']['value'].'('.$count .'='. $countdown.')';

            //echo '('.$count .'='. $countdown.')';


		}

        // get errors from previous submission
        $tokenx = (isset($_SESSION[$form['elements']['formname']['value'].'_'. session_id()]['form_token'])? $_SESSION[$form['elements']['formname']['value'].'_'. session_id()]['form_token']: '');
        if($tokenx == '')
        {
            $salt = sha1(md5(session_id()));
            $tokenx = md5(uniqid(microtime(), true) . $salt);
            $tokenx = $form['elements']['formname']['value'] . '_' . $tokenx;
            $_SESSION[$form['elements']['formname']['value'] . '_' . session_id()]['form_token'] = $tokenx;
        }
        $secure =
                array(
                    'type' => 'hidden',
                    'name' => 'security',
                    'value' => $tokenx
                );

        $output .= $cck->_form_element($secure, 'html_form_hidden');

		$form['elements'] = $output ;


		$output = $cck->_form_process($template_path, $form);


		return $output;

	}

    function _form_element($element, $template)
    {
        global $cck,$settings;

        //$template_path = DOCROOT . DIRECTORY_SEPARATOR . '_views' . DIRECTORY_SEPARATOR . 'html' . DIRECTORY_SEPARATOR . $template . '.tpl.php';

        $template_path =
            DOCROOT .
            DIRECTORY_SEPARATOR . $settings['system']['themes']['value'].
            DIRECTORY_SEPARATOR .$settings['site']['theme']['value'] .
            DIRECTORY_SEPARATOR . 'html' .
            DIRECTORY_SEPARATOR . $template . '.tpl.php';
        $output = $cck->_form_process($template_path, $element);
        return $output;
    }

    /**
     * @param array $form_submission
     * @return bool
     *
     * validation of form fields based on array key "required" set as true
     * in form array stack. Errors are added to the forms Session security token used when
     * building the form on page for the user.
     */
    function _form_validate($form_submission = array(), $success=NULL)
    {
        global $cck, $settings;

        // filter submisssion methods
        $method = $_SERVER['REQUEST_METHOD'];
        $request = explode("/", substr(@$_SERVER['PATH_INFO'], 1));

        switch ($method) {
            case 'PUT':
                exit($method . ' not allowed');
                break;
            case 'GET':
                //unset($_GET);
                break;
            case 'HEAD':
                exit($method . ' not allowed');
                break;
            case 'DELETE':
                exit($method . ' not allowed');
                break;
            case 'OPTIONS':
                exit($method . ' not allowed');
                break;

        }

        // if security token not found or no match stop csrf attack
        $token_to_match = (isset($_SESSION[$form_submission['formname'].'_'. session_id()]['form_token']) ? $_SESSION[$form_submission['formname'].'_'. session_id()]['form_token'] : '');
        $token = $form_submission['security'];
        if($token_to_match == $token)
        {
            $cck->_message_set('notice','Form security check passed', 'success');
            unset($_SESSION[$form_submission['formname'].'_'. session_id()]['form_token']);
        }
        else
        {
            $cck->_message_set('notice','Form security check failed', 'error');
            unset($_SESSION[$form_submission['formname'].'_'. session_id()]['form_token']);
            return false;
        }

        $key = $form_submission['formname'];

        // validation list is stored in session
        $validation = (isset($_SESSION[$key.'_'. session_id()]) ? $_SESSION[$key.'_'. session_id()]: '' );
        $form_submission['form'] = NULL;

        ///////////////////////////777
        $errors = 0;
       $output = 'Posted form fields: <pre>'. print_r($form_submission, 1) . '</pre>';


        $validate = explode(',', $form_submission['validation']);
        foreach($validate as $item)
        {
            $element = explode('[', $item);
            // check for form names in array format and break out
            if(isset($element[1]))
            {
                $key = str_replace(']','', $element[1]);
                $required[$element[0]][$key] = '';
            }
            else
            {
                $required[$element[0]] = '';
            }
        }

        $output .= 'Required fields: <pre>'. print_r($required,1) . '</pre>';

        $output .= ''. "\n";

        foreach($required as $for => $form_element)
        {
            if(is_array($form_element))
            {
                foreach($form_element as $validate => $value)
                {
                    if(isset($form_submission[$for][$validate]) && $form_submission[$for][$validate]  == '')
                    {
                        $output .= 'error: ' . $validate . " empty.\n";
                        $errors++;

                    }

                }

            }
            else
            {
                if(isset($form_submission[$for]) && $form_submission[$for]  == '')
                {
                    $output .= 'error: ' . $for . " empty.\n";
                    $errors++;
                }

            }



        }

        ///////////////////////////7777


        if($errors > 0)
        {
            //
            //
            $output .= $cck->_debug($_SESSION);
            $_SESSION[$form_submission['formname'].'_'. session_id()] = '';
            $cck->_message_set('notice',$output, 'error');
            return $output;
        }
        else
        {
            //return $output . $_SESSION[$form_submission['formname'].'_'. session_id()]['form_elements']['token'];
            $success = (isset($success)? $success : $form_submission['formname']. ' form validated and submitted.');
            $cck->_message_set('notice', $success , 'success');
            return TRUE;//
        }


    }

    function _form_get_message($form_name, $message_type = NULL)
    {
        global $cck;
        $message = (isset($_SESSION[$form_name . '_'. session_id()]) ? $_SESSION[$form_name . '_'. session_id()] : '');
        $template_path = DOCROOT . DIRECTORY_SEPARATOR . '_views' . DIRECTORY_SEPARATOR . 'html' . DIRECTORY_SEPARATOR .'html_form_error.tpl.php';

        switch($message_type)
        {
            case 'error':
                if(isset($message['form_elements']['errors']['form']))
                {
                    $errors['errors'] = $message['form_elements']['errors']['form'];
                    $message = $output = $cck->_template($template_path, $errors);
                    return $message;
                }

                break;


        }


    }

    function _file_write($filename = NULL, $content = '', $operation = NULL)
    {
        $filename = INI_FILENAME;

        if (is_writable($filename)){
            try
            {
                $completed = file_put_contents($filename, $content, LOCK_EX);
                if ($completed == FALSE) {
                    throw new Exception("Cannot write to ($filename). Possible permissions error?");
                }
                else
                {
                    $completed = 'Wrote ' . $completed . 'to  file.';
                }
            }
            //catch exception
            catch(Exception $e) {
                echo 'Message: ' .$e->getMessage() . "<br />\n";
                echo "The error occured on line: " . $e->getLine();
                exit;
            }

        }
        else
        {
            $completed = 'configuration file not writable';
        }

        return $completed;


    }

    /**
     * @param $text
     * @return mixed
     *
     *  general  function to keep  higher utf8 characters out of filenames e.g. German, Swedish
     *  language characters.
     */
    function _filename_clean_utf8($text)
    {
        $utf8 = array(
            '/[áàâãªä]/u'   =>   'a',
            '/[ÁÀÂÃÄ]/u'    =>   'A',
            '/[ÍÌÎÏ]/u'     =>   'I',
            '/[íìîï]/u'     =>   'i',
            '/[éèêë]/u'     =>   'e',
            '/[ÉÈÊË]/u'     =>   'E',
            '/[óòôõºö]/u'   =>   'o',
            '/[ÓÒÔÕÖ]/u'    =>   'O',
            '/[úùûü]/u'     =>   'u',
            '/[ÚÙÛÜ]/u'     =>   'U',
            '/ç/'           =>   'c',
            '/Ç/'           =>   'C',
            '/ñ/'           =>   'n',
            '/Ñ/'           =>   'N',
            '/–/'           =>   '_', // UTF-8 hyphen to "normal" hyphen
            '/[’‘‹›‚]/u'    =>   '', // Literally a single quote
            '/[“”«»„]/u'    =>   '', // Double quote
            '/ /'           =>   '', // nonbreaking space (equiv. to 0x160)
        );
        return preg_replace(array_keys($utf8), array_values($utf8), $text);
    }

    function _api_test()
	{
		print 'Services are working. Ask for a token by connecting  to a resource using: <em>[module name]/services/[response type]/{class}/{method}</em>';
	}

	/**
	 * @param $class
	 * @param $action
	 * @param $format
	 * @param $arguments
	 *
	 * All requests require two trips the first to aquire a CSRF token, The secound to
	 * make the actual call using the token. This does slow the system usage. But better safe than
	 * hacked.
	 * TODO: make the CSRF token request an option in config.inc
	 */
	function _api_request($class,$action,$format,$arguments)
	{
		// The method (GET, POST, PUT or DELETE) of the request
		$method = $_SERVER['REQUEST_METHOD'];
		$query = $_SERVER['QUERY_STRING'];
		parse_str($query, $arguments);
		$body = file_get_contents("php://input");

		// set content type to default when server variable empty
		$content_type = 'text/html';
		$parameters = array();

		// since not all browsers and clients are RESTful this might be ignored
		if(isset($_SERVER['CONTENT_TYPE'])) {
			$content_type = $_SERVER['CONTENT_TYPE'];
		}

		//$method. print_r($request,1)print $format;
		switch ($format) {
			case 'xml':
				header('Content-type: application/xml');
				break;
			case 'html':
				header('Content-type: text/html');
				break;
			case 'text':
				header('Content-type: text/plain');
				break;
			case 'json':
				header("Content-type: application/json; charset=utf-8");
				header("access-control-allow-origin: *");
				//echo $_GET['callback'];
				break;
			case 'image':
				header('Content-type: image/jpeg');
				break;
			case 'pdf':
				header('Content-type: application/pdf');
				break;
			case 'php':
				header('Content-type: text/plain;; charset=utf-8');
				break;
			default:
				// Otherwise, bad request
				header('status: 400 Bad Request', true, 400);
				$response = 'Bad Request Header';
				break;
		}

		$parameters = $this->_api_parse_request($body,$content_type);

		// check for first empty call to query and body and return token for client use
		// if body with token and/or query tap resource and build response
		if(empty($query) && empty($body))
		{
			$response_data = $this->_api_request_token_create();
			$response  = $this->_api_response_build($format,$response_data);
			exit($response);
		}
		else
		{
			$authorized = $this->_api_request_token_validate();

			// the resource request names are sent here from the _router() after sniffing URI
			$resource = new $class();
			$response_data = $resource->$action($method,$format,$parameters,$arguments);

			// the response format is validated internally
			$response = $this->_api_response_build($format,$response_data);
			exit($response);
		}


	}

	/**
	 *  parse and validate the content and content type of the request
	 */
	function _api_parse_request($body = NULL,$content_type = false)
	{
		$parameters = array();

		switch($content_type) {

			case "text/html":
			case "application/json":
				$body_params = json_decode($body);
				if($body_params) {
					foreach($body_params as $param_name => $param_value) {
						$parameters[$param_name] = $param_value;
					}
				}
				break;
			case "application/x-www-form-urlencoded":
				parse_str($body, $postvars);
				foreach($postvars as $field => $value) {
					$parameters[$field] = $value;
				}
				break;
			default:
				// pass through
				break;
		}

		return $parameters;
	}



	// cross site forgery prevention create a session token
	function _api_request_token_create()
	{
		$index = user_password(16);
		$binarySalt = mcrypt_create_iv(64, MCRYPT_DEV_URANDOM);
		$token = substr(strtr(base64_encode($binarySalt), '+', '.'), 0, 48);
		$token = str_replace('/','',$token);
		$token = str_replace('\\','',$token);
		$token = str_replace('.','',$token);
		$token = $index .$token;
		return array('token' => $token);
	}

	// validate the request token for the session
	function _api_request_token_validate($data = NULL)
	{
		// get the token from the body or GET url
		// take the first 16 characters as the index key
		// find the SESSION by index key
		// compare the sent token string to session variable content string
		return FALSE;
	}


	function _api_response_build($type = NULL, array $data)
	{
		global $user;

		/*
         *  format response in accordance with uri call
         *  becomes the service mvc [module]/services/[response type]/{class}/{method}/{parameters}
         *  response types: JSON,XML,HTML,PHP,TEXT
         *  overrides the accept header which is not a trustworthy constant in all clients.
         *  this goes against RESTful concept but is Formless HTTP QUERY Kind.
         */
		switch($type)
		{
			case 'xml':
				$xml_data = new SimpleXMLElement("<?xml version=\"1.0\"?><data></data>");
				$this->_array_to_xml($data,$xml_data);
				$response = $xml_data->asXML();
				break;
			case 'json':
				$response =  json_encode($data, JSON_PRETTY_PRINT); // json encoded array
				break;
			case 'html':
				$response = '<!DOCTYPE html>' . $this->html($data); // html list
				break;
			case 'php':
				$response = var_export($data); // PHP code for with eval()
				break;
			case 'text':
				$response = print_r($data, 1); // readable array key value list for debug
				break;

		}

		return $response;

	}


    function _array_to_print ($varname, $varval, $section = NULL)
    {
        global $cck;
        static $output;
        static $count = 0;
        static $mark = '';


        // clean and set values
        if (!is_array($varval)):

            $text = var_export($varval, true);

            // clean text with the quote characters ' and " removed.
            $text = str_replace('"', '',$text);
            $text = str_replace("'", '',$text);

            // add string value quotes for parsable code
            $output .= $varname . ' = "' . $text . '"' . ";\n";

            $count--;
            if($count == 0):
                $output .= "//end " . $mark ."\n";
            endif;

            else:

            $count = count($varval);

            $output .=  "\n//" . $section .  "\n"; //' ' . $count . "\n";
            $mark = $section;

            foreach ($varval as $key => $val):

                $this->_array_to_print($varname . "[" . var_export($key, true) . "]", $val, $key);

            endforeach;

        endif;

        return $output ;

    }

    function _array_to_list($varname, $varval)
    {
        global $cck;
        static $list;

        if (!is_array($varval)):

            $list .= $varname . ' = ' . var_export($varval, true) . ";\n";

        else:
            //$output .=  $varname . " = array();\n";
            foreach ($varval as $key => $val):
                $this->_array_to_list($varname . "[" . var_export($key, true) . "]", $val);
            endforeach;

        endif;

        return $list;
    }

    function _array_to_item ($varval, $id = null)
    {
        global $cck;
        $output = $cck->_debug($varval). "\n";

        if (is_array($varval))
        {
            foreach ($varval as $key => $val):
                if (is_array($val)) {

                    $output .= "[" . var_export($key, true) . "]" ;
                    $output .= $this->_array_to_item ($val, var_export($key, true));
                }
                else
                {
                    $output .= $id. "[" . var_export($key, true) . "]";
                    $output .=  ' = '   . var_export($val, true) . ";\n";
                }

            endforeach;
            //$output .=  ' = '   . var_export($val, true) . ";\n";
        }



            return $output;



    }

	function _array_to_xml($data, &$xml_data) {
		foreach($data as $key => $value) {
			if(is_array($value)) {
				$key = is_numeric($key) ? "item_$key" : $key;
				$subnode = $xml_data->addChild("$key");
				$this->_array_to_xml($value, $subnode);
			}
			else {
				$key = is_numeric($key) ? "item_$key" : $key;
				$xml_data->addChild("$key","$value");
			}
		}
	}

	function _api_html($element,$parent = NULL)
	{
		if(!$parent) {
			$output = '<ul>';
		}
		else
		{
			$output = '';
		}
		foreach ($element as $key => $value) {

			if(is_array($value))
			{
				$output .=  $this->_api_html_children($key,$value);
			}
			else
			{
				if($parent)
				{
					$output .= "<li>";
					$output .= '<span>'. $parent . ' (' . $key . ') ' . '</span> : <span>' . $value . '</span>';
					$output .= "</li>" . "\n";
				}
				else
				{
					$output .= "<li>";
					$output .= '<span>' . $key . '</span> : <span>' . $value . '</span>';
					$output .= "</li>" . "\n";
				}


			}


		}
		if(!$parent) {
			$output .= "</ul>"  . "\n";
		}

		return $output;
	}


	function _api_html_children($key,$child)
	{
		$output = "<li>";
		$output .= $key ; // parent name

		if(!empty($child))
		{
			$output .= "<ul>";

			foreach($child as $i => $item)
			{
				if(is_array($item))
				{
					$output .= $this->html($item,$i);
				}
				else
				{
					$output .= "<li>";
					$output .= '<span>' . $i . '</span> : <span>' . $item . '</span>';
					$output .= "</li>" . "\n";
				}

			}
			$output .= "</ul>";
		}

		$output .= "</li>" . "\n";

		return $output;

	}

		/**
		 * This function will return only the methods for the object you indicate. It will strip out the inherited methods.
		*/
	function _get_class_methods($class){
			$array1 = get_class_methods($class);
			if($parent_class = get_parent_class($class)){
				$array2 = get_class_methods($parent_class);
				$array3 = array_diff($array1, $array2);
			}else{
				$array3 = $array1;
			}
			return($array3);
	}

	/**
	 * @return mixed
	 * get the first comment block from the top of the file
	 */
	function _get_file_documentation($class=NULL, $method=NULL)
	{

		$reflector = new ReflectionClass($class);

		// to get the Class DocBlock
		$fileDocComment = $reflector->getDocComment();

		// to get the Method DocBlock
		if($method)
		{
			$fileDocComment = $reflector->getMethod($method)->getDocComment();
		}

		return $fileDocComment;
		/*
		$docComments = array_filter(
				token_get_all( file_get_contents( __FILE__ ) ), function($entry) {
				return $entry[0] == T_DOC_COMMENT;
			}
			);
			$fileDocComment = array_shift( $docComments );
			return $fileDocComment[1];
		*/
	}

    function _fatal_error_handler()
    {
        global $cck;
        $error = error_get_last();
        if ($error['type'] == 1)
        {
            $output = 'There was a serious system error ending here.' . $cck->_debug($error);
            $variables['content'] = $output;
            print $cck->_view('page_404', $variables);
            //exit('ending error here');
        }
    }

    /**
     * @param string $type
     * @param $method
     * @param $class
     * @return bool
     *
     * To stop protected or static methods from being called by the router
     */
    function is_class_method($type="public", $method, $class) {

        global $cck;
        // $type = mb_strtolower($type);
        try
        {
            $reflection = new ReflectionMethod($class, $method);
            switch($type) {
                case "static":
                    if($reflection->isStatic())
                    {
                        $output = 'Calling this address can lead to unexpected results' ;
                        $variables['content'] = $output;
                        print $cck->_view('page_404', $variables);
                        exit('The address requested  is not accessible.');
                        //return $refl->isPrivate();
                    }
                    break;
                case "public":
                    return $reflection->isPublic();
                    break;
                case "private":
                    if($reflection->isProtected())
                    {
                        $output = 'The address requested  is protected.' ;
                        $variables['content'] = $output;
                        //print $cck->_view('page_404', $variables);
                        exit('The address requested  is protected.');

                    }

                    break;
            }

        }
        catch(Exception $e)
        {
            $output = 'The address requested does not exist in this website' ;
            $variables['content'] = $output;
            echo $cck->_view('page_404', $variables);
            exit();
        }

    }


    function _format_datetime($unix_timestamp = NULL, $formatstring = 'Y-m-d H:i:s')
    {
        global $cck, $settings;
        date_default_timezone_set($settings['site']['timezone']['value']);
        $date = date($formatstring, $unix_timestamp);
        return $date;
    }
    


    function _page($page = NULL, $template = NULL)
    {
        global $cck,$settings;
        $output = '';



        $template_path =
            DOCROOT .
            DIRECTORY_SEPARATOR . $settings['system']['themes']['value'].
            DIRECTORY_SEPARATOR .$settings['site']['theme']['value'] .
            DIRECTORY_SEPARATOR . 'html' .
            DIRECTORY_SEPARATOR . $template . '.tpl.php';

        if (file_exists($template_path) == false)
        {
            trigger_error("Template {$template} not found in ". $template_path);
            return false;
        }



            foreach($page['elements'] as $key => $element)
            {

                switch($element['type'])
                {
                    case 'text':
                        $output .= $cck->_page_element($element, 'html_form_text');
                        break;
                    case 'textarea':
                        $output .= $cck->_page_element($element, 'html_form_textarea');
                        break;
                    case 'password':
                        $output .= $cck->_page_element($element, 'html_form_password');
                        break;
                    case 'radio':
                        $output .= $cck->_page_element($element, 'html_form_radio');
                        break;
                    case 'checkbox':
                        $output .= $cck->_page_element($element, 'html_form_checkbox');
                        break;
                    case 'select':
                        $list = '';
                        foreach($element['options'] as $item)
                        {
                            if(isset($item['group']) && $item['group'] !=='')
                            {
                                $options[$item['group']][] = $cck->_page_element($item,'html_form_select_option');
                            }
                            else
                            {
                                $options['nogroup'][] = $cck->_page_element($item,'html_form_select_option');
                            }

                        }

                        break;


                    case 'hidden':

                        $output .= $cck->_page_element($element, 'html_form_hidden');
                        break;

                    case 'image':
                        $output .= $cck->_page_element($element, 'html_form_image');
                        break;

                    case 'file':
                        $output .= $cck->_page_element($element, 'html_form_file');
                        break;
                    case 'number':
                        $output .= $cck->_page_element($element, 'html_form_number');
                        break;
                    case 'date':
                        $output .= $cck->_page_element($element, 'html_form_date');
                        break;
                    case 'color':
                        $output .= $cck->_page_element($element, 'html_form_color');
                        break;
                    case 'range':
                        $output .= $cck->_page_element($element, 'html_form_range');
                        break;
                    case 'month':
                        $output .= $cck->_page_element($element, 'html_form_month');
                        break;
                    case 'week':
                        $output .= $cck->_page_element($element, 'html_form_week');
                        break;
                    case 'time':
                        $output .= $cck->_page_element($element, 'html_form_time');
                        break;
                    case 'datetime':
                        $output .= $cck->_page_element($element, 'html_form_datetime');
                        break;
                    case 'datetime-local':
                        $output .= $cck->_page_element($element, 'html_form_datetime_local');
                        break;
                    case 'email':
                        $output .= $cck->_page_element($element, 'html_form_email');
                        break;
                    case 'search':
                        $output .= $cck->_page_element($element, 'html_form_search');
                        break;
                    case 'tel':
                        $output .= $cck->_page_element($element, 'html_form_tel');
                        break;
                    case 'url':
                        $output .= $cck->_page_element($element, 'html_form_url');
                        break;
                    case 'html':
                        $output .= $cck->_page_element($element, 'html_form_html');
                        break;
                }


            }



        $output = $cck->_form_process($template_path, $page);


        return $output;

    }

    function _page_builder($elements = array(), $field_data = array(), $action = NULL)
    {
        // add data section
        global $cck;

        $page = array();

        //exit($cck->_debug($elements));
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

                        foreach($value as $data_key => $data_element)
                        {
                            switch($data_element['element_type'])
                            {

                                case 'file':

                                    $files['files'] = json_decode($field_data[$data_key], true);
                                    $page['elements'][$data_key ]['type'] = 'html';
                                    $page['elements'][$data_key ]['label'] = $data_element['label'];

                                    foreach($files['files'] as $k => $v)
                                    {
                                        $page['elements'][$data_key ]['value'][] = (isset($field_data[$data_key]) ? $v : '');
                                    }
                                    break;
                                default:
                                    $page['elements'][$data_key ] =
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


                        }
                    }


                    break;
                case 'ccid':

                    $page['elements'][$key] =
                        array(
                            'type' => 'text',
                            'id' => 'id-' . $key,
                            'class' => 'class-' . $key,
                            'title' => $value,
                            'label' => $key,
                            'name' => 'container['. $key .']',
                            'value' => $value,
                            'readonly' => '',
                            'before' => ''

                        );

                    break;
                case 'last_update':

                    $page['elements'][$key] =
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

                    $page['elements'][$key] =
                        array(
                            'type' => 'text',
                            'id' => 'id-' . $key,
                            'class' => 'class-' . $key,
                            'title' => $value,
                            'label' => str_replace('_', ' ',$key),
                            'name' => 'container['. $key .']',
                            'value' => date( 'Y-m-d H:m:s', $value),


                        );

                    break;

                case 'content_type_id':


                    $page['elements']['content_type_id'] =
                        array(
                            'type' => 'text',
                            'label' => 'type',
                            'id'=> 'hidden-'.$elements['content_type_info']['type'],
                            'class'=> 'hidden-'.$elements['content_type_info']['type'],
                            'name'=> 'container[content_type_id]',
                            'value'=> $elements['content_type_id'],

                        );
                    $page['elements']['content_type_label'] =
                        array(
                            'type' => 'text',
                            'label' => 'type',
                            'id'=> $elements['content_type_info']['type'],
                            'class'=> $elements['content_type_info']['type'],
                            'name'=> 'container[content_type_label]',
                            'value'=> $elements['content_type_info']['label'],
                            'readonly' => true

                        );
                    break;

                default:
                    if(!is_array($value))
                    {

                        $page['elements'][$key] =
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
        //$page['elements'][$key]['after'] = '</div></div>';

        //$output = $cck->_debug($page);
        //exit($output);
        return $page;//$cck->_page($page,'html_page');
    }

    /**
     * @param array $elements
     * @param null $content_type
     * @return mixed
     *
     *  this is a helper function for finding and using custom templates for field content
     *  otherwise the content can printed in the page template and formatted manually with html
     *  use $cck->_debug($content); to get the names of the available content elements.
     *
     *  To use a custom template name the  template  [field name].tpl.php the variable name in the file is $[field name]
     *  place the  file in _views/themes/[theme name]/content_types/[content type]/
     *
     */
    function _page_content($elements =  array(), $content_type = NULL)
    {
        global $cck,$settings;
        $output = '';

        $default_template =
            DOCROOT .
            DIRECTORY_SEPARATOR . $settings['system']['themes']['value'].
            DIRECTORY_SEPARATOR . $settings['site']['theme']['value'] .
            DIRECTORY_SEPARATOR . 'content_types'.
            DIRECTORY_SEPARATOR . 'default'.
            DIRECTORY_SEPARATOR . 'default.tpl.php';

        foreach($elements as $name => $v)
        {
            $template_path =
                DOCROOT .
                DIRECTORY_SEPARATOR . $settings['system']['themes']['value'].
                DIRECTORY_SEPARATOR . $settings['site']['theme']['value'] .
                DIRECTORY_SEPARATOR . 'content_types'.
                DIRECTORY_SEPARATOR . $content_type .
                DIRECTORY_SEPARATOR . $name . '.tpl.php';
            // look for array
            if(is_array($v) && file_exists($template_path))
            {
                foreach($v as $id => $line)
                {
                    $variables['id'] = $name . '-' . $id;
                    $variables['class'] = $name;
                    $variables[$name] = $line;
                    $output .= $cck->_template($template_path, $variables);
                }
            }
            elseif(is_array($v) && !file_exists($template_path))
            {
                foreach($v as $line)
                {
                    $variables['content'] = $line;
                    $output .= $cck->_template($default_template, $variables);
                }
            }
            // not array and template file exists for content type element
            elseif(file_exists($template_path))
            {
                $variables['id'] = $name;
                $variables['class'] = $name;
                $variables[$name] = $v;
                $output .= $cck->_template($template_path, $variables);
            }
            else
            {
                $variables['content'] = $v;
                $output .= $cck->_template($default_template, $variables);
            }
        }
        return $output;
    }

    function _page_element($element, $template)
    {
        global $cck,$settings;

        //$template_path = DOCROOT . DIRECTORY_SEPARATOR . '_views' . DIRECTORY_SEPARATOR . 'html' . DIRECTORY_SEPARATOR . $template . '.tpl.php';

        $template_path =
            DOCROOT .
            DIRECTORY_SEPARATOR . $settings['system']['themes']['value'].
            DIRECTORY_SEPARATOR .$settings['site']['theme']['value'] .
            DIRECTORY_SEPARATOR . 'html' .
            DIRECTORY_SEPARATOR . $template . '.tpl.php';
        $output = $cck->_template($template_path, $element);
        return $output;
    }

    function _truncate_bywords($text, $limit, $ellipsis = '...') {
        $words = preg_split("/[\n\r\t ]+/", $text, $limit + 1, PREG_SPLIT_NO_EMPTY|PREG_SPLIT_OFFSET_CAPTURE);
        if (count($words) > $limit) {
            end($words); //ignore last element since it contains the rest of the string
            $last_word = prev($words);

            $text =  substr($text, 0, $last_word[1] + strlen($last_word[0])) . $ellipsis;
        }
        return $text;
    }

    function _truncate_bycharacters($text, $limit, $ellipsis = '...') {
        if( strlen($text) > $limit ) {
            $endpos = strpos(str_replace(array("\r\n", "\r", "\n", "\t"), ' ', $text), ' ', $limit);
            if($endpos !== FALSE)
                $text = trim(substr($text, 0, $endpos)) . $ellipsis;
        }
        return $text;
    }

    function _find_links($text)
    {
        $text= preg_replace("/(^|[\n ])([\w]*?)((ht|f)tp(s)?:\/\/[\w]+[^ \,\"\n\r\t&lt;]*)/is", "$1$2<a href=\"$3\" >$3</a>", $text);
        $text= preg_replace("/(^|[\n ])([\w]*?)((www|ftp)\.[^ \,\"\t\n\r&lt;]*)/is", "$1$2<a href=\"http://$3\" >$3</a>", $text);
        $text= preg_replace("/(^|[\n ])([a-z0-9&\-_\.]+?)@([\w\-]+\.([\w\-\.]+)+)/i", "$1<a href=\"mailto:$2@$3\">$2@$3</a>", $text);
        return($text);
    }
}


?>
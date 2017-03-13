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

/*

 *
 *  the purpose of this class is to module resources as Web Services.
 *  The system is Formless Http Query Kind and not RESTful but uses most of its concepts.
 *  the normal mvc  [module]/{class}/{method}/{parameters}
 *  becomes the service mvc [module]/services/[response type]/{class}/{method}/{parameters}
 *  response types: JSON,XML,HTML,PHP,TEXT
 *  request types: JSON,XML,X-WWW-FORM-URLENCODED
 *  request methods:  GET,POST,PUT,DELETE,OPTION
 *
 *  All requests require two client calls the first to acquire a CSRF token, The second to
 *  make the actual call using the token. This does slow the system usage. But better safe than
 *  hacked.
 *
 *
 */
namespace services;


class services{

    public $section;
    public $module;
    public $format;

    function __construct()
    {
        /* Test the Common settings */
        $this->section = __CLASS__;
        $this->module = __NAMESPACE__;
    }

    function index()
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
    function request($class,$action,$format,$arguments)
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

        $parameters = $this->parse_request($body,$content_type);

        // check for first empty call to query and body and return token for client use
        // if body with token and/or query tap resource and build response
        if(empty($query) && empty($body))
        {
            $response_data = $this->request_token_create();
            $response  = $this->response_build($format,$response_data);
            exit($response);
        }
        else
        {
            $authorized = $this->request_token_validate();

            // the resource request names are sent here from the _router() after sniffing URI
            $resource = new $class();
            $response_data = $resource->$action($method,$format,$parameters,$arguments);

            // the response format is validated internally
            $response = $this->response_build($format,$response_data);
            exit($response);
        }


    }

    /**
     *  parse and validate the content and content type of the request
     */
    function parse_request($body = NULL,$content_type = false)
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
    function request_token_create()
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
    function request_token_validate($data = NULL)
    {
        // get the token from the body or GET url
        // take the first 16 characters as the index key
        // find the SESSION by index key
        // compare the sent token string to session variable content string
        return FALSE;
    }

    
    function response_build($type = NULL, array $data)
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
                $this->array_to_xml($data,$xml_data);
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


    function array_to_xml($data, &$xml_data) {
        foreach($data as $key => $value) {
            if(is_array($value)) {
                $key = is_numeric($key) ? "item_$key" : $key;
                $subnode = $xml_data->addChild("$key");
                $this->array_to_xml($value, $subnode);
            }
            else {
                $key = is_numeric($key) ? "item_$key" : $key;
                $xml_data->addChild("$key","$value");
            }
        }
    }
    function html($element,$parent = NULL)
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
                $output .=  $this->html_children($key,$value);
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


     function html_children($key,$child)
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


}
?>

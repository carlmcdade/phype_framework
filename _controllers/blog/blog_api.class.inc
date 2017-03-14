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

namespace blog;

/**
 *  Documentation and usage example for this controller blog_api
 */

class blog_api{


	public  $settings;
	
	
	function __construct()
	{


    }
    	
    function __destruct()
    {
    		//
    }

    /**
     *  Example of usage url: api/blog/blog_add_post/
     *  $url = 'http://server.com/path';
        $data = array('key1' => 'value1', 'key2' => 'value2');

        // use key 'http' even if you send the request to https://...
        $options = array(
        'http' => array(
        'header'  => "Content-type: application/x-www-form-urlencoded\r\n",
        'method'  => 'POST',
        'content' => http_build_query($data),
        ),
        );
        $context  = stream_context_create($options);
        $result = file_get_contents($url, false, $context);
     */
        
    function blog_add_post()
    {
		print 'tested api show info for web service  in JSON format';
		exit;
    }

    /**
     *  delete a blog post
     *  url: api/blog/blog_delete_post/
     */
    function blog_delete_post()
    {
        print 'tested api show info for web service  in JSON format';
        exit;
    }

    /**
     *  list posts by user id
     *  url: api/blog/blog_list_posts/
     */
    function blog_list_posts()
    {
        print 'tested api show info for web service  in JSON format';
        exit;
    }
}
?>

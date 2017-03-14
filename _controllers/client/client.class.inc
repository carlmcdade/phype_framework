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
namespace client;

class client
{

    public  $section;
    public  $module;

    function __construct()
    {
        //Test the Common settings
        $this->section = __CLASS__;
        $this->module = __NAMESPACE__;
    }

    function index()
    {
        $token = $this->send_request("http://demo.phype.net/?services/index");
        print_r($token);
    }

    function send_request($url, array $post_array = array(), $cookie = NULL, $token = NULL)
    {
        $ch = curl_init();

        curl_setopt($ch, CURLOPT_URL, $url);
        curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
        curl_setopt($ch, CURLOPT_USERAGENT, 'googlebot');
        //curl_setopt($ch, CURLOPT_VERBOSE, $post_array);

        if (!empty($post_array)) {
            curl_setopt($ch, CURLOPT_POST, 1);
            curl_setopt($ch, CURLOPT_POSTFIELDS, $post_array);
        }

        if ($cookie) {
            curl_setopt($ch, CURLOPT_COOKIE, $cookie);
        }

        if ($token) {
            curl_setopt($ch, CURLOPT_HTTPHEADER, array('X-CSRF-Token: ' . $token));
        }

        $result = curl_exec($ch);
        curl_close($ch);

        return $result;
    }

    /**
     * @param $url
     * @param $data
     * @param string $referer
     * @return array
     *
     * use when cUrl not available
     * Example of usage
     * // Submit those variables to the server

     */

    function post_request($url, $data, $referer = '')
    {

        // Convert the data array into URL Parameters like a=b&foo=bar etc.
        $data = http_build_query($data);

        // parse the given URL
        $url = parse_url($url);

        if ($url['scheme'] != 'http') {
            die('Error: Only HTTP request are supported !');
        }

        // extract host and path:
        $host = $url['host'];
        $path = $url['path'];

        // open a socket connection on port 80 - timeout: 30 sec
        $fp = fsockopen($host, 80, $errno, $errstr, 30);

        if ($fp) {

            // send the request headers:
            fputs($fp, "POST $path HTTP/1.1\r\n");
            fputs($fp, "Host: $host\r\n");

            if ($referer != '')
                fputs($fp, "Referer: $referer\r\n");

            fputs($fp, "Content-type: application/x-www-form-urlencoded\r\n");
            fputs($fp, "Content-length: " . strlen($data) . "\r\n");
            fputs($fp, "Connection: close\r\n\r\n");
            fputs($fp, $data);

            $result = '';
            while (!feof($fp)) {
                // receive the results of the request
                $result .= fgets($fp, 128);
            }
        } else {
            return array(
                'status' => 'err',
                'error' => "$errstr ($errno)"
            );
        }

        // close the socket connection:
        fclose($fp);

        // split the result header from the content
        $result = explode("\r\n\r\n", $result, 2);

        $header = isset($result[0]) ? $result[0] : '';
        $content = isset($result[1]) ? $result[1] : '';

        // return as structured array:
        return array(
            'status' => 'ok',
            'header' => $header,
            'content' => $content);

    }

    function get_info()
    {
        $post_data = array(
            'test' => 'foobar',
            'okay' => 'yes',
            'number' => 2
        );

        // Send a request to example.com
        $result = $this->post_request('http://www.example.com/', $post_data);

        if ($result['status'] == 'ok') {

            // Print headers
            echo $result['header'];

            echo '<hr />';

            // print the result of the whole request:
            echo $result['content'];

        } else {
            echo 'A error occured: ' . $result['error'];
        }

    }

    function do_post_request($url, $data, $optional_headers = null)
    {
        $params = array('http' => array(
            'method' => 'POST',
            'content' => $data
        ));
        if ($optional_headers !== null) {
            $params['http']['header'] = $optional_headers;
        }
        $ctx = stream_context_create($params);
        $fp = @fopen($url, 'rb', false, $ctx);
        if (!$fp) {
            throw new Exception("Problem with $url, $php_errormsg");
        }
        $response = @stream_get_contents($fp);
        if ($response === false) {
            throw new Exception("Problem reading data from $url, $php_errormsg");
        }
        return $response;
    }

    /**
     * @param $url
     * @param null $params
     * @param string $verb
     * @param string $format
     * @return bool|mixed|SimpleXMLElement|string
     * @throws Exception
     *
     * // This lists projects by Ed Finkler on GitHub:
    foreach (
    rest_helper('http://github.com/api/v2/json/repos/show/funkatron')
    ->repositories as $repo) {
    echo $repo->name, "<br>\n";
    echo htmlentities($repo->description), "<br>\n";
    echo "<hr>\n";
    }
    }
     */

    function rest_helper($url, $params = null, $verb = 'GET', $format = 'json')
    {
        $cparams = array(
            'http' => array(
                'method' => $verb,
                'ignore_errors' => true
            )
        );
        if ($params !== null) {
            $params = http_build_query($params);
            if ($verb == 'POST') {
                $cparams['http']['content'] = $params;
            } else {
                $url .= '?' . $params;
            }
        }

        $context = stream_context_create($cparams);
        $fp = fopen($url, 'rb', false, $context);
        if (!$fp) {
            $res = false;
        } else {
            // If you're trying to troubleshoot problems, try uncommenting the
            // next two lines; it will show you the HTTP response headers across
            // all the redirects:
            // $meta = stream_get_meta_data($fp);
            // var_dump($meta['wrapper_data']);
            $res = stream_get_contents($fp);
        }

        if ($res === false) {
            throw new Exception("$verb $url failed: $php_errormsg");
        }

        switch ($format) {
            case 'json':
                $r = json_decode($res);
                if ($r === null) {
                    throw new Exception("failed to decode $res as json");
                }
                return $r;

            case 'xml':
                $r = simplexml_load_string($res);
                if ($r === null) {
                    throw new Exception("failed to decode $res as xml");
                }
                return $r;
        }
        return $res;
    }
}


?>
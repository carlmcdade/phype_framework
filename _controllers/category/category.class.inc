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
namespace category;

class category{

    public  $section;
    public  $module;

    function __construct()
    {
        //Test the Common settings
        $this->section = __CLASS__;
        $this->module = __NAMESPACE__;
    }

    function hook_css()
    {
        $css = 'css';

        $var[$css][1] = array(
            'link' => '_css/'.$this->module.'.css',
        );

        return $var;
    }

    
    
}

?>

<?php echo (isset($before) ? $before : '') . "\n"; ?>
<?php echo "\n" . '<form'.
    (isset($id) ? ' id="'. $id .'"': '').
    (isset($name) ? ' name="' .$name . '"': '').
    (isset($method) ? ' method="' .$method . '"': 'POST').
    (isset($enctype) ? ' enctype="' .$enctype . '"': '').
    (isset($charset) ? ' accept-charset="' . $charset . '"': '').
    (isset($title) ? ' title="' .$title . '"': '').
    (isset($autocomplete) ? ' autocomplete="' . $autocomplete . '"': '').
    (isset($novalidate) ? ' novalidate' : '').
    (isset($action) ? ' action="' . $action . '"': '').
    '>' . "\n".
    (isset($elements) ? $elements : '').
    '</form>';
    ?>
<?php echo (isset($after) ? $after : '') . "\n"; ?>
<?php

/**
 * Content Connection Kit
 * @author Carl McDade
 * @copyright Carl McDade
 * @since 2011
 * @version 1.0
 * @license Apache 2.0
 *
 * @link http://fhqk.com/cck
 * ==================================================================
 *  Copyright 2011 Carl Adam McDade Jr.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * http://www.apache.org/licenses/LICENSE-2.0
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * ==================================
 *
 */
?>
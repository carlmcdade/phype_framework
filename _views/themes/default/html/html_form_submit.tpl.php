<?php echo (isset($before) ? $before : '') . "\n"; ?>
<?php echo "\n".'<input'.
    (isset($id) ? ' id="'. $id .'"': '').
    (isset($class) ? ' class="'. $class .'"': '').
    (isset($name) ? ' name="' .$name . '"': '').
    (isset($title) ? ' title="' .$title . '"': '').
    (isset($type) ? ' type="' .$type . '"': 'submit').
    (isset($tabindex) ? ' tabindex="' . $tabindex . '"': '').
    (isset($disabled) ? ' disabled' : '').
    (isset($autofocus) ? ' autofocus' : '').
    (isset($formaction) ? ' formaction="' . $formaction . '"' : '').
    (isset($formenctype) ? ' formenctype="' . $formenctype . '"' : '').
    (isset($formnovalidate) ? ' formnovalidate="' . $formnovalidate . '"' : '').
    (isset($formtarget) ? ' formtarget="' . $formtarget . '"' : '').
    (isset($form) ? ' form="' . $form . '"' : '').
    (isset($value) ? ' value="' . $value . '"' : '').
    '>' . "\n"
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

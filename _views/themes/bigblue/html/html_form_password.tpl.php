<?php echo (isset($before) ? $before : '') . "\n"; ?>
<?php echo (isset($label) ? '<label for="'. $name .'">' . $label . '</label>' : ''); ?>
<?php $output = "\n" . '<input'.
    (isset($id) ? ' id="'. $id .'"': '').
    (isset($class) ? ' class="'. $class .'"': '').
    (isset($name) ? ' name="' .$name . '"': '').
    (isset($type) ? ' type="' .$type . '"': 'password').
    (isset($placeholder) ? ' placeholder="' .$placeholder . '"': '').
    (isset($tabindex) ? ' tabindex="' . $tabindex . '"': '').
    (isset($title) ? ' title="' .$title . '"': '').
    (isset($size) ? ' size="' . $size . '"': '').
    (isset($autocomplete) ? ' autocomplete=on)' : '').
    (isset($disabled) ? ' disabled' : '').
    (isset($required) ? ' required' : '').
    (isset($autofocus) ? ' autofocus' : '').
    (isset($readonly) ? ' readonly' : '').
    (isset($form) ? ' form="' . $form . '"' : '').
    (isset($pattern) ? ' pattern="' . $pattern . '"' : '').
    (isset($value) ? ' value="' . $value . '"' : '').
    '>' . "\n"
?>
<?php echo (isset($required) ? "\n" . '<div class="required">' . $output . '<span class="required-mark">&#171;</span></div>' : $output); ?>
<?php echo (isset($after) ? $after : '') . "\n"; ?>
<?php

/**
 *
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

<?php echo (isset($label) ? '<label for="'. $name .'">' . $label . '</label>' : ''); ?>
<input
    <?php echo (isset($id) ? 'id="'. $id .'"': ''); ?>
    <?php echo (isset($class) ? 'class="'. $class .'"': ''); ?>
    <?php echo (isset($name) ? 'name="' .$name . '"': ''); ?>
    <?php echo (isset($type) ? 'type="' .$type . '"': 'image'); ?>
    <?php echo (isset($height) ? 'height="' .$height . '"': ''); ?>
    <?php echo (isset($width) ? 'width="' . $width . '"': ''); ?>
    <?php echo (isset($alt) ? 'alt="' .$alt . '"': ''); ?>
    <?php echo (isset($source) ? 'src="' . $source . '"': ''); ?>
    <?php echo (isset($disabled) ? 'disabled' : ''); ?>
    <?php echo (isset($required) ? 'required' : ''); ?>
    <?php echo (isset($autofocus) ? 'autofocus' : ''); ?>
    <?php echo (isset($novalidate) ? 'novalidate' : ''); ?>
    <?php echo (isset($form) ? 'form="' . $form . '"' : ''); ?>
    <?php echo (isset($formaction) ? 'formaction="' . $formaction . '"' : ''); ?>
    <?php echo (isset($formtarget) ? 'formtarget="' . $formtarget . '"' : ''); ?>
    <?php echo (isset($formenctype) ? 'formenctype="' . $formenctype . '"' : ''); ?>
    <?php echo (isset($value) ? 'value="' . $value . '"' : ''); ?>>
<?php echo (isset($required) ? '<span class="required">' . $required . '</span>' : ''); ?>
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
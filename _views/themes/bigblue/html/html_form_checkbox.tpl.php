<?php echo (isset($before) ? $before : '<div class="squaredThree">') . "\n"; ?>

<?php echo '<input'.
    (isset($id) ? ' id="'. $id .'"': '').
    (isset($class) ? ' class="'. $class .'"': '').
    (isset($name) ? ' name="' .$name . '"': '').
    (isset($type) ? ' type="' .$type . '"': ' type="checkbox"').
    (isset($tabindex) ? ' tabindex="' . $tabindex . '"': '').
    (isset($title) ? ' title="' .$title . '"': '').
    (isset($disabled) && $disabled == 'on' ? ' disabled' : '').
    (isset($autofocus) && $autofocus == 'on' ? ' autofocus' : '').
    (isset($readonly) && $readonly == 'on' ? ' readonly' : '').
    (isset($form) ? ' form="' . $form . '"' : '').
    (isset($checked) && $checked == 'on'  ? $checked = ' checked' : $checked = '').
    (isset($value) ? ' value="' . $value . '"' : ' value=""').
    '>'. "\n";
?>
<?php echo "\n" . (isset($label) ? '<label for="'. $id .'"><span class="a"></span><span class="b"></span><span class="c">' . $label . '</span></label>' : ''). "\n"; ?>
<?php echo (isset($required) ? '<span class="required">' . $required . '</span>' . "\n": ''); ?>
<?php echo (isset($description) ? '<span class="element-description">'. $description . '</span>' . "\n" : ''); ?>
<?php echo (isset($after) ? $after : '</div>') . "\n"; ?>



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

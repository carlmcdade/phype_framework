<?php echo (isset($label) ? '<label for="'. (isset($name) ?   $name  : '') .'">' . $label . '</label>' : ''); ?>
<?php echo "\n" .'<select'.
    (isset($id) ? ' id="'. $id .'"': '').
    (isset($class) ? ' class="'. $class .'"': '').
    (isset($size) ? ' size="' . $size . '"': '').
    (isset($disabled) && $disabled !== FALSE ? ' disabled' : '').
    (isset($required) ? ' required' : '').
    (isset($autofocus) ? ' autofocus' : '').
    (isset($multiple) ? ' multiple' : '').
    (isset($name) ? ' name="' . $name . '"': '').
    (isset($form) ? ' form="' . $form . '"' : '').
    '>'."\n".
    (isset($options) ? $options : '').
    '</select>' . "\n";
    ?>
<?php echo (isset($required) ? '<span class="required">&#171;</span>' : ''); ?>
<?php

/**
 * Example of usage in code:
 *
 *
$form['elements']['city'] =
array(
    'type' => 'select',
    'label' => 'city',
    'id'=> 'mylastname',
    'class'=> 'myclassname',
    'multiple' =>'',
    'name'=> 'cityname',
    'form'=> 'cityname',
    'options'=> array(
    array(
        'type' => 'option',
        'id'=> 'city_1',
        'class'=> 'city_1',
        'value'=> 'pittsburg',
        'description'=> 'pittsburg',
    ),
    array(
        'type' => 'option',
        'id'=> 'city_2',
        'class'=> 'city_2',
        'value'=> 'antioch',
        'description'=> 'antioch',
    ),
    array(
        'type' => 'option',
        'id'=> 'city_3',
        'class'=> 'city_3',
        'value'=> 'livermore',
        'description'=> 'livermore',
    ),
)
 */
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

?>

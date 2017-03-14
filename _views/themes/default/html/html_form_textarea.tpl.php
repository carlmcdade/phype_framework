<?php echo (isset($before) ? $before : '') . "\n"; ?>
<?php echo (isset($label) ? '<label for="'. $name .'">' . $label . '</label>' : ''); ?>
    <div class="wysihtml5-toolbar" id="wysihtml5-toolbar" style="display: none;">
        <a class="command" data-wysihtml5-command="bold">bold</a>
        <a class="command" data-wysihtml5-command="italic">italic</a>
        <a class="command" data-wysihtml5-command="underline">underline</a>

        <a class="command" data-wysihtml5-command="insertUnorderedList">ul</a>
        <a class="command" data-wysihtml5-command="insertOrderedList">ol</a>
        <a class="command" data-wysihtml5-command="formatBlock" data-wysihtml5-command-value="p">p</a>

        <!-- Some wysihtml5 commands require extra parameters
        <a data-wysihtml5-command="foreColor" data-wysihtml5-command-value="red">red</a>
        <a data-wysihtml5-command="foreColor" data-wysihtml5-command-value="green">green</a>
        <a data-wysihtml5-command="foreColor" data-wysihtml5-command-value="blue">blue</a> -->

        <!-- Some wysihtml5 commands like 'createLink' require extra paramaters specified by the user (eg. href) -->
        <a class="command" data-wysihtml5-command="createLink">link</a>
        <a class="command" data-wysihtml5-action="change_view">html</a>
        <div class="" data-wysihtml5-dialog="createLink" style="display: none;">
            <label for="addlink">Link:</label>
                <input id="addlink" type="text" data-wysihtml5-dialog-field="href" value="http://" class="text">

            <a class="command" data-wysihtml5-dialog-action="save">OK</a> <a class="command" data-wysihtml5-dialog-action="cancel">Cancel</a>
        </div>
    </div>
<?php echo "\n" . '<textarea'.
    (isset($id) ? ' id="'. $id .'"': '').
    (isset($class) ? ' class="'. (isset($html) && $html == 'on'? 'html-editor ' : '') . $class .'"': '').
    (isset($name) ? ' name="' .$name . '"': '').
    (isset($wrap) ? ' wrap="' .$wrap . '"': '').
    (isset($placeholder) ? ' placeholder="' .$placeholder . '"': '').
    (isset($tabindex) ? ' tabindex="' . $tabindex . '"': '').
    (isset($title) ? ' title="' .$title . '"': '').
    (isset($columns) ? ' cols="' . $columns . '"': '').
    (isset($rows) ? ' rows="' . $rows . '"': '').
    (isset($maxlength) ? ' maxlength="' . $maxlength . '"': '').
    (isset($minlength) ? ' minlength="' . $minlength . '"': '').
    (isset($autocomplete) ? ' autocomplete=on ' : '').
    (isset($disabled) ? ' disabled=disabled ' : '').
    (isset($autofocus) ? ' autofocus' : '').
    (isset($readonly) ? ' readonly' : '').
    (isset($form) ? ' form="' . $form . '"' : '').
    (isset($pattern) ? ' pattern="' . $pattern . '"' : '>').
    (isset($value) ? $value : '') . "\n".
    '</textarea>' . "\n"
?>
<?php echo (isset($required) ? '<span class="required">&#171;</span>' : ''); ?>
<?php echo (isset($description) ? '<span class="element-description">'. $description . '</span>' . "\n" : ''); ?>
<?php echo (isset($after) ? $after : '') . "\n"; ?>
<?php

if(isset($html) && $html == 'on') { ?>


    <script>
        window.onload = function(){
            //var editor = new wysihtml5.Editor(document.querySelector('.html-editor')  // by class elements
            var editor = new wysihtml5.Editor("<?php echo $id; ?>", { // id of textarea element
                toolbar:      "wysihtml5-toolbar", // id of toolbar element
                parserRules:  wysihtml5ParserRules,
                stylesheets: ["<?php echo '_css/skeleton.css' ; ?>"]// defined in parser rules set
            });

        }

    </script>

<?php } ?>
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
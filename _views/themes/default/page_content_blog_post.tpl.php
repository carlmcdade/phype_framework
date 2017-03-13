<?php

/**
 *   When a new field is added to the content type a new variable with that fields name is
 *   made available to this template
 */

$output = '<h3>'.$post_title.'</h3>'. "\n";
$post_bodyx = $cck->_readable_string($post_body);
$post_bodyx = $cck->_truncate_bywords($post_bodyx, 200);
$output .= '<div>'. $post_bodyx .'</div>'. "\n";
$output .= "<br />";
$output .= (isset($date_created) ? '<span>'. $date_created .'</span>' : ''). "\n";
$output .= (isset($ccid) ? '<span>'. $ccid .'</span>' : ''). "\n";

echo $output . "<br />";

?>

<?php
/**
 * Content Connection Kit
 * @author Carl McDade
 * @copyright Carl McDade
 * @since 2011
 * @version 2.0
 * @license FHQK Universal
 *
 * @link http://fhqk.com/cck
 * ==================================================================
 *  Copyright 2011 Carl Adam McDade Jr.
 * Licensed under the FHQK Universal, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://cck.fhqk.com/license.txt
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
?>
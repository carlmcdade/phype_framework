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

namespace blog;

class blog_form {
  // Sets properties
  public $user_id;
  public $user_name_first;
  public $user_name_last;

  // Method of the class
  function blog_form_get_values() {
    // Returns a string with the properties value. Uppercase the first character of each word
    return ucwords($this->user_id. ' - '. $this->user_name_first . $this->user_name_last) . '<br />';
  }
  
  // Method of the class
  function blog_form_make_form($results)
  {
  	
  	$output = '';
  	
  	// Returns a string with the properties value. Uppercase the first character of each word
  	foreach($results as $item)
  	{
		$output .= $item;
	}
  	return $output;
  }
  
}


?>
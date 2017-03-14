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
/**
 *  Development Documentation outside of scope set by namespace is not visible to the
 *  documentation function used in CCK
 */

namespace users;

/**
 *  Documentation and usage example for this controller users_api
 *  Developers should document code by writing in the comment blocks
 *  of the Class file. The text will show in the list of methods made available
 *  as public and to pages.
 */

class users_api{


	public  $settings;
	
	
	function __construct()
	{

    }
    	
    function __destruct()
    {
    		//
    }

    /**
     *  Usage example  api/user/users_add_user/name/email
     */
    function users_add_user()
    {
		print 'tested api show info for web service  in JSON format';
		exit;
    }

    /**
     *  Usage example  api/user/users_delete_users/id
     */
    function users_delete_users()
    {
        print 'tested api show info for web service  in JSON format';
        exit;
    }

    /**
     *  Usage example  api/user/users_list_users/all
     *  api/user/users_list_users/1/45/89
     */

    function users_list_users()
    {
        print 'tested api show info for web service  in JSON format';
        exit;
    }
}

?>
<?php
/**
 *
 * @author Carl McDade
 * @copyright Carl McDade
 * @since 2011
 * @version 2.0
 * @license Apache 2.0
 *
 * @link http://fhqk.com/cck
 * ==================================================================
 *  Copyright 2011 Carl Adam McDade Jr.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

?>
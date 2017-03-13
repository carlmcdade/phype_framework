<?php
$start_time = microtime(true);
ob_start();

define('DOCROOT', dirname(__FILE__));
define('INI_FILENAME', DOCROOT . "/_configuration/". $_SERVER['SERVER_NAME']. "/config.inc");
define('BASE_URL', '');
define('INSTALLDIR',basename(__DIR__));
define('CLASS_SEPERATOR','\\');
define('ARROW_RIGHT','&raquo;');
define('ARROW_LEFT','&raquo;');
define('LICENSE','Q53a$=9-10-31');

ini_set('session.cookie_httponly', 1);
ini_set('session.use_strict_mode', 1);
ini_set('session.cookie_lifetime', 3600);
session_start();            // Start the PHP session

ini_set('opcache.enable', FALSE);


/**
 * Content Connection Kit
 * @author Carl McDade
 * @copyright Carl McDade
 * @since 2011
 * @version 2.0
 *
 * @link http://cck.fhqk.com/
 * ==================================================================
 *  Copyright 2011 Carl Adam McDade Jr.
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

// find the directory where all of cck is located



// start  the cck front loader
require_once('pyp.php');






// Start system and respond to calls
$cck = CCK::get_instance();
// Set the front page by redirection
if (!$_SERVER['QUERY_STRING']) header('location:' . $cck->_url($settings['site']['frontpage']['value']));
$cck->_bootstrap();


$_SESSION[session_id()]["timer-page"] = ' Page generated in '. round(microtime(true) - $start_time, 4). ' seconds';

?>
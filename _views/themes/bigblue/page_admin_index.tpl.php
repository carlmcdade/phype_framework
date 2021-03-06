<!DOCTYPE html>
<!--[if lt IE 7 ]><html class="ie ie6" lang="en"> <![endif]-->
<!--[if IE 7 ]><html class="ie ie7" lang="en"> <![endif]-->
<!--[if IE 8 ]><html class="ie ie8" lang="en"> <![endif]-->
<!--[if (gte IE 9)|!(IE)]><!--><html lang="en"> <!--<![endif]-->
<head>
    <meta charset="utf-8" />
    <title><?php echo (isset($site_name) ? $site_name : 'PHYPE | Framework'); ?> | <?php echo (isset($page_title) ? $page_title : 'PHYPE | Framework Demo | '); ?></title>
    <meta name="description" content="PHYPE is an API-centric PHP framework for web developers to build on.">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <meta name="keywords" content="Phype Framework, drupal, wordpress,PHP framework, cms, hosting, webhosting, server, php">

    <link rel="stylesheet" href="_css/default.css" type="text/css" />
    <link rel="stylesheet" href="_css/normalize.css" type="text/css" />
    <link rel="stylesheet" href="_css/skeleton.css" type="text/css" />
    <?php //echo (isset($stylesheets) ? print_r($stylesheets,1) : ''); ?>

    <?php //echo (isset($javascript) ? print_r($javascript,1) : ''); ?>

</head>
<body>
<div class="controlcanvas">
    <div class="left-container">
        <?php echo (isset($blocks_left) ? $blocks_left : 'blocks'); ?>
    </div>
</div>
<input accesskey="m" type="checkbox" id="nav-trigger" class="nav-trigger" />
<label for="nav-trigger"></label>

<div class="site-wrap">
<div class="container">
    <div class="row">
        <div id="site-logo" class="three columns"><a href="<?php echo (isset($site_frontpage) ? $site_frontpage : $site_root); ?>"><img src="http://fhqk.com/images/logo_med.jpg"></a></div>
        <div class="nine columns">
            <div id="site-name">
                <span id="site-name-text"><?php echo (isset($site_name) ? $site_name : 'Phype | Framework'); ?></span><br />
                <div id="page-name"><span id="page-name-text"><?php echo (isset($page_title) ? $page_title : ''); ?></span></div>
            </div>
        </div>
    </div>
    <div class="row">
        <div id="navigation" class="sixteen columns">
            <?php echo (isset($navigation) ? $navigation : ''); ?>
        </div>
    </div>
    <div class="row">
        <?php if(isset($sub_navigation)): ?>
            <div id="sub-menu" class="sixteen columns">
                <?php echo $sub_navigation; ?>
            </div>
        <?php endif; ?>
    </div><!-- /#banner -->
    <div id="content-title" class="sixteen columns">
        <span><?php echo (isset($content_title) ? $content_title : ''); ?></span>
    </div>
    <div id="admin-section">
        <?php echo (isset($admin_navigation) ? $admin_navigation : ''); ?>
    </div>
    <div class="row">
        <div id="foot" class="sixteen columns">
            <footer id="post-info" class="body">
                <span><?php echo (isset($content_footer) ? $content_footer : ''); ?></span>
                <span><?php echo 'Now Running PHP version : ' . phpversion();?></span>
            </footer>
        </div>
    </div>
</div>
</div>
<div style="clear:both"></div>
</body>
</html> 
<?php
/**
 * Phype Framework
 * @author Carl McDade
 * @copyright Carl McDade
 * @since 2011
 * @version 1.0
 * @license Apache 2.0
 *
 * @link http://phype.net
 * ==================================================================
 *  Copyright 2011 Carl Adam McDade Jr.



Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
 * ==================================
 */
?>

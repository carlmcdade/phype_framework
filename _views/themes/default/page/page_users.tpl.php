<!DOCTYPE html>
<!--[if lt IE 7 ]><html class="ie ie6" lang="en"> <![endif]-->
<!--[if IE 7 ]><html class="ie ie7" lang="en"> <![endif]-->
<!--[if IE 8 ]><html class="ie ie8" lang="en"> <![endif]-->
<!--[if (gte IE 9)|!(IE)]><!--><html lang="en"> <!--<![endif]-->
<head>
<meta charset="utf-8" />
<title>FHQK | | <?php echo (isset($page_title) ? $page_title : ''); ?></title>
<meta name="description" content="CCK is an API-centric PHP framework for web developers to build on.">
	<meta name="viewport" content="width=device-width, initial-scale=1">
	<meta name="keywords" content=", cck, drupal, wordpress, framework, cms, hosting, webhosting, server, php,podnix">

	<link rel="stylesheet" href="_css/default.css" type="text/css" />
	<link rel="stylesheet" href="_css/normalize.css" type="text/css" />
	<link rel="stylesheet" href="_css/skeleton.css" type="text/css" />
    <link rel="stylesheet" href="_css/print.css" type="text/css" media="print" />

<?php //echo (isset($stylesheets) ? print_r($stylesheets,1) : ''); ?>

<?php //echo (isset($javascript) ? print_r($javascript,1) : ''); ?>

</head>

<body id="<?php echo (isset($page) ? $page : 'default'); ?>" class="<?php echo (isset($page_class) ? $page_class : 'home'); ?> <?php echo (isset($page) ? $page : 'default'); ?>">
<input accesskey="m" type="checkbox" id="nav-trigger" class="nav-trigger" />
<label for="nav-trigger"></label>
<input accesskey="l" type="checkbox" id="access-trigger" class="access-trigger" />

<label for="access-trigger">
    <span class="hook"></span>
    <span class="hook-eye"></span>
    <span class="hook-open"></span>
    <span class="case"></span>
</label>


<div class="controlcanvas">
    <div class="left-container">
        <?php echo (isset($blocks_left) ? $blocks_left : 'blocks'); ?>
    </div>
    <div class="access-container">
        <?php echo (isset($site_blocks_access) ? $site_blocks_access : 'no form found'); ?>
    </div>
</div>

<div class="site-wrap">
<div class="container">
	<div class="row">
		<div class="three columns"><a href="<?php echo (isset($site_frontpage) ? $site_frontpage : $site_root); ?>"><?php echo (isset($site_logo) ? '<img src="'. $site_logo.'"/>' : ''); ?></a></div>
		<div class="nine columns">
			<div id="site-name">
				<span id="site-name-text"><?php echo (isset($site_name) ? $site_name : 'Content Connection Kit'); ?></span><br />
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
	</div>
    <?php if(isset($site_messages)): ?>
        <div class="row">
            <div id="messages" class="sixteen columns">
                <?php echo $site_messages; ?>
                <?php //$cck->_end_sessions('kill_messages'); ?>

            </div>
        </div>
    <?php endif; ?>
<!-- /#banner -->
	<div class="row">
<div id="content-title" class="sixteen columns">
	<span><?php echo (isset($content_title) ? $content_title : ''); ?></span>
</div>

<div id="content" class="sixteen columns">
	<?php echo (isset($content) ? $content : ''); ?>
</div>
		</div><!-- /#content -->
	<div class="row">
		<div id="foot" class="sixteen columns">
			<footer id="post-info" class="eleven columns">
				<span><?php echo (isset($content_footer) ? $content_footer : ''); ?></span>
				<span><?php echo 'Now Running PHP version : ' . phpversion();?></span>
			</footer>
		</div>
	</div>
</div>
</div>
</body>

</html> 
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

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
 * ==================================
 */
?>

<!DOCTYPE html>
<!--[if lt IE 7 ]><html class="ie ie6" lang="en"> <![endif]-->
<!--[if IE 7 ]><html class="ie ie7" lang="en"> <![endif]-->
<!--[if IE 8 ]><html class="ie ie8" lang="en"> <![endif]-->
<!--[if (gte IE 9)|!(IE)]><!--><html lang="en"> <!--<![endif]-->
<head>
	<meta charset="utf-8" />
	<title>Content Connection Kit | <?php echo (isset($page_title) ? $page_title : ''); ?></title>
	<meta name="description" content="CCK is an API-centric PHP framework for web developers to build on.">
	<meta name="viewport" content="width=device-width, initial-scale=1">
	<meta name="keywords" content=", cck, drupal, wordpress, framework, cms, hosting, webhosting, server, php,podnix">

	<link rel="stylesheet" href="_css/default.css" type="text/css" />
	<link rel="stylesheet" href="_css/normalize.css" type="text/css" />
	<link rel="stylesheet" href="_css/skeleton.css" type="text/css" />
	<?php //echo (isset($stylesheets) ? print_r($stylesheets,1) : ''); ?>

	<?php //echo (isset($javascript) ? print_r($javascript,1) : ''); ?>
</head>

<body id="<?php echo (isset($page_id) ? $page_id : 'home'); ?>" class="<?php echo (isset($page_class) ? $page_class : 'home'); ?>">

<header id="banner" class="body">

<section id="page-title" class="page-title">
<span><?php echo (isset($page_title) ? $page_title : ''); ?></span>
</section>

<nav>
	<?php echo (isset($navigation) ? $navigation : ''); ?>
</nav>

<?php if(isset($sub_navigation)): ?>
	<div id="sub-menu">
		<?php echo $sub_navigation; ?>
	</div>
<?php endif; ?> 

</header><!-- /#banner -->

<section id="content-title" class="content-title">
	<span><?php echo (isset($content_title) ? $content_title : ''); ?></span>
</section>

<section id="content" class="user-control-panel body">
	<?php echo (isset($content) ? $content : ''); ?>
</section><!-- /#content -->

<footer id="post-info" class="body">
    <span> The project is owned and operated by &copy;2010 - Carl McDade - All rights reserved.</span>
    <span><?php echo (isset($content_footer) ? $content_footer : ''); ?></span>
</footer>

</body>

</html> 
<?php
 
/**
 * @author Carl McDade
 * @copyright Carl McDade
 * @since 2011
 * @version 1.0
 * @license MIT
 *
 * @link http://berlinto.com/berlinto
 * ==================================================================
 *
 *                             users.tpl.php
 *
 * ==================================================================
 *
 * @todo make a template for this comment
 *
 */
?>

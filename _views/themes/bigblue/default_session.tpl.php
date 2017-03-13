<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="utf-8" />
<title>Content Connection Kit | <?php echo (isset($page_title) ? $page_title : ''); ?></title>
<meta name="description" content="CCK is a PHP framework for web developers to build on.">
<meta name="keywords" content=" cck, drupal, wordpress, framework, cms, hosting, webhosting, server, php, servage">
<link rel="stylesheet" href="_css/default.css" type="text/css" />
 
<!--[if IE]>
	<script src="http://html5shiv.googlecode.com/svn/trunk/html5.js"></script><![endif]-->
<!--[if lte IE 7]>
	<script src="js/IE8.js" type="text/javascript"></script><![endif]-->
<!--[if lt IE 7]>
	<link rel="stylesheet" type="text/css" media="all" href="css/ie6.css"/>
<![endif]-->

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

<section id="content" class="content">
	<?php echo (isset($content) ? $content : ''); ?>
</section><!-- /#content -->

<footer id="post-info" class="body">
    <span> The Content Connection Kit project is owned and operated by &copy;2010 - Carl McDade - All rights reserved.</span>
    <span><?php echo (isset($content_footer) ? $content_footer : ''); ?></span>
</footer>

</body>

</html> 
<?php
 
/**
 * @author Carl McDade
 * @copyright Carl McDade
 * @since 2012
 * @version 1.0
 * @license MIT
 *
 * @link http://berlinto.com/berlinto
 * ==================================================================
 *
 *                        default.tpl.php
 *
 * ==================================================================
 *
 * @todo make a template for this comment
 *
 */
?>

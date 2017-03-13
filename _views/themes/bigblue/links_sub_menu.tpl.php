<ul id="sub-menu-<?php print $menu_index; ?>" class="sub-menus">
<?php foreach($links as $key => $link ){ ?>
	<li id="<?php print $menu_index; ?>-<?php print $key; ?>" class=""><?php print $link; ?></li>
<?php } ?>
</ul>
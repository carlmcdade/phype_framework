<?php
print '<ul id="main-menu" class="menus">';
foreach($links as $section => $link)
{	
	foreach($link as $key => $value)
	{
		print '<li id="' . $section . '-' . $key . '" class="' . $section . ' main-item">' . $value . '</li>' ."\n";		
	}	
}
print '</ul>';
?>
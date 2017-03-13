<?php 
$output = '<div id = "" class="csstable u-full-width">';
$output .= '<div class="cssthead">';
// table header
foreach ($header as $th => $column)
{
	$output .= '<span class="cssth">' .  $column . '</span>' . "\n";
}
$output .= '</div>' . "\n";
if(!empty($rows))
{
	$output .= '<div class="csstbody">' . "\n";
	// table rows
	foreach ($rows as $tr => $row)
	{
		$output .= '<div class="csstr">';
		// table cells per row
		foreach($header as $td => $cell)
		{
			if(isset($row[$td]))
			{
				$output .= '<span class="csstd">' . $row[$td] . '</span>' . "\n";
			}
			else
			{
				$output .= '<span class="csstd">&nbsp;</span>' . "\n";
			}
		}
		$output .= '</div>' . "\n";
	}
	$output .= '</div>' . "\n";
}
$output .= '</div>';
print $output;
?>

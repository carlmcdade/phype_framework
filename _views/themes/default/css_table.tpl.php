<?php 
$output = '<div id = "" class="'. (isset($classes) ? $classes : 'csstable u-full-width') .'">'. "\n";
$output .= '<div class="cssthead">'. "\n";
// table header
foreach ($header as $th => $column)
{
	$output .= '<div class="cssth">' .  $column . '</div>' . "\n";
}
$output .= '</div>' . "\n\n";
if(!empty($rows))
{
	$output .= '<div class="csstbody">' . "\n";
	// table rows
	foreach ($rows as $tr => $row)
	{
		$output .= '<div class="csstr">' ."\n";
		// table cells per row
		foreach($header as $td => $cell)
		{
			if(isset($row[$td]))
			{
                $output .= '<div class="csslabel">' . $header[$td] . '</div>';
				$output .= '<div class="csstd">' . $row[$td] . '</div>' . "\n";
			}
			else
			{
				$output .= '<div class="csstd">&nbsp;</div>' . "\n";
			}
            $output .= '<div class="cssnlbr"></div>' ."\n";
		}

		$output .= '</div>' . "\n\n";
	}
	$output .= '</div>' . "\n";
}
$output .= '</div>' . "\n";
print $output;
?>

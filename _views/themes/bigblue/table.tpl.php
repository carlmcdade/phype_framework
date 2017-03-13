<?php 
$output = '<table class="u-full-width">';
$output .= '<thead>';
// table header
foreach ($header as $th => $column)
{
	$output .= '<th>' .  $column . '</th>' . "\n";
}
$output .= '</thead>' . "\n";
if(!empty($rows))
{
	$output .= '<tbody>' . "\n";
	// table rows
	foreach ($rows as $tr => $row)
	{
		$output .= '<tr>';
		// table cells per row
		foreach($header as $td => $cell)
		{
			if(isset($row[$td]))
			{
				$output .= '<td>' . $row[$td] . '</td>' . "\n";
			}
			else
			{
				$output .= '<td>&nbsp;</td>' . "\n";
			}
		}
		$output .= '</tr>' . "\n";
	}
	$output .= '</tbody>' . "\n";
}

$output .= '</table>';
print $output;
?>

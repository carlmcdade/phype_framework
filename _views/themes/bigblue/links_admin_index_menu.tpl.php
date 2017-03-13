<?php
global $cck;
$count = 0;
$rows = array();
$output = '';



foreach($links as $section => $link)
{

    $module_name = explode('_', $section);


    $doc_link = array(
        'text' => 'documentation',
        'path' => 'admin/admin/documentation/' . $module_name[0],
        'attach_menu' => array(), // attach a child menu
        'css_class' => array($module_name[0] . '-docs'),
        'css_id' => $module_name[0]. '-docs'
    );

    $setting_link = array(
        'text' => 'module',
        'path' => 'admin/admin/module/' . $module_name[0],
        'attach_menu' => array(), // attach a child menu
        'css_class' => array($module_name[0] . '-set'),
        'css_id' => $module_name[0]. '-set'
    );
    $documentation = $cck->_link('links',$doc_link);
    $section_settings = $cck->_link('links',$setting_link);
    $output .=  "\n".'<div class="six columns">';
	$output .= '<h5 class="section-title">' . $module_name[0] . '  <span class="doc-link">'. (isset($documentation) ? $documentation : 'documentation') .' </span>'. '<span class="doc-link"> | </span>' .
        ' <span class="doc-link"> '. (isset($section_settings) ? $section_settings : 'module') .' </span>' .
        '</h5>';
	$output .= '<ul class="' . $section . '">';
	
			foreach($link as $key => $value)
			{
				//
				$output .= '<li id="' . $section . '-' . $key . '" class="' . $section . '">' . $value . '</li>' ."\n";

			}

	$output .= '</ul>' ."\n";
	$output .= '</div>' . "\n" ;


	if($count %2 == 0) {
        $rows[] = "\n\n" . '<div class="row" >' . $output . '</div>';
        $output = '';


    }
    else
    {
        $rows[] = "\n\n" . '<div class="row" >' . $output . '</div>';
        $output = '';
    }

    ++$count;
}

	print implode(' ',$rows);



?>
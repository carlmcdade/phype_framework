<?php


class content_model
{

    function __construct($form = array())
    {

    }


    function content_type_get($content_type_id = NULL)
    {
        global $cck;
        try
        {
            $connect = $cck->_dbconnect('datasource_default');
            $result = $connect->prepare("SELECT type_id, label, type, description FROM content_types WHERE type_id='". $content_type_id ."'");
            $result->execute();
            $data = $result->fetch(PDO::FETCH_ASSOC);
        }
        catch (Exception $e)
        {
            echo 'Data retrieval error: ',  $e->getMessage(), "\n";
        }
        return $data;
    }


    function content_add($form = array(), $content_type = NULL)
    {
        global $cck, $settings;

        $fields = array();
        $values = array();

        $connect = $cck->_dbconnect('datasource_default');
        $connect->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

        // build a field filter so form extras are not sent to query
        $table_name = 'content_containers';
        $list = $connect->query("PRAGMA table_info(" . $table_name . ")");
        $list->setFetchMode(PDO::FETCH_ASSOC);

        foreach ($list as $conkey => $convalue)
        {

            $elements[] = $convalue['name'];

        }

        // unix timestamp
         //Date example


//The variables should be arranged according to your date format and so the separators

        $form['container']['date_created'] = strtotime($form['container']['date_created']);

        foreach($form['container'] as $c => $value)
        {
            //
            if(!empty($value) && in_array($c, $elements))
            {
                $contain_fields[] = $c;
                $contain_markers[] = ':' . $c;
                $contain_values[':' . $c] = $value;
            }


        }

        // get the content type container data from db
        $table = 'content_containers';
        $fields = '' . implode(',', $contain_fields) . '';
        $markers = "" . implode(",", $contain_markers). "";
        $sql = "INSERT INTO " . $table . "(" . $fields .") VALUES(". $markers .")";

        $container_result = $connect->prepare($sql);
        //echo  $cck->_debug($markers);
        //echo  $cck->_debug($sql);
        //exit($cck->_debug($contain_values));
        $created = $container_result->execute($contain_values);


        // add data to container only if container was created
        if($created != FALSE)
        {
            // add needed criteria for data identification to array
            foreach($form['data'] as $form_field => $field_data)
            {

                $build['data']['ccid'] = $form['container']['ccid'];
                $build['data']['content_type_id'] = $form['container']['content_type_id'];
                $build['data']['content_type_field'] = $form_field;
                $build['data']['content_type_field_data'] = $field_data;
                $item[] = $build['data'];
            }

            // fields and markers
            foreach($build['data'] as $d => $value)
            {
                //
                $data_fields[] = $d;
                $data_markers[] = ':' . $d;


            }

            // data entries
            foreach($item as $row => $entry)
            {

                foreach($entry as $key => $me)
                {
                    $new[':' . $key] = $me;
                }
                $data_values[] = $new;

            }

            // echo $cck->_debug($data_values);

            $table = 'content_containers_data';
            $fields = '' . implode(',', $data_fields) . '';
            $markers = "" . implode(",", $data_markers). "";
            $sql = "INSERT INTO " . $table . "(" . $fields .") VALUES(". $markers .");";
            $container_data_result = $connect->prepare($sql);
            foreach($data_values as $table_data)
            {
                $container_data_result->execute($table_data);
            }

            return TRUE;

        }
        else
        {
            // insure the data container  was created first show errors and return end result
            echo $cck->_debug($connect->errorInfo());
            return FALSE;
        }


    }



    function content_save($form = array())
    {
        global $cck;
        //echo $cck->_debug($_POST);

        $fields = array();
        $values = array();

        //unix format time
        //$form['container']['date_created'] = strtotime($form['container']['date_created']);
        $table = 'content_containers';
        $list = $this->content_table_columns($table);
        $time_value = array('date_created','last_update');

        foreach($form['container'] as $c => $value)
        {
            if(in_array($c, $list))
            {
                $contain_fields[] = $c;
                $contain_markers[$c] = $c . '=:' . $c;
                $contain_values[':' . $c] = (in_array($c, $time_value) ? strtotime($value): $value);
            }
        }

        // marker for ccid not needed
        unset($contain_markers['ccid']);

        $connect = $cck->_dbconnect('datasource_default');
        $connect->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
        $table = 'content_containers';

        $fields = '' . implode(',', $contain_fields) . '';
        $markers = "" . implode(",", $contain_markers). "";
        $sql = "UPDATE " . $table . " SET " . $markers ." WHERE ccid=:ccid";
	    $container_update = $connect->prepare($sql);
        $updated_con = $container_update->execute($contain_values);
        //return $updated_con;

        if($updated_con == TRUE)
        {
            foreach($form['data'] as $d => $value)
            {
                //
                $entry[$d][':ccid'] = $form['container']['ccid'];
                $entry[$d][':field'] = $d;
                $entry[$d][':data'] = $value;
            }

            //exit($cck->_debug($entry));

            $table = 'content_containers_data';
            $sql = "UPDATE " . $table . " SET content_type_field_data = :data WHERE ccid =:ccid AND content_type_field = :field";
            $data_update = $connect->prepare($sql);

            foreach ($entry as $entry_data)
            {
                try
                {
                    $data_update->execute($entry_data);

                }
                catch (PDOException $e)
                {
                    echo 'Error: ' . $e->getMessage();
                    return($e->getMessage());

                }
            }


            $no=$data_update->rowCount();

            /*
             * when no data is affected because of an empty container catch the
             * form data values and insert new rows
             */
            if($no == 0)
            {
                // add needed criteria for data identification to array
                foreach($form['data'] as $form_field => $field_data)
                {

                    $build['data']['ccid'] = $form['container']['ccid'];
                    $build['data']['content_type_id'] = $form['container']['content_type_id'];
                    $build['data']['content_type_field'] = $form_field;
                    $build['data']['content_type_field_data'] = $field_data;
                    $item[] = $build['data'];
                }

                // fields and markers
                foreach($build['data'] as $d => $value)
                {
                    //
                    $data_fields[] = $d;
                    $data_markers[] = ':' . $d;


                }

                // data entries
                foreach($item as $row => $entry)
                {

                    foreach($entry as $key => $me)
                    {
                        $new[':' . $key] = $me;
                    }
                    $data_values[] = $new;

                }

                // echo $cck->_debug($data_values);

                $table = 'content_containers_data';
                $fields = '' . implode(',', $data_fields) . '';
                $markers = "" . implode(",", $data_markers). "";
                $sql = "INSERT INTO " . $table . "(" . $fields .") VALUES(". $markers .");";
                $container_data_result = $connect->prepare($sql);
                foreach($data_values as $table_data)
                {
                    $container_data_result->execute($table_data);
                }

                return TRUE;

            }
            else
            {
                // insure the data container  was created first show errors and return end result
                //echo $cck->_debug($connect->errorInfo());
                return FALSE;
            }

            return 'updated';


        }
        //echo $cck->_debug($contain_values);
        //exit($cck->_debug($sql));
        //$data_update = $connect->prepare($sql);
        //$updated = $data_update->execute($data_values);
    }

    function content_add_files($file_post = array())
    {

        global $cck, $settings;

        $allowedTypes = array(IMAGETYPE_PNG, IMAGETYPE_JPEG, IMAGETYPE_GIF);
        $build = array();


        // set array format

        foreach($file_post['files'] as $line => $list)
        {
            if (is_array($list['name']))
            {
                foreach ($list as $key => $item)
                {

                    foreach ($item as $k => $v)
                    {
                        $files[$line][$k][$key] = $v;
                    }
                }

            }
            else
            {
                    $files[$line][] = $list;
            }

        }


        //$files = $this->content_add_files_array($file_post['files']);

        //return $cck->_debug($file_post) . $cck->_debug($files) . $cck->_debug($data);

        // upload files and get file data


        foreach($files as $field => $items)
        {
            foreach($items as $key => $item)
            {
                $detectedType = exif_imagetype($item['tmp_name']);
                $error = !in_array($detectedType, $allowedTypes);

                $destination = $settings['site']['files']['value'] . $file_post['container']['ccid']. DIRECTORY_SEPARATOR . $field ;
                if (!file_exists($destination)) {
                    mkdir($destination, 0777, true);
                }

                $filename = $destination .  DIRECTORY_SEPARATOR . $cck->_filename_clean_utf8($item['name']);


                // Check for errors
                if($item['error'] > 0)
                {
                    die('An error ocurred when uploading.');
                }

                if(!getimagesize($item['tmp_name']))
                {
                    die('Please ensure you are uploading an image.');
                }

                 // Check filetype
                if($error > 0)
                {
                    die('Unsupported filetype uploaded.');
                }

                 // Check filesize
                if($item['size'] > 1500000)
                {
                    die('File uploaded exceeds maximum upload size.');
                }

                 // Check if the file exists
                if(file_exists($filename))
                {
                    die('File with that name already exists.');
                    //unlink($filename);
                }

                 // Upload file
                if(!move_uploaded_file($item['tmp_name'], $filename))
                {
                    die('Error uploading file - check destination is writeable.');
                }



            }

            $build[$field]['ccid'] = $file_post['container']['ccid'];
            $build[$field]['content_type_id'] = $file_post['container']['content_type_id'];
            $build[$field]['content_type_field'] = $field;
            foreach($files[$field] as $key => $item)
            {
                $build[$field]['content_type_field_data'][] = $destination .  DIRECTORY_SEPARATOR . $files[$field][$key]['name'];
            }

        }


        $db_fields = array_keys($build[$field]);
        foreach($db_fields as $name)
        {
            $data_fields[] = $name;
            $data_markers[] = ':' .$name;
        }

        foreach($build as $field => $item)
        {
            foreach($item as $key => $name)
            {
                $data_values[$field][':'. $key] =  (is_array($name) ? json_encode($name, true) : $name);
            }

        }


        //exit($cck->_debug($data_markers). $cck->_debug($data_fields). $cck->_debug($data_values)) ;//$cck->_debug($file_post) .

        // fields and markers

        // insert file data

        $connect = $cck->_dbconnect('datasource_default');
        $connect->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
        $table = 'content_containers_data';
        $fields = '' . implode(',', $data_fields) . '';
        $markers = "" . implode(",", $data_markers). "";
        $sql = "INSERT INTO " . $table . "(" . $fields .") VALUES(". $markers .");";
        $upload_data_result = $connect->prepare($sql);

        foreach($data_values as $field_data)
        {

                $upload_data_result->execute($field_data);

        }


        return $build;

    }

    function content_add_files_array($file_post = array())
    {
        global $cck;


        foreach($file_post['files'] as $line => $list)
        {
            if (is_array($list['name']))
            {
                foreach ($list as $key => $item)
                {

                    foreach ($item as $k => $v)
                    {
                        $files[$line][$k][$key] = $v;
                    }
                }

            }
            else
            {
                $files[$line][] = $list;
            }

        }


            foreach($files['data'] as $line => $list)
            {
                if (is_array($list['name']))
                {
                    foreach ($list as $key => $item)
                    {

                        foreach ($item as $k => $v)
                        {
                            $filesx[$line][$k][$key] = $v;
                        }
                    }

                }
                else
                {
                    $filesx[$line][] = $list;
                }

            }
            return $filesx;



    }

    function content_remove_files($files = array())
    {
        global $cck;

        foreach($files as $field  => $items)
        {
            foreach($items as $key => $path) {
                if (file_exists($path)) {
                    unlink($path);
                }
            }
        }

        return $cck->_debug($files);
    }

    function content_upload_files($files = array())
    {
        foreach($files as $field => $items)
        {
            if(is_array($items))
            {
                foreach($items as $key => $item)
                {
                    if(!move_uploaded_file($item['temp_name'], $item['file_name']))
                    {
                        die('Error uploading file - check destination is writeable.');
                    }
                }

            }


        }

        return FALSE;
    }

    function content_update_files($file_post = array())
    {

        global $cck, $settings;

        $post = $file_post['post'];
        $destination = $settings['site']['files']['value'] . $post['container']['ccid']  ;

        // find the  key chk-delete_file  and  use elements to set up removal
        $connect = $cck->_dbconnect('datasource_default');
        $connect->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

        $data = $this->content_get_container_data($post['container']['ccid']);


        // removing marked items from field
        if(isset($post['chk-delete_file']))
        {
            foreach($post['chk-delete_file']  as  $field => $remove)
            {
                $items[$field] = json_decode($data[$field]);

                foreach($remove as $key => $value)
                {
                    if( $value == $items[$field][$key] )
                    {
                        unset($items[$field][$key]);
                    }

                }

            }

        }

        // get new items from post
        $files = $cck->_model('content','content_add_files_array',$file_post);


        // match data fields to corresponding database field and convert json

        foreach($files as $field_match => $info)
        {
            $list_data[$field_match] = json_decode($data[$field_match]);
        }

        foreach($list_data as $item => $value)
        {


                $existing_item[$item] = array_flip($value);
                foreach($value as $key =>$path)
                {

                    if( isset($post['chk-delete_file'][$item][$key]) && in_array($post['chk-delete_file'][$item][$key],$list_data[$item]))
                    {

                        //echo  ' deleting: ' . $post['chk-delete_file'][$item][$key]."<br>\n";
                        //echo  $item.'-'. $key . '='.$list_data[$item][$key]."<br>\n";
                        unset($existing_item[$item][$post['chk-delete_file'][$item][$key]]);
                    }


                }

            $existing_item[$item] = array_flip($existing_item[$item]);
        }


        foreach($files as $newfield => $newitems)
        {
            // only try with sent file changes
            if($files[$newfield][key($newitems)]['error']  === 0 )
            {
                $build[$newfield]['ccid'] = $post['container']['ccid'];
                $build[$newfield]['content_type_id'] = $post['container']['content_type_id'];
                $build[$newfield]['content_type_field'] = $newfield;


                    //new uploads
                    foreach ($files[$newfield] as $k => $v) {

                        $allowedTypes = array(IMAGETYPE_PNG, IMAGETYPE_JPEG, IMAGETYPE_GIF);
                        $detectedType = (!empty($files[$newfield][$k]['tmp_name']) ? exif_imagetype($files[$newfield][$k]['tmp_name']) : IMAGETYPE_GIF);
                        $error = !in_array($detectedType, $allowedTypes);

                        // if an upload filed was added to an existing content type with  container content the
                        // directories may not exist.


                        if (!file_exists($destination)) {
                            mkdir($destination, 0777, true);
                        }

                        // Check for errors
                        if($files[$newfield][$k]['error'] > 0)
                        {
                            die('An error ocurred when uploading.');

                        }

                        if(!getimagesize($files[$newfield][$k]['tmp_name']))
                        {
                            die('Please ensure you are uploading an image.');
                        }

                        // Check filetype
                        if($error > 0)
                        {
                            die('Unsupported filetype uploaded.');
                        }

                        // Check filesize
                        if($files[$newfield][$k]['size'] > 1500000)
                        {
                            die('File uploaded exceeds maximum upload size.');
                        }

                        // Check if the file exists
                        if(file_exists($files[$newfield][$k]['name']))
                        {
                            die('File with that name already exists.');
                            //unlink($filename);
                        }


                        if(!empty($files[$newfield][$k]['name']))
                        {
                            $build[$newfield]['content_type_field_data'][] = $destination . DIRECTORY_SEPARATOR . $newfield . DIRECTORY_SEPARATOR . $cck->_filename_clean_utf8($files[$newfield][$k]['name']);
                            $uploads[$newfield][] = array(
                                'file_name' => $destination . DIRECTORY_SEPARATOR . $newfield . DIRECTORY_SEPARATOR . $cck->_filename_clean_utf8($files[$newfield][$k]['name']),
                                'temp_name' => $files[$newfield][$k]['tmp_name'],
                            );
                        }

                    }

                if(!empty($existing_item[$newfield]))
                {
                    // existing
                    foreach ($existing_item[$newfield] as $i => $path) {
                        $build[$newfield]['content_type_field_data'][] = $path;
                    }

                }



            }
            else
            {
                // there are changes like deletes but no uploads
                $build[$newfield]['ccid'] = $post['container']['ccid'];
                $build[$newfield]['content_type_id'] = $post['container']['content_type_id'];
                $build[$newfield]['content_type_field'] = $newfield;

                if(!empty($existing_item[$newfield]))
                {
                    // existing
                    foreach ($existing_item[$newfield] as $i => $path) {
                        $build[$newfield]['content_type_field_data'][] = $path;
                    }

                    //$uploads[$newfield] = $build[$newfield]['content_type_field_data'];
                }
                else{

                    // nothing to upload and empty database field
                    //$single_item = array();
                    //if(isset($files[$newfield][0]['name']) && !empty($files[$newfield][0]['name']))
                    //{
                        //$single_item =  array($destination . DIRECTORY_SEPARATOR . $newfield . DIRECTORY_SEPARATOR . $files[$newfield][0]['name']);
                    //}

                    foreach ($files[$newfield] as $i => $path) {
                        $path = NULL;
                        if(isset($files[$newfield][$i]['name']) && $files[$newfield][$i]['name'] != '')
                        {
                            $path =  $destination . DIRECTORY_SEPARATOR . $newfield . DIRECTORY_SEPARATOR . $files[$newfield][$i]['name'];

                        }

                        $build[$newfield]['content_type_field_data'][] = $path;

                    }
                    //$build[$newfield]['content_type_field_data'] = $single_item;
                    //$uploads[$newfield] = 'nothing';
                }
            }



        }

        //$output = 'in database:'.$cck->_debug($list_data);

        //$output .= 'left over:'.$cck->_debug($existing_item);
        //$output .= 'post files:'.$cck->_debug($files);

        $output = 'update to database:'.(isset($build) ? $cck->_debug($build): $cck->_debug(' nothing to change'));
        $output .= 'completed update to database:'. (isset($build) ? $this->content_update_files_data($build): $cck->_debug(' nothing to change'));
        $output .= 'remove these:'. (isset($post['chk-delete_file']) ? $this->content_remove_files($post['chk-delete_file']) :$cck->_debug(' nothing to change'));
        $output .= 'upload or over-write existing or empty directory:'.(isset($uploads) ? $this->content_upload_files($uploads) :$cck->_debug(' nothing to change'));
       return $output;
    }

    function content_update_files_data($data = array())
    {
        global $cck;

        foreach($data as $field => $value)
        {
            //
            $entry[$field][':ccid'] = $value['ccid'];
            $entry[$field][':field'] = $value['content_type_field'];
            $entry[$field][':data'] = (!empty($value['content_type_field_data'])?json_encode($value['content_type_field_data'], true): '');
        }

       //return $cck->_debug($entry);

        $connect = $cck->_dbconnect('datasource_default');
        $connect->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

        $table = 'content_containers_data';
        $sql = "UPDATE " . $table . " SET content_type_field_data = :data WHERE ccid =:ccid AND content_type_field = :field";
        $data_update = $connect->prepare($sql);

        foreach ($entry as $entry_data)
        {
            try
            {
                $data_update->execute($entry_data);

            }
            catch (PDOException $e)
            {
                echo 'Error: ' . $e->getMessage();
                return($e->getMessage());

            }
        }

        return $cck->_debug($entry);
    }

    function content_format_files($files = array() , $style = 'image')
    {
        global $cck;

        $list = json_decode($files['files']);
        $output = '';

        switch($style)
        {
            case 'image':
                foreach($list as $key => $item)
                {
                    $parts = explode('/', $item);
                    $item_name = array_pop($parts);
                    $content['label'] = '';
                    $content['title'] = 'click to remove';
                    $content['id'] = 'chk-delete_file['.$files['field'].']['. $item_name .']';
                    $content['name'] = 'chk-delete_file['.$files['field'].'][]';
                    $content['before'] = '<div class="squaredFour">';
                    $content['description'] = 'mark to remove';
                    $content['value'] = $item;
                    $variables['checkbox'] = $cck->_view('html_form_checkbox', $content);
                    $variables['src'] = $item;
                    $output .= $cck->_view('html_image', $variables);
                }
                break;
            case 'link':
                break;
            case 'text':
                break;
        }


        return $output;

    }

    function content_format_data($data = array())
    {
        $formatted_data = '';

        foreach($data as $i => $value)
        {
            if(array_key_exists('content_type_field',$value))
            {
                // check to see if key is in array of fields for content type
                $formatted_data[$value['content_type_field']] = $value['content_type_field_data'];
            }
            else
            {
                $formatted_data[$value['content_type_field']] = $value['content_type_field_data'];
            }
        }

        return $formatted_data;
    }


    function content_edit($form = array(), $content_type = NULL)
    {
        global $cck, $settings;

        $fields = array();
        $values = array();

        $table = '';

        // use extract only for these array elements
        // $aVarToExtract = array(my, important, info);
        // extract (array_intersect_key ($form, array_flip($aVarToExtract)));


        // find the $variable names. they should be identical to the database field names but
        // use $arr = get_defined_vars(); to make sure
        // out put the values to string for debug and development

        foreach($form['container'] as $c => $value)
        {
            //
            $contain_fields[] = $c;
            $contain_markers[] = ':' . $c;
            $contain_values[':' . $c] = $value;
        }



        // get the content type container data from db
        $connect = $cck->_dbconnect('datasource_default');
        $table = 'content_containers';
        $fields = '' . implode(',', $contain_fields) . '';
        $markers = "" . implode(",", $contain_markers). "";
        $sql = "INSERT INTO " . $table . "(" . $fields .") VALUES(". $markers .");";

        $container_result = $connect->prepare($sql);
        $container_result->execute($contain_values);


        // add needed criteria for data identification to array
        $form['data']['ccid'] = $form['container']['ccid'];
        $form['data']['content_type'] = $form['container']['content_type_id'];

        foreach($form['data'] as $d => $value)
        {
            //
            $data_fields[] = $d;
            $data_markers[] = ':' . $d;
            $data_values[':' . $d] = $value;
        }

        $table = 'content_containers_data';
        $fields = '' . implode(',', $data_fields) . '';
        $markers = "" . implode(",", $data_markers). "";
        $sql = "INSERT INTO " . $table . "(" . $fields .") VALUES(". $markers .");";

        $container_data_result = $connect->prepare($sql);
        $container_data_result->execute($data_values);


        // get fields for the content type fields by id
        //$field_result = $this->connect->prepare("SELECT field_id, label, name FROM content_types_fields WHERE content_type_id='". $row['type_id']."'");
        //$field_result->execute();

        //$fields_all = $field_result->fetch(PDO::FETCH_ASSOC);

        // match form fields and values to database content type fields

        // insert form field values to table with container id  content type and field name


    }




    function content_delete_container($ccid = NULL)
    {
        global $cck;
        $connect = $cck->_dbconnect('datasource_default');
        $ccid_query = $connect->prepare("DELETE FROM content_containers WHERE ccid='" . $ccid ."'");
        $ccid_query->execute();
        $container = $ccid_query->fetch(PDO::FETCH_ASSOC);

        if($container == FALSE){

            return FALSE;
        }
        else
        {
            return TRUE;
        }

    }

    function content_delete_container_data($ccid = NULL)
    {
        global $cck;
        $connect = $cck->_dbconnect('datasource_default');
        $ccid_query = $connect->prepare("DELETE FROM content_containers_data WHERE ccid='" . $ccid ."'");
        $ccid_query->execute();
        $container = $ccid_query->fetch(PDO::FETCH_ASSOC);

        if($container == FALSE){

            return FALSE;
        }
        else
        {
            return TRUE;
        }

    }

    function content_get_type_fields($arguments = array())
    {
        global $cck;


        $connect = $cck->_dbconnect('datasource_default');
        $table = 'content_types_fields';
        $fields = '' . implode(',', $arguments['fields']) . '';
        //$condition = "" . implode(",", $data_markers). "";
        $sql = "SELECT field_id,name" . $fields ." FROM ". $table . " WHERE content_type_id='" . $arguments['content_type_id'] ."';";


        $container_data_result = $connect->prepare($sql);
        $container_data_result->execute();
        $con_fields = $container_data_result->fetchAll(PDO::FETCH_ASSOC);
        return $con_fields;

    }

    function content_get_field_types($id = NULL)
    {
        global $cck;


        $connect = $cck->_dbconnect('datasource_default');
        $table = 'content_types_fields_types';
        if($id)
        {
            $sql = "SELECT * FROM ". $table . " WHERE field_type_id='" . $id ."';";
        }
        else
        {
            $sql = "SELECT * FROM ". $table . ";";
        }



        $container_data_result = $connect->prepare($sql);
        $container_data_result->execute();
        $field_types = $container_data_result->fetchAll(PDO::FETCH_ASSOC);
        return $field_types;

    }

    function content_get_container($ccid = NULL)
    {
        global $cck;
        $connect = $cck->_dbconnect('datasource_default');

        $ccid_query = $connect->prepare("SELECT ccid,administration_title,author_id, last_update, date_created, content_type_id FROM content_containers WHERE ccid='" . $ccid ."'");
        $ccid_query->execute();
        $container = $ccid_query->fetch(PDO::FETCH_ASSOC);


        if($container == FALSE){

            return FALSE;
        }

        // add some type info
        $container['content_type_info'] = $this->content_type_get($container['content_type_id']);
        $order = array_reverse($container);
        $container = $order;

        $field_result = $connect->prepare("SELECT ctf.field_id,ctf.field_type_id, ctf.label,ctf.html,ctf.multiple,ctf.name, ctf.required, ments.type as element_type FROM content_types_fields AS ctf JOIN content_types_fields_types AS ments ON ctf.field_type_id = ments.field_type_id WHERE ctf.content_type_id='". $container['content_type_id']."'");
        $field_result->execute();
        $data_fields = $field_result->fetchALL(PDO::FETCH_ASSOC);

        if(empty($data_fields))
        {
            $admin_link['text'] = 'create a field';
            $admin_link['path'] = 'admin/content/content_type_field_add/'. $container['content_type_id'];
            $container['data'] = array(
                array(
                    'field_id' => NULL,
                    'field_type_id' => '11',
                    'label' => 'NO FIELDS',
                    'name' => 'no_fields',
                    'required' => '',
                    'element_type' => 'html',
                    'value' => 'No content fields for this type have been created. You may create a container for later  use or '. $cck->_link('links',$admin_link),
                ));
        }
        else
        {
            foreach ($data_fields as $datakey => $datavalue)
            {
                $container['data'][$datavalue['name']] = $datavalue;
            }

            //$data = array_reverse($container['data']);

        }

        // separate and merge to place data fields array first
        $last = array_reverse($container);

        return $last;
    }

    function content_get_container_data($ccid = NULL)
    {
        global $cck;

        $connect = $cck->_dbconnect('datasource_default');
        $ccid_query = $connect->prepare("SELECT * FROM content_containers_data WHERE ccid='" . $ccid ."'");
        $ccid_query->execute();
        $data = $ccid_query->fetchAll(PDO::FETCH_ASSOC);
        if($data == FALSE){

            return array();
        }
        foreach($data as $i => $value)
        {
            $formatted_data[$value['content_type_field']] = $value['content_type_field_data'];

        }
        //exit($cck->_debug($formatted_data));
        //$formatted = $this->content_format_data('', $data);

        return $formatted_data;
    }

    function content_type_fields_count($content_type = NULL)
    {
        global $cck, $settings;
        $connect = $cck->_dbconnect('datasource_default');

        // get the existing fields for the content type
        $table = 'content_types_fields';
        //$fields = '' . implode(',', $arguments['fields']) . '';
        //$condition = "" . implode(",", $data_markers). "";
        $sql = "SELECT count(*) FROM " . $table . " WHERE content_type_id='" . $content_type . "';";
        $existing_field_result = $connect->prepare($sql);
        $existing_field_result->execute();
        $rows = $existing_field_result->fetch(PDO::FETCH_NUM);

        return $rows[0];
    }

    function content_type_quick_field_add($arguments)
    {
        global $cck,$settings;
        $connect = $cck->_dbconnect('datasource_default');
        $connect->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

        // get the existing fields for the content type
        $table = 'content_types_fields';
        //$fields = '' . implode(',', $arguments['fields']) . '';
        //$condition = "" . implode(",", $data_markers). "";
        $sql = "SELECT count(*) FROM ". $table . " WHERE content_type_id='" . $arguments[0] ."';";
        $existing_field_result = $connect->prepare($sql);
        $existing_field_result->execute();
        $rows = $existing_field_result->fetch(PDO::FETCH_NUM);



        /*
         * get the field details by type form the defaults table
         * for quick field add avoiding the need of a form to carry information
         */
        $table = 'content_types_field_defaults';
        //$fields = '' . implode(',', $arguments['fields']) . '';
        //$condition = "" . implode(",", $data_markers). "";
        $sql = "SELECT *  FROM ". $table . " WHERE field_type_id='" . $arguments[1] ."';";

        $form_field_result = $connect->prepare($sql);
        $form_field_result->execute();
        //$form_field = $form_field_result->fetch(PDO::FETCH_ASSOC);


        // add  row id and minimal attributoes for form field
        $new_index = ($rows[0] + 1);
        $form_field['content_type_id'] = $arguments[0];
        $form_field['field_type_id'] = $arguments[1];
        $form_field['name'] = 'field_named_' . $new_index;
        $form_field['label'] = 'field_labeled_' . $new_index;

        foreach($form_field as $d => $value)
        {
            //
            if((!empty($value)))
            {
                $data_fields[] = $d;
                $data_markers[] = ':' . $d;
                $data_values[':' . $d] = $value ;
            }


        }



        $table = 'content_types_fields';
        $fields = '' . implode(',', $data_fields) . '';
        $markers = "" . implode(",", $data_markers). "";
        $sql = "INSERT INTO " . $table . "(" . $fields .") VALUES(". $markers .");";



        /*return  $cck->_debug($form_field) .
                $cck->_debug($data_fields) .
                $cck->_debug($data_markers) .*/
        echo  $cck->_debug($data_values);
        echo  $cck->_debug($sql);

        $field_result = $connect->prepare($sql);
        $newfield = $field_result->execute($data_values);

        if($newfield != FALSE)
        {
            $cck->_debug($connect->errorInfo());
           // header('location:'. $settings['base_url']. '/?admin/content/content_type_fields/'.$arguments[0]);
        }
        else
        {
            // insure the data container  was created first show errors and return end result
            exit($cck->_debug($connect->errorInfo()));
        }


    }

    function content_type_field_add($field_posted = array())
    {
        global $cck,$settings;





        echo $cck->_debug($field_posted);

        /*
         * get the field details by type form the defaults table
         * for quick field add avoiding the need of a form to carry information
         */
        $table = 'content_types_fields';
        $columns = $this->content_table_columns($table);


        // add  row id and minimal attributoes for form field
        //$form_field['content_type_id'] = $arguments[0];
        //$form_field['field_type_id'] = $arguments[1];

        foreach($field_posted as $d => $value)
        {
            //find checkbox keys and filter
            if (0 === strpos($d, 'chk-')) {
                $d = substr( $d, 4 ) ;// It starts with 'chk-'
            }

            if((!empty($value) && in_array($d, $columns)))
            {
                $data_fields[] = $d;
                $data_markers[] = ':' . $d;
                $data_values[':' . $d] = trim($value);
            }


        }

        $connect = $cck->_dbconnect('datasource_default');
        $connect->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

        $table = 'content_types_fields';
        $fields = '' . implode(',', $data_fields) . '';
        $markers = "" . implode(",", $data_markers). "";
        $sql = "INSERT INTO " . $table . "(" . $fields .") VALUES(". $markers .");";
        $field_result = $connect->prepare($sql);
        $newfield = $field_result->execute($data_values);


        //echo  $cck->_debug($data_fields);
        //echo  $cck->_debug($data_values);
        //echo  $cck->_debug($sql);
        //exit ($cck->_debug($connect->errorInfo()));



        if($newfield != FALSE)
        {

             return TRUE;
        }
        else
        {
            // insure the data container  was created first show errors and return end result
            return $cck->_debug($connect->errorInfo());
        }


    }

    function content_type_field_save($field_posted = array())
    {
        global $cck,$settings;
        $connect = $cck->_dbconnect('datasource_default');
        $connect->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
        //$defaults = content_get_type_fields($arguments = array());

        $table = 'content_types_fields';
        $columns = $this->content_table_columns($table);

        //unset($field_posted['field_id']);
        foreach($field_posted as $d => $value)
        {
            //find checkbox keys and filter
            if (0 === strpos($d, 'chk-')) {
                $d = substr( $d, 4 ) ;// It starts with 'chk-'
            }

            if((!empty($value) && in_array($d, $columns)))
            {
                $field_fields[] = $d;
                $field_markers[] = $d. '=:' . $d;
                $field_values[':' . $d] = trim($value);
            }



        }


        // update fields
        $fields = '' . implode(',', $field_fields) . '';
        $markers = implode(",", $field_markers);
        $fieldsql = "UPDATE " . $table ." SET ". $markers ." WHERE field_id=:field_id;";


        try
        {

            $field_result = $connect->prepare($fieldsql);
            $updated_field = $field_result->execute($field_values);

            // update the data table
            if($updated_field == TRUE)
            {
                $updated_data = $this->content_type_field_data_update($field_posted['content_type_id'], $field_posted['name'], $field_posted['existing_field_name']);
            }

            $output = $cck->_debug($field_posted). $cck->_debug($markers).$cck->_debug($field_fields).$cck->_debug($field_values);

            exit($updated_data);
            // empty form by field type


        }
        catch (PDOException $e)
        {
            echo $cck->_debug($fieldsql).
                'Data entry error: ',  $e->getMessage(), "\n";
            echo $cck->_debug($field_posted). $cck->_debug($field_markers).$cck->_debug($field_fields).$cck->_debug($field_values);

            exit();
        }

    }

    function content_type_field_delete($field = array())
    {
        global $cck,$settings;
        $connect = $cck->_dbconnect('datasource_default');
        $connect->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

        $delete_query = $connect->prepare("DELETE FROM content_types_fields WHERE field_id='" . $field[1] ."'");
        $deleted_field = $delete_query->execute();

        if($deleted_field == FALSE){

            return FALSE;
        }
        else
        {
            return TRUE;
        }


    }

    function content_type_field_data_delete($field = array())
    {
        global $cck;

        //get field info
        // get content type id

        $connect = $cck->_dbconnect('datasource_default');
        $connect->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

        $delete_query = $connect->prepare("DELETE FROM content_containers_data WHERE content_type_id = '" . $field[0] . "' AND content_type_field=" . $field[1] );
        $deleted_data = $delete_query->execute();

        if($deleted_data == FALSE){

            return FALSE;
        }
        else
        {
            return TRUE;
        }

    }

    function content_type_field_data_update($content_type_id = NULL, $new_field_name = NULL, $old_field_name = NULL)
    {
        global $cck, $settings;

        $connect = $cck->_dbconnect('datasource_default');
        $connect->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

        // update fields names in data table
        $table = 'content_containers_data';
        $values = array(
            ':new_field_name' =>  $new_field_name,
            ':old_field_name' => $old_field_name,
            ':content_type_id' => $content_type_id,

        );
        $datasql = "UPDATE " . $table ." SET content_type_field=:new_field_name WHERE content_type_id=:content_type_id  AND content_type_field=:old_field_name;";

        $field_result = $connect->prepare($datasql);
        $field_result->execute($values);


    }

    function content_table_columns($table_name = NULL)
    {
        global $cck;

        $connect = $cck->_dbconnect('datasource_default');
        $connect->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

        // build a field filter so form extras are not sent to query
        $list = $connect->query("PRAGMA table_info(" . $table_name . ")");
        $list->setFetchMode(PDO::FETCH_ASSOC);

        foreach ($list as $conkey => $convalue)
        {

            $columns[] = $convalue['name'];

        }

        return $columns;
    }


}
// variables used here  for $class $method and $form are previously set in the $cck->_model() call
//$model =  $class . '_model';
//$content = new $class();
//return $content->$method($arguments);

/**
 * Content Connection Kit
 * @author Carl McDade
 * @copyright Carl McDade
 * @since 2011
 * @version 2.0
 * @license FHQK Universal
 *
 * @link http://fhqk.com/cck
 * ==================================================================
 *  Copyright 2011 Carl Adam McDade Jr.
 * Licensed under the FHQK Universal, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://cck.fhqk.com/license.txt
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
?>
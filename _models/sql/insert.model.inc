<?php

$model = $cck->_model('insert',
    array(
        'fields' => array('*'),
        'table' => array('content_type_info'),
        'conditions' => array(
            'id' => '1',

        ),
    )

);
//exit;
// table header from database
//INSERT INTO people (full_name, job_title) VALUES ("John Doe","manager")');
$fields = '' . implode(',', $fields) . '';
$values = '"' . implode('","', $values). '"';

$connect = $cck->_dbconnect('datasource_default');
$sql = "INSERT INTO " . $table . " (" . $fields .") VALUES (". $values .")";
$result = $connect->prepare($sql);
$result->execute();
$type_info = $result->fetchAll(PDO::FETCH_ASSOC);
?>
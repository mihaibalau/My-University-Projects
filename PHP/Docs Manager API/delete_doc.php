<?php
require_once "DBUtils.php"; 

if (isset($_GET['id'])) {
    $doc_id = $_GET['id'];

    $db = new DBConnection();
    $success = $db->deleteDocument($doc_id);

}

?>

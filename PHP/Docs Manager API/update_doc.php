<?php

header("Access-Control-Allow-Origin: *");
header("Access-Control-Allow-Methods: GET, POST, OPTIONS");
header("Access-Control-Allow-Headers: Content-Type");

require_once "DBUtils.php"; 

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $doc_id = $_POST['id'];
    $author = $_POST['author'];
    $title = $_POST['title'];
    $noPages = $_POST['noPages'];
    $type = $_POST['type'];

    $db = new DBConnection();
    $success = $db->updateDocument($doc_id, $author, $title, $noPages, $type);

    if ($success) {
        exit();
    } else {
        echo "Failed to update document.";
    }
}
?>

<?php
header("Access-Control-Allow-Origin: *");
header("Access-Control-Allow-Methods: GET, POST, OPTIONS");
header("Access-Control-Allow-Headers: Content-Type");

require_once "DBUtils.php";
$db = new DBConnection();

if (isset($_GET['type']) && $_GET['type'] !== "All") {
    $type = $_GET['type'];
    $docs = $db->selectDocsByType($type);
    echo json_encode($docs);
} else {
    $docs = $db->selectAllDocuments();
    echo json_encode($docs);
}
?>

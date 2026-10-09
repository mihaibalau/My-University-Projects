<?php
header("Access-Control-Allow-Origin: *");
header("Access-Control-Allow-Methods: GET, POST, OPTIONS");
header("Access-Control-Allow-Headers: Content-Type");

require_once "DBUtils.php";
$db = new DBConnection();

if (!isset($_GET['id']) || !is_numeric($_GET['id'])) {
    echo json_encode(["error" => "Missing or invalid document ID"]);
    exit;
}

$id = $_GET['id'];
$doc = $db->selectDocumentById($id);

echo json_encode($doc);
?>

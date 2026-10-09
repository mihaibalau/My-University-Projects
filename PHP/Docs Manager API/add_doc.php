<?php
require_once "DBUtils.php"; 
header("Access-Control-Allow-Origin: *");
header("Content-Type: application/json");

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $data = json_decode(file_get_contents("php://input"), true);

    $author = $data["author"];
    $title = $data["title"];
    $noPages = $data["noPages"];
    $type = $data["type"];

    $db = new DBConnection();
    $success = $db->insertDocument($author, $title , $noPages, $type);

    echo json_encode(["success" => $success]);
    exit;
}
?>

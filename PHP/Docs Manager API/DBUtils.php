<?php
header("Access-Control-Allow-Origin: *");
header("Access-Control-Allow-Methods: GET, POST, OPTIONS");
header("Access-Control-Allow-Headers: Content-Type");

class DBConnection
{
    private $host = "localhost";
    private $user = "root";
    private $pass = "";
    private $db = "documentsdb";
    private $charset = 'utf8';

    private $pdo;
    private $error;

    public function __construct()
    {
        $dsn = "mysql:host=$this->host;dbname=$this->db;charset=$this->charset";
        $opt = array(
            PDO::ATTR_ERRMODE   => PDO::ERRMODE_EXCEPTION,
            PDO::ATTR_DEFAULT_FETCH_MODE => PDO::FETCH_ASSOC,
            PDO::ATTR_EMULATE_PREPARES   => false
        );

        try {
            $this->pdo = new PDO($dsn, $this->user, $this->pass, $opt);
        } 
        catch (PDOException $e) {
            $this->error = $e->getMessage();
            echo "Error connecting to DB: " . $this->error;
        }
    }

    public function insertDocument($author, $title, $noPages, $type)
    {
        $stmt = $this->pdo->prepare(
            "INSERT INTO documents (author, title, noPages, type) VALUES (?, ?, ?, ?)"
        );
        return $stmt->execute([$author, $title, $noPages, $type]);
    }


    public function selectAllDocuments()
    {
        $stmt = $this->pdo->prepare("SELECT * FROM documents");
        $stmt->execute();
        return $stmt->fetchAll();
    }
    
    public function selectDocumentById($docId)
    {
        $stmt = $this->pdo->prepare("SELECT * FROM documents WHERE id = ?");
        $stmt->execute([$docId]);
        return $stmt->fetch(); 
    }

    public function selectDocsByType($type)
    {
        $stmt = $this->pdo->prepare("SELECT * FROM documents WHERE type = ?");
        $stmt->execute([$type]);
        return $stmt->fetchAll(); 
    }

    public function updateDocument($id, $author, $title, $noPages, $type)
    {
        $stmt = $this->pdo->prepare("
            UPDATE documents 
            SET author = ?, title = ?, noPages = ?, type = ? 
            WHERE id = ?
        ");
        return $stmt->execute([$author, $title, $noPages, $type, $id]);
    }


    public function deleteDocument($id)
    {
        $stmt = $this->pdo->prepare("DELETE FROM documents WHERE id = ?");
        return $stmt->execute([$id]);
    }
}


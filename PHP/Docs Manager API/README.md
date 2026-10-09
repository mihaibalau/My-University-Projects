# Docs Manager API

PHP backend for a document library, written for the web course. The Angular screens that call it are in `TypeScript/Docs Manager`.

There is no framework. Each script is one request:

- `get_documents.php` returns every document, or only one type when the query string has `type`
- `get_doc_by_id.php` returns a single row
- `add_doc.php`, `update_doc.php` and `delete_doc.php` read a JSON body and answer with a success flag

`DBUtils.php` opens a PDO connection to MySQL (`documentsdb`) and runs prepared statements. A document has an author, a title, a page count and a type (book, novel, thriller, poetry). The responses send CORS headers so the Angular app can call the scripts from another port.

Technologies: PHP, PDO, MySQL, JSON.

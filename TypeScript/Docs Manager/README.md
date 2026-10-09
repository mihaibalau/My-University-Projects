# Docs Manager

Angular frontend for the document library from the web course. It talks to the PHP scripts in `PHP/Docs Manager API`.

The home screen loads the list and filters it by type (all, book, novel, thriller, poetry) through a reactive form control. Add and edit are separate routes: `/add` and `/edit/:id`. The list is kept in a signal and refreshed after the filter changes. Requests go out with `HttpClient` to the PHP endpoints (`get_documents.php`, `add_doc.php`, and the get-by-id / update / delete scripts).

Components are standalone. Routing and the HTTP client are registered in `app.config.ts`.

Technologies: TypeScript, Angular (standalone components, signals, reactive forms, `HttpClient`).

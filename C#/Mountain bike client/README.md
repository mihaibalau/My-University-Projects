# Mountain bike client

Windows Forms client for the Mountain bike racing database from the databases course. The schema and the SQL scripts live in `SQL/Mountain Bike Racing`.

The form loads the parent table (bikers). Selecting a row loads only the child rows that point at that biker (bikes). Add, update and delete use `SqlDataAdapter` with parameters, not string-concatenated values. Table names, primary keys, the foreign key and the delete statement are read from `App.config`. The commented block in that file switches the same form to bikes and their maintenance records, which was the point of the lab: one screen, two parent-child pairs.

Technologies: C#, .NET Framework 4.7.2, Windows Forms, ADO.NET, SQL Server.



USE [Mountain bike racing]
GO

DELETE FROM CompetitionParticipants;
DELETE FROM Bikers;
DELETE FROM Bikes;
DELETE FROM Competitions;

-- (!) insert data – for at least 4 tables; at least one statement must violate referential integrity constraints;

insert into Bikers(BikerID, Age, Name) values (1001, 25, 'Vasile')
insert into Bikers(BikerID, Age, Name) values (1002, 19, 'Ioana')
insert into Bikers(BikerID, Age, Name) values (1003, 47, 'Carl')
insert into Bikers(BikerID, Age, Name) values (1004, 34, 'Rudolf')
insert into Bikers(BikerID, Age, Name) values (1005, 21, 'Anca')
insert into Bikers(BikerID, Age, Name) values (1006, 28, 'Elisabeta')

insert into Bikes(BikeSeries, Model, Value, BikerId) values (27412369, 'Cannondale', 3500, 1001) -- The one with error
insert into Bikes(BikeSeries, Model, Value) values (79684215, 'Specialized', 4800);
insert into Bikes(BikeSeries, Model, Value) values (71023653, 'Cube', 2400);
insert into Bikes(BikeSeries, Model, Value) values (51936414, 'DHS', 1000);
insert into Bikes(BikeSeries, Model, Value) values (13719245, 'Devron', 1300, 1003);
insert into Bikes(BikeSeries, Model, Value) values (81233672, 'Santa Cruz', 5600);
insert into Bikes(BikeSeries, Model, Value) values (51814244, 'Giant', 5000);
insert into Bikes(BikeSeries, Model, Value) values (34634254, 'Nukeproof', 6200);
insert into Bikes(BikeSeries, Model, Value) values (61345152, 'Sprint', 1800);
insert into Bikes(BikeSeries, Model, Value) values (25647251, 'Cross', 1700);

insert into Competitions(CompetitionId, CompetitionName) values (501, 'Macin')
insert into Competitions(CompetitionId, CompetitionName) values (502, 'Via Maria Theresia')
insert into Competitions(CompetitionId, CompetitionName) values (503, 'Unde-i ursu?')
insert into Competitions(CompetitionId, CompetitionName) values (504, 'Straja')

insert into CompetitionParticipants(BikerId, BikeSeries, CompetitionId) values (1001, 79684215, 501)
insert into CompetitionParticipants(BikerId, BikeSeries, CompetitionId) values (1003, 51814244, 501)
insert into CompetitionParticipants(BikerId, BikeSeries, CompetitionId) values (1006, 34634254, 501)
insert into CompetitionParticipants(BikerId, BikeSeries, CompetitionId) values (1004, 25647251, 502)
insert into CompetitionParticipants(BikerId, BikeSeries, CompetitionId) values (1006, 34634254, 502)
insert into CompetitionParticipants(BikerId, BikeSeries, CompetitionId) values (1001, 79684215, 503)
insert into CompetitionParticipants(BikerId, BikeSeries, CompetitionId) values (1002, 71023653, 503)
insert into CompetitionParticipants(BikerId, BikeSeries, CompetitionId) values (1005, 13719245, 503)
insert into CompetitionParticipants(BikerId, BikeSeries, CompetitionId) values (1006, 34634254, 503)
insert into CompetitionParticipants(BikerId, BikeSeries, CompetitionId) values (1002, 71023653, 504)


-- (!) update data – for at least 3 tables;

update Bikes
	set Bikes.BikerId = 1002 where Bikes.BikeSeries = 51936414;
update Bikes
	set Bikes.BikerId = 1003 where Bikes.BikeSeries = 81233672;
update Bikes
	set Bikes.BikerId = 1004 where Bikes.BikeSeries = 34634254;
update Bikes
	set Bikes.BikerId = 1005 where Bikes.BikeSeries = 61345152;
update Bikes
	set Bikes.BikerId = 1006 where Bikes.BikeSeries = 25647251;

-- Decrease the age for girls
update Bikers
	set Bikers.Age = Age - 1 where Bikers.Name like '%a'

-- Decrease the price for not owned bikes
update Bikes
	set Bikes.Value = Bikes.Value * 0.8 where Bikes.BikerId is NULL

-- Update the new purchased bike for a biker
update CompetitionParticipants
	set CompetitionParticipants.BikeSeries = 81233672 where CompetitionParticipants.BikeSeries = 34634254 OR CompetitionParticipants.BikerId = 1006
	

-- (!) delete data – for at least 2 tables.

-- Delete the premium bikes which wasn't sold
delete from Bikes 
	where Bikes.BikerId is NULL 
	and Bikes.value between 4000 and 10000

-- Delete the expensive bikes from the "Unde-i ursu?" comptetion
delete from CompetitionParticipants 
	where BikeSeries IN 
	(select Bikes.BikeSeries from Bikes 
		where Bikes.BikerId is not NULL and Value > 4000);


-- (!) 2 queries with the union operation; use UNION [ALL] and OR;

-- All available bikers for 503 competition
select DISTINCT CompetitionParticipants.BikerId from CompetitionParticipants
	where CompetitionParticipants.CompetitionId = 503
UNION ALL
select Bikes.BikerId from Bikes 
	where Bikes.Value <= 4000 * 0.99;

-- All bikers from competitions 501 and 502
select TOP 10 CompetitionParticipants.BikeSeries from CompetitionParticipants 
	where CompetitionParticipants.CompetitionId = 501 
	OR CompetitionParticipants.CompetitionId = 502


--  (!) 2 queries with the intersection operation; use INTERSECT and IN;

-- All bikers which participate to a competition
select Bikers.BikerID from Bikers
INTERSECT
select CompetitionParticipants.BikerId from CompetitionParticipants

select Bikers.BikerID from Bikers
	where Bikers.BikerID IN 
	(select CompetitionParticipants.BikerId from CompetitionParticipants)


-- (!) 2 queries with the difference operation; use EXCEPT and NOT IN;

-- All bikers which don't participate to a competition
select DISTINCT Bikers.BikerID from Bikers
EXCEPT
select CompetitionParticipants.BikerId from CompetitionParticipants where CompetitionParticipants.BikerId = 1002;

select Bikers.BikerID from Bikers
	where Bikers.BikerID NOT IN 
	(select CompetitionParticipants.BikerId from CompetitionParticipants)


-- (!) 4 queries with INNER JOIN, LEFT JOIN, RIGHT JOIN, and FULL JOIN (one query per operator); 
-- one query will join at least 3 tables, while another one will join at least two many-to-many relationships;

-- The table with bikers who participate at a competition and have a bike
select DISTINCT Bikers.BikerID, Bikers.Name, Bikes.Model, CompetitionParticipants.CompetitionId from Bikers
INNER JOIN Bikes on Bikes.BikerId = Bikers.BikerID
INNER JOIN CompetitionParticipants on CompetitionParticipants.BikerId =  Bikers.BikerID

-- The bikers and his bikes
select TOP 5 Bikers.BikerID, Bikers.Name, Bikes.Model, Bikes.Value from Bikers
LEFT JOIN Bikes on Bikers.BikerID = Bikes.BikerId

-- The bikes and his owners
select Bikers.Name, Bikes.BikeSeries, Bikes.Model, Bikes.Value from Bikers
RIGHT JOIN Bikes on Bikers.BikerID = Bikes.BikerId

-- All bikers and all competitions
select Bikers.Name, Competitions.CompetitionName from Bikers
FULL JOIN CompetitionParticipants on Bikers.BikerID = CompetitionParticipants.BikerID
FULL JOIN Competitions on CompetitionParticipants.CompetitionID = Competitions.CompetitionID;


-- (!) 2 queries with the EXISTS operator and a subquery in the WHERE clause;

select Bikers.Name from Bikers
	where EXISTS 
	(select 1 from CompetitionParticipants where CompetitionParticipants.BikerID = Bikers.BikerID AND CompetitionParticipants.CompetitionID = 503);

select Bikers.BikerID from Bikers
	where EXISTS 
	(select 1 from Bikes where Bikes.BikerID = Bikers.BikerID);


-- (!) 2 queries with the IN operator and a subquery in the WHERE clause; 
-- in at least one case, the subquery must include a subquery in its own WHERE clause;

select Model, Value from Bikes where Value IN 
	(select Value from Bikes where BikerId IS NOT NULL);

select Name from Bikers where Age IN 
	(select Age from CompetitionParticipants cp JOIN Bikers b on cp.BikerId = b.BikerID where cp.CompetitionId = 503);


-- (!) 2 queries with a subquery in the FROM clause;  

select Model, AvgValue from 
	(select Model , AVG(Value) as AvgValue from Bikes group by Model) as BikeAverages
order by AvgValue desc;

select CompetitionId, TotalParticipants from 
	( select CompetitionId, COUNT(BikerId) as TotalParticipants from CompetitionParticipants
    group by CompetitionId ) as CompetitionCounts
order by TotalParticipants asc;


-- (!) 4 queries with the GROUP BY clause, 3 of which also contain the HAVING clause; 
-- 2 of the latter will also have a subquery in the HAVING clause; 

select Age, COUNT(BikerID) as NumberOfBikers from Bikers group by Age

select Model, SUM(Value) AS TotalValue from Bikes
	group by Model having SUM(Value) > (select AVG(Value) FROM Bikes);

select CompetitionId, COUNT(BikerId) as ParticipantCount from CompetitionParticipants
	group by CompetitionId having COUNT(BikerId) > 
		(select AVG(ParticipantCount) from (select CompetitionId, COUNT(BikerId) as ParticipantCount 
			from CompetitionParticipants group by CompetitionId) as CompCount);

select Model, AVG(Value) as AvgValue, MIN(Value) as MinValue from Bikes
	group by Model having AVG(Value) > 3000 AND MIN(Value) > 2000;


-- (!) 4 queries using ANY and ALL to introduce a subquery in the WHERE clause (2 queries per operator); 
-- rewrite 2 of them with aggregation operators, and the other 2 with IN / [NOT] IN.

select Model, Value from Bikes where Value < ANY 
	(select Value from Bikes where BikerId IS NOT NULL);

select Name from Bikers where Age > ANY 
	(select Age from CompetitionParticipants cp JOIN Bikers b ON cp.BikerId = b.BikerID where cp.CompetitionId = 503);

select Model, Value from Bikes where Value > ALL 
	(select Bikes.Value from Bikes JOIN CompetitionParticipants on Bikes.BikeSeries = CompetitionParticipants.BikeSeries where CompetitionId = 501);

select Name from Bikers where Age > ALL 
	(select Age from Bikers b JOIN Bikes on b.BikerID = Bikes.BikerId where Bikes.Model = 'Cube');

select Model, Value from Bikes where Value > 
	(select MAX(Value) from Bikes b JOIN CompetitionParticipants cp on b.BikeSeries = cp.BikeSeries where cp.CompetitionId = 501);

select Name from Bikers where Age > 
	(select MAX(Age) from Bikers b JOIN Bikes on b.BikerID = Bikes.BikerId where Bikes.Model = 'Cube');

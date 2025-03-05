
DROP PROCEDURE IF EXISTS newColumnType
GO
DROP PROCEDURE IF EXISTS newColumnTypeBackup
GO

DROP PROCEDURE IF EXISTS addNewColumn
GO
DROP PROCEDURE IF EXISTS removeExistentColumn
GO

DROP PROCEDURE IF EXISTS addNewConstaint
GO
DROP PROCEDURE IF EXISTS removeExistentConstaint
GO

DROP PROCEDURE IF EXISTS createNewTable
GO
DROP PROCEDURE IF EXISTS deleteExistentTable
GO

DROP PROCEDURE IF EXISTS addNewPrimaryKey
GO
DROP PROCEDURE IF EXISTS removePrimaryKey
GO

DROP PROCEDURE IF EXISTS addNewCandidateKey
GO
DROP PROCEDURE IF EXISTS removeExistentCandidateKey
GO

DROP PROCEDURE IF EXISTS addNewForeignKey
GO
DROP PROCEDURE IF EXISTS removeForeignKey
GO

DROP PROCEDURE IF EXISTS createDatabaseVersionTable
GO
DROP PROCEDURE IF EXISTS createVersionsTable
GO

DROP PROCEDURE IF EXISTS changeVersion
GO
DROP PROCEDURE IF EXISTS insertVersions
GO

-- modify the type of a column;

CREATE PROCEDURE newColumnType
AS
	ALTER TABLE  RaceResults 
	ALTER COLUMN TimeTaken VARCHAR(12)
GO

CREATE PROCEDURE newColumnTypeBackup
AS
	ALTER TABLE  RaceResults 
	ALTER COLUMN TimeTaken DECIMAL(5, 2)
GO

-- add / remove a column;

CREATE PROCEDURE addNewColumn
AS
    ALTER TABLE SponsorContracts
    ADD ContractValue INT
GO

CREATE PROCEDURE removeExistentColumn
AS
    ALTER TABLE SponsorContracts
    DROP COLUMN ContractValue
GO

-- add / remove a DEFAULT constraint;

CREATE PROCEDURE addNewConstaint
AS
	ALTER TABLE TrainingSessions
	ADD CONSTRAINT DF_Duration DEFAULT 3 for Duration
GO

CREATE PROCEDURE removeExistentConstaint
AS
	ALTER TABLE TrainingSessions
	DROP CONSTRAINT DF_Duration
GO

-- create / drop a table.

CREATE PROCEDURE createNewTable
AS
	CREATE TABLE Supporters(
		ID INT NOT NULL,
		Name VARCHAR(100),
		BikerID INT,
		BikerBikeSeries INT
	)
GO

CREATE PROCEDURE deleteExistentTable
AS
	DROP TABLE Supporters
GO

-- add / remove a primary key;

CREATE PROCEDURE addNewPrimaryKey
AS
	ALTER TABLE Supporters
	ADD CONSTRAINT PK_Supporters PRIMARY KEY (ID)
GO

CREATE PROCEDURE removePrimaryKey
AS
	ALTER TABLE Supporters
	DROP CONSTRAINT PK_Supporters
GO

-- add / remove a candidate key;

CREATE PROCEDURE addNewCandidateKey
AS
	ALTER TABLE Supporters
	ADD CONSTRAINT UQ_Supporter UNIQUE (BikerID, BikerBikeSeries);
GO

CREATE PROCEDURE removeExistentCandidateKey
AS
	ALTER TABLE Supporters
	DROP CONSTRAINT UQ_Supporter
GO

-- add / remove a foreign key;

CREATE PROCEDURE addNewForeignKey
AS
	ALTER TABLE Supporters
	ADD CONSTRAINT FK_Biker FOREIGN KEY (BikerID) REFERENCES Bikers(BikerID)
GO

CREATE PROCEDURE removeForeignKey
AS
	ALTER TABLE Supporters
	DROP CONSTRAINT FK_Biker
GO

-----------------

-- Create a new table that holds the current version of the database schema. 
-- Simplifying assumption: the version is an integer number.

CREATE OR ALTER PROCEDURE createDatabaseVersionTable
AS
	DROP TABLE databaseVersion
	CREATE TABLE databaseVersion(
		Vers INT DEFAULT 0
	)
	INSERT INTO databaseVersion(Vers) VALUES (0)
GO

CREATE PROCEDURE createVersionsTable
AS
	CREATE TABLE Versions(
		currentProcedure VARCHAR(100),
		previousProcedure VARCHAR(100),
		versionId INT UNIQUE)
GO

-- Write a stored procedure that receives as a parameter a version number and brings the database to that version.

CREATE PROCEDURE insertVersions
AS
	INSERT INTO Versions(currentProcedure, previousProcedure, versionId) VALUES
		('newColumnType', 'newColumnTypeBackup', 1),
		('addNewColumn', 'removeExistentColumn', 2),
		('addNewConstaint', 'removeExistentConstaint', 3),
		('deleteExistentTable', 'createNewTable', 4),
		('addNewPrimaryKey', 'removePrimaryKey', 5),
		('addNewCandidateKey', 'removeExistentCandidateKey', 6),
		('addNewForeignKey', 'removeForeignKey', 7)
GO

CREATE PROCEDURE changeVersion @newVersion INT
AS
BEGIN

    DECLARE @currentVersion INT
    SET @currentVersion = (SELECT Vers FROM databaseVersion)
    
    IF @newVersion = @currentVersion
    BEGIN
        PRINT 'Inputed version is the same as current one!'
        RETURN
    END
    ELSE
    BEGIN
        DECLARE @currentProcedure VARCHAR(50)
        IF @currentVersion < @newVersion
        BEGIN
            WHILE @currentVersion < @newVersion
            BEGIN
                SET @currentProcedure = (SELECT currentProcedure FROM Versions WHERE versionId = @currentVersion + 1)
                EXEC(@currentProcedure)
                SET @currentVersion = @currentVersion + 1
            END
        END
        ELSE
        BEGIN
            WHILE @currentVersion > @newVersion
            BEGIN
                SET @currentProcedure = (SELECT previousProcedure FROM Versions WHERE versionId = @currentVersion)
                EXEC(@currentProcedure)
                SET @currentVersion = @currentVersion - 1
            END
        END
        UPDATE databaseVersion SET Vers = @newVersion
        PRINT 'The version was updated!'
    END
END
GO

-----------------
EXEC newColumnType
EXEC newColumnTypeBackup

EXEC addNewColumn
EXEC removeExistentColumn

EXEC addNewConstaint
EXEC removeExistentConstaint

EXEC deleteExistentTable
EXEC createNewTable

EXEC addNewPrimaryKey
EXEC removePrimaryKey

EXEC addNewCandidateKey
EXEC removeExistentCandidateKey

EXEC addNewForeignKey
EXEC removeForeignKey

EXEC createDatabaseVersionTable

EXEC changeVersion 1
--------

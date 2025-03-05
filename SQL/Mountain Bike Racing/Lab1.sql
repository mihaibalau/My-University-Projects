-- Imagine a simple application that requires a database. Represent the application data in a relational structure and implement the structure in a SQL Server database. 
--The database must contain at least: 10 tables, two 1:n relationships, one m:n relationship.

-- Use Mountain bike racing database
-- Create database [Mountain bike racing];

USE [Mountain bike racing];
GO

CREATE TABLE Bikers(
    BikerID INT PRIMARY KEY,
    Name VARCHAR(50) NOT NULL,
    Age INT
);	

CREATE TABLE Bikes(
    BikeSeries INT PRIMARY KEY,
    Model VARCHAR(50) NOT NULL,
    Value INT NOT NULL,
    BikerId INT NULL,
    FOREIGN KEY (BikerId) REFERENCES Bikers(BikerId)
);

CREATE TABLE Competitions (
    CompetitionId INT PRIMARY KEY,
    CompetitionName VARCHAR(100)
);

CREATE TABLE CompetitionParticipants (
    CompetitionId INT,
    BikerId INT, 
    BikeSeries INT,
    
    FOREIGN KEY (CompetitionId) REFERENCES Competitions(CompetitionId),
    FOREIGN KEY (BikerId) REFERENCES Bikers(BikerId),
    FOREIGN KEY (BikeSeries) REFERENCES Bikes(BikeSeries),

    PRIMARY KEY (CompetitionId, BikerId, BikeSeries)
);

CREATE TABLE RaceResults (
    ResultId INT PRIMARY KEY,
    CompetitionId INT NOT NULL,
    BikerId INT NOT NULL,
    Position INT,
    TimeTaken DECIMAL(5, 2),
    FOREIGN KEY (CompetitionId) REFERENCES Competitions(CompetitionId),
    FOREIGN KEY (BikerId) REFERENCES Bikers(BikerId)
);

CREATE TABLE Sponsors (
    SponsorId INT PRIMARY KEY,
    SponsorName VARCHAR(100) NOT NULL,
    SponsorType VARCHAR(50) 
);


CREATE TABLE SponsorContracts (
    SponsorId INT NOT NULL,
    BikerId INT NOT NULL,
    ContractDetails VARCHAR(200),
    StartDate DATE,
    EndDate DATE,
    FOREIGN KEY (SponsorId) REFERENCES Sponsors(SponsorId),
    FOREIGN KEY (BikerId) REFERENCES Bikers(BikerId),
    PRIMARY KEY (SponsorId, BikerId)
);

CREATE TABLE BikeMaintenance (
    MaintenanceId INT PRIMARY KEY,
    BikeSeries INT NOT NULL,
    MaintenanceDate DATE NOT NULL,
    Description VARCHAR(200),
    Cost DECIMAL(10, 2),
    FOREIGN KEY (BikeSeries) REFERENCES Bikes(BikeSeries)
);


CREATE TABLE BikeComponents (
    ComponentSetupID INT PRIMARY KEY,
    BikeSeries INT NOT NULL,
    Transmision VARCHAR(50) NOT NULL,
    Brakes VARCHAR(50) NOT NULL,
    Shocks VARCHAR(50) NOT NULL,
    InstallationDate DATE,
    FOREIGN KEY (BikeSeries) REFERENCES Bikes(BikeSeries)
);


CREATE TABLE TrainingSessions (
    SessionId INT PRIMARY KEY,
    BikerId INT NOT NULL,
    SessionDate DATE NOT NULL,
    Duration DECIMAL(4, 2),
    TrainingType VARCHAR(50),
    FOREIGN KEY (BikerId) REFERENCES Bikers(BikerId)
);

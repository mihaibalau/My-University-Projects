
Use [Mountain bike racing]

GO
CREATE FUNCTION uf_ValidateCompetition (@name NVARCHAR(100)) RETURNS INT AS
BEGIN
	DECLARE @return INT;
	SET @return = 0;
	IF LEN(@name) > 2
		SET @return = 1;
	RETURN @return;
END;
GO

CREATE FUNCTION uf_ValidateBiker (@name VARCHAR(50), @age INT) RETURNS INT AS
BEGIN
	DECLARE @return INT;
	SET @return = 0;
	IF @name is not NULL AND LEN(@name) >= 3
		IF @age is not NULL AND @age > 0
			SET @return = 1;
	RETURN @return;
END;
GO

CREATE FUNCTION uf_ValidateParticipant(@bikeSeries INT) RETURNS INT AS
BEGIN
	DECLARE @return INT;
	SET @return = 0;
	IF @bikeSeries is not NULL AND @bikeSeries > 0
		SET @return = 1;
	RETURN @return;
END;
GO

CREATE TABLE LogTable(
	Lid INT IDENTITY PRIMARY KEY,
	TypeOperation VARCHAR(50),
	TableOperation VARCHAR(50),
	ExecutionDate DATETIME)

GO
CREATE OR ALTER PROCEDURE sp_AddBikerWithCompetitioon_scenario1
	@Name NVARCHAR(50),
	@Age INT,
	@CompetitonName NVARCHAR(100)
AS
BEGIN
	DECLARE @BikerID INT, @CompetitionID INT, @BikeSeries INT;
	BEGIN TRANSACTION;
	BEGIN TRY
		IF dbo.uf_ValidateBiker(@Name, @Age) = 0
			RAISERROR('Invalid name or age for biker', 14, 1);
		IF dbo.uf_ValidateCompetition(@CompetitonName) = 0
			RAISERROR('Invalid competiton name', 14, 1);

		INSERT INTO Competitions(CompetitionName) 
		VALUES (@CompetitonName);
		SET @CompetitionID = SCOPE_IDENTITY();

		INSERT INTO Bikers(Name, Age)
		VALUES (@Name, @Age);
		SET @BikerID = SCOPE_IDENTITY();

		INSERT INTO CompetitionParticipants(CompetitionID, BikerID)
		VALUES (@CompetitionID, @BikerID);

		COMMIT TRANSACTION;
		SELECT 'Transaction commited'
	END TRY
BEGIN CATCH
		ROLLBACK TRANSACTION;
		SELECT 
			'Transaction Rollbackend' AS Status,
			ERROR_NUMBER() AS ErrorNumber,
			ERROR_MESSAGE() AS ErrorMessage,
			ERROR_LINE() AS ErrorLine,
			ERROR_PROCEDURE() AS ErrorProcedure;
	END CATCH
END;
GO

Select * from CompetitionParticipants;
Select * from Competitions;
Select * from Bikers;

EXEC sp_AddBikerWithCompetitioon_scenario1
    @Name = 'Alexandru',
    @Age = 20,
    @CompetitonName = 'Vertical Race 2025';

Select * from CompetitionParticipants;
Select * from Competitions;
Select * from Bikers;



EXEC sp_AddBikerWithCompetitioon_scenario1
    @Name = 'Ab',  -- Less than 3 characters
    @Age = 20,
    @CompetitonName = 'Vertical Race 2025';

Select * from CompetitionParticipants;
Select * from Competitions;
Select * from Bikers;





Use [Mountain bike racing]

GO
CREATE OR ALTER PROCEDURE sp_AddBikerWithCompetitioon_scenario2
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

		INSERT INTO Bikers(Name, Age)
		VALUES (@Name, @Age);
		SET @BikerID = SCOPE_IDENTITY();

		COMMIT TRANSACTION;
		SELECT 'First transaction commited'
	END TRY
	BEGIN CATCH
		ROLLBACK TRANSACTION;
		SELECT 
			'First transaction Rollbackend' AS Status,
			ERROR_NUMBER() AS ErrorNumber,
			ERROR_MESSAGE() AS ErrorMessage,
			ERROR_LINE() AS ErrorLine,
			ERROR_PROCEDURE() AS ErrorProcedure;
	END CATCH

	
	BEGIN TRANSACTION;
	BEGIN TRY
		IF dbo.uf_ValidateCompetition(@CompetitonName) = 0
			RAISERROR('Invalid competiton name', 14, 1);

		INSERT INTO Competitions(CompetitionName) 
		VALUES (@CompetitonName);
		SET @CompetitionID = SCOPE_IDENTITY();

		COMMIT TRANSACTION;
		SELECT 'Second transaction commited'
	END TRY
	BEGIN CATCH
		ROLLBACK TRANSACTION;
		SELECT 
			'Second transaction Rollbackend' AS Status,
			ERROR_NUMBER() AS ErrorNumber,
			ERROR_MESSAGE() AS ErrorMessage,
			ERROR_LINE() AS ErrorLine,
			ERROR_PROCEDURE() AS ErrorProcedure;
	END CATCH


	
	BEGIN TRANSACTION;
	BEGIN TRY

		INSERT INTO CompetitionParticipants(CompetitionID, BikerID)
		VALUES (@CompetitionID, @BikerID);

		COMMIT TRANSACTION;
		SELECT 'Third transaction commited'
	END TRY
	BEGIN CATCH
		ROLLBACK TRANSACTION;
		SELECT 
			'Third transaction Rollbackend' AS Status,
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

EXEC sp_AddBikerWithCompetitioon_scenario2
    @Name = 'Alexandru',
    @Age = 20,
    @CompetitonName = 'Vertical Race 2025';

Select * from CompetitionParticipants;
Select * from Competitions;
Select * from Bikers;



EXEC sp_AddBikerWithCompetitioon_scenario2
    @Name = 'Ab',  -- Less than 3 characters
    @Age = 20,
    @CompetitonName = 'Vertical Race 2025';

Select * from CompetitionParticipants;
Select * from Competitions;
Select * from Bikers;




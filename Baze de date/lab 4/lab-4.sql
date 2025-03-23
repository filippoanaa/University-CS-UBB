--comanda : 1 pk, no fk
--produs: 1 pk, 2 fk
--comanda_produse: 2 pk
INSERT INTO Tables(Name) VALUES
('comanda'), ('produs'), ('comanda_produse');
SELECT* FROM Tables

CREATE VIEW view_1 AS 
    SELECT pret from comanda

CREATE VIEW view_2 AS
    SELECT  a.judet, f.nume, t.fix
	FROM adresa a
	JOIN furnizor f ON a.furnizor_id = f.id
	JOIN telefon t ON f.id = t.furnizor_id
	WHERE t.fix IS NOT NULL;

CREATE VIEW view_3 AS
	SELECT m.id AS numar_masa, COUNT(cl.id) AS numar_clienti, a.nume AS angajat
	FROM masa m
	JOIN angajat a ON m.angajat_id = a.id
	JOIN client cl ON m.id = cl.masa_id
	WHERE cl.specificatii LIKE '%Fara gluten%'
	GROUP BY m.id, a.nume;

INSERT INTO Views(Name) VALUES
('view_1'), ('view_2'), ('view_3')
SELECT * FROM Views
delete from Views

INSERT INTO Tests(Name) VALUES
('deletion'), ('insertion'), ('evaluation');
SELECT* FROM Tests
delete from Tests

INSERT INTO TestViews(TestID, ViewID) VALUES
(3,1), (3,2),(3,3);
SELECT * FROM TestViews
delete from TestViews

INSERT INTO TestTables(TestID, TableID,NoOfRows,Position) VALUES
(1,1,50,3),(1,2,50,2), (1,3,50,1);
INSERT INTO TestTables(TestID, TableID,NoOfRows,Position) VALUES
(2,1,100,1),(2,2,100,2),(2,3,100,3);
select * from TestTables
delete from TestTables

go
CREATE OR ALTER PROCEDURE insertion (@no_of_rows INT, @position INT)
AS
BEGIN
	DECLARE @index INT
	SET @index = 1

	WHILE @index <= @no_of_rows
	BEGIN
		IF @position = 1
		BEGIN
		
			DECLARE @id_comanda INT, @pret_comanda INT
			SET @id_comanda = (SELECT MAX(id) FROM comanda) + 1
			SET @pret_comanda = CAST((SELECT RAND() * (200 - 5 ) + 5) AS INT)

			INSERT INTO comanda(id, pret) VALUES (@id_comanda, @pret_comanda)
		END

		IF @position = 2
		BEGIN
			
			DECLARE @id_produs INT, @nume VARCHAR(50), @descriere VARCHAR(50), @pret_produs INT, @categorie_id INT, @furnizor_id INT

			SET @id_produs = (SELECT MAX(id) FROM produs) + 1
			SET @nume = CONCAT('Nume', @id_produs)
			SET @descriere = CONCAT('Descriere', @id_produs)
			SET @pret_produs = CAST((SELECT RAND() * (70 - 5 ) + 5) AS INT)
			SET @categorie_id = CAST((SELECT RAND() * 2 + 1) AS INT)

			DECLARE @min_id_furnizor INT, @max_id_furnizor INT
			SET @min_id_furnizor = (SELECT MIN(id) FROM furnizor)
			SET @max_id_furnizor = (SELECT MAX(id) FROM furnizor)
			SET @furnizor_id = (SELECT RAND() * (@max_id_furnizor - @min_id_furnizor) + @min_id_furnizor)

			INSERT INTO produs(id, nume, descriere, pret, categorie_id, furnizor_id) VALUES (@id_produs, @nume, @descriere, @pret_produs, @categorie_id, @furnizor_id)

		END

		IF @position = 3 
		BEGIN 
			DECLARE @comanda_id INT, @produs_id INT, @cantitate INT

			DECLARE @min_id_comanda INT, @max_id_comanda INT
			SET @min_id_comanda = (SELECT MIN(id) FROM comanda)
			SET @max_id_comanda = (SELECT MAX(id) FROM comanda)
			SET @comanda_id = (SELECT RAND() * (@max_id_comanda - @min_id_comanda) + @min_id_comanda)

			DECLARE @min_id_produs INT, @max_id_produs INT
			SET @min_id_produs = (SELECT MIN(id) FROM produs)
			SET @max_id_produs = (SELECT MAX(id) FROM produs)
			SET @produs_id = (SELECT RAND() * (@max_id_produs - @min_id_produs) + @min_id_produs)
			
			WHILE EXISTS(SELECT 1 FROM comanda_produse WHERE comanda_id = @comanda_id AND produs_id = @produs_id)
			BEGIN
				SELECT TOP 1 @comanda_id = id
				FROM comanda
				WHERE id NOT IN (
					SELECT comanda_id
					FROM comanda_produse
					WHERE produs_id = @produs_id
				)
				ORDER BY id;


				SELECT TOP 1 @produs_id = id 
				FROM produs
				WHERE id  NOT IN(
					SELECT produs_id
					FROM comanda_produse 
					WHERE comanda_id = @comanda_id
				)
				ORDER BY id;
			END

			SET @cantitate = CAST((SELECT RAND() * 9 + 1) AS INT)

			INSERT INTO comanda_produse(comanda_id, produs_id, cantitate)  VALUES (@comanda_id, @produs_id, @cantitate)
		END

	SET @index = @index + 1

	END
END


go
CREATE OR ALTER PROCEDURE deletion(@no_of_rows INT, @position INT) 
AS
BEGIN
	DECLARE @index INT = 1;

	DECLARE @comanda_id INT, @produs_id INT, @id_comanda INT, @id_produs INT;

	SET @comanda_id = (SELECT MIN(comanda_id) FROM comanda_produse);
	SET @id_produs = (SELECT MIN(id) FROM produs);
	SET @id_comanda = (SELECT MIN(id) FROM comanda);

	WHILE @index <= @no_of_rows
	BEGIN
		IF @position = 1
		BEGIN
			DELETE FROM comanda_produse WHERE comanda_id = @comanda_id

			SET @comanda_id = (SELECT MIN(comanda_id) FROM comanda_produse);

		END

		IF @position = 2
		BEGIN
			PRINT 'Deleting from produs where id = ' + CAST(@id_produs AS VARCHAR);
			DELETE FROM produs WHERE id = @id_produs;

			SET @id_produs = (SELECT MIN(id) FROM produs);
		END

		IF @position = 3
		BEGIN
			
			DELETE FROM comanda WHERE id = @id_comanda;

			SET @id_comanda = (SELECT MIN(id) FROM comanda);
		END

		SET @index = @index + 1;
	END
END

GO
CREATE OR ALTER PROCEDURE evaluation (@no_of_view INT)
AS
BEGIN
	IF @no_of_view = 1
	BEGIN
		SELECT * FROM view_1
	END

	IF @no_of_view = 2
	BEGIN
		SELECT * FROM view_2
	END

	IF @no_of_view = 3
	BEGIN
		SELECT * FROM view_3
	END

END

go
CREATE OR ALTER PROCEDURE MainProcedure
(@tableID VARCHAR(10))
AS
BEGIN
	PRINT 'Starting MainProcedure for TableID: ' + @tableID;
		
	SET @tableID = CONVERT(INT, @tableID)

	DECLARE @startTime DATETIME, @intermediateTime DATETIME, @endTime DATETIME

	DECLARE @table VARCHAR(50), @test VARCHAR(50)

	DECLARE @noOfRows INT, @position INT, @testID INT

	SET @table = (SELECT Name FROM Tables WHERE TableID = @tableID)

	--- Start of tests:
	SET @startTime = GETDATE()
	
	--- Insertion:
	SELECT @test = t.Name, @noOfRows = tt.NoOfRows,  @position = tt.Position
	FROM Tests t INNER JOIN TestTables tt ON t.TestID = tt.TestID
	WHERE tt.TableID = @tableID  AND tt.TestID = 2;

	PRINT 'Calling insertion with @no_of_rows=' + CAST(@noOfRows AS VARCHAR) + ', @position=' + CAST(@position AS VARCHAR);
    EXECUTE insertion @noOfRows, @position;

    --- Deletion:
	SELECT @test = t.Name, @noOfRows = tt.NoOfRows,  @position = tt.Position
	FROM Tests t INNER JOIN TestTables tt ON t.TestID = tt.TestID
	WHERE tt.TableID = @tableID  AND tt.TestID = 1;

	PRINT 'Calling deletion with @no_of_rows=' + CAST(@noOfRows AS VARCHAR) + ', @position=' + CAST(@position AS VARCHAR);
	EXECUTE deletion @noOfRows, @position
	

	SET @intermediateTime = GETDATE()

	--- Evaluation:
	SELECT @test = t.Name
	FROM Tests t
	INNER JOIN TestViews tv ON t.TestID = tv.TestID
	WHERE tv.TestID = 3;

	PRINT 'Starting test : ' + @test + ' for view ' + CAST(@tableId  AS VARCHAR);
	EXECUTE evaluation @tableID

	--- Finish:
	SET @endTime = GETDATE()

	

	INSERT INTO TestRuns(Description, StartAt, EndAt) VALUES ('Modified table: ' + @tableID +  ' + eval view' + CAST(@tableId AS VARCHAR), @startTime, @endTime)
	SET @testID = (SELECT MAX(TestRunID) FROM TestRuns)

	INSERT INTO TestRunTables(TestRunID, TableID, StartAt, EndAt) VALUES (@testID, @tableID, @startTime, @intermediateTime)
	INSERT INTO TestRunViews(TestRunID, ViewID, StartAt, EndAt) VALUES (@testID, @tableID, @intermediateTime, @endTime)

	

END

EXEC MainProcedure 1

select * from comanda
select * from produs
select * from comanda_produse

select * from TestRuns
select * from TestRunTables
select * from TestRunViews

delete from TestRunTables
delete from TestRuns
delete from TestRunViews






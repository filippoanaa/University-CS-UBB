--tabele: comanda, produs, comanda_produse, angajat, categorie
USE cafenea
CREATE OR ALTER FUNCTION validare_comanda(@id INT, @pret INT)
RETURNS VARCHAR(256)
AS
BEGIN
	DECLARE @erori VARCHAR(256);
	SET @erori = '';

	IF (EXISTS( SELECT 1 id FROM comanda WHERE id = @id))
		SET @erori = @erori + ' Exista deja comanda cu id-ul: ' + CONVERT(VARCHAR, @id) + CHAR(13) + CHAR(10);

	IF (@pret < 0) 
		SET @erori = @erori + ' Pretul nu poate fi numar negativ! ' ;

	RETURN @erori;
END

CREATE OR ALTER PROCEDURE CRUD_comanda(@id INT, @pret INT)
AS
BEGIN
	DECLARE @erori VARCHAR(256);
	SET @erori = dbo.validare_comanda(@id, @pret);

	IF ( @erori != '' )
	BEGIN
		PRINT @erori;
		RETURN
	END

	PRINT 'CRUD pe comanda';

	--CREATE
	INSERT INTO comanda(id, pret) VALUES (@id, @pret);
	PRINT 'Am inserat in comanda valorile: ' + CONVERT(VARCHAR, @id) + ' ' +CONVERT(VARCHAR, @pret);

	--READ
	SELECT * FROM comanda;

	--UPDATE
	UPDATE comanda SET pret = @pret + 10 WHERE id = @id;
	PRINT 'Am modificat pretul comenzii cu id-ul: ' + CONVERT(VARCHAR, @id) + ' ' + 'cu: ' + CONVERT(VARCHAR, @pret + 10);
	SELECT * FROM comanda;

	--DELETE
	DELETE FROM comanda WHERE id = @id;
	PRINT 'Am sters comanda cu id-ul: ' + CONVERT(VARCHAR, @id);
	SELECT * FROM comanda;


END

EXEC CRUD_comanda 9, 10
EXEC CRUD_comanda 1, -1


CREATE OR ALTER FUNCTION validare_produs(@id INT, @nume VARCHAR(50), @descriere VARCHAR(50), @pret INT, @cid INT, @fid INT)
RETURNS VARCHAR(1000)
AS
BEGIN
	DECLARE @erori VARCHAR(1000);
	SET @erori = '';

	IF (EXISTS(SELECT 1 FROM produs WHERE id = @id))
		SET @erori = @erori +'Exista deja produs cu id: ' + CONVERT(VARCHAR, @id) + CHAR(13) + CHAR(10);

	IF (@nume = '')
		SET @erori = @erori + 'Numele nu poate fi vid'+ CHAR(13) + CHAR(10);

	 IF (@descriere = '')
        SET @erori = @erori + 'Descrierea nu poate fi vida' + CHAR(13) + CHAR(10);

    IF (@pret < 0)
        SET @erori = @erori + 'Pretul nu poate fi negativ' + CHAR(13) + CHAR(10);

	IF(NOT EXISTS(SELECT 1 id FROM categorie WHERE id = @cid))
		 SET @erori = @erori + 'Categorie invalida'+ CHAR(13) + CHAR(10);
	
	IF( NOT EXISTS(SELECT 1 id FROM furnizor WHERE id = @fid))
		SET @erori = @erori + 'Furnizor invalid'+ CHAR(13) + CHAR(10);
	RETURN @erori;

END

CREATE OR ALTER PROCEDURE CRUD_produs(@id INT, @nume VARCHAR(50), @descriere VARCHAR(50), @pret INT, @cid INT, @fid INT)
AS
BEGIN
	DECLARE @erori VARCHAR(1000);
	SET @erori = dbo.validare_produs(@id, @nume, @descriere, @pret, @cid, @fid);
	
	IF ( @erori != '' )
	BEGIN
		PRINT @erori;
		RETURN
	END

	--CREATE
	INSERT INTO produs(id, nume, descriere, pret, categorie_id, furnizor_id) VALUES (@id, @nume, @descriere, @pret, @cid, @fid);
	PRINT 'Am inserat in produs valorile: '  + CONVERT(VARCHAR, @id) + ' ' + @nume + ' ' + @descriere + ' ' + CONVERT(VARCHAR, @pret) + ' '  + CONVERT(VARCHAR, @cid) + ' '  + CONVERT(VARCHAR, @fid) + ' ' ;

	--READ
	SELECT * FROM produs;

	--UPDATE
	UPDATE produs SET pret = @pret + 10 WHERE id = @id;
	PRINT 'Am modificat pretul produsului cu id-ul: ' + CONVERT(VARCHAR, @id) + ' ' + 'cu: ' + CONVERT(VARCHAR, @pret + 10);
	SELECT * FROM produs;

	--DELETE
	DELETE FROM produs WHERE id = @id;
	PRINT 'Am sters produsul cu id-ul: ' + CONVERT(VARCHAR, @id);
	SELECT * FROM produs;
END

EXEC CRUD_produs 10, 'produs nou', 'descriere', 10, 1,7
EXEC CRUD_produs 1, '', '', -1, 100,700

CREATE OR ALTER FUNCTION validare_comanda_produse(@cid INT, @pid INT, @cantiate INT)
RETURNS VARCHAR(1000)
AS
BEGIN
	DECLARE @erori VARCHAR(1000);
	SET @erori = '';

	IF(EXISTS(SELECT 1 FROM comanda_produse WHERE comanda_id = @cid AND produs_id = @pid))
		SET @erori = @erori +'Exista deja combinatia de id-uri: ' + '(' + CONVERT(VARCHAR, @cid) + ', ' +CONVERT(VARCHAR, @pid)+ ')' + CHAR(13) + CHAR(10);

	IF (NOT EXISTS(SELECT 1 FROM comanda WHERE id = @cid))
		SET @erori = @erori +'Nu exista comanda cu id-ul: ' + CONVERT(VARCHAR, @cid) + CHAR(13) + CHAR(10);

	IF (NOT EXISTS(SELECT 1 FROM produs WHERE id = @pid))
		SET @erori = @erori +'Nu exista produs cu id-ul: ' + CONVERT(VARCHAR, @pid) + CHAR(13) + CHAR(10);

	IF (@cantiate < 0)
		SET @erori = @erori + 'Cantitatea nu poate fi negativa' + CHAR(13) + CHAR(10);

	RETURN @erori;
END


CREATE OR ALTER PROCEDURE CRUD_comanda_produse(@cid INT, @pid INT, @cantiate INT)
AS
BEGIN
	DECLARE @erori VARCHAR(1000);
	SET @erori = dbo.validare_comanda_produse(@cid, @pid, @cantiate);
	
	IF ( @erori != '' )
	BEGIN
		PRINT @erori;
		RETURN
	END

	--CREATE
	INSERT INTO comanda_produse(comanda_id, produs_id, cantitate) VALUES (@cid, @pid, @cantiate);
	PRINT 'Am inserat in comanda_produse valorile: ' + CONVERT(VARCHAR, @cid) + ' ' + CONVERT(VARCHAR, @pid) + ' ' + CONVERT(VARCHAR, @cantiate);
	
	--READ
	SELECT * FROM comanda_produse

	--UPDATE
	UPDATE comanda_produse SET cantitate = @cantiate + 10;
	PRINT 'Am modificat cantiatatea de la id-ul cu: (' + CONVERT(VARCHAR, @cid) + ' ' + CONVERT(VARCHAR, @pid) +') cu ' + CONVERT(VARCHAR, @cantiate + 10);

	--DELETE
	DELETE FROM comanda_produse WHERE comanda_id = @cid AND produs_id = @pid;
	PRINT 'Am sters : (' + CONVERT(VARCHAR, @cid) + ' ' + CONVERT(VARCHAR, @pid) +')';

	SELECT * FROM comanda_produse;

END

EXEC CRUD_comanda_produse 1,1,-1
EXEC CRUD_comanda_produse 1,8,1

CREATE OR ALTER FUNCTION validare_furnizor(@id INT, @nume VARCHAR(50))
RETURNS VARCHAR(256)
AS
BEGIN
	DECLARE @erori VARCHAR(1000);
	SET @erori = '';

	IF(EXISTS(SELECT 1 FROM furnizor WHERE id = @id))
		SET @erori = @erori +'Exista deja furnizor cu id: ' + CONVERT(VARCHAR, @id) + CHAR(13) + CHAR(10);

	IF(EXISTS(SELECT 1 FROM furnizor WHERE nume = @nume))
		SET @erori = @erori +'Exista deja furnizor cu numele: ' + @nume + CHAR(13) + CHAR(10);

	IF(@nume = '')
		SET @erori = @erori + 'Numele nu poate fi vid'+ CHAR(13) + CHAR(10);

	RETURN @erori;
END

CREATE OR ALTER PROCEDURE CRUD_furnizor(@id INT, @nume VARCHAR(50))
AS
BEGIN
	DECLARE @erori VARCHAR(1000);
	SET @erori = dbo.validare_furnizor(@id, @nume);
	
	IF ( @erori != '' )
	BEGIN
		PRINT @erori;
		RETURN
	END

	--CREATE
	INSERT INTO furnizor(id, nume) VALUES (@id, @nume);
	PRINT 'Am inserat in furnizor valorile: '  + CONVERT(VARCHAR, @id) + ' ' + @nume + CHAR(13) + CHAR(10);

	--READ
	SELECT * FROM furnizor;

	--UPDATE
	UPDATE furnizor SET nume = 'nume nou' WHERE id = @id;
	PRINT 'Am modificat numele furnizorului: '  + CONVERT(VARCHAR, @id) + 'cu: nume nou';
	SELECT * FROM furnizor;

	--DELETE
	DELETE FROM furnizor WHERE id = @id;
	PRINT 'Am sters furnizorul cu id-ul: ' + CONVERT(VARCHAR, @id);
	SELECT * FROM furnizor;
END

EXEC CRUD_furnizor 9, 'Carrefour';
EXEC CRUD_furnizor 1, 'Lidl';

CREATE OR ALTER FUNCTION valideaza_angajat(@id INT, @nume VARCHAR(50), @functie VARCHAR(50), @salariu INT)
RETURNS VARCHAR(1000)
AS
BEGIN
    DECLARE @erori VARCHAR(1000);
    SET @erori = '';

    IF (EXISTS(SELECT 1 FROM angajat WHERE id = @id))
    BEGIN
        SET @erori = @erori + 'Exista deja angajat cu id-ul: ' + CONVERT(VARCHAR, @id) + CHAR(13) + CHAR(10);
    END

    IF (@nume = '')
    BEGIN
        SET @erori = @erori + 'Numele nu poate fi vid.' + CHAR(13) + CHAR(10);
    END

    IF (@functie = '')
    BEGIN
        SET @erori = @erori + 'Functia nu poate fi vida.' + CHAR(13) + CHAR(10);
    END

    IF (@salariu < 1500)
    BEGIN
        SET @erori = @erori + 'Salariul nu poate fi mai mic de 1500.' + CHAR(13) + CHAR(10);
    END

    RETURN @erori;
END

CREATE OR ALTER PROCEDURE CRUD_angajat(@id INT, @nume VARCHAR(50), @functie VARCHAR(50), @salariu INT)
AS
BEGIN
    DECLARE @erori VARCHAR(1000);
    SET @erori = dbo.valideaza_angajat(@id, @nume, @functie, @salariu);
    
    IF (@erori != '')
    BEGIN
        PRINT @erori;
        RETURN
    END

    -- CREATE
    INSERT INTO angajat(id, nume, functie, salariu) VALUES (@id, @nume, @functie, @salariu);
    PRINT 'Am inserat in angajat valorile: ' + CONVERT(VARCHAR, @id) + ' ' + @nume + ' ' + @functie + ' ' + CONVERT(VARCHAR, @salariu) + CHAR(13) + CHAR(10);

    -- READ
    SELECT * FROM angajat;

    -- UPDATE
    UPDATE angajat SET salariu = @salariu + 500 WHERE id = @id;
    PRINT 'Am modificat salariul angajatului cu id-ul: ' + CONVERT(VARCHAR, @id) + ' la ' + CONVERT(VARCHAR, @salariu + 500);
    SELECT * FROM angajat;

    -- DELETE
    DELETE FROM angajat WHERE id = @id;
    PRINT 'Am sters angajatul cu id-ul: ' + CONVERT(VARCHAR, @id);
    SELECT * FROM angajat;
END
GO

EXEC CRUD_angajat 5,'Ceuca Ioana', 'Casier', 2000;
EXEC CRUD_angajat 1, '', '', 0;



CREATE OR ALTER VIEW view_furnizor AS
SELECT f.nume 
FROM furnizor f
WHERE f.nume LIKE 'C%'

SELECT * FROM view_furnizor

CREATE OR ALTER VIEW view_angajat AS
SELECT a.nume AS angajat, a.salariu AS salariu
FROM angajat a
WHERE a.salariu < 2000

SELECT * FROM view_angajat


CREATE OR ALTER VIEW view_comanda_produs_comandaprodus AS
--numele produselor impreuna cu suma de bani obtinuta in urma comenzilor acelui produs
--tabele : Comanda, Produs, ComandProduse
SELECT p.nume AS produs, SUM(cp.cantitate * p.pret) AS total_vanzari
FROM produs p
JOIN comanda_produse cp ON p.id = cp.produs_id
JOIN comanda c ON cp.comanda_id = c.id
GROUP BY p.nume;

SELECT * FROM view_comanda_produs_comandaprodus

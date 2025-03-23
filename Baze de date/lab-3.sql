CREATE PROCEDURE proc_modifica_strada AS
BEGIN 
    ALTER TABLE adresa 
	ALTER COLUMN strada VARCHAR(100);
	PRINT 'S-a modificat coloana strada din tabelul adresa';
END;

CREATE PROCEDURE proc_undo_modifica_strada AS
BEGIN
    ALTER TABLE adresa
	ALTER COLUMN strada VARCHAR(20);
	PRINT 'S-a facut undo la modificarea coloanei strada din tabelul adresa';
END;

CREATE PROCEDURE proc_constrangere_cantitate AS
BEGIN
    ALTER TABLE comanda_produse  
	ADD CONSTRAINT cantitate_min DEFAULT 1 FOR cantitate;
	PRINT 'S-a adaugat constrangere pentru coloana cantitate din tabelul comanda_produse';
END;

CREATE PROCEDURE proc_undo_constrangere_cantitate AS
BEGIN
    ALTER TABLE comanda_produse  
	DROP CONSTRAINT Cantitate_Min;
	PRINT 'S-a facut undo la constrangerea pentru coloana cantitate din tabelul comanda_produse ';
END;

CREATE PROCEDURE proc_creeaza_comenzi_finalizate AS
BEGIN
    CREATE TABLE comenzi_finalizate(
		id INT PRIMARY KEY NOT NULL,
		finalizat VARCHAR(30)
	);
	PRINT 'S-a creat un tabel nou';
END;

CREATE PROCEDURE proc_undo_creeaza_comenzi_finalizate AS
BEGIN
   DROP TABLE comenzi_finalizate;
	PRINT 'S-a facut undo la tabelul nou creat';
END;

DROP PROCEDURE proc_adauga_ora_finalizare
CREATE PROCEDURE proc_adauga_ora_finalizare AS
BEGIN
    ALTER TABLE comenzi_finalizate
	ADD ora_finalizarii TIME;
	PRINT 'S-a adaugat un camp nou la tabelul comenzi_inalizate';
END;

DROP PROCEDURE proc_UndoAdaugaOraFinalizare
CREATE PROCEDURE proc_undo_adauga_ora_finalizare AS
BEGIN
    ALTER TABLE comenzi_finalizate
	DROP COLUMN ora_finalizarii;
	PRINT 'S-a facut undo la adaugarea campului nou la tabelul comenzi_finalizate';
END;

DROP PROCEDURE proc_adauga_cheie_straina
CREATE PROCEDURE proc_adauga_cheie_straina AS
BEGIN
    ALTER TABLE comenzi_finalizate
	ADD CONSTRAINT fk_constraint FOREIGN KEY(id) REFERENCES Comanda(id);
	PRINT 'S-a adaugat cheie straina';
END;

DROP PROCEDURE comenzi_proc_undo_adauga_cheie_straina
CREATE PROCEDURE comenzi_proc_undo_adauga_cheie_straina AS
BEGIN
   ALTER TABLE comenzi_finalizate
	DROP CONSTRAINT fk_constraint;
	PRINT 'S-a eliminat cheia straina';
END;

CREATE TABLE versiune_db (
    numar_versiune INT
);


CREATE TABLE proceduri_versiune (
    versiune INT PRIMARY KEY,
    procedura_do VARCHAR(50),
    procedura_undo VARCHAR(50)
);

INSERT INTO proceduri_versiune VALUES (1, 'proc_modifica_strada', 'proc_undo_modifica_strada');
INSERT INTO proceduri_versiune VALUES (2, 'proc_constrangere_cantitate', 'proc_undo_constrangere_cantitate');
INSERT INTO proceduri_versiune VALUES (3, 'proc_creeaza_comenzi_finalizate', 'proc_undo_creeaza_comenzi_finalizate');
INSERT INTO proceduri_versiune VALUES (4, 'proc_adauga_ora_finalizare', 'proc_undo_adauga_ora_finalizare');
INSERT INTO proceduri_versiune VALUES (5, 'proc_adauga_cheie_straina', 'comenzi_proc_undo_adauga_cheie_straina');

delete from proceduri_versiune

CREATE OR ALTER PROCEDURE main @versiune INT AS
BEGIN
    IF @versiune < 0 OR @versiune > 5
    BEGIN
        PRINT 'Versiunea specificată este invalidă!';
        RETURN;
    END;

    DECLARE @versiune_curenta INT;
    SET @versiune_curenta = (SELECT numar_versiune FROM versiune_db);

    IF @versiune = @versiune_curenta
    BEGIN
        PRINT 'Versiunea specificată este deja versiunea curentă.';
        RETURN;
    END;

    DECLARE @do_proc VARCHAR(50);
    DECLARE @undo_proc VARCHAR(50);

    DELETE FROM versiune_db;
    INSERT INTO versiune_db(numar_versiune) VALUES (@versiune);

    WHILE (@versiune_curenta < @versiune)
    BEGIN
        SET @versiune_curenta = @versiune_curenta + 1;
        SET @do_proc = (SELECT procedura_do FROM proceduri_versiune WHERE versiune = @versiune_curenta);
        PRINT 'Executăm ' + @do_proc + ':';
        EXEC @do_proc;
    END;

    WHILE (@versiune_curenta > @versiune)
    BEGIN
        SET @undo_proc = (SELECT procedura_undo FROM proceduri_versiune WHERE versiune = @versiune_curenta);
        PRINT 'Executăm ' + @undo_proc + ':';
        EXEC @undo_proc;
        SET @versiune_curenta = @versiune_curenta - 1;
    END;
END;


EXEC main 0;
EXEC main 1;
EXEC main 2;
EXEC main 3;
EXEC main 4;
EXEC main 5;
EXEC main 10;


EXEC proc_modifica_strada;
EXEC proc_undo_modifica_strada;

EXEC proc_constrangere_cantitate;
EXEC proc_undo_constrangere_cantitate;

EXEC proc_creeaza_comenzi_finalizate;
EXEC proc_undo_creeaza_comenzi_finalizate;

EXEC proc_adauga_ora_finalizare;
EXEC proc_undo_adauga_ora_finalizare;

EXEC proc_adauga_cheie_straina;
EXEC comenzi_proc_undo_adauga_cheie_straina;



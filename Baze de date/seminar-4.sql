use [ParcDistractii ]
GO

CREATE TABLE Sectiuni(
	sid INT PRIMARY KEY NOT NULL,
	nume VARCHAR(50),
	descriere VARCHAR(100)
);

CREATE TABLE Atractii(
	aid INT PRIMARY KEY NOT NULL,
	nume VARCHAR(50),
	descriere VARCHAR(50),
	varsta_min INT, 
	sectiune INT FOREIGN KEY REFERENCES Sectiuni(sid)
);


CREATE TABLE Categorii(
	cid INT PRIMARY KEY NOT NULL,
	nume VARCHAR(50)
);

CREATE TABLE Vizitatori(
	vid INT PRIMARY KEY NOT NULL,
	nume VARCHAR(50),
	email VARCHAR(50),
	categorie INT FOREIGN KEY REFERENCES Categorii(cid)
);

CREATE TABLE Note(
	vid INT FOREIGN KEY REFERENCES vizitatori(vid),
	aid INT FOREIGN KEY REFERENCES atractii(aid),
	nota INT CHECK ( nota >=1 AND nota <= 10), 
    CONSTRAINT pk_nota PRIMARY KEY (vid, aid)
);

INSERT INTO Sectiuni (sid, nume, descriere) VALUES
(1, 'Aventura', 'Atractii pline de adrenalina'),
(2, 'Relaxare', 'Zona de relaxare si plimbari usoare'),
(3, 'Copii', 'Atractii dedicate copiilor');

INSERT INTO Atractii (aid, nume, descriere, varsta_min, sectiune) VALUES
(1, 'Roller Coaster', 'Montagne russe cu viteza mare', 12, 1),
(2, 'Carusel', 'Plimbare clasica pe carusel', 3, 3),
(3, 'Casa Groazei', 'Experienta de groaza interactiva', 16, 1),
(4, 'Plimbare cu Barca', 'Relaxare pe apa', 0, 2);

INSERT INTO Categorii (cid, nume) VALUES
(1, 'Adulti'),
(2, 'Copii'),
(3, 'Seniori');

INSERT INTO Vizitatori (vid, nume, email, categorie) VALUES
(1, 'Ion Popescu', 'ion.popescu@gmail.com', 1),
(2, 'Maria Ionescu', 'maria.ionescu@gmail.com', 2),
(3, 'Andrei Georgescu', 'andrei.georgescu@gmail.com', 1),
(4, 'Ana Marinescu', 'ana.marinescu@gmail.com', 3);

INSERT INTO Note (vid, aid, nota) VALUES
(1, 1, 9),
(1, 3, 7),
(2, 2, 10),
(3, 1, 8),
(3, 4, 9),
(4, 4, 8);

GO
CREATE OR ALTER FUNCTION gasesteCodCategorie(@numeCategorie VARCHAR(50))
RETURNS INT AS BEGIN
RETURN (SELECT cid FROM Categorii WHERE nume = @numeCategorie)
END
GO
PRINT dbo.gasesteCodCategorie('Adulti');


GO
CREATE TRIGGER eliminareCategorie
ON Categorii
INSTEAD OF DELETE
AS
BEGIN
PRINT 'Nu pot sterge inregistrarile din tabelul Categorii'
END;
GO
DELETE FROM Categorii WHERE cid > 0

GO
CREATE VIEW CategoriiCopiiPensionari
AS
SELECT cid, nume FROM Categorii WHERE nume='Copii' or nume='Pensionari;'
GO
SELECT * FROM CategoriiCopiiPensionari


GO
CREATE VIEW viewNumeC AS
SELECT nume, descriere, sid
FROM Sectiuni
WHERE Nume LIKE 'C%';
GO
SELECT * FROM viewNumeC

GO
CREATE OR ALTER FUNCTION valSectiune(@litera VARCHAR(1))
RETURNS TABLE AS
RETURN (SELECT * FROM Sectiuni WHERE nume LIKE '%_' + @litera)
GO
SELECT * FROM valSectiune('a');

GO
CREATE VIEW viewVNA
AS
SELECT v.nume AS NumeV, n.nota, a.nume 
FROM Vizitatori V
INNER JOIN Note n ON n.vid = V.vid
INNER JOIN Atractii a ON a.aid = n.aid
GO

SELECT * FROM viewVNA




 
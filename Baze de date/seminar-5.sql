use Seminar5;


CREATE TABLE tipuri(
	id INT PRIMARY KEY,
	descriere VARCHAR(256)
);


CREATE TABLE trenuri(
	id INT PRIMARY KEY IDENTITY(1,1),
	nume VARCHAR(256),
	tid INT FOREIGN KEY REFERENCES tipuri(id)
);


CREATE TABLE statii(
	id INT PRIMARY KEY IDENTITY(1,1),
	nume VARCHAR(256)
);

CREATE TABLE rute(
	id INT PRIMARY KEY IDENTITY(1,1),
	nume VARCHAR(256),
	tid INT FOREIGN KEY REFERENCES trenuri(id)
);

CREATE TABLE statii_rute(
	sid INT FOREIGN KEY REFERENCES statii(id),
	rid INT FOREIGN KEY REFERENCES rute(id),
    CONSTRAINT pk_statii_rute PRIMARY KEY(sid, rid),
	sosire TIME,
	plecare TIME
);


-- Inserare date în tabelul tipuri
INSERT INTO tipuri (id, descriere) 
VALUES 
(1, 'Personal'), 
(2, 'Accelerat'), 
(3, 'InterRegio'), 
(4, 'Express');

-- Inserare date în tabelul trenuri
INSERT INTO trenuri (nume, tid) 
VALUES 
('Tren1', 1), 
('Tren2', 2), 
('Tren3', 3), 
('Tren4', 4);

-- Inserare date în tabelul statii
INSERT INTO statii (nume) 
VALUES 
('Gara București'), 
('Gara Brașov'), 
('Gara Constanța'), 
('Gara Cluj');

-- Inserare date în tabelul rute
INSERT INTO rute (nume, tid) 
VALUES 
('Ruta București - Brașov', 1), 
('Ruta Brașov - Constanța', 2), 
('Ruta Cluj - București', 3), 
('Ruta Constanța - Cluj', 4);

-- Inserare date în tabelul statii_rute
INSERT INTO statii_rute (sid, rid, sosire, plecare) 
VALUES 
(1, 1, '08:00:00', '08:10:00'), -- București pe ruta 1
(2, 1, '09:30:00', '09:40:00'), -- Brașov pe ruta 1
(2, 2, '10:00:00', '10:10:00'), -- Brașov pe ruta 2
(3, 2, '12:00:00', '12:10:00'), -- Constanța pe ruta 2
(4, 3, '14:00:00', '14:10:00'), -- Cluj pe ruta 3
(1, 3, '16:00:00', '16:10:00'), -- București pe ruta 3
(3, 4, '18:00:00', '18:10:00'), -- Constanța pe ruta 4
(4, 4, '20:00:00', '20:10:00'); -- Cluj pe ruta 4


CREATE PROCEDURE AddOrUpdateStationToRoute
    @id_ruta INT,        
    @id_statie INT,       
    @sosire TIME,         
    @plecare TIME        
AS
BEGIN
    IF EXISTS (
        SELECT 1 
        FROM Statii_Rute 
        WHERE rid = @id_ruta AND sid = @id_statie
    )
    BEGIN
        UPDATE statii_rute
        SET sosire = @sosire,
            plecare = @plecare
        WHERE rid = @id_ruta AND sid = @id_statie;
    END
    ELSE
    BEGIN
        INSERT INTO statii_rute (sid, rid, sosire, plecare)
        VALUES (@id_statie, @id_ruta, @sosire, @plecare);
    END
END;
 
EXEC AddOrUpdateStationToRoute @id_ruta = 2, @id_statie = 3, @sosire = '08:00:00', @plecare = '08:10:00';
 
 
EXEC AddOrUpdateStationToRoute @id_ruta = 1, @id_statie = 1, @sosire = '15:30:00', @plecare = '15:40:00';
 

SELECT * FROM Statii_Rute;

CREATE VIEW view1 AS
	SELECT rute.nume as ruta
	from rute
	inner join statii_rute ON rute.id = statii_rute.rid
	GROUP BY rute.id, rute.nume
	HAVING COUNT(*)  = (SELECT COUNT(*) FROM statii)


SELECT * FROM view1
--trb sa fie o ruta legata de tpate statiile





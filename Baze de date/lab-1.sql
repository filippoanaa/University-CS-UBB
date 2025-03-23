CREATE DATABASE cafenea;
USE cafenea;
GO

CREATE TABLE angajat(
	id INT PRIMARY KEY,
	nume VARCHAR(50),
	functie VARCHAR(50),
	salariu INT
);

CREATE TABLE categorie(
	id INT PRIMARY KEY,
	nume VARCHAR(50) CHECK (nume IN ('bauturi', 'mancare'))
);

CREATE TABLE furnizor(
	id INT PRIMARY KEY,
	nume VARCHAR(50)
);

CREATE TABLE telefon(
	furnizor_id INT,
	mobil INT NOT NULL,
	fix INT NULL,
	CONSTRAINT pk_telefon PRIMARY KEY(furnizor_id),
	FOREIGN KEY (furnizor_id) REFERENCES furnizor(id) ON DELETE CASCADE
);

CREATE TABLE adresa(
	furnizor_id INT,
	judet VARCHAR(20),
	oras VARCHAR(20),
	strada VARCHAR(20),
	numar INT,
	CONSTRAINT pk_adresa PRIMARY KEY(furnizor_id),
	FOREIGN KEY (furnizor_id) REFERENCES furnizor(id) ON DELETE CASCADE
);

CREATE TABLE produs(
	id INT PRIMARY KEY,
	nume VARCHAR(50),
	descriere VARCHAR(100),
	pret INT,
	categorie_id INT,
	furnizor_id INT,
	FOREIGN KEY (categorie_id) REFERENCES categorie(id) ON DELETE CASCADE,
	FOREIGN KEY (furnizor_id) REFERENCES furnizor(id) ON DELETE CASCADE
);

CREATE TABLE comanda(
	id INT PRIMARY KEY,
	pret INT
);

CREATE TABLE masa(
	id INT PRIMARY KEY,
	nr_locuri INT,
	angajat_id INT,
	comanda_id INT,
	FOREIGN KEY (angajat_id) REFERENCES angajat(id) ON DELETE CASCADE,
	FOREIGN KEY (comanda_id) REFERENCES comanda(id) ON DELETE CASCADE
);

CREATE TABLE client(
	id INT PRIMARY KEY,
	nume VARCHAR(50),
	specificatii VARCHAR(100),
	masa_id INT,
	FOREIGN KEY (masa_id) REFERENCES masa(id) ON DELETE CASCADE
);

CREATE TABLE comanda_produse(
	comanda_id INT,
	produs_id INT,
	cantitate INT,
	CONSTRAINT pk_comanda_produse PRIMARY KEY(comanda_id, produs_id),
	FOREIGN KEY (comanda_id) REFERENCES comanda(id) ON DELETE CASCADE,
	FOREIGN KEY (produs_id) REFERENCES produs(id) ON DELETE CASCADE
);

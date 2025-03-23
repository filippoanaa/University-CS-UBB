use cafenea
go

--Furnizor
INSERT INTO furnizor(id, nume) VALUES (1, 'Panemar'), (2,'Gigi'), (3, 'Delissima'),
(4,'Lidl'), (5, 'CocaCola Company'), (6, 'Nesscafe'), (7, 'Tchibo'), (8,'Jacobs');


--Adresa
INSERT INTO adresa(furnizor_id, judet, oras, strada,numar) VALUES 
(1, 'Cluj', 'Cluj-Napoca', 'Memo', 8),  -- Panemar
(2, 'Cluj',  'Cluj-Napoca', 'Sucevei', 34),     -- Gigi
(3, 'Cluj',  'Cluj-Napoca', 'Fantanele', 10), -- Delissima
(4, 'Bihor', 'Oradea', 'Dacia', 12),          -- Lidl
(5, 'Bihor', 'Beius', 'Brates', 2),       -- CocaCola Company
(6, 'Brasov', 'Brasov', 'Plopilor', 5),      -- Nesscafe
(7, 'Timis', 'Timisoara', 'Lalelelor', 18),  -- Tchibo
(8, 'Constanta', 'Constanta', 'Marului', 4); -- Jacobs


--Telefon
INSERT INTO Telefon(furnizor_id, Mobil, Fix) VALUES 
(1, '0723456789', '0264123456'), -- Panemar
(2, '0729876543', '0219876543'), -- Gigi
(3, '0745123456', NULL), -- Delissima
(4, '0730123456', '0259123456'), -- Lidl
(5, '0765432109', '0216543210'), -- CocaCola Company
(6, '0756543210', NULL), -- Nesscafe
(7, '0723654789', '0256236547'), -- Tchibo
(8, '0745236987', NULL); -- Jacobs

--categorie
INSERT INTO Categorie(id, nume)
VALUES 
(1, 'Bauturi'),
(2, 'Mancare');

INSERT INTO produs(id, nume, descriere, pret, categorie_id, furnizor_id)
VALUES 
(1, 'Cafea Espresso', 'Cafea preparata din boabe de calitate', 10, 1, 7),
(2, 'Croissant', 'Croissant frantuzesc cu unt', 5, 2, 1),
(3, 'Foitaj cu mar ', 'Delicios, cu mere bio', 8, 2, 5),
(4, 'Apa Minerala', 'Apa minerala plata', 4, 1, 8),
(5, 'Sandwich', 'Sandwich cu sunca si branza', 12, 2, 2),
(6, 'Ceai Verde', 'Ceai verde organic', 6, 1, 6),
(7, 'Ciocolata Calda', 'Ciocolata calda cremoasa', 10, 1, 2),
(8, 'Latte Machiatto', 'Cafea preparata cu 1 shot de esspreso si 3 de lapte', 15, 2, 1),
(9, 'Panetonne cu fistic', 'Gustul perfect', 15, 1, 4); 


--Comanda
INSERT INTO comanda(id, pret)
VALUES 
(1, 30),
(2, 25),
(3, 40),
(4, 50),
(5, 32),
(6, 27),
(7, 50),
(8, 15);


--angajat
INSERT INTO angajat(id, nume, functie, salariu) 
VALUES 
(1, 'Ion Popescu', 'Manager', 3000),
(2, 'Andrei Marinescu', 'Chelner', 1800),
(3, 'Pop Maria', 'Chelner', 2200),
(4, 'Mihai Dobre', 'Chelner', 1800);


--Masa 
INSERT INTO masa(id, nr_locuri, angajat_id, comanda_id)
VALUES 
(1, 4, 1, 1),
(2, 2, 2, 2),
(3, 6, 3, 3),
(4, 4, 3, 4),
(5, 4, 2, 2),
(6, 2, 2, 3),
(7, 6, 2, 4),
(8, 4, 3, 2);

INSERT INTO client(id, nume, specificatii, masa_id)
VALUES 
(1, 'Radu Marinescu', 'Alergic la lactate', 1),
(2, 'Ana Stanescu', 'Nu consuma zahar', 2),
(3, 'Mihai Petrescu', 'Vegetarian', 3),
(4, 'Ioana Iliescu', 'Fara gluten', 6),
(5, 'George Matei', 'Fara sare', 5),
(6, 'Elena Popescu', 'Fara gluten', 6),
(7, 'Andreea Pavel', 'Fara gluten', 3),
(8, 'Cristian Tudor', 'Fara sare', 3);


--ComandaProduse
INSERT INTO comanda_produse(comanda_id, produs_id, cantitate)
VALUES 
(1, 1, 2),
(2, 2, 3),
(3, 3, 1),
(4, 4, 2),
(5, 5, 1),
(6, 6, 2),
(7, 7, 1),
(8, 1, 1);

-- selectare din toate tabelele

SELECT * FROM angajat;
SELECT * FROM categorie;
SELECT * FROM furnizor;
SELECT * FROM telefon;
SELECT * FROM adresa;
SELECT * FROM produs;
SELECT * FROM comanda;
SELECT * FROM masa;
SELECT * FROM client;
SELECT * FROM comanda_produse;

--Produse care au un pret mai mic decat 10, impreuna cu furnizorii, categoria si pretul lor
--tabele: produs, Furnizor, Categorie
--cnt WHERE:1
SELECT p.nume AS produs, f.nume AS furnizor, c.nume AS categorie, p.pret as pret
FROM produs p
JOIN furnizor f on p.furnizor_id = f.id
JOIN categorie c ON p.categorie_id = c.id
WHERE p.pret < 10
ORDER BY p.pret;

--Numarul de clienti care au specificatia "Fara gluten", rezultatul fiind grupat dupa masa si anjagatul responsabil 
--tabele: Masa, angajat, Client
--cnt WHERE: 2
--cnt GROUP BY: 1
SELECT m.id AS numar_masa, COUNT(cl.id) AS numar_clienti, a.nume AS angajat
FROM Masa m
JOIN angajat a ON m.angajat_id = a.id
JOIN client cl ON m.id = cl.masa_id
WHERE cl.specificatii LIKE '%Fara gluten%'
GROUP BY m.id, a.nume;

--Furnizaorii din Cluj-Napoca care furnizeaza mai mult de 1 produs, impreuna cu nr de produse oferite
--tabele: Furnizor, Adresa, Produs
--cnt WHERE:3
--cnt GROUP BY: 2
--CNT HAVING: 1	
SELECT f.nume AS nume, COUNT(p.id) AS numar_produse
FROM furnizor f
JOIN produs p ON f.id = p.furnizor_id
JOIN adresa a ON f.id = a.furnizor_id
WHERE a.oras = 'Cluj-Napoca'
GROUP BY f.nume
HAVING COUNT(p.id) >= 1;

--angajatii chelneri care au strans comenzi de la mese, insumand total mai mult decat 50 de lei 
--tabele: angajat, comanda, masa
--cnt WHERE : 4
--cnt GROUP BY: 3 OKK
--cnt HAVING : 2 OKK
SELECT  a.nume AS angajat, SUM(c.pret) AS total_pret
FROM masa m
JOIN comanda c ON m.comanda_id = c.id
JOIN angajat a ON m.angajat_id = a.id
WHERE a.functie = 'Chelner'
GROUP BY a.nume
HAVING SUM(c.pret) >= 50;


--Judetele care au cel putin un furnizorcare furnizeaza produse avand categoria: mancare
--tabele: Adresa, Furnizor, Produs, Categorie
--cnt WHERE : 5 OKK
--cnt DISTINCT :1
SELECT DISTINCT a.judet AS judet
FROM adresa a
JOIN furnizor f ON a.furnizor_id = f.id
JOIN produs p ON f.id = p.furnizor_id
JOIN categorie c ON p.categorie_id = c.id
WHERE c.nume = 'Mancare';

--Comenzile care contin 'Cafea espresso', impreuna cu cantitatea 
--tabele : Comanda, Produs, ComandProduse
SELECT c.id AS numar_comanda, p.nume AS produs, cp.cantitate AS cantitate
FROM comanda c
JOIN comanda_produse cp ON c.id = cp.comanda_id
JOIN produs p ON cp.produs_id = p.id
WHERE p.nume = 'Cafea Espresso';

--numele produselor impreuna cu suma de bani obtinuta in urma comenzilor acelui produs
--tabele : Comanda, Produs, ComandProduse
SELECT p.nume AS produs, SUM(cp.cantitate * p.pret) AS total_vanzari
FROM produs p
JOIN comanda_produse cp ON p.id = cp.produs_id
JOIN comanda c ON cp.comanda_id = c.id
GROUP BY p.nume;

--judetele in care exista cel putin 1 furnizorcare poate fi contactat prin fix
--tabele: adresa, furnizor, telefon
--cnt DISTINCT: 2 OKK
SELECT DISTINCT a.judet
FROM adresa a
JOIN furnizor f ON a.furnizor_id = f.id
JOIN telefon t ON f.id = t.furnizor_id
WHERE t.fix IS NOT NULL;

--angajatii care gestioneaza mese cu cel putin doi clienti, impreuna cu numarul de clienti pentru fiecare masa
--tabele: angajat,masa, client
SELECT a.nume AS angajat, m.id AS numar_masa, COUNT(cl.id) AS numar_clienti
FROM masa m
JOIN angajat a ON m.angajat_id = a.id
JOIN client cl ON m.id = cl.masa_id
GROUP BY a.nume, m.id
HAVING COUNT(cl.id) >= 2;


--clientii care au la specificatia comezii: fara sare, impreuna cu numarul mesei si angajatul responsabil
--tabele: masa, client, angajat
SELECT cl.nume AS client, m.id AS numar_masa, a.nume AS angajat
FROM masa m
JOIN angajat a ON m.angajat_id = a.id
JOIN client cl ON m.id = cl.masa_id
WHERE cl.specificatii LIKE '%Fara sare%'
ORDER BY m.id, cl.nume;


-- sterge datele din toate tabelele 

DELETE FROM comanda_produse;
DELETE FROM client;
DELETE FROM masa;
DELETE FROM comanda;
DELETE FROM produs;
DELETE FROM adresa;
DELETE FROM telefon;
DELETE FROM furnizor;
DELETE FROM categorie;
DELETE FROM angajat;




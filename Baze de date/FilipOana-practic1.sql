create database practic

create table carti(
	id int primary key identity,
	titlu varchar(100),
	editira varchar(100),
	an int, 
	isbn int
)

create table povesti(
	id int primary key identity,
	denumire varchar(100),
	autor varchar(100),
	an int,
	nr_pag int, 
	id_carte int foreign key references carti(id)
)

create table  orase(
	id int primary key identity,
	nume varchar(100),
	judet varchar(100),
	tara varchar(100)
)

create table biblioteci(
	id int primary key identity,
	denumire varchar(100),
	an_infiintare int,
	id_oras int foreign key references orase(id)
)

create table carti_biblioteca(
	id_carte int foreign key references carti(id),
	id_biblioteca int foreign key references biblioteci(id),
	nr_exemplare int,
	data_inregistrare date,
    constraint pk primary key (id_carte, id_biblioteca)

)

insert into carti (titlu, editira, an, isbn)
values 
('Cartea 1', 'Editura A', 2020, 6789),
('Cartea 2', 'Editura B', 2019, 2340),
('Cartea 3', 'Editura C', 2021, 3459)


insert into carti (titlu, editira, an, isbn)
values 
('Cartea 4', 'Editura D', 2022, 2345),
('Cartea 5', 'Editura E', 2013, 2654),
('Cartea 6', 'Editura F', 2024, 5321)
select * from carti
delete from carti

insert into povesti (denumire, autor, an, nr_pag, id_carte)
values 
('Povestea 1', 'Autor 1', 2020, 150, 7),
('Povestea 2', 'Autor 2', 2019, 200, 8),
('Povestea 3', 'Autor 3', 2021, 120, 9)
select * from povesti
delete from povesti

insert into orase (nume, judet, tara)
values 
('Oras 1', 'Judet 1', 'Romania'),
('Oras 2', 'Judet 2', 'Romania'),
('Oras 3', 'Judet 3', 'Romania')
select * from orase
delete from orase

insert into biblioteci (denumire, an_infiintare, id_oras)
values 
('Biblioteca 1', 2000, 4),
('Biblioteca 2', 2005, 5),
('Biblioteca 3', 2010, 6)
select * from biblioteci 
delete from biblioteci

insert into carti_biblioteca (id_carte, id_biblioteca, nr_exemplare, data_inregistrare)
values 
(7, 5, 5, '2024-01-01'),
(7, 6, 3, '2024-01-02'),
(7, 7, 7, '2024-01-03'),
(8, 5, 2, '2024-01-04'),
(8, 6, 5, '2024-01-05'),
(8, 7, 5, '2024-01-06'),
(9, 7, 5, '2024-01-07')
select * from carti_biblioteca
delete from carti_biblioteca

go
create or alter procedure proc1(@id_biblioteca int, @id_carte int, @nr_exemplare int, @data date)
as 
begin 
	 if not exists (select 1 from biblioteci where id = @id_biblioteca)
    begin
        print 'biblioteca nu exista'
        return
    end

    if not exists (select 1 from carti where id = @id_carte)
    begin
        print 'cartea nu exista'
        return
    end

    if (exists (select 1 from carti_biblioteca where id_carte = @id_carte and id_biblioteca = @id_biblioteca))
    begin
        update carti_biblioteca
        set nr_exemplare = @nr_exemplare, data_inregistrare = @data
        where id_carte = @id_carte and id_biblioteca = @id_biblioteca
		print 'update facut cu succes' 
    end
    else
    begin
        insert into carti_biblioteca (id_carte, id_biblioteca, nr_exemplare, data_inregistrare)
        values (@id_carte, @id_biblioteca, @nr_exemplare, @data)
		print 'inserare realizata cu succes'
    end
end
go


exec proc1 5,7,4, '2024-01-01'
exec proc1 5,10,4, '2024-01-01'
select * from carti_biblioteca
select * from biblioteci
select * from carti

create or alter view view3
as
	select titlu
	from carti
	where (select count(*) from carti_biblioteca cb where cb.id_carte = carti.id) = (select count(*) from biblioteci)
select * from view3



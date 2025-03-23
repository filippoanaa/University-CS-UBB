%predicat care inverseaza o lista de cifre
%inverseazaAux(l1..ln , c1..cn) = c , n = 0
%                              l1 U inverseazaAux(l2..ln , c1..cn),
%                                  altfel, unde U - reuniune
%model de flux : inverseazaAux(i, i , o)
%inverseazaAux(Lista : lista, Colector: lista, Rezultat: lista)
%Lista - lista de cifre de inversat
%Colector - lista in care se inverseaza lista de cifre
%Rezutat : lista inversata
inverseazaAux([], Colector, Colector).
inverseazaAux([H|T],Colector, Rezultat):-inverseazaAux(T,[H|Colector], Rezultat).

%inverseaza(l1..ln) = inverseazaAux(l1..ln, [])
%model de flux : (i,o)
%inverseaza(Lista : lista ,  Rezultat : lista)
%Lista - lista de inversat
%Rezultat -  lista inversata
inverseaza(Lista, Rezultat):-inverseazaAux(Lista,[],Rezultat).

%predicat care transforma o lista de cifre in numar
%listaInNumarAux(l1..ln, poz) = 0 , n = 0
%                                  poz*l1 + listaInNumarAux(l2..ln,
%                                  poz*10), altfel
% model de flux : listaInNumarAux(i,i,o)
% listaInNumarAux(Lista : lista, Poz : intreg, Numar : intreg)
% Lista - Lista de cifre de transformat
% Poz - pozitia de pe care se incepe transformarea
% Numar - numarul rezultat
listaInNumarAux([],_,0):-!.
listaInNumarAux([Cifra|T], Poz, Numar):-
    ValCurenta is Poz*Cifra,
    PozUrm is Poz * 10,
    listaInNumarAux(T, PozUrm, Numar1),
    Numar is ValCurenta + Numar1.

%inverseazaInNumar(l1..ln) =  listaInNumarAux(inverseaza(l1..ln))
%model de flux : inverseazaInNumar(i,o)
%listaInNumar(Lista : lista , Numar : intreg)
%Lista - lista de cifre de transformat
%Numar - numarul rezultat din transformare
listaInNumar(Lista, Numar):-inverseaza(Lista, ListaInversata), listaInNumarAux(ListaInversata,1,Numar).

%predicat care transforma un numar in liste
%numarInListaAux(numar,l1..ln) = l1..ln , numar = 0
%                               numarInListaAux(numar/10, numar%10 U
%                               l1..ln) ,  altfel
% model de flux :  numarInListaAux(i,i,o)
% numarInListaAux(Numar : intreg, Colector : lista, Rezultat : lista)
% Numar - numarul de transformat in lista
% Colector - lista in care se realizeaza transformarea
% Rezultat  - lista rezultat din transformare
numarInListaAux(0,Colector,Colector):-!.
numarInListaAux(Numar, Colector, Rezultat):-
    UltimaCifra is Numar mod 10,
    Numar1 is Numar//10,
    numarInListaAux(Numar1,[UltimaCifra|Colector],Rezultat).

%numarInLista(Numar) = numarInListaAux(Numar, [])
%model de flux : numarInLista(i, o)
%numarInLista(Numar: intreg, Rezultat : lista)
%Numar - numarul de trabformat in lista
%Rezultat - lista rezultata din transformare
numarInLista(Numar, Rezultat):-numarInListaAux(Numar,[], Rezultat).

%predicat care afla suma a doua numere reprezentate sub forma de liste
% sumaListe(l1..ln, p1..pm) = numarInLista(listaInNumar(l1..ln) +
% listaInNumar(p1..pm))
% model de flux : sumaListe(i,i,o)
% sumaListe(L1: lista, L2: lista, Rezultat:intreg)
sumaListe(L1, L2, Rezultat) :-
    listaInNumar(L1, Num1),
    listaInNumar(L2, Num2),
    Suma is Num1 + Num2,
    numarInLista(Suma, Rezultat).

% predicat care daca un element e lista il converteste in numar, iar
% daca e numar nu ii aplica nicio transformare
% tratareElement(Element) :- listaInNumar(Element), Element e lista
%                            Element, daca e numar
%model de flux : tratareElement(i, o)
%tratareElement(Element : lista/numar, Numar: intreg)
%Element - elementul de tranformat
%Numar - elementul transformat
tratareElement(Element, Numar) :- is_list(Element),
    listaInNumar(Element, Numar).
tratareElement(Element, Numar):-number(Element),
    Numar = Element.


sumaTotala([],[0]).
sumaTotala([H|T], Rezultat) :-
    is_list(H),!,
    sumaTotala(T, Rezultat1),
    sumaListe(H, Rezultat1, Rezultat).

sumaTotala([_|T], Rezultat):-
    sumaTotala(T, Rezultat).












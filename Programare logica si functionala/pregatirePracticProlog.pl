%diferenta a doua multimi
%contine(l1..ln, e) = false, daca n = 0
%                     true, l1 == e
%                     contine(l2..ln, e), altfel
%model de flux : (i,i)
contine([H|_], H):-!.
contine([_|T], E):-contine(T,E).

%diferenta(l1..ln,m1..mp) = [], daca n = 0
%                           diferenta(l2..ln,m1..mp), daca
%                           contine(m1..mp, l1) =  true
%                           l1 + diferenta(l2..ln,m1..mp), altfel
diferenta([], _, []).
diferenta([H|T], L2, Rez):-contine(L2,H),!,diferenta(T, L2, Rez).
diferenta([H|T],L2, [H|Rez]):-diferenta(T, L2, Rez).

%adaug 1 dupa fiecare elem par din lista
e_par(N):-N mod 2 =:= 0.

adauga_unu([],[]).
adauga_unu([H|T],[H,1|Rez]):-e_par(H),!,adauga_unu(T,Rez).
adauga_unu([_|T],Rez):-adauga_unu(T,Rez).

%cmmc al unei liste
cmmdc(A,A,A):-!.
cmmdc(A,B,Rez):-A > B,!,A1 is A-B, cmmdc(A1,B, Rez).
cmmdc(A,B,Rez):- A < B, !, B1 is B-A, cmmdc(A,B1,Rez).

cmmmc(A,B,Rez):- cmmdc(A,B,D), Rez is (A*B)//D.

cmmmc_lista([H],H).
cmmmc_lista([H1,H2|T],Rez):-cmmmc(H1,H2,M), cmmmc_lista([M|T],Rez).



%adauga dupa 1-ul, al 2-lea, al 4-lea, al 8-lea un el v
adauga_dupa([],_,_,_,[]).
adauga_dupa([H|T],E,Poz,PozPutere2, [H,E|Rez]):-
    Poz =:= PozPutere2, !,
    PozPutere2Next is PozPutere2 * 2,
    PozNext is Poz + 1,
    adauga_dupa(T,E,PozNext, PozPutere2Next, Rez).

adauga_dupa([H|T],E,Poz,PozPutere2,[H|Rez]):-
    PozNext is Poz + 1,
    adauga_dupa(T,E,PozNext,PozPutere2,Rez).


%    Sa se scrie un predicat care transforma o lisa %intr-o multime, in
%    ordinea primei aparitii

transforma([], []).
transforma([H|T], [H|M]) :-
    \+contine(M, H), !,
    transforma(T, M).
transforma([_|T], M) :-
    transforma(T, M).



% Sa se scrie un predicat care substituie intr-o lista un element printr-o alta lista.

substituie_lista([],_,_,[]).
substituie_lista([H|T], E, L,[L|Rez]):- H=:=E,!,
    substituie_lista(T,E,L,Rez).
substituie_lista([H|T],E,L,[H|Rez]):- substituie_lista(T,E,L,Rez).



%sa se elimine elementul de pe poz a n a intr o lista
%elimina_n_lea_elem(l1..ln,poz, cnt)=[], n = 0
%                                 l2..ln , cnt = poz
%                                l1 + elimina(l2..ln, poz, cnt + 1),
% model de flux : elimina_n_lea_elem(i,i,i,o)
% elimina_n_lea_elem(L: lista, N : intreg, Cnt: intreg, Rez: lista)
elimina_n_lea_elem([],_,_,[]).
elimina_n_lea_elem([_|T], N, N,T):-!.
elimina_n_lea_elem([H|T],N, Cnt, [H|Rez]):-CntNext is Cnt + 1, elimina_n_lea_elem(T,N,CntNext,Rez).


%elimina_atom(l1..ln,a)= [], n = 0
%                         l1 + elimina_atom(l2..ln,a), l1 !=a
%                         elimina_atom(ln..ln), l1 = a
%model de flux: elimina_atom(i,i,o)
%elimina_atom(L: lista, A: atom, Rez: lista)
elimina_atom([],_,[]).
elimina_atom([H|T],H,Rez):-elimina_atom(T,H,Rez),!.
elimina_atom([H|T],A,[H|Rez]):-elimina_atom(T,A,Rez).

%returneaza lista formata din liste de forma [val, frecv]
numara_si_elimina([],_,0,[]).
numara_si_elimina([E|T],E,Cnt, Rez):-numara_si_elimina(T,E,Cnt1,Rez),!, Cnt is Cnt1 + 1.
numara_si_elimina([H|T], E, Cnt, [H|Rez]):-numara_si_elimina(T,E,Cnt, Rez).


perechi_frecventa([],[]).
perechi_frecventa([H|T], [[H,F]|Rez]):-numara_si_elimina([H|T],H,F,R1), perechi_frecventa(R1,Rez).

%elimina toate elementele care se repeta
calc_frecventa([],_,0).
calc_frecventa([E|T],E,Cnt):-!,calc_frecventa(T,E,Cnt1),Cnt is Cnt1+1.
calc_frecventa([_|T],E,Cnt):-calc_frecventa(T,E,Cnt).

elimina_duplicate([],[]).
elimina_duplicate([H|T],R):- calc_frecventa([H|T],H,F),
    F > 1,!, elimina_atom(T,H,R1) , elimina_duplicate(R1,R).
elimina_duplicate([H|T],[H|R]):- elimina_duplicate(T,R).


%elimina prima ap a lui min in lista
min_lista([],0).
min_lista([E],E).
min_lista([H|T],H):-min_lista(T,Min),H < Min.
min_lista([_|T],Min):-min_lista(T,Min).

elimina_prima_ap([],_,[]).
elimina_prima_ap([E|T],E,T):-!.
elimina_prima_ap([H|T],E,[H|R]):-elimina_prima_ap(T,E,R).

elim_prim_min(L,R):-min_lista(L,M),elimina_prima_ap(L,M,R).

inverseaza([],C,C).
inverseaza([H|T],C,Rez):-inverseaza(T,[H|C],Rez).


%cea mai lunga secventa de nr pare

ceaMaiLungaSecv(L,Rez):-
    ceaMaiLungaSecvPare(L,[],[],R),
    inverseaza(R,[],Rez).

ceaMaiLungaSecvPare([],Curr,Max,Max):-
    length(Curr, LCurr),
    length(Max,LMax),
    LCurr =< LMax, !.
ceaMaiLungaSecvPare([],Curr,_,Curr).

ceaMaiLungaSecvPare([H|T], Curr, Max, Rez):-
    H mod 2 =:= 0,
    !,
    ceaMaiLungaSecvPare(T,[H|Curr],Max,Rez).
ceaMaiLungaSecvPare([_|T],Curr,Max,Rez):-
    length(Curr, LCurr),
    length(Max,LMax),
    LCurr > LMax, !,
    ceaMaiLungaSecvPare(T,[],Curr,Rez).
ceaMaiLungaSecvPare([_|T], _,Max,Rez):-
    ceaMaiLungaSecvPare(T,[],Max,Rez).


%sa se sorteze o lista cu pastrarea dublurilor
sorteaza([],[]).
sorteaza([H|T],R):-sorteaza(T,SortedTail),
    insereaza(SortedTail, H, R).

insereaza([],X,[X]).
insereaza([H|T],X,[X,H|T]):- X =< H,!.
insereaza([H|T],X,[H|R]):-insereaza(T,X,R).


%sa se sorteze o lista cu eliminarea dublurilor

sorteazaFaraDubluri([],[]).
sorteazaFaraDubluri([H|T],R):-
    sorteazaFaraDubluri(T, SortedTail),
    insereazaFaraDubluri(SortedTail,H,R).

insereazaFaraDubluri([],X,[X]).
insereazaFaraDubluri([H|T],X,[X,H|T]):-
    X < H, !.
insereazaFaraDubluri([H|T],X,[H|R]):-
    X > H, !,
    insereazaFaraDubluri(T,X,R).
insereazaFaraDubluri([X|T],X,[X|T]).

%interclasare 2 liste sortate fara pastrarea dublurilor


% Predicatul principal pentru interclasare fără dubluri
interclaseaza([], [], []).
interclaseaza([H|T], [], [H|T]).
interclaseaza([], [H|T], [H|T]).
interclaseaza([H1|T1], [H2|T2], [H1|R]) :-
    H1 < H2,
    interclaseaza(T1, [H2|T2], R).
interclaseaza([H1|T1], [H2|T2], [H2|R]) :-
    H1 > H2,
    interclaseaza([H1|T1], T2, R).
interclaseaza([H1|T1], [H2|T2], [H1|R]) :-
    H1 =:= H2,
    interclaseaza(T1, T2, R).

elimina_dubluri([], []).
elimina_dubluri([H], [H]).
elimina_dubluri([H, H|T], R) :-
    elimina_dubluri([H|T], R).
elimina_dubluri([H1, H2|T], [H1|R]) :-
    H1 \= H2,
    elimina_dubluri([H2|T], R).

interclaseaza_fara_dubluri(L1, L2, R) :-
    interclaseaza(L1, L2, RInterclasat),
    elimina_dubluri(RInterclasat, R).

%pozitiile elementului maxim intr o lista
max_lista([],0).
max_lista([X],X).
max_lista([H|T],H):-max_lista(T,MaxTail),
    MaxTail =< H.
max_lista([H|T],MaxTail):-max_lista(T,MaxTail),
    MaxTail > H.

poz_max(_,[],_,[]):-!.
poz_max(Max,[Max|T],Cnt,[Cnt|Poz]):-!,
    CntNext is Cnt + 1,
    poz_max(Max,T,CntNext,Poz).
poz_max(Max, [_|T],Cnt, Poz):-
    CntNext is Cnt + 1,
    poz_max(Max,T,CntNext,Poz).

pozitii_max(L,R):-max_lista(L,Max), poz_max(Max, L,1,R).



%numere prime dintr o lista

%div(X,Y)= true, daca x%2 = 0
%          false, altfel
% model de flux : (i,i)
div(X,Y):-X mod Y =:= 0.

%prim(x,y) = true, daca y * y > x
%            prim(x,y+1), daca div(x,y) = false
%model de flux : (i,i)
prim(X,Y):- Y*Y > X.
prim(X,Y):-
    \+ div(X,Y),
    Y1 is Y+1,
    prim(X,Y1).

%este_prim(X) = true, daca n =2
%                prim(x,3), daca x > 1 si div(x,2) = false
%               false, altfel
este_prim(2).
este_prim(X):-
    X > 1,
    \+div(X,2),
    prim(X,3).

%lista_prime(l1..ln)= [], daca n = 0
%                     l1 + lista_prime(l2..ln), daca este_prim(l1)
%                     lista_prime(l2..ln), altfel
lista_prime([],[]).
lista_prime([H|T],[H|R]):-
    este_prim(H),!,
    lista_prime(T,R).
lista_prime([_|T],R):-lista_prime(T,R).





/*
    a) Sa se adauge dupa fiecare element dintr-o lista
divizorii elementului.
*/

concat([], L2, L2).
concat([H | T], L2, [H | R]) :-
        concat(T, L2, R).

divizori(E, _, []) :- E < 2, !.
divizori(E, E, []) :- !.
divizori(E, D, [D | R]) :-
        E mod D =:= 0, !,
        D1 is D + 1,
        divizori(E, D1, R).
divizori(E, D, R) :-
        D1 is D + 1,
        divizori(E, D1, R).

adaugaDiv([], []).
adaugaDiv([H | T], [H | R]) :-
        divizori(H, 2, Divs),
        adaugaDiv(T, R1),
        concat(Divs, R1, R).










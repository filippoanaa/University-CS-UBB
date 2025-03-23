%predicat care verifica daca un element exista in multime
%contineElement(L1..Ln, Element) = true, daca L1 = Element
%                                 false, daca n = 0
%                                 contineElement(L2..Ln), altfel
% model de flux : contineElement(i, i)
% L1..Ln : multimea in care se cauta elementul
% Element : intreg, elementul cautat in multime
contineElement([H|_], Element):- Element = H, !.
contineElement([H|T], Element):-contineElement(T,Element).


% predicat care verifica daca elementele din prima multime se afla in a
% doua multime
% toateElementeleExistaIn(L1..Ln, M1..Mp) = true, daca n = 0
%                                           toateElementeleExistaIn(L2..M
%                                          Ln, M1..Mp), daca
%                                          contineElement(M1..Mp, L1) si
%                                          toateElementeleExistaIn(L2..Ln
%                                          ,M1..Mp)
% Model de flux : toateElementeleExistaIn(i,i)
% L1..Ln- multimea a carei elemente se verifica daca exista in a doua
% multime
% M1..mp - multimea a carei elemente se compara cu elementele primei
% multimi
toateElementeleExistaIn([],_).
toateElementeleExistaIn([H|T], L2):- contineElement(L2, H),toateElementeleExistaIn(T, L2).

% Predicat care verifica daca o lista este multime, adica nu contine
% duplicate
% esteMultime(L1..Ln) = true, daca contineElement(L2..Ln, L1) == false
% Model de flux: esteMultime(i)
% L1..Ln - lista de verificat daca este multime
esteMultime([H|T]):-not(contineElement(T,H)).


%predicat care verifica egalitatea a doua multimi
%multimiEgale(L1..Ln, M1..Mp) = true, daca n=p=0
%                               toateElementeleExistaIn(L1..Ln, M1..Mp)
%                                si
%                                toateElementeleExistaIn(M1..Mp,L1..Ln)
%                                , altfel
%model de flux : multimiEgale(i,i)
%L1..Ln -prima multime de comparat
%M1..Mp - a doua multime de comparat
%multimiEgale = true, daca n=p=0
%               esteMultime(M1..Mp) si  esteMultime(L1..LN) si toateElementeleExistaIn(L1..Ln,M1..Mp) si toateElementeleExistaIn(M1..Mp, L1..Ln), altfel
multimiEgale([],[]).
multimiEgale(M1,M2):-esteMultime(M1), esteMultime(M2),toateElementeleExistaIn(M1,M2), toateElementeleExistaIn(M2,M1).

%Predicat care extrage al n-lea element
%extrageNth(L1..Ln, N, Contor) = element, daca N = Contor
%                               extrageNth(L2..Ln, N, Contor+1), altfel
%
%Model de flux: extrageNth(i,i,o)
%L1..Ln : lista din care se extrage al n-lea element
%N : pozitia de pe care vrea sa se extraga eleementul, int
%Contor : int
%Element : elementul extras de pe a n-a pozitie
extrageNth([Element|_],N,N,Element2):- Element2 is 2*Element.
extrageNth([_|Coada],N,Contor,Element):-Contor1 is Contor+1, extrageNth(Coada,N,Contor1,Element).

%apelExtrage(L1..Ln, N, Element) = extrageNth(L1..lN,N,1Element)
%model de flux: apelExtrage(i,i,i,o)
%L1..Ln - lista din care sa se extraga elementul
%N-pozitia de pe care sa se extraga elementul
%Element: elementul extras de pe a n-a pozitie
apelExtrage(Lista,N,Element):-extrageNth(Lista,N,1,Element).





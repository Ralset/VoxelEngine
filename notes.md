# Notes za maturski:

## Tehnologije
Za windows koristim:
C++17, CMake 3.x, MSYS2/MinGW
Na macu:
Clang

Od biblioteka:
GLFW, GLAD, GLM

## Resursi
https://learnopengl.com/
https://docs.gl/

## Pre projekta
Ono sto znam za OpenGL je da je to konfiguracija.
Sta to tacno znaci nisam siguran. Kako bih opisao moje shvatanje jeste da OpenGL je kao biblioteka bez implementacije, na foru .h; i onda proizvodjaci grafickih kartica prave implementaciju (driveri) tako da koristi format OpenGL-a.
Takodje OpenGL je state machine i koristi se tako sto privezemo (bind) kontekst (state) i takodje privezemo ostale stvari potrebne da bi izvrsio tu operaciju, i posle odvezemo (unbind) stvari (malo je povrsno objasnjeno jer ne znam tacno da li je ovo bas tacno).

------------------------------

## Dan 1 - 28.4.2026.
Setupovao sam projekat i povezao sa github repo-om.
Najteze je bilo podesiti tako da radi na windowsu i mac-u jer
nisam znao cmake (sad znam bas malo ali dovoljno nadam se)

Sturktura projekta izgleda ovako
imamo external u kome se nalaze biblioteke
assets u kome ce se nalaziti slike/teksture i shaderi
u src je implementacija
imamo main.cpp koji pokrece projekat
ostali folderi u src-u su
core koji sluzi za stvari kao otvaranje prozora, input i tako "mehanicke" stvari
graphics on ce da renderuje stvari i pretvara ga u kontekst za opengl ne znam jos tacno koje sve jer nisam naucio full opengl
player skripta za igraca/kameru
world u njemu ce se nalaziti vecina stvari kao chunkovi blokovi svet...

------------------------------

## Dan 2 - 29.4.2026.
Napravio sam Window klasu koja se brine oko kreacije ekrana.
Problem je bio da sam stvaio da mi pointer na glfwwindow bude private, ali napravio funkciju koja bukvalno daje pristup tome.
Promenio sam kod tako da sada imam funkcije koje daju pristup nekih od funkcionalnosti za window koje su potrebne (encapsulation).
Jedino sto sam za sada ostavio u konstruktoru sto mozda ne treba tu da bude jeste windowhints za opengl verziju i profil. Jer se ti hintovi koriste globalno ali lepse izgleda ako su deo klase za window kreaiju umesto da ih stavim u main.

### Zapazanja
Klasa treba da sadrzi i brine samo o svojim resursima - ne treba nista globalno da menja.
Encapsulation razmisljanje - prvo sve stavi privatno a posle toga daj public funkcije koje daju pristup samo onome sto je potrebno iz te klase. Ako je sve potrebno onda tek premestiti u public

------------------------------

## Dan 3 - 30.4.2026.
Nista nisam radio osim pomerio shadere u drugi fajl

------------------------------

## Dan 4 - 1.5.2026.
Dodao sam funkciju koja daje runtime error ako postoji neka greska i olaksava debuggovanje.
Takodje sam implementirao da se crtaju vertexi preko indeksa

------------------------------

## Dan 5 - 2.6.2026.
Dodao sam nesto nmg da se setim ali nista posebno

------------------------------

## Dan 6 - 3.5.2026.
Naucio sam sta je castovanje i koristim ga u window klasi jer parametri glfw funkcije za resize callback ne ukljucuju intancu moje klase i zato nisam mogao da referenciram tacnu instancu klase koja mi treba.
Onda sam zakacio na instancu glfw prozora adresu moje instance klase tako da kada je dobijem kao callback u static funkciji mogu da iskoristim static_cast tako da ce kompajler da ga pretvori/odnosi prema tom pointeru kao da je tip moje klase i onda prepisem pointer na instancu tacne klase koja poseduje tu instancu glwf prozora.

Beefovao sam sa chatgptom jer nije hteo da prizna da sam u pravu:
Imamo Window klasu i njenu instancu. this je pointer (adresa) na tu instancu. Tu adresu prosledimo GLFW-u koji je sacuva u svom internom void* polju vezanom za GLFWwindow.
Kasnije, u callback-u, iz GLFW-a trazimo tu sacuvanu adresu. GLFW nam vraca isti pointer koji smo ranije upisali. Mi ga smestamo u lokalni Window* self (ili ekvivalent), sto je nova lokalna promenljiva koja zauzima mesto u memoriji procesa.


Nastavak rada.
Napravio sam input i application klasu.
Application klasa je vlasnik window i input klase tako da onda sadrzi celu igricu.
Imao sam problem u konstruktoru oko pravljenja prozora i inicijalizacije glfw.
Zato sto glfw treba prvo da se inicijalizuje ja sam u konstruktoru to uradio pa sam napravio onda instancu window klase
Ali posto nije automatksi napravljena ona dobije default (prazni) konstruktor koji sam dodao u window klasu.
Doslo je do problema da kada zapocnem program odmah se pozove i destruktor te nove instance, zato sto se ta instanca napravi, kopira u moju vrednost unutar aplikacije, i brise sto poziva destruktor i invalidira vrednost koju smo kopirali.
Resenje je koriscenje unique_ptr (unique pointera) i make_uniqe. Napravimo jednu instancu klase window na heapu i make unique nam vraca unique_ptr koji ga poseduje.
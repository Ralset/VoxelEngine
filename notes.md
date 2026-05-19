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
http://www.cse.yorku.ca/~amana/research/grid.pdf

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

------------------------------

## Dan 7 - 4.5.2026.
Implementirao sam input za key press held i release
Takodje imao sam gresku kod window sizea jer na macu koji ima retina display njegova rezolucija je veca u pixelima, to je dovelo do problema gde postavljanje viewporta(gde se iscrtava opengl kod na ekranu) jer se nije podudaralo sa celim ekranom.
Bolje objasnjeno:
GLFW resize callback daje logicke piksele (OS koordinate), ali OpenGL radi sa fizickim pikselima (framebuffer). Na Retina displeju odnos je 2:1, pa je viewport bio duplo manji nego sto treba. Resenje: koristiti glfwGetFramebufferSize umesto parametara callback-a.

------------------------------

## Dan(i) 8 - 5-16.5.2026.
Implementirao sam sve osnovne klase koje pokrivaju opengl
Kao sto su shader vao vbo ebo vertexlayout
Tako da to sam malo skippovao jer ne znam zasto ali nisam pisao note-ove tada. Pogledaj commit history kasnije da vidim sta je tacno sve uradjeno

------------------------------

## Dan 9 - 17.5.2026.

Implementirao sam 3d blokove.
Napravio sam 3 matrixa, projection, view i model koji su potrebni za prikazivanje 3d grafike

------------------------------

## Dan 10 - 18.5.2026.

Implementirao sam kameru.
Trebam da je prebacim u sopstvenu klasu
Kamera je zapravo projection i view matrix. Projection sluzi da normalizuje value da i dubinu smanji ih ili uveca od daljine od kamere
view sluzi da prebacimo sve nase trouglove iz world spacea u view/camera space. uzima camera position u odnosu na svet i to koristi kao novi koordinatni pocetak.

Objasniti pitch i yaw i pomeranje kako to utice na view matricu.

------------------------------

## Dan 11 - 19.5.2026.

Implementirao sam klasu za kameru.
Problem koji sam nasao jeste kada sam pravio player klasu
Imam problem koji je da applicaiton klasa sadrzi window klasu, a player sadrzi input klasu
Window ima resize callback u application klasi
a input ima key i mouse callback u playeru
GLFWindow context za callbackove moze da pointuje samo na jednu klasu tako da je resenje da u applicaitonu.h napravimo struct koji cuvao pointer za application klasu i player klasu i onda mozemo da referencujemo taj struct i da preko nje biramo app ili player za odredjene callbackove

------------------------------

## Dan 11-12 - 19/20.5.2026

Sta sam krenuo da radim nakon sto mi je kamera i player proradio jeste chunk klasa.
Ono sto sam provalio jeste da je chunk vrlo tezak za implementiranje zbog grafike.
Ono sto chunk ima jeste niz 16x256x16 koji sadrzi id bloka
sad ono sto sam razmisljao jeste da kada gradimo mesh (nalaze se koordinate iz model space-a) i dodamo takodje 6 indexa za jedan face (kvadrat - 2 trougla).
Prva ideja mi je bila da napravim VBO koji sadrzi sve moguce tacke koje mogu da se koriste (grid 16x256x16) i onda da imam samo EBO koji ce sadrzati indekse vertexa u VBO-u koji se koriste (visible). Ali shvatio sam da je to los pristup jer ce VBO biti prepun vertexa koji su nepotrebni.
Bolji pristup ovome jeste da svaki put kada zatreba izgradimo nov VBO i EBO (oni su povezani) tako sto prodjemo koordinatu po koordinatu unutar chunka i pogledamo za svaku poziciju svaki face (gore dole levo desno napred nazad) i onda za svaki face dodamo 4 vertexa (mozda cak i 2 jer susedni blok deli potencijalno). Takodje jos razmatram da sve cuvam u mapi ili setu pa onda da nemam duplikate tako.
Ne razmatram vise zato sto kada dodam teksture dodaju u VBO i UV koordinate tako da za svaki face dodamo 4 vertexa.
E sad ja mogu da uzmem u chunku da kazem da su faceovi po kooridnatama kao sto je i kocka:
```cpp
float points[24] = {
    -0.5f, -0.5f, 0.5f, // dole levo front
    0.5f, -0.5f, 0.5f, // dole desno front
    0.5f, 0.5f, 0.5f,  // gore desno front
    -0.5f, 0.5f, 0.5f, // gore levo  front

    -0.5f, -0.5f, -0.5f, // dole levo back
    0.5f, -0.5f, -0.5f, // dole desno back
    0.5f, 0.5f, -0.5f,  // gore desno back
    -0.5f, 0.5f, -0.5f, // gore levo  back
};
```
Ali mislim da to rusi poentu blok klase koja treba da bude abstraktna klasa. Tako da verovatno ce onda svaki id uzimati iz takve blok klase za taj id parametre.
ALI za to mi treba blok klasa da radi i da je napisem.
PRVA Verzija ce biti chunk sa hard codovanim blok koordinatama a zatim kada to proradi mogu da razmisljam o blok klasi

------------------------------

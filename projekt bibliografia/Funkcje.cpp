#include "Funkcje.h"

using namespace std;

struct etykiety_ksiazek
{
	string etykiety;
	string imie;
	string nazwisko;
	string tytul;
	etykiety_ksiazek* lewa;
	etykiety_ksiazek* prawa;

};
/*
Deklaruj� struktur� etykiety ksi��ek oraz kolejne elementy etykiet w drzewie.
Nadaj� wska�niki na lewy i prawy w�ze� w drzewie.
*/

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Lista_dwukierunkowa
{
	Lista_dwukierunkowa* nastepny;
	Lista_dwukierunkowa* poprzedni;
	etykiety_ksiazek* etykiety;
	int numer;
};
/*
Deklaruj� list� dwukierunkow� oraz wska�niki na element poprzedni i nast�pny.
Dodaj� wska�nik na etykiety w drzewie.
*/

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void utworz_drzewo(etykiety_ksiazek*& root, string etykiety, string imie, string nazwisko, string tytul)
{
	if (!root)
		root = new etykiety_ksiazek{ etykiety, imie, nazwisko, tytul,nullptr,nullptr };
	else if (etykiety < root->etykiety) utworz_drzewo(root->lewa, etykiety, imie, nazwisko, tytul);
	else utworz_drzewo(root->prawa, etykiety, imie, nazwisko, tytul);
}
/*
Tworz� funkcj� tworz�c� drzewo
Najpierw sprawdzam czy korze� drzewa jest pusty, je�li tak, przypisuj� mu odpowiednie etykiety.
Ustalam jak b�d� one por�wnywane. 'Stringi' w etykietach b�d� por�wnywane alfabetycznie.
Na lewo id� elementy zaczynaj�ce si� na liter� alfabetu, kt�ra jest wcze�niej ni� elementy id�ce na stron� praw�.
*/

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Lista_dwukierunkowa* Stworz_liste(Lista_dwukierunkowa *&head, etykiety_ksiazek*& root, int numer)
{
	Lista_dwukierunkowa *nowa_lista = new Lista_dwukierunkowa;  //Tworz� list� dwukierunkow� i nadaj� jej wska�nik.
	nowa_lista->numer = numer;
	nowa_lista->etykiety = root;
	
	if (head == nullptr)										// je�li g�owa jest pusta
	{
		nowa_lista->nastepny = nullptr;						    // ustawiam wska�nik na element nast�pny oraz na element poprzedni
		nowa_lista->poprzedni = nullptr;						// przypisuj� im warto�� NULL
		
		head = nowa_lista;										// wskaznik head wskazuje na to samo co nowa lista
		return nowa_lista;										// i jest zwracany
	}


	else if (head->etykiety->nazwisko >= nowa_lista->etykiety->nazwisko)
	{															// je�eli element na kt�rym jeste�my jest pocz�tkiem listy
														        // wska�nik nast�pny nowego elementu ustawiamy tak by wskazywa� na aktualn� g�ow�
		nowa_lista->nastepny = head;
		nowa_lista->poprzedni = nullptr;						// aktualizujemy wskazanie wska�nika 'poprzedni' starego elementu i ka�emy mu wskazywa� na nowy element
		head->poprzedni = nowa_lista;							// ten element staje si� teraz now� g�ow� listy (czyli wstawiamy go przed poprzedni element)
		head = nowa_lista;
	}
	else {
		Lista_dwukierunkowa *obecna = head;						// szukam pozycji nowego elementu wykorzystuj�c do tego dodatkowy wska�nik,
																// kt�ry b�dzie nam pokazywa�, gdzie aktualnie jeste�my
		while (obecna->nastepny != nullptr && obecna->nastepny->etykiety->nazwisko < nowa_lista->etykiety->nazwisko)
		{
			obecna = obecna->nastepny;
		}														// nowy element le�y teraz pomi�dzy pozycj� aktualn�, a pozycj� o jeden dalej
																// (czyli pomi�dzy aktualnym elementem, a jego nastepnikiem)
		nowa_lista->poprzedni = obecna;
		nowa_lista->nastepny = obecna->nastepny;				// mo�liwe jest, �e nowy element b�dzie dodany na ko�cu. 
																// w tej sytuacji nie mo�emy aktualizowa� wskazania wska�nika obecna->nastepny,
																// bo wskazuje na null i program si� wysypie, bo udamy sie poza strukture 
		if (obecna->nastepny != nullptr) {
			obecna->nastepny->poprzedni = nowa_lista;			//aktualizacja wska�nika poprzedni, wskazuje na to samo co nowa_lista
		}
		obecna->nastepny = nowa_lista;							//aktualizujemy wskazanie 'nast�pny' (wska�nika na obecn� pozycj�) i ka�emy
	    }														//mu wskazywa� na nowa_lista (czyli jakiego� nowego elementu)  
	
	return head;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

etykiety_ksiazek* Szukaj_w_drzewie(const string& et, etykiety_ksiazek* wskaznik_na_drzewo) 
{
	while (wskaznik_na_drzewo)											// dop�ki mo�na i�� na lewo lub prawo i nie dojedziemy do konca to b�dziemy powtarza� p�tl�. 
	{
		if (wskaznik_na_drzewo->etykiety == et)							// sprawdzamy, czy etykieta, kt�ra znajduje si� w w�le drzewa na kt�ry wskazuje ten wska�nik
																		// co sobie utworzyli�my, jest taka sama jak nasza szukana etykieta wyci�gnieta z pliku.
			return wskaznik_na_drzewo;
		if (et < wskaznik_na_drzewo->etykiety)							// je�eli jednak nie s� takie same to wtedy sprawdzamy jakie s� wzgl�dem siebie.
																		
			wskaznik_na_drzewo = wskaznik_na_drzewo->lewa;				// Je�eli ta, kt�rej szukamy jest wi�ksza alfabetycznie od tej w drzewie,
		else
			wskaznik_na_drzewo = wskaznik_na_drzewo->prawa;				// kt�ra teraz por�wnujemy, to idziemy na prawo. Je�eli jest mniejsza  alfabetycznie to idziemy na lewo.
	}

	return wskaznik_na_drzewo;
}
/*

*/

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Czytaj_Opisy(const string& input_file_name_2, etykiety_ksiazek*& root)
{
	ifstream input(input_file_name_2);										// otwieram plik z etykietami
	if (!input)																//sprawdzam czy plik istnieje
	{
		cout << "Nie mozna otworzyc pliku: " << input_file_name_2 << "\n";
		return;
	}

	string imie;
	string nazwisko;
	string etykiety;
	string tytul;
	string bufor;

	while (!input.eof()) //eof - end of file					
	{
		input >> etykiety;										// w p�tli pobieram kolejno imi� i nazwisko do bia�ego znaku
		input >> imie;															
		input >> nazwisko;
		getline(input, bufor);									// funkcj� 'getline' pobieram ca�� lini�, aby odczyta� tytu�
		getline(input, tytul);
		getline(input, bufor);
		utworz_drzewo(root, etykiety, imie, nazwisko, tytul);   // tworz� drzewo z pobranymi napisami
	}

	input.close();												// zamykam plik
	return;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Czytaj_Publikacje(const string& input_file_name, etykiety_ksiazek*& root, Lista_dwukierunkowa*& head)  // Tworz� funkcj� odczytuj�c� plik 'Publikacje'
{
	ifstream Publikacje(input_file_name);																	// otwieram plik 'Publikacje'
	if (!Publikacje)																						// sprawdzam czy plik istnieje
	{
		cout << "Nie mozna otworzyc pliku: " << input_file_name << endl;
	}

	string bufor;
	etykiety_ksiazek* wskaznik_drzewo = nullptr;															// tworz� wskaznik na drzewo i przypisuj� mu warto�� NULL
	etykiety_ksiazek* dodatkowy_wskaznik = nullptr;
	int pozycja_klamry = 0;																					// Aby odczyta� etykiet� z pliku musimy wyci�gn�� tylko to
	int pozycja_drugiej_klamry = 0;																			// co znajduje si� mi�dzy dwoma klamrami, przypisujemy im warto�� 0.
	string linia;

	while (getline(Publikacje, linia))
	{
		while (linia.find("\\cite") != string::npos)														// u�ywamy funkcji 'find', aby odszuka� w tek�cie frazy "\\cite"
		{																									
			pozycja_klamry = linia.find_first_of("{");														// je�li j� znajdziemy szukamy pierwszej klamry
			pozycja_klamry = pozycja_klamry + 1;															// dodajemy 1, poniewa� potrzebujemy znak�w po klamrze
			pozycja_drugiej_klamry = linia.find_first_of("}");												// szukamy drugiej klamry
			bufor = linia.substr(pozycja_klamry, pozycja_drugiej_klamry - pozycja_klamry);					// odejmujemy pozycj� drugiej klamry od pozycji pierwszej klamry
			wskaznik_drzewo = root;
			dodatkowy_wskaznik = Szukaj_w_drzewie(bufor, wskaznik_drzewo);
			linia.replace(linia.begin() + linia.find_first_of("\\"), linia.begin() + linia.find_first_of("}") + 1, "[]"); //zamieniamy znaki
			Stworz_liste(head, dodatkowy_wskaznik, 0);
		}
	}
	Publikacje.close();																						// zamykamy plik
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Nadaj_numer(Lista_dwukierunkowa*& head)
{
	int i = 1;
	Lista_dwukierunkowa* wsk_pomocniczy = head;
	while (wsk_pomocniczy != nullptr)
	{
		wsk_pomocniczy->numer = i;
		i = i + 1;
		wsk_pomocniczy = wsk_pomocniczy->nastepny;
	}
	return;
}
/*
Przypisujemy kolejne numery etykiet w li�cie
*/

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Lista_dwukierunkowa* Szukaj_w_liscie(Lista_dwukierunkowa*& head, string etykieta)   // Funkcja, kt�ra wyszukuje odczytan� z pliku etykiet� w li�cie dwukierunkowej
{
	Lista_dwukierunkowa* wskaznik_pomocniczy = head;								// Tworzymy wskaznik pomocniczy, ktory bedziemy przesuwac po liscie zeby nie "zgubic" poczatku 
	bool czy_znaleziona = false;													// Tworzymy zmienna typu bool, ktora bedzie wyznaczala koniec naszej petli 
																					// (skonczy sie wykonywac gdy znaleziona zostanie odpowiednia etykieta)
	while (czy_znaleziona == false)													// Jak wyzej, warunkiem wykonywania petli jest szukanie elementu, zakonczy sie gdy znajdziemy go w liscie	
	{
		if (wskaznik_pomocniczy->etykiety->etykiety == etykieta)					// Sprawdzamy czy etykieta, ktora zawarta jest w liscie (wskaznik wskazuje na wezel drzewa,
		{																			// w ktorym przechowywane sa informacje o ksiazkach) jest zgodna z t� wyszukiwan� przez nas
			czy_znaleziona = true;													// Je�li tak to zmienna bool przybiera warto�� true (czyli znale�li�my element) i mo�emy wyj�� z p�tli
		}
		else wskaznik_pomocniczy = wskaznik_pomocniczy->nastepny;					// Je�li nie to znaczy, �e ten element nie zawiera takiej etykiety, wi�c "przeskakujemy" na kolejny element listy, sprawdzamy go itd.
	}
	return wskaznik_pomocniczy;														// Gdy ju� znajdziemy element to zwracamy wska�nik, kt�ry wskazuje na element z nasz� szukan� etykiet�.
}																					// Dzi�ki temu potem mo�emy wyci�gn�� numer i wrzuci� do pliku (ale to w innej funkcji)

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void usun_drzewo(etykiety_ksiazek*& root)
{
	if (!root)
		return;
	usun_drzewo(root->lewa);
	usun_drzewo(root->prawa);
	delete root;
	root = nullptr;

}
/*
Usuwam drzewo, sprawdzam czy korze�=null, a p�niej po kolei usuwam w�z�y
*/

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void usun_liste(Lista_dwukierunkowa*& head)
{
	Lista_dwukierunkowa* przesun_wskaznik = head;
	if (head == nullptr)
		return;

	while (head != nullptr)
	{
		head = head->nastepny;
		delete przesun_wskaznik;
		przesun_wskaznik = head;
		if (przesun_wskaznik != nullptr) przesun_wskaznik->poprzedni = nullptr;
	}
}

/*
Tworz� funkcj� usuwaj�c� list�, dodaj� wska�nik, kt�ry b�dzie si� przesuwa� po kolejnych elementach.
Przesuwam si� po kolejnych elementach listy usuwaj�c je, a� ca�a lista b�dzie mia�a warto�� NULL.
*/

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Zastap_numerem(Lista_dwukierunkowa*& head, const string& input_file_name, const string& output_file_name)
{
	ifstream Publikacje(input_file_name);
	if (!Publikacje)
	{
		cout << "Nie mozna otworzyc pliku: " << input_file_name << endl;
	}

	ofstream Publikacja_wyjsciowa(output_file_name);
	if (!Publikacja_wyjsciowa)
	{
		cout << "Nie mozna otworzyc pliku:" << output_file_name << endl;
	}

	string wyrazy_publikacja;
	string bufor;
	Lista_dwukierunkowa* dodatkowy_wskaznik = nullptr;
	Lista_dwukierunkowa* wskaznik_na_glowe = nullptr;
	int pozycja_klamry = 0;
	int pozycja_drugiej_klamry = 0;
	string linia;


	while (getline(Publikacje, linia))
	{
		while (linia.find("\\cite") != string::npos)
		{
			pozycja_klamry = linia.find_first_of("{");
			pozycja_klamry = pozycja_klamry + 1;
			pozycja_drugiej_klamry = linia.find_first_of("}");
			bufor = linia.substr(pozycja_klamry, pozycja_drugiej_klamry - pozycja_klamry);
			wskaznik_na_glowe = head;
			dodatkowy_wskaznik = Szukaj_w_liscie(wskaznik_na_glowe, bufor);
			linia.replace(linia.begin() + linia.find_first_of("\\"), linia.begin() + linia.find_first_of("}") + 1, "[" + to_string(dodatkowy_wskaznik->numer) + "]");
		}

		Publikacja_wyjsciowa << linia << endl;


	}
	Publikacje.close();
	Publikacja_wyjsciowa.close();
}
/*
W tej funkcji zamiast frazy \cite{etykieta} wprowadzam odpowiedni numer w nawiasach kwadratowych [numer].
Operuj� na dw�ch plikach: Publikacje i na pliku wyj�ciowym.
*/

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Wypisz_bibliografie(Lista_dwukierunkowa*& head, const string& output_file_name)
{
	Lista_dwukierunkowa* wsk_pomocniczy = head;

	ofstream Publikacja_wyjsciowa(output_file_name, ios::app);
	if (!Publikacja_wyjsciowa)
	{
		cout << "Nie mozna otworzyc pliku: " << output_file_name << endl;
	}

	Publikacja_wyjsciowa << endl;
	Publikacja_wyjsciowa << "******************************************************" << endl;
	Publikacja_wyjsciowa << "BIBLIOGRAFIA" << endl;
	Publikacja_wyjsciowa << "******************************************************" << endl;
	Publikacja_wyjsciowa << endl;


	while (wsk_pomocniczy != nullptr)
	{
		Publikacja_wyjsciowa << "[" << wsk_pomocniczy->numer << "]" << " " << wsk_pomocniczy->etykiety->imie << " " << wsk_pomocniczy->etykiety->nazwisko << " " << wsk_pomocniczy->etykiety->tytul << endl;
		wsk_pomocniczy = wsk_pomocniczy->nastepny;
	}


	Publikacja_wyjsciowa.close();
	return;
}
/*
W tej funkcji tworz� plik wyj�ciowy. Znajduj� si� w nim wypisane publikacje oraz numery z autorami.
*/

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

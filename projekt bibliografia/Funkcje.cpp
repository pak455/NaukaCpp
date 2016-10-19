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
Deklarujê strukturê etykiety ksi¹¿ek oraz kolejne elementy etykiet w drzewie.
Nadajê wskaŸniki na lewy i prawy wêze³ w drzewie.
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
Deklarujê listê dwukierunkow¹ oraz wskaŸniki na element poprzedni i nastêpny.
Dodajê wskaŸnik na etykiety w drzewie.
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
Tworzê funkcjê tworz¹c¹ drzewo
Najpierw sprawdzam czy korzeñ drzewa jest pusty, jeœli tak, przypisujê mu odpowiednie etykiety.
Ustalam jak bêd¹ one porównywane. 'Stringi' w etykietach bêd¹ porównywane alfabetycznie.
Na lewo id¹ elementy zaczynaj¹ce siê na literê alfabetu, która jest wczeœniej ni¿ elementy id¹ce na stronê praw¹.
*/

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Lista_dwukierunkowa* Stworz_liste(Lista_dwukierunkowa *&head, etykiety_ksiazek*& root, int numer)
{
	Lista_dwukierunkowa *nowa_lista = new Lista_dwukierunkowa;  //Tworzê listê dwukierunkow¹ i nadajê jej wskaŸnik.
	nowa_lista->numer = numer;
	nowa_lista->etykiety = root;
	
	if (head == nullptr)										// jeœli g³owa jest pusta
	{
		nowa_lista->nastepny = nullptr;						    // ustawiam wskaŸnik na element nastêpny oraz na element poprzedni
		nowa_lista->poprzedni = nullptr;						// przypisujê im wartoœæ NULL
		
		head = nowa_lista;										// wskaznik head wskazuje na to samo co nowa lista
		return nowa_lista;										// i jest zwracany
	}


	else if (head->etykiety->nazwisko >= nowa_lista->etykiety->nazwisko)
	{															// je¿eli element na którym jesteœmy jest pocz¹tkiem listy
														        // wskaŸnik nastêpny nowego elementu ustawiamy tak by wskazywa³ na aktualn¹ g³owê
		nowa_lista->nastepny = head;
		nowa_lista->poprzedni = nullptr;						// aktualizujemy wskazanie wskaŸnika 'poprzedni' starego elementu i ka¿emy mu wskazywaæ na nowy element
		head->poprzedni = nowa_lista;							// ten element staje siê teraz now¹ g³ow¹ listy (czyli wstawiamy go przed poprzedni element)
		head = nowa_lista;
	}
	else {
		Lista_dwukierunkowa *obecna = head;						// szukam pozycji nowego elementu wykorzystuj¹c do tego dodatkowy wskaŸnik,
																// który bêdzie nam pokazywa³, gdzie aktualnie jesteœmy
		while (obecna->nastepny != nullptr && obecna->nastepny->etykiety->nazwisko < nowa_lista->etykiety->nazwisko)
		{
			obecna = obecna->nastepny;
		}														// nowy element le¿y teraz pomiêdzy pozycj¹ aktualn¹, a pozycj¹ o jeden dalej
																// (czyli pomi¹dzy aktualnym elementem, a jego nastepnikiem)
		nowa_lista->poprzedni = obecna;
		nowa_lista->nastepny = obecna->nastepny;				// mo¿liwe jest, ¿e nowy element bêdzie dodany na koñcu. 
																// w tej sytuacji nie mo¿emy aktualizowaæ wskazania wskaŸnika obecna->nastepny,
																// bo wskazuje na null i program siê wysypie, bo udamy sie poza strukture 
		if (obecna->nastepny != nullptr) {
			obecna->nastepny->poprzedni = nowa_lista;			//aktualizacja wskaŸnika poprzedni, wskazuje na to samo co nowa_lista
		}
		obecna->nastepny = nowa_lista;							//aktualizujemy wskazanie 'nastêpny' (wskaŸnika na obecn¹ pozycjê) i ka¿emy
	    }														//mu wskazywaæ na nowa_lista (czyli jakiegoœ nowego elementu)  
	
	return head;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

etykiety_ksiazek* Szukaj_w_drzewie(const string& et, etykiety_ksiazek* wskaznik_na_drzewo) 
{
	while (wskaznik_na_drzewo)											// dopóki mo¿na iœæ na lewo lub prawo i nie dojedziemy do konca to bêdziemy powtarzaæ pêtlê. 
	{
		if (wskaznik_na_drzewo->etykiety == et)							// sprawdzamy, czy etykieta, która znajduje siê w wêŸle drzewa na który wskazuje ten wskaŸnik
																		// co sobie utworzyliœmy, jest taka sama jak nasza szukana etykieta wyci¹gnieta z pliku.
			return wskaznik_na_drzewo;
		if (et < wskaznik_na_drzewo->etykiety)							// je¿eli jednak nie s¹ takie same to wtedy sprawdzamy jakie s¹ wzglêdem siebie.
																		
			wskaznik_na_drzewo = wskaznik_na_drzewo->lewa;				// Je¿eli ta, której szukamy jest wiêksza alfabetycznie od tej w drzewie,
		else
			wskaznik_na_drzewo = wskaznik_na_drzewo->prawa;				// która teraz porównujemy, to idziemy na prawo. Je¿eli jest mniejsza  alfabetycznie to idziemy na lewo.
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
		input >> etykiety;										// w pêtli pobieram kolejno imiê i nazwisko do bia³ego znaku
		input >> imie;															
		input >> nazwisko;
		getline(input, bufor);									// funkcj¹ 'getline' pobieram ca³¹ liniê, aby odczytaæ tytu³
		getline(input, tytul);
		getline(input, bufor);
		utworz_drzewo(root, etykiety, imie, nazwisko, tytul);   // tworzê drzewo z pobranymi napisami
	}

	input.close();												// zamykam plik
	return;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Czytaj_Publikacje(const string& input_file_name, etykiety_ksiazek*& root, Lista_dwukierunkowa*& head)  // Tworzê funkcjê odczytuj¹c¹ plik 'Publikacje'
{
	ifstream Publikacje(input_file_name);																	// otwieram plik 'Publikacje'
	if (!Publikacje)																						// sprawdzam czy plik istnieje
	{
		cout << "Nie mozna otworzyc pliku: " << input_file_name << endl;
	}

	string bufor;
	etykiety_ksiazek* wskaznik_drzewo = nullptr;															// tworzê wskaznik na drzewo i przypisujê mu wartoœæ NULL
	etykiety_ksiazek* dodatkowy_wskaznik = nullptr;
	int pozycja_klamry = 0;																					// Aby odczytaæ etykietê z pliku musimy wyci¹gn¹æ tylko to
	int pozycja_drugiej_klamry = 0;																			// co znajduje siê miêdzy dwoma klamrami, przypisujemy im wartoœæ 0.
	string linia;

	while (getline(Publikacje, linia))
	{
		while (linia.find("\\cite") != string::npos)														// u¿ywamy funkcji 'find', aby odszukaæ w tekœcie frazy "\\cite"
		{																									
			pozycja_klamry = linia.find_first_of("{");														// jeœli j¹ znajdziemy szukamy pierwszej klamry
			pozycja_klamry = pozycja_klamry + 1;															// dodajemy 1, poniewa¿ potrzebujemy znaków po klamrze
			pozycja_drugiej_klamry = linia.find_first_of("}");												// szukamy drugiej klamry
			bufor = linia.substr(pozycja_klamry, pozycja_drugiej_klamry - pozycja_klamry);					// odejmujemy pozycjê drugiej klamry od pozycji pierwszej klamry
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
Przypisujemy kolejne numery etykiet w liœcie
*/

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Lista_dwukierunkowa* Szukaj_w_liscie(Lista_dwukierunkowa*& head, string etykieta)   // Funkcja, która wyszukuje odczytan¹ z pliku etykietê w liœcie dwukierunkowej
{
	Lista_dwukierunkowa* wskaznik_pomocniczy = head;								// Tworzymy wskaznik pomocniczy, ktory bedziemy przesuwac po liscie zeby nie "zgubic" poczatku 
	bool czy_znaleziona = false;													// Tworzymy zmienna typu bool, ktora bedzie wyznaczala koniec naszej petli 
																					// (skonczy sie wykonywac gdy znaleziona zostanie odpowiednia etykieta)
	while (czy_znaleziona == false)													// Jak wyzej, warunkiem wykonywania petli jest szukanie elementu, zakonczy sie gdy znajdziemy go w liscie	
	{
		if (wskaznik_pomocniczy->etykiety->etykiety == etykieta)					// Sprawdzamy czy etykieta, ktora zawarta jest w liscie (wskaznik wskazuje na wezel drzewa,
		{																			// w ktorym przechowywane sa informacje o ksiazkach) jest zgodna z t¹ wyszukiwan¹ przez nas
			czy_znaleziona = true;													// Jeœli tak to zmienna bool przybiera wartoœæ true (czyli znaleŸliœmy element) i mo¿emy wyjœæ z pêtli
		}
		else wskaznik_pomocniczy = wskaznik_pomocniczy->nastepny;					// Jeœli nie to znaczy, ¿e ten element nie zawiera takiej etykiety, wiêc "przeskakujemy" na kolejny element listy, sprawdzamy go itd.
	}
	return wskaznik_pomocniczy;														// Gdy ju¿ znajdziemy element to zwracamy wskaŸnik, który wskazuje na element z nasz¹ szukan¹ etykiet¹.
}																					// Dziêki temu potem mo¿emy wyci¹gn¹æ numer i wrzuciæ do pliku (ale to w innej funkcji)

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
Usuwam drzewo, sprawdzam czy korzeñ=null, a póŸniej po kolei usuwam wêz³y
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
Tworzê funkcjê usuwaj¹c¹ listê, dodajê wskaŸnik, który bêdzie siê przesuwaæ po kolejnych elementach.
Przesuwam siê po kolejnych elementach listy usuwaj¹c je, a¿ ca³a lista bêdzie mia³a wartoœæ NULL.
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
Operujê na dwóch plikach: Publikacje i na pliku wyjœciowym.
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
W tej funkcji tworzê plik wyjœciowy. Znajduj¹ siê w nim wypisane publikacje oraz numery z autorami.
*/

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

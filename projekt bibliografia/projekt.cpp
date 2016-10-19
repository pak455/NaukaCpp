#include <iostream>
#include <fstream>
#include <string>

#include "Parametry.h"
#include "Pomoc.h"
#include "Funkcje.h"

using namespace std;


int main(int argc, char**argv)
{
	string input_file_name, input_file_name_2 ,output_file_name;
	if (!parse_parameters(argc, argv, input_file_name, input_file_name_2,output_file_name))
	{
		cout << "Bledne parametry:"<<endl;
		help();
		return 1; 
	}

	etykiety_ksiazek* root = nullptr;
	Lista_dwukierunkowa* head = nullptr;
	Czytaj_Opisy(input_file_name_2, root);
	Czytaj_Publikacje(input_file_name, root, head);
	Nadaj_numer(head);
	Zastap_numerem(head, input_file_name, output_file_name);
	Wypisz_bibliografie(head, output_file_name);
	usun_drzewo(root);
	usun_liste(head);

	return 0;
}


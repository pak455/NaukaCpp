//#pragma once
#include <iostream>
#include <string>
#include <fstream>

#ifndef _FUNKCJE_H
#define _FUNKCJE_H

struct etykiety_ksiazek;
struct Lista_dwukierunkowa;

/*
Funkcja tworzy drzewo
root-korzen drzewa
etykiety,imie,nazwisko,tytul-komorki w ktorych przechowywane sa informacje odczytane z pliku
*/
void utworz_drzewo(etykiety_ksiazek*& root, std::string etykiety, std::string imie, std::string nazwisko, std::string tytul);
/**/
Lista_dwukierunkowa* Stworz_liste(Lista_dwukierunkowa *&head, etykiety_ksiazek*& root, int numer);
etykiety_ksiazek* Szukaj_w_drzewie(const std::string& et, etykiety_ksiazek* wskaznik_na_drzewo);
void Czytaj_Opisy(const std::string& input_file_name_2, etykiety_ksiazek*& root);
void Czytaj_Publikacje(const std::string& input_file_name, etykiety_ksiazek*& root, Lista_dwukierunkowa*& head);
void Nadaj_numer(Lista_dwukierunkowa*& head);
Lista_dwukierunkowa* Szukaj_w_liscie(Lista_dwukierunkowa*& head, std::string etykieta);
void usun_drzewo(etykiety_ksiazek*& root);
void usun_liste(Lista_dwukierunkowa*& head);
void Zastap_numerem(Lista_dwukierunkowa*& head, const std::string& input_file_name, const std::string& output_file_name);
void Wypisz_bibliografie(Lista_dwukierunkowa*& head, const std::string& output_file_name);

#endif

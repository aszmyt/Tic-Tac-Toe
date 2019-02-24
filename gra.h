#pragma once
#include <iostream>

using namespace std;
class gra
{
public:
	gra(int rozmiar, int ile){
		this->ile = ile;
		aktualnygracz='o';
		this->rozmiar = rozmiar;
		tab = new char*[rozmiar];  //przydzielenie pamieci tablicy 2wymiarowej
		for( int i=0 ; i< rozmiar; i++){
			tab[i] = new char[rozmiar]; }

		for(int m=0; m<rozmiar; m++){
			for(int n=0; n<rozmiar; n++){
				tab[m][n] = ' ';
			}
		}
	}
	~gra(){
		for(int i = 0; i< rozmiar; i++){ //zwalnianie pamieci
			delete[]tab[i];
		}
		delete[]tab;
	}


	char **tab;
	int rozmiar;
	char aktualnygracz;
	int ile;

	bool wygrana(char znak);
	bool remis();
	int minmax(char znak, int depth);
	int ruch_komputera();
	void graj();
	void wypisz_plansze();
	int alfabeta(char znak, int depth, int alfa, int beta);
};


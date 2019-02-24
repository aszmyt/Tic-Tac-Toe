#include "gra.h"

bool gra::wygrana(char znak){

	int licznik;
	for(int i=0; i<rozmiar; i++){ 
		licznik=0;
		// obsluguja wiersze
		//jesli do  konca dojdzie jako true to wygrana
		for(int j=0; j<rozmiar; j++){
			if(tab[i][j]==znak){
				licznik++;
			}
			else{
				licznik = 0;
			}
			if(licznik ==ile){
				return true;
			}

		}
	}
	for(int i=0; i<rozmiar; i++){          //obsluguja kolumny
		licznik = 0;              //jesli do  konca dojdzie jako true to wygrana
		for(int j=0; j<rozmiar; j++){
			if(tab[j][i]==znak){
				licznik++;
			}
			else{
				licznik=0;
			}
			if(licznik ==ile){
				return true;
			}
		}
	}
	//obsluguja przekotnych
	licznik = 0;               //jesli do  konca dojdzie jako true to wygrana
	for(int i=0; i<rozmiar; i++){
		if(tab[i][i]==znak){
			licznik++;
		}
		else{
			licznik=0;
		}
		if(licznik ==ile){
			return true;
		}
	}

	//obsluguja przekotnych
	licznik = 0;                  //jesli do  konca dojdzie jako true to wygrana
	for(int i=0; i<rozmiar; i++){
		if(tab[i][rozmiar-i-1]==znak){
			licznik++;
		}
		else{
			licznik=0;
		}
		if(licznik ==ile){
			return true;
		}
	}
	return false;
}
bool gra::remis(){
	for(int i=0; i<rozmiar; i++){
		for(int j=0; j<rozmiar; j++){
			if(tab[i][j] ==' '){ //jesli znak pusty bedzie to false nie ma remisu
				return false;
			}
		}
	}
	return true; //jesli wszystko bedzie zape�nione to remis
}

int gra::minmax(char znak, int depth){    // depth max ilosc reukrencji jaka damy mu odiagnac, ile do przodu bedzie przewidywa� ruchy
	int wartosc_pola;
	int tmp;
	if (wygrana(znak)) {
		if (znak == 'x')
			return (1);
		else
			return (-1);
	}
	if (remis()) {
		return (0);
	}
	if (depth == 0){
		return 0;

	}
	znak = (znak == 'o') ? 'x' : 'o';
	wartosc_pola = (znak == 'o') ? ((rozmiar* rozmiar) + 1) : -(rozmiar*rozmiar) - 1;

	for (int i = 0; i < rozmiar; i++) {
		for(int j=0; j< rozmiar; j++){
			if (tab[i][j] == ' ') {
				tab[i][j] = znak;

				tmp = minmax(znak, depth - 1);
				tab[i][j]= ' ';
				if ((znak == 'o' && tmp < wartosc_pola) || (znak == 'x' && tmp > wartosc_pola)) {

					wartosc_pola = tmp;

				}

			}

		}

	}

	return (wartosc_pola);
}
int gra::ruch_komputera(){
	int oszacowanie;
	int best = -rozmiar*rozmiar-1;
	int ruch;
	for (int i=0; i<rozmiar; i++){
		for(int j=0; j< rozmiar; j++){
			if(tab[i][j] ==' '){            //jesli puste to ruszamy komp na niego xem
				tab[i][j]='x';
				oszacowanie = alfabeta('x',3, -999999, 999999);
				//oszacowanie = minmax('x',7);
				tab[i][j]=' ';      //zwraca jaki ten  ruch byl dobry
				if(oszacowanie > best){
					best = oszacowanie;
					ruch = i*rozmiar + j;
				}
			}

		}
	}return ruch; //return true
}

void gra::graj(){
	int ruch;
	int w, k;

	if(aktualnygracz=='o'){
		cout<<"podaj pole"<<endl;
		cin>> ruch;
		w = ruch/rozmiar;
		k = ruch - (w*rozmiar);

		while(ruch<0 ||ruch>=rozmiar*rozmiar ||tab[w][k]!=' '){
			cout<<"podaj jeszcze raz"<<endl;
			cin>> ruch;
			w = ruch/rozmiar;
			k = ruch - (w*rozmiar);
		}
		tab[w][k] = 'o';
	}
	else{
		ruch=ruch_komputera();
		w=ruch/rozmiar;
		k = ruch - (w*rozmiar);
		tab[w][k]='x';
		wypisz_plansze();
	}
	if(aktualnygracz=='o'){
		aktualnygracz='x';
	}
	else{
		aktualnygracz='o';
	}

}
int gra::alfabeta(char znak, int depth, int alfa, int beta)
{
	int wartosc_pola;
	if (wygrana(znak)) {
		if (znak == 'x')
			return (1);
		else
			return (-1);
	}
	if (remis()) {
		return (0);
	}
	if (depth == 0){
		return 0;
	}
	znak = (znak == 'o') ? 'x' : 'o';
	wartosc_pola = (znak == 'o') ? ((rozmiar* rozmiar) + 1) : -(rozmiar*rozmiar) - 1;

	for (int i = 0; i < rozmiar; i++) {
		for(int j=0; j< rozmiar; j++){
			if (tab[i][j] == ' ') {
				tab[i][j] = znak;
				if(znak =='o'){
					beta = min(beta, alfabeta(znak, depth-1, alfa, beta));
				}
				else{
					alfa = max(alfa, alfabeta(znak, depth-1, alfa, beta));
				}
				tab[i][j]= ' ';  //czyszczenie pola
				if(alfa>=beta){
					break;
				}
			}

		}

	}
	if(znak =='o'){
		return beta;
	}
	if(znak =='x'){
		return alfa;
	}
	return 0;
}

void gra::wypisz_plansze(){
	for (int i=0; i<rozmiar; i++){
		for(int j=0; j< rozmiar; j++){
			cout<<tab[i][j]<< "|";
		}
		cout<<endl;
	}cout<<endl;
}

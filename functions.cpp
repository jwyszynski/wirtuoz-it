/** Dodatkowe funkcje do programu Wirtuoz IT **/

#include <iostream> // cout // cin
#include <cstdlib> // atoi // system()
#include "functions.h" // err

using namespace std;

/** Funkcja err czysci ekran i wyswietla informacje o bledzie. Takze zwraca informacja o blendzie.
 */

int err(string err_text, int err_code) /* (text blendu, kod blendu) */
{
	system("CLS");
	cout << "## Wystapil blad programu ##" << endl;
	cout << "Opis blendu: " << err_text << endl;
	cout << "Kod blendu:" << err_code << endl;
	return err_code;
}

/** Funkcja losuje liczbe calkowita z podanego zakresu.
 */
int liczbaLosowaZ_Zakresu(int startowa_liczba, int koncowa_liczba) {
	int wylosowana_liczba = ((rand() % (koncowa_liczba - startowa_liczba + 1)) + startowa_liczba);
	return wylosowana_liczba;
}



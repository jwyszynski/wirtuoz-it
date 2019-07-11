/* Napisz program do nauki pisania na klawiaturze (bezwzrokowego).
 * Jako wzor zobacz program „Mistrz klawiatury”. Losuj z pliku wybrane teksty, slowa. Stwórz menu do obslugi programu.
 */
/**
  * This is a documentation comment block
  * @param
  * @author Jakub Wyszynski
  */

#include <iostream>
#include <string>
#include <fstream> // odczyt danych z pliku
#include <cstring> // Do funkcji tr
#include <cstdlib> // srand
#include <ctime>   // srand
#include <conio.h> // getch()
#include <windows.h> // gotoxy
#include "functions.h" // err() // liczbaLosowaZ_Zakresu()

using namespace std;

string zdanie_wzor = "Ala ma kota";
string zdanie_wpisane;
string zdanie_bledy;
int bledy = 0;
int wszystkie_bledy = 0;
char wcisniety_znak; /* Wcisniety znak */
int blad_flaga = 0;

void gotoxy( int x, int y )
{
    COORD c;
    c.X = x - 1;
    c.Y = y - 1;
    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), c );
}

string jakiZnak(char input)
{
    string output;
    output.clear();
    output += input;
    if (input==32) output = "[Space]";
    if (input==8) output = "[Backspace]";
    return output;
}

int zlicz_Bledy()
{
    bledy = 0;
    zdanie_bledy.clear();
    for(int i = 0 ; i < zdanie_wpisane.length() ; i ++)
    {
        if (zdanie_wpisane[i]!=zdanie_wzor[i])
        {
            bledy++;
            zdanie_bledy+="^";
            //wszystkie_bledy++;
        }
        else zdanie_bledy += " ";
    }
    return bledy;
}

void czy_blad()
{
    if (zdanie_wpisane[zdanie_wpisane.length()-1]!=zdanie_wzor[zdanie_wpisane.length()-1]&&wcisniety_znak!=8)
    {
        wszystkie_bledy++; blad_flaga = 1;
    } else blad_flaga = 0;
}

void odswiez_UI()
{
    system("CLS");
    cout << "-------- Przepisz ponizsze znaki ---------\n";
    cout << "==========================================\n\n";

    cout << "Wszystkie bledy: " << wszystkie_bledy << "\n\n";
    //if (bledy == 0) cout << "Brak blendow" << "\n\n";
    //if (bledy == 1) cout << "Masz 1 blad" << "\n\n";
    //if (bledy >= 2) cout << "Muszisz poprawic to co napisales(wiencej niz 1 blad)" << "\n\n";

    cout << "Znak jaki wpisales: " << jakiZnak(wcisniety_znak) << " ";
    if (blad_flaga > 0) cout << "Powinno byc: " << jakiZnak(zdanie_wzor[zdanie_wpisane.length()-1]);
    cout << "\n";
    cout << "==========================================\n";
    cout << "Przepisz: " << zdanie_wzor << "\n";

    cout << "Wpisales: " << zdanie_wpisane << "\n";
    cout << "Blendy:   " << zdanie_bledy << "\n";
    gotoxy(zdanie_wpisane.length()+11,9);
}

void przepisz_to()
{
    odswiez_UI();
    for (int i = 0 ; i < zdanie_wzor.length()||bledy!=0 ; )
    {
        wcisniety_znak = _getch();
        if (wcisniety_znak==8&&i>0)
        {
            zdanie_wpisane = zdanie_wpisane.substr(0,zdanie_wpisane.length()-1);
            i=i-1;
        }
        else if (wcisniety_znak!=8&&zdanie_wpisane.length()<=zdanie_wzor.length())
        {
            zdanie_wpisane += wcisniety_znak;
            i++;
        }
        zlicz_Bledy();
        czy_blad();
        odswiez_UI();

    }
}

void pobierzZasobyZ_PlikuI_Wylosuj(string typ)
{
    fstream plik;
    plik.open( typ.c_str(), ios::in );

    if(plik.good()==false) err(string("Nie mozna otworzyc pliku!"), 400);

    int i = 0;
    string linia;
    string tab[50];
    while (getline(plik, linia))
    {
        tab[i] = linia;
        cout << tab[i] << "\n\n";
        i++;
    }

    zdanie_wzor = tab[liczbaLosowaZ_Zakresu(0, i-1)];

    plik.close();
}



int main()
{
    srand( time( NULL ) );

    /**< Ponizej kodowanie polskich znakow */
    //setlocale(LC_CTYPE, "Polish");

    cout << "Witaj w programie Wirtuoz IT (mistrz klawiatury)" << endl;
    cout << "============ MENU =============" << endl;
    cout << "  1. Przepisuj losowe slowa" << endl;
    cout << "  2. Przepisuj cale zdania" << endl;
    //cout << "  3. --" << endl;
    //cout << "  4. Instrukcja obslugi" << endl;
    cout << "===============================" << endl;
    cout << "*         WERSJA 0.1          *" << endl;
    cout << "===============================" << endl;

    char wybor;
    wybor = _getch();
    for(;;)
    {
        switch(wybor)
        {
        case '1':
            {
                pobierzZasobyZ_PlikuI_Wylosuj("slowa.txt");
                przepisz_to();
            }
        break;
        case '2':
            {
                pobierzZasobyZ_PlikuI_Wylosuj("zdania.txt");
                przepisz_to();
            }
        break;
        default:
            {
                exit(1);
            }
        }

        system("CLS");
        if (wszystkie_bledy==0)
            cout << "Brawo, piszesz bezblednie!\n";
        else
            cout << "Popelniles " << wszystkie_bledy << " bledow.\n";
        cout << "Czy chcesz pocwiczyc jeszcze raz? (t/n)";
        char wybor_koncowy = _getch();
        if (wybor_koncowy=='t'||wybor_koncowy=='T')
        {
            zdanie_wzor.clear();
            zdanie_wpisane.clear();
            zdanie_bledy.clear();
            bledy = 0;
            wszystkie_bledy = 0;
            wcisniety_znak = ' ';
            blad_flaga = 0;
            continue;
        }
        break;
    }




    return 0;
}



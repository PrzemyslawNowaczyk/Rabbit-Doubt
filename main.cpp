#include <cstdlib>
#include <iostream>
#include <windows.h>
#include <fstream>
#include <cstring>
#include <conio.h>
#include <math.h>
#include <ctime>


using namespace std;


enum grupa {pierwsze, drugie};


enum kolor {bialy, czerwony, szary, niebieski, zolty};


struct kroliki
{
    int numer;
    string imie;
    bool wilk;
    bool zywy;
    bool izolatka;
    grupa stado;
    bool oznaczony;
    bool widoczny;
};


struct wyniki
{
	int pozycja;
	string imie;
	int ilekrolikow;
	int dni;
	int ruchy;
	float wynik;
};


int LiczKroliki(int KrolikowOgolem, kroliki *krolik, int ktore);
int srodek (string napis);
int zagryz (int KrolikowOgolem, int KtoreStado, kroliki *krolik);
void BladKomendy (string blad);
void braki();
void buforclr();
void color (string kolor);
void gotoxy (int x, int y);
void gra (int IleKrolikow, string ImieGracza, kroliki *krolik, int IleWilkow);
void intro();
void koniec();
void lineclr (int x);
void literuj (string napis, int speed, bool dzwiek);
void menu();
void NocnyRaport (int KrolikowOgolem, int *ofiary, kroliki *krolik);
void NowaGra();
void pokazranking ();
void StanStada (int KrolikowOgolem, kroliki *krolik, int dzien, int ZostaloRuchow, int izolatka);
void strtochar (string napis, char *tab);
void Tworcy();
void welcome();
void wpiszwranking(int KrolikowOgolem, int KrolikowZostalo, int WilkowOgolem, int dni, int ruchy, string ImieGracza, bool caly);
void zakonczenie (string wynik);
void zasady();
void zdradzwynik (int wynik, int ruchy, int dni, int KrolikowOgolem, kroliki *krolik);
bool SprawdzWartosc( int wartosc, int zakres, kroliki *krolik);
string nadajimie (int NumerImienia);






//wyœwietlanie b³êdu krytycznego
void bladkrytyczny (string blad)
{
	system ("cls");
	gotoxy (srodek (blad), 13);
	cout << blad;
	gotoxy (52,25);
	cout << "nacisnij dowolny klawisz...";
	buforclr();
	getch();
	exit(0);
}






//funkcja okreœlaj¹ca kolor tekstu
// pobrana z http://cpp0x.pl/kursy/Kurs-WinAPI-C++/Roznosci/Kolory-w-konsoli/374

void color (kolor jakikolor)
{

    if (jakikolor == szary)
    {
        SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED );
    }

    if (jakikolor == czerwony)
    {
        SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), FOREGROUND_RED | FOREGROUND_INTENSITY);
    }

    if (jakikolor == bialy)
    {
        SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
    }

    if (jakikolor == niebieski)
    {
        SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), FOREGROUND_GREEN | FOREGROUND_BLUE);
    }

    if (jakikolor == zolty)
    {
        SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), FOREGROUND_GREEN | FOREGROUND_RED);
    }

}





//funkcja czyszcz¹ca bufor klawiatury
void buforclr ()
{
    char a;
    while ( kbhit() )
    {
    a = getch();
    }
}




//funkcja obliczaj¹ca wysrodkowan¹ pozycjê napisu
int srodek(string napis)
{
    return ( ( 80 - napis.length() ) / 2);
}




//funkcja czyszcz¹ca tylko jedn¹ liniê tekstu
void lineclr(int x)
{
    gotoxy(1,x);
    cout << "                                                                                ";
}




//funkcja ustawiaj¹ca kursor tekstowy w okreœlonej pozycji
//http://www.kaspro.pl/instrukcja-iteracyjna-ptle.html

void gotoxy(int x, int y)
{
    COORD c;
    c.X = x - 1;
    c.Y = y - 1;
    SetConsoleCursorPosition (GetStdHandle(STD_OUTPUT_HANDLE), c);
}




//procedura lietruj¹ca tekst z podan¹ prêdkoœci¹
void literuj(string napis, int speed, bool dzwiek)
{
    for (int k=0; k < napis.length(); k++)
    {
        cout<<napis[k];

        if (dzwiek == 1)
        {

            if (speed <= 60)
            {

                if (k % 2 == 0)
                {
                    Beep(300,8);
                }

            }

            else
            {
                Beep(300,8);
            }

        }

        Sleep(speed);

    }

}






//wskazanie, ¿e prace nad funkcj¹ wci¹¿ trwaj¹                                  Po skoñczeniu projektu wywaliæ!
void braki()
{
    system("cls");
    cout << "Obecnie brak tej funkcji... ";
    Sleep(1000);
    menu();
}






//ekran powitalny
void welcome()
{
    system("cls");
    ifstream plik ("logo.txt");

    if (plik)
    {
        string linijka;

        while (getline (plik, linijka))
        {
           cout << linijka << endl;
        }

	}

    else
	{
		bladkrytyczny ("Blad wczytywania pliku logo.txt!");
	}

    plik.close();

	Sleep(3000);

}




//wyœwietla g³ówne menu gry
void menu()
{

    char wybor = 0;

    while (wybor != 'n' || wybor != 'i')
    {

        system("cls");
        cout << "MENU GLOWNE";
        gotoxy (5,5);
        cout << "[n]owa gra";
        gotoxy (5,6);
        cout << "[i]ntro";
        gotoxy (5,7);
        cout << "[z]asady";
        gotoxy (5,8);
        cout << "[r]anking";
        gotoxy (5,9);
        cout << "[t]worca";
		gotoxy (5,10);
        cout << "[w]yjscie";
        gotoxy (5,11);


        buforclr();
        wybor = getch();


        switch (wybor)
        {


            case 'n':
            case 'N':

                NowaGra();
                break;




            case 'i':
            case 'I':

                intro();
                break;




            case 'z':
            case 'Z':

                zasady();
                break;




            case 'r':
            case 'R':

                pokazranking();
                break;




			case 't':
            case 'T':

                Tworcy();
                break;



            case 'w':
            case 'W':
            case 27:

                koniec();
				break;

        }
    }
}






//wczytywanie z pliku tekstowego intra gry
void intro()
{
    system("cls");
    ifstream plik ("intro.txt");

    if (plik)
    {
        string linijka;
        bool koniec = 0;
        int pozycja = 0;

        while (!koniec)
        {
            getline(plik, linijka);

            if (linijka=="end.")
            {
                koniec = 1;
            }

			else
            {
                gotoxy (srodek (linijka), (pozycja*2)+3);
                literuj(linijka, 30, 0);
                Sleep(1000);
			}

			pozycja++;

        }

        welcome();
        gotoxy (52,25);
        cout << "nacisnij dowolny klawisz...";
        buforclr();
        getch();
    }

    else
	{
		bladkrytyczny ("Blad wczytywania pliku intro.txt!");
	}

    plik.close();

}






//wyswietla (niezwykle ubogie) creditsy
void Tworcy()
{
	system("cls");
    ifstream plik ("tworcy.txt");

    if (plik)
    {
        string linijka;

        while (getline(plik, linijka))
        {
			cout << linijka << endl;
        }

        gotoxy (52,25);
        cout << "nacisnij dowolny klawisz...";
        buforclr();
        getch();

    }

    else
	{
		bladkrytyczny ("Blad wczytywania pliku tworcy.txt!");
	}

    plik.close();

}





//pokazuje aktualny ranking
void pokazranking ()
{
	system("cls");

	gotoxy (5, 1);
	cout <<" __RANKING_______________________________________________________________ ";
	gotoxy (5, 2);
	cout <<"|--#--.-------GRACZ-------.--WIELKOSC-STADA--.--DNI--.--RUCHY--.--WYNIK--|";

	for (int y = 3; y <= 23 ; y++)
	{
		gotoxy (5, y);
		cout <<"|     |                   |                  |       |         |         |";
	}

	gotoxy (5, 24);
	cout <<"|_____|___________________|__________________|_______|_________|_________|";



	wyniki wynik[20];
	ifstream plik ("ranking.txt");

	int k = 0;

	if (plik)
    {
        string linijka;
		char tablica[6] = {0};
		int kontrolna = -1;

        while ( (getline (plik, linijka) ) && (k < 20) )
        {

			kontrolna++;

            if (kontrolna == 0)
            {
            strtochar (linijka, tablica);
			wynik[k].pozycja = atoi (tablica);
            }

		    if (kontrolna == 1)
            {
			wynik[k].imie = linijka;
            }

            if (kontrolna == 2)
            {
			strtochar (linijka, tablica);
			wynik[k].ilekrolikow = atoi (tablica);
            }

			if (kontrolna == 3)
            {
			strtochar (linijka, tablica);
			wynik[k].dni = atoi (tablica);
            }

			if (kontrolna == 4)
            {
			strtochar (linijka, tablica);
			wynik[k].ruchy = atoi (tablica);
            }

			if (kontrolna == 5)
            {
			strtochar (linijka, tablica);
			wynik[k].wynik = atof (tablica);
            }

            if (kontrolna == 6)
            {
			k++;
			kontrolna = -1;
            }

        }

	}

	else
	{
		bladkrytyczny ("Blad wczytywania pliku ranking.txt!");
	}

	plik.close();


	int ilewynikow = k;

	for (int i = 0; i < ilewynikow; i++)
	{
		gotoxy (8,i + 4);
		cout << wynik[i].pozycja;
		gotoxy (13 + ( (17 - wynik[i].imie.length()) / 2 ) ,i + 4);
		cout << wynik[i].imie;
		gotoxy(40,i + 4);
		cout << wynik[i].ilekrolikow;
		gotoxy(54,i + 4);
		cout << wynik[i].dni;
		gotoxy(63,i + 4);
		cout << wynik[i].ruchy;
		gotoxy(71,i + 4);
		cout << wynik[i].wynik;
	}

	gotoxy (52,25);
	cout << "nacisnij dowolny klawisz...";
	buforclr();
	getch();
}






//Pytanie kontrolne przed opuszczniem progarmu
void koniec ()
{

    char wybor = 0;

     while (wybor != 'y' && wybor != 'Y' &&                                     // 27 = "escape"
            wybor != 'n' && wybor != 'N' &&                                     // 13 = "enter"
            wybor != 27  && wybor != 13)
     {

         system("cls");
         string komunikat = "Czy na pewno chcesz zakonczyc gre? (y/n)";
         gotoxy (srodek (komunikat),10);
         cout << komunikat;

         buforclr();
         wybor = getch();

         if (wybor == 'y' || wybor == 'Y' || wybor == 13)
         {
            exit(0);
         }

     }

}






//wczytywanie zasad gry
void zasady()
{
    system("cls");
    ifstream plik ("zasady.txt");

    if (plik)
    {
        string linijka;
        bool koniec = 0;

        while (getline (plik, linijka) )
        {

            if (linijka=="end.")
            {
                buforclr();
				getch();
				system ("cls");
            }

			else
            {
                cout << linijka << endl;
			}

        }

    }

    else
	{
		bladkrytyczny ("Blad wczytywania pliku zasady.txt!");
	}

    plik.close();

}






//Zwraca imie o konkretnym numerze z bazy plików
string nadajimie (int NumerImienia)
{
    ifstream BazaImion ("names.txt");
    string ImieZPliku;

    for (int s = 0; s < NumerImienia; s++)
        {
            (getline (BazaImion, ImieZPliku));
        }

    BazaImion.close();

    return ImieZPliku;
}




// rozpoczêcie rozgrywki
void NowaGra()
{

    //czytanie imienia gracza (do u¿ycia przy rankingu)
    system ("cls");
    gotoxy(20,12);
    cout << "Podaj swoje imie: ";

    string ImieGracza;
    cin.sync();
	getline (cin, ImieGracza);
	if (ImieGracza == "")
    {
        ImieGracza = "Anonim";
    }


    //czytanie iloœci królików, które bêd¹ w grze
    system ("cls");
    string komunikat = "Podaj ilosc krolikow w twoim stadzie";
    gotoxy (srodek (komunikat), 10);
    cout << komunikat;
    komunikat = "(minimalna wielkosc stada to 10 krolikow";
    gotoxy (srodek (komunikat), 11);
    cout << komunikat;
    komunikat = "maksymalna to 45 krolikow)";
    gotoxy (srodek (komunikat), 12);
    cout << komunikat;
    gotoxy (39, 13);


    string blad = "Nieprawidlowa wartosc!";
    int ilekrolikow = 0;
    bool poprawny = 0;

    while (!poprawny)
    {
        cin.sync();
        cin >> ilekrolikow;

        if (cin.fail())
        {
            cin.clear();
            cin.sync();
            lineclr(13);
            lineclr(14);
            lineclr(15);
            gotoxy (srodek (blad), 13);
            cout << blad;
            Sleep (1500);
            lineclr(13);
            lineclr(14);
            lineclr(15);
            gotoxy (39, 13);
            buforclr();
        }

        else
        {

            if (ilekrolikow < 10 || ilekrolikow > 45)
            {
                lineclr(13);
                lineclr(14);
                lineclr(15);
                gotoxy (srodek (blad), 13);
                cout << blad;
                Sleep (1500);
                lineclr(13);
                lineclr(14);
                lineclr(15);
                gotoxy (39, 13);
                buforclr();
            }

            else
            {
                poprawny = 1;
            }

        }

    }

    system("cls");


    // skanowanie pliku z baz¹ imion w celu ustalenia jej wielkoœci

    int ileimion = 0;

    ifstream bazaimion ("names.txt");
    if (bazaimion)
    {
        string linijka;

        while (getline(bazaimion, linijka))
            {
                ileimion++;
            }
    }

    else
	{
		bladkrytyczny ("Blad wczytywania pliku names.txt!");
    }

    bazaimion.close();


	//b³¹d na wypadek, gdyby w bazie nie by³o 45 imion.
	if (ileimion < 45)
	{
		bladkrytyczny ("Baza imion jest zbyt mala! Uzupelnij ja do minimum 45 imion!");
	}


    //Przydzielanie królikom parametrów
    kroliki krolik[ilekrolikow];
    int tab[ilekrolikow];

    for (int k = 0; k < ilekrolikow; k++)
    {
        bool powtorka = 1;

        while (powtorka)
        {
            tab[k] = 1 + (rand() % ileimion);
            powtorka = 0;

            for (int l = 0; l < k; l++)
            {

                if (tab[l] == tab[k])
                {
                   powtorka = 1;
                }

            }

        }

        krolik[k].numer = k + 1;
        krolik[k].imie = nadajimie (tab[k]);
        krolik[k].wilk = 0;
        krolik[k].zywy = 1;
        krolik[k].izolatka = 0;
        krolik[k].stado = pierwsze;
        krolik[k].oznaczony = 0;
        krolik[k].widoczny = 1;

    }


    int IleWilkow = ( ilekrolikow / 7 ) + ( rand() % (ilekrolikow / 10) );

    for (int k = 0; k < IleWilkow; k++)
    {

        int liczba = rand();

        int LosujWilka = (liczba * 37) % ilekrolikow;
        krolik[LosujWilka].wilk = 1;
    }

    gra(ilekrolikow, ImieGracza, krolik, IleWilkow);

}




//funkcja licz¹ca iloœæ krolikow w stadzie
int LiczKroliki(int KrolikowOgolem, kroliki *krolik, int ktore)
{
    int wynik = 0;


	if (ktore == 0)
    {

		for (int k = 0; k < KrolikowOgolem; k++)
        {

            if (krolik[k].zywy)
            {
                wynik++;
            }

        }

        return wynik;
    }

	if (ktore == 1)
	{

		for (int k = 0; k < KrolikowOgolem; k++)
		{

			if (krolik[k].zywy && !krolik[k].izolatka && krolik[k].stado == pierwsze)
			{
				wynik++;
			}

		}

    return wynik;
	}

	if (ktore == 2)
	{

		for (int k = 0; k < KrolikowOgolem; k++)
		{

			if (krolik[k].zywy && !krolik[k].izolatka && krolik[k].stado == drugie)
			{
				wynik++;
			}

		}

		return wynik;

	}





	if (ktore == 10)
	{

		for (int k = 0; k < KrolikowOgolem; k++)
		{

			if (krolik[k].zywy && krolik[k].wilk)
			{
				wynik++;
			}

		}
		return wynik;

    }

   	if (ktore == 11)
	{

		for (int k = 0; k < KrolikowOgolem; k++)
		{

			if (krolik[k].zywy && !krolik[k].izolatka && krolik[k].stado == pierwsze && krolik[k].wilk)
			{
				wynik++;
			}

		}

    return wynik;
	}

	if (ktore == 12)
	{

		for (int k = 0; k < KrolikowOgolem; k++)
		{

			if (krolik[k].zywy && !krolik[k].izolatka && krolik[k].stado == drugie && krolik[k].wilk)
			{
				wynik++;
			}

		}

		return wynik;

	}





	if (ktore == 20)
	{

		for (int k = 0; k < KrolikowOgolem; k++)
		{

			if (krolik[k].widoczny)
			{
				wynik++;
			}

		}
		return wynik;

    }

   	if (ktore == 21)
	{

		for (int k = 0; k < KrolikowOgolem; k++)
		{

			if (krolik[k].widoczny && krolik[k].stado == pierwsze)
			{
				wynik++;
			}

		}

    return wynik;
	}

	if (ktore == 22)
	{

		for (int k = 0; k < KrolikowOgolem; k++)
		{

			if (krolik[k].widoczny && krolik[k].stado == drugie)
			{
				wynik++;
			}

		}

		return wynik;

	}

}




// wyswitla obecny stan stada
void StanStada (int KrolikowOgolem, kroliki *krolik, int dzien, int ZostaloRuchow, int izolatka)
{

    int StadoI = LiczKroliki(KrolikowOgolem, krolik, 1);
    int StadoII = LiczKroliki(KrolikowOgolem, krolik, 2);
    int KrolikowWidocznych = LiczKroliki(KrolikowOgolem, krolik, 20);
    int KrolikowWidocznychI = LiczKroliki(KrolikowOgolem, krolik, 21);
	int KrolikowWidocznychII = LiczKroliki(KrolikowOgolem, krolik, 22);
	int WilkowZostalo = LiczKroliki(KrolikowOgolem, krolik, 10);


    system("cls");
    cout << "DZIEN " << dzien;

    gotoxy(74,1);
    cout << "RUCHY " << ZostaloRuchow;
    gotoxy(74,2);
	cout << "WILKI " << WilkowZostalo;

    bool malokrolikow = 0;
    if (KrolikowWidocznych <= 21)
    {
        malokrolikow = 1;
    }

    int granica;

    if (malokrolikow)
    {
        granica = 19;
    }

    else
    {
            granica = 20;
    }


    // wypisywanie pierwszego stada

    int s = 0;
    int x = 5;
    int y = 5;


    if (KrolikowWidocznychI > 0)
    {
        gotoxy(x,3);
        cout << "Stado I (" << StadoI << ")";
    }

    while ( s < KrolikowOgolem)
    {

        if (y >= granica)
        {
            y = 5;
            x = x + 19;
        }

        gotoxy(x,y);

        if (krolik[s].stado == pierwsze)
        {

            if (krolik[s].widoczny)
        	{
		        string przerwa;

        		if (krolik[s].numer < 10)
		        {
        			przerwa = "  ";
	        	}

		        else
        		{
		        	przerwa = " ";
		        }


		        if (krolik[s].zywy)
		        {

                    if (krolik[s].oznaczony)
			        {
                        color(zolty);
		        	}

                    cout << "[" << krolik[s].numer << "]" << przerwa << krolik[s].imie;

			        color(szary);

//		        	if (krolik[s].wilk)
//			        {
//                        cout << " [W]";
//		        	}

		        }

		        else
		        {
                    color (czerwony);
			        cout << "[" << krolik[s].numer << "]" << przerwa << krolik[s].imie;
		            color (szary);
                }

                y++;

                if (malokrolikow)
                {
                    y++;
                }

            }

        }

        s++;
    }


    //linia rozdzielaj¹ca

    if (KrolikowWidocznychI > 0 && KrolikowWidocznychII > 0)
    {
        if (y != 5)
        {
            x = x + 15;
        }

        for(int y = 5; y < 20; y++)
        {
            gotoxy(x,y);
            cout << "|";
        }
    }

    //wypisywanie drugiego stada

    x = x + 5;
    y = 5;
    s = 0;

    if (StadoII > 0)
    {
        gotoxy(x,3);
        cout << "Stado II (" << StadoII << ")";
    }

    while ( s < KrolikowOgolem)
    {

        if (y >= granica)
        {
            y = 5;
            x = x + 19;
        }

        gotoxy(x,y);

        if (krolik[s].stado == drugie)
        {

            if (krolik[s].widoczny)
        	{

                string przerwa;

        		if (krolik[s].numer < 10)
		        {
        			przerwa = "  ";
	        	}

		        else
        		{
		        	przerwa = " ";
		        }

		        		        if (krolik[s].zywy)
		        {

                    if (krolik[s].oznaczony)
			        {
                        color(zolty);
		        	}

                    cout << "[" << krolik[s].numer << "]" << przerwa << krolik[s].imie;

			        color(szary);

//		        	if (krolik[s].wilk)
//			        {
//                        cout << " [W]";
//		        	}

		        }

		        else
		        {
			        color (czerwony);
			        cout << "[" << krolik[s].numer << "]" << przerwa << krolik[s].imie;
		            color (szary);
		        }

                y++;

                if (malokrolikow)
                {
                    y++;
                }

            }

        }

        s++;
    }


    //rysowanie izolatki
    gotoxy(55,21);
    cout << " __IZOLATKA____________";
    gotoxy(55,22);
    cout << "|                      |";
    gotoxy(55,23);
    cout << "|                      |";
    gotoxy(55,24);
    cout << "|______________________|";


    gotoxy(57,23);
    if (izolatka == 0)
    {
        cout << "       Pusto";
    }

    else
    {
        if (krolik[izolatka - 1].zywy)
        {

            if (krolik[izolatka - 1].oznaczony)
			{
			    color(zolty);
            }

            cout << "[" << krolik[izolatka - 1].numer << "]" << " " << krolik[izolatka - 1].imie;

		    color(szary);

//      	    if (krolik[izolatka - 1].wilk)
//			{
//                  cout << " [W]";
//            }

        }

		else
		{
		    color (czerwony);
            cout << "[" << krolik[izolatka - 1].numer << "] " << krolik[izolatka - 1].imie;
		    color (szary);
        }

    }


    //rysowanie linii komend
    gotoxy(1,21);
    cout << " __LINIA_KOMEND_____________________________________";
    gotoxy(1,22);
    cout << "|                                                   |";
    gotoxy(1,23);
    cout << "|                                                   |";
    gotoxy(1,24);
    cout << "|___________________________________________________|";


}






//funkcja zwraca indeks kandydata do zagryzienia, lub -1, jeœli ma ju¿ czego jeœæ
int zagryz (int KrolikowOgolem, int KtoreStado, kroliki *krolik)
{
    int stado;
    int wilki;

	if (KtoreStado == 1)
	{
		stado = LiczKroliki (KrolikowOgolem, krolik, 1);
		wilki = LiczKroliki (KrolikowOgolem, krolik, 11);
	}

	if (KtoreStado == 2)
	{
		stado = LiczKroliki (KrolikowOgolem, krolik, 2);
		wilki = LiczKroliki (KrolikowOgolem, krolik, 12);
	}

	if ((stado - wilki) > 0)
	{

        int k = rand() % KrolikowOgolem;

		if (KtoreStado == 1)
		{

            while (!krolik[k].zywy || krolik[k].wilk || krolik[k].izolatka || krolik[k].stado == drugie)
			{
				k = rand() % KrolikowOgolem;

            }
		}

		if (KtoreStado == 2)
		{

            while (!krolik[k].zywy || krolik[k].wilk || krolik[k].izolatka || krolik[k].stado == pierwsze)
			{
				k = rand() % KrolikowOgolem;
			}

		}

		return k;

	}

	else
	{
		return -5;
	}

}




// Wyswietla informacje o bledzie
void BladKomendy(string blad)
{
    gotoxy(1,23);
    cout << "|                                                   |";
    gotoxy ((53 - blad.length()) / 2 ,23);
    cout << blad;
    Sleep (blad.length() * 40);
   	gotoxy(1,23);
    cout << "|                                                   |";

}




//Sprawdza wartosc parametru pod wzglêdem poprawnoœci jak i zakresu
bool SprawdzWartosc(int wartosc, int zakres, kroliki *krolik)
{

    string blad;

    if (wartosc < 1 || wartosc > zakres)
    {
        blad = "Nieprawidlowa wartosc!";
        BladKomendy(blad);
        return 0;
    }

    else
    {

        if (!krolik[wartosc - 1].zywy)
        {
            blad = "Niedozwolony ruch!";
            BladKomendy(blad);
            return 0;
        }

    }

    return 1;
}






// sprawdzanie, czy w stadzie jest dostatecznie du¿o królików
// opcja 0 - za malo krolikow by przeniesc; opcja 1 - stado sie rozpada
void KrolikiUciekaja (kroliki *krolik, int KrolikowOgolem, bool opcja)
{

	string jakiblad;

	if(!opcja)
	{
		jakiblad = "W stadzie musi byc minimum piec krolikow!";
	}

	else
	{
		jakiblad = "Samotnosc przeraza kroliki...";
	}

	BladKomendy(jakiblad);

	for (int s = 0; s < KrolikowOgolem; s++)
	{

		if (krolik[s].stado == drugie)
		{
			krolik[s].stado = pierwsze;
		}

	}

}






// g³ówny ekran gry
void gra (int IleKrolikow, string ImieGracza, kroliki *krolik, int IleWilkow)
{
    int dzien = 0;
    int ruchy = 0;

    int KrolikowOgolem = IleKrolikow;
    int WilkowOgolem = IleWilkow;

    int KrolikowZostalo = LiczKroliki(KrolikowOgolem, krolik, 0);
    int WilkowZostalo = LiczKroliki(KrolikowOgolem, krolik, 10);

    int StadoI = LiczKroliki(KrolikowOgolem, krolik, 1);
    int StadoII = LiczKroliki(KrolikowOgolem, krolik, 2);

    int WilkiI = LiczKroliki(KrolikowOgolem, krolik, 11);
    int WilkiII = LiczKroliki(KrolikowOgolem, krolik, 12);


    bool porazka = 0;
    bool wygrana = 0;

    int izolatka = 0;


    while (!porazka && !wygrana)
    {

        int ZostaloRuchow = 5;
	    dzien++;

        //obs³uga linii komend
        while (ZostaloRuchow > 0)
        {

            bool poprawnie = 0;
			StanStada (KrolikowOgolem, krolik, dzien, ZostaloRuchow, izolatka);

			if ( ((StadoI < 5 && StadoI > 0) || (StadoII < 5 && StadoII > 0)) && (KrolikowZostalo > 5) )
			{
                KrolikiUciekaja (krolik, KrolikowOgolem, 1);
			    StanStada (KrolikowOgolem, krolik, dzien, ZostaloRuchow, izolatka);
                StadoI = LiczKroliki(KrolikowOgolem, krolik, 1);
                StadoII = LiczKroliki(KrolikowOgolem, krolik, 2);
			}


            while (!poprawnie)
            {

                char komenda = 0;
                char parametr1[25];
                int wartosc1 = 0;

                char YesNo;

                char ZmiennaCzytajaca[2][5] = {32};
                int dolnagranica = 0;
                int gornagranica = 0;
                int IleWartosci;
                bool czytaj = 0;

				int zakres;

				int StadoIprzed = 0;
				int StadoIIprzed = 0;

                gotoxy(1,23);
                cout << "|                                                   |";
                buforclr();
                gotoxy (4,23);
                komenda = getch();


                switch (komenda)
                {

                    case 'k' : case 'K':                                        // kill

                        gotoxy (4,23);
                        cout << "Kill rabbit # ";
                        cin.sync();
						cin >> parametr1;
                        wartosc1 = atoi (parametr1);

                        if (SprawdzWartosc(wartosc1, KrolikowOgolem, krolik))
                        {
                            poprawnie = 1;
                            ruchy++;
                            ZostaloRuchow--;

                            krolik[wartosc1 - 1].zywy = 0;
                            krolik[wartosc1 - 1].oznaczony = 0;

							if (krolik[wartosc1 - 1].wilk)
							{
								string tymczasowy = krolik[wartosc1 - 1].imie;
								tymczasowy = tymczasowy + " byl wilkiem!";
								BladKomendy(tymczasowy);
								Sleep(200);
							}

							else
							{
								string tymczasowy = krolik[wartosc1 - 1].imie;
								tymczasowy = tymczasowy + " byl niewinny!";
								BladKomendy(tymczasowy);
								Sleep(200);
							}


                            KrolikowZostalo = LiczKroliki(KrolikowOgolem, krolik, 0);
                            WilkowZostalo = LiczKroliki(KrolikowOgolem, krolik, 10);
                            StadoI = LiczKroliki(KrolikowOgolem, krolik, 1);
                            StadoII = LiczKroliki(KrolikowOgolem, krolik, 2);
                            WilkiI = LiczKroliki(KrolikowOgolem, krolik, 11);
                            WilkiII = LiczKroliki(KrolikowOgolem, krolik, 12);

							StanStada (KrolikowOgolem, krolik, dzien, ZostaloRuchow, izolatka);

							if (WilkowZostalo == 0)
							{
								ZostaloRuchow = 0;
							}

						}

                        break;






                    case 'i' : case 'I':                                        // isolate

                        gotoxy (4,23);
                        cout << "Isolate rabbit # ";
                        cin.sync();
						cin >> parametr1;
                        wartosc1 = atoi (parametr1);

                        if (SprawdzWartosc(wartosc1, KrolikowOgolem, krolik))
                        {

                            if (izolatka == 0)
                            {
                                poprawnie = 1;
                                ruchy++;
                                ZostaloRuchow--;

                                krolik[wartosc1 - 1].izolatka = 1;
                                izolatka = wartosc1;

                                krolik[izolatka - 1].widoczny = 0;

                                KrolikowZostalo = LiczKroliki(KrolikowOgolem, krolik, 0);
                                WilkowZostalo = LiczKroliki(KrolikowOgolem, krolik, 10);
                                StadoI = LiczKroliki(KrolikowOgolem, krolik, 1);
                                StadoII = LiczKroliki(KrolikowOgolem, krolik, 2);
                                WilkiI = LiczKroliki(KrolikowOgolem, krolik, 11);
                                WilkiII = LiczKroliki(KrolikowOgolem, krolik, 12);

								StanStada (KrolikowOgolem, krolik, dzien, ZostaloRuchow, izolatka);

                            }

                            else
                            {
                                BladKomendy("Izolatka zajeta!");
                            }

                        }

                        break;






                    case 'f' : case 'F':                                        // free

                        YesNo = 0;

                        if (izolatka != 0)
                        {

                        while (YesNo != 'y' && YesNo != 'Y' &&                  // 27 = "escape"
                               YesNo != 'n' && YesNo != 'N' &&                  // 8  = "backspace"
                               YesNo != 27  && YesNo !=  8  &&                  // 13 = "enter"
                               YesNo != 13)
                            {
                                gotoxy(1,23);
					    		cout << "|                                                   |";
				    			gotoxy (4,23);
			    				cout << "Free rabbit " << krolik[izolatka - 1].imie << "? (y/n) " ;
		    					YesNo = 0;
	    						buforclr();
    							YesNo = getch();

				    			if (YesNo == 'y' || YesNo == 'Y' || YesNo == 13)
			    				{
		    						poprawnie = 1;
	    							ruchy++;
    								ZostaloRuchow--;

                                    krolik[izolatka - 1].izolatka = 0;

						    		krolik[izolatka - 1].widoczny = 1;


									//aktualizacja wartosci
                                    KrolikowZostalo = LiczKroliki(KrolikowOgolem, krolik, 0);
                                    WilkowZostalo = LiczKroliki(KrolikowOgolem, krolik, 10);
                                    StadoI = LiczKroliki(KrolikowOgolem, krolik, 1);
                                    StadoII = LiczKroliki(KrolikowOgolem, krolik, 2);
                                    WilkiI = LiczKroliki(KrolikowOgolem, krolik, 11);
                                    WilkiII = LiczKroliki(KrolikowOgolem, krolik, 12);

									izolatka = 0;
                                }

                            }

                        }

                        else
                        {
                            BladKomendy("Izolatka jest pusta!");
                        }


                        break;






                    case 'b' : case 'B':                                        // blame

						gotoxy (4,23);
						cout << "Blame rabbit # ";
						cin.sync();
						cin.getline (parametr1,25);

						// Przerabianie stringa na jedn¹ lub dwie wartoœci integer
						IleWartosci = 0;
						czytaj = 0;

						for (int k = 0; k <= strlen(parametr1); k++)
						{
							int l;

							if (parametr1[k] == 32)
							{
								czytaj = 0;
							}

							else
							{

								if (!czytaj)
								{
									l = 0;
									IleWartosci++;
									czytaj = 1;
								}

								ZmiennaCzytajaca[IleWartosci - 1][l] = parametr1[k];
								l++;
							}

						}

						dolnagranica = atoi(ZmiennaCzytajaca[0]);
						gornagranica = atoi(ZmiennaCzytajaca[1]);

						zakres = gornagranica - dolnagranica + 1;


						// TUTAJ JU¯ MAM LICZBÊ WARTOŒCI I WARTOŒCI W ZMIENNYCH
						if (IleWartosci >= 1 && IleWartosci <= 2)
						{

							// Jeœli po blame podano jeden parametr
							if (IleWartosci == 1)
							{

								if (dolnagranica >= 1 && dolnagranica <= KrolikowOgolem)
								{

									if (krolik[dolnagranica - 1].zywy)
									{

										if (krolik[dolnagranica - 1].oznaczony)
										{
											BladKomendy("Krolik jest juz oznaczony!");
										}

										else
										{
											krolik[dolnagranica - 1].oznaczony = 1;
											poprawnie = 1;
										}

									}

									else
									{
										BladKomendy("Nie mozna oznaczyc martwego krolika!");
									}

								}

								else
								{
									BladKomendy("Nieprawidlowa wartosc!");
								}

							}



							// Jeœli po blame podano dwa parametry
							else
							{

								if (dolnagranica >= 1 &&
									dolnagranica <= gornagranica &&
									gornagranica <= KrolikowOgolem)
								{

									int LiczMartweKroliki = 0;
									int LiczOznaczoneKroliki = 0;

									for (int k = (dolnagranica - 1);  k <= (gornagranica - 1); k++)
									{

										if (krolik[k].oznaczony)
										{
											LiczOznaczoneKroliki++;
										}

										if (krolik[k].zywy)
										{
											krolik[k].oznaczony = 1;
										}

										else
										{
											LiczMartweKroliki++;
										}

									}

									poprawnie = 1;

									if (LiczMartweKroliki == zakres)
									{
										BladKomendy("Te kroliki sa juz martwe!");
									}

									if (LiczOznaczoneKroliki == zakres)
									{
										BladKomendy("Te kroliki sa juz oznaczone!");
									}

									if ( (LiczMartweKroliki > 0) && (LiczOznaczoneKroliki > 0) &&
										 (LiczMartweKroliki + LiczOznaczoneKroliki == zakres ) )
									{
										BladKomendy("Ten rozkaz niczego nie zmieni!");
									}


								}

								else
								{
									BladKomendy("Nieprawidlowa wartosc!");
								}

							}

						}

						break;






                    case 'r' : case 'R':                                        // remove

                        YesNo = 0;

                        while (YesNo != 'y' && YesNo != 'Y' &&                  // 27 = "escape"
                               YesNo != 'n' && YesNo != 'N' &&                  // 8  = "backspace"
                               YesNo != 27  && YesNo !=  8  &&                  // 13 = "enter"
                               YesNo != 13)
                        {
                            gotoxy(1,23);
                            cout << "|                                                   |";
                            gotoxy (4,23);
                            cout << "Remove dead bodies? (y/n) ";
                            buforclr();
                            YesNo = getch();

                            if (YesNo == 'y' || YesNo == 'Y' || YesNo == 13)
                            {
                                poprawnie = 1;

                                for (int k = 0; k < KrolikowOgolem; k++)
                                {

                                    if (!krolik[k].zywy)
                                    {
                                        krolik[k].widoczny = 0;
                                    }

                                }

                                if (!krolik[izolatka - 1].zywy)
                                {
                                    krolik[izolatka - 1].izolatka = 0;
                                    izolatka = 0;
                                }

                            }

                        }


                        break;






                    case 'c' : case 'C':                                        // clear

						gotoxy (4,23);
						cout << "Clear rabbit # ";
						cin.sync();
						cin.getline (parametr1,25);

						// Przerabianie stringa na jedn¹ lub dwie wartoœci integer
						IleWartosci = 0;
						czytaj = 0;

						for (int k = 0; k <= strlen(parametr1); k++)
						{
							int l;

							if (parametr1[k] == 32)
							{
								czytaj = 0;
							}

							else
							{

								if (!czytaj)
								{
									l = 0;
									IleWartosci++;
									czytaj = 1;
								}

								ZmiennaCzytajaca[IleWartosci - 1][l] = parametr1[k];
								l++;
							}

						}

						dolnagranica = atoi(ZmiennaCzytajaca[0]);
						gornagranica = atoi(ZmiennaCzytajaca[1]);

						zakres = gornagranica - dolnagranica + 1;


						// TUTAJ JU¯ MAM LICZBÊ WARTOŒCI I WARTOŒCI W ZMIENNYCH
						if (IleWartosci >= 1 && IleWartosci <= 2)
						{

							// Jeœli po clear podano jeden parametr
							if (IleWartosci == 1)
							{

								if (dolnagranica >= 1 && dolnagranica <= KrolikowOgolem)
								{

									if (krolik[dolnagranica - 1].zywy)
									{

										if (!krolik[dolnagranica - 1].oznaczony)
										{
											BladKomendy("Ten krolik nie jest oznaczony!");
										}

										else
										{
											krolik[dolnagranica - 1].oznaczony = 0;
											poprawnie = 1;
										}

									}

									else
									{
										BladKomendy("Ten krolik jest martwy!");
									}

								}

								else
								{
									BladKomendy("Nieprawidlowa wartosc!");
								}

							}



							// Jeœli po clear podano dwa parametry
							else
							{

								if (dolnagranica >= 1 &&
									dolnagranica <= gornagranica &&
									gornagranica <= KrolikowOgolem)
								{

									int LiczMartweKroliki = 0;
									int LiczNieoznaczoneKroliki = 0;

									for (int k = (dolnagranica - 1);  k <= (gornagranica - 1); k++)
									{

										if (!krolik[k].oznaczony)
										{
											LiczNieoznaczoneKroliki++;
										}

										if (krolik[k].zywy)
										{
											krolik[k].oznaczony = 0;
										}

										else
										{
											LiczMartweKroliki++;
										}

									}

									poprawnie = 1;

									if (LiczMartweKroliki == zakres)
									{
										BladKomendy("Te kroliki sa juz martwe!");
									}

									if (LiczNieoznaczoneKroliki == zakres)
									{
										BladKomendy("Te kroliki nie zostaly oznaczone!");
									}

									if ( (LiczMartweKroliki > 0) && (LiczNieoznaczoneKroliki > 0) &&
										 (LiczMartweKroliki + LiczNieoznaczoneKroliki == zakres ) )
									{
										BladKomendy("Ten rozkaz niczego nie zmieni!");
									}


								}

								else
								{
									BladKomendy("Nieprawidlowa wartosc!");
								}

							}

						}

						break;






                    case 'm' : case 'M':                                        // move

						gotoxy (4,23);
						cout << "Move rabbit # ";

						cin.sync();
						cin.getline (parametr1,25);

						// Przerabianie stringa na jedn¹ lub dwie wartoœci integer
						IleWartosci = 0;
						czytaj = 0;

						for (int k = 0; k <= strlen(parametr1); k++)
						{
							int l;

							if (parametr1[k] == 32)
							{
								czytaj = 0;
							}

							else
							{

                                if (!czytaj)
                                {
                                    l = 0;
                                    IleWartosci++;
                                    czytaj = 1;
                                }

                                ZmiennaCzytajaca[IleWartosci - 1][l] = parametr1[k];
                                l++;
                            }

                        }

                        dolnagranica = atoi(ZmiennaCzytajaca[0]);
                        gornagranica = atoi(ZmiennaCzytajaca[1]);


                        // TUTAJ JU¯ MAM LICZBÊ WARTOŒCI I WARTOŒCI W ZMIENNYCH

						StadoIprzed = LiczKroliki(KrolikowOgolem, krolik, 1);
						StadoIIprzed = LiczKroliki(KrolikowOgolem, krolik, 2);

						zakres = gornagranica - dolnagranica + 1;


                        if (IleWartosci >= 1 && IleWartosci <= 2)
                        {

							// Jeœli po move podano jeden parametr
                            if (IleWartosci == 1)
                            {

                                if (dolnagranica >= 1 && dolnagranica <= KrolikowOgolem)
                                {

									if (krolik[dolnagranica - 1].zywy)
									{

										if (krolik[dolnagranica - 1].stado == pierwsze)
										{
											krolik[dolnagranica - 1].stado = drugie;
										}

										else
										{
											krolik[dolnagranica - 1].stado = pierwsze;
										}

										// ponowne obliczanie parametrow stada
										StadoI = LiczKroliki(KrolikowOgolem, krolik, 1);
										StadoII = LiczKroliki(KrolikowOgolem, krolik, 2);
										WilkiI = LiczKroliki(KrolikowOgolem, krolik, 11);
										WilkiII = LiczKroliki(KrolikowOgolem, krolik, 12);


										//kwestia wielkoœci nowego stada
										if ( ( (StadoI < 5 && StadoI > 0) || (StadoII < 5 && StadoII > 0) ) && (KrolikowZostalo > 5) )
										{

											if (StadoIprzed == 0 || StadoIIprzed == 0)
											{
												KrolikiUciekaja (krolik, KrolikowOgolem, 0);
											}

											else
											{
												poprawnie = 1;
												ruchy++;
												ZostaloRuchow--;
												StanStada (KrolikowOgolem, krolik, dzien, ZostaloRuchow, izolatka);
												KrolikiUciekaja (krolik, KrolikowOgolem, 1);
											}

											StanStada (KrolikowOgolem, krolik, dzien, ZostaloRuchow, izolatka);
											StadoI = LiczKroliki(KrolikowOgolem, krolik, 1);
											StadoII = LiczKroliki(KrolikowOgolem, krolik, 2);

										}

										else
										{
											poprawnie = 1;
											ruchy++;
											ZostaloRuchow--;
										}

									}

									else
									{

										if (krolik[dolnagranica - 1].widoczny)
										{
											BladKomendy("Nie mozna przeniesc martwego krolika!");
										}

										else
										{
											BladKomendy("Nieprawidlowa wartosc!");
										}

									}

								}

								else
								{
									BladKomendy("Nieprawidlowa wartosc!");
								}

                            }



                            // Jeœli po move podano dwa parametry
                            else
                            {

                                if (dolnagranica >= 1 &&
                                    dolnagranica <= gornagranica &&
                                    gornagranica <= KrolikowOgolem)
                                {

									int LiczMartweKroliki = 0;

									for (int k = (dolnagranica - 1);  k <= (gornagranica - 1); k++)
                                    {

										if (!krolik[k].zywy)
										{
											LiczMartweKroliki++;
										}

									}

									if(LiczMartweKroliki != zakres)
									{

										for (int k = (dolnagranica - 1);  k <= (gornagranica - 1); k++)
										{

											if (krolik[k].stado == pierwsze && krolik[k].zywy)
											{
												krolik[k].stado = drugie;
											}

											else
											{

												if (krolik[k].stado == drugie && krolik[k].zywy)
												{
													krolik[k].stado = pierwsze;
												}

											}

										}

										// ponowne obliczanie parametrow stada
										StadoI = LiczKroliki(KrolikowOgolem, krolik, 1);
										StadoII = LiczKroliki(KrolikowOgolem, krolik, 2);
										WilkiI = LiczKroliki(KrolikowOgolem, krolik, 11);
										WilkiII = LiczKroliki(KrolikowOgolem, krolik, 12);


										//kwestia wielkosci nowego stadka
										if ( ((StadoI < 5 && StadoI > 0) || (StadoII < 5 && StadoII > 0)) && (KrolikowZostalo > 5) )
										{

											if (StadoIprzed == 0 || StadoIIprzed == 0)
											{
											KrolikiUciekaja (krolik, KrolikowOgolem, 0);
											}

											else
											{
												poprawnie = 1;
												ruchy++;
												ZostaloRuchow--;
												StanStada (KrolikowOgolem, krolik, dzien, ZostaloRuchow, izolatka);
												KrolikiUciekaja (krolik, KrolikowOgolem, 1);
											}

											StanStada (KrolikowOgolem, krolik, dzien, ZostaloRuchow, izolatka);
											StadoI = LiczKroliki(KrolikowOgolem, krolik, 1);
											StadoII = LiczKroliki(KrolikowOgolem, krolik, 2);
										}

										else
										{
											poprawnie = 1;
											ruchy++;
											ZostaloRuchow--;
										}

									}

									else
									{
										BladKomendy("Nie przenos martwych krolikow!");
									}

								}

                                else
                                {
                                    BladKomendy("Nieprawidlowa wartosc!");
                                }

                            }

                        }

                        else
                        {
                            BladKomendy("Nieprawidlowa wartosc!");
                        }

                        break;






                    case 'e' : case 'E':                                        // end

                        YesNo = 0;

                        while (YesNo != 'y' && YesNo != 'Y' &&                  // 27 = "escape"
                               YesNo != 'n' && YesNo != 'N' &&                  // 8  = "backspace"
                               YesNo != 27  && YesNo !=  8  &&                  // 13 = "enter"
                               YesNo != 13)
                        {
                            gotoxy(1,23);
                            cout << "|                                                   |";
                            gotoxy (4,23);
                            cout << "End turn? (y/n) ";;

                            buforclr();
                            YesNo = getch();

                            if (YesNo == 'y' || YesNo == 'Y' || YesNo == 13)
                            {
                                poprawnie = 1;
                                ZostaloRuchow = 0;
                            }

                        }


                        break;






                    case 27 :													// zakoncz gre

                        koniec();
						StanStada (KrolikowOgolem, krolik, dzien, ZostaloRuchow, izolatka);

						break;




				}

				if (ZostaloRuchow == 0)
				{
					StanStada (KrolikowOgolem, krolik, dzien, ZostaloRuchow, izolatka);
				}

			}


			//komenda zosta³a poprawnie wykonana

			if( ((StadoI < 5 && StadoI > 0) || (StadoII < 5 && StadoII > 0)) && (KrolikowZostalo > 5) )
			{
                KrolikiUciekaja (krolik, KrolikowOgolem, 1);
			    StanStada (KrolikowOgolem, krolik, dzien, ZostaloRuchow, izolatka);
                StadoI = LiczKroliki(KrolikowOgolem, krolik, 1);
                StadoII = LiczKroliki(KrolikowOgolem, krolik, 2);
			}


        }

        //tu wstawiæ co siê dzieje, kiedy koñcz¹ siê ruchy

		// Wyznaczanie krolikow, ktore zgina tej nocy


		//aktualizacja wartosci
		KrolikowZostalo = LiczKroliki(KrolikowOgolem, krolik, 0);
		WilkowZostalo = LiczKroliki(KrolikowOgolem, krolik, 10);
		StadoI = LiczKroliki(KrolikowOgolem, krolik, 1);
		StadoII = LiczKroliki(KrolikowOgolem, krolik, 2);
		WilkiI = LiczKroliki(KrolikowOgolem, krolik, 11);
		WilkiII = LiczKroliki(KrolikowOgolem, krolik, 12);


        StanStada (KrolikowOgolem, krolik, dzien, ZostaloRuchow, izolatka);



		//tworzenie listy krolikow skazanych na smierc




        int AktywnychWilkow = WilkiI + WilkiII;

		int ofiary[AktywnychWilkow];


		for (int k = 0; k < AktywnychWilkow; k++)
		{
            ofiary[k] = -5;
        }


		int pamietajwynik = 0;

		int sprawdz;

		for (int k = 0; k < WilkiI; k++)
		{
			sprawdz = zagryz (KrolikowOgolem, 1, krolik);

			if (sprawdz >= 0)
			{
				krolik[sprawdz].zywy = 0;
				krolik[sprawdz].oznaczony = 0;
				ofiary[pamietajwynik] = sprawdz;
				pamietajwynik++;
			}


		}


		for (int k = 0; k < WilkiII; k++)
		{
            sprawdz = zagryz (KrolikowOgolem, 2, krolik);

			if (sprawdz >= 0)
			{
				krolik[sprawdz].zywy = 0;
				krolik[sprawdz].oznaczony = 0;
				ofiary[pamietajwynik] = sprawdz;
				pamietajwynik++;
			}
        }


		NocnyRaport(KrolikowOgolem, ofiary, krolik);

		KrolikowZostalo = LiczKroliki(KrolikowOgolem, krolik, 0);
        WilkowZostalo = LiczKroliki(KrolikowOgolem, krolik, 10);
        StadoI = LiczKroliki(KrolikowOgolem, krolik, 1);
        StadoII = LiczKroliki(KrolikowOgolem, krolik, 2);
        WilkiI = LiczKroliki(KrolikowOgolem, krolik, 11);
        WilkiII = LiczKroliki(KrolikowOgolem, krolik, 12);



        if (KrolikowOgolem - KrolikowZostalo > (KrolikowOgolem / 2) )
        {
            porazka = 1;
        }

		if (WilkowZostalo == 0)
        {
            wygrana = 1;
        }


    }
    //tu wstawiæ to co siê dzieje w razie zakonczenia rozgrywki
    // z rozró¿nieniem na wygran¹ i przegran¹

    int PrzekazWynik;

    if (wygrana || porazka)
    {

        string wynik;

        if (wygrana && porazka)
        {
            wynik = "REMIS";
            PrzekazWynik = 2;
            wpiszwranking(KrolikowOgolem, KrolikowZostalo, WilkowOgolem, dzien, ruchy, ImieGracza, 0);
        }

        if (wygrana && !porazka)
        {
            wynik = "ZWYCIESTWO!";
            PrzekazWynik = 1;
            wpiszwranking(KrolikowOgolem, KrolikowZostalo, WilkowOgolem, dzien, ruchy, ImieGracza, 1);
        }

        if (!wygrana && porazka)
        {
            wynik = "PORAZKA...";
            PrzekazWynik = 0;
        }

        zakonczenie (wynik);
        zdradzwynik(PrzekazWynik, ruchy, dzien, KrolikowOgolem, krolik);
		pokazranking();

    }


    Sleep(1000);

}






//Raport o zgonach w ciagu nocy
void NocnyRaport(int KrolikowOgolem, int *ofiary, kroliki *krolik)
{
	BladKomendy("Koniec ruchow. Zbliza sie wieczor...");
	system("cls");
    string napis = "MINELA NOC...";
    gotoxy (srodek (napis), 12);
    literuj(napis, 60, 1);
    Sleep(1000);

	gotoxy (5, 3);
	cout <<" __NOCNY_RAPORT__________________________________________________";

	for (int y = 4; y <= 22 ; y++)
	{
		gotoxy (5, y);
		cout <<"|                                                                |";
	}

	gotoxy (5, 23);
	cout <<"|________________________________________________________________|";


	int WilkiI = LiczKroliki(KrolikowOgolem, krolik, 11);
	int WilkiII = LiczKroliki(KrolikowOgolem, krolik, 12);
	int AktywnychWilkow = WilkiI + WilkiII;


	int ileofiar = 0;

	for (int k = 0; k < AktywnychWilkow; k++)
	{

		if (ofiary[k] >= 0)
		{
            ileofiar++;
        }

    }

	if (ileofiar == 0)
	{
		gotoxy (7, 5);
		cout << "Tej nocy nie zginal zaden krolik.";
	}

	else
	{
	    gotoxy (7, 5);
		cout << "Tej nocy zycie stracili:";

		int y = 8;

		for (int k = 0; k < AktywnychWilkow; k++)
		{

			if (ofiary[k] >= 0)
			{
				gotoxy (10, y);

				string przerwa;

				if (krolik[ofiary[k]].numer < 10)
		        {
        			przerwa = "  ";
	        	}

		        else
        		{
		        	przerwa = " ";
		        }

				if (krolik[ofiary[k]].stado == pierwsze)
				{
					cout << "[" << krolik[ofiary[k]].numer << "]" << przerwa << krolik[ofiary[k]].imie << " ze stada I";
				}

				else
				{
					cout << "[" << krolik[ofiary[k]].numer << "]" << przerwa << krolik[ofiary[k]].imie << " ze stada II";
				}

			}

            y++;

		}

	}
	gotoxy (52,25);
    cout << "nacisnij dowolny klawisz...";
    buforclr();
    getch();

}





//Napis koñcowy
void zakonczenie(string wynik)
{
    int dlugosc = wynik.length();

    int poczatek = ( 80 - wynik.length() ) / 2;

    char x,y;
    char znak;



    for (int l = 0; l < 50000; l++)
    {
        x = 1 + ( rand() % 80);
        y = 1 + ( rand() % 25);

        if (y == 25 && x == 80)
        {
            x = 79;
        }

        znak = 65 + (rand() % 26);
        gotoxy(x,y);


        if (l > 20000)
        {

            if (y >= 12 && y <= 14 &&
                x >= 32 &&
                x <= 47 )
            {
                znak = ' ';
            }

        }


        if (l > 30000)
        {

            if (y == 13 &&
                x >= poczatek &&
                x <= (poczatek + dlugosc) )
            {
                znak = wynik[x - poczatek];
            }

        }
        cout << znak;

    }

    int dzielnik = 7;

    int rosnij = 170;

    for (int l = 100; l <= 15000; l++)
    {
        x = 1 + ( rand() % 80);
        y = 1 + ( rand() % 25);

        if (y == 25 && x == 80)
        {
            x == 78;
        }

        znak = 65 + (rand() % 26);


        if (l % rosnij == 0 && dzielnik > 1)
        {
            dzielnik--;
            rosnij = 2 * rosnij;
        }


        if (l % dzielnik == 0)
        {
            znak = ' ';

        }

        gotoxy(x,y);
        cout << znak;


    }

    system("cls");


}




//kto by³ wilkiem, kto byl pszemkiem
void zdradzwynik(int wynik, int ruchy, int dni, int KrolikowOgolem, kroliki *krolik)
{

    gotoxy (5, 3);
	cout <<" __WYNIK_OGOLNY__________________________________________________________ ";

	for (int y = 4; y <= 23 ; y++)
	{
		gotoxy (5, y);
		cout <<"|                                                                        |";
	}

	gotoxy (5, 24);
	cout <<"|________________________________________________________________________|";



    if (wynik == 0)
    {
        gotoxy (7, 5);
        cout << "Niestety, zbyt wiele krolikow stracilo zycie...";
    }

    if (wynik == 1)
    {
        gotoxy (7, 5);
        cout << "Wszystkie wilki nie zyja. Zwyciezyles!";
    }

    if (wynik == 2)
    {
        gotoxy (7, 5);
        cout << "Zabiles wszystkie wilki.";
        gotoxy (7, 6);
        cout << "Niestety, zbyt wiele krolikow stracilo przy tym zycie...";
    }

    gotoxy(50, 3);
    cout << dni << "_DNI";

    gotoxy(60, 3);
    cout << ruchy << "_RUCHOW";

    int s = 0;
    int x = 10;
    int y = 7;

    while (s < KrolikowOgolem)
    {
        if (y == 22)
        {
            y = 7;
            x = x + 20;
        }


        gotoxy(x,y);

        string przerwa;

		if (krolik[s].numer < 10)
		{
            przerwa = "  ";
        }

		else
        {
		    przerwa = " ";
        }



        if (krolik[s].zywy)
        {
            cout << "[" << krolik[s].numer << "]" << przerwa << krolik[s].imie;
        }

        else
        {
            color (czerwony);
			cout << "[" << krolik[s].numer << "]" << przerwa << krolik[s].imie;
            color (szary);
        }


        if (krolik[s].wilk && krolik[s].zywy)
        {
			cout << " [wilk]";
        }

		if (krolik[s].wilk && !krolik[s].zywy)
        {
			color (czerwony);
			cout << " [wilk]";
			color (szary);
        }

        s++;
        y++;

    }

    gotoxy (52,25);
    cout << "nacisnij dowolny klawisz...";
    buforclr();
    getch();

}




//konwersja stringa do tablicy charów
void strtochar (string napis, char *tab)
{

	for (int k = 0; k < 6; k++)
    {
        tab[k] = 0;
    }

    for (int k = 0; k < 6; k++)
    {
		tab[k] = (char)napis[k];
    }

}






//zapisuje wynik do rankingu
void wpiszwranking(int KrolikowOgolem, int KrolikowZostalo, int WilkowOgolem, int dni, int ruchy, string ImieGracza, bool caly)
{

	system("cls");
	wyniki wynik[21];
    ifstream plik ("ranking.txt");

	int k = 0;

    cin.sync();

	if (plik)
    {
        string linijka;

		char tablica[6] = {0};

		int kontrolna = -1;

        while ( (getline (plik, linijka) ) && (k < 20) )
        {

			kontrolna++;

            if (kontrolna == 0)
            {
            strtochar (linijka, tablica);
			wynik[k].pozycja = atoi (tablica);
            }

		    if (kontrolna == 1)
            {
			wynik[k].imie = linijka;
            }

            if (kontrolna == 2)
            {
			strtochar (linijka, tablica);
			wynik[k].ilekrolikow = atoi (tablica);
            }

			if (kontrolna == 3)
            {
			strtochar (linijka, tablica);
			wynik[k].dni = atoi (tablica);
            }

			if (kontrolna == 4)
            {
			strtochar (linijka, tablica);
			wynik[k].ruchy = atoi (tablica);
            }

			if (kontrolna == 5)
            {
			strtochar (linijka, tablica);
			wynik[k].wynik = atof (tablica);
            }

            if (kontrolna == 6)
            {
			k++;
			kontrolna = -1;
            }

        }

	}

	else
	{
        fstream plik ("ranking.txt", ios::trunc | ios::out);
		plik.close();
	}

	plik.close();


	wyniki temp;

	int ilewynikow = k;

	wynik[ilewynikow].pozycja = k;
	wynik[ilewynikow].imie = ImieGracza;
	wynik[ilewynikow].ilekrolikow = KrolikowOgolem;
	wynik[ilewynikow].dni = dni;
	wynik[ilewynikow].ruchy = ruchy;
	wynik[ilewynikow].wynik = floor ( ( KrolikowOgolem * WilkowOgolem - ruchy - dni ) * ( KrolikowZostalo / (float)KrolikowOgolem * 100 ) );

    if (!caly)
    {
        wynik[ilewynikow].wynik = floor ( (wynik[ilewynikow].wynik) / 2);
    }


	bool poprawnie = 0;


	if (ilewynikow == 0)
	{
		fstream zapis ("ranking.txt", ios::trunc | ios::out);

		zapis << wynik[ilewynikow].imie << endl;
		zapis << wynik[ilewynikow].ilekrolikow << endl;
		zapis << wynik[ilewynikow].dni << endl;
		zapis << wynik[ilewynikow].ruchy << endl;
		zapis << wynik[ilewynikow].wynik << endl;
		zapis <<  endl;

		zapis.close();
	}

	else
	{

		while (!poprawnie  && k > 0)
		{

			if (wynik[k].wynik > wynik[k - 1].wynik)
			{
				temp = wynik[k];
				wynik[k] = wynik[k - 1];
				wynik[k - 1] = temp;
				k--;
			}

			else
			{
				poprawnie = 1;
			}

		}

		fstream zapis ("ranking.txt", ios::trunc | ios::out);


		for (int i = 0; i <= ilewynikow; i++)
		{
			wynik[i].pozycja = i + 1;
			zapis << wynik[i].pozycja << endl;
			zapis << wynik[i].imie << endl;
			zapis << wynik[i].ilekrolikow << endl;
			zapis << wynik[i].dni << endl;
			zapis << wynik[i].ruchy << endl;
			zapis << wynik[i].wynik << endl;
			zapis << endl;
		}

		zapis.close();

	}

}






int main(int argc, char *argv[])
{
    srand (time (NULL));
    welcome();
    menu();

    system("pause");
    return 0;
}

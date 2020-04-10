#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <fstream>
#include <stdio.h>
#include <ctype.h>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>

using namespace std;

struct Kontakt
{
    int id = 0;
    string imie = "", nazwisko = "", nrTelefonu = "", email = "", adresZamieszkania = "";
};

bool sprawdzCzyIstnieje(vector<Kontakt> &kontakty, int idDoZmiany );
int wczytajDaneZPlikuTekstowego(vector<Kontakt> &kontakty);
Kontakt pobierzDaneKontaktu(string daneKontaktuOddzielonePionowymiKreskami);
int utworzNowyKontakt( vector<Kontakt> &kontakty, int idOstatniegoKontaktu);
void wyswietlListeKontaktow ();
void wyswietlWybraneKontakty(vector<Kontakt> kontakty, int i);
void wyszukajKontaktPoImieniu(vector<Kontakt> &kontakty);
void wyszukajKontaktPoNazwisku(vector<Kontakt> &kontakty);
void edytujKontakt(vector<Kontakt> &kontakty);
int usunKontakt(vector<Kontakt> &kontakty, int idOstatniegoKontaktu);

int main()
{
    vector<Kontakt> kontakty;
    int idOstatniegoKontaktu = 0;

    char wybor;

    idOstatniegoKontaktu = wczytajDaneZPlikuTekstowego(kontakty);

    while(1)
    {
        system("cls");
        cout << "1. Dodaj nowy kontakt" << endl;
        cout << "2. Wyswietl po imieniu" << endl;
        cout << "3. Wyszukaj po nazwisku" << endl;
        cout << "4. Wyswietl wszystkie kontakty" << endl;
        cout << "5. Usun kontakt" << endl;
        cout << "6. Edytuj kontakt" << endl;
        cout << "9. Zakoncz program" << endl;
        cout << "Twoj wybor: " << endl;
        cin >> wybor;
        cout << endl << endl;

        if(wybor == '1')
        {
            idOstatniegoKontaktu = utworzNowyKontakt(kontakty, idOstatniegoKontaktu);
        }
        else if (wybor == '2')
        {
            wyszukajKontaktPoImieniu(kontakty);
        }
        else if (wybor == '3')
        {
            wyszukajKontaktPoNazwisku(kontakty);
        }
        else if (wybor == '4')
        {
            wyswietlListeKontaktow();
        }
        else if (wybor == '5')
        {
            idOstatniegoKontaktu = usunKontakt(kontakty, idOstatniegoKontaktu);
        }
        else if (wybor == '6')
        {
            edytujKontakt(kontakty);
        }

        else if (wybor == '9')
        {
            exit(0);
        }
    }

    return 0;
}

bool sprawdzCzyIstnieje(vector<Kontakt> &kontakty, int idDoZmiany )
{
    system("cls");

    bool istnieje = false;
    for (int i = 0; i < kontakty.size(); i++)
    {
        if(kontakty[i].id == idDoZmiany)
            istnieje = true;
    }

    return istnieje;
}

Kontakt pobierzDaneKontaktu(string daneKontaktuOddzielonePionowymiKreskami)
{
    Kontakt osoba;

    char znakDzielacy = '|';
    std::istringstream podzial(daneKontaktuOddzielonePionowymiKreskami);
    std::vector<std::string> podzieloneDaneKontaktu;
    for (std::string daneOsobno; std::getline(podzial, daneOsobno, znakDzielacy); podzieloneDaneKontaktu.push_back(daneOsobno));

    osoba.id = atoi(podzieloneDaneKontaktu[0].c_str());
    osoba.imie = podzieloneDaneKontaktu[1];
    osoba.nazwisko = podzieloneDaneKontaktu[2];
    osoba.nrTelefonu = podzieloneDaneKontaktu[3];
    osoba.email = podzieloneDaneKontaktu[4];
    osoba.adresZamieszkania = podzieloneDaneKontaktu[5];

    return osoba;
}

int wczytajDaneZPlikuTekstowego(vector<Kontakt> &kontakty)
{
    system("cls");
    string imie,nazwisko, nrTelefonu, email, adresZamieszkania;
    int iloscKontaktow = 0;


    Kontakt osoba;
    string daneKontaktuOddzielonePionowymiKreskami = "";

    fstream plik;
    plik.open ("ksiazka_adresowa.txt", ios::in );
    if(plik.good() == true)
    {
        if(ifstream("ksiazka_adresowa.txt", ios::ate).tellg())
        {

            while(getline(plik, daneKontaktuOddzielonePionowymiKreskami))
            {
                osoba = pobierzDaneKontaktu(daneKontaktuOddzielonePionowymiKreskami);

                kontakty.push_back(osoba);

                iloscKontaktow++;
            }
            plik.close();

            iloscKontaktow = kontakty.size();

            if(iloscKontaktow == kontakty[iloscKontaktow-1].id )
                return iloscKontaktow;
            else
                return kontakty[iloscKontaktow-1].id;
        }
        else
        {
            cout <<" Plik pusty! Dodaj nowy kontakt!" << endl;
            Sleep(1500);
            return iloscKontaktow;
        }
    }
    else
    {
        cout << "Brak zapisanych kontaktow! Dodaj nowy kontakt." << endl;
        Sleep(1500);
        return iloscKontaktow;
    }
}

int utworzNowyKontakt( vector<Kontakt> &kontakty, int idOstatniegoKontaktu)
{
    system("cls");
    string imie,nazwisko, nrTelefonu, email, adresZamieszkania;

    Kontakt osoba;

    osoba.id = idOstatniegoKontaktu+1;
    cout << "Podaj imie: ";
    cin >> osoba.imie;
    imie[0] = ::toupper(imie[0]);
    cout << "Podaj nazwisko: ";
    cin >> osoba.nazwisko;
    nazwisko[0] = ::toupper(nazwisko[0]);
    cout << "Podaj numer telefonu: ";
    cin.sync();
    getline(cin, osoba.nrTelefonu);
    cout << "Podaj adres email: ";
    cin >> osoba.email;
    cout << "Podaj adres zamieszkania: ";
    cin.sync();
    getline(cin, osoba.adresZamieszkania);

    kontakty.push_back(osoba);

    fstream plik;
    plik.open("ksiazka_adresowa.txt", ios::out | ios::app );

    if(plik.good())
    {
        plik << osoba.id <<"|"<< osoba.imie <<"|"<< osoba.nazwisko <<"|"<< osoba.nrTelefonu <<"|"<< osoba.email <<"|"<< osoba.adresZamieszkania<<"|"<<endl;

        plik.close();

        cout << "Kontakt zostal utworzony." << endl;
        Sleep(1500);
    }
    else
    {
        cout << "Nie mozna otworzyc pliku: ksiazka_adresowa.txt" << endl;
    }

    return osoba.id ;
}

void wyswietlWybraneKontakty(vector<Kontakt> kontakty, int i)
{
    cout << kontakty[i].id <<endl;
    cout << "Imie i nazwisko: " << kontakty[i].imie << " " << kontakty[i].nazwisko << endl;
    cout << "Numer telefonu: " << kontakty[i].nrTelefonu << endl;
    cout << "Adres email: "<< kontakty[i].email << endl;
    cout << "Adres zamieszkania: " << kontakty[i].adresZamieszkania << endl;
    cout << endl << endl;
}

void wyswietlListeKontaktow()
{
    vector<Kontakt> kontakty;
    wczytajDaneZPlikuTekstowego(kontakty);

    if (kontakty.size() > 0)
    {
        cout << "Lista kontaktow: " <<endl;
        cout << endl;

        for (int i = 0; i < kontakty.size(); i++)
        {
            wyswietlWybraneKontakty(kontakty, i);
        }
    }

    cout<<"Nacisnij 'Enter' aby powrocic do menu glownego";
    getchar();
    getchar();
}

void wyszukajKontaktPoImieniu(vector<Kontakt> &kontakty)
{
    system("cls");
    string imie, imieSzukane;

    cout << "Podaj imie: ";
    cin >> imieSzukane;
    imieSzukane[0] = ::toupper(imieSzukane[0]);
    cout << endl << endl;
    bool wyswietlony = true;
    for(int i = 0; i < kontakty.size(); i++)
    {
        if(kontakty[i].imie == imieSzukane)
        {
            wyswietlWybraneKontakty(kontakty, i);
            wyswietlony = false;
        }
    }
    for (int i = 0; i < kontakty.size(); i++)
    {
        if(kontakty[i].imie != imieSzukane)
        {
            if(wyswietlony)
            {
                cout << "Brak kontaktow o podanym imieniu." << endl;
                wyswietlony = false;
            }
        }
    }
    cout << "Nacisnij 'Enter' aby powrocic do menu glownego";
    getchar();
    getchar();
}

void wyszukajKontaktPoNazwisku(vector<Kontakt> &kontakty)
{
    system("cls");
    string nazwisko, nazwiskoSzukane;

    cout << "Podaj nazwisko: ";
    cin >> nazwiskoSzukane;
    nazwiskoSzukane[0] = ::toupper(nazwiskoSzukane[0]);
    cout << endl << endl;
    bool wyswietlony = true;
    for (int i = 0; i < kontakty.size(); i++)
    {
        if(kontakty[i].nazwisko == nazwiskoSzukane)
        {
            wyswietlWybraneKontakty(kontakty, i);
            wyswietlony = false;
        }
    }
    for (int i = 0; i < kontakty.size(); i++)
    {
        if(kontakty[i].nazwisko != nazwiskoSzukane)
        {
            if(wyswietlony)
            {
                cout << "Brak kontaktow o podanym nazwisku." << endl;
                wyswietlony = false;
            }
        }

    }
    cout << "Nacisnij 'Enter' aby powrocic do menu glownego";
    getchar();
    getchar();
}

void edytujKontakt(vector<Kontakt> &kontakty)
{
    system("cls");
    string imie, nazwisko;
    int idKontaktuDoEdycji;

    Kontakt osoba;
    char wybor;

    cout << "Wybierz kontakt do edycji: ";
    cin >> idKontaktuDoEdycji;

    if(sprawdzCzyIstnieje(kontakty,idKontaktuDoEdycji) == true)
    {

        system("cls");
        cout << "Edytuj: " << endl;
        cout << "1 - imie" << endl;
        cout << "2 - nazwisko" << endl;
        cout << "3 - numer telefonu" << endl;
        cout << "4 - email" << endl;
        cout << "5 - adres zamieszkania" << endl;
        cout << "6 - powrot do menu glownego" << endl;
        cin >> wybor;
        cout << endl << endl;

        if (wybor == '6')
        {
            cout << "Nastapi powrot do menu glownego.";
            Sleep (1500);

        }
        else
        {

            fstream plik;
            plik.open("ksiazka_adresowa.txt", ios::out | ios::trunc );
            if (plik.good())
            {
                plik.seekp(0,ios_base::beg);
                for(int i = 0; i < kontakty.size(); i++)
                {
                    if(kontakty[i].id == idKontaktuDoEdycji)
                    {
                        osoba.id = idKontaktuDoEdycji;
                        osoba.imie = kontakty[i].imie;
                        osoba.nazwisko = kontakty[i].nazwisko;
                        osoba.nrTelefonu = kontakty[i].nrTelefonu;
                        osoba.email = kontakty[i].email;
                        osoba.adresZamieszkania = kontakty[i].adresZamieszkania;

                        if(wybor == '1')
                        {
                            cout << "Podaj imie: ";
                            cin >> osoba.imie;
                            imie[0] = ::toupper(imie[0]);
                        }
                        else if (wybor == '2')
                        {
                            cout << "Podaj nazwisko: ";
                            cin >> osoba.nazwisko;
                            nazwisko[0] = ::toupper(nazwisko[0]);
                        }
                        else if (wybor == '3')
                        {
                            cout << "Podaj numer telefonu: ";
                            cin.sync();
                            getline(cin, osoba.nrTelefonu);
                        }
                        else if (wybor == '4')
                        {
                            cout << "Podaj adres email: ";
                            cin >> osoba.email;
                        }
                        else if (wybor == '5')
                        {
                            cout << "Podaj adres zamieszkania: ";
                            cin.sync();
                            getline(cin, osoba.adresZamieszkania);
                        }

                        plik << osoba.id <<"|"<< osoba.imie <<"|"<< osoba.nazwisko <<"|"<< osoba.nrTelefonu <<"|"<< osoba.email <<"|"<< osoba.adresZamieszkania<<"|"<<endl;
                    }
                    else
                    {
                        plik << kontakty[i].id <<"|"<< kontakty[i].imie <<"|"<< kontakty[i].nazwisko <<"|"<< kontakty[i].nrTelefonu <<"|"<< kontakty[i].email <<"|"<< kontakty[i].adresZamieszkania<<"|"<<endl;
                    }
                }
                plik.close();
                kontakty.clear();
                wczytajDaneZPlikuTekstowego(kontakty);
                cout << "Kontakt zostal zaktualizowany." << endl;
                Sleep(1500);
            }
            else
            {
                cout << "Nie mozna otworzyc pliku: ksiazka_adresowa.txt" << endl;
            }
        }
    }
    else
    {
        cout << "Kontakt nie istnieje!Sprobuj ponownie." << endl;
        Sleep(1500);
    }


}

int usunKontakt(vector<Kontakt> &kontakty, int idOstatniegoKontaktu)
{
    system("cls");

    Kontakt osoba;
    int idDoUsuniecia;
    char potwierdzenie = 't';

    cout << "Wybierz kontakt do usuniecia: ";
    cin >> idDoUsuniecia ;
    if(sprawdzCzyIstnieje(kontakty,idDoUsuniecia) == true)
    {

        cout << "Czy na pewno chcesz usunac kontakt? Nacisnij klawisz <t>, aby potwierdzic."<<endl;
        cin >> potwierdzenie;

        if (potwierdzenie == 't')
        {
            fstream plik;
            plik.open("ksiazka_adresowa.txt", ios::out | ios::trunc );

            if (plik.good())
            {
                plik.seekp(0,ios_base::beg);
                for(int i = 0; i < kontakty.size(); i++)
                {
                    if(kontakty[i].id != idDoUsuniecia)
                    {
                        plik << kontakty[i].id <<"|"<< kontakty[i].imie <<"|"<< kontakty[i].nazwisko <<"|"<< kontakty[i].nrTelefonu <<"|"<< kontakty[i].email <<"|"<< kontakty[i].adresZamieszkania<<"|"<<endl;
                    }
                }

                plik.close();

                cout << "Kontakt zostal usuniety." << endl;
                Sleep(1500);
                kontakty.clear();
                wczytajDaneZPlikuTekstowego(kontakty);
                idOstatniegoKontaktu = kontakty.size();

                if(idOstatniegoKontaktu == kontakty[idOstatniegoKontaktu-1].id )
                    return idOstatniegoKontaktu;
                else
                    return kontakty[idOstatniegoKontaktu-1].id;
            }
            else
            {
                cout << "Nie mozna otworzyc pliku: ksiazka_adresowa.txt" << endl;
                return idOstatniegoKontaktu;
            }
        }
        else
        {
            cout <<"Kontakt nie zostal usuniety. Nastapi powrot do menu glownego" <<endl;
            Sleep(1500);
            idOstatniegoKontaktu = kontakty.size();

            if(idOstatniegoKontaktu == kontakty[idOstatniegoKontaktu-1].id )
                return idOstatniegoKontaktu;
            else
                return kontakty[idOstatniegoKontaktu-1].id;
        }
    }
    else
    {
        cout << "Kontakt nie istnieje!Sprobuj ponownie." << endl;
        Sleep(1500);
    }
}

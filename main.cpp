#include <fstream>
// ===== Preprocesoriaus direktyvos ===== //

// Include'iname bibliotekas. J� reik�jo b�tent �ioje programoje, nes...
// Dirbome su �vesties/i�vesties stream'ais (cin/cout).
#include <iostream>

// Nes naudojome setprecision() funkcij�.
#include <iomanip>

// Panaudojome ribas dirbdami su �vesties srautu ir maksimaliomis skaitini� tip� reik�m�mis.
#include <limits>

// Naudojome modulio funkcij� abs().
#include <cmath>

// Hard code'iname masyvo dyd�io reik�m�.
#define MASYVO_DYDIS 500

// =====                           =====  //

// Naudojame standartin� std namespace'�.
// Be jo reik�t� ra�yti std::cout, std::cin, std::endl ir pn�.
using namespace std;

int main(int argc, char* argv[]) {
    int kompiuteriuSkaicius;
    double kompiuteriuKainos[MASYVO_DYDIS];
    int pasikartojimuSkaicius = 1;
    double kainuVidurkis;

    cout << "Sveiki, tai programa, kuri parodys  ar  yra vienodu  kompiuteriu kainu"
         << "\nbei kuri ras kompiuteri su kaina, kuri artimiausia kainu vidurkiui "

         << "\n Copyright(C)2017 Rokas Marcauskas MITnl16 "
         << "\n\nIveskite kompiuteriu skaiciu."
         << "\n> ";


     // Apsauga nuo netinkam� reik�mi� �vestyje, t.y. kit� simboli� nei skai�iai.



     ifstream duomenys("duomenys.txt");
 while (duomenys >> kompiuteriuSkaicius ){
cout  << kompiuteriuSkaicius  << endl;
}
duomenys.close();
    cout << "\nIveskite kompiuteriu kainas, centus atskirdami tasku (pvz.: 500.95)." << endl;
    for (int i = 0; i < kompiuteriuSkaicius; i++) {
        cout << "> #" << i << ": ";
        // Apsauga nuo netinkam� reik�mi� �vestyje, t.y. kit� simboli� nei skai�iai.
        while (!(cin >> kompiuteriuKainos[i])) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    cout << endl;
    for (int i = (kompiuteriuSkaicius - 1); i > 0; i--) {
        for (int j = 1; j <= i; j++) {
            if (kompiuteriuKainos[j - 1] > kompiuteriuKainos[j]) {
                double temp = kompiuteriuKainos[j - 1];
                kompiuteriuKainos[j - 1] = kompiuteriuKainos[j];
                kompiuteriuKainos[j] = temp;
            }
        }
    }

    double ankstesnisElementas = kompiuteriuKainos[0];
    for (int i = 1; i < kompiuteriuSkaicius; i++) {
        if (kompiuteriuKainos[i] == ankstesnisElementas) {
            pasikartojimuSkaicius++;
            if (kompiuteriuSkaicius < 3) {
                if (pasikartojimuSkaicius > 1) {
                    cout << "[!] Masyve kompiuterio kaina '" << fixed << setprecision(2) << ankstesnisElementas
                         << "' pasikartojo " << pasikartojimuSkaicius << " karta (-us)." << endl;
                }
            }
        } else {
            if (pasikartojimuSkaicius > 1) {
                cout << "[!] Masyve kompiuterio kaina '" << fixed << setprecision(2) << ankstesnisElementas
                     << "' pasikartojo " << pasikartojimuSkaicius << " karta (-us)." << endl;
                ankstesnisElementas = kompiuteriuKainos[i];
                pasikartojimuSkaicius = 1;
            }
        }
    }

    double kainuSuma = 0;
    for (int i = 0; i < kompiuteriuSkaicius; i++) {
        kainuSuma += kompiuteriuKainos[i];
    }
    kainuVidurkis = kainuSuma / kompiuteriuSkaicius;

    int artimiausiosKainosKompiuteris = 0;
    double maziausiasSkirtumas = numeric_limits<double>::max();
    for (int i = 0; i < kompiuteriuSkaicius; i++) {
        if (abs(kompiuteriuKainos[i] - kainuVidurkis) < maziausiasSkirtumas) {
            maziausiasSkirtumas = abs(kompiuteriuKainos[i] - kainuVidurkis);
            artimiausiosKainosKompiuteris = i;
        }
    }

    cout << "\nKompiuterio kainu vidurkis: " << kainuVidurkis;
    cout << "\nKompiuterio, kurio kaina yra maziausiai nutolusi nuo vidurkio, numeris yra: "
         << artimiausiosKainosKompiuteris << ".\nJo kaina yra: "
         << kompiuteriuKainos[artimiausiosKainosKompiuteris] << endl;


ofstream blankas ("rezultatas.txt");
blankas << pasikartojimuSkaicius  << ' ' << kainuVidurkis << ' ' <<  artimiausiosKainosKompiuteris <<  endl;
blankas.close();

    cout << "\nPaspauskite <ENTER>.";
    cin.sync();
    cin.ignore(numeric_limits<streamsize>::max(),'\n');

    return 0;
}

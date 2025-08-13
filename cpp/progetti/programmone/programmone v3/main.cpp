#include <iostream>
#include <cmath>
#include <limits>
#include <string>
#define VERSIONE_PROGRAMMONE 3
using namespace std;

#ifdef _WIN32
   #define byte win_byte_override
   #include <windows.h>
   #undef byte
   #define OS "windows"
   #define DORMI(periodo) Sleep(periodo)
   #define CLEAR() system("cls")
   #define PAUSE() system("pause")
#elif __linux__
   #include <unistd.h>
   #include <chrono>
   #include <thread>
   #define OS "linux"
   #define DORMI(periodo) std::this_thread::sleep_for(std::chrono::milliseconds(periodo))
   #define CLEAR() system("clear")
   #define PAUSE() system("read -n 1 -s -r -p \"Premi un tasto per continuare...\"")
#elif __APPLE__
   cout << "Hmm. Vedo che stai usando Apple. No\n";
   return EXIT_FAILURE;
#elif __ANDOIRD__
   cout << "Non ho voglia di portarlo anche per Android. La prossima volta usi una vera distro di Linux\n";
   return EXIT_FAILURE:
#else
   cerr << "ERRORE CATASTROFICO: Non sono riuscito ad identificare il tuo sistema operativo!\n";
   return EXIT_FAILURE;
#endif

// prototipi
void menuPrincipale();
void account();

// variabili globali
bool debugMode = false, ownerMode = true;

int sceltaINT;

char sceltaCHAR;

string sceltaSTR;

// utilities
void wait() {
   DORMI(300);
   cout << "." << flush;
   DORMI(300);
   cout << "." << flush;
   DORMI(300);
   cout << "." << flush;
   DORMI(300);
   return;
}
void ERRORE(string parametro) {
   cerr << "/!\\ ERRORE: " << parametro;
   wait();
   cout << endl;
   return;
}
void ATTENZIONE(string parametro) {
   cerr << "/!\\ ATTENZIONE: " << parametro;
   wait();
   cout << endl;
   return;
}
void INFORMAZIONE(string parametro) {
   cout << "Info: " << parametro;
   wait();
   cout << endl;
   return;
}
void PURO(string parametro) {
   cout << parametro;
   wait();
   cout << endl;
   return;
}
void DEBUG(string parametro) {
   if (debugMode) cout << "DEBUG: " << parametro << endl;
   return;
}
bool CINCHECK (string errore) {
   if (cin.fail()) {
      ERRORE(errore);
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      return true;
   } else {
      return false;
   }
}
void titolo(string parametro, bool systemCLS) {
   if (systemCLS) CLEAR();

   cout << "O";
   for (int i = 0; i < 2*parametro.length() + 5; i++) {
      cout << "-";
   }
   cout << "O" << endl;

   cout << "|   ";
   for (int i = 0; i < parametro.length(); i++) {
      cout << parametro.at(i);
      cout << " ";
   }
   cout << "  |" << endl;

   cout << "O";
   for (int i = 0; i < 2*parametro.length() + 5; i++) {
      cout << "-";
   }
   cout << "O";
   cout << endl << endl;
}
void workInProgress() {
   titolo("ATTENZIONE", true);
   cout << "Questa pagina e' ancora in lavorazione, percio' non e' ancora accessibile";
   wait();
   cout << endl;
   cout << "Verrai reindirizzato al menu principale";
   wait();
   menuPrincipale();
   return;
}

// corpo del programmone v3

void conversioni() {
   double unitaOriginale;

   titolo("CONVERSIONI", true);
   cout << "Selezionare le unita' di misura da convertire:" << endl;
   cout << "- 1: Temperatura" << endl;
   cout << "- 2: Massa" << endl;
   cout << "- 3: Valuta" << endl;
   cout << "- 0: Torna al menu principale" << endl;
   cout << "> "; cin >> sceltaINT;

   switch (sceltaINT) {
   case 1:// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - CONVERSIONE DELLA TEMPERATURA
      titolo("CONVERSIONE della TEMPERATURA", true);
      cout << "selezionare l'unita' di partenza (C, F, K, R): "; cin >> sceltaCHAR;
      switch (sceltaCHAR) {
      case 'C':
      case 'c':
         cout << "Inserire la temperatura in C: "; cin >> unitaOriginale;

         if(CINCHECK("Inserire un numero")) {
            conversioni();
            return;
            break;
         }

         cout << "In che unita' convertire? (F, K, R): "; cin >> sceltaCHAR;

         if (sceltaCHAR == 'F' || sceltaCHAR == 'f') {
            cout << unitaOriginale << "C e' uguale a " << unitaOriginale * 9/5 + 32 << "F" << endl;
            PAUSE();
            conversioni();
            return;
            break;
         } else if (sceltaCHAR == 'K' || sceltaCHAR == 'k')  {
            cout << unitaOriginale << "C e' uguale a " << unitaOriginale + 273.15 << "K" << endl;
            PAUSE();
            conversioni();
            return;
            break;
         } else if (sceltaCHAR == 'R' || sceltaCHAR == 'r') {
            cout << unitaOriginale << "C e' uguale a " << (unitaOriginale + 273.15) * 9/5 << "R" << endl;
            PAUSE();
            conversioni();
            return;
            break;
         } else {
            ERRORE("Scegliere un opzione accettabile");
            conversioni();
            return;
            break;
         }
         
         break;
      
      case 'F':
      case 'f':
         cout << "Inserire la temperatura in F: "; cin >> unitaOriginale;

         if(CINCHECK("Inserire un numero")) {
            conversioni();
            return;
            break;
         }

         cout << "In che unita' convertire? (C, K, R): "; cin >> sceltaCHAR;

         if (sceltaCHAR == 'C' || sceltaCHAR == 'c') {
            cout << unitaOriginale << "F e' uguale a " << (unitaOriginale - 32) * 5/9 << "C" << endl;
            PAUSE();
            conversioni();
            return;
            break;
         } else if (sceltaCHAR == 'K' || sceltaCHAR == 'k')  {
            cout << unitaOriginale << "F e' uguale a " << (unitaOriginale + 459.67) * 5/9 << "K" << endl;
            PAUSE();
            conversioni();
            return;
            break;
         } else if (sceltaCHAR == 'R' || sceltaCHAR == 'r') {
            cout << unitaOriginale << "F e' uguale a " << unitaOriginale + 459.67 << "R" << endl;
            PAUSE();
            conversioni();
            return;
            break;
         } else {
            ERRORE("Scegliere un opzione accettabile");
            conversioni();
            return;
            break;
         }
         
         break;
      
      case 'K':
      case 'k':
         cout << "Inserire la temperatura in K: "; cin >> unitaOriginale;

         if(CINCHECK("Inserire un numero")) {
            conversioni();
            return;
            break;
         }

         cout << "In che unita' convertire? (C, F, R): "; cin >> sceltaCHAR;

         if (sceltaCHAR == 'C' || sceltaCHAR == 'c') {
            cout << unitaOriginale << "K e' uguale a " << unitaOriginale - 273.15 << "C" << endl;
            PAUSE();
            conversioni();
            return;
            break;
         } else if (sceltaCHAR == 'F' || sceltaCHAR == 'f')  {
            cout << unitaOriginale << "K e' uguale a " << unitaOriginale * 9/5 - 459.67 << "F" << endl;
            PAUSE();
            conversioni();
            return;
            break;
         } else if (sceltaCHAR == 'R' || sceltaCHAR == 'r') {
            cout << unitaOriginale << "K e' uguale a " << unitaOriginale * 9/5 << "R" << endl;
            PAUSE();
            conversioni();
            return;
            break;
         } else {
            ERRORE("Scegliere un opzione accettabile");
            conversioni();
            return;
            break;
         }
         
         break;
      
      case 'R':
      case 'r':
         cout << "Inserire la temperatura in R: "; cin >> unitaOriginale;

         if(CINCHECK("Inserire un numero")) {
            conversioni();
            return;
            break;
         }

         cout << "In che unita' convertire? (C, F, K): "; cin >> sceltaCHAR;

         if (sceltaCHAR == 'C' || sceltaCHAR == 'c') {
            cout << unitaOriginale << "R e' uguale a " << unitaOriginale * 5/9 - 273.15 << "C" << endl;
            PAUSE();
            conversioni();
            return;
            break;
         } else if (sceltaCHAR == 'F' || sceltaCHAR == 'f')  {
            cout << unitaOriginale << "R e' uguale a " << unitaOriginale - 459.67 << "F" << endl;
            PAUSE();
            conversioni();
            return;
            break;
         } else if (sceltaCHAR == 'K' || sceltaCHAR == 'k') {
            cout << unitaOriginale << "R e' uguale a " << unitaOriginale * 5/9 << "K" << endl;
            PAUSE();
            conversioni();
            return;
            break;
         } else {
            ERRORE("Scegliere un opzione accettabile");
            conversioni();
            return;
            break;
         }
         
         break;
      
      default:
         ERRORE("Selezionare un'opzione accettabile");
         conversioni();
         return;
         break;
      }
      break;
   
   case 2: // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - CONVERSIONE DELLA MASSA
      titolo("CONVERSIONE della MASSA", true);
      cout << "Selezionare l'unita' di partenza (Kg, Lb, St, Slug, Tal, OzT): "; cin >> sceltaSTR;

      if          (sceltaSTR == "Kg"   || sceltaSTR == "kg") {
         cout << "Inserire la massa in Kg: "; cin >> unitaOriginale;
   
         if(CINCHECK("Inserire un numero")) {
            conversioni();
            return;
         }
   
         cout << "In che unita' convertire? (Lb, St, Slug, Tal, OzT): "; cin >> sceltaSTR;
   
         if (sceltaSTR == "Lb" || sceltaSTR == "lb") {
            cout << unitaOriginale << "Kg e' uguale a " << unitaOriginale * 2.20462 << sceltaCHAR << endl;
            PAUSE();
            conversioni();
            return;

         } else if (sceltaSTR == "St" || sceltaSTR == "st") {
            cout << unitaOriginale << "Kg e' uguale a " << unitaOriginale / 6.35029 << sceltaCHAR << endl;
            PAUSE();
            conversioni();
            return;

         } else if (sceltaSTR == "Slug" || sceltaSTR == "slug") {
            cout << unitaOriginale << "Kg e' uguale a " << unitaOriginale / 14.5939 << sceltaCHAR << endl;
            PAUSE();
            conversioni();
            return;

         } else if (sceltaSTR == "Tal" || sceltaSTR == "tal") {
            cout << unitaOriginale << "Kg e' uguale a " << unitaOriginale / 32.3 << sceltaCHAR << endl;
            PAUSE();
            conversioni();
            return;

         } else if (sceltaSTR == "OzT" || sceltaSTR == "ozt") {
            cout << unitaOriginale << "Kg e' uguale a " << unitaOriginale / 0.0311035 << sceltaCHAR << endl;
            PAUSE();
            conversioni();
            return;

         } else {
            ERRORE("Scegliere un'opzione accettabile");
            conversioni();
            return;

         }

      } else if   (sceltaSTR == "Lb"   || sceltaSTR == "lb") {
         cout << "Inserire la massa in Lb: "; cin >> unitaOriginale;
   
         if(CINCHECK("Inserire un numero")) {
            conversioni();
            return;
         }
   
         cout << "In che unita' convertire? (Kg, St, Slug, Tal, OzT): "; cin >> sceltaSTR;
   
         if (sceltaSTR == "Kg" || sceltaSTR == "kg") {
            cout << unitaOriginale << "Lb e' uguale a " << unitaOriginale * 0.453592 << sceltaCHAR << endl;
            PAUSE();
            conversioni();
            return;

         } else if (sceltaSTR == "St" || sceltaSTR == "st") {
            cout << unitaOriginale << "Lb e' uguale a " << unitaOriginale / 14 << sceltaCHAR << endl;
            PAUSE();
            conversioni();
            return;

         } else if (sceltaSTR == "Slug" || sceltaSTR == "slug") {
            cout << unitaOriginale << "Lb e' uguale a " << unitaOriginale * 0.031081 << sceltaCHAR << endl;
            PAUSE();
            conversioni();
            return;

         } else if (sceltaSTR == "Tal" || sceltaSTR == "tal") {
            cout << unitaOriginale << "Lb e' uguale a " << unitaOriginale * 0.0140486 << sceltaCHAR << endl;
            PAUSE();
            conversioni();
            return;

         } else if (sceltaSTR == "OzT" || sceltaSTR == "ozt") {
            cout << unitaOriginale << "Lb e' uguale a " << unitaOriginale * 14.5833 << sceltaCHAR << endl;
            PAUSE();
            conversioni();
            return;

         } else {
            ERRORE("Scegliere un'opzione accettabile");
            conversioni();
            return;
         }

      } else if   (sceltaSTR == "St"   || sceltaSTR == "st") {

         cout << "Inserire la massa in St: "; cin >> unitaOriginale;

         if(CINCHECK("Inserire un numero")) {
            conversioni();
            return;
         }

         cout << "In che unita' convertire? (Kg, Lb, Slug, Tal, OzT): "; cin >> sceltaSTR;

         if (sceltaSTR == "Kg" || sceltaSTR == "kg") {
            cout << unitaOriginale << "St e' uguale a " << unitaOriginale * 6.35029 << sceltaCHAR << endl;
            PAUSE();
            conversioni();
            return;

         } else if (sceltaSTR == "Lb" || sceltaSTR == "lb") {
            cout << unitaOriginale << "St e' uguale a " << unitaOriginale * 14 << sceltaCHAR << endl;
            PAUSE();
            conversioni();
            return;

         } else if (sceltaSTR == "Slug" || sceltaSTR == "slug") {
            cout << unitaOriginale << "St e' uguale a " << unitaOriginale * 0.435923 << sceltaCHAR << endl;
            PAUSE();
            conversioni();
            return;

         } else if (sceltaSTR == "Tal" || sceltaSTR == "tal") {
            cout << unitaOriginale << "St e' uguale a " << unitaOriginale * 0.196594 << sceltaCHAR << endl;
            PAUSE();
            conversioni();
            return;

         } else if (sceltaSTR == "OzT" || sceltaSTR == "ozt") {
            cout << unitaOriginale << "St e' uguale a " << unitaOriginale * 204.166 << sceltaCHAR << endl;
            PAUSE();
            conversioni();
            return;

         } else {
            ERRORE("Scegliere un'opzione accettabile");
            conversioni();
            return;

         }
      } else if   (sceltaSTR == "Slug" || sceltaSTR == "slug") {

         cout << "Inserire la massa in Slug: "; cin >> unitaOriginale;

         if(CINCHECK("Inserire un numero")) {
            conversioni();
            return;
         }

         cout << "In che unita' convertire? (Kg, Lb, St, Tal, OzT): "; cin >> sceltaSTR;

         if (sceltaSTR == "Kg" || sceltaSTR == "kg") {
            cout << unitaOriginale << "Slug e' uguale a " << unitaOriginale * 14.5939 << sceltaCHAR << endl;
            PAUSE();
            conversioni();
            return;

         } else if (sceltaSTR == "Lb" || sceltaSTR == "lb") {
            cout << unitaOriginale << "Slug e' uguale a " << unitaOriginale * 32.174 << sceltaCHAR << endl;
            PAUSE();
            conversioni();
            return;

         } else if (sceltaSTR == "St" || sceltaSTR == "st") {
            cout << unitaOriginale << "Slug e' uguale a " << unitaOriginale / 2.294 << sceltaCHAR << endl;
            PAUSE();
            conversioni();
            return;

         } else if (sceltaSTR == "Tal" || sceltaSTR == "tal") {
            cout << unitaOriginale << "Slug e' uguale a " << unitaOriginale * 0.451822 << sceltaCHAR << endl;
            PAUSE();
            conversioni();
            return;

         } else if (sceltaSTR == "OzT" || sceltaSTR == "ozt") {
            cout << unitaOriginale << "Slug e' uguale a " << unitaOriginale * 469.104 << sceltaCHAR << endl;
            PAUSE();
            conversioni();
            return;

         } else {
            ERRORE("Scegliere un'opzione accettabile");
            conversioni();
            return;

         }
      } else if   (sceltaSTR == "Tal"  || sceltaSTR == "tal") {

         cout << "Inserire la massa in Tal: "; cin >> unitaOriginale;

         if(CINCHECK("Inserire un numero")) {
            conversioni();
            return;
         }

         cout << "In che unita' convertire? (Kg, Lb, St, Slug, OzT): "; cin >> sceltaSTR;

         if (sceltaSTR == "Kg" || sceltaSTR == "kg") {
            cout << unitaOriginale << "Tal e' uguale a " << unitaOriginale * 32.3 << sceltaCHAR << endl;
            PAUSE();
            conversioni();
            return;

         } else if (sceltaSTR == "Lb" || sceltaSTR == "Lb") {
            cout << unitaOriginale << "Tal e' uguale a " << unitaOriginale * 71.215 << sceltaCHAR << endl;
            PAUSE();
            conversioni();
            return;

         } else if (sceltaSTR == "St" || sceltaSTR == "st") {
            cout << unitaOriginale << "Tal e' uguale a " << unitaOriginale * 5.0868 << sceltaCHAR << endl;
            PAUSE();
            conversioni();
            return;

         } else if (sceltaSTR == "Slug" || sceltaSTR == "Slug") {
            cout << unitaOriginale << "Tal e' uguale a " << unitaOriginale * 2.213 << sceltaCHAR << endl;
            PAUSE();
            conversioni();
            return;

         } else if (sceltaSTR == "OzT" || sceltaSTR == "ozt") {
            cout << unitaOriginale << "Tal e' uguale a " << unitaOriginale / 1038.85 << sceltaCHAR << endl;
            PAUSE();
            conversioni();
            return;

         } else {
            ERRORE("Scegliere un'opzione accettabile");
            conversioni();
            return;

         }
      } else if   (sceltaSTR == "OzT"  || sceltaSTR == "Ozt"   || sceltaSTR == "ozt") {

         cout << "Inserire la massa in OzT: "; cin >> unitaOriginale;

         if(CINCHECK("Inserire un numero")) {
            conversioni();
            return;
         }

         cout << "In che unita' convertire? (Kg, Lb, St, Slug, Tal): "; cin >> sceltaSTR;

         if (sceltaSTR == "Kg" || sceltaSTR == "kg") {
            cout << unitaOriginale << "OzT e' uguale a " << unitaOriginale * 0.0311035 << sceltaCHAR << endl;
            PAUSE();
            conversioni();
            return;

         } else if (sceltaSTR == "Lb" || sceltaSTR == "lb") {
            cout << unitaOriginale << "OzT e' uguale a " << unitaOriginale / 14.5833 << sceltaCHAR << endl;
            PAUSE();
            conversioni();
            return;

         } else if (sceltaSTR == "St" || sceltaSTR == "st") {
            cout << unitaOriginale << "OzT e' uguale a " << unitaOriginale / 204.166 << sceltaCHAR << endl;
            PAUSE();
            conversioni();
            return;

         } else if (sceltaSTR == "Slug" || sceltaSTR == "slug") {
            cout << unitaOriginale << "OzT e' uguale a " << unitaOriginale / 469.104 << sceltaCHAR << endl;
            PAUSE();
            conversioni();
            return;

         } else if (sceltaSTR == "Tal" || sceltaSTR == "tal") {
            cout << unitaOriginale << "OzT e' uguale a " << unitaOriginale / 1038.85 << sceltaCHAR << endl;
            PAUSE();
            conversioni();
            return;

         } else {
            ERRORE("Scegliere un'opzione accettabile");
            conversioni();
            return;

         }
      } else {

         ERRORE("Selezionare un'opzione accettabile");
         conversioni();
         return;
      }
      break;

   case 3: // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - CONVERSIONE DELLE VALUTE
      titolo("CONVERSIONE delle VALUTE", true);
      cout << "Selezionare la valuta di partenza (EUR, USD, JPY, RUB): "; cin >> sceltaSTR;

      if          (sceltaSTR == "EUR" || sceltaSTR == "Eur" || sceltaSTR == "eur") {
         cout << "Inserire la quantita' di Euro da convertire: "; cin >> unitaOriginale;

         if (CINCHECK("Inserire un numero")) {
            conversioni();
            return;
         }

         cout << "In che valuta convertire (USD, JPY, RUB): "; cin >> sceltaSTR;

         if (sceltaSTR == "USD" || sceltaSTR == "Usd" || sceltaSTR == "usd") {
            cout << unitaOriginale << " Euro equivalgono a " << unitaOriginale * 1.17 << " Dollari americani" << endl;
            PAUSE();
            conversioni();
            return;
         } else if (sceltaSTR == "JPY" || sceltaSTR == "Jpy" || sceltaSTR == "jpy") {
            cout << unitaOriginale << " Euro equivalgono a " << unitaOriginale * 172 << " Yen giapponesi" << endl;
            PAUSE();
            conversioni();
            return;
         } else if (sceltaSTR == "RUB" || sceltaSTR == "Rub" || sceltaSTR == "rub") {
            cout << unitaOriginale << " Euro equivalgono a " << unitaOriginale * 91.43 << " Rubli russi" << endl;
            PAUSE();
            conversioni();
            return;
         } else {
            ERRORE("Scegliere un'opzione accettabile");
            conversioni();
            return;
         }
      } else if   (sceltaSTR == "USD" || sceltaSTR == "Usd" || sceltaSTR == "usd") {
         cout << "Inserire la quantita' di Dollari statunitensi da convertire: "; cin >> unitaOriginale;

         if (CINCHECK("Inserire un numero")) {
            conversioni();
            return;
         }

         cout << "In che valuta convertire (EUR, JPY, RUB): "; cin >> sceltaSTR;

         if (sceltaSTR == "EUR" || sceltaSTR == "Eur" || sceltaSTR == "eur") {
            cout << unitaOriginale << " Dollari statunitensi equivalgono a " << unitaOriginale * 0.86 << " Euro" << endl;
            PAUSE();
            conversioni();
            return;
         } else if (sceltaSTR == "JPY" || sceltaSTR == "Jpy" || sceltaSTR == "jpy") {
            cout << unitaOriginale << " Dollari statunitensi equivalgono a " << unitaOriginale * 147 << " Yen" << endl;
            PAUSE();
            conversioni();
            return;
         } else if (sceltaSTR == "RUB" || sceltaSTR == "Rub" || sceltaSTR == "rub") {
            cout << unitaOriginale << " Dollari statunitensi equivalgono a " << unitaOriginale * 78.20 << " Rubli russi" << endl;
            PAUSE();
            conversioni();
            return;
         } else {
            ERRORE("Scegliere un'opzione accettabile");
            conversioni();
            return;
         }
      } else if   (sceltaSTR == "JPY" || sceltaSTR == "Jpy" || sceltaSTR == "jpy") {
         cout << "Inserire la quantita' di Yen da convertire: "; cin >> unitaOriginale;

         if (CINCHECK("Inserire un numero")) {
            conversioni();
            return;
         }

         cout << "In che valuta convertire (EUR, USD, RUB): "; cin >> sceltaSTR;

         if (sceltaSTR == "EUR" || sceltaSTR == "Eur" || sceltaSTR == "eur") {
            cout << unitaOriginale << " Yen equivale a " << unitaOriginale * 1.17 << " Euro" << endl;
            PAUSE();
            conversioni();
            return;
         } else if (sceltaSTR == "USD" || sceltaSTR == "Usd" || sceltaSTR == "usd") {
            cout << unitaOriginale << " Yen equivale a " << unitaOriginale * 172 << " Dollari statunitensi" << endl;
            PAUSE();
            conversioni();
            return;
         } else if (sceltaSTR == "RUB" || sceltaSTR == "Rub" || sceltaSTR == "rub") {
            cout << unitaOriginale << " Yen equivale a " << unitaOriginale * 91.43 << " Rubli russi" << endl;
            PAUSE();
            conversioni();
            return;
         } else {
            ERRORE("Scegliere un'opzione accettabile");
            conversioni();
            return;
         }
      } else if (sceltaSTR == "EUR" || sceltaSTR == "Eur" || sceltaSTR == "eur") {
         cout << "Inserire la quantita' di Euro da convertire: "; cin >> unitaOriginale;

         if (CINCHECK("Inserire un numero")) {
            conversioni();
            return;
         }

         cout << "In che valuta convertire (USD, JPY, RUB): "; cin >> sceltaSTR;

         if (sceltaSTR == "USD" || sceltaSTR == "Usd" || sceltaSTR == "usd") {
            cout << unitaOriginale << " Euro equivale a " << unitaOriginale * 1.17 << " Dollari americani" << endl;
            PAUSE();
            conversioni();
            return;
         } else if (sceltaSTR == "JPY" || sceltaSTR == "Jpy" || sceltaSTR == "jpy") {
            cout << unitaOriginale << " Euro equivale a " << unitaOriginale * 172 << " Yen giapponesi" << endl;
            PAUSE();
            conversioni();
            return;
         } else if (sceltaSTR == "RUB" || sceltaSTR == "Rub" || sceltaSTR == "rub") {
            cout << unitaOriginale << " Euro equivale a " << unitaOriginale * 91.43 << " Rubli russi" << endl;
            PAUSE();
            conversioni();
            return;
         } else {
            ERRORE("Scegliere un'opzione accettabile");
            conversioni();
            return;
         }
      }
   
   case 0:
      PURO("Verrai reindirizzato al menu principale");
      menuPrincipale();
      return;
      break;
   default:
      ERRORE("Selezionare un'opzione accettabile");
      conversioni();
      return;
      break;
   }
}

void calcolatrice() {
   char segno;
   double base, indice, esponente, campione, risultato=NAN;

   titolo("CALCOLATRICE", true);

   cout << "Selezionare il tipo di operazione da eseguire:" << endl;
   cout << "-  1: Operazioni semplici (+, -, *, /)    -  2: Potenza (!PZ)     " << endl;
   cout << "-  3: Radice                              -  4: Fattoriale        " << endl;
   cout << "-  5: Percentuale                         -  6: Logaritmo         " << endl;
   cout << "-  7: Esponenziale                        -  8: Seno              " << endl;
   cout << "-  9: Coseno                              - 10: Tangente          " << endl;
   cout << "- 11: Arco-Seno                           - 12: Arco-Coseno       " << endl;
   cout << "- 13: Arco-Tangente                       - 14: Valore Assoluto   " << endl;
   cout << "- 0: Torna al menu principale   " << endl;
   cout << "> "; cin >> sceltaINT;

   switch (sceltaINT) {
   case 1:
      titolo("OPERAZIONI SEMPLICI", true);
      cout << "Inserire l'espressione da eseguire. Per visualizzare il risultato, inserire '='." << endl;
      cout << "ATTENZIONE: Questa calcolatrice NON tiene conto dell'ordine matematico, bensi' esegue le operazioni in ordine di IMMISSIONE." << endl << endl;
      while (true) {
         cout << "> "; cin >> campione;

         if (CINCHECK("Inserire un numero")) {
            calcolatrice();
            return;
            break;
         }
         
         DEBUG(to_string(campione));
         
         if (isnan(risultato)) {
            risultato = campione;
            DEBUG("risultato = campione");
         } else {
            if (segno == '+') risultato += campione;
            else if (segno == '-') risultato -= campione;
            else if (segno == '*') risultato *= campione;
            else if (segno == '/') risultato /= campione;
            else if (segno == '\0'); //se il segno non c'è (prima esecuzione) lo ottiene senza fare cose
            else ERRORE("Inserire un segno corretto: '+' come somma; '-' come sottrazione; '*' come moltiplicazione; '/' come divisione");
         }

         cout << "> "; cin >> segno;
         
         if (segno == '=') {
            cout << endl << "Il risultato e' " << risultato << endl;
            PAUSE();
            calcolatrice();
            return;
            break;
         }
         DEBUG("Risultato parziale = " + to_string(risultato));
      }

      break;

   case 2:
      titolo("POTENZE", true);
      cout << "Inserire la base della potenza: "; cin >> base;
      cout << "Inserire l'esponente della potenza: "; cin >> esponente;

      cout << endl << base << "^" << esponente << " risulta " << pow(base, esponente) << endl;
      PAUSE();
      calcolatrice();
      return;
      break;

   case 3:
      titolo("RADICE", true);
      cout << "Inserire la base della radice: "; cin >> base;
      cout << "Inserire l'indice della radice: "; cin >> indice;

      if (indice < 0)  {
         ATTENZIONE("Questa calcolatrice non supporta numeri immaginari");
         calcolatrice();
         return;
         break;
      }

      cout << endl << "Questa radice ha come risultato " << pow(base, 1/indice) << endl;
      PAUSE();
      calcolatrice();
      return;
      break;

   case 4:
      titolo("FATTORIALE", true);
      cout << "Inserire il numero di cui calcolare il fattoriale: "; cin >> campione;
      
      if (CINCHECK("Inserire un numero")) {
         calcolatrice();
         return;
         break;
      }
      risultato = 1;

      for (int i = 0; i < campione; i++) {
         risultato *= i+1;
      }
      
      cout << endl << campione << "! = " << risultato << endl;
      
      PAUSE();
      calcolatrice();
      return;
      break;

   case 5:
      titolo("PERCENTUALE", true);
      cout << "Inserire il numero di cui calcolare la percentuale: "; cin >> campione;

      if(CINCHECK("Inserire un numero")) {
         calcolatrice();
         return;
         break;
      }
      
      cout << endl << campione << "% = " << campione/100.0 << endl;
      PAUSE();
      calcolatrice();
      return;
      break;

   case 6:
      titolo("LOGARITMO", true);   
      cout << "Inserire la base del logaritmo: "; cin >> campione;
      
      if (CINCHECK("Inserire un numero")) {
         calcolatrice();
         return;
         break;
      }

      cout << "Questo logaritmo e' in base 10? (s/n) " << endl;
      cout << "> "; cin >> sceltaCHAR;
      cout << endl;
      
      (sceltaCHAR == 's')? cout << "Log10(" << campione << ") = " << log10(campione) : cout << "Log(" << campione << ") = " << log(campione);
      cout << endl;
      PAUSE();
      calcolatrice();
      return;
      break;

   case 7:
      titolo("ESPONENZIALE", true);
      cout << "Inserire il numero da calcolare: "; cin >> campione;

      if(CINCHECK("Inserire un numero")) {
         calcolatrice();
         return;
         break;
      }

      cout << endl << "e^" << campione << " = " << exp(campione) << endl;

      PAUSE();
      calcolatrice();
      return;
      break;
      
   case 8:
      titolo("SENO", true);
      cout << "Inserire il numero da calcolare: "; cin >> campione;
      
      if(CINCHECK("Inserire un numero"))  {
         calcolatrice();
         return;
         break;
      }

      cout << endl << "sin(" << campione << ") = " << sin(campione) << endl;

      PAUSE();
      calcolatrice();
      return;
      break;

   case 9:
      titolo("COSENO", true);
      cout << "Inserire il numero da calcolare: "; cin >> campione;
      
      if(CINCHECK("Inserire un numero"))  {
         calcolatrice();
         return;
         break;
      }

      cout << endl << "cos(" << campione << ") = " << cos(campione) << endl;
      
      PAUSE();
      calcolatrice();
      return;
      break;

   case 10:
      titolo("TANGENTE", true);
      cout << "Inserire il numero da calcolare: "; cin >> campione;
      
      if(CINCHECK("Inserire un numero"))  {
         calcolatrice();
         return;
         break;
      }

      cout << endl << "tan(" << campione << ") = " << tan(campione) << endl;
      
      PAUSE();
      calcolatrice();
      return;
      break;

   case 11:
      titolo("ARCO-SENO", true);
      cout << "Inserire il numero da calcolare: "; cin >> campione;
      
      if(CINCHECK("Inserire un numero"))  {
         calcolatrice();
         return;
         break;
      }

      cout << endl << "asin(" << campione << ") = " << asin(campione) << endl;
      
      PAUSE();
      calcolatrice();
      return;
      break;

   case 12:
      titolo("ARCO-COSENO", true);
      cout << "Inserire il numero da calcolare: "; cin >> campione;
      
      if(CINCHECK("Inserire un numero"))  {
         calcolatrice();
         return;
         break;
      }

      cout << endl << "acos(" << campione << ") = " << acos(campione) << endl;
      
      PAUSE();
      calcolatrice();
      return;
      break;

   case 13:
      titolo("ARCO-TANGENTE", true);
      cout << "Inserire il numero da calcolare: "; cin >> campione;
      
      if(CINCHECK("Inserire un numero"))  {
         calcolatrice();
         return;
         break;
      }

      cout << endl << "atan(" << campione << ") = " << atan(campione) << endl;
      
      PAUSE();
      calcolatrice();
      return;
      break;

   case 14:
      titolo("VALORE ASSOLUTO", true);
      cout << "Inserire il numero da calcolare: "; cin >> campione;

      if(CINCHECK("Inserire un numero")) {
         calcolatrice();
         return;
         break;
      }

      cout << endl << "|" << campione << "| = " << abs(campione) << endl;

      PAUSE();
      calcolatrice();
      return;
      break;
   case 0:
      PURO("Verrai reindirizzato al menu principale");
      menuPrincipale();
      return;
      break;

   default:
      ERRORE("Selezionare un'opzione accettabile");
      calcolatrice();
      return;
      break;
   }
   return;
}

void informazioni() {
   titolo("INFORMAZIONI & ABBREVIAZIONI", true);
   cout << "                                  ABBREVIAZIONI                                 " << endl;
   cout << "                                 ---------------                                " << endl;
   cout << "88=========================88=================88==============================88" << endl;
   cout << "||          Massa          ||   Temperatura   ||            Valute            ||" << endl;
   cout << "||         -------         ||  -------------  ||           --------           ||" << endl;
   cout << "|| - Kg    Chilogrammo     || - C  Celsius    || - EUR  Euro                  ||" << endl;
   cout << "|| - Lb    Libra           || - F  Farenheit  || - USD  Dollaro Statunitense  ||" << endl;
   cout << "|| - St    Stone           || - K  Kelvin     || - JPY  Yen Giapponese        ||" << endl;
   cout << "|| - Slug  Slug            || - R  Rankine    || - RUB  Rublo Russo           ||" << endl;
   cout << "|| - Tal   Talento Romano  88=================88==============================88" << endl;
   cout << "|| - OzT   Oncia Troy      ||" << endl;
   cout << "88=========================88" << endl;
   cout << endl;
   cout << "Il cambio delle valute e' aggiornato a Lunedi' 14 Luglio 2025,  CEST" << endl;

   cout << endl; PAUSE();
   account();
   return;
}

void crediti() {
   titolo("CREDITI", true);
   cout << "Idea originale: - - - - - - - - Carletti Stefano" << endl;
   cout << "Project Manager:- - - - - - - - Carletti Stefano" << endl;
   cout << "Software Architect: - - - - - - Carletti Stefano" << endl;
   cout << "Software Delevopers:- - - - - - Carletti Stefano" << endl;
   cout << "                              \\ E basta" << endl;
   cout << "User Interface Designer:- - - - Inesistente" << endl;
   cout << "User Experience Designer: - - - Per la sua incolumita', non disponibile" << endl;
   cout << "Code Tester:- - - - - - - - - - Carletti Stefano" << endl;
   cout << "Quality Assurance Specialist: - Nessuno" << endl;
   cout << "COPYRIGHT - Nessuno, perche' siamo poveri" << endl;
   cout << endl;
   PAUSE();
   account();
   return;
}

void impostazioni() {
   int scelta;
   string passwordMaybe, passwordDEBUGMODE="a", passwordOWNERMODE="a";

   titolo("IMPOSTAZIONI", true);

   DEBUG("DebugPassword = " + passwordDEBUGMODE);
   ownerMode? cout << "DebugPassword = " << passwordDEBUGMODE << " | OwnerPassword = " << passwordOWNERMODE << endl : cout << "";
   
   cout << "Che impostazione vorresti modificare?" << endl;
   cout << "- 1: Debug Mode -- " << debugMode << endl;
   cout << "- 2: Owner Mode -- " << ownerMode << endl;
   cout << "- 0: Torna al menu dell'account" << endl;
   cout << "> "; cin >> scelta;

   switch (scelta) {
   case 0:
      PURO("Verrai reindirizzato al menu dell'account");
      account();
      return;
      break;
   case 1:
      CLEAR();
      cout << "Per modificare, inserire la password: "; cin >> passwordMaybe;
      if (passwordMaybe == passwordDEBUGMODE) {
         debugMode = !debugMode;
         PURO("Impostazione modificata con successo");
         impostazioni();
         return;
         break;
      } else {
         ERRORE("Password sbagliata");
         impostazioni();
         return;
         break;
      }
      return;
      break;
   case 2:
      CLEAR();
      cout << "Per modificare, inserire la password: "; cin >> passwordMaybe;
      if (passwordMaybe == passwordOWNERMODE) {
         ownerMode = !ownerMode;
         PURO("Password modificata con successo");
         impostazioni();
         return;
         break;
      } else {
         ERRORE("Password sbagliata");
         impostazioni();
         return;
         break;
      }
      return;
      break;
   default:
      ERRORE("Selezionare un'opzione accettabile!");
      impostazioni();
      return;
      break;
   }
   return;
}

void account() {
   CLEAR();
   cout << "Cosa vorresti visualizzare?" << endl;
   cout << "- 1: Impostazioni" << endl;
   cout << "- 2: Crediti" << endl;
   cout << "- 3: Informazioni" << endl;
   cout << "- 0: Torna al menu principale" << endl;
   cout << ">  "; cin >> sceltaINT;

   switch (sceltaINT) {
   case 1:
      impostazioni();
      return;
      break;
   case 2:
      crediti();
      return;
      break;
   case 3:
      informazioni();
      return;
      break;
   case 0:
      PURO("Verrai reindirizzato al menu principale");
      menuPrincipale();
      return;
      break;
   default:
      ERRORE("Selezionare un'opzione accettabile");
      account();
      return;
      break;
   }
}

void menuPrincipale() {
   titolo("BENVENUTO", true);

   cout << "Cosa vorresti fare di bello in questo programmone?" << endl;
   cout << "- 1: Calcolatrice" << endl;
   cout << "- 2: Conversioni" << endl;
   cout << "- 0: Account" << endl;
   cout << "- 100: Uscire dal programmone" << endl;
   cout << "> "; cin >> sceltaINT;

   switch (sceltaINT) {
   case 1:
      calcolatrice();
      return;
      break;
   case 2:
      conversioni();
      return;
      break;
   case 0:
      account();
      return;
      break;
   case 100:
      PURO("Arrivederci! Torna presto");
      CLEAR();
      return;
      break;
   case 69:
      CLEAR();
      cout << "nice";
      DORMI(300);
      CLEAR();
      menuPrincipale();
      return;
      break;
   default:
      ERRORE("Inserire un'opzione accettabile");
      menuPrincipale();
      return;
      break;
   }
   return;
}

// main
int main() {
   PAUSE();
   menuPrincipale();
   return 0;
}
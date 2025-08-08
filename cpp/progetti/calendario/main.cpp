#include <iostream>
#include <cmath>
#include <limits>
#include <string>
#include <ctime>
#include <fstream>
#include <filesystem>
#include <thread>
#include "lib/json.hpp"

using namespace std;
using json = nlohmann::json;

namespace fs = filesystem;

#ifdef _WIN32
   #ifndef NOMINMAX
   #define NOMINMAX
   #endif
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
   #define OS "linux"
   #define DORMI(periodo) std::this_thread::sleep_for(std::chrono::milliseconds(periodo))
   #define CLEAR() system("clear")
   #define PAUSE() system("read -n 1 -s -r -p \"Premi un tasto per continuare...\"")
#else
   cerr << "ERRORE CATASTROFICO: Non sono riuscito ad identificare il tuo sistema operativo!\n";
   return EXIT_FAILURE;
#endif

// prototipi
void menuPrincipale();
void salva();
void aggiornaImpostazioni();

// variabili globali

bool debugMode, autoSave, deletePastEvents; //DEFAULTS: f, t, t

int sceltaINT;

char sceltaCHAR;

string sceltaSTR, JSON_PATH="n/a";
string giorno, ora, evento, descrizione;

json dati;

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
void ERRORE(string parametro, bool fatale=false) {
   cerr << "/!\\ ERRORE: " << parametro;
   wait();
   cout << endl;
   if (fatale) exit(1); 
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

// automatics

void salvataggioAutomatico() {
   while(autoSave) {
      salva();
      if (debugMode) DEBUG("Salvataggio automtico completato");
      DORMI(30000);
   }
}

void eliminazioneEventiPassati() {
   auto now = chrono::system_clock::now();
   time_t now_time_t = chrono::system_clock::to_time_t(now);

   auto convertInTimeT = [](const string& giorno, const string& ora) -> time_t {
      tm tm_data = {};
      sscanf(giorno.c_str(), "%d-%d-%d", &tm_data.tm_year, &tm_data.tm_mon, &tm_data.tm_mday);

      tm_data.tm_year -= 1900;
      tm_data.tm_mon -= 1;
      sscanf(ora.c_str(), "%d:%d", &tm_data.tm_hour, &tm_data.tm_min);
      tm_data.tm_sec = 0;
      tm_data.tm_isdst = -1;
      return mktime(&tm_data);
   };

   vector<string> giorniDaCancellare;

   for (auto& [giorno, eventiGiorno] : dati.items()) {
      vector<string> orariDaCancellare;

      for (auto& [ora, evento] : eventiGiorno.items()) {
         time_t evento_time = convertInTimeT(giorno, ora);
         if (evento_time < now_time_t) {
            orariDaCancellare.push_back(ora);
         }
      }

      for (const auto& ora : orariDaCancellare) {
         eventiGiorno.erase(ora);
      }

      if (eventiGiorno.empty()) {
         giorniDaCancellare.push_back(giorno);
      }
   }

   for (const auto& g : giorniDaCancellare) {
      dati.erase(g);
   }

   if (!giorniDaCancellare.empty()) {
      salva();
      DEBUG("Eventi passati eliminati automaticamente");
   }
}

// corpo del programma

void getJsonPath() {
   #ifdef _WIN32
      const char* appdata = getenv("APPDATA");
      if (appdata) {
         JSON_PATH = string(appdata) + "\\Calendario\\calendario.json"; // C:\users\$user$\appdata\roaming\calendario\calendario.json
         fs::create_directories(fs::path(JSON_PATH).parent_path());
         INFORMAZIONE("Archivio caricato senza problemi");
      } else {
         ERRORE("Non sono riuscito a caricare l'archivio", true);
      }
   #elif __linux__
      const char* home = getenv("HOME");
      if (home) {
         JSON_PATH = string(home) + "/.config/calendario/calendario.json"; // /home/$user$/.config/calendario/calendario.json
         fs::create_directories(fs::path(JSON_PATH).parent_path());
         INFORMAZIONE("Archivio caricato senza problemi");
      } else {
         ERRORE("Non sono riuscito a caricare l'archivio", true);
      }
   #endif
}

string getOggi() {
   auto oggi = chrono::system_clock::now();
   time_t tempo  = chrono::system_clock::to_time_t(oggi);
   tm localTime;

   #ifdef _WIN32
      localtime_s(&localTime, &tempo);
   #elif __linux__
      localtime_r(&tempo, &localTime);
   #endif
   ostringstream oss;
   oss << put_time(&localTime, "%Y-%m-%d");
   return oss.str();
}

void inizializzaDatabase() {
   if (JSON_PATH == "n/a") {
      ERRORE("Non sono riuscito a trovare l'archivio!", true);
   }

   if (!fs::exists(JSON_PATH)) {
      ofstream file(JSON_PATH);
      file << "{}";
      file.close();
      dati = json::object();
   } else {
      ifstream file(JSON_PATH);
      file >> dati;
      file.close();
   }
   
   if (!dati.contains("impostazioni")) {
      dati["impostazioni"] = {
         {"debugMode", false},
         {"autoSave", true},
         {"deletePastEvents", true}
      };
      salva();
   }

   debugMode = dati["impostazioni"].value("debugMode", false);
   autoSave = dati["impostazioni"].value("autoSave", true);
   deletePastEvents = dati["impostazioni"].value("deletePastEvents", true);

   aggiornaImpostazioni();
}

void salva() {
   ofstream file(JSON_PATH);
   file << dati.dump(4);
   file.close();
}

int getFirstFreeId(const json& dati) {
   int id = 0;

   while (true) {
      bool usato = false;
      for (const auto& [giorno, eventiGiorno] : dati.items()) {
         for (const auto& [ora, evento] : eventiGiorno.items()) {
            if (evento.contains("id") && (evento["id"] == id)) {
               usato = true;
               break;
            }
         }
         if (usato) break;
      }
      if (!usato) return id;
      id++;
   }
}

void aggiornaImpostazioni() {
   dati["impostazioni"]["debugMode"] = debugMode;
   dati["impostazioni"]["autoSave"] = autoSave;
   dati["impostazioni"]["deletePastEvents"] = deletePastEvents;
   salva();
}

void nuovoEvento() {
   titolo("NUOVO EVENTO", true);

   cout << "In che giorno si svolgera' questo evento? (YYYY-MM-GG): "; cin >> giorno; cin.ignore();
   cout << "E a che ora si svolgera'? (HH:MM): "; cin >> ora; cin.ignore();
   cout << "Inserisci il titolo dell'evento:" << endl;
   cout << "> "; getline(cin, evento);
   cout << "Infine, inserisci una descrizione dell'evento:" << endl;
   cout << "> "; getline(cin, descrizione);

   int id = getFirstFreeId(dati);

   dati[giorno][ora] = {
      {"id", id},
      {"titolo", evento},
      {"descrizione", descrizione}
   };

   salva();
   PURO("Evento aggiunto con successo");

   menuPrincipale();
}

void visualizzaEvento() {
   titolo("VISUALIZZA un EVENTO", true);
   cout << "Che giorno vorresti controllare? (YYYY-MM-GG): "; getline(cin, giorno);

   if (!dati.contains(giorno)) {
      PURO("Non c'e' nessun evento in programma per il " + giorno);
      menuPrincipale();
   }

   size_t quanti = dati[giorno].size();

   cout << (quanti == 1? "C'e' " : "Ci sono ") << quanti << (quanti == 1? " evento " : " eventi ") << " per il " << giorno << endl;

   for (auto& [ora, evento] : dati[giorno].items()) {
      string intestazione = evento.value("titolo", "(nessun titolo)");
      string descrizione = evento.value("descrizione", "");

      cout << "[" << ora << "] - " << intestazione << endl;

      if (!descrizione.empty()) {
         cout << "   \\ " << descrizione << endl;
      }
      cout << endl;
   }
   cout << endl << endl;
   PAUSE();
   menuPrincipale();
}

void visualizzaTutto() {
   titolo("VISUALIZZA TUTTI gli EVENTI", true);
   cout << endl;

   if (dati.empty()) {
      PURO("Non ci sono eventi salvati in calendario");
      PAUSE();
      menuPrincipale();
   }

   for (const auto& [giorno, eventiGiorno] : dati.items()) {
      cout << giorno << ":" << endl;
      for (const auto& [ora, evento] : eventiGiorno.items()) {
         string titolo = evento.value("titolo", "[nessun titolo]");
         cout << "   [" << ora << "] - " << titolo << endl;
      }
      cout << endl;
   }

   cout << endl;
   PAUSE();
   menuPrincipale();
}

void eliminaEvento() {
   titolo("ELIMINA un EVENTO", true);

   cout << "Questi sono gli eventi disponibili:" << endl << endl;

   for (const auto& [giorno, eventiGiorno] : dati.items()) {
      cout << giorno << ":" << endl;
      for (const auto& [ora, evento] : eventiGiorno.items()) {
         string titolo = evento.value("titolo", "[nessun titolo]");
         cout << "[" << ora << "] - " << titolo << endl;
      }
   }

   cout << endl << "Inserire il giorno di cui eliminare gli eventi (YYYY-MM-GG): "; getline(cin, giorno);

   if (giorno == "0") {
      PURO("Verrai riportato al menu principale");
      menuPrincipale();
      return;
   }
   if (!dati.contains(giorno)) {
      PURO("Non sono presenti eventi per questo giorno");
      menuPrincipale();
      return;
   }
   
   size_t quanti = dati[giorno].size();

   cout << "Ho trovato " << quanti << (quanti == 1? " evento " : " eventi ") << "per il " << giorno << endl;
   cout << "Vorresti eliminare tutti gli eventi della giornata (1) o solo un orario specifico (2)? "; cin >> sceltaINT;
   cin.ignore();

   if (quanti == 1) {
      dati.erase(giorno);
      salva();
      PURO("Evento eliminato con successo");
      menuPrincipale();
      return;
   }

   switch (sceltaINT) {
   case 1:
      dati.erase(giorno);
      salva();
      PURO("Giornata eliminata con successo");
      break;

   case 2:   
      cout << "Inserisci l'ora dell'evento da eliminare (HH:MM): "; getline(cin, ora);
      if (dati[giorno].contains(ora)) {
         dati[giorno].erase(ora);
      } else {
         ATTENZIONE("Non esiste alcun evento per quest'ora");
         eliminaEvento();
      }
      salva();
      break;
      
   default:
      ATTENZIONE("Inserire un'opzione accettabile");
      eliminaEvento();
      break;
   }
   return;
}

void modificaEvento() {
   titolo("MODIFICA un EVENTO", true);

   int id, idDaModificare;
   string giornoNuovo, oraNuova, titoloNuovo, descrizioeNuova;

   cout << "Questi sono gli eventi attuali:" << endl;
   for (const auto& [giorno, eventiGiorno] : dati.items()) {
      for (const auto& [ora, evento] : eventiGiorno.items()) {
         id = evento.value("id", -1);
         string titolo = evento.value("titolo", "[nessun titolo]");
         cout << "ID: " << id << " | " << giorno << " [" << ora << "] - " << titolo << endl;
      }
   }

   cout << endl << "Inserisci l'ID dell'evento da modificare: "; cin >> idDaModificare; cin.ignore();

   string giornoVecchio, oraVecchia;
   json eventoOriginale;

   for (const auto& [giorno, eventiGiorno] : dati.items()) {
      for (const auto& [ora, evento] : eventiGiorno.items()) {
         if (evento.value("id", -1) == idDaModificare) {
            giornoVecchio = giorno;
            oraVecchia = ora;
            eventoOriginale = evento;
         }
      }
   }

   if (eventoOriginale.empty()) {
      ATTENZIONE("Nessun evento trovato con id " + id);
      menuPrincipale();
      return;
   }

   titolo("modifica", false);

   cout << "Per mantenere il valore attuale, premere INVIO" << endl;

   cout << "Giorno [" << giornoVecchio << "] : "; getline(cin, giornoNuovo);
   if (giornoNuovo.empty()) giornoNuovo = giornoVecchio;

   cout << "Ora [" << oraVecchia << "] : "; getline(cin, oraNuova);
   if (oraNuova.empty()) oraNuova = oraVecchia;

   cout << "Titolo [" << eventoOriginale["titolo"] << "] : "; getline(cin, titoloNuovo);
   if (titoloNuovo.empty()) titoloNuovo = eventoOriginale["titolo"];

   cout << "Descrizione [" << eventoOriginale["descrizione"] << "] : "; getline(cin, descrizioeNuova);
   if (descrizioeNuova.empty()) descrizioeNuova = eventoOriginale["descrizione"];

   if (giornoVecchio != giornoNuovo || oraVecchia != oraNuova) {
      dati[giornoVecchio].erase(oraVecchia);
   }

   dati[giornoNuovo][oraNuova] = {
      {"id", idDaModificare},
      {"titolo", titoloNuovo},
      {"descrizione", descrizioeNuova}
   };

   salva();
   PURO("Evento modificato con successo");
   menuPrincipale();
}

void impostazioni() {
   titolo("INFORMAZIONI", true);

   cout << "Tutti gli eventi passati vengono eliminati automaticamente. Puoi disattivare quest'impostazione qua sotto." << endl;
   cout << "Questo tiene conto dell'ora: elimina gli eventi impostati per stamattina, ma non stasera." << endl << endl;

   titolo("IMPOSTAZIONI", false);

   cout << "Per modificare un impostazione, inserire il rispettivo ID." << endl;
   cout << "'1' indica che l'opzione e' attivata; '0' indica che l'opzione e' disattivata" << endl;
   cout << endl;
   cout << "- 1: debugMode -  -  -  -  -  -  -  -  -  -  -  -  - " << debugMode << endl;
   cout << "- 2: salvataggio automatico   -  -  -  -  -  -  -  - " << autoSave << endl;
   cout << "- 3: Eliminazione automatica degli eventi passati  - " << deletePastEvents << endl;
   cout << "- 0: Torna al menu principale" << endl;
   cout << "> "; cin >> sceltaINT; cin.ignore();

   switch (sceltaINT) {
   case 1:
      debugMode = !debugMode;
      aggiornaImpostazioni();
      impostazioni();
      break;
   case 2:
      autoSave = !autoSave;
      aggiornaImpostazioni();
      impostazioni();
      break;
   case 3:
      deletePastEvents = !deletePastEvents;
      aggiornaImpostazioni();
      impostazioni();
      break;
   case 0:
      PURO("Verrai reindirizzato al menu principale");
      menuPrincipale();
      break;
   default:
      ATTENZIONE("Inserire un'opzione accettabile");
      break;
   }
}

void menuPrincipale() {
   titolo("CALENDARIO TOSTAPANICO", true);

   cout << "Cosa vorresti fare?" << endl;
   cout << "- 1: Creare un nuovo evento" << endl;
   cout << "- 2: Visualizzare gli eventi di una giornata" << endl;
   cout << "- 3: Visualizza tutti gli eventi salvati" << endl;
   cout << "- 4: Modifica un evento" << endl;
   cout << "- 5: Elimina un evento" << endl;
   cout << "- 6: Elimina l'intero archivio" << endl;
   cout << "- 9: Impostazioni" << endl;
   cout << "- 0: Chiudi il calendario" << endl;
   cout << "> "; cin >> sceltaINT; cin.ignore();

   switch (sceltaINT) {
   case 1:
      nuovoEvento();
      break;
   case 2:
      visualizzaEvento();
      break;
   case 3:
      visualizzaTutto();
      break;
   case 4:
      modificaEvento();
      break;
   case 5:
      eliminaEvento();
      break;
   case 6:
      titolo("ELIMINAZIONE TOTALE", true);
      cin.ignore();
      cout << "Sei sicuro di voler eliminare TUTTI gli eventi?" << endl;
      cout << "Questa azione e' IRREVERSIBILE, e gli eventi spariranno per sempre (molto tempo)!";
      cout << "Per eliminare tutto, scrivere 'CAPISCO E VOGLIO ELIMINARE'" << endl;
      cout << "> "; getline(cin, sceltaSTR);

      if (sceltaSTR == "CAPISCO E VOGLIO ELIMINARE") {
         dati = json::object();
         salva();
      }

      menuPrincipale();
      break;
   case 9:
      impostazioni();
      break;
   case 0:
      autoSave = false;
      PURO("Arrivederci, torna presto, il salvataggio e' automatico");
      salva();
      break;
   default:
      ATTENZIONE("Inserire un'opzione accettabile");
      menuPrincipale();
      break;
   }

}

int main() {
   if (debugMode) PAUSE();

   getJsonPath();
   
   inizializzaDatabase();

   if (deletePastEvents) eliminazioneEventiPassati();

   thread salvataggio(salvataggioAutomatico);
   salvataggio.detach();
   
   menuPrincipale();
   return 0;
}
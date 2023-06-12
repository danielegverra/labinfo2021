**DESCRIZIONE MODULI**

*CARTELLA ANALIZZATORE*

ANALIZZATORE: Il modulo "analizzatore" gestisce l'accettazione dei comandi forniti da utente, segnalando anche i possibili errori nella lettura di questi.

*CARTELLA COMANDI*

COMANDI MOVIMENTO: Il modulo "comandi_movimento" gestisce tutti i comandi relativi allo spostamento del giocatore.

COMANDI OGGETTO:  Il modulo "comandi_oggetto" gestisce tutti i comandi che coinvolgono l'utilizzo di oggetti.

COMANDI PARTITA: Il modulo "comandi_partita" contiene tutte le funzioni volte ad uno svolgimento ottimale della partita e che riguardano l'utilizzo del "gioco" più in generale.

SAVE.bin: file binario su cui la partita viene salvata\ da cui viene caricata

*CARTELLA DATI*

GET_SET:  Il modulo "get_set.h" gestisce l'accesso ai campi del tipo di dato "partita"

GLOBALI: Il modulo "globali" gestisce le costanti globali comuni a tutti i moduli.

TIPI_DI_DATO: Il modulo "tipi_di_dato.h" serve per definire i tipi di dato associati alla partita di gioco

*CARTELLA INIZIALIZZAZIONE*

AMBIENTI_DIREZIONE.txt: il file di testo contiene in ordine, per ogni ambiente, nome, identificatore delle varie stanze raggiungibili proseguendo verso nord\sud\ovest\est (in quest'ordine) e gli eventuali oggetti presenti dell'ambiente (se non ci sono oggetti l'id sarà -1, se non si potrà proseguire in una direzione l'id sarà -1, se proseguire in una direzione provoca la perdita di una vita l'id sarà -2)

AMBIENTI.txt: il file di testo contiene in ordine, per ogni ambiente,

INIZIALIZZA: Il modulo "inizializza" gestisce l'inizializzazione del tipo di dato partita ai valori iniziali.

INVENTARIO.txt: il file di testo contiene per ogni oggetto il suo nome e la quantità di tali oggetti in esso a inizio partita

*ESTERNO*

TESORO.txt: contiene la stampa di un disegno raffigurante il tesoro# labinfo2021

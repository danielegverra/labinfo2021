/** 
  * Il modulo "comandi_partita" contiene tutte le funzioni
  * volte ad uno svolgimento ottimale della partita e che riguardano
  * l'utilizzo del "gioco" più in generale.
*/

#ifndef COMANDI_PARTITA_H
#define COMANDI_PARTITA_H

#include "../dati/tipi_di_dato.h"

//la funzione permette di salvare su file la partita così com'è//
void salvare(partita *game);

//la funzione permette di caricare da file la partita così come è stata salvata//
void caricare(partita *game);

// la funzione verifica se l'utente ha risolto l'indovinello, se viene risolto restituisce un booleano con esito positivo
bool verificare_indovinello(partita game);

//la funzione visualizza l'inventario, le vite o i comandi disponibili//
void visualizzare(partita game, int id);

//la funzione stampa la descrizione dell'ambiente in cui il protagonista si trova
void guardare(partita *game);

//la funzione permette di interagire con un personaggio presente nell'ambiente, se ce n'è uno//
void interagire(partita *game);

//stampa l'immagine di un forziere del tesoro subito dopo la vittoria
void stampare_tesoro();

#endif
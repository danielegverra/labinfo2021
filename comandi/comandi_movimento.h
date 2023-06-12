 /** 
  * Il modulo "comandi_movimento" gestisce tutti i comandi
  * relativi allo spostamento del giocatore.
*/

#ifndef COMANDI_MOVIMENTO_H
#define COMANDI_MOVIMENTO_H

#include "../dati/tipi_di_dato.h"

// la funzione modifica la stanza attuale della partita data in input
void salire(partita *game);

// la funzione modifica la stanza attuale della partita data in input
void scendere(partita *game);

//la funzione modifica la stanza attuale della partita data in input a seconda della direzione
void vai(partita *game, int direzione);

//la funzione permette di entrare in un luogo, se disponibile//
void entrare(partita * game, int id);

//la funzione permette di uscire da un luogo chiuso//
void uscire(partita * game);

#endif
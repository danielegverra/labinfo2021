/** 
  * Il modulo "analizzatore" gestisce l'accettazione
  * dei comandi forniti da utente, segnalando anche i possibili errori
  * nella lettura di questi.
*/

#ifndef ANALIZZATORE_H
#define ANALIZZATORE_H

#include <stdbool.h>
#include "../dati/tipi_di_dato.h"


//prende da tastiera l'intera frase
void richiedere_comando(string input);

//divide la frase in 2 parole che vengono controllate da scanner e parser, se c'è stato qualche problema stampa a video un messaggio di errore
void analizzare_comando(partita * game, char input[]);

// controlla che il numero di parole inserite da utente sia consono a quello accettato
bool controllare_struttura (char *input);

// seleziona la prima parola inserita da utente
void prendere_parola_1(char *input, char *parola1);

// seleziona la seconda parola inserita da utente
void prendere_parola_2(char *input, char *parola2);

//gli errori ritrovati vengono passati alla funzione che si occupa di riconoscere l'errore e comunicarlo a utente
void error_mgr(int i, string a, string b);

// controlla che la parola inserita (una per volta) sia accettata dal gioco
int scanner(string parola);

// indirizza le due parole inserite da utente e ne analizza il significato di modo da richiamare la funzione corrispondente
void parser(partita * game, char *parola1, char *parola2);


#endif
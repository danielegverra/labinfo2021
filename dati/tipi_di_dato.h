/** 
  * Il modulo "tipi_di_dato.h" serve per definire
  * i tipi di dato associati alla partita di gioco
  *
*/


#ifndef TIPI_DI_DATO_H
#define TIPI_DI_DATO_H

#include "globali.h"

typedef char string[500];

typedef struct 
{
  char nome_oggetto[MAX_NME];
  int quantita;
} oggetto;

typedef struct 
{
  char descrizione[MAX_DSC];
  char nome_ambiente[MAX_NME];
  int nord;
  int sud;
  int est;
  int ovest;
  int oggetto1;
  int oggetto2;
} stato;

typedef struct 
{
  int n_vite;
  int stanza_attuale;
  oggetto inventario[MAX_OGG];
  stato ambienti[MAX_AMB];
  int n_azioni;
} partita;

#endif

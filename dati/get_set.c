/** 
  * Il modulo "get_set.h" gestisce l'accesso ai campi del
  * tipo di dato "partita"
*/

#include <string.h>
#include "tipi_di_dato.h"

//la funzione restituisce il campo n_vite di game//
int get_n_vite(partita game)
{
  int vite;

  vite = game.n_vite;
  
  return vite;
}

//la funzione setta il nuovo valore del campo n_vite//
void set_n_vite(partita * game, int vite_new)
{
  game->n_vite = vite_new;

  return;
}

//la funzione restituisce il campo stanza_attuale di game//
int get_stanza_attuale(partita game)
{
  int stanza;

  stanza = game.stanza_attuale;
  
  return stanza;
}

//la funzione setta il nuovo valore del campo stanza_attuale//
void set_stanza_attuale(partita * game, int stanza_new)
{
  game->stanza_attuale = stanza_new;

  return;
}

//la funzione restituisce il campo n_azioni di game//
int get_n_azioni(partita *game)
{
int azioni;
azioni=game->n_azioni;
return azioni;
}

//la funzione setta il nuovo valore del campo n_azioni//
void set_n_azioni(partita *game,int azioni_new)
{
  game->n_azioni=azioni_new;
}

//la funzione restituisce il campo nome_oggetto di inventario in posizione id//
void get_nome_oggetto(partita*game,int id,char*oggetto)
{
  strcpy(oggetto,game->inventario[id].nome_oggetto);
}

//la funzione setta il campo nome_oggetto di inventario in posizione id//
void set_nome_oggetto(partita*game,int id,char*oggetto_new)
{
  strcpy(game->inventario[id].nome_oggetto,oggetto_new);
}

//la funzione restituisce il campo quantità dell'oggetto id//
int get_quantita_oggetto(partita game, int id)
{
  int quantita;
  quantita=game.inventario[id].quantita;
  return quantita;
}

//la funzione setta il valore del campo quantità di oggetto id a "quantita_new"//
void set_quantita_oggetto(partita *game, int id, int quantita_new)
{
  game->inventario[id].quantita=quantita_new;
  return;
}

//la funzione restituisce il campo descrizione dell'ambiente id, nella stringa "descrizione"//
void get_descrizione_ambiente(partita game, int id, char *descrizione)
{
  strcpy(descrizione, game.ambienti[id].descrizione);
  return;
}

//la funzione setta il contenuto di descrizione_ambiente uguale al contenuto di "descrizione_new"//
void set_descrizione_ambiente(partita *game, int id, char *descrizione_new)
{
  strcpy(game->ambienti[id].descrizione, descrizione_new);
  game->ambienti[id].descrizione[strlen(descrizione_new)]='\n';
  game->ambienti[id].descrizione[strlen(descrizione_new)+1]='\0';
  return;
}

//la funzione restituisce il campo nome_ambiente dell'ambiente id, nella stringa "nome"//
void get_nome_ambiente(partita game, int id, char *nome)
{
  strcpy(nome, game.ambienti[id].nome_ambiente);
  return;
}

//la funzione setta contenuto di nome_ambiente al contenuto di "nome_new"//
void set_nome_ambiente(partita *game, int id, char *nome_new)
{
  strcpy(game->ambienti[id].nome_ambiente, nome_new);
  return;
}

//la funzione restituisce l'id dell'ambiente che si trova idealmente a nord dell'ambiente in cui si trova il giocatore//
int get_nord(partita game, int id)
{
  int destinazione;

  destinazione= game.ambienti[id].nord;
  return destinazione;
}

//la funzione imposta l'id dell'ambiente che si trova idealmente a nord dell'ambiente in cui si trova il giocatore//
void set_nord(partita *game, int id, int new_nord)
{
  game->ambienti[id].nord= new_nord;
}

//la funzione restituisce l'id dell'ambiente che si trova idealmente a sud dell'ambiente in cui si trova il giocatore//
int get_sud(partita game, int id)
{
  int destinazione;

  destinazione= game.ambienti[id].sud;
  return destinazione;
}

//la funzione imposta l'id dell'ambiente che si trova idealmente a sud dell'ambiente in cui si trova il giocatore//
void set_sud(partita *game, int id, int new_sud)
{
  game->ambienti[id].sud= new_sud;
}

//la funzione restituisce l'id dell'ambiente che si trova idealmente a est dell'ambiente in cui si trova il giocatore//
int get_est(partita game, int id)
{
  int destinazione;

  destinazione= game.ambienti[id].est;
  return destinazione;
}

//la funzione imposta l'id dell'ambiente che si trova idealmente a est dell'ambiente in cui si trova il giocatore//
void set_est(partita *game, int id, int new_est)
{
  game->ambienti[id].est= new_est;
}

//la funzione restituisce l'id dell'ambiente che si trova idealmente a ovest dell'ambiente in cui si trova il giocatore//
int get_ovest(partita game, int id)
{
  int destinazione;
  destinazione = game.ambienti[id].ovest;
  return destinazione;
}

//la funzione imposta l'id dell'ambiente che si trova idealmente a ovest dell'ambiente in cui si trova il giocatore//
void set_ovest(partita *game, int id, int destinazione_new)
{
  game->ambienti[id].ovest = destinazione_new;
  return;
}

//la funzione restituisce il campo oggetto1 del campo ambienti in posizione id di game//
int get_oggetto1(partita game, int id)
{
  int oggetto;
  oggetto = game.ambienti[id].oggetto1;
  return oggetto;
}

//la funzione setta il campo oggetto1 del campo ambienti in posizione id di game//
void set_oggetto1(partita *game, int id, int oggetto1_new)
{
  game->ambienti[id].oggetto1 = oggetto1_new;
  return;
}

//la funzione restituisce il campo oggetto2 del campo ambienti in posizione id di game//
int get_oggetto2(partita game, int id)
{
  int oggetto;
  oggetto = game.ambienti[id].oggetto2;
  return oggetto;
}

//la funzione setta il campo oggetto1 del campo ambienti in posizione id di game//
void set_oggetto2(partita *game, int id, int oggetto2_new)
{
  game->ambienti[id].oggetto2 = oggetto2_new;
  return;
}


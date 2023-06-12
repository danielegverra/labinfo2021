/** 
  * Il modulo "comandi_oggetto" gestisce tutti i comandi
  * che coinvolgono l'utilizzo di oggetti.
*/

#ifndef COMANDI_OGGETTO_H
#define COMANDI_OGGETTO_H

#include "../dati/tipi_di_dato.h"

//la funzione permette di attaccare il gigante, personaggio dell'ambiente 34, ma, qualsiasi arma il giocatore scelga per attaccarlo, gli farà perdere una vita
void colpire (partita *game);

//la funzione verifica se nella partita passata in input l'arco ha le frecce incendiate e se si trova nella stanza giusta e in caso positivo fa vincere il personaggio
void scoccare(partita *game, int id);

//la funzione modifica lo stato dell'oggetto id nell'inventario solo se questo è uguale alla posizione del mantello
void indossare(partita *game, int id);

// la funzione inserisce l'oggetto pagnotta nell'inventario, inoltre eseguire questa azione comporta un cambio di ambiente
void rubare_pagnotta(partita *game);

//la funzione comporta lo sblocco di un ambiente, in particolare dall'ambiente 6 sarà possibile passare all'ambiente 8
void forzare_finestra(partita *game);

//la funzione permette di prendere un oggetto dall'ambiente in cui ci si trova, questo verrà aggiunto all'inventario
void prendere_oggetto(partita *game, int id);

//la funzione permette di mangiare un oggetto, se disponibile nello zaino//
void mangiare(partita * game);

//la funzione consente di bere la pozione, se disponibile//
void bere(partita * game);

//permette di accendere determinati oggetti in particolari situazioni di gioco//
void accendere(partita *game,int id);

//permette di suonare determinati oggetti in particolari situazioni di gioco//
void suonare(partita *game);

//questa funzione spinge l'oggetto fisso "libro", se nella stanza corretta//
void spingere(partita *game);

//questa funzione incastra l'oggetto "elsa", se nella stanza corretta//
void incastrare(partita *game);

//la funzione apre un oggetto fisso, se è possibile aprirlo//
void aprire(partita *game, int id);

//la funzione chiude un oggetto fisso, se è possibile chiuderlo//
void chiudere(partita *game, int id);

#endif
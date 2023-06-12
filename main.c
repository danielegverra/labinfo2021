/**                MAGICA AVVENTURA TESTUALE 
  *       (di Guerra Daniele, De Santis Ugo Gabriele,
  *   Frascella Adriana, Lassandro Nicola e Castano Matteo)
  *
  *  *******************************************************
  *
  *  Avventura testuale realizzata tra Marzo e Giugno 2021,
  *  terminata nella prima versione il 07 / 06 / 2021 .
  *
  *          
  *
*/

#include <stdio.h>
#include <stdlib.h>

#include "dati/tipi_di_dato.h"
#include "dati/get_set.h"
#include "dati/globali.h"
#include "analizzatore/analizzatore.h"
#include "comandi/comandi_partita.h"
#include "comandi/comandi_movimento.h"
#include "comandi/comandi_oggetto.h"
#include "inizializzazione/inizializza.h"



int main(void) 
{
  
  char input[MAX_CMD*2];
  partita game;
  char nome[MAX_NME];
  
  //inizializzazione della partita
  inizializzare(&game);
  
  //intro del gioco
  printf("\n-----BENVENUTO NEL NOSTRO GIOCO!-----\n\n");
  printf("N.B. Se hai difficoltà puoi consultare l'elenco dei comandi scrivendo 'visualizza comandi'.\n\n");
  printf("Navigavi con i tuoi compagni in mare aperto, improvvisamente un lampo squarcia il cielo e la tempesta incalza. Lottate contro il vento che tende le vele causandone un movimento duro, incontrollato … l’attrezzatura viene violentemente trasportata da una fiancata all’altra della nave, i tuoi compagni si feriscono così provi a prendere in mano la situazione ma è troppo tardi… il boma della vela principale ti colpisce trascinandoti in acqua… non riesci più a lottare… tutto si fa nero e ti abbandoni alle onde…\n\n");
  
  //stampa il nome e la descizione del luogo iniziale
  get_nome_ambiente(game, get_stanza_attuale(game), nome);
  printf("\n\n%s", nome);
  guardare(&game);

  //ciclo di esecuzione dei comandi
  while(get_n_vite(game) > 0  &&  get_stanza_attuale(game) < MAX_AMB-1)
  {
    int ambiente = get_stanza_attuale(game);
    
    richiedere_comando(input);
    analizzare_comando(&game, input);

    //se ci siamo spostati stampa il nuovo ambiente
    if(get_stanza_attuale(game)!= ambiente)
    {
      get_nome_ambiente(game, get_stanza_attuale(game), nome);
      printf("\n%s", nome);
      guardare(&game);
    }
    set_n_azioni(&game, get_n_azioni(&game)+1); //incremento n_azioni//
  }

  //messaggio di fine gioco se siamo morti o vivi
  if(get_n_vite(game) <= 0)
  {
    printf("\n\nHai perso tutte le vite! Ritenta, sarai più fortunato.");
  }
  else
  {
    printf("\n\n'Ho cercato a lungo un degno successore per il mio tesoro... non pensavo di riuscire a trovarne uno, avevo perso ogni speranza... ma quando ho visto i tuoi occhi sinceri e furbi ho capito che in te c'era qualcosa di speciale. Sono più di 300 anni che custodisco questo tesoro, racchiude infatti in sè l'essenza dell'isola e tutte le sue ricchezze. Più volte dei barbari hanno tentato di rubare il tesoro per avere in pugno la prosperità dell'isola e regnare sui magici abitanti del posto ma per fortuna ora sei arrivato tu e tutto questo... ora è tuo! Mi raccomando prenditene cura!\n'");
    printf("\n\nHai vinto!\n\n**Il tuo punteggio è : %d / 1000 **\n\n", 1700-(get_n_azioni(&game)*10));

    stampare_tesoro();
  }
  
  return 0;
}



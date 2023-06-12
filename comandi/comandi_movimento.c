/** 
  * Il modulo "comandi_movimento" gestisce tutti i comandi
  * relativi allo spostamento del giocatore.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "../dati/tipi_di_dato.h"
#include "../dati/get_set.h"

// la funzione modifica la stanza attuale della partita data in input
void salire(partita *game)
{
  int stanza;
  stanza=get_stanza_attuale(*game);

  if (stanza==9 && get_quantita_oggetto(*game, 5)==1)
  {
    printf("\nStai salendo le scale...\nHai raggiunto il piano superiore della torre!\n");
    set_stanza_attuale(game, 8);
  } else if (stanza==9 && get_quantita_oggetto(*game, 5)==0)
  {
    printf("\nNon mi sembra un'idea saggia, questo posto è pieno di guardie!\n");
  } else if (stanza==5)
  {
    printf("\nStai salendo sull'albero!");
    set_stanza_attuale(game, 6);
  } else if (stanza==22 && get_quantita_oggetto(*game, 9)==1)
  {
    printf("\nPrima di poter uscire dal lago, dovresti RACCOGLIERE qualcosa!\n");
  } else if (stanza==22 && get_quantita_oggetto(*game, 9)==2)
  {
    printf("\nStai salendo in superficie!\nSei arrivato sull’altra sponda del lago, da qui non potrai più tornare indietro\n");
    set_stanza_attuale(game, 23);
  }
  return;
}

// la funzione modifica la stanza attuale della partita data in input
void scendere(partita *game)
{
  int stanza;
  stanza=get_stanza_attuale(*game);

  if (stanza==21)
  {
    printf("\nStai scendendo all'interno del lago, qualcosa di mistico potrebbe accadere!\nQualcosa nella borsa sta cercando di uscire, sta cercando di trascinarti verso il fondo...\n");
    set_stanza_attuale(game, 22);

  } else if (stanza==8)
  {
    printf("\nStai scendendo le scale...\nSei arrivato al piano inferiore della torre.\n");
    set_stanza_attuale(game, 9);
  } else
  {
    printf("\nNon puoi scendere qui.\n");
  }
  return;
}

//la funzione modifica la stanza attuale della partita data in input a seconda della direzione
void vai(partita *game, int direzione)
{
  if (direzione==0) //nord
  {
    if (get_nord(*game, get_stanza_attuale(*game))>-1)
    {
      set_stanza_attuale(game, get_nord(*game, get_stanza_attuale(*game)));
    }
    else if (get_nord(*game, get_stanza_attuale(*game))==-2) 
    {
      printf("\nQuesto luogo era troppo pericoloso per le tue capacità, hai perso una vita!");
      set_n_vite(game, get_n_vite(*game)-1);
    } else 
    {
      printf("\nNon puoi procedere in questa direzione!");
    }
  }
  else if (direzione==3) //sud
  {
    if (get_sud(*game, get_stanza_attuale(*game))>-1)
    {
      set_stanza_attuale(game, get_sud(*game, get_stanza_attuale(*game)));
    }
    else if (get_sud(*game, get_stanza_attuale(*game))==-2) 
    {
      printf("\nQuesto luogo era troppo pericoloso per le tue capacità, hai perso una vita!");
      set_n_vite(game, get_n_vite(*game)-1);
    } else 
    {
      printf("\nNon puoi procedere in questa direzione!");
    }
  }
  else if (direzione==1) //est
  {
    if (get_est(*game, get_stanza_attuale(*game))>-1)
    {
      set_stanza_attuale(game, get_est(*game, get_stanza_attuale(*game)));
    } 
    else if (get_est(*game, get_stanza_attuale(*game))==-2) 
    {
      printf("\nQuesto luogo era troppo pericoloso per le tue capacità, hai perso una vita!");
      set_n_vite(game, get_n_vite(*game)-1);
    } else 
    {
      printf("\nNon puoi procedere in questa direzione!");
    }
  }
  else  if (direzione==2) //ovest
  {
    if (get_ovest(*game, get_stanza_attuale(*game))>-1)
    {
      set_stanza_attuale(game, get_ovest(*game, get_stanza_attuale(*game)));
    }
    else if (get_ovest(*game, get_stanza_attuale(*game))==-2) 
    {
      printf("\nQuesto luogo era troppo pericoloso per le tue capacità, hai perso una vita!");
      set_n_vite(game, get_n_vite(*game)-1);
    } else 
    {
      printf("\nNon puoi procedere in questa direzione!");
    }
  }

  return;
}

//la funzione permette di entrare in un luogo, se disponibile//
void entrare(partita * game, int id)
{
  if(id == 0  && get_stanza_attuale(*game) == 27) //bazar-villaggio//
  {
    if(get_quantita_oggetto(*game, 1)==0) //se non hai l'arco//
    {
      printf("\nIl bazar è pieno di gente, non puoi entrarci ora.");
    } else 
    {
      set_stanza_attuale(game, 32); //accesso al bazar//
    }
  } else
  {
    if(id == 1  && get_stanza_attuale(*game) == 27) //taverna-villaggio//
    {
      if(get_quantita_oggetto(*game, 1)==0) //se non hai l'arco//
      {
        set_stanza_attuale(game, 28); //accesso alla taverna//
        set_descrizione_ambiente(game, 27, "Che strano villaggio, le numerose case sono molto più basse del normale. In giro non si vede nessuno, ma si sentono delle voci provenire da due strutture: un bazar e una taverna, in particolare quest'ultimo sembra molto affollato...");
      } else 
      {
        printf("\nIl passaggio è bloccato dalla folla.");
      }
    } else
    {
      if(id == 2  && get_stanza_attuale(*game) == 16) //casetta-entrataforesta//
      {
        set_stanza_attuale(game, 17);
      } else
      {
        if(id == 3  && get_stanza_attuale(*game) == 25) //capanna-percorso3//
        {
          set_stanza_attuale(game, 26);
        } else
        {
          if(id == 4  && get_stanza_attuale(*game) == 20) //lago-riva1//
          {
            if(get_quantita_oggetto(*game, 7) == -4) //pozione bevuta//
            {
              set_stanza_attuale(game, 21);
            } else
            {
              printf("\nPotresti entrare qui solamente se tu fossi capace di respirare sott'acqua.");
            }
          } else
          {
            printf("\nNon c'è nessun luogo di questo tipo nei paraggi.");
          }
        }
      }
    }
  }

  return;
}

//la funzione permette di uscire da un luogo chiuso//
void uscire(partita * game)
{
  if(get_stanza_attuale(*game) == 28)  //taverna//
  {
    if(get_nord(*game, 2) == -1)
    {
      set_quantita_oggetto(game, 1, 1); //arco con frecce//
      set_stanza_attuale(game, 30); //campo di addestramento//
      printf("\nDecidi di uscire dalla taverna e Mortimer ti segue... 'Auch... Ehi, attento a dove cammini, mi hai fatto male!'\nA quel punto Mortimer si scusa al posto tuo con lo gnomo e gli chiede informazioni su Amelia.\n'Come dici? Cerchi Amelia? Forse la puoi trovare al CAMPO DI ADDESTRAMENTO, è lì che spesso allena i suoi allievi\nse vuoi ti ci accompagno...'\n...\n'Eccoci arrivati! Guarda lì, quello è l'allenatore, braccio destro di Amelia, ti potrà dare maggiori informazioni.'\nVi avvicinate all'allenatore e Mortimer gli chiede dove Amelia si trovi. L'elfo risponde di aver visto Amelia andar via poco prima e vi dice di cercarla nel suo BAZAR al villaggio. Prima di lasciarvi andare, ti consegna un 'arco con frecce' da consegnare ad Amelia.\n (arco con frecce è stato aggiunto all'inventario)\n ");
    } else
    {
      printf("\nPrima di andartene potrebbe esserti utile interagire con l'uomo misterioso...");
    }
  } else
  {
    if(get_stanza_attuale(*game) == 32)  //bazar//
    {
      set_stanza_attuale(game, 27); //villaggio//
    } else
    {
      if(get_stanza_attuale(*game) == 17)  //casetta
      {
        set_stanza_attuale(game, 16); //entrata foresta//
      } else
      {
        if(get_stanza_attuale(*game) == 26)  //capanna//
        {
          set_stanza_attuale(game, 25); //percorso3//
        } else
        {
          if(get_stanza_attuale(*game) == 22)  //profondità lago//
          {
            if(get_quantita_oggetto(*game, 9)==2) //se hai due talismani//
            {
              set_stanza_attuale(game, 23); //riva2//
              printf("\nOra il lago si è gelato, sei sull'altra riva.");
            } else
            {
              printf("\nDovresti prima RACCOGLIERE qualcosa sul fondo del lago.");
            }
          } else
          {
            printf("\nNon sei in un posto da cui puoi uscire.");
          }
        }
      }
    }
  }

  return;
}
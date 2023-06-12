/** 
  * Il modulo "comandi_oggetto" gestisce tutti i comandi
  * che coinvolgono l'utilizzo di oggetti.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../dati/tipi_di_dato.h"
#include "../dati/get_set.h"


/*la funzione permette di attaccare il gigante, personaggio dell'ambiente 34, ma, qualsiasi arma il giocatore
* scelga per attaccaro, gli farà perdere una vita
*/
void colpire (partita *game)
{
  char arma[MAX_NME];
  
  if(get_stanza_attuale(*game) == 34) // arena sotterranea
  { 
    printf("\nCon cosa vuoi colpirlo? Con 'arco' o con 'spada'?\n\n");
    scanf("%s", arma);
    while (strcmp(arma, "arco") != 0 && strcmp(arma, "spada") != 0)
    {
      printf("\n\nQuesto oggetto non può essere utilizzato con questo comando, con cosa vuoi colpirlo?\n\n");
      scanf("%s", arma);
    }
    set_n_vite(game, get_n_vite(*game)-1);
    printf("\nNon è stata la scelta giusta, il ciclope non è stato danneggiato dal colpo,\nsi è infuriato e ti ha schiacciato con la sua mazza.\nHai perso una vita… riprova diversamente.");
  }
  else
  {
    printf("\nNon è possibile utilizzare questo comando al momento.");
  }

  return;
}

//la funzione verifica se nella partita passata in input l'arco ha le frecce incendiate e se si trova nella stanza giusta e in caso positivo fa vincere il personaggio
void scoccare(partita *game, int id)
{
  int stato;
  int stanza;

  if (id==0)
  {
    stato=get_quantita_oggetto(*game, 1);
    stanza=get_stanza_attuale(*game);

    if (stato==-2 && stanza==34)
    {
      printf("\nCOMPLIMENTI!!!\nHai ucciso il ciclope e hai ottenuto il tesoro nascosto!");
      set_stanza_attuale(game, 35);
    } else if (stanza!=34)
    {
      printf("\nNon puoi scoccare le frecce in questo momento!");
    } else 
    {
      printf("\nDevi prima incendiare le frecce!");
    }
  }
  return;
}

//la funzione modifica lo stato dell'oggetto id nell'inventario solo se questo è uguale alla posizione del mantello
void indossare(partita *game, int id)
{

  if (id==0)
  {
    if (get_quantita_oggetto(*game, 4)==1)
    {
      printf("\nHai deciso di indossare il mantello, adesso sarai invisibile alle guardie, ma potrai comunque essere visto da personaggi con abilità magiche!");
      set_quantita_oggetto(game, 4, -3);
      set_sud(game, 7, 9);
    } else if (get_quantita_oggetto(*game, 4)==-3)
    {
      printf("\nHai già indossato il mantello");
    } else 
    {
      printf("\nNon hai nessun mantello");
    }
  }
  return;
}

// la funzione inserisce l'oggetto pagnotta nell'inventario, inoltre eseguire questa azione comporta un cambio di ambiente
void rubare_pagnotta(partita *game)
{
  if (get_stanza_attuale(*game) == 3)
  {
    set_oggetto1(game, 3, -1); // tolgo la pagnotta dall'ambiente bancarella
    set_quantita_oggetto(game, 10, 1); // aggiungo pagnotta all'inventario
    printf("\nOh no, sei stato scoperto...\nIl panettiere sta chiamando le guardie...\nCorri facendoti spazio tra la gente del villaggio finchè, improvvisamente, qualcuno ti afferra il braccio, tirandoti via in un vicolo ombroso...\n'Andiamo, allontaniamoci di qui! Presto!'\n");
    set_stanza_attuale(game, 4); // passo all'ambiente successivo
  }
  else
  {
    printf("\nNon c'e' nulla da rubare qui.");
  }

  return;
}

// la funzione comporta lo sblocco di un ambiente, in particolare dall'ambiente 6 sarà possibile passare all'ambiente 8
void forzare_finestra(partita *game)
{
  if(get_stanza_attuale(*game) == 6) //controllo che l'ambiente supporti il comando
  {
    printf("\nOra la finestra è aperta, per fortuna avevi con te quel coltello!\nStai entrando all'interno della torre.\n");
    set_stanza_attuale(game, 8);
  }
  else 
  {
    printf("\nNon c’è alcuna finestra da forzare!");
  }

  return;
}

//la funzione permette di prendere un oggetto dall'ambiente in cui ci si trova, questo verrà aggiunto all'inventario
void prendere_oggetto(partita *game, int id)
{
  if (get_oggetto1(*game, get_stanza_attuale(*game))==id || get_oggetto2(*game, get_stanza_attuale(*game))==id)
  {
    set_quantita_oggetto(game, id, get_quantita_oggetto(*game, id)+1);
    if(get_oggetto1(*game, get_stanza_attuale(*game))==id)
    {
      set_oggetto1(game, get_stanza_attuale(*game), -1);
      printf("\nPreso!\n");
      if(get_stanza_attuale(*game) == 1)
      {
        printf("\nI resti del relitto sono crollati, non si può più prendere l'altro oggetto.\n");
        set_oggetto2(game, get_stanza_attuale(*game), -1);
        set_stanza_attuale(game, 0);
        set_nord(game, get_stanza_attuale(*game), -1);
        set_sud(game, get_stanza_attuale(*game), 2);
        set_descrizione_ambiente(game, 0, "\nLa nave ormai è completamente distrutta per fortuna sei riuscito a recuperare del materiale... l'ambiente intorno è molto boscoso ma, in lontananza verso SUD, riesci a vedere una TORRE...");
      }
      if(get_stanza_attuale(*game) == 14)
      {
        printf("\nIl passaggio è crollato e sei fuggito appena in tempo...\n'Fiuuu..., c'è mancato veramente poco.\nMenomale che ora sono in salvo! Chissà dove mi trovo...'\n");
        set_stanza_attuale(game, 15);
      }
    }
    else
    {
      set_oggetto2(game, get_stanza_attuale(*game), -1);
      printf("\nPreso!");
      if(get_stanza_attuale(*game) == 1)
      {
        printf("\nI resti del relitto sono crollati, non si può più prendere l'altro oggetto.\n");
        set_oggetto1(game, get_stanza_attuale(*game), -1);
        set_stanza_attuale(game, 0);
        set_nord(game, get_stanza_attuale(*game), -1);
        set_sud(game, get_stanza_attuale(*game), 2);
        set_descrizione_ambiente(game, 0, "La nave ormai è completamente distrutta per fortuna sei riuscito a recuperare del materiale... l'ambiente intorno è molto boscoso ma, in lontananza verso SUD, riesci a vedere una TORRE...");
      }
      if(get_stanza_attuale(*game) == 14)
      {
        printf("\nIl passaggio è crollato e sei fuggito appena in tempo...\n 'Fiuuu..., c'è mancato veramente poco.\nMenomale che ora sono in salvo! Chissà dove mi trovo...'\n");
        set_stanza_attuale(game, 15);
      }
    }
  }
  else
  {
    printf("Non c'è niente del genere qui.\n");
  }
  
  return;
}

//la funzione permette di mangiare un oggetto, se disponibile nello zaino//
void mangiare(partita * game)
{
  if(get_quantita_oggetto(*game, 15) == 1) //carne//
  {
    set_quantita_oggetto(game, 15, 0);
    printf("\nHai mangiato la carne, era molto gustosa\nHai guadagnato una vita.");
    set_n_vite(game, get_n_vite(*game)+1);
  } else
  {
    if(get_quantita_oggetto(*game, 10) == 1  &&  get_stanza_attuale(*game) == 4) //pagnotta e viale//
    {
      printf("\n'Per bacco, non mi sono ancora presentato! Il mio nome e' Mortimer, abito su quest'isola da tanti anni, tu cosa ci fai qui?' \n...\n'Caspita, un naufragio... sara' stato terribile ma qualcosa mi dice che la sfida che sto per proporti ti solleverà il morale! Si vocifera che su quest'isola sia stato nascosto un preziosissimo tesoro, nessuno sa per certo dove si trovi ma molti ritengono sia stato nascosto nelle segrete del castello più a sud... Come dici? Sei davvero interessato? Ma e' fantastico, prima di andare però vediamo cosa hai con te...'");
      set_quantita_oggetto(game, 10, 0);
      if(get_quantita_oggetto(*game, 4) != 0)  //se hai il mantello//
      {
        printf("\n'WOW! Questo antico mantello mi ricorda qualcosa... forse dovresti provare ad indossarlo'");
        set_sud(game, 4, 7); //androne della torre//
      } else
      {
        printf("\n'WOW! Un coltello da caccia, spero possa tornarti utile...");
        set_sud(game, 4, 5); //CORTILE//
      }
      printf("\nOra devo andare, ti lascio questa chiave...'\n(chiave è stato aggiunto all'inventario)\n'Ma mi raccomando... raggiungi la torre!'");
      set_quantita_oggetto(game, 8, 1);
    } else
    {
      printf("\nNon hai nulla da mangiare, ma non hai molta fame...");
    }
  } 

  return;
}

//la funzione consente di bere la pozione, se disponibile//
void bere(partita * game)
{
  if(get_quantita_oggetto(*game, 7) == -4)
  {
    printf("\nLa pozione è già stata bevuta.");
  } else
  {
    if(get_quantita_oggetto(*game, 7) == 1)
    {
      set_quantita_oggetto(game,7,-4);
      printf("\nHai bevuto la pozione, sembra che questa ti abbia dato la capacità di respirare sott’acqua!");
    } else
    {
      printf("\nNon hai nulla da bere al momento...");
    }
  }

  return;
}

//permette di accendere determinati oggetti in particolari situazioni di gioco//
void accendere(partita *game,int id)
{
  int stanza=get_stanza_attuale(*game);
  if(id==0) //lanterna
  {
    if(get_quantita_oggetto(*game,0)==1)
    {
      set_quantita_oggetto(game,0,-1);
      printf("\nHai acceso la lanterna!");
      if(get_quantita_oggetto(*game, 8) == 0)
      {
        set_est(game, 9, 11);
        set_descrizione_ambiente(game, 9, "'Eccomi nel cuore della torre' pensi tra te e te... procedendo a OVEST sembra possibile raggiungere un altro ambiente mentre a EST vedi una stanza, è molto buia, ma con la lanterna non dovrebbe essere un problema.");
      }
    }
    else if(get_quantita_oggetto(*game,0)==-1)
    {
      printf("\nLa lanterna è gia accesa!");
    }
    else
    {
      printf("\nNon sembri essere in possesso della lanterna.");
    }
  }
  else if(id==1) //arco
  {
    if (get_stanza_attuale(*game)==34)
    {
      set_quantita_oggetto(game,1,-2);
      printf("\nHai incendiato le frecce!");
    }
    else if(get_stanza_attuale(*game)!=34)
    {
      printf("\nC'è un tempo e un luogo per ogni cosa.");
    }
  }
}

//permette di suonare determinati oggetti in particolari situazioni di gioco//
void suonare(partita *game)
{
  int stanza,stato;
  stanza=get_stanza_attuale(*game);
  stato=get_quantita_oggetto(*game, 6);
  if (stanza!=31 && stato==1)
    {
       printf("\nNon puoi farlo in questo posto.");
     }
  else if (stanza==31 && stato ==1) // grotta del drago con oggetto cetra
  {
    printf ("\nIl drago si è addormentato, potrebbe essere un’ottima occasione per prendere una squama.");
    set_quantita_oggetto(game, 6, -5);
    set_oggetto1(game, 31, 16);
    set_descrizione_ambiente(game, 31, "L'odore di zolfo è super penetrante... il drago sta dormendo ma sarebbe meglio non procedere in questa direzione... potresti svegliarlo. A EST c'è l'uscita della GROTTA.");
    set_est(game, 31, 29);
  }
  else if (stanza!=31 && stato!=1)
  {
    printf ("\nNon puoi usare questo comando, non hai strumenti musicali con te!");
  }
  else if (stanza==31 && stato!=1)
  {
    printf ("\nHai già suonato la cetra, ora è rotta...");
  }
}

//questa funzione spinge l'oggetto fisso "libro", se nella stanza corretta//
void spingere(partita *game)
{
  if(get_stanza_attuale(*game) == 11)
  {
    printf("\nOra tutti i libri sono ben allineati, la libreria si è spostata da sola mostrando, alle sue spalle, un varco che da accesso ad un sottopassaggio (a SUD).");
    set_sud(game, get_stanza_attuale(*game), 12);
    set_descrizione_ambiente(game, 11, "'Questa stanza è davvero buia... wow l'antica libreria (SUD) nascondeva un passaggio segreto alle sue spalle'");
  } else {
    printf("\nNon c'è niente qui che si possa spingere.");
  }

  return;
}

//questa funzione incastra l'oggetto "elsa", se nella stanza corretta//
void incastrare(partita *game)
{
  if(get_stanza_attuale(*game) == 33)
  {
    if(get_quantita_oggetto(*game, 3) == 1)
    {
      printf("\nL'elsa si è incastrata perfettamente all'interno dell'altare, è il momento di leggere la pergamena.\n\n**CI FU UN TEMPO IN CUI GLI DEI VIVEVANO NEL CENTRO DELLA TERRA, GLI UOMINI LI TEMEVANO E OGNI ANNO PORTAVANO LORO DONI IN CAMBIO DI PROSPERITA'. UN GIORNO UNO DEGLI ABITANTI DECISE DI INGANNARE GLI DEI DONANDO LORO ALCUNI PRODOTTI RUBATI DAL LORO REGNO. HANNIBAL, IL RE DEGLI DEI, SI ACCORSE DELL'IMBROGLIO E DECISE DI TRASFORMARE QUELL'UOMO IN UN CICLOPE DESTINATO A RIMANERE ALLA GUARDIA DEL CENTRO DELLA TERRA, SARA' DUNQUE DESTINATO A VIVERE NEL CUORE DELLA TERRA CIRCONDATO DALLE FIAMME... NULLA POTRA' SCALFIRLO TRANNE L'ELEMENTO CHE CARATTERIZZA LA TERRA DOVE VIVE**\n\nNel terreno si apre un varco che ti risucchia al suo interno...\nUna volta in fondo vedi una strana figura dall'aria minacciosa!\nC'è una spada sul terreno, decidi di prenderla per poterti difendere.\n\n(La spada è stata aggiunta all'inventario.)");
      set_stanza_attuale(game, 34);
      set_quantita_oggetto(game, 3, 0);
      set_quantita_oggetto(game, 2, 1);
    } else {
      printf("\nNon sembra che tu abbia l'oggetto giusto.");
    }
  } else {
    printf("\nNon c'è niente qui che si possa incastrare.");
  }
  
  return;
}

//la funzione apre un oggetto fisso, se è possibile aprirlo//
void aprire(partita *game, int id)
{
  if(id == 0) //porta
  {
    if(get_stanza_attuale(*game) == 9)
    {
      if(get_quantita_oggetto(*game, 8) == 1)
      {
        printf("\nHai usato la chiave per aprire la porta, ora la porta è aperta.");
        if(get_quantita_oggetto(*game, 0) == -1)
        {
          set_est(game, get_stanza_attuale(*game), 11);
          set_descrizione_ambiente(game, 9, "'Eccomi nel cuore della torre' pensi tra te e te... procedendo a OVEST sembra possibile raggiungere un altro ambiente mentre a EST vedi una stanza, è molto buia, ma con la lanterna non dovrebbe essere un problema.");
        }
        else
        {
          set_descrizione_ambiente(game, 9, "'Eccomi nel cuore della torre' pensi tra te e te... procedendo a OVEST sembra possibile raggiungere un altro ambiente mentre a EST vedi una porta... è aperta, ma è troppo buio per vederci qualcosa.");
        }
        set_quantita_oggetto(game, 8, 0);
      } else {
        printf("\nLa porta è già aperta.");
      }
    } else {
      printf("\nNon c'è nessuna porta.");
    }
  } else {
    if(id == 1) //finestra
    {
      if(get_stanza_attuale(*game) == 6)
      {
        printf("\nE' bloccata, forse forzandola si potrebbe aprire...");
      } else {
        printf("\nNon c'è nessuna finestra.");
      }
    } else {
      if(id == 2) //baule
      {
        if(get_stanza_attuale(*game) == 26)
        {
          if(get_quantita_oggetto(*game, 8) == 1)
          {
            printf("\nHai usato la chiave per aprire il baule.\nOra è aperto, c'è della carne, siccome potrebbe servire decidi di prenderla.\n(La carne è stata aggiunta all'inventario)");
            set_quantita_oggetto(game, 15, 1);
            set_quantita_oggetto(game, 8, 0);
          } else {
            printf("\nIl baule è già aperto.");
          }
        } else {
          printf("\nNon c'è nessun baule.");
        }
      }
    }
  }
  return;
}

//la funzione chiude un oggetto fisso, se è possibile chiuderlo//
void chiudere(partita *game, int id)
{
  if(id == 0) //porta
  {
    if(get_stanza_attuale(*game) == 9)
    {
      if(get_quantita_oggetto(*game, 8) == 1)
      {
        printf("\nLa porta è già chiusa.");
      } else {
        printf("\nNon serve chiudere la porta.");
      }
    } else {
      printf("\nNon c'è nessuna porta.");
    }
  } else {
    if(id == 1) //finestra
    {
      if(get_stanza_attuale(*game) == 6)
      {
        printf("\nLa finestra è già chiusa.");
      } else {
        printf("\nNon c'è nessuna finestra.");
      }
    } else {
      if(id == 2) //baule
      {
        if(get_stanza_attuale(*game) == 26)
        {
          if(get_quantita_oggetto(*game, 8) == 1)
          {
            printf("\nIl baule è già chiuso.");
          } else {
            printf("\nNon serve chiudere il baule.");
          }
        } else {
          printf("\nNon c'è nessun baule.");
        }
      }
    }
  }
  return;
}
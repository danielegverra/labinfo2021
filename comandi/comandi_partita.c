/** 
  * Il modulo "comandi_partita" contiene tutte le funzioni
  * volte ad uno svolgimento ottimale della partita e che riguardano
  * l'utilizzo del "gioco" più in generale.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "../analizzatore/analizzatore.h"
#include "../dati/tipi_di_dato.h"
#include "../dati/get_set.h"

//la funzione permette di salvare su file la partita così com'è
void salvare(partita *game)
{
  FILE *fp;
  fp=fopen("comandi/save.bin", "wb");

  if (fp==NULL)
  {
    printf("\nERRORE SALVATAGGIO\n\n");
  }
  else
  {
    fwrite(game, sizeof(partita), 1, fp);
    printf("\n\nFile salvato correttamente!\n\n");
  }

  fclose(fp);
}

//la funzione permette di caricare da file la partita così come è stata salvata
void caricare(partita *game)
{
  FILE *fd;
  fd=fopen("comandi/save.bin", "rb");

  if(fd==NULL)
  {
    printf("\n\nERRORE NEL CARICARE PARTITA\n\n");
  }
  else 
  {
    fread(game, sizeof(partita), 1, fd);
    printf("\n\nFile caricato correttamente!\n\n");
  }

  fclose(fd);
}

// la funzione verifica se l'utente ha risolto l'indovinello, se viene risolto restituisce un booleano con esito positivo
bool verificare_indovinello(partita *game)
{
  printf("\nNasce dentro una conchiglia,\nquesta è mamma, quella è figlia,\npuò esser bianca, rosa o nera,\nè assai preziosa quando è vera.\nNon sei curioso di vederla?\nÈ in fondo al mare ed è una...");
  bool indovinata=0;
  char parola[MAX_CMD];
  char parola_giusta[MAX_CMD]="perla";
  int tentativi;
  
  while (get_n_vite(*game)>0 && indovinata==0)
  {
    tentativi=0;
    while (tentativi<3 && indovinata==0)
    {
      printf("\nInserisci la risposta: ");
      richiedere_comando(parola);

      if (strcmp(parola, parola_giusta)==0)
      {
        indovinata=1;
      } else 
      {
        printf("\n\nLa parola inserita non è quella corretta, ti consiglio di riprovare; ma ricorda: ogni tre tentativi sbagliati perderai una vita!");
        tentativi++;
      }
    }
    if (indovinata==0)
    {
      set_n_vite(game, get_n_vite(*game)-1);
      printf("\n\nI tentativi sono esauriti, HAI PERSO UNA VITA! Continua a provare!");
    }
  }
  return indovinata;
}

//la funzione visualizza l'inventario, le vite o i comandi disponibili//
void visualizzare(partita game, int id)
{
  int pos;
  char nome[MAX_NME];
  
  if(id == 0)
  {
    printf("\nIl tuo inventario è:\n\n");
    pos = 0;
    while(pos < 17)
    {
      if(get_quantita_oggetto(game,pos) != 0)
      {
        get_nome_oggetto(&game, pos, nome);
        printf("%s", nome);
        if(get_quantita_oggetto(game, pos) > 0)
        {
          printf(" x %d\n", get_quantita_oggetto(game, pos));
        } else
        {
          if(get_quantita_oggetto(game, pos) == -1)
          {
            printf(" accesa x 1\n");
          } else 
          {
            if(get_quantita_oggetto(game, pos) == -2)
            {
              printf(" infuocate x 1\n");
            } else
            {
              if(get_quantita_oggetto(game, pos) == -3)
              {
                printf(" indossato x 1\n");
              } else 
              {
                if(get_quantita_oggetto(game, pos) == -4)
                {
                  printf(" terminata x 1\n");
                } else 
                {
                  if(get_quantita_oggetto(game, pos) == -5)
                  {
                    printf(" rotta x 1\n");
                  } else 
                  {
                    printf(" (rimasugli)\n");
                  }
                }
              }
            }
          }
        }
      }
      pos++;
    }
  } else
  {
    if(id == 1)
    {
      printf("\nIl numero di vite a tua disposizione è %d.", get_n_vite(game) );
    } else
    {
      if(id == 2)
      {
        printf("\nECCO I COMANDI DISPONIBILI:\n\n --> salva\n --> carica\n --> visualizza + comandi/vite/inventario\n --> entra + luogo\n --> scendi\n --> sali\n --> esci\n --> vai + direzione\n --> guarda\n --> prendi + oggetto\n --> ruba\n --> mangia\n --> bevi\n --> indossa + mantello\n --> apri + finestra/porta/scrigno\n --> chiudi\n --> forza + finestra\n --> suona + cetra\n --> colpisci\n --> accendi + oggetto\n --> interagisci\n --> scocca + freccia\n\n");
      }
    }
  }

  return;
}

// la funzione stampa la descrizione dell'ambiente in cui il protagonista si trova
void guardare(partita *game)
{
  char s[MAX_DSC];

  get_descrizione_ambiente(*game, get_stanza_attuale(*game), s);
  printf("%s", s);
  if(get_oggetto1(*game, get_stanza_attuale(*game))!=-1 || get_oggetto2(*game, get_stanza_attuale(*game))!=-1)
  {
    printf("\nQuesti sono gli oggetti presenti qui:");
    if(get_oggetto1(*game, get_stanza_attuale(*game))!=-1)
    {
      get_nome_oggetto(game, get_oggetto1(*game, get_stanza_attuale(*game)), s);
      printf("\n> %s", s);
    }
    if(get_oggetto2(*game, get_stanza_attuale(*game))!=-1)
    {
      get_nome_oggetto(game, get_oggetto2(*game, get_stanza_attuale(*game)), s);
      printf("\n> %s", s);
    }
  }
  return;
}

//la funzione permette di interagire con un personaggio presente nell'ambiente, se ce n'è uno//
void interagire(partita *game)
{
  if(get_stanza_attuale(*game) == 12)   //PORCUS GNOMO
  {
    if(get_quantita_oggetto(*game, 4) != -3 && get_quantita_oggetto(*game, 5) != 1)
    {
      printf("\nTi ringrazio, ora puoi proseguire senza problemi.");
    } else {
      if(get_quantita_oggetto(*game, 4) == -3)
      {
        printf("\nSalute viandante! Sono Porcus, lo gnomo protettore di questo sottopassaggio.\nPer poter proseguire devi rinunciare a qualcosa di valore.\nQuel tuo mantello permette di diventare invisibile, giusto?.\nMi interesserebbe averlo con me, me lo cederesti?\n\n");
      } else {
        if(get_quantita_oggetto(*game, 5) == 1)
        {
          printf("\nSalute viandante! Sono Porcus, lo gnomo protettore di questo sottopassaggio.\nPer poter proseguire devi rinunciare a qualcosa di valore.\nQuel tuo coltello sembrerebbe avere delle finiture in oro.\nMi interesserebbe averlo con me, me lo cederesti?\n\n");
        }
      }
      char risposta[MAX_NME];
      richiedere_comando(risposta);
      while(strcmp(risposta, "si") != 0)  //finché non dice si
      {
        printf("\nDaiii, non accetterò una risposta che non sia : 'si'.\n");
        richiedere_comando(risposta);
      }
      printf("\nTi ringrazio, ora puoi proseguire senza problemi.");
      set_sud(game, get_stanza_attuale(*game), 13);
      set_quantita_oggetto(game, 4, 0);
      set_quantita_oggetto(game, 5, 0);
      set_descrizione_ambiente(game, 12, "'Che posto misterioso!', più a sud c'è un corridoio, ora lo gnomo sembra propenso a lasciarti passare.");
    }
  } else {
    if(get_stanza_attuale(*game) == 4 && get_quantita_oggetto(*game, 10) == 1)   //TIPO INCAPPUCCIATO (1)
    {
      printf("\nMi sembri un po' stanco, forse dovresti mangiare qualcosa.");
    } else {
      if(get_stanza_attuale(*game) == 17)   //VECCHIA STREGA
      {
        if(get_quantita_oggetto(*game, 11) == 0)
        {
          printf("\nSalve bel giovanotto, che ci fai in casa mia? Hai l'aria di uno che ha bisogno di aiuto. \nTi darò quello che ti serve, a patto che tu mi porti una pianta speciale che cresce solo in questo bosco.");
          set_oggetto1(game, 19, 11);
        }
        if(get_quantita_oggetto(*game, 11) == 1)
        {
          printf("\nTi ringrazio, ma per poter produrre ciò che ti serve ho bisogno di un altro oggetto: una ciocca di sirena. \nRiesci a procurartela?");
          set_quantita_oggetto(game, 11, -6);
        }
        if(get_quantita_oggetto(*game, 11) == -6 && get_quantita_oggetto(*game, 14) == 1)
        {
          printf("\nTi ringrazio ancora, è proprio la ciocca che cercavo...\nDammi solo qualche minuto...\nEcco fatto, tieni questa pozione, ti permetterà di respirare sott'acqua.\nSecondo me ti tornerà utile.\n(la POZIONE è stata aggiunta all'inventario)");
          set_quantita_oggetto(game, 14, 0);
          set_quantita_oggetto(game, 7, 1);
        }
        if(get_quantita_oggetto(*game, 7) == 1 || get_quantita_oggetto(*game, 7) == -4)
        {
          printf("\nMi hai fatto un grande favore, buona fortuna con il tuo viaggio.");
        }
      } else {
        if(get_stanza_attuale(*game) == 20)   //SIRENA
        {
          if(get_quantita_oggetto(*game, 8) == 0)
          {
            printf("\nCiao bel marinaio d'acqua dolce. Come dici?\nTi serve una mia ciocca di capelli?\nVa bene, te la cederò, ma solo se riuscirai a superare una prova.");
            if(verificare_indovinello(game) == true)
            {
              printf("\nComplimenti, non mi aspettavo che ce l'avresti fatta.\nManterrò la promessa e ti dirò ciò che ti ho promesso.\n(la CIOCCA ed una CHIAVE sono state aggiunte all'inventario)\n");
              set_quantita_oggetto(game, 14, 1);
              set_quantita_oggetto(game, 8, 1);
            }
          }
          if(get_quantita_oggetto(*game, 8) == 1)
          {
            printf("\nChe ci fai ancora qui?\nSu, forza ... procedi con il tuo viaggio.");
          }
        } else {
          if(get_stanza_attuale(*game) == 28)   //TIPO INCAPPUCCIATO (2)
          {
            printf("\nTi ho tenuto d'occhio per tutto il tempo e devo dire che hai fatto un ottimo lavoro, continua così.\nAhh... a proposito, quei due talismani possono essere uniti solo da un potente incantesimo!\nE da queste parti sembrerebbe esserci una certa Amelia che fa giusto al caso tuo.");
            set_nord(game, 2, -1);
          } else {
            if(get_stanza_attuale(*game) == 32)   //AMELIA
            {
              if(get_quantita_oggetto(*game, 6) == 0 || get_quantita_oggetto(*game, 6) == 1)
              {
                printf("\nEhi tu, che ci fai qui? Come dici? Ti serve il mio aiuto?\nD'accordo, ma solo in cambio di una squama di drago, portamela e ti aiuterò.\nAhh... a proposito, quell'arco è per me? non mi serve, tienilo pure!\nE prendi anche questa cetra: usata correttamente ti potrebbe salvare la vita ahah. \n(la CETRA è stata aggiunta all'inventario)");
                set_quantita_oggetto(game, 6, 1);
                set_ovest(game, 29, 31);
                set_descrizione_ambiente(game, 29, "Ora la strada rivolta verso OVEST è libera... il gregge sarà andato a pascolare più avanti... si intravede una grotta ma l’ambiente è cupo, sembra pericoloso! A EST c'è il CAMPO DI ADDESTRAMENTO.");
              }
              if(get_quantita_oggetto(*game, 6) == -5 && get_quantita_oggetto(*game, 16) == 1)
              {
                printf("\nWow, sei riuscito davvero a procurartela? Wow, mi hai stupito.\nCome promesso ti aiuterò.\nVuoi che unisca quei due talismani? Niente di più semplice per me.\nTieni questa pergamena, leggendola si potrà raggiungere il luogo del giudizio. \n(hai ottenuto un'ELSA e una PERGAMENA)");
                set_quantita_oggetto(game, 9, 0);
                set_quantita_oggetto(game, 16, 0);
                set_quantita_oggetto(game, 3, 1);
                set_quantita_oggetto(game, 12, 1);
              }
              if(get_quantita_oggetto(*game, 3) == 1)
              {
                printf("\nAncora qui?! Ti ho già aiutato, ora smamma!");
              }
            } else {
              printf("\nNon puoi interagire con nessuno al momento.");
            }
          }
        }
      }
    }
  }
  return;
}

//stampa l'immagine di un forziere del tesoro subito dopo la vittoria
void stampare_tesoro()
{
  FILE *ft = fopen("tesoro.txt", "r");
  while(!feof(ft))
  {
    char t = getc(ft);
    printf("%c",t);
  }
  return;
}
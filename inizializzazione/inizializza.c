/** 
  * Il modulo "inizializza" gestisce l'inizializzazione
  * del tipo di dato partita ai valori iniziali.
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "../dati/tipi_di_dato.h"
#include "../dati/get_set.h"
#include "../dati/globali.h"

// vengono inizializzate le info di default per gli ambienti del gioco
void inizializzare_ambienti(partita *game)
{
  FILE *fp = fopen("inizializzazione/ambienti_direzioni.txt", "r");
  FILE *fd = fopen("inizializzazione/ambienti.txt", "r");
  int i; // id per ambienti
  int descrizione;
  char nome_ambiente[MAX_NME];
  int nord;
  int sud;
  int est;
  int ovest;
  int oggetto1;
  int oggetto2;
  
  i= 0;
  while(getc(fp)!=EOF)
  {
    fgets(nome_ambiente, MAX_NME, fp);
    set_nome_ambiente(game, i, nome_ambiente);
    fscanf(fp, "%d",&descrizione); //salto un intero perche abbiamo cambiato idea sul tipo di dato descrizione
    fscanf(fp, "%d",&nord);
    set_nord(game, i, nord);
    fscanf(fp, "%d",&sud);
    set_sud(game, i, sud);
    fscanf(fp, "%d",&est);
    set_est(game, i, est);
    fscanf(fp, "%d",&ovest);
    set_ovest(game, i, ovest);
    fscanf(fp, "%d",&oggetto1);
    set_oggetto1(game, i, oggetto1);
    fscanf(fp, "%d",&oggetto2);
    set_oggetto2(game, i, oggetto2);
    i++;
  } 

  int j = 0;
  while (j<MAX_AMB)
  {
    char nome[MAX_NME];
    char descrizione[MAX_DSC];
    fgets(nome, MAX_NME, fd);
    fgets(descrizione, MAX_DSC, fd);
    set_descrizione_ambiente(game, j, descrizione);
    j++;
  }
  
    
  fclose(fp);
  fclose(fd);
}

// vengono inizializzate le info di default per l'inventario del gioco
void inizializzare_inventario(partita *game)
{
  FILE *fp = fopen("inizializzazione/inventario.txt", "r");
  int i = 0;
  char nome_oggetto[MAX_NME];
  int quantita; 
  
  while(i<MAX_OGG)
  {
    fscanf(fp, "%s", nome_oggetto);
    fscanf(fp, "%d", &quantita);
    set_nome_oggetto(game, i, nome_oggetto);
    set_quantita_oggetto(game, i, quantita);
    i++;
  }
  set_nome_oggetto(game, 1, "Arco con frecce");
  set_nome_oggetto(game, 13, "Pietra Focaia");

  fclose(fp);
 
}

// vengono inizializzate le info di default per il gioco
void inizializzare(partita *game)
{
  set_n_vite(game, 3);
  set_stanza_attuale(game, 0);
  inizializzare_inventario(game);
  inizializzare_ambienti(game);
  set_n_azioni(game, 0);
}


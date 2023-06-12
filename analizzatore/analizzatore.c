/** 
  * Il modulo "analizzatore" gestisce l'accettazione
  * dei comandi forniti da utente, segnalando anche i possibili errori
  * nella lettura di questi.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "analizzatore.h"
#include "../dati/tipi_di_dato.h"
#include "../dati/globali.h"
#include "../comandi/comandi_partita.h"
#include "../comandi/comandi_movimento.h"
#include "../comandi/comandi_oggetto.h"

//definizione del tipo di dato "keyword"
typedef char keyword[MAX_CMD];
//lista delle parole valide
const keyword lista_keyword[MAX_KWD] = {"salva", "carica", "visualizza", "entra", "scendi", "sali", "esci", "ruba", "guarda", "interagisci", "parla", "mangia", "bevi","colpisci", "scocca", "vai", "indossa", "prendi", "apri", "chiudi", "forza", "incastra", "spingi", "suona", "accendi", "pagnotta", "carne", "inventario", "vite", "comandi", "freccia", "frecce", "nord", "sud", "est", "ovest", "mantello", "lanterna", "coltello", "talismano", "pianta", "pietra", "squama", "bazar", "taverna", "casetta", "capanna", "lago", "porta", "finestra", "baule", "elsa", "libro", "cetra", "", "chiave", "arco"};

//prende da tastiera l'intera frase
void richiedere_comando(char *input)
{
  int i;
  
  printf("\n\n'Cosa dovrei fare?'\n> ");
  fgets(input, MAX_CMD*2, stdin);
  input[strlen(input)-1]='\0'; //per rimuovere '\n' dalla stringa//

  i = 0;
  while(input[i] != '\0') //trasforma tutto in minuscolo//
  {
    if(input[i] >= 'A' && input[i] <= 'Z')
    {
      input[i] = input[i] + 32;
    }
    i++;
  }
  
}

//divide la frase in 2 parole che vengono controllate da scanner e parser, se c'è stato qualche problema stampa a video un messaggio di errore
void analizzare_comando(partita * game, char input[])
{
  char parola1[MAX_CMD];
  char parola2[MAX_CMD];
  
  if (controllare_struttura(input)==1) //se non ci sono più di 2 parole//
  {
    prendere_parola_1(input, parola1);
    prendere_parola_2(input, parola2);

    if(scanner(parola1)==true && scanner(parola2)==true)
    {
      parser(game, parola1, parola2);
    } else
    {
      error_mgr(7, parola1, parola2);
    }
  } else
  {
    error_mgr(6, parola1, parola2);
  }
}

// controlla che il numero di parole inserite da utente sia consono a quello accettato
bool controllare_struttura (char *input)
{
  int i = 0; //posizione in string input
  int j = 0; //contatore parole
  bool esito = true;

  while (i<strlen(input) && esito==true)
  {
    if (input[i]!=' ' && input[i]!='\0' && ( input[i+1]==' ' || input[i+1]=='\0'))
    {
      j++;
    }
    
    i++;
    
    if (j>2)
    {
      esito=false;
    }

  }
  return esito;
}

// seleziona la prima parola inserita da utente
void prendere_parola_1(char *input, char *parola1)
{
  int i = 0;
  int j = 0;
  
  while (input[i]==' ')
  {
    i++;
  }

  while (input[i]!=' ' && input[i]!='\0')
  {
    parola1[j]=input[i];
    j++;
    i++;
  }

  parola1[j]='\0';

}

// seleziona la seconda parola inserita da utente
void prendere_parola_2(char *input, char *parola2)
{
  int i = 0;
  int j = 0;
  
  while (input[i]==' ')
  {
    i++;
  }
  
  while (input[i]!=' ' && input[i]!='\0')
  {
    i++;
  }

  while (input[i]==' ')
  {
    i++;
  }
  
  while (input[i]!=' ' && input[i]!='\0')
  {
    parola2[j]=input[i];
    j++;
    i++;
  }
  parola2[j]='\0';
 
}

//gli errori ritrovati vengono passati alla funzione che si occupa di riconoscere l'errore e comunicarlo a utente
void error_mgr(int i, string a, string b)
{
  if(i==1)
  {
    printf("--> Il comando **%s** non supporta una seconda parola!\n", a);
  }
  else if(i==2)
  {
    printf("--> Il verbo **%s** non supporta la parola **%s**\n",a, b);
  }
  else if(i==3)
  {
    printf("--> Il verbo **%s** necessita di una seconda parola\n", a);
  }
  else if(i==4)
  {
    printf("--> Il verbo **%s** necessita di una direzione come seconda parola (nord / sud / est / ovest)\n",a);
  }
  else if(i==5)
  {
    printf("--> **%s** non è un verbo.\n",a);
  }
  else if(i==6)
  {
    printf("--> Hai inserito troppe parole!\n");
  }
  else if(i==7)
  {
    printf("--> Almeno una delle due parole non è riconosciuta!\n");
  } 
}

// controlla che la parola inserita (una per volta) sia accettata dal gioco
int scanner(string parola) 
{
  int accettato;
  int i;

  accettato= false;
  i= 0;
  while (accettato == false && i < MAX_KWD)
  {
    if (strcmp(parola, lista_keyword[i]) == 0)
    {
      accettato= true;
    }
    i++;
  }
  
  return accettato;
}

// indirizza le due parole inserite da utente e ne analizza il significato di modo da richiamare la funzione corrispondente
void parser(partita * game, char *parola1, char *parola2)
{

  if(strcmp(parola1, "salva") == 0)
  {
    if(strlen(parola2)==0)
    {
      salvare(game);
    } 
    else
    {
      error_mgr(1, parola1, parola2);
    }
  } 
  else
  {
    if(strcmp(parola1, "carica") == 0)
    {
      if(strlen(parola2)==0)
      {
        caricare(game);
      } 
      else
      {
        error_mgr(1, parola1, parola2);
      }
    } 
    else
    {
      if(strcmp(parola1, "scendi") == 0)
      {
        if(strlen(parola2)==0)
        {
          scendere(game);
        } 
        else
        {
          error_mgr(1, parola1, parola2);
        }
      } 
      else
      {
        if(strcmp(parola1, "sali") == 0)
        {
          if(strlen(parola2)==0)
          {
            salire(game);
          } 
          else
          {
            error_mgr(1, parola1, parola2);
          }
        } 
        else
        {
          if(strcmp(parola1, "esci") == 0)
          {
             if(strlen(parola2)==0)
            {
              uscire(game);
            } 
            else
            {
              error_mgr(1, parola1, parola2);
            }
          } 
          else
          {
            if(strcmp(parola1, "ruba") == 0)
            {
              if(strlen(parola2)==0  || strcmp(parola2, "pagnotta")==0)
              {
                rubare_pagnotta(game);
              } 
              else
              {
                error_mgr(2, parola1, parola2);
              }
            } 
            else
            {
              if(strcmp(parola1, "guarda") == 0)
              {
                if(strlen(parola2)==0)
                {
                  guardare(game);
                } 
                else
                {
                  error_mgr(1, parola1, parola2);
                }
              } 
              else
              {
                if(strcmp(parola1, "interagisci") == 0  || strcmp(parola1, "parla") == 0)
                {
                  if(strlen(parola2)==0)
                  {
                    interagire(game);
                  } 
                  else
                  {
                    error_mgr(1, parola1, parola2);
                  }
                } 
                else
                {
                  if(strcmp(parola1, "mangia") == 0)
                  {
                    if(strlen(parola2)==0)
                    {
                      mangiare(game);
                    }
                    else
                    {
                      error_mgr(1, parola1, parola2);
                    }
                  } 
                  else
                  {
                    if(strcmp(parola1, "bevi") == 0)
                    {
                      if(strlen(parola2)==0)
                      {
                        bere(game);
                      } 
                      else
                      {
                        error_mgr(1, parola1, parola2);
                      }
                    } 
                    else
                    {
                      if(strcmp(parola1, "colpisci") == 0)
                      {
                        if(strlen(parola2)==0)
                        {
                          colpire(game);
                        } 
                        else
                        {
                          error_mgr(1, parola1, parola2);
                        }
                      } 
                      else
                      {
                        if(strcmp(parola1, "visualizza") == 0)
                        {
                          if(strcmp(parola2, "inventario")==0)
                          {
                            visualizzare(*game, 0);
                          } 
                          else
                          {
                            if(strcmp(parola2, "vite")==0)
                            {
                              visualizzare(*game, 1);
                            } 
                            else
                            {
                              if(strcmp(parola2, "comandi")==0)
                              {
                                visualizzare(*game, 2);
                              } 
                              else
                              {
                                if(strlen(parola2)!=0)
                                {
                                  error_mgr(2, parola1, parola2);
                                } 
                                else
                                {
                                  error_mgr(3, parola1, parola2);
                                }
                              }
                            }
                          }
                        } 
                        else
                        {
                          if(strcmp(parola1, "scocca") == 0)
                          {
                            if(strcmp(parola2, "freccia")==0)
                            {
                              scoccare(game, 0);
                            }
                            else
                            {
                              if(strlen(parola2)!=0)
                              {
                                error_mgr(2, parola1, parola2);
                              } 
                              else
                              {
                                error_mgr(3, parola1, parola2);
                              }
                            }
                          } 
                          else
                          {
                            if(strcmp(parola1, "vai") == 0)
                            {
                              if(strcmp(parola2, "nord") == 0)
                              {
                                vai(game, 0);
                              } 
                              else
                              {
                                if(strcmp(parola2, "sud") == 0)
                                {
                                  vai(game, 3);
                                } 
                                else
                                {
                                  if(strcmp(parola2, "est") == 0)
                                  {
                                    vai(game, 1);
                                  } 
                                  else
                                  {
                                    if(strcmp(parola2, "ovest") == 0)
                                    {
                                      vai(game, 2);
                                    }
                                    else
                                    {
                                      error_mgr(4, parola1, parola2);
                                    }
                                  }
                                }
                              }
                            }
                            else
                            {
                              if(strcmp(parola1, "indossa") == 0)
                              {
                                if(strcmp(parola2, "mantello") == 0)
                                {
                                  indossare(game, 0);
                                } 
                                else
                                {
                                  if(strlen(parola2) != 0)
                                  {
                                    error_mgr(2, parola1, parola2);
                                  }
                                  else
                                  {
                                    error_mgr(3, parola1, parola2);
                                  }
                                }
                              }
                              else
                              {
                                if(strcmp(parola1, "prendi") == 0)
                                {
                                  if(strcmp(parola2, "lanterna") == 0)
                                  {
                                    prendere_oggetto(game, 0);
                                  } 
                                  else
                                  {
                                    if(strcmp(parola2, "mantello") == 0)
                                    {
                                      prendere_oggetto(game, 4);
                                    } 
                                    else
                                    {
                                      if(strcmp(parola2, "coltello") == 0)
                                      {
                                        prendere_oggetto(game, 5);
                                      }
                                      else
                                      {
                                        if(strcmp(parola2, "talismano") == 0)
                                        {
                                          prendere_oggetto(game, 9);
                                        } 
                                        else
                                        {
                                          if(strcmp(parola2, "pianta") == 0)
                                          {
                                            prendere_oggetto(game, 11);
                                          } 
                                          else
                                          {
                                            if(strcmp(parola2, "pietra") == 0)
                                            {
                                              prendere_oggetto(game,13);
                                            }
                                            else
                                            {
                                              if(strcmp(parola2, "squama") == 0)
                                              {
                                                prendere_oggetto(game, 16);
                                              } 
                                              else
                                              {
                                                if(strlen(parola2) != 0)
                                                {
                                                  error_mgr(2, parola1, parola2);
                                                }
                                                else
                                                {
                                                  error_mgr(3, parola1, parola2);
                                                }
                                              }
                                            }
                                          }
                                        }
                                      }
                                    }
                                  }
                                }
                                else
                                {
                                  if(strcmp(parola1, "entra") == 0)
                                  {
                                    if(strcmp(parola2, "bazar") == 0)
                                    {
                                      entrare(game, 0);
                                    } 
                                    else
                                    {
                                      if(strcmp(parola2, "taverna") == 0)
                                      {
                                        entrare(game, 1);
                                      } 
                                      else
                                      {
                                        if(strcmp(parola2, "casetta") == 0)
                                        {
                                          entrare(game, 2);
                                        } 
                                        else
                                        {
                                          if(strcmp(parola2, "capanna") == 0)
                                          {
                                            entrare(game, 3);
                                          } 
                                          else
                                          {
                                            if(strcmp(parola2, "lago") == 0)
                                            {
                                              entrare(game, 4);
                                            }
                                            else
                                            {
                                              if(strlen(parola2) != 0)
                                              {
                                                error_mgr(2, parola1, parola2);
                                              }
                                              else
                                              {
                                                error_mgr(3, parola1, parola2);
                                              }
                                            }
                                          }
                                        }
                                      }
                                    }
                                  }
                                  else
                                  {
                                    if(strcmp(parola1, "apri") == 0)
                                    {
                                      if(strcmp(parola2, "porta") == 0)
                                      {
                                        aprire(game, 0);
                                      }
                                      else
                                      {
                                        if(strcmp(parola2, "finestra") == 0)
                                        {
                                          aprire(game, 1);
                                        }
                                        else
                                        {
                                          if(strcmp(parola2, "baule") == 0)
                                          {
                                            aprire(game, 2);
                                          }
                                          else
                                          {
                                            if(strlen(parola2) != 0)
                                            {
                                              error_mgr(2, parola1, parola2);
                                            }
                                            else
                                            {
                                              error_mgr(3, parola1, parola2);
                                            }
                                          }
                                        }
                                      }
                                    }
                                    else
                                    {
                                      if(strcmp(parola1, "chiudi") == 0)
                                      {
                                        if(strcmp(parola2, "porta") == 0)
                                        {
                                          chiudere(game, 0);
                                        }
                                        else
                                        {
                                          if(strcmp(parola2, "finestra") == 0)
                                          {
                                            chiudere(game, 1);
                                          }
                                          else
                                          {
                                            if(strcmp(parola2, "baule") == 0)
                                            {
                                              chiudere(game, 2);
                                            }
                                            else
                                            {
                                              if(strlen(parola2) != 0)
                                              {
                                                error_mgr(2, parola1, parola2);
                                              }
                                              else
                                              {
                                                error_mgr(3, parola1, parola2);
                                              }
                                            }
                                          }
                                        }
                                      }
                                      else
                                      {
                                        if(strcmp(parola1, "forza") == 0)
                                        {
                                          if(strcmp(parola2, "finestra") == 0)
                                          {
                                            forzare_finestra(game);
                                          }
                                          else
                                          {
                                            if(strlen(parola2) != 0)
                                            {
                                              error_mgr(2, parola1, parola2);
                                            }
                                            else
                                            {
                                              error_mgr(3, parola1, parola2);
                                            }
                                          }
                                        }
                                        else
                                        {
                                          if(strcmp(parola1, "incastra") == 0)
                                          {
                                            if(strcmp(parola2, "elsa") == 0)
                                            {
                                              incastrare(game);
                                            }
                                            else
                                            {
                                              if(strlen(parola2) != 0)
                                              {
                                                error_mgr(2, parola1, parola2);
                                              }
                                              else
                                              {
                                                error_mgr(3, parola1, parola2);
                                              }
                                            }
                                          }
                                          else
                                          {
                                            if(strcmp(parola1, "spingi") == 0)
                                            {
                                              if(strcmp(parola2, "libro") == 0)
                                              {
                                                spingere(game);
                                              }
                                              else
                                              {
                                                if(strlen(parola2) != 0)
                                                {
                                                  error_mgr(2, parola1, parola2);
                                                }
                                                else
                                                {
                                                  error_mgr(3, parola1, parola2);
                                                }
                                              }
                                            }
                                            else
                                            {
                                              if(strcmp(parola1, "suona") == 0)
                                              {
                                                if(strcmp(parola2, "cetra")==0)
                                                {
                                                  suonare(game);
                                                }
                                                else
                                                {
                                                  if(strlen(parola2) != 0)
                                                  {
                                                    error_mgr(2, parola1, parola2);
                                                  }
                                                  else
                                                  {
                                                    error_mgr(3, parola1, parola2);
                                                  }
                                                }
                                              }
                                              else
                                              {
                                                if(strcmp(parola1, "accendi") == 0)
                                                {
                                                  if(strcmp(parola2, "lanterna") == 0)
                                                  {
                                                    accendere(game,0);
                                                  }
                                                  else
                                                  {
                                                    if(strcmp(parola2, "freccia") == 0 || strcmp(parola2, "frecce") == 0)
                                                    {
                                                      accendere(game,1);
                                                    }
                                                    else
                                                    {
                                                      if(strlen(parola2) != 0)
                                                      {
                                                        error_mgr(2, parola1, parola2);
                                                      }
                                                      else
                                                      {
                                                        error_mgr(3, parola1, parola2);
                                                      }
                                                    }
                                                  }
                                                }
                                                else
                                                {
                                                  error_mgr(5, parola1, parola2);
                                                }
                                              }
                                            }
                                          }
                                        }
                                      }                                     
                                    }
                                  }
                                }
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
}

/* 
 * File:   main.c
 * Author: Davide Cafaro
 *
 * Created on 3 ottobre 2017, 22.00
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//struttura dei due duellanti contenente le loro statistiche

typedef struct
{
   int hp;
   const unsigned int atk;
   const unsigned int def;
   //le chance sono numeri da 0 a 100 che indicano una probabilità
   const short int critChance; //critico = 3*atk in un sol colpo
   const short int dodgeChance;
   const short int killChance; //uccisione istantanea
} participant;

//restituisce un numero pseudocasuale da 1 a 100

short int d100(void)
{
   return((rand() % 100) + 1);
}

//risolve un attacco: gli attacchi si tengono in contemporanea

void attack(participant *attacker, participant *defender)
{
   //l'attacco colpisce?
   if(d100() > defender->dodgeChance)
   {
      //uccisione?
      if(d100() <= attacker->killChance)
      {
         defender->hp = 0;
         return;
      }

      int damage;
      //critico?
      if(d100() <= attacker->critChance)
         damage = 3 * attacker->atk - defender->def;

      else
         damage = attacker->atk - defender->def;

      //danneggio il difensore
      defender->hp -= damage;
   }

}

int main(int argc, char** argv)
{
   unsigned long long int inputTurns, draws = 0, knightWins = 0, dragonWins = 0;
   char buf[100];

   srand(time(NULL));

   //input turni
   puts("How many turns would you like to try? ");
   fgets(buf, 99, stdin);

   if(strlen(buf) > 20)
   {
      fputs("input too long", stderr);
      exit(EXIT_FAILURE);
   }
   inputTurns = atoll(buf);

   if(inputTurns == 0 && strcmp(buf, "0") != 0)
   {
      fputs("input error", stderr);
      exit(EXIT_FAILURE);
   }
   //fine input
      participant Knight = {300, 80, 30, 33, 90, 0};
      participant Dragon = {1500, 120, 60, 0, 0, 25};
   for(int i = 0; i < inputTurns; i++)
   {
      Knight.hp = 300;
      Dragon.hp = 1500;
      
      //ciclo di gioco; si arresta se un partecipante muore
      for(;;)
      {
         //risolvo gli attacchi in contemporanea
         attack(&Knight, &Dragon);
         
         attack(&Dragon, &Knight);

         //controlli di fine ciclo
         if(Knight.hp < 1 && Dragon.hp < 1)
         {
            draws++;
            break;
         }
         else if(Knight.hp < 1)
         {
            dragonWins++;
            break;
         }
         else if(Dragon.hp < 1)
         {
            knightWins++;
            break;
         }
      }
   }
   //fine gioco
   printf("Simulation ended.\n"
           "Total turns: %llu.\n"
           "Total draws: %llu.\n"
           "Total Knight Wins: %llu.\n"
           "Total Dragon Wins: %llu.\n", inputTurns, draws, knightWins, dragonWins);



   return(EXIT_SUCCESS);
}


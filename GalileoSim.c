
/* 
 * File:   main.c
 * Author: Davide Cafaro
 *
 * Created on 3 ottobre 2017, 21.43
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//costanti di enumerazione che indicano se il gioco deve continuare, se ha vinto uno dei due o se si è verificato un pareggio
typedef enum
{
   CONTINUE,
   KNIGHT, //vittoria del cavaliere
   DRAGON, //vittoria del drago
   DRAW
} game;

//struttura dei due duellanti contenente le loro statistiche
typedef struct
{
   const char name[50];
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
         printf("%s scored a killstrike!\n", attacker->name);
         defender->hp = 0;
         return;
      }

      int damage;
      //critico?
      if(d100() <= attacker->critChance)
      {
         damage = 3 * attacker->atk - defender->def;
         printf("%s scored a critical strike for %d damage!\n", attacker->name, damage);
      }
      else
      {
         damage = attacker->atk - defender->def;
         printf("%s scored %d damage.\n", attacker->name, damage);
      }
      //danneggio il difensore
      defender->hp -= damage;
      printf("%s has now %d hp.\n", defender->name, defender->hp);
   }
   else
      printf("%s didn't hit!\n", attacker->name);

}

int main(int argc, char** argv)
{
   game gamestatus = CONTINUE;

   participant Knight = {"Knight", 300, 80, 30, 33, 90, 0};
   participant Dragon = {"Dragon", 1500, 120, 60, 0, 0, 25};

   //inizializza il seme
  srand(time(NULL));

   //ciclo di gioco; si arresta se un partecipante muore
   do
   {
      //risolvo gli attacchi in contemporanea
      attack(&Knight, &Dragon);
      puts("");
      attack(&Dragon, &Knight);
      puts("");

      //controlli di fine ciclo
      if(Knight.hp < 1 && Dragon.hp < 1)
         gamestatus = DRAW;
      else if(Knight.hp < 1)
         gamestatus = DRAGON;
      else if(Dragon.hp < 1)
         gamestatus = KNIGHT;

   }while(gamestatus == CONTINUE);

   //fine gioco
   if(gamestatus == DRAGON)
      puts("Dragon wins!");
   else if(gamestatus == KNIGHT)
      puts("Knight wins!");
   else
      puts("Wo-hoo! A draw!");



   return(EXIT_SUCCESS);
}


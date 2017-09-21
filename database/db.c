#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "utils.h"
#include "list.h"
#include "tree.h"


struct rack
{
  char *shelf;
  int amount;
};

typedef struct rack rack_t;

struct item
{
  char *name;
  char *desc;
  int price;
  list_t *list;
};

typedef struct item item_t;

/* ---- tmp ---- */
void print_item_name(item_t *item)
{
  printf("%s\n", item->name);
  return;
}

void print_db(list_t *list)
{
  //print_list(list, print_item_name);
  return;
}
/* ---- Skriv ut meny ----*/

void print_menu(void)
{
  puts("\n[L]ägga till en vara\n\
[T]a bort en vara\n\
[R]edigera en vara\n\
Ån[g]ra senaste ändringen\n\
Lista [h]ela varukatalogen\n\
[A]vsluta\n");
}


/* ---- Skriv ut meny för redigering av vara ---- */
void print_edit()
{
  puts("\n[B]eskrivning\n\
[P]ris\n\
[L]agerhylla\n\
An[t]al\n\
\nVälj rad eller [a]vbryt: \n");
}


/* ---- Input hanterare för meny ----*/

char ask_question_menu(void)
{
  print_menu();
  char *c = ask_question("Input:", is_menu_char, (convert_func) strdup).s;
  char true_c;
  true_c = c[0];
  true_c = toupper(true_c);
  return true_c;
}


char ask_question_menu_edit(void)
{
  print_edit();
  char *c = ask_question("Input:", is_menu_edit_char, (convert_func) strdup).s;
  char true_c;
  true_c = c[0];
  true_c = toupper(true_c);
  return true_c;
}



/* ---- Skriv ut item ----*/
/*
void print_item(item_t *it)
{
  printf("Name:  %s\nDesc:  %s\nPrice: %d\nShelf: %s\nAmount: %d", it->name, it->desc, it->price, it->rack.shelf, it->rack.amount);
}
*/
/* ---- Skapar item ----*/

item_t *make_item(tree_t *db, char *nm, char *dsc, int prc, char *slf, int amnt)
{

  rack_t *shlf = calloc(1, sizeof(rack_t));
  shlf->shelf = slf;
  shlf->amount = amnt;
  item_t *itm = calloc(1, sizeof(item_t));
  itm->name = nm;
  itm->desc = dsc;
  itm->price = prc;
  if(!tree_has_key(db, itm->name))
    {
      //list_t *list = calloc(1, sizeof(list_t));
      list_t *list = list_new();
      itm->list = list;
    }
  list_append(itm->list, shlf);
  return itm;
}

/* ---- Input hanterare för nya items ----*/

item_t *input_item(tree_t *db)
{
  char *name  = ask_question_string("Name of item:");
  char *desc  = ask_question_string("Description of item:");
  int price   = ask_question_int("Price of item:");
  char *shelf = ask_question_shelf("Item stored on shelf:");
  int amount  = ask_question_int("Amount of item:");

  return make_item(db, name, desc, price, shelf, amount);
}

/* ---- Magic naming ----*/

char *magick(char *adverbs[], char *verbs[], char *nouns[], int array_length)
{
  char buf[255];
  char * adverb  = adverbs[rand() % array_length];
  char * verb    = verbs[rand() % array_length];
  char * noun    = nouns[rand() % array_length];

  sprintf(buf, "%s-%s %s", adverb, verb, noun);

  return strdup(buf);
}

/* ---- Skriv ut databas ----*/

void list_db_helper(tree_t *db, K *key_list, int i, int page)
{
  while(i < page && i < tree_size(db))
    {
      printf("%d. %s\n", i+1, key_list[i]);
      i++;
    }
}

void list_db(tree_t *db) // Funkar inte helt
{
  K *key_list = tree_keys(db);
  int i = 0;
  int page = 20;
  while(i < tree_size(db))
    {
      list_db_helper(db, key_list, i, page);
      i += 20;
      if(i >= tree_size(db))
        {
          char *next  = ask_question_string("Press [N]ext to view next page or any other key to go back\n");
          if(next[0] == 'n' && next[0] == 'N')
            {
              page += 20;
            }
          else
            {
              return;
            } 
        }
    }
  return;
}

/* ---- Input hanterare för edit av databas ----*/

void edit_db(tree_t *db)
{
  return;
}

/* ---- S ----*/

void add_item_to_db(tree_t *db)
{
  item_t *item = input_item(db);
  char *key = item->name;
  if(tree_has_key(db, item->name))
    {
      return;
    }
  else
    {
      tree_insert(db, key, item);
      return;
    }
}

/* ---- I/O för radering av item från databas ----*/

void remove_item_from_db(tree_t *db)
{
  return;
}

void event_loop_edit(tree_t *db)
{
  bool quit_v = true;
  while(quit_v)
        {
          char option = ask_question_menu_edit();
          switch(option)
            {
            case 'B' :
              break;

            case 'P' :
              puts("Not yet implemented!");
              break;

            case 'L' :
              puts("Not yet implemented!");
              break;

            case 'T' :
              puts("Not yet implemented!");
              break;

            case 'A' :
              quit_v = false;
              break;
            }
        }
}

void event_loop(tree_t *db)
{
  bool quit_v = true;
  while(quit_v)
        {
          char option = ask_question_menu();
          switch(option)
            {
            case 'L' :
              add_item_to_db(db);
              break;

            case 'T' :
              tree_keys(db);
              puts("Not yet implemented!");
              break;

            case 'R' :
              event_loop_edit(db);
              break;

            case 'G' :
              puts("Not yet implemented!");
              break;

            case 'H' :
              list_db(db);
              break;

            case 'A' :
              quit_v = false;
              break;
            }
        }
}

/* ---- MAIN ----*/

int main(int argc, char *argv[])
{
  puts("Välkommen till database v1.0 av Erik/Grim/Jonathan\n\
==================================================\n");
  tree_t *db = tree_new();
  tree_insert(db, "test 1", make_item(db, "test 1", "dsc1", 1000, "A10", 100));
  tree_insert(db, "test 2", make_item(db, "test 2", "dsc2", 1000, "B10", 100));
  tree_insert(db, "test 3", make_item(db, "test 3", "dsc3", 1000, "C10", 100));
  /*
  tree_insert(db, "Erik", make_item(db, "Erik", "Bäst av alla", 1000, "P20", 100));
  tree_insert(db, "Grim", make_item(db, "Grim", "Också bra", 1000, "R15", 100));
  tree_insert(db, "Jonathan", make_item(db, "Jonathan", "Stilig karl", 1000, "T50", 100));
  tree_insert(db, "Stol", make_item(db, "Stol", "dsc1", 1000, "Q65", 100));
  tree_insert(db, "Bord", make_item(db, "Bord", "dsc1", 1000, "L70", 100));
  */
  tree_insert(db, "test 4", make_item(db, "test 4", "dsc4", 1000, "C20", 100));
  tree_insert(db, "test 5", make_item(db, "test 5", "dsc5", 1000, "C30", 100));
  tree_insert(db, "test 6", make_item(db, "test 6", "dsc6", 1000, "C40", 100));
  tree_insert(db, "test 7", make_item(db, "test 7", "dsc7", 1000, "C50", 100));
  tree_insert(db, "test 8", make_item(db, "test 8", "dsc8", 1000, "C60", 100));
  tree_insert(db, "test 9", make_item(db, "test 9", "dsc9", 1000, "C70", 100));
  /*
  tree_insert(db, "test 10", make_item(db, "test 10", "dsc3", 1000, "C10", 100));
  tree_insert(db, "test 11", make_item(db, "test 11", "dsc3", 1000, "C10", 100));
  tree_insert(db, "test 12", make_item(db, "test 12", "dsc3", 1000, "C10", 100));
  tree_insert(db, "test 13", make_item(db, "test 13", "dsc3", 1000, "C10", 100));
  tree_insert(db, "test 14", make_item(db, "test 14", "dsc3", 1000, "C10", 100));
  tree_insert(db, "test 15", make_item(db, "test 15", "dsc3", 1000, "C10", 100));
  tree_insert(db, "test 16", make_item(db, "test 16", "dsc3", 1000, "C10", 100));
  */
  //K *key_list = tree_keys(db);

  //tree_keys funkar enbart med max 9 element i trädet, fattar inte varför
  //Kallar man på tree_keys här i main, och sen i list_db får man segfault.
  puts("event loop");
  event_loop(db);
  return 0;
}


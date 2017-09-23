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
void print_shelfs(rack_t *elem, void *data)
{
  printf("%s\n", elem->shelf);
  return;
}

void print_amounts(rack_t *elem, void *data)
{
  printf("%s has %d nr of items\n", elem->shelf, elem->amount);
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


/* ---- Input hanterare för menyer ----*/
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

/* ---- Skapar item ----*/
item_t *make_item(tree_t *db, char *nm, char *dsc, int prc, char *slf, int amnt)
{
  rack_t *shlf = calloc(1, sizeof(rack_t));
  shlf->shelf = slf; // TODO: Måste spara shelf någonstans, för man ska inte kunna lägga till flera varor på samma shelf
  shlf->amount = amnt;

  item_t *itm = calloc(1, sizeof(item_t));
  itm->name = nm;
  itm->desc = dsc;
  itm->price = prc;

  list_t *list = list_new();
  itm->list = list;
  list_append(itm->list, shlf);

  return itm;
}

/* ---- Edit item ----*/
void edit_desc(tree_t *db)
{
  item_t *edit = tree_get(db, "Stol"); // "Stol" tmp tills list funkar
  printf("Current description: %s\n", edit->desc);
  puts("--------------------------------\n");
  edit->desc = ask_question_string("New description:");
  return;
}

void edit_price(tree_t *db)
{
  item_t *edit = tree_get(db, "Stol"); // "Stol" tmp tills list funkar
  printf("Current price: %d\n", edit->price);
  puts("--------------------------------\n");
  edit->price = ask_question_int("New price:");
  return;
}

void edit_shelf(tree_t *db)
{
  item_t *edit = tree_get(db, "Stol"); // "Stol" tmp tills list funkar
  puts("Current shelf(s):");
  list_apply(edit->list, print_shelfs, NULL);
  puts("--------------------------------\n");
  char *shelf_edit = ask_question_string("What shelf do you wish to change(case sensitive)?");
  char *shelf_new = ask_question_string("What do you wish to change it to?");

  return;
}

void edit_amount(tree_t *db)
{
  item_t *edit = tree_get(db, "Stol"); // "Stol" tmp tills list funkar
  puts("Current shelf(s) and amount(s):");
  list_apply(edit->list, print_amounts, NULL);
  puts("--------------------------------\n");
  // Vilken shelf's amount vill du ändra?
  // ändra shelf's amount
  return;
}

/* ---- Input hanterare för items ----*/
item_t *input_item(tree_t *db)
{
  char *name  = ask_question_string("Name of item:");
  char *desc  = ask_question_string("Description of item:");
  int price   = ask_question_int("Price of item:");
  char *shelf = ask_question_shelf("Item stored on shelf:");
  int amount  = ask_question_int("Amount of item:");

  return make_item(db, name, desc, price, shelf, amount);
}

/* ---- Skriv ut databas ----*/
void list_db(tree_t *db)
{
  K *key_list = tree_keys(db);
  int i = 1;                      // Visat index
  int position = 0;               // Riktiga positionen i arrayen
  int page = 20;                  // Limiter för antal visade varor
  while(position < tree_size(db))
    {
      while(position < page)
        {
          printf("%d. %s\n", i, key_list[position]);
          i++;
          position++;
        }
      i = 1;                      // Återställ visat index
      page += 20;                 // Incrementera en page
      if(page > tree_size(db))    // Minskar page för att inte överskrida array size.
        {
          page += tree_size(db)-page;
        }
      puts("New page starts here\n");
      // TODO:  ask_question_page
      // Tror bästa sättet kan vara att göra två menyer. En för att välja nästa sida, Avsluta, eller
      // välj vara. Och om man väljer välj vara så kör man ask_question_int. Annars måste
      // Vi kolla om det är specifika bokstäver ELLER siffra.
      // Plus att funktionen kan då inte köra toupper, utifall att det är en siffra.
      // Och "siffran"(strängen), kan va längre än 1 iom att index går till 20. Så då måste vi returna
      // char * istället för char som menyerna nu gör.
      // Ja, osv osv. Blir lite fult, men tror det är mkt enklare att göra två menyer.

      // visa/editera vara = key_list[page - <int answer> - 1]
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
  puts("pre if");
  printf("item->name = %s\n", item->name);
  if(tree_has_key(db, item->name)) // Detta funkar inte. Se main.
    {
      puts("has key");
      //item_t *existing = tree_get(db, item->name);
      // if(shelf exist)
      //     existing amount += item amount
      // else
      //     list_append(list, item list)
      return;
    }
  else
    {
      puts("in else");
      tree_insert(db, item->name, item);
      return;
    }
}

/* ---- I/O för radering av item från databas ----*/

void remove_item_from_db(tree_t *db)
{
  // TODO: Först i inlupp 2.
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
              edit_desc(db);
              break;

            case 'P' :
              edit_price(db);
              break;

            case 'L' :
              edit_shelf(db);
              break;

            case 'T' :
              edit_amount(db);
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
  tree_insert(db, "test1", make_item(db, "test1", "dsc1", 1000, "A10", 100));
  tree_insert(db, "test 2", make_item(db, "test 2", "dsc2", 1000, "B10", 100));
  tree_insert(db, "test 3", make_item(db, "test 3", "dsc3", 1000, "C10", 100));

  tree_insert(db, "Erik", make_item(db, "Erik", "Bäst av alla", 1000, "P20", 100));
  tree_insert(db, "Grim", make_item(db, "Grim", "Också bra", 1000, "R15", 100));
  tree_insert(db, "Jonathan", make_item(db, "Jonathan", "Stilig karl", 1000, "T50", 100));
  tree_insert(db, "Stol", make_item(db, "Stol", "dsc1", 1000, "Q65", 100));
  tree_insert(db, "Bord", make_item(db, "Bord", "dsc1", 1000, "L70", 100));

  tree_insert(db, "test 4", make_item(db, "test 4", "dsc4", 1000, "C20", 100));
  tree_insert(db, "test 5", make_item(db, "test 5", "dsc5", 1000, "C30", 100));
  tree_insert(db, "test 6", make_item(db, "test 6", "dsc6", 1000, "C40", 100));
  tree_insert(db, "test 7", make_item(db, "test 7", "dsc7", 1000, "C50", 100));
  tree_insert(db, "test 8", make_item(db, "test 8", "dsc8", 1000, "C60", 100));
  tree_insert(db, "test 9", make_item(db, "test 9", "dsc9", 1000, "C70", 100));

  tree_insert(db, "test 10", make_item(db, "test 10", "dsc3", 1000, "C10", 100));
  tree_insert(db, "test 11", make_item(db, "test 11", "dsc3", 1000, "C10", 100));
  tree_insert(db, "test 12", make_item(db, "test 12", "dsc3", 1000, "C10", 100));
  tree_insert(db, "test 13", make_item(db, "test 13", "dsc3", 1000, "C10", 100));
  tree_insert(db, "test 14", make_item(db, "test 14", "dsc3", 1000, "C10", 100));
  tree_insert(db, "test 15", make_item(db, "test 15", "dsc3", 1000, "C10", 100));
  tree_insert(db, "test 16", make_item(db, "test 16", "dsc3", 1000, "C10", 100));
  tree_insert(db, "test 17", make_item(db, "test 17", "dsc3", 1000, "C10", 100));
  tree_insert(db, "test 18", make_item(db, "test 18", "dsc3", 1000, "C10", 100));
  tree_insert(db, "test 19", make_item(db, "test 19", "dsc3", 1000, "C10", 100));
  tree_insert(db, "test 20", make_item(db, "test 20", "dsc3", 1000, "C10", 100));

  //list_db(db);
  //add_item_to_db(db);
  /* tree_has_key funkar tydligen bara om man stoppar in en sträng direkt.
  if(tree_has_key(db, "Erik"))
    {
      puts("true!");
    }
  else
    {
      puts("false");
    }
  */
  event_loop(db);
  return 0;
}


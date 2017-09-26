#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "utils.h"
#include "list.h"
#include "tree.h"



//////////// ================= STRUCTS
///
/// Structs for items and racks
/// TODO: Ångra


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

struct action
{
  int type; // NOTHING = 0, ADD = 1, REMOVE = 2, EDIT = 3
  item_t *merch;
  item_t copy;
};

typedef struct action action_t;

/* ---- tmp ---- */

//////////// ================= APPLY FUNCTIONS
///
/// Functions for use in tree_apply and list_apply
///
void print_tree(K key, T elem, void *data)
{
  printf("%s\n", (char *)key);
}


void print_shelfs(void *elem, void *data)
{
  printf("%s\n", ((rack_t *)elem)->shelf); // ((rack_t *)elem) = typdefintion
  return;
}

void print_amounts(void *elem, void *data)
{
  printf("Lagerhylla: %s\nAntal: %d\n", ((rack_t *)elem)->shelf, ((rack_t *)elem)->amount);
  return;
}

void shelf_exist(void *elem, void *exist)
{
  if(strcmp(((rack_t *)elem)->shelf, exist) == 0)
    {
      strcpy(exist, "trueeeeeeeeeeeeeeeeee");
    }
}

void change_shelf(void *elem, void *exist)
{
  if(strcmp(((rack_t *)elem)->shelf, exist) == 0)
    {
      printf("Changing shelf: %s\n", ((rack_t *)elem)->shelf);
      puts("--------------------------------\n");
      ((rack_t *)elem)->shelf = ask_question_shelf("New shelf:");
      strcpy(exist, "trueeeeeeeeeeeeeeeeee");// Detta för att vi ska veta att hyllan hittats.
    }
  return;
}

void change_amount(void *elem, void *exist)
{
  if(strcmp(((rack_t *)elem)->shelf, exist) == 0)
    {
      printf("Changing shelf: %s. With amount: %d\n", ((rack_t *)elem)->shelf, ((rack_t *)elem)->amount);
      puts("--------------------------------\n");
      ((rack_t *)elem)->amount = ask_question_int("New amount:");
      strcpy(exist, "trueeeeeeeeeeeeeeeeee");// Detta för att vi ska veta att hyllan hittats.
    }
  return;
}

//////////// ================= AUX
///
/// Auxilary functions
//

bool shelf_existance(tree_t *db, char *shelf_name)
{
  T *elem_list = tree_elements(db);
  for(int i = 0; i < tree_size(db); i++)
    {
      item_t *current = elem_list[i];
      list_t *current_list = current->list;
      char *shelf_tmp = strdup(shelf_name);
      list_apply(current_list, shelf_exist, shelf_tmp);
      if(strlen(shelf_tmp) > 10)
        {
          return true;
        }
    }
  return false;
}
//////////// ================= MENU DISPLAYS
///
/// Displays menus
///
void print_menu(void)
{
  puts("\n[L]ägga till en vara\n\
[T]a bort en vara\n\
[R]edigera en vara\n\
Ån[g]ra senaste ändringen\n\
Lista [h]ela varukatalogen\n\
[A]vsluta\n");
}

void print_edit()
{
  puts("\n[B]eskrivning\n\
[P]ris\n\
[L]agerhylla\n\
An[t]al\n\
\nVälj rad eller [a]vbryt: \n");
}

//////////// ================= ASK QUESTIONS
///
/// Functions for converting input to useable variables
///
char ask_question_list_db(void)
{
  char *c = ask_question("Input:", is_list_db_char, (convert_func) strdup).s;
  char true_c;
  true_c = c[0];
  true_c = toupper(true_c);
  return true_c;
}

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

//////////// ================= MAKE ITEMS
///
/// Functions for making and adding items to db
/// TODO: Fix shelf duplicates
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


  if(shelf_existance(db, slf))
    {
      printf("Vara finns redan på hylla %s, pröva igen\n", slf);
      itm->name = "AVBRYT";
      return itm;
    }

  if(tree_has_key(db, itm->name))                 // Om item finns
    {
      item_t *existing = tree_get(db, itm->name); // Hämta item
      // if(shelf exist)
      //     existing amount += item amount
      // else
      list_append(existing->list, shlf);          // Och appenda shelf
    }

  return itm;
}

item_t *input_item(tree_t *db)
{
  char *name  = ask_question_string("Name of item:");
  char *desc  = ask_question_string("Description of item:");
  int price   = ask_question_int("Price of item:");
  char *shelf = ask_question_shelf("Item stored on shelf:");
  int amount  = ask_question_int("Amount of item:");

  return make_item(db, name, desc, price, shelf, amount);
}

void add_item_to_db(tree_t *db)
{
  item_t *item = input_item(db);     // Gör nytt item
  if(strcmp("AVBRYT", item->name) == 0)
    {
      return;
    }
  if(tree_has_key(db, item->name))   // Om item finns, gör inget(för list_append sker i input)
    {
      printf("Vara %s finns redan", item->name);
      return;
    }
  else                               // Annars inserta item
    {
      tree_insert(db, item->name, item);
      return;
    }
}

//////////// ================= LIST DB
///
/// Funtion to display the database and specific items in the database
///
void list_db(tree_t *db)
{
  K *key_list = tree_keys(db);
  int position = 0;               // Riktiga positionen i arrayen
  int page = 10;                  // Limiter för antal visade varor
  int page_ind = 0;
  int ind;
  while(position < tree_size(db))
    {
      int i = 1;
      while(position < page)
        {
          printf("%d. %s\n", i, key_list[position]);
          i++;
          position++;
        }
      i = 1;                      // Återställ visat index

      puts("\n[V]isa nästa 20 varor\n\
Vä[l]j vara\n\
[A]vbryt\n");

      char answer_id = ask_question_list_db();
      switch(answer_id)
        {
        case 'L':
          ind = ask_question_int("Vilken vara vill du välja?: ");
          if(page > 10)
            {
              item_t *my_elem = tree_get(db, key_list[ind+page_ind-1]);
              printf("Namn: %s\nBeskrivning: %s\nPris: %d\n", key_list[ind+page_ind-1], my_elem->desc, my_elem->price);
              list_apply(my_elem->list, print_amounts, NULL);
            }
          else
            {
              item_t *my_elem = tree_get(db, key_list[ind-1]);
              printf("Namn: %s\nBeskrivning: %s\nPris: %d\n", key_list[ind-1], my_elem->desc, my_elem->price);
              list_apply(my_elem->list, print_amounts, NULL);
}
          return;
        case 'A':
          return;
        case 'V':
          page += 10;                 // Incrementera en page
          page_ind +=10;
          break;
        }
      if(page > tree_size(db))    // Minskar page för att inte överskrida array size.
        {
          page += tree_size(db)-page;
        }
    }
  puts("Listan är slut!");
  return;
}

//////////// ================= CHOOSE ITEM
///
/// Function to display the database, and choose an item to edit.
///
item_t *choose_list_db(tree_t *db)
{
  K *key_list = tree_keys(db);
  int position = 0;               // Riktiga positionen i arrayen
  int page = 10;                  // Limiter för antal visade varor
  int page_ind = 0;
  int ind;
  item_t *false_item = calloc(1, sizeof(item_t));
  false_item->name = "AVBRYT";     // Fulhax för att kunna returna i event_loop_edit
  while(position < tree_size(db))
    {
      int i = 1;
      while(position < page)
        {
          printf("%d. %s\n", i, key_list[position]);
          i++;
          position++;
        }
      i = 1;                      // Återställ visat index

      puts("\n[V]isa nästa 20 varor\n\
Vä[l]j vara\n\
[A]vbryt\n");

      char answer_id = ask_question_list_db();
      switch(answer_id)
        {
        case 'L':
          ind = ask_question_int("Vilken vara vill du välja?: ");
          if(page > 10)
            {
              return tree_get(db, key_list[ind+page_ind-1]);
            }
          else
            {
              return tree_get(db, key_list[ind-1]);
            }
        case 'A':
          return false_item;
        case 'V':
          page += 10;                 // Incrementera en page
          page_ind +=10;
          break;
        }
      if(page > tree_size(db))    // Minskar page för att inte överskrida array size.
        {
          page += tree_size(db)-page;
        }
    }
  return false_item;
}

//////////// ================= EDIT ITEM
///
/// function to edit various values of items.
///
void edit_desc(tree_t *db, item_t *item)
{
  printf("Current description: %s\n", item->desc);
  puts("--------------------------------\n");
  item->desc = ask_question_string("New description:");
  return;
}

void edit_price(tree_t *db, item_t *item)
{
  printf("Current price: %d\n", item->price);
  puts("--------------------------------\n");
  item->price = ask_question_int("New price:");
  return;
}

void edit_shelf(tree_t *db, item_t *item)
{
  puts("Current shelf(s):");
  list_apply(item->list, print_shelfs, NULL); // Prints shelfs
  puts("--------------------------------\n");
  bool has_shelf = true;
  while(has_shelf)
    {
      char *shelf_edit = ask_question_string("What shelf do you wish to change?(case sensitive)");
      list_apply(item->list, change_shelf, shelf_edit); // Ändrar shelf, om den finns.
      if(strlen(shelf_edit) > 10) // change_shelf ändrar shelf edit till lång sträng.
        {
          has_shelf = false;
        }
    }
  return;
}

void edit_amount(tree_t *db, item_t *item)
{
  puts("Current shelf(s) and amount(s):");
  list_apply(item->list, print_amounts, NULL);
  puts("--------------------------------\n");
  bool has_shelf = true;
  while(has_shelf)
    {
      char *shelf_edit = ask_question_string("What shelf do you wish to change?(case sensitive)");
      list_apply(item->list, change_amount, shelf_edit);
      if(strlen(shelf_edit) > 10) // change_shelf ändrar shelf edit till lång sträng.
        {
          has_shelf = false;
        }
    }
  return;
}
//////////// ================= REMOVE ITEM
///
/// TODO: Inlupp 2
///
void remove_item_from_db(tree_t *db)
{
  // TODO: Först i inlupp 2.
  return;
}


void event_loop_edit(tree_t *db, action_t *undo)

//////////// ================= EVENT LOOPS
///
/// Handles menus
///

{
  bool quit_v = true;
  item_t *chosen_item = choose_list_db(db);
  undo->copy = *chosen_item;
  undo->merch = chosen_item;
  if(strcmp(chosen_item->name, "AVBRYT") == 0) // Avbryt valdes i choose_list_db
    {
      return;
    }
  while(quit_v)
        {
          char option = ask_question_menu_edit();
          switch(option)
            {
            case 'B' :
              edit_desc(db, chosen_item);
              break;

            case 'P' :
              edit_price(db, chosen_item);
              break;

            case 'L' :
              edit_shelf(db, chosen_item);
              break;

            case 'T' :
              edit_amount(db, chosen_item);
              break;

            case 'A' :
              quit_v = false;
              break;
            }
        }
}

void undo_func(action_t undo)
{
  if(undo.type == 0)
    {
      puts("Det finns inget att ångra");
    }
  if(undo.type == 1)
    {
      puts("Inte implementerat");
    }
  if(undo.type == 2)
    {
      puts("Inte implementerat");
    }
  if(undo.type == 3)
    {
      puts("Ångrade din senaste redigering");
      *undo.merch = undo.copy;      
    }
}

void event_loop(tree_t *db)
{
  bool quit_v = true;
  action_t undo = {.type = 0};
  while(quit_v)
        {
          char option = ask_question_menu();
          switch(option)
            {
            case 'L' :
              undo.type = 1;
              add_item_to_db(db);
              break;
            case 'T' :
              undo.type = 2;
              puts("Not yet implemented!");
              break;

            case 'R' :
              undo.type = 3;
              event_loop_edit(db, &undo);
              break;

            case 'G' :
              undo_func(undo);
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

//////////// ================= MAIN
///
/// Does the shit
///
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
  tree_insert(db, "Stol", make_item(db, "Stol", "dsc1", 1000, "Q70", 100));
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

  //tree_apply(db, inorder, print_tree, NULL);
  event_loop(db);
  return 0;
}


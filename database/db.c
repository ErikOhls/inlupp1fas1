#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "utils.h"

struct item
{
  char *name;
  char *desc;
  int price;
  char *shelf;
  int amount;
};

typedef struct item item_t;

/* ---- Skriv ut meny ----*/

void print_menu(void)
{
  puts("[L]ägga till en vara\n\
        [T]a bort en vara\n\
        [R]edigera en vara\n\
        Ån[g]ra senaste ändringen\n\
        Lista [h]ela varukatalogen\n\
        [A]vsluta");
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

/* ---- Skriv ut item ----*/

void print_item(item_t *it)
{
  printf("Name:  %s\nDesc:  %s\nPrice: %d\nShelf: %s\nAmount: %d", it->name, it->desc, it->price, it->shelf, it->amount);
}

/* ---- Skapar item ----*/

item_t make_item(char *nm, char *dsc, int prc, char *slf, int amnt)
{
  item_t itm = { .name = nm, .desc = dsc, .price = prc, .shelf = slf, .amount = amnt };
  return itm;
}

/* ---- Input hanterare för nya items ----*/

item_t input_item(void)
{
  char *name  = ask_question_string("Name of item:");
  char *desc  = ask_question_string("Description of item:");
  int price   = ask_question_int("Price of item:");
  char *shelf = ask_question_shelf("Item stored on shelf:");
  int amount  = ask_question_int("Amount of item:");

  return make_item(name, desc, price, shelf, amount);
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

void list_db(item_t *items, int no_items)
{
  int i = 0;
  while(i < no_items)
    {
      printf("%d. %s\n", i+1, items[i].name);
      i++;
    }
}

/* ---- Input hanterare för edit av databas ----*/

void edit_db(item_t *items)
{
  int i = 100;
  while(i < 0 || i > 16)
  {
    i = ask_question_int("Index of item to edit:");
  }
  print_item(&items[i-1]);
  puts("\nPlease edit item:\n");
  items[i-1] = input_item();
}

/* ---- S ----*/

void add_item_to_db(item_t *items, int *db_siz)
{
  item_t item = input_item();
  items[*db_siz] = item;
  ++*db_siz;
}

/* ---- I/O för radering av item från databas ----*/

void remove_item_from_db(item_t *items, int *db_siz)
{
  list_db(items, *db_siz);
  int i = 100;
  while(i < 0 || i > 16)
  {
    i = ask_question_int("Index of item to delete:");
  }
  while(i < *db_siz)
    {
      items[i-1] = items[i];
      i++;
    }
  --*db_siz;
}
void event_loop(item_t *items, int *db_siz)
{
  bool quit_v = true;
  while(quit_v)
        {
          char option = ask_question_menu();
          switch(option)
            {
            case 'L' :
              add_item_to_db(items, db_siz);
              break;

            case 'T' :
              remove_item_from_db(items, db_siz);
              break;

            case 'R' :
              edit_db(items);
              break;

            case 'G' :
              puts("Not yet implemented!");
              break;
            case 'H' :
              list_db(items, *db_siz);
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
  char *array1[] = { "Extraordinärt", "Liten",  "Avkapad"   };
  char *array2[] = { "konstig",       "Rolig",  "påhittad"  };
  char *array3[] = { "benkapare",     "skärm",  "stol"      };

  if (argc < 2)
  {
    printf("Usage: %s number\n", argv[0]);
  }
  else
  {
    item_t db[16]; // Array med plats för 16 varor
    int db_siz = 0;    // Antalet varor i arrayen just nu

    int items = atoi(argv[1]); // Antalet varor som skall skapas

    if (items > 0 && items <= 16)
    {
      for (int i = 0; i < items; ++i)
      {
        // Läs in en vara, lägg till den i arrayen, öka storleksräknaren
        item_t item = input_item();
        db[db_siz] = item;
        ++db_siz;
      }
    }
    else
    {
      puts("Sorry, must have [1-16] items in database.");
      return 1; // Avslutar programmet!
    }
    
    for (int i = db_siz; i < 16; ++i)
      {
        char *name = magick(array1, array2, array3, 3);
        char *desc = magick(array1, array2, array3, 3);
        int price = random() % 200000;
        char shelf[] = { random() % ('Z'-'A') + 'A',
                         random() % 10 + '0',
                         random() % 10 + '0',
                         '\0' };
        int amount = 1;
        item_t item = make_item(name, desc, price, strdup(shelf), amount);
        
        db[db_siz] = item;
        ++db_siz;
      }
    event_loop(db, &db_siz);
  }
  return 0;
}


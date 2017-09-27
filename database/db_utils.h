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

struct action
{
  int type; // NOTHING = 0, ADD = 1, REMOVE = 2, EDIT = 3
  item_t *merch;
  item_t copy;
};

typedef struct action action_t;

// ------- Print --------
// Skriver ut en nods key
void print_tree(K key, T elem, void *data);

// Skriver ut lagerhyllan
void print_shelfs(void *elem, void *data);

// Skriver ut en lagerhylla och antalet av varan som finns där
void print_amounts(void *elem, void *data);

// Skriver ut programmets huvudmeny
void print_menu(void);

// Skriver ut menyn för editering av varor
void print_edit(void);

// Skriver ut en vara. Dess namn, beskrivning, pris, vilken hylla den finns på samt antalet av varan.
void print_item(item_t* item);

// Skriver ut menyn vid visning av varor
void print_list_db(void);

// ------- Edit -------

// Ändrar en varas beskrivning
void edit_desc(tree_t *db, item_t *item);

// Ändrar en varas pris
void edit_price(tree_t *db, item_t *item);

// Ändrar en varas hylla
void edit_shelf(tree_t *db, item_t *item);

// Ändrar antalet av en vara
void edit_amount(tree_t *db, item_t *item);

// ------ Ask question

// Funktion som returnerar ett godkänt svarsalternativ vid funktionen list_db.
char ask_question_list_db();

// Funktion som returnerar ett godkänt svarsalternativ vid funktionen event_loop.
char ask_question_menu();

// Funktion som returnerar ett godkänt svarsalternativ vid funktionen event_loop_edit
char ask_question_menu_edit();

// -------- Change shelf/amount ----------

// Funktion som kollar om hyllan med ett visst element finns.
void shelf_exist(void *elem, void *exist);

// Funktion som byter hylla
void change_shelf(void *elem, void *exist);

// Funktion som byter antalet på en vara 
void change_amount(void *elem, void *exist);


// 
bool shelf_existance(tree_t *db, char *shelf_name);

// Skapar en vara innehållandes varans data
item_t *make_item(tree_t *db, char *nm, char *dsc, int prc, char *slf, int amnt);

// Sätter in itemet i ett träd
item_t *input_item(tree_t *db);

// Ej implementerat
void remove_item_from_db(tree_t *db);

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

//// Skriver ut en nods key
// \param key. Key to be printed
// \param elem. Unused
// \param data. Unused
//
void print_tree(K key, T elem, void *data);

// Skriver ut lagerhyllan
// \param elem. Elem to be printed
// \param data. Unused
//
void print_shelfs(void *elem, void *data);

//// Skriver ut en lagerhylla och antalet av varan som finns där
// \param elem. Elem to be printed
// \param data. Unused

void print_amounts(void *elem, void *data);

//// Skriver ut programmets huvudmeny
///
//
void print_menu(void);

//// Skriver ut menyn för editering av varor
///
//
void print_edit(void);

//// Skriver ut en vara. Dess namn, beskrivning, pris, vilken hylla den finns på samt antalet av varan.
/// \param item_t*. Item to be printed 
//
void print_item(item_t* item);

//// Skriver ut menyn vid visning av varor
///
//
void print_list_db(void);

// ------- Edit -------

//// Ändrar en varas beskrivning
/// \param tree_t*. Tree item is stored in
//  \param item_t*. Item to be edited

void edit_desc(tree_t *db, item_t *item);

//// Ändrar en varas pris
/// \param tree_t*. Tree item is stored in
//  \param item_t*. Item to be edited

void edit_price(tree_t *db, item_t *item);

// Ändrar en varas hylla
/// \param tree_t*. Tree item is stored in
//  \param item_t*. Item to be edited

void edit_shelf(tree_t *db, item_t *item);

//// Ändrar antalet av en vara
/// \param tree_t*. Tree item is stored in
//  \param item_t*. Item to be edited

void edit_amount(tree_t *db, item_t *item);

// ------ Ask question

//// Frågar menyval i list_db
/// Funktion som returnerar ett godkänt svarsalternativ vid funktionen list_db.
// returns valid menu choice
char ask_question_list_db();

//// Frågar menyval i ask_question_menu
/// Funktion som returnerar ett godkänt svarsalternativ vid funktionen event_loop.
// return valid menu choice
char ask_question_menu();

//// Frågar menyval i ask_question_menu_edit
/// Funktion som returnerar ett godkänt svarsalternativ vid funktionen event_loop_edit
//  returns valid menu choice
char ask_question_menu_edit();

// -------- Change shelf/amount ----------

//// Funktion som kollar om hyllan med ett visst element finns.
/// \param elem. Existing shelf
//  \param exist. Name of shelf to check existing of
//
void shelf_exist(void *elem, void *exist);

//// Funktion som byter hylla
///  \param elem. Existing shelf
//   \param exisit. Shelf to change
//
void change_shelf(void *elem, void *exist);

//// Funktion som byter antalet på en vara 
/// \param elem. Existing shelf.
//  \param exists. Shelf to change
//
void change_amount(void *elem, void *exist);


//// Kollar om hyllan finns i hela databasen
/// \param tree_t*. Three where shelf exists. 
//  \param char*. Shelf to check existence of. 
//
bool shelf_existance(tree_t *db, char *shelf_name);

//// Skapar en vara innehållandes varans data
/// \param tree_t. Three where the item will be inserted.
//  \param char*. Item name, description, shelf
//  \param int. Price, amount
//  returns bool whether shelf exist
//
item_t *make_item(tree_t *db, char *nm, char *dsc, int prc, char *slf, int amnt);

//// Frågar användaren om varans specifikationer
///  \param tree_t*. The three where to item belongs. 
//   returns a complete item.
//
item_t *input_item(tree_t *db);

//// Ej implementerat
///
//
//
void remove_item_from_db(tree_t *db);

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tree.h"

/// Define struct tree in your .c file not here! (why?)
struct tree
{
  struct node* top;
};

typedef struct node node_t;

struct node
{
  K key;
  T elem;
  node_t *left;
  node_t *right;
};

/// \file tree.h
///
/// \author Tobias Wrigstad
/// \version 1.1
/// \date 2017-09-03


/// Creates a new tree
///
/// \returns: empty tree
tree_t *tree_new()
{
  return calloc(1, sizeof(struct tree));
}


node_t *node_new(K key, T elem)
{
  node_t *new_node = calloc(1, sizeof(node_t));
  new_node->key = key;
  new_node->elem = elem;
  return new_node;
}

void print_specific(tree_t *tree)
{
  //printf("%s\n", tree->top->right->right->right->key);
}
/// Remove a tree along with all T elements.
/// Note, if T is a pointer, elements will not
/// be removed. 
///
/// \returns: empty tree
void tree_delete(tree_t *tree)
{
  // Ska alltså köra free() på SAMTLIGA noder.
}

/// Get the size of the tree 
///
/// \returns: the number of nodes in the tree

/// ------ Detta fixar grim -------

int help_recurs_node(node_t *cursor)
{
  int size = 0;

  if (cursor == NULL)              // Tomt träd
    {
      return size;
    }
  if (cursor != NULL)              // Om ej tomt träd
    {
      if (cursor->right != NULL)   // Höger
        {
          size += help_recurs_node(cursor->right);
        }
      if (cursor->left != NULL)    // Vänster
        {
          size += help_recurs_node(cursor->left);
        } 
    }
  return size +1;
}


int tree_size(tree_t *tree)
{
  return help_recurs_node(tree->top);
}

/// Get the depth of the tree 
///
/// \returns: the depth of the deepest subtree
// Tror denna fungerar nu. Returnerar värdet på längsta sub tree inkl toppnoden.
int tree_depth_helper(node_t *n)
{
  int node_l, node_r;
  if(n == NULL)                                 // Tomt träd
    {
      return 0;
    }
  else
    {
      node_l = tree_depth_helper(n->left)+1;
      node_r = tree_depth_helper(n->right)+1;
    }
  if(node_l > node_r)                           // Om vänster djupare
    {
      return node_l;
    }
  else                                          // Om höger djupare
    {
      return node_r;
    }
}

int tree_depth(tree_t *tree)
{
  if(tree->top == NULL)
    {
      puts("Tree top  = NULL");
      return 0;
    }
  else
    {
      return tree_depth_helper(tree->top);
    }
}

/// Insert element into the tree. Returns false if the key is already used.
///
/// \param tree pointer to the tree
/// \param key the key of element to be appended
/// \param elem the element 
/// \returns: true if successful, else false
node_t *tree_insert_helper(node_t *cursor, K key, T elem, bool *success)
{
  if(cursor == NULL)               // Om tomma noden är nådd
    {
      cursor = node_new(key, elem);
      success = true;              // Varför varning här? Borde va &?
      return cursor;
    }
  if(strcmp(cursor->key, key) < 0) // Vänster
    {
      cursor->left = tree_insert_helper(cursor->left, key, elem, success);
    }
  if(strcmp(cursor->key, key) > 0) // Höger
    {
      cursor->right = tree_insert_helper(cursor->right, key, elem, success);
    }
  if(strcmp(cursor->key, key) == 0)// Finns
    {
      success = false;
      return cursor;
    }
  return cursor;                   // Skicka cursor bakåt i rekursiven
}

bool tree_insert(tree_t *tree, K key, T elem) // Ej helt funktionell än
{
  bool *success;
  success = false;
  node_t *cursor = tree->top;
  puts("calling insert_helper\n");
  tree_insert_helper(cursor, key, elem, success);
  if(&success)
    {
      puts("success == true\n");
    }
  return success;
}

/// Checks whether a key is used in a tree
///
/// \param tree pointer to the tree
/// \param key the key of elem to be removed
/// \returns: true if key is a key in tree


bool tree_has_key_helper(node_t *n, K key_el)
{
  while(n != NULL)
    {
      if(n->key == key_el)
        {
          return true;
        }
      else
        {
          return (tree_has_key_helper(n->right, key_el) || tree_has_key_helper(n->left,  key_el));  // Or? Hur vet vilken sida?
        }
    }
  return false;
}

bool tree_has_key(tree_t *tree, K key)
{
  if(tree->top == NULL)
  {
    return false;
  }
  else
    {
      return tree_has_key_helper(tree->top, key);
    }
  return false;
}

/// Returns the element for a given key in tree.
/// (The implementation may assume that the key exists.)
///
/// \param tree pointer to the tree
/// \param key the key of elem to be removed
/// \returns: true if key is a key in tree

/// Detta funkar i princip(tror jag). Är jox med pekare jag inte får styr på.
node_t *tree_get_helper(node_t *cursor, K key, T *elem)
{
  if(strcmp(cursor->key, key) < 0) // Vänster
    {
      cursor->left = tree_get_helper(cursor->left, key, elem);
    }
  if(strcmp(cursor->key, key) > 0) // Höger
    {
      cursor->right = tree_get_helper(cursor->right, key, elem);
    }
  if(strcmp(cursor->key, key) == 0)// Hittad!
    {
      *elem = cursor->key;         // * Avreferar, varför varnar den?
      return cursor;
    }
  return cursor;                   // Inte intresserad av returen. Finns bättre lösning på denna funktion?
}

T tree_get(tree_t *tree, K key)
{
  T *elem;
  node_t *cursor = tree->top;
  tree_get_helper(cursor, key, elem);
  printf("elem found = %d\n", *elem);
  return *elem;
}

/// This does not need implementation until Assignment 2
///
/// \param tree pointer to the tree
/// \param key the key of elem to be removed
/// \returns: the removed element
T tree_remove(tree_t *tree, K key)
{

}

int main(void)
{
  tree_t *t = tree_new();

  //tree_get(t, "DDD");

  t->top = node_new("abc", 1);
  t->top->right = node_new("def", 2);
  t->top->left = node_new("ghi", 3);
  t->top->right->right = node_new("klm", 4);
  t->top->right->left = node_new("opq", 5);

  int size = tree_size(t);
  printf("antalet noddjup är = %d\n", size);
  /*
  t->top->left = node_new("hejewq",4);
  t->top->left->left = node_new("heja",4);
  t->top->left->left->left = node_new("jjj",6);
  t->top->left->left->left->right = node_new("jjj",6);
  t->top->left->left->left->right->left = node_new("jjj",6);
  t->top->left->left->left->right->left->right = node_new("jjj",6);
  t->top->left->left->left->right->left->right->left = node_new("hej",6);
  t->top->left->right= node_new("s",3);
  t->top->left->right->left = node_new("s",3);
  t->top->left->right->left->right = node_new("woppa",3);
  t->top->left->right->left->right->left = node_new("s",3);
  t->top->left->right->left->right->left->right = node_new("s",3);
  t->top->left->right->left->right->left->right->left = node_new("snälla",6);
  */
  
  //tree_insert(t, "xxx", 6);
  //print_specific(t);

  //int depth = tree_depth(t);
  //printf("%d\n",depth);

  bool tree_key = tree_has_key(t,"snälla");
  printf("%d\n", tree_key);
  
  
  int depth = tree_depth(t);
  printf("%d\n",depth);

  printf("antalet noder %d\n",tree_size(t) );

  return 0;
}

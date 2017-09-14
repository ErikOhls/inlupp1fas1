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
int tree_size(tree_t *tree)
{
  return 0;
}

/// Get the depth of the tree 
///
/// \returns: the depth of the deepest subtree
// Tror denna fungerar nu. Returnerar värdet på längsta sub tree inkl toppnoden.
int tree_depth_helper(node_t *n)
{
  int node_l, node_r;
  if(n == NULL)
    {
      return 0;
    }
  else
    {
      node_l = tree_depth_helper(n->left)+1;
      node_r = tree_depth_helper(n->right)+1;
    }
  if(node_l > node_r)
    {
      return node_l;
    }
  else
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
/// Insert element into the tree. Returns false if the key is already used.
///
/// \param tree pointer to the tree
/// \param key the key of element to be appended
/// \param elem the element 
/// \returns: true if successful, else false
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
/// ---- Detta jobbar Erik på -----
bool tree_has_key(tree_t *tree, K key)
{
  return true;
}

/// Returns the element for a given key in tree.
/// (The implementation may assume that the key exists.)
/// 
/// \param tree pointer to the tree
/// \param key the key of elem to be removed
/// \returns: true if key is a key in tree
T tree_get(tree_t *tree, K key)
{

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
  /*
  t->top = node_new("DDD", 1);
  t->top->right = node_new("BBB", 2);
  t->top->left = node_new("EEE", 3);
  t->top->right->right = node_new("AAA", 4);
  t->top->right->left = node_new("CCC", 5);

  tree_insert(t, "1", 6);
  print_specific(t);
  */
  t->top = node_new("abc", 1);
  t->top->right = node_new("def", 2);
  t->top->left = node_new("ghi", 3);
  t->top->left->left = node_new("ghi", 3);
  t->top->left->left->left = node_new("ghi", 3);
  t->top->left->left->left->left = node_new("ghi", 3);
  t->top->left->left->left->left->left = node_new("ghi", 3);
  t->top->right->right = node_new("klm", 4);
  t->top->right->left = node_new("opq", 5);

  //tree_insert(t, "xxx", 6);
  //print_specific(t);

  int depth = tree_depth(t);
  printf("%d\n",depth);

  return 0;
}

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
  printf("%s", tree->top->right->key);
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

node_t *tree_insert_helper(node_t *cursor, K key, T elem)
{
  puts("top of helper\n");
  if(cursor == NULL)
    {
      puts("reached null\n");
      cursor = node_new(key, elem);
      return cursor;
    }
  if(strcmp(key, cursor->key) < 0)
    {
      puts("in left\n");
      cursor->left = tree_insert_helper(cursor->left, key, elem);
    }
  if(strcmp(key, cursor->key) > 0)
    {
      puts("in right\n");
      cursor->right = tree_insert_helper(cursor->right, key, elem);
    }
  if(strcmp(key, cursor->key) == 0)
    {
      puts("in equal\n");
      return node_new(key, elem);
    }
  puts("reached (supposedly) impossible state\n");
  return node_new(key, elem);
}
/// Insert element into the tree. Returns false if the key is already used.
///
/// \param tree pointer to the tree
/// \param key the key of element to be appended
/// \param elem the element 
/// \returns: true if successful, else false
bool tree_insert(tree_t *tree, K key, T elem) // Ej helt funktionell än
{
  bool success = false;
  node_t *cursor = tree->top;
  puts("calling insert_helper\n");
  tree_insert_helper(cursor, key, elem);
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
          return (tree_has_key_helper(n->right, key_el) || tree_has_key_helper(n->left,  key_el));       
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
  t->top = node_new("abc", 1);
  t->top->right = node_new("def", 2);
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
  
  
  //tree_insert(t, "xxx", 6);
  //print_specific(t);

  //int depth = tree_depth(t);
  //printf("%d\n",depth);

  bool tree_key = tree_has_key(t,"hej");
  printf("%d\n", tree_key);
  
  
  return 0;
}

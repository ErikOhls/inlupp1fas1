#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tree.h"
#include "list.h"

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

struct success
{
  bool value;
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


node_t *t_node_new(K key, T elem)

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
void free_node(K key, T elem)
{
  puts("in free_node");
  printf("key = %s\n", key);
  free(key);
  //free(&elem); // Ligger inte heapen?
}

void tree_delete_helper(node_t *cursor, tree_action cleanup)
{
  if (cursor == NULL)
    {
      return;
    }
  tree_delete_helper(cursor->left, cleanup);
  tree_delete_helper(cursor->right, cleanup);
  printf("^ Key = %s\n", cursor->key);
  //cleanup(cursor->key, cursor->elem);
  free(cursor);
}


void tree_delete(tree_t *tree, tree_action cleanup)
{
  if(tree->top == NULL)
    {
      free(tree->top);
    }
  else
    {
      tree_delete_helper(tree->top, cleanup);
    }
  free(tree);
}

/// Get the size of the tree 
///
/// \returns: the number of nodes in the tree
int tree_size_helper(node_t *cursor)
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
          size += tree_size_helper(cursor->right);
        }
      if (cursor->left != NULL)    // Vänster
        {
          size += tree_size_helper(cursor->left);
        } 
    }
  return size +1;
}


int tree_size(tree_t *tree)
{
  return tree_size_helper(tree->top);
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

/// Funkar bara om man manuelt lägger in första noden. Varför??
node_t *tree_insert_helper(node_t *cursor, K key, T elem, struct success *success)
{
  if(cursor == NULL)               // Om tomma noden är nådd
    {
      //puts("hit");
      cursor = t_node_new(key, elem);
      success->value = true;
      return cursor;
    }
  if(strcmp(cursor->key, key) > 0) // Vänster
    {
      //puts("left");
      cursor->left = tree_insert_helper(cursor->left, key, elem, success);
    }
  if(strcmp(cursor->key, key) < 0) // Höger
    {
      //puts("right");
      cursor->right = tree_insert_helper(cursor->right, key, elem, success);
    }
  if(strcmp(cursor->key, key) == 0)// Finns
    {
      //puts("exist");
      return cursor;
      success->value = false;
    }
  return cursor;                   // Skicka cursor bakåt i rekursiven
}

bool tree_insert(tree_t *tree, K key, T elem) // Ej helt funktionell än
{
  struct success* success= calloc(1, sizeof(struct success));
  success->value = false;
  if(tree->top == NULL)
    {
      tree->top = t_node_new(key, elem);
    }
  else
    {
      tree_insert_helper(tree->top, key, elem, success);
    }
  if(success->value)
    {
      free(success);
      return true;
    }
  else
    {
      free(success);
      return false;
    }
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

/// Detta funkar i princip(tror jag). Är jox med pekare jag inte får styr på.
node_t *tree_get_helper(node_t *cursor, K key, T *elem)
{
  if(strcmp(cursor->key, key) > 0) // Vänster
    {
      cursor->left = tree_get_helper(cursor->left, key, elem);
    }
  if(strcmp(cursor->key, key) < 0) // Höger
    {
      cursor->right = tree_get_helper(cursor->right, key, elem);
    }
  if(strcmp(cursor->key, key) == 0)// Hittad!
    {
      *elem = cursor->elem;
      return cursor;
    }
  return cursor;
}

T tree_get(tree_t *tree, K key)
{
  T *elem = calloc(1, sizeof(T));
  tree_get_helper(tree->top, key, elem);
  //printf("elem found = %d\n", *elem);
  T tmp = *elem;
  free(elem);
  return tmp;
}

/// This does not need implementation until Assignment 2
///
/// \param tree pointer to the tree
/// \param key the key of elem to be removed
/// \returns: the removed element
/*T tree_remove(tree_t *tree, K key)
{

}
*/

K *keys_helper( node_t *cursor, K *array, int *i)
{
 if (cursor == NULL)
   {
     return array;
   }
 if (cursor != NULL)
   {
     keys_helper(cursor->left, array, i);
     *i = *i + 1;
     array[*i] =  cursor->key;
     keys_helper(cursor->right, array, i);
   }
 return array;
}


K *tree_keys(tree_t * tree)
{
 int i = -1;
 K *my_arr = calloc(tree_size(tree), sizeof(K));
 return keys_helper(tree->top, my_arr, &i);
}

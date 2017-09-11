#ifndef __tree_h__
#define __tree_h__

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "tree.h"

/// Define struct tree in your .c file not here! (why?)
typedef struct tree
{
  int key;
  struct tree* left;
  struct tree* right;
} tree;

typedef struct tree tree_t;

/// For now, let an element's key be string -- Ändrat till int
typedef int K;

/// Change this definition and replace int with the appropriate type
/// in your program. Note, however, that your implementation of list.c
/// should treat T as if it did not know the type.
typedef int T;

/// \file tree.h
///
/// \author Tobias Wrigstad
/// \version 1.1
/// \date 2017-09-03

/// FOR TESTING PURPOSES
void print_tree(tree_t *tree)
{
  printf("root = %d\n", tree->key);
}

void print_right(tree_t *tree)
{
  if(tree->right != NULL)
    {
      printf("right = %d\n", tree->right->key);
    }
  else
    puts("right = NULL");
}

void print_left(tree_t *tree)
{
  if(tree->left != NULL)
    {
      printf("left = %d\n", tree->left->key);
    }
  if(tree->left == NULL)
    puts("left = NULL");
}

void print_left_left(tree_t *tree)
{
  if(tree->left->left != NULL)
    {
      printf("left left = %d\n", tree->left->left->key);
    }
  else
    {
      puts("left left = NULL\n");
    }
}

/// Creates a new tree
///
/// \returns: empty tree
tree_t *tree_new(T value)
{
  tree *root_node = (tree *)malloc(sizeof(tree)); // allokera minne och skicka tillbaka en pointer
  root_node->key = value;
  root_node->left = NULL;
  root_node->right = NULL;
  return root_node;
}

/// Remove a tree along with all T elements.
/// Note, if T is a pointer, elements will not
/// be removed. 
///
/// \returns: empty tree
void tree_delete(tree_t *tree)
{
  
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
int tree_depth(tree_t *tree)
{
  return 0;
}


/// Helper function
///
/// \Returns: tree with inserted element
tree_t *tree_insert_helper(tree_t *tree, K key, T elem, bool *success)
{
  if (tree == NULL)  // Om noden är NULL, skapa ny nod där
    {
      return tree_new(key);
    }
  if (key < tree->key) // Om key är mindre, rekursiv call på vänster
    {
      tree->left  = tree_insert_helper(tree->left, key, elem, success);
    }
  if (key > tree->key) // Om key är större, rekursiv call på höger
    {
      tree->right = tree_insert_helper(tree->right, key, elem, success);
    }
  if (key == tree->key)
    {
      success = false;
      return tree;
    }
  return tree;
}

/// Insert element into the tree. Returns false if the key is already used.
///
/// \param tree pointer to the tree
/// \param key the key of element to be appended
/// \param elem the element 
/// \returns: true if successful, else false
bool tree_insert(tree_t *tree, K key, T elem)
{
  bool *success;
  tree = tree_insert_helper(tree, key, elem, success);
  return success;
}

/// Checks whether a key is used in a tree
///
/// \param tree pointer to the tree
/// \param key the key of elem to be removed
/// \returns: true if key is a key in tree
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
  return 0;
}

/// This does not need implementation until Assignment 2
///
/// \param tree pointer to the tree
/// \param key the key of elem to be removed
/// \returns: the removed element
T tree_remove(tree_t *tree, K key)
{
  return 0;
}

/// Swap the element for a given key for another.
///
/// \param tree pointer to the tree
/// \param key the key of elem to be changed
/// \param elem the updated element 
/// \returns: the updated element
#define tree_update(t, k, e)                    \
  { T tmp = tree_remove(t, k);                  \
    tree_insert(t, k, e);                       \
    tmp; }                                      \

int main(int argc, char *argv[])
{
  tree_t *t = tree_new(5);
  print_tree(t);
  int i = 4;
  int i2 = 6;
  int i3 = 3;
  printf("inserting %d, %d, %d\n", i, i2, i3);
  tree_insert(t, i, 2);
  tree_insert(t, i2, 2);
  tree_insert(t, i3, 2);
  print_tree(t);
  print_right(t);
  print_left(t);
  print_left_left(t);
  return 0;
}

#endif

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "list.h"

struct list
{
  struct node* first;
  struct node* last;
};

struct node
{
  struct rack* rack;
  struct node* next;
};
 
/// Change this definition and replace int with the appropriate type
/// in your program.
struct rack
{
  char *shelf;
  int amount;
};

/// \file list.h
///
/// \author Tobias Wrigstad
/// \version 1.1
/// \date 2017-09-03
/// \bug None known. 


/// Creates a new list
///
/// \returns: empty list
list_t *list_new()
{
  puts("in list new");
  list_t *list = (list_t *)malloc(sizeof(list_t));
  list->rack = NULL;
  list->next = NULL;
  puts("return list");
  return list;
}

/// Inserts a new element at the end of the list
///
/// \param list pointer to the list
/// \param elem the element to be appended
void list_append(list_t *list, L elem)
{
  puts("in append");
  *list->rack = elem;
  puts("exit append");
}

/// Inserts a new element at the beginning of the list
///
/// \param list pointer to the list
/// \param elem the element to be prepended
void list_prepend(list_t *list, L elem)
{
  puts("in prepend");
  *


  puts("out prepend");
}

/// Inserts a new element at a given index. 
///
/// Valid indexes are [0..size]. 
///
/// Example:
///
/// list_t *l = list_new(); // l == []
/// list_insert(l, 0, e1);  // l == [e1]
/// list_insert(l, 0, e2);  // l == [e2, e1]
/// list_insert(l, 1, e3);  // l == [e2, e3, e1]
/// list_insert(l, 5, e4);  // l == [e2, e3, e1]
///
/// The last case fails (and returns false) because
/// size is 3, meaning 5 is not a valid index. 
///
/// Note that insert at index 0 is the same as prepend 
/// and insert index size is the same as append. 
///
/// Negative indexes should be supported:
///
/// list_insert(l, -1, e4);       // l == [e2, e3, e1, e4]
///
/// A positive index can be calculated from a 
/// negative like this: pos_i = size + 1 + neg_i.
/// 
/// \param list  pointer to the list
/// \param index the index for elem to be inserted at
/// \param elem  the element to be prepended
/// \returns true if succeeded, else false
bool list_insert(list_t *list, int index, L elem)
  {

}

/// Removes an element from a list.
///
/// Example: (assume l == [e2, e3, e1, e4])
///
/// int elem;
/// list_remove(l, 1, &elem);  // l = [e2, e1, e4], elem == e3
/// list_remove(l, -1, &elem); // l = [e2, e1], elem == e4
///
/// \param list  pointer to the list
/// \param index the index to be removed
/// \param elem a pointer to where the element can be stored
/// \returns true if succeeded, else 
bool list_remove(list_t *list, int index, L *elem)
{
  return true;
}

/// Returns the element at a given index
/// \param list  pointer to the list
/// \param index the index to be returns
/// \returns a pointer to the element at index index
L list_get(list_t *list, int index)
{
  
}

/// A convenience for list_get(list, 0)
L list_first(list_t *list)
{

}

/// A convenience for list_get(list, -1)
L list_last(list_t *list)
{

}

/// Returns the length of the list. It is undefined
/// whether the length is calculated in O(n) time or
/// whether there is a size counter in the list object
/// that is manipulated by insert, remove, etc. 
/// \param list the list
/// \returns the length of list
int list_length(list_t *list)
{
  return 1;
}

int main(void)
{
  list_t *list = list_new();
  L rack = { .shelf = "A45", .amount = 1};
  list_append(list, rack);
  return 0;
}

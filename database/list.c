#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "list.h"

struct list
{
  struct node* first;
  struct node* last;
};
 
/// Change this definition and replace int with the appropriate type
/// in your program.
struct rack
{
  char *shelf;
  int amount;
};

struct node
{
  L rack;
  struct node* next;
};

/// \file list.h
///
/// \author Tobias Wrigstad
/// \version 1.1
/// \date 2017-09-03
/// \bug None known. 


/// ---- TESTING -----
void print_list(list_t* list)
{
  node_t *cursor = list->first;
  if(cursor != NULL)
    {
      while(cursor != NULL)
        {
          printf("%s, %d\n", cursor->rack.shelf, cursor->rack.amount);
          cursor = cursor->next;
        }
    }
  else
    {
      puts("Empty list ffs!");
    }
}

void print_rack(L elem)
{
  printf("shelf = %s, amount = %d\n", elem.shelf, elem.amount); 
}

/// Creates a new list
///
/// \returns: empty list
list_t *list_new()
{
  return calloc(1, sizeof(struct list));
}

/// node_new
node_t *node_new(L elem, node_t *next)
{
  node_t *new_node = malloc(sizeof(node_t));
  new_node->rack = elem;
  new_node->next = next;
  return new_node;
}

/// Inserts a new element at the end of the list
///
/// \param list pointer to the list
/// \param elem the element to be appended
void list_append(list_t *list, L elem)
{
  // Flytta logik till list_insert?
  if (list->last == NULL)  // Om sista plats ej finns
    {
      list->last = node_new( elem, NULL); // Sätt in elem på sista plats
    }
  else 
    {
      list->last->next = node_new(elem, NULL); 
      list->last = list->last->next; // Peka om last
    }
  if(list->first == NULL)
    {
      list->first = list->last;
    }  
}

/// Inserts a new element at the beginning of the list
///
/// \param list pointer to the list
/// \param elem the element to be prepended
void list_prepend(list_t *list, L elem)
{
  // Flytta logik till list_insert?
  list->first = node_new(elem , list->first); // Ny list->first/peka om
  if (list->last == NULL) // Om list var tom
    {
      list->last = list->first; // Peka last till samma elem
    }
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
  node_t* pointer = list->first;
  if(index < 0) // If index is negative
    {
      index = list_length(list)+1+index;
    }
  int i = 0;
  if(index == 0 || list->first == NULL) // Om tom lista
    {
      list_prepend(list, elem);
      return true;
    }
  while(i < index)
    {
      if(pointer == NULL) // Om nått sista node och index för stort
        {
          return false;
        }
      i++;
      pointer = pointer->next;
    }
  if(i == index && pointer == NULL) // Om vill lägga på på sista plats
    {
      list_append(list, elem);
      return true;
    }
  pointer = node_new(elem, pointer->next);
  return true;
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
  node_t *pointer = list->first;
  int i = 0;
  if(index == 0)
    {
      puts("Index == 0\n");
      node_t *tmp = pointer->next;
      free(list->first);
      list->first = tmp;
      return true;
    }
  while(++i < index)
    {
      printf("while i = %d\n", i);
      if(i == index)
        {
          puts("i == index-1\n");
          pointer = pointer->next->next;
          free(pointer->next);
          return true;
        }
      pointer->next = pointer->next->next;
    }
  return false;
}

/// Returns the element at a given index
/// \param list  pointer to the list
/// \param index the index to be returns
/// \returns a pointer to the element at index index
L list_get(list_t *list, int index)
{
  int i=0;
  node_t *pointer = list->first;
  while (i != index)
    {
    pointer = pointer->next;
    i++;
  }
  return pointer->rack;
}

/// A convenience for list_get(list, 0)
L list_first(list_t *list)
{
  L first_e;
  first_e = list->first->rack;
  return first_e;
}

/// A convenience for list_get(list, -1)
L list_last(list_t *list)
{
  L last_e;
  last_e = list->last->rack;
  return last_e;
}

/// Returns the length of the list. It is undefined
/// whether the length is calculated in O(n) time or
/// whether there is a size counter in the list object
/// that is manipulated by insert, remove, etc. 
/// \param list the list
/// \returns the length of list
int list_length(list_t *list)
{
  int i = 0;
  node_t *cursor = list->first;
  while(cursor != NULL) // While end not reached
    {
      i++;
      cursor = cursor->next;
    }
  return i;
}

int main(void)
{
  list_t *list = list_new();
  L rack = { .shelf = "A45", .amount = 1};
  L rack2 = { .shelf = "B10", .amount = 2};
  L rack3 = { .shelf = "C15", .amount = 4};
  L rack4 = { .shelf = "D25", .amount = 6};
  L rack5 = { .shelf = "E65", .amount = 9};
  list_append(list, rack);
  list_append(list, rack2);
  list_append(list, rack3);
  list_append(list, rack4);
  list_insert(list, -1, rack5);
  print_list(list);
  //puts("remove");
  //list_remove(list, 4, &rack5);
  //print_list(list);
  printf("List length = %d\n", list_length(list));
  print_rack(list_get(list, 4));
  return 0;
}

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
typedef struct list list_t;
typedef struct link link_t;

typedef struct iter iter_t;





struct list{
  link_t *first;
  link_t *last;
};




struct link
{
  char *value;
  link_t *next;
};

struct iter
{
  link_t *current;
};


iter *list_iterator();

list_t *list_new()
{
  return calloc(1, sizeof(struct list));
  
}

void list_delete(list_t *list)
{
  link_t *cursor = list->first;


  while (cursor)
    {
      link_t *tmp = cursor;
      cursor = cursor->next;
      free(tmp->value);
      free(tmp);
    }
  free(list);
  
}

link_t *link_new(char *value, link_t *next);

link_t *link_new(char *value, link_t *next)
{
  link_t *result = malloc(sizeof(struct link));

  if (result)
    {
      result->next = next;
      result->value = value;
    }
  return result;

}

void list_prepend(list_t *list, char *value)
{

  //  list->first = link_new(value, NULL); //NULL == NEXT PEKARE
  list->first = link_new(value, list->first);
  if (list->last == NULL)
    {
      list->last = list->first;
    }
  
  //  list->last = list->first;

  //  list->first = link_new(value, list->first);
}

char *list_get(list_t *list, int index)
{
  link_t *cursor = list->first;

  while (index)
    {
      cursor = cursor->next;
      --index;
    }

  return cursor->value;
}



int main (int argc, char *argv[argc])
{
  list_t *list = list_new();

  for (int i = 0; i < argc; ++i)
    {
      list_prepend(list, argv[i]);
    }
  
  for (int i = 0; i < argc; ++i)
    {
      printf("%s\n", list_get(list, i));
      
             
    }


  
  return 0;
}

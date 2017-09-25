#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#include "utils.h"

answer_t ask_question(char *question, check_func check, convert_func convert)
{
  int buf_siz = 255;
  char buf[buf_siz];

  printf("%s", question);
  scanf("%s", buf);

  if(!check(buf))
    {
      printf("Felaktig inmatning '%s'\n", buf);
      ask_question(question, check, convert);
    }
  return convert(buf);
}

bool is_number(char *str)
{
  for(unsigned int i = 0; i < strlen(str); i = i + 1)
    {
      if(isdigit(str[i]) == false)
        {
          return false;
        }
    }
    return true;
}

bool is_shelf(char* str)
{
  if(isdigit(str[0]))
    return false;
  for(unsigned int i = 1; i < strlen(str); i++)
    {
      if(!isdigit(str[i]))
	{
	  return false;
	}
    }
  return true;
}

bool not_empty(char *str)
{
  return strlen(str) > 0;
}

bool is_menu_char(char *str)
{
  if(strlen(str) != 1)
    {
      return false;
    }
  if(str[0] == 'L' ||
     str[0] == 'l' ||
     str[0] == 'T' ||
     str[0] == 't' ||
     str[0] == 'R' ||
     str[0] == 'r' ||
     str[0] == 'G' ||
     str[0] == 'g' ||
     str[0] == 'H' ||
     str[0] == 'h' ||
     str[0] == 'A' ||
     str[0] == 'a')
    {
    return true;
    }
  return false;
}
bool is_menu_edit_char(char *str)
{
  if(strlen(str) != 1)
    {
      return false;
    }
  if(str[0] == 'B' ||
     str[0] == 'b' ||
     str[0] == 'P' ||
     str[0] == 'p' ||
     str[0] == 'L' ||
     str[0] == 'l' ||
     str[0] == 'T' ||
     str[0] == 't' ||
     str[0] == 'A' ||
     str[0] == 'a')
    {
    return true;
    }
  return false;
}

bool is_list_db_char(char *str)
{
  if(strlen(str) != 1)
    {
      return false;
    }
  if(str[0] == 'V' ||
     str[0] == 'v' ||
     str[0] == 'L' ||
     str[0] == 'l' ||
     str[0] == 'A' ||
     str[0] == 'a')
    {
    return true;
    }
  return false;
}

int ask_question_int(char *question)
{
  answer_t answer = ask_question(question, is_number, (convert_func) atoi);
  return answer.i; // svaret som ett heltal
}


int read_string(char *buf, int buf_siz)
{
  int i = 0;
  char c;
  do
    {
      c = getchar(); // hämta bokstav
      buf[i] = c;    // position 'i' i array = bokstav
      i = i + 1;
    }
  while (i < buf_siz - 1 && c != '\n');
  buf[i-1] = '\0';
  return i;
}


char *ask_question_string(char *question)
{
  return ask_question(question, not_empty, (convert_func) strdup).s;
}

char *ask_question_shelf(char *question)
{
  return ask_question(question, is_shelf, (convert_func) strdup).s;
}

int string_length(char *str)
{
  int c = 0;
  while(str[c] != '\0')
  {
    c++;
  }
  return c;
}

void print(char *str)
{
  int length = string_length(str);
  int i = 0;
  while(i < length)
    {
      putchar(str[i]);
      i++;
    }
}

void println(char *str)
{
  print(str);
  putchar('\n');
}

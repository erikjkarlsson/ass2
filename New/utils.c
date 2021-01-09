
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "utils.h"


/// String and Chars:

int read_string(char *buf, int buf_siz){
  int buf_cnt = 0;
  char c = ' ';
  while (1){
    // Check to prevent buffer overflows
    if (buf_cnt == (buf_siz - 1)){
      break;
      // Check to show that a buffer overflow has
      // occured.
    }else if (buf_cnt > (buf_siz - 1)){
      printf("ERROR: Buffer Overflow");
      return -1;  
    }else{
      // Get char
      c = getchar();
      if (c != '\n'){
	// Set char in array
	buf[buf_cnt] = c;
	// Count chars in buffer
	// Increment
	buf_cnt += 1;
      }else{
	break;
      }      
    }
  }
  // Mark end of the string 
  buf[buf_siz] = '\0';
  // Increment size to compensate for \0
  return (buf_cnt + 1);
}

bool not_empty(char *str){
  return strlen(str) > 0;
}

char *ask_question_string(char *question){
  return ask_question(question, not_empty, (convert_func) strdup).string_value;
}




/// Integers:

bool is_shelf(char *str){
  // Returns true upon a correctly formatted
  // shelf string; <A-Z><0-9><0-9>
  unsigned long index = 1;
  // |String| > 2 & 
  if (isalpha(str[0]) < 1)  return false;
  else if (str[0] == '\0')  return false;
  else if (strlen(str) < 2) return false;
  
  // Returns false if any character in str is not an element of {0,...,9}
  for (; index < strlen(str); index++){
    if (!isdigit(str[index])) return false;
  }
  return true;
}

char *ask_question_shelf(char *question){
  answer_t answer = ask_question(question, is_shelf, (convert_func) strdup);
  return answer.string_value;
}

bool is_number(char *str){
  // Return true if the string "is a number"
  unsigned long index = 0;
  // Handle negative numbers
  if (str[0] == '-') index = 1;
  else if (str[0] == '\0')
    return false;
  
  // Returns false if any character
  // in str is not an element of {0,...,9}
  for (; index < strlen(str); index++){
    if (!isdigit(str[index])) return false;
  }
  return true;
}

bool is_float(char *str){
  int index = 0;
  int dot_count = 0;
  
  // Handle negative numbers
  if (str[0] == '-'){
    index = 1;
  }else if (str[0] == '\0'){
    // Empty string
    return false;
  }
  // Returns false if any character in
  // str is not an element of {0,...,9}
  for (; index < strlen(str); index++){
    if (str[index] == '.'){
      dot_count++;
    }else if (!isdigit(str[index])){
      return false;
    }
  }
  // A floating point number can only have ONE
  // decimal point.
  if (dot_count == 1){
    return true;
  }else{
    return false;
  }
}

int ask_question_int_safe(char *question, int buffer_size){
  // Prompt user for input using provided question
  // Save input in a char array of size, buffer_size
  // check if the provided string can be converted into
  // a number, if it can, convert and return
  // if it can't return -1
  
  int result = -1;
  char input[buffer_size];
  
  read_string(input, buffer_size);
  
  if (is_number(input)) result = atoi(input);
			  
  return result;
}

int ask_question_int(char *question){
  answer_t answer = ask_question(question, is_number, (convert_func) atoi);
  return answer.int_value;
}


/// Floating Point:

double ask_question_float(char *question){
  return ask_question(question, is_float, make_float).float_value;
}

answer_t make_float(char *str){
  return (answer_t) { .float_value = atof(str) };
}


/// General:

void clear_buffer(char *buffer, int buffer_size){
  int index = 0;
  while (1){
    if (index == buffer_size) break;
    buffer[index] = '\0';
    index++;
  }
}

answer_t ask_question(char *question, check_func check, convert_func convert){
  char buffer[255];
  do {
    clear_buffer(buffer, 255);
    printf(question);
    read_string(buffer, 255);

    if (check(buffer)) break;

    
  }while (1);

  return convert(buffer);
}

int seed_random(void){
  // Seed Randomness
  time_t t;
  srandom((unsigned)time(&t));
  return 0;
}

int random_number(int range){
  // Return a random number within
  // Scope: (0 -> range)
  return (rand() % range);  
}

bool valid_command(char *command){
  // Check if command is a valid command
  // of ask_question_menu
  char *string = "SsLlTtRrGgHhAa";
  char *ptr = strstr(string, command);
  if (ptr != NULL){//command found    
    return true;
  }else{
    return false;
  }
}

char *ask_question_menu(){
  puts("--- Meny för kundvagnen ---"); 
  char *command = ask_question_string("[S]kapa en ny kundvagn \n[L]ägga till en vara \n[T]a bort en vara \n[R]edigera en vara \nÅn[g]ra senaste ändringen \nLista [h]ela kundvagnen \n[A]vsluta och checka ut\n");
  while(!valid_command(command)){
    command = ask_question_string("Använd ett giltigt kommando: ");
  }
    return command;
}

bool continue_printing(){
  // Prompt for a yes "y"/"Y" returning true (else false)
  char *ans = ask_question_string("Continue? y/n \n");

  if((strcmp(ans, "y") == 0) || (strcmp(ans, "Y") == 0))      
    return true;    
  else
    return false;
}
		  
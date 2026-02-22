#include "stack.h"
#include "vector.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

typedef enum {
  MINUS= 0,
  PLUS=0,

  TIMES=1,
  DIVIDE=1,

  MODULO=1,

  POW=2,
  LBRACKET=3,
  RBRACKET=3,
  FUNC=3
} Operation;

const char* operations[] = {
  "-",
  "+",
  "*",
  "/",
  "%",
  "^",
};
Operation char_to_operation(char* ch) {
  if(strcmp(ch, "-")==0) {
    return MINUS;
  }
  if(strcmp(ch, "+")==0) {
    return PLUS;
  }
  if(strcmp(ch, "*")==0) {
    return TIMES;
  }
  if(strcmp(ch, "/")==0) {
    return DIVIDE;
  }
  if(strcmp(ch, "%")==0) {
    return MODULO;
  }
  if(strcmp(ch, "^")==0) {
    return POW;
  }
  return FUNC;
}
bool is_operator(char* c) {
  for(int i = 0; i < sizeof(operations)/sizeof(char*); ++i) {
    if(strcmp(c, operations[i])==0) {
      return true;
    }
  }  
  return false;
}

int main(int argc, char** argv) {
  // TODO files and hashmap
  Vector equation;
  initialize_vector(&equation, sizeof(char*));
  for(int i = 1; i < argc; ++i) {
    push_vector(&equation, &argv[i]);
  }
  
  Vector ans;
  initialize_vector(&ans, sizeof(char*));

  Stack operator_stack;
  initialize_stack(&operator_stack, sizeof(char*));
  
  char* token;
  char* buffer;
  for (int i = 0; i < get_size_vector(&equation); ++i) {
    get_vector(&equation, i, &token);
    if(isdigit(*token)) {
      push_vector(&ans, &token);
    }

    else if(strcmp(token, ",")==0) {
      char* op;
      while(!is_empty_stack(&operator_stack)) {
        peep_stack(&operator_stack, &op);
        if(strcmp(op, "(")==0) {
          break;
        }
        pop_stack(&operator_stack, &op);
        push_vector(&ans,&op);
      }
    }

    else if(strcmp(token, "(")==0) {
      push_stack(&operator_stack, &token);
    }

    else if(strcmp(token, ")")==0) {
      if (is_empty_stack(&operator_stack)) return -1;
      char* op;
      bool found = false;
      while(!is_empty_stack(&operator_stack)) {
        pop_stack(&operator_stack, &op);
        if(strcmp(op, "(")==0) {
          found = true;
          break;
        }

        push_vector(&ans, &op);
      }
      if(!found) return -1;
      peep_stack(&operator_stack, &buffer);
      if(!is_operator(buffer) && !isdigit(*buffer) && !(strcmp(buffer, ",")==0) && !(strcmp(token, "(")==0) && !(strcmp(token, ")")==0)) {
        pop_stack(&operator_stack, &buffer);
        push_vector(&ans, &buffer);
      }
    }
    else if(is_operator(token)) {
      char* pop_buff;
      while(!is_empty_stack(&operator_stack)) {
        peep_stack(&operator_stack, &buffer);
        if(strcmp(buffer, "(")==0){
          break;
        }
        if(char_to_operation(buffer) >= char_to_operation(token)) {
          pop_stack(&operator_stack, &pop_buff);
          push_vector(&ans, &pop_buff);
        }
        else {
          break;
        }
      }
        
      push_stack(&operator_stack,&token);
    }
    else { //custom function
      push_stack(&operator_stack,&token);
    }
  }
  while(!is_empty_stack(&operator_stack)) {
    pop_stack(&operator_stack, &buffer);
    if(strcmp(buffer, "(")==0) {
      return -1;
    }
    push_vector(&ans, &buffer);
  }

  
  
  char* buff;
  for(int i = 0; i < get_size_vector(&ans); ++i) {
    get_vector(&ans, i, &buff);
    printf("%s ", buff);
  }

  free_vector(&equation);
  free_vector(&ans);
  free_stack(&operator_stack);
  return 0;
}

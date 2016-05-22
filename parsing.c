#include <stdio.h>
#include <stdlib.h>

#include "mpc/mpc.h"

// If windows
#ifdef _WIN32
#include <string.h>

static char buffer[2048];

// Fake readline function
char* readline(char* prompt) {
  fputs(prompt, stdout);
  fgets(buffer, 2048, stdin);
  char* cpy = malloc(strlen(buffer)+1);
  strcpy(cpy, buffer);
  cpy[strlen(cpy)-1] = '\0';
  return cpy;
}

// fake add_history
void add_history(char* unused) {}

#else
#include <editline/readline.h>
#endif

long eval_op (long x, char* op, long y) {
  if (strcmp(op, "+") == 0) { return x + y; }
  if (strcmp(op, "-") == 0) { return x - y; }
  if (strcmp(op, "*") == 0) { return x * y; }
  if (strcmp(op, "/") == 0) { return x / y; }
  return 0;
}

long eval (mpc_ast_t* t) {
  // return the number directly
  if (strstr(t->tag, "number")) {
    return atoi(t->contents);
  }

  // The operator is always the second child
  char* op = t->children[1]->contents;

  // stashing the third child
  long x = eval(t->children[2]);

  // iterate over the remaining children and combine
  int i = 3;
  while (strstr(t->children[i]->tag, "expr")) {
    x = eval_op(x, op, eval(t->children[i]));
    i++;
  }

  return x;
}

int main (int argc, char** argv) {
  // Parsers
  mpc_parser_t* Number = mpc_new("number");
  mpc_parser_t* Operator = mpc_new("operator");
  mpc_parser_t* Expr = mpc_new("expr");
  mpc_parser_t* Clisp = mpc_new("clisp");

  // Define the parsers
  mpca_lang(MPCA_LANG_DEFAULT,
    "                                                     \
      number    : /-?[0-9]+/ ;                            \
      operator  : '+' | '-' | '*' | '/' ;                 \
      expr      : <number> | '(' <operator> <expr>+ ')' ; \
      clisp     : /^/ <operator> <expr>+ /$/ ;            \
    ",
    Number, Operator, Expr, Clisp);

  // Version information, &c.
  puts("Clisp v. 0.0.0.0.0.1.1.1");
  puts("☕  & 🍔 ");
  puts("Press ⌃ C to Exit");

  while (1) {

    // Output prompt and receive input
    char* input = readline("clisp > ");

    // adds input to history
    add_history(input);

    mpc_result_t r;
    if (mpc_parse("<stdin>", input, Clisp, &r)) {
      long result = eval(r.output);
      printf("%li\n", result);
      mpc_ast_delete(r.output);
    } else {
      mpc_err_print(r.error);
      mpc_err_delete(r.error);
    }

    // Free retrieved input. Function from the stdlib
    free(input);
  }

  mpc_cleanup(4, Number, Operator, Expr, Clisp);

  return 0;
}

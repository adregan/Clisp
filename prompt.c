#include <stdio.h>
#include <stdlib.h>

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

int main(int argc, char** argv) {
  // Version information, &c.
  puts("Clisp v. 0.0.0.0.0.0.0.0");
  puts("Press ⌃ C to Exit");

  while (1) {

    // Output prompt and receive input
    char* input = readline("clisp > ");

    // adds input to history
    add_history(input);

    // echo back
    printf("No, you're a %s\n", input);

    // Free retrieved input. Function from the stdlib
    free(input);
  }

  return 0;
}

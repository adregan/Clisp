#include <stdio.h>
#include <stdlib.h>

#include <editline/readline.h>

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

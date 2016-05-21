#include <stdio.h>

// buffer for user input. size is 2048
static char input[2048];

int main(int argc, char** argv) {
  // Version information, &c.
  puts("Clisp v. 0.0.0.0.0.0.0.0");
  puts("Press ⌃ C to Exit");

  while (1) {

    // outputs the prompt
    fputs("clisp> ", stdout);

    // Reads a line of user input. Max 2048
    fgets(input, 2048, stdin);

    // echo back
    printf("No, you're a %s", input);
  }

  return 0;
}

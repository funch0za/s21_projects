#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 10000

void set_args(int argc, char **argv, int *b, int *e, int *n, int *s, int *t,
              int *v);
void usage();

int main(int argc, char **argv) {
  int b = 0, e = 0, n = 0, s = 0, t = 0, v = 0;
  set_args(argc, argv, &b, &e, &n, &s, &t, &v);

  int number = 0, space_flag = 0;
  for (int j = 1; j < argc; ++j) {
    if (argv[j][0] != '-') {
      FILE *file = fopen(argv[j], "r");
      if (file == NULL) {
        fprintf(stderr, "%s: No such file or directory\n", argv[j]);
        exit(-1);
      }

      char current[MAXN];
      while (fgets(current, MAXN, file) != NULL) {
        if (space_flag == 1 && current[0] == '\n') {
          continue;
        }

        if (current[0] == '\n' && s == 1) {
          space_flag = 1;
        } else {
          space_flag = 0;
        }

        if (n == 1 || (b == 1 && current[0] != '\n')) {
          ++number;
          printf("%6d\t", number);
        }

        if (e == 1 && current[strlen(current) - 1] == '\n') {
          current[strlen(current) - 1] = '$';
        }

        if (t == 1 || v == 1) {
          for (size_t k = 0; k < strlen(current); ++k) {
            if (t == 1 && current[k] == '\t') {
              printf("^I");
            } else if (v == 1 && current[k] == 127) {
              printf("^?");
            } else if (v == 1 && 0 <= current[k] && current[k] <= 31 &&
                       current[k] != '\n' && current[k] != '\t') {
              char ch = '@' + current[k];
              printf("^%c", ch);
            } else {
              printf("%c", current[k]);
            }
          }
        } else {
          printf("%s", current);
        }

        if (e == 1 && current[strlen(current) - 1] == '$') {
          printf("\n");
        }
      }
      fclose(file);
    }
  }
  return 0;
}

void set_args(int argc, char **argv, int *b, int *e, int *n, int *s, int *t,
              int *v) {
  struct option options[4];

  options[0].name = "number-nonblank";
  options[0].has_arg = 0;
  options[0].val = 'b';
  options[0].flag = 0;

  options[1].name = "number";
  options[1].has_arg = 0;
  options[1].val = 'n';
  options[1].flag = 0;

  options[2].name = "squeeze-blank";
  options[2].has_arg = 0;
  options[2].val = 's';
  options[2].flag = 0;

  options[3].name = 0;
  options[3].has_arg = 0;
  options[3].val = 0;
  options[3].flag = 0;

  int current;
  while ((current = getopt_long(argc, argv, "benstTv", options, NULL)) != -1) {
    if (current == 'b') {
      *b = 1;
    } else if (current == 'v') {
      *v = 1;
    } else if (current == 'E') {
      *e = 1;
    } else if (current == 'e') {
      *e = 1;
      *v = 1;
    } else if (current == 'n') {
      *n = 1;
    } else if (current == 's') {
      *s = 1;
    } else if (current == 'T') {
      *t = 1;
    } else if (current == 't') {
      *t = 1;
      *v = 1;
    } else {
      usage();
    }
  }
}

void usage() {
  fprintf(stderr, "cat [OPTION] [FILE]...");
  exit(-1);
}

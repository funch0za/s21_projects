#include <getopt.h>
#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 64
#define STR_LEN 4100

int set_arcgs(int argc, char *argv[], bool *e, bool *i, bool *v, bool *c,
              bool *l, bool *n, bool *h, bool *s, char patterns[STR_LEN][MAX_N],
              int *n_patterns);
int get_filenames(int argc, char **argv, char filenames[STR_LEN][MAX_N],
                  int *n_filenames);
int run_on_file(char filename[STR_LEN], char patterns[STR_LEN][MAX_N], bool e,
                bool i, bool v, bool c, bool l, bool n, bool h, bool s,
                int n_filenames, int n_patterns);
void usage();
void cannot_open_file(char *filename);
bool search(char str[STR_LEN], bool e, bool i, bool v,
            char temps[STR_LEN][MAX_N], int n_temps);

#include "main.h"

int main(int argc, char *argv[]) {
  char patterns[STR_LEN][MAX_N];
  int n_patterns, exit_status;
  bool e, i, v, c, l, n, h, s;

  e = i = v = c = l = n = h = s = false;
  n_patterns = 0;

  exit_status = set_arcgs(argc, argv, &e, &i, &v, &c, &l, &n, &h, &s, patterns,
                          &n_patterns);

  if (exit_status == 0) {
    if (!e) {
      // ищем один шаблон
      for (int j = 1; j < argc && n_patterns == 0; ++j) {
        if (argv[j][0] != '-') {
          n_patterns = 1;
          strcpy(patterns[0], argv[j]);
        }
      }
    }

    char filenames[STR_LEN][MAX_N];
    int n_filenames = 0;

    exit_status = get_filenames(argc, argv, filenames, &n_filenames);

    for (int j = 0; j < n_filenames && exit_status != 1; ++j) {
      if (!e && j == 0) {
        continue;
      }
      if (run_on_file(filenames[j], patterns, e, i, v, c, l, n, h, s,
                      n_filenames, n_patterns) == 1) {
        exit_status = 2;
      }
    }
  }

  return exit_status;
}

int set_arcgs(int argc, char *argv[], bool *e, bool *i, bool *v, bool *c,
              bool *l, bool *n, bool *h, bool *s, char patterns[STR_LEN][MAX_N],
              int *n_patterns) {
  int exit_status = 0;

  if (argc < 2) {
    usage();
    exit_status = 1;
  }

  int opt;
  while ((opt = getopt(argc, argv, "e:ivclnhsf:")) != -1 && exit_status == 0) {
    switch (opt) {
      case 'e':
        *e = true;
        if (*n_patterns == MAX_N) {
          exit_status = 2;
          fprintf(stderr, "Error\n");
        } else {
          strcpy(patterns[*n_patterns], optarg);
          ++(*n_patterns);
        }
        break;
      case 'i':
        *i = true;
        break;
      case 'v':
        *v = true;
        break;
      case 'c':
        *c = true;
        break;
      case 'l':
        *l = true;
        break;
      case 'n':
        *n = true;
        break;
      case 'h':
        *h = true;
        break;
      case 's':
        *s = true;
        break;
      case 'f':
        *e = true;
        FILE *file = fopen(optarg, "r");
        if (file == NULL) {
          cannot_open_file(optarg);
          exit_status = 1;
        } else {
          char current[STR_LEN];
          while (fgets(current, STR_LEN, file) && exit_status == 0) {
            if (*n_patterns == MAX_N) {
              exit_status = 1;
              fprintf(stderr, "Error\n");
            } else {
              strcpy(patterns[*n_patterns], current);
              if (patterns[*n_patterns][strlen(patterns[*n_patterns]) - 1] ==
                  '\n') {
                patterns[*n_patterns][strlen(patterns[*n_patterns]) - 1] = '\0';
              }
              ++(*n_patterns);
            }
          }
          fclose(file);
        }
        break;
      default:
        usage();
        exit_status = 1;
    }
  }

  return exit_status;
}

int get_filenames(int argc, char **argv, char filenames[STR_LEN][MAX_N],
                  int *n_filenames) {
  int exit_code = 0;
  char last_flag = '&';
  for (int i = 1; i < argc && exit_code == 0; ++i) {
    if (argv[i][0] == '-') {
      last_flag = argv[i][1];
    } else {
      if (*n_filenames == MAX_N) {
        exit_code = 1;
        fprintf(stderr, "Error\n");
      } else if (last_flag != 'e' && last_flag != 'f') {
        strcpy(filenames[*n_filenames], argv[i]);
        ++(*n_filenames);
      }
      last_flag = '&';
    }
  }
  return exit_code;
}

void usage() { fprintf(stderr, "Usage: grep [OPTION]... PATTERNS [FILE]..."); }

void cannot_open_file(char *filename) {
  fprintf(stderr, "%s : No such file or directory", filename);
}

bool search(char str[STR_LEN], bool e, bool i, bool v,
            char temps[STR_LEN][MAX_N], int n_temps) {
  bool flag = 0;
  for (int j = 0; j < n_temps && flag == 0; ++j) {
    if (e) {
      regex_t reg;
      int val_reg;
      val_reg = regcomp(&reg, temps[j], 0);

      if (val_reg != 0) {
        exit(-1);
      }

      val_reg = regexec(&reg, str, 0, NULL, 0);

      if (val_reg == 0) {
        flag = 1;
      }
      regfree(&reg);
    } else {
      if (i) {
        char str_copy[STR_LEN];
        strcpy(str_copy, str);
        for (size_t k = 0; k < strlen(str_copy); ++k) {
          if ('A' <= str_copy[k] && str_copy[k] <= 'Z') {
            str_copy[k] = str_copy[k] - 'A' + 'a';
          }
        }

        for (size_t k = 0; k < strlen(temps[j]); ++k) {
          if ('A' <= temps[j][k] && temps[j][k] <= 'Z') {
            temps[j][k] = temps[j][k] - 'A' + 'a';
          }
        }

        if (strstr(str_copy, temps[j]) != NULL) {
          flag = 1;
        }
      } else {
        if (strstr(str, temps[j]) != NULL) {
          flag = 1;
        }
      }
    }

    if (v) {
      flag = !flag;
    }
  }

  return flag;
}

int run_on_file(char filename[STR_LEN], char patterns[STR_LEN][MAX_N], bool e,
                bool i, bool v, bool c, bool l, bool n, bool h, bool s,
                int n_filenames, int n_patterns) {
  if (!e) {
    --n_filenames;
  }

  int exit_status = 0;

  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    if (!s) {
      cannot_open_file(filename);
    }
    exit_status = 1;
  } else {
    char str[STR_LEN];
    int count_str = 0;
    for (int line = 1; fgets(str, STR_LEN, file) != NULL; ++line) {
      int status_search = search(str, e, i, v, patterns, n_patterns);
      count_str += status_search;

      if (status_search == 1 && !c && !l) {
        if (n_filenames > 1 && !h) {
          printf("%s:", filename);
        }
        if (n) {
          printf("%d:", line);
        }
        printf("%s", str);
      }
    }

    if (count_str == 0) {
      exit_status = 1;
    }
    if (c) {
      if (n_filenames > 1 && !h) {
        printf("%s:", filename);
      }
      printf("%d\n", count_str);
    }
    if (count_str != 0 && l) {
      printf("%s\n", filename);
    }

    fclose(file);
  }

  return exit_status;
}

#define _CRT_SECURE_NO_WARNINGS
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

static int append_escaped_string(char** out, size_t* n, char* arg) {

  static const size_t BUFF_SIZE = 256;

  /* allocate */
  if (*out == NULL) {
    *out = (char*)malloc(BUFF_SIZE*sizeof(char));
    (*out)[0] = '\0';
    *n = BUFF_SIZE;
  }

  /* empty argument */
  if (arg[0] == '\0') {
    return TRUE;
  }

  /* check length, whitespace, special characters */
  size_t nwhitespace = 0;
  size_t nspecial = 0;
  size_t len = 0;
  char c;
  while ((c = arg[len]) != '\0') {
    if (isspace(c)) {
      ++nwhitespace;
    } else if (c == '\\' || c == '"') {
      ++nspecial;
    }
    ++len;
  }

  /* new length */
  size_t pos = strlen(*out);
  size_t newlen = pos + len + 1; /* terminating NUL */
  if (nwhitespace > 0) {
    newlen += 2;  /* quotes */
  }
  newlen += nspecial;

  /* re-allocate */
  if (newlen > *n) {
    void* ptr = realloc(*out, newlen);
    /* failed to allocate */
    if (ptr == NULL) {
      return FALSE;
    } 
      
    *out = (char*)ptr;
    *n = newlen;
  }

  char* buff = *out;

  if (nwhitespace > 0) {
    /* quote content */
    buff[pos++] = '"';
  }

  /* copy characters */
  size_t i = 0;
  while ( (c = arg[i]) != '\0' ) {
    /* escape slash and quote */
    if (c == '\\' || c == '"') {
      buff[pos++] = '\\';
    }
    buff[pos++] = c;
    ++i;
  }

  if (nwhitespace > 0) {
    /* close quote */
    buff[pos++] = '"';
  }

  /* terminate string */
  buff[pos++] = '\0';

  return TRUE;
}

static int append_string(char** out, size_t* n, char* arg) {

  static const size_t BUFF_SIZE = 256;

  /* allocate */
  if (*out == NULL) {
    *out = (char*)malloc(BUFF_SIZE*sizeof(char));
    (*out)[0] = '\0';
    *n = BUFF_SIZE;
  }

  /* empty argument */
  if (arg[0] == '\0') {
    return TRUE;
  }

  /* new length */
  size_t pos = strlen(*out);
  size_t len = strlen(arg);
  size_t newlen = pos + len + 1; /* terminating NUL */
  
  /* re-allocate */
  if (newlen > *n) {
    void* ptr = realloc(*out, newlen);
    /* failed to allocate */
    if (ptr == NULL) {
      return FALSE;
    }
    *out = (char*)ptr;
    *n = newlen;
  }

  /* copy characters */
  size_t i = 0;
  char c;
  char* buff = *out;
  while ( (c = arg[i]) != '\0' ) {
    buff[pos++] = c;
    ++i;
  }

  /* terminate string */
  buff[pos++] = '\0';

  return TRUE;
}

static int redirect(char* cmd, char* input, char* output) {

    /* create system command */
  size_t len = strlen(cmd) + strlen(input) + strlen(output) + 11;
  char* exec = (char*)malloc(len * sizeof(char));
  exec[0] = '\0';

  append_escaped_string(&exec, &len, cmd);
  append_string(&exec, &len, " <");
  append_escaped_string(&exec, &len, input);
  append_string(&exec, &len, " >");
  append_escaped_string(&exec, &len, output);

  /* sprintf(exec, "\"%s\" <\"%s\" >\"%s\"", cmd, input, output); */
  printf("Command: %s\n", exec);

  /* need to wrap yet-again for system call on Windows */
#if defined(_WIN32) || defined(WIN32)
  char* sys = NULL;
  size_t n = 0;
  append_string(&sys, &n, "\"");
  append_string(&sys, &n, exec);
  append_string(&sys, &n, "\"");
    /* run system command */
  int out = system(sys);
  free(sys);
  sys = NULL;
#else
  int out = system(exec);
#endif
  free(exec);
  exec = NULL;

  return out;
}

static int compare_files(char* filename1, char* filename2) {

  /* open files for reading */
  FILE* file1 = fopen(filename1, "r");
  if (file1 == NULL) {
    return FALSE;
  }

  FILE* file2 = fopen(filename2, "r");
  if (file2 == NULL) {
    fclose(file1);
    return FALSE;
  }

  /* read files character by character */
  int c1 = getc(file1);
  int c2 = getc(file2);
  int match = TRUE;
  int line = 1;

  /* compare characters */
  do {
    /* check for disagreement */
    if (c1 != c2) {
      /* allow for trailing space */
      if ((isspace(c1) || c1 == EOF) && (isspace(c2) || c2 == EOF)) {
        /* advance c1 to next non-space character or EOL */
        while (isspace(c1) && c1 != '\n') {
          c1 = getc(file1);
        }
        /* check if non-trailing whitespace */
        if (c1 != '\n' && c1 != EOF) {
          match = FALSE;
          break;
        }

        /* advance c2 to next non-space character or EOL */
        while (isspace(c2) && c2 != '\n') {
          c2 = getc(file2);
        }

        /* check if non-trailing whitespace */
        if (c2 != '\n' && c2 != EOF) {
          match = FALSE;
          break;
        }
      } else {
        match = FALSE;
        break;
      }
    }

    /* characters must now match OR only one is EOL */
    if (c1 != c2) {
      /* final check for single terminating newline */
      if (c1 == EOF && c2 == '\n') {
        c2 = getc(file2);
      } else if (c1 == '\n' && c2 == EOF) {
        c1 = getc(file1);
      }
      match = (c1 == c2);
      break;
    }

    /* increment line count */
    if (c1 == '\n') {
      ++line;
    } else if (c1 == EOF) {
      break;
    }

    /* advance to next character if possible */
    c1 = getc(file1);
    c2 = getc(file2);
  } while (match);

  /* close files */
  fclose(file1);
  file1 = NULL;
  fclose(file2);
  file2 = NULL;

  /* print first difference */
  if (!match) {
    printf("Outputs differ on line %d\n", line);
    return FALSE;
  }

  return match;
}

/* combination of redirect and compare */
int main(int argc, char* argv[]) {
  if (argc < 5) {
    printf(
        "\nUsage:\n\t%s <program> <input_file> <output_file> "
        "<expected_output_file>\n\n",
        argv[0]);
    return 1;
  }

  /* get command and I/O files */
  char* cmd = argv[1];
  char* input = argv[2];
  char* output = argv[3];
  char* expected = argv[4];

  /* run command and redirect stdin/stdout */
  int out = redirect(cmd, input, output);
  if (out != 0) {
    return -1;
  }

  /* compare output to expected output */
  int match = compare_files(output, expected);
  if (!match) {
    return 1;
  }

  return 0;
}
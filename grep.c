#include <stdio.h>
#include <stdlib.h>

int MAXLEN = 1000;

void find(char* key, int keysize, char* filename, int indices[MAXLEN]);
int set_charlen(char* key);

int main(int argc, char** argv) {

  if(argc != 3) {
    printf("Usage: grep [key] [file]\n");
    return EXIT_FAILURE;
  }
  
  char* key = argv[1], *fname = argv[2];
  int indices[MAXLEN], keysize = set_charlen(key);
  
  if(!(key && fname))
    return EXIT_FAILURE;

  find(key, keysize, fname, indices);
  
  return EXIT_SUCCESS;
}

void find(char* key, int keysize, char* filename, int indices[MAXLEN]) {

  FILE* fptr = fopen(filename, "r");
  char str[MAXLEN];
  int current_line_num = 0, indices_index = 0;
  
  while(fgets(str, MAXLEN, fptr)) {
    int i = 0;

    while(str[i]) {
      if(str[i] == key[0]) {

	int c = i;
	for(int d = 0; d < keysize; ++d) {
	  if(key[d] != str[c++]) break;
	}

	if ((i+keysize) == c )  {
	  indices[indices_index++] = current_line_num;
	}
      }
      ++i;
    }
    ++current_line_num;
  }

  for(int i = 0; i < indices_index; ++i) {
    printf("found on line: %d\n", indices[i]);
  }
}

int set_charlen(char* key) {
  int len = 0;
  while(*key++ != '\0') ++len;

  return len;
}

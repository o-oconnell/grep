#include <stdio.h>
#include <stdlib.h>

int MAXLEN = 1000;

void find(char* key, int keysize, char* filename, int indices[MAXLEN]);

int main(int argc, char** argv) {

  if(argc != 3) {
    printf("Usage: grep [key] [file]\n");
    return EXIT_FAILURE;
  }
  char* key = argv[1];
  char* fname = argv[2];
  
  int indices[MAXLEN];
  int keysize = sizeof(key) / sizeof(key[0]);
  find(key, keysize, fname, indices);
  
  return EXIT_SUCCESS;
}

void find(char* key, int keysize, char* filename, int indices[MAXLEN]) {
  
  if(key && filename)
    printf("Searching for \"%s\" in \"%s\"\n", key, filename);

  FILE* fptr = fopen(filename, "r");
  char str[MAXLEN];
  int current_line_num = 0;
  int indices_index = 0;
  
  while(fgets(str, MAXLEN, fptr)) {

    int i = 0;

    while(str[i]) {
      if(str[i] == key[0]) {
	int c = i;
	for(; c < keysize; ++c)
	  if(key[c] != str[c]) break;

	if (c == keysize) 
	  indices[indices_index++] = current_line_num;
	
      }
      ++i;
    }
    
    ++current_line_num;
  }
  

}

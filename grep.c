#include <stdio.h>
#include <stdlib.h>

#define MAXLEN 1000

/* prints line numbers with found substrings
 * @param key - the key to find
 * @param filename - the name of the file to search
 */
void find(char* key, char* filename);

/* returns char length
 * @param key - char to return length of
 */
int set_charlen(char* key);

/* checks user input validity */
int usage(int argc, char** argv);

int main(int argc, char** argv) {

  usage(argc, argv);

  find(argv[1], argv[2]);

  return EXIT_SUCCESS;
}

void find(char* key, char* filename) {

  FILE* fptr = fopen(filename, "r");
  char str[MAXLEN];
  int current_line_num = 0, indices_index = 0, indices[MAXLEN],
    keysize = set_charlen(key);
  
  while(fgets(str, MAXLEN, fptr)) {
    int i = 0;
    while(str[i]) {
      if(str[i] == key[0]) {

	int c = i, d = 0;
	for(;d < keysize;)
	  if(key[d++] != str[c++]) break;

	if (i+keysize == c )
	  indices[indices_index++] = current_line_num;
      }
      ++i;
    }
    ++current_line_num;
  }

  for(int i = 0; i < indices_index; )
    printf("found on line: %d\n", indices[i++]);
}

int set_charlen(char* key) {
  int len = 0;
  while(*key++ != '\0') ++len;

  return len;
}

int usage(int argc, char** argv) {
  FILE *fcheck = fopen(argv[2], "r");
    
  if(argc != 3) {
    printf("Usage: %s [key] [file]\n", argv[0]);
    exit(1);
  } else if(!fcheck) {
    printf("Failed to open \"%s\"\n", argv[2]);
    exit(1);
  } else
    return 0;

}

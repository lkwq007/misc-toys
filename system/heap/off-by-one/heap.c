
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h> 
#define DELETE 1
#define PRINT 2

void create();
void process(unsigned int);
 
char *ptrs[10];
 
int main() {
 
  setvbuf(stdout, NULL, _IONBF, 0);
 
  while(1) {
    unsigned int choice;
    puts("1. create\n2. delete\n3. print\n4. exit");
    printf("> ");
    scanf("%u", &choice);
 
    switch(choice) {
      case 1: create(); break;
      case 2: process(DELETE); break;
      case 3: process(PRINT); break;
      case 4: exit(0); break;
      default: puts("invalid choice"); break;
    }
  }
}
 
void create() {
 
  unsigned int i, size;
  unsigned int idx = 10;
  char buf[1024];
 
  for (i = 0; i < 10; i++) {
    if (ptrs[i] == NULL) {
      idx = i;
      break;
    }
  }
  if (idx == 10) {
    puts("no free slots\n");
    return;
  }
   
  printf("\nusing slot %u\n", idx);
 
  printf("size: ");
  scanf("%u", &size);
  if (size > 1023) {
    puts("maximum size (1023 bytes) exceeded\n");
    return;
  }
 
  printf("data: ");
  size = read(0, buf, size);
  buf[size] = 0x00;
   
  ptrs[idx] = (char*)malloc(size);
  strcpy(ptrs[idx], buf);
 
  puts("successfully created chunk\n");
}

void process(unsigned int action) {
 
  unsigned int idx;
  printf("idx: ");
  scanf("%u", &idx);
 
  if (idx > 10) {
    puts("invalid index\n");
    return;
  }
 
  if (ptrs[idx] == NULL) {
    puts("chunk not existing\n");
    return;
  }
 
  if (action == DELETE) {
    free(ptrs[idx]);
    ptrs[idx] = NULL;
    puts("successfully deleted chunk\n");
  }
  else if (action == PRINT) {
    printf("\ndata: %s\n", ptrs[idx]);
  }
 
}
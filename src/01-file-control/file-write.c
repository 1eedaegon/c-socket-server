#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define BUFF_SIZE 100
#define type(x) _Generic((x),                                                     \
        _Bool: "_Bool",                  unsigned char: "unsigned char",          \
         char: "char",                     signed char: "signed char",            \
    short int: "short int",         unsigned short int: "unsigned short int",     \
          int: "int",                     unsigned int: "unsigned int",           \
     long int: "long int",           unsigned long int: "unsigned long int",      \
long long int: "long long int", unsigned long long int: "unsigned long long int", \
        float: "float",                         double: "double",                 \
  long double: "long double",                   char *: "char *",                 \
       void *: "void *",                         int *: "int *",                  \
      default: "unknown")

void err_handling(char* message);

int main(int argc, char *argv[]){
  int fd;
  char * sample ="정상적으로 작동하는지 테스트 뭄ㄴ자열";
  int type_argv;
  if(argc != 2){
    printf("Usage: %s <Some messages>\n", argv[0]);
    exit(1);
  }
  printf("Input string is: %s / %s\n", argv[1], type(argv[1]));
  
  fd=open("output.txt", O_CREAT|O_WRONLY|O_TRUNC);
  if(fd == -1) { err_handling("Open error."); }
  printf("File descriptor: %d \n", fd);

  if(write(fd, argv[1], sizeof(argv[1])) == -1){ err_handling("Write error."); }
  close(fd);
  return 0;
}
void err_handling(char* message){
  fputs(message, stderr);
  fputc('\n', stderr);
  exit(1);
}

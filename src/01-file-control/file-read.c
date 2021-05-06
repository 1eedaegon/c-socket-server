#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
// fctnl: file descriptor에 대한 설명은 나중에
#include <unistd.h>

#define BUFF_SIZE 100

void err_handling(char* message);

int main(void){
 // File descriptor
 int fd;
 char buff[BUFF_SIZE];
 fd = open("sample.txt", O_RDONLY);
 if(fd < 0){ err_handling("open() error."); }

 printf("File descriptor: %d \n", fd);
 if(read(fd, buff, sizeof(buff)) < 0){ err_handling("read() error."); }
 // read함수는 성공 시 바이트수 반환, EOF시 0반환, 실패 시 -1
 // linux는 소켓과 파일을 같은 취급하지만 windows는 다른 리소스 취급
 printf("Data in file: %s", buff);
 close(fd);
}

void err_handling(char* message){
  fputs(message, stderr);
  fputs("\n", stderr);
  exit(1);
}

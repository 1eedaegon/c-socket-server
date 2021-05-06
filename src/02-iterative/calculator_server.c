#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024
#define OPSZ 4

void err_handling(char *msg);
int calculator(int opnum, int opnds[], char operator);

int main(int argc, char *argv[]){
  int serv_sock, clnt_sock;
  char opinfo[BUF_SIZE];
  int result, opnd_cnt, i;
  int recv_cnt, recv_len;
  struct sockaddr_in serv_adr, clnt_adr;
  socklen_t clnt_adr_sz;
  
  if(argc != 2) {
    printf("Please usage: %s <PORT>\n", argv[0]);
    exit(1);
  }
  // MAKE SOCKET
  serv_sock=socket(PF_INET, SOCK_STREAM, 0);
  if(serv_sock == -1) err_handling("socket() error.");
  memset(&serv_adr, 0, sizeof(serv_adr));
  serv_adr.sin_family=AF_INET;
  serv_adr.sin_addr.s_addr=htonl(INADDR_ANY);
  serv_adr.sin_port=htons(atoi(argv[1]));

  // MAKE BIND
  if(bind(serv_sock, (struct sockaddr*) &serv_adr, sizeof(serv_adr)) == -1)
    err_handling("bind error.");
  // NOW LISTENING
  if(listen(serv_sock, 5) == -1)
    err_handling("listen() error.");
  clnt_adr_sz=sizeof(clnt_adr);

  // ACCEPT MAXIMUM 5 CONNECTION
  for(i=0; i<5; i++){
    opnd_cnt=0;
    clnt_sock=accept(clnt_sock, (struct sockaddr*) &clnt_adr, &clnt_adr_sz);
    read(clnt_sock, &opnd_cnt, 1);
    recv_len=0;
    // READ WHEN MSG REACH EOF
    while((opnd_cnt*OPSZ+1)>recv_len){
      recv_cnt=read(clnt_sock, &opinfo[recv_len], BUF_SIZE-1);
      recv_len+=recv_cnt;
    }
    // CALCULATE OPERAND
    result=calculator(opnd_cnt, (int*)opinfo, opinfo[recv_len-1]);
    // SEND WHEN OPERAND FINISHED
    write(clnt_sock, (char*) &result, sizeof(result));
    close(clnt_sock);
  }
  close(serv_sock);
  return 0;
}
int calculator(int opnum, int opnds[], char operator){
  int result=opnds[0], i;
  switch(operator) {
    case '+':
      for(i=1; i<opnum; i++) result+=opnds[i];
      break;
    case '-':
      for(i=1; i<opnum; i++) result-=opnds[i];
      break;
    case '*':
      for(i=1; i<opnum; i++) result*=opnds[i];
      break;
  }
  return result;
};
void err_handling(char *msg){
  fputs(msg, stderr);
  fputc('\n', stderr);
  exit(1);
}

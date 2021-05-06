# Iterative socket

최대 1명을 5번 연결받을 수 있는 순차적인 소켓 서버
- for문 밑에 `accept()`를 여러번 호출함으로써 연결을 받는다.
- `read(sock, msg, buff)`와 `write(sock, msg, strlen(msg))`가 핵심.
- `socket(PF_INET,SOCK_STREAM,0)` 구조는 TCP 연결임.
- `read()`에 함정이 있는데, TCP연결 구조 상`read()`로 한번에 읽을 수 없다.
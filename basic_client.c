#include "pipe_networking.h"

int to_server; // server to client
int from_server; // client to server

static void sighandler(int signo) {
    if (signo == SIGINT) {
        printf("Client disconnected\n");
        close(from_server);
    }
}

int main() {
  signal(SIGINT, sighandler);

  printf("running client\n");
  from_server = client_handshake( &to_server );

  while (1) {
    int message;
    int ret = read(from_server, &message, sizeof(int));

    if (ret == -1) {
        break;
    } else if (ret == 0) {
        printf("Server disconnected\n");
        break;
    }

    printf("Message: %d\n", message);
  }
}

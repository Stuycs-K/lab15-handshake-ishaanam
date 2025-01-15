#include "pipe_networking.h"

int to_client; // server to client
int from_client; // client to server

pid_t child;

static void sighandler(int signo) {
    if (signo == SIGINT) {
        printf("Server disconnected\n");
        close(to_client);
        remove(WKP);
        exit(1);
    } else if (signo = SIGPIPE) {
        printf("Client disconnected\n");
    }
}

int main() {
  signal(SIGINT, sighandler);
  signal(SIGPIPE, sighandler);

  while (1) {
      from_client = server_handshake( &to_client );
      child = fork();

      if (child == 0) {
          while (1) {
            srand(time(0));
            int message = rand() % 101;
            if (write(to_client, &message, sizeof(int)) == -1) {
                break;
            }
            printf("Message: %d\n", message);
            sleep(1);
          }
      }
  }
}

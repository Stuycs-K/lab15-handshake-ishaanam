#include "pipe_networking.h"

int main() {

  int to_server;
  int from_server;

  printf("running client\n");
  from_server = client_handshake( &to_server );
}

#include "pipe_networking.h"

int main() {
  int to_client; // server to client
  int from_client; // client to server

  from_client = server_handshake( &to_client );
}

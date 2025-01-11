#include "pipe_networking.h"
//UPSTREAM = to the server / from the client
//DOWNSTREAM = to the client / from the server
/*=========================
  server_setup

  creates the WKP and opens it, waiting for a  connection.
  removes the WKP once a connection has been made

  returns the file descriptor for the upstream pipe.
  =========================*/
int server_setup() {
  int from_client = 0;
  mkfifo(WKP, 0666);

  // waiting for connection
  printf("waiting for connection\n");
  from_client = open(WKP, O_RDONLY);

  // got connection
  // printf("got connection\n"); I actually don't think this is getting the connection
  remove(WKP);

  /*
  */

  return from_client;
}

/*=========================
  server_handshake 
  args: int * to_client

  Performs the server side pipe 3 way handshake.
  Sets *to_client to the file descriptor to the downstream pipe (Client's private pipe).

  returns the file descriptor for the upstream pipe (see server setup).
  =========================*/
int server_handshake(int *to_client) {
  printf("set up server");
  int from_client = server_setup();

  char output_text[200];
  read(from_client, output_text, 200);

  // connect to PP
  printf("connect to PP\n");
  *to_client = open(output_text, O_WRONLY);

  int num = 8;
  write(*to_client, &num, sizeof(int)); // should be random int

  int ack_number;
  read(*to_client, &ack_number, sizeof(int)); // should be random int

  if (ack_number == 9) {
    printf("Connection successful\n");
  }

  return from_client;
}


/*=========================
  client_handshake
  args: int * to_server

  Performs the client side pipe 3 way handshake.
  Sets *to_server to the file descriptor for the upstream pipe.

  returns the file descriptor for the downstream pipe.
  =========================*/
int client_handshake(int *to_server) {
  int from_server;
  pid_t pid = getpid();
  char pipe_name[BUFFER_SIZE];
  sprintf(pipe_name, "%d_pipe", pid);
  mkfifo(pipe_name, 0666);

  int fd;
  printf("connecting\n");
  fd = open(WKP, O_RDWR);
  write(fd, pipe_name, sizeof(pipe_name));

  int ack_number;
  read(fd, &ack_number, sizeof(int));

  write(fd, pipe_name, sizeof(pipe_name));

  return from_server;
}


/*=========================
  server_connect
  args: int from_client

  handles the subserver portion of the 3 way handshake

  returns the file descriptor for the downstream pipe.
  =========================*/
int server_connect(int from_client) {
  int to_client  = 0;
  return to_client;
}



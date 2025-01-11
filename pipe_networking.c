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
  // Step #1
  mkfifo(WKP, 0666);

  // Step #2
  // waiting for connection
  printf("waiting for connection\n");
  int from_client = open(WKP, O_RDONLY);

  // Step #4
  printf("got connection\n");
  remove(WKP);

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
  printf("set up server\n");
  int from_client = server_setup();

  // Step #5
  char output_text[200];
  read(from_client, output_text, 200);

  // Step #6
  // connect to PP
  printf("connect to PP\n");
  *to_client = open(output_text, O_WRONLY);

  // Step #7
  int num = 8;
  write(*to_client, &num, sizeof(int)); // should be random int

  // Step #9
  int ack_number;
  read(*to_client, &ack_number, sizeof(int)); // should be random int

  ack_number += 1;
  printf("ack number: %d\n", ack_number);

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

  // Step #3
  pid_t pid = getpid();
  char pipe_name[BUFFER_SIZE];
  sprintf(pipe_name, "%d_pipe", pid);
  mkfifo(pipe_name, 0666);

  int fd;
  printf("connecting\n");
  fd = open(WKP, O_RDWR);
  write(fd, pipe_name, sizeof(pipe_name));

  int pp = open(pipe_name, O_RDWR);

  // Step #8
  printf("%s\n", pipe_name);
  remove(pipe_name);

  int ack_number;
  read(pp, &ack_number, sizeof(int));

  ack_number += 1;
  printf("ack number: %d\n", ack_number);
  write(pp, &ack_number, sizeof(int));

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



#include <time.h>

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
  printf("Step 1\n");
  mkfifo(WKP, 0666);

  // Step #2
  // waiting for connection
  printf("Step 2\n");
  printf("waiting for connection\n");
  int from_client = open(WKP, O_RDONLY, 0666);

  // Step #4
  printf("Step 4\n");
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
  printf("Step 5\n");
  char output_text[200];
  read(from_client, output_text, 200);
  printf("pipe name: %s\n", output_text);

  // Step #6
  // connect to PP
  printf("Step 6\n");
  printf("connect to PP\n");
  *to_client = open(output_text, O_WRONLY, 0666);

  // Step #7
  printf("Step 7\n");
  srand(time(0));
  int num = rand() % 101;
  write(*to_client, &num, sizeof(int)); // should be random int

  // Step #9
  printf("Step 9\n");
  int ack_number;
  int ret = read(from_client, &ack_number, sizeof(int));

  if (ret <= 0) {
    printf("error reaading ack number\n");
  }

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
  // Step #3
  printf("Step 3\n");
  pid_t pid = getpid();
  char pipe_name[BUFFER_SIZE];
  sprintf(pipe_name, "%d_pipe", pid);
  mkfifo(pipe_name, 0666);

  printf("connecting\n");
  *to_server = open(WKP, O_WRONLY, 0666);
  write(*to_server, pipe_name, strlen(pipe_name));

  int from_server = open(pipe_name, O_RDONLY, 0666);

  // Step #8
  printf("Step 8\n");
  printf("%s\n", pipe_name);

  int ack_number;
  read(from_server, &ack_number, sizeof(int));
  remove(pipe_name);

  ack_number += 1;
  printf("ack number: %d\n", ack_number);
  if (write(*to_server, &ack_number, sizeof(int)) == -1) {
    printf("error in writing ack number to server\n");
  }

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



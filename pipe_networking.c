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
  char *pipe_name = "WKP";
  mkfifo(pipe_name, 0666);

  // waiting for connection
  printf("waiting for connection\n");
  int fd = open(pipe_name, O_RDONLY);
  char output_text[200];
  read(fd, output_text, 200);
  
  // got connection
  printf("got connection\n");
  close(fd);
  remove(pipe_name);

  printf("connect to PP\n");
  from_client = open(output_text, O_WRONLY);

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
  // connect to PP
  int num = 8;
  write(fd, &num, sizeof(int)); // should be random int

  int ack_number;
  read(fd, &ack_number, sizeof(int)); // should be random int

  if (ack_number == 9) {
    printf("Connection successful\n");
  }

  int from_client;
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

  char *server_pipe = "WKP";

  int fd;
  printf("connecting\n");
  fd = open(server_pipe, O_RDWR);
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



.PHONY: clean compile client server
compile: basic_client.o basic_server.o pipe_networking.o
	gcc -o client_exec basic_client.o pipe_networking.o
	gcc -o server_exec basic_server.o pipe_networking.o
client: client_exec
	./client

server: server_exec
	./server

basic_client.o: basic_client.c pipe_networking.h
	gcc -c basic_client.c

basic_server.o: basic_server.c pipe_networking.h
	gcc -c basic_server.c

pipe_networking.o: pipe_networking.c pipe_networking.h
	gcc -c pipe_networking.c

clean:
	rm *.o

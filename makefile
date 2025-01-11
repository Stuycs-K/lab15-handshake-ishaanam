.PHONY: clean compile client server
compile: client_exec server_exec
client_exec: basic_client.o pipe_networking.o
	gcc -o client_exec basic_client.o pipe_networking.o
server_exec: basic_server.o pipe_networking.o
	gcc -o server_exec basic_server.o pipe_networking.o
client: client_exec
	./client_exec

server: server_exec
	./server_exec

basic_client.o: basic_client.c pipe_networking.h
	gcc -c basic_client.c

basic_server.o: basic_server.c pipe_networking.h
	gcc -c basic_server.c

pipe_networking.o: pipe_networking.c pipe_networking.h
	gcc -c pipe_networking.c

clean:
	rm *.o
	rm client_exec
	rm server_exec

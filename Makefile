default: client server

server: server.c serverRpc.c server_functions.c server_functions.h server_function_skels.h server_function_skels.c
	gcc -o server server.c serverRpc.c server_functions.c server_function_skels.c -ggdb -lpthread

client: client1.c clientRpc.c 
	gcc -o client client1.c clientRpc.c -ggdb

clean: 
	rm *.o client server


client:des.o client.c
	cc des.o client.c -o client
server:des.o server.c
	cc des.o server.c -o server
des.o:des.c
	cc -c des.c
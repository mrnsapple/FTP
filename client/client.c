/*
** EPITECH PROJECT, 2019
** d
** File description:
** d
*/

#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <unistd.h>
#include <arpa/inet.h>
/*
int main(int argc, char const **av) 
{ 
	int sock = 0, valread; 
	struct sockaddr_in serv_addr; 
	char buffer[1024] = {0};

	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
	{ 
		printf("\n Socket creation error \n"); 
		return -1; 
	} 
	
	memset(&serv_addr, '0', sizeof(serv_addr)); 
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(atoi(av[2]));
	serv_addr.sin_addr.s_addr = inet_addr(av[1]);
	
	
	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
	{ 
		printf("\nConnection Failed \n"); 
		return -1; 
	} 
	char *sender[] = {"USER ANONUMOUS", "PASS PASWORD", NULL};
	//while(1) {
	for (int i = 0; sender[i] != NULL; i++) {
		send(sock , sender[i], strlen(sender[i]) , 0 ); 
		printf("Hello message sent\n"); 
		valread = read( sock , buffer, 1024); 
		printf("%s\n",buffer ); 
	
	}
	//}
	return 0; 
} 
*/
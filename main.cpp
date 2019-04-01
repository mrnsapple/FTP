/*
** EPITECH PROJECT, 2019
** 203hotline_2018
** File description:
** main
*/
// Server side C/C++ program to demonstrate Socket programming 
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <sys/types.h>
#include <sys/wait.h>
#define PORT 8080

int set_socket(int port)
{
	 int		sok;
  struct sockaddr_in addr;

	if ((sok = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("setsockopt"); 
		exit(EXIT_FAILURE);   
	}
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(port);
	if (bind(sok, (struct sockaddr *)&addr, sizeof(addr)) == -1)
		perror("setsockopt"); 
	if (listen(sok, 5) == -1)
		perror("setsockopt"); 
	return (sok);
}

int	fork_stuff(int new_sock)
{
	pid_t pid = fork();
	int start;
	char *hello = (char *)"hellooooo";

	if (pid == 0) {
		printf("the child:%d\n", new_sock);
		send(new_sock, hello, strlen(hello), 0);
		exit (0);
	} //else if (pid > 0) //	close (new_sock);
	else if (pid < 0) {
		return 84;
	}
	else if (pid > 0) {
		waitpid(pid, &start, 0);
		close(new_sock);
	}
	return 0;
}

int	loop(int sock, int port)
{
	struct sockaddr_in adr;
  	int		ads = sizeof(adr);
	int new_sock;

	printf("INFO : Server started on port %d.\n", port);
	for (int i = 0; i == 0; i = 0) {
		new_sock = accept(sock, (struct sockaddr*)&adr, (socklen_t*)(&ads));
		printf("the child loop:%d\n", new_sock);
		if (new_sock > 0)
			fork_stuff(new_sock);
	} 
	close(sock);
	return 0;	
}

int main(int ac, char **av)
{
	int sock;
	int port;

	if (ac == 2 && av != NULL) {
		port = atoi(av[1]);
		sock = set_socket(port);
		return (loop(sock, port));
	}
	return 84;
}
/*
int main(int argc, char const *argv[]) 
{ 
	int server_fd, new_socket, valread; 
	struct sockaddr_in address; 
	int opt = 1; 
	int addrlen = sizeof(address); 
	char buffer[1024] = {0}; 
	char *hello = "Hello from server"; 
	
	// Creating socket file descriptor 
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
	{ 
		perror("socket failed"); 
		exit(EXIT_FAILURE); 
	} 
	
	// Forcefully attaching socket to the port 8080 
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
												&opt, sizeof(opt))) 
	{ 
		perror("setsockopt"); 
		exit(EXIT_FAILURE); 
	} 
	address.sin_family = AF_INET; 
	address.sin_addr.s_addr = INADDR_ANY; 
	address.sin_port = htons( PORT ); 
	
	// Forcefully attaching socket to the port 8080 
	if (bind(server_fd, (struct sockaddr *)&address, 
								sizeof(address))<0) 
	{ 
		perror("bind failed"); 
		exit(EXIT_FAILURE); 
	} 
	if (listen(server_fd, 3) < 0) 
	{ 
		perror("listen"); 
		exit(EXIT_FAILURE); 
	} 
	if ((new_socket = accept(server_fd, (struct sockaddr *)&address, 
					(socklen_t*)&addrlen))<0) 
	{ 
		perror("accept"); 
		exit(EXIT_FAILURE); 
	} 
	valread = read( new_socket , buffer, 1024); 
	printf("%s\n",buffer ); 
	send(new_socket , hello , strlen(hello) , 0 ); 
	printf("Hello message sent\n"); 
	return 0; 
} 
*/
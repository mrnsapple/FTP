/*
** EPITECH PROJECT, 2019
** d
** File description:
** d
*/

#include "list.h"

int	select_encap(list_t *l)
{
	l->read_fd_set = l->active_fd_set;

	return (select (l->new_sock, &(l->read_fd_set), NULL, NULL, NULL) < 0);
}

int	loop(list_t *l)
{
	l->ads = sizeof(l->adr);
	printf("INFO : Server started on port %d.\n", l->port);

	for (int i = 0; i == 0; i = 0) {
		l->new_sock = accept(l->sock, (struct sockaddr*)&(l->adr), (socklen_t*)(&(l->ads)));
		printf("the child loop:%d\n", l->new_sock);
		if (l->new_sock > 0)
			fork_stuff(l);
	} 
	close(l->sock);
	return 0;	
}

int main(int ac, char **av)
{
	list_t *l = malloc(sizeof(list_t));

	if (ac == 2 && av != NULL && l != NULL) {
		l->port = atoi(av[1]);
		l->sock = set_socket(l->port);
		return (loop(l));
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
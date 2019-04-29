/*
** EPITECH PROJECT, 2019
** d
** File description:
** d
*/

#include "list.h"

list_t *l;

int select_encap(list_t *l)
{
    return (select (FD_SETSIZE, &(l->read_fd_set), NULL, NULL, NULL));
}

void	print_current_clients(client_sock_t   *client_socket)
{
	while(client_socket != NULL) {
		printf("client_socket:%d\n", client_socket->client_socket);
		client_socket = client_socket->next;
	}
}

int loop(list_t *l)
{
	l->ads = sizeof(struct sockaddr_in);
	printf("INFO : Server started on port %d.\n", l->port);
	while(1) {
		FD_ZERO (&(l->read_fd_set));
		FD_SET (l->sock, &(l->read_fd_set));
		add_client_to_sockket(l);
		select_encap(l);
		for (int i = 0; i < FD_SETSIZE; ++i)
		 	if (FD_ISSET (i, &(l->read_fd_set))) {
				accept_client(i, l);
				//interact_with_client(l);
			}
		//print_current_clients(l);
	} 
	printf("outside_loop\n");
	close(l->sock);
	return 0;	
}

int	print_help()
{
	printf("USAGE: ./myftp port path\n");
	printf("\tport is the port number on which the server socket listens\n");
	printf("\tpath is the path to the home directory for the Anonymous user\n");
	return (0);
}

void	close_socket(int dummy)
{
	if (l != NULL) {
		close(l->sock);
		printf("closed _soket: %d\n", l->sock);
	}
	exit(0);
}


int main(int ac, char **av)
{
	l = malloc(sizeof(list_t));
	l->read = malloc(sizeof(read_t));

	signal(SIGINT, close_socket);
	if (ac == 2 && av != NULL && l != NULL && l->read != NULL) {
		if (strcmp("-help", av[1]) == 0)
			return (print_help());
		l->port = atoi(av[1]);
		set_socket(l);
		set_options(l);
		return (loop(l));
	}
	return 84;
}

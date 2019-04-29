/*
** EPITECH PROJECT, 2019
** d
** File description:
** d
*/

#include "list.h"

list_t *l;

int select_encap(fd_set *read_fd_set)
{
    return (select (FD_SETSIZE, read_fd_set, NULL, NULL, NULL));
}

int loop(list_t *l)
{
	printf("INFO : Server started on port %d.\n", l->port);
	while(1) {
		FD_ZERO (&(l->read_fd_set));
		FD_SET (l->sock, &(l->read_fd_set));
		select_encap(&(l->read_fd_set));
		for (int i = 0; i < FD_SETSIZE; ++i)
		 	if (FD_ISSET (i, &(l->read_fd_set))) {
				accept_client(i, l);
			}
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

void	close_socket()
{
	if (l != NULL) {
		close(l->sock);
		printf("closed _soket: %d\n", l->sock);
	}
	exit(0);
}

int	my_ftp(int ac, char **av)
{
	l = malloc(sizeof(list_t));

	signal(SIGINT, close_socket);
	if (ac == 3 && av != NULL && l != NULL) {
		if (strcmp("-help", av[1]) == 0)
			return (print_help());
		l->port = atoi(av[1]);
		l->path = av[2];
		set_socket(l);
		set_options(l);
		return (loop(l));
	}
	return 84;
}

int main(int ac, char **av)
{
	return (my_ftp(ac, av));
}

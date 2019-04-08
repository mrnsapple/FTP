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
	return (select (FD_SETSIZE, &(l->read_fd_set), NULL, NULL, NULL));
}

int	loop(list_t *l)
{
	l->ads = sizeof(l->adr);
	printf("INFO : Server started on port %d.\n", l->port);
	FD_ZERO (&(l->active_fd_set));
	FD_SET (l->sock, &(l->active_fd_set));
	for (l->counter = 0; l->counter >= 0; l->counter++) {
		select_encap(l);
		for (int i = 0; i < FD_SETSIZE; ++i)
		 	if (FD_ISSET (i, &(l->read_fd_set)))
          		inside_stuff(i, l);
	} 
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

int main(int ac, char **av)
{
	list_t *l = malloc(sizeof(list_t));

	if (ac == 2 && av != NULL && l != NULL) {
		if (strcmp("-help", av[1]) == 0)
			return (print_help());
		l->port = atoi(av[1]);
		set_socket(l);
		set_options(l);
		return (loop(l));
	}
	return 84;
}
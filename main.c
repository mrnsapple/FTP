/*
** EPITECH PROJECT, 2019
** d
** File description:
** d
*/

#include "list.h"

list_t *my_var;

int select_encap(fd_set *read_fd_set)
{
    return (select (FD_SETSIZE, read_fd_set, NULL, NULL, NULL));
}

int loop(list_t *my_var)
{
    printf("INFO : Server started on port %d.\n", my_var->port);
    while(1) {
        FD_ZERO (&(my_var->read_fd_set));
        FD_SET (my_var->sock, &(my_var->read_fd_set));
        select_encap(&(my_var->read_fd_set));
        for (int i = 0; i < FD_SETSIZE; ++i)
            if (FD_ISSET (i, &(my_var->read_fd_set))) {
                accept_client(i, my_var);
            }
    } 
    printf("outside_loop\n");
    close(my_var->sock);
    return 0;	
}

int print_help(void)
{
    printf("USAGE: ./myftp port path\n");
    printf("\tport is the port number on which the server socket listens\n");
    printf("\tpath is the path to the home directory for the Anonymous user\n");
    return (0);
}

void    close_socket(int sock)
{
    if (my_var != NULL) {
        close(my_var->sock);
        printf("closed _soket: %d\n", my_var->sock);
    }
    if (sock == 0)
        exit(0);
    exit(0);
}

int	my_ftp(int ac, char **av)
{
    my_var = malloc(sizeof(list_t));
    signal(SIGINT, close_socket);
    if (ac == 3 && av != NULL && my_var != NULL) {
        if (strcmp("-help", av[1]) == 0)
            return (print_help());
        my_var->port = atoi(av[1]);
        my_var->path = av[2];
        set_socket(my_var);
        set_options(my_var);
        return (loop(my_var));
    }
    return 84;
}

int main(int ac, char **av)
{
    return (my_ftp(ac, av));
}

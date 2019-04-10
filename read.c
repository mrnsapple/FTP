/*
** EPITECH PROJECT, 2019
** read
** File description:
** by oriol
*/

#include "list.h"

void    initialize_clients(list_t   *l)
{
    for (int i = 0; i < MAX_CLIENTS; i++)
        l->client_socket[i] = 0;
}

void    add_client_to_sockket(list_t    *l)
{
    for (int i = 0; i < MAX_CLIENTS; i++)
        if (l->client_socket[i] > 0)
            FD_SET(l->client_socket[i], &(l->read_fd_set));
}

void	add_new_socket(list_t   *l, int   new_socket)
{
    for (int    i = 0; i < MAX_CLIENTS; i++)
        if (l->client_socket[i] == 0) {
            l->client_socket[i] = new_socket;
            printf("added client:%d\n", l->client_socket[i]);
            break;
        }
}

int read_stuff(list_t   *l)
{
    int result;

    printf("current:%d",l->current_socket);
    bzero(l->read->buff, 2000);
    printf("current:%d",l->current_socket);
    result = read(l->current_socket, l->read->buff, 2000);
    printf("read:%s\n", l->read->buff);
    if (result <= 0) {
        perror("read error\n");
        return (result);
    }
    l->read->buff[result] = '\0';
    l->read->buff_array = my_str_to_wordtab(l->read->buff, ' ');
    l->read->buff_array_size = len_array(l->read->buff_array);
    return (result);
}

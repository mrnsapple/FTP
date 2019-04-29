/*
** EPITECH PROJECT, 2019
** read
** File description:
** by oriol
*/

#include "list.h"

int    add_clients(client_sock_t **client_list, int client_value)
{
    client_sock_t *client_sock;
    client_sock_t *client = *client_list;

    client_sock = malloc(sizeof(client_sock_t));
    client_sock->client_socket = client_value;
    client_sock->next = NULL;
    if (client == NULL) {
        printf("in if\n");

        (*client_list) = client_sock;
    }
    else {
        while (client->next != NULL) {
            printf("in while\n");
           client = client->next;
        }
        client->next = client_sock;
    }
    return (0);
}

int   add_client_to_sockket(list_t    *l)
{   
    client_sock_t *client_sock;

    if (l == NULL)
        return (84);
    client_sock = l->client_socket;
    while (client_sock != NULL) {
        printf("setting client: %d\n", client_sock->client_socket);
        FD_SET(client_sock->client_socket, &(l->read_fd_set));
        client_sock = client_sock->next;
    }
    return (0);
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

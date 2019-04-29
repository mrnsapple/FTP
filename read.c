/*
** EPITECH PROJECT, 2019
** read
** File description:
** by oriol
*/

#include "list.h"

/*int    add_clients(client_sock_t **client_list, int client_value)
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
}*/

read_t  *read_stuff(int child_socket, read_t *reader)
{
    int result;

    if (reader == NULL)
        return (NULL);
    //printf("current:%d",l->current_socket);
    bzero(reader->buff, 2000);
    //printf("current:%d",l->current_socket);
    result = read(child_socket, reader->buff, 2000);
    //printf("read:%s\n", l->read->buff);
    if (result <= 0) {
        //perror("read error\n");
        free(reader);
        return (NULL);
    }
    reader->buff[result] = '\0';
    reader->buff_array = my_str_to_wordtab(reader->buff, ' ');
    reader->buff_array_size = len_array(reader->buff_array);
    return (reader);
}

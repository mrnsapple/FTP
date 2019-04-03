/*
** EPITECH PROJECT, 2019
** read
** File description:
** by oriol
*/

#include "list.h"

int        read_stuff(list_t *l)
{
    int result;

    result = read(l->new_sock, l->buff, 2000);
    printf("result:%d\n", result);

    if (result <= 0)
        return -1;
    if (result <= 0) {
      return (-1);
    }
    printf("result:%s\n", l->buff);
    return (0);
    //for (i = 0; i < r; i++)
    //    if (ct->buffer[i] == '\n' || clt->buffer[i] == '\r')
    //    clt->buffer[i] = '\0';
}
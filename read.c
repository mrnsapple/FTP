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

    bzero(l->buff, 2000);
    result = read(l->new_sock, l->buff, 2000);
    if (result <= 0) {
        perror("read error\n");
        //l->counter = -10;
        exit (0);
    }
    l->buff[result] = '\0';
    l->buff_array = my_str_to_wordtab(l->buff, ' ');
    l->buff_array_size = len_array(l->buff_array);
    return (0);
}
/*
** EPITECH PROJECT, 2019
** send
** File description:
** bur ooipol
*/

#include "list.h"

void    user_authentification(list_t *l)
{
    if (l->buff_array_size == 2 &&
        strcmp("USER", l->buff_array[0]) == 0)
        send_specific_code(l, 331);
}

void    password_authentification(list_t *l)
{
    if (l->buff_array_size == 2 &&
        strcmp("PASS", l->buff_array[0]) == 0)
        send_specific_code(l, 230);

}

void    set_options(list_t *l)
{
    l->options[0] = &user_authentification;
    l->options[1] = &password_authentification;
    l->options[2] = NULL;

}

void    try_options(list_t *l)
{
    for(int i =0 ; l->buff_array[i] != NULL; i++) {
        printf("s:%s\n", l->buff_array[i]);
    }
    for (int i = 0; l->options[i] != NULL; i++) {
        (l->options[i])(l);
    }
}
//if ((l->counter == 0 && reply_codes_num[i] == 220) || (l->counter == 1 && reply_codes_num[i] == 331))
//	send(l->new_sock, reply_codes[i], strlen(reply_codes[i]), 0);
			
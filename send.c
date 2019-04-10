/*
** EPITECH PROJECT, 2019
** send
** File description:
** bur ooipol
*/

#include "list.h"

void    user_authentification(list_t *l)
{
    if (l->read->buff_array_size == 2 &&
        strcmp("USER", l->read->buff_array[0]) == 0)
        send_specific_code(l, 331);
}

void    password_authentification(list_t *l)
{
    if (l->read->buff_array_size == 2 &&
        strcmp("PASS", l->read->buff_array[0]) == 0)
        send_specific_code(l, 230);
    
}

void    cwd(list_t *l)
{
    if (l->read->buff_array_size == 2 &&
        strcmp("CWD", l->read->buff_array[0]) == 0)
        send_specific_code(l, 250);
}

void    cdup(list_t *l)
{
    if (l->read->buff_array_size == 2 &&
        strcmp("CDUP", l->read->buff_array[0]) == 0)
        send_specific_code(l, 200);
}

void    quit(list_t *l)
{
    if (l->read->buff_array_size == 2 &&
        strcmp("QUIT", l->read->buff_array[0]) == 0)
        send_specific_code(l, 221);
}

void    delete(list_t *l)
{
    if (l->read->buff_array_size == 2 &&
        strcmp("DELETE", l->read->buff_array[0]) == 0)
        send_specific_code(l, 250);
}

void    pwd(list_t *l)
{
    if (l->read->buff_array_size == 2 &&
        strcmp("PWD", l->read->buff_array[0]) == 0)
        send_specific_code(l, 257);
}

void    pasv(list_t *l)
{
    if (l->read->buff_array_size == 2 &&
        strcmp("PASV", l->read->buff_array[0]) == 0)
        send_specific_code(l, 227);
}

void    port(list_t *l)
{
    if (l->read->buff_array_size == 2 &&
        strcmp("PORT", l->read->buff_array[0]) == 0)
        send_specific_code(l, 200);
}

void    help(list_t *l)
{
    if (l->read->buff_array_size == 2 &&
        strcmp("HELP", l->read->buff_array[0]) == 0)
        send_specific_code(l, 214);
}

void    noop(list_t *l)
{
    if (l->read->buff_array_size == 2 &&
        strcmp("NOOP", l->read->buff_array[0]) == 0)
        send_specific_code(l, 200);
}

void    retr(list_t *l)
{
    if (l->read->buff_array_size == 2 &&
        strcmp("RETR", l->read->buff_array[0]) == 0)
        send_specific_code(l, 150);
}

void    stor(list_t *l)
{
    if (l->read->buff_array_size == 2 &&
        strcmp("STOR", l->read->buff_array[0]) == 0)
        send_specific_code(l, 150);
}

void    list(list_t *l)
{
    if (l->read->buff_array_size == 2 &&
        strcmp("LIST", l->read->buff_array[0]) == 0)
        send_specific_code(l, 150);
}

void    set_options(list_t *l)
{
    l->options[0] = &user_authentification;
    l->options[1] = &password_authentification;
    l->options[2] = &cwd;
    l->options[3] = &cdup;
    l->options[4] = &quit;
    l->options[5] = &delete;
    l->options[6] = &pwd;
    l->options[7] = &pasv;
    l->options[8] = &port;
    l->options[9] = &help;
    l->options[10] = &noop;
    l->options[11] = &retr;
    l->options[12] = &stor;
    l->options[12] = &list;
    l->options[13] = NULL;
}

void    try_options(list_t *l)
{
    for(int i =0 ; l->read->buff_array[i] != NULL; i++) {
        printf("s:%s\n", l->read->buff_array[i]);
    }
    for (int i = 0; l->options[i] != NULL; i++) {
        (l->options[i])(l);
    }
}

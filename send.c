/*
** EPITECH PROJECT, 2019
** send
** File description:
** bur ooipol
*/

#include "list.h"

void    user_authentification(int child_socket, read_t  *read)
{
    if (read->buff_array_size == 2 &&
        strcmp("USER", read->buff_array[0]) == 0)
        send_specific_code(child_socket, 331);
}

void    password_authentification(int child_socket, read_t  *read)
{
    if (read->buff_array_size == 2 &&
        strcmp("PASS", read->buff_array[0]) == 0)
        send_specific_code(child_socket, 230);
    
}

void    cwd(int child_socket, read_t  *read)
{
    if (read->buff_array_size == 2 &&
        strcmp("CWD", read->buff_array[0]) == 0)
        send_specific_code(child_socket, 250);
}

void    cdup(int child_socket, read_t  *read)
{
    if (read->buff_array_size == 2 &&
        strcmp("CDUP", read->buff_array[0]) == 0)
        send_specific_code(child_socket, 200);
}

void    quit(int child_socket, read_t  *read)
{
    if (read->buff_array_size == 2 &&
        strcmp("QUIT", read->buff_array[0]) == 0)
        send_specific_code(child_socket, 221);
}

void    delete(int child_socket, read_t  *read)
{
    if (read->buff_array_size == 2 &&
        strcmp("DELETE", read->buff_array[0]) == 0)
        send_specific_code(child_socket, 250);
}

void    pwd(int child_socket, read_t  *read)
{
    if (read->buff_array_size == 2 &&
        strcmp("PWD", read->buff_array[0]) == 0)
        send_specific_code(child_socket, 257);
}

void    pasv(int child_socket, read_t  *read)
{
    if (read->buff_array_size == 2 &&
        strcmp("PASV", read->buff_array[0]) == 0)
        send_specific_code(child_socket, 227);
}

void    port(int child_socket, read_t  *read)
{
    if (read->buff_array_size == 2 &&
        strcmp("PORT", read->buff_array[0]) == 0)
        send_specific_code(child_socket, 200);
}

void    help(int child_socket, read_t  *read)
{
    if (read->buff_array_size == 2 &&
        strcmp("HELP", read->buff_array[0]) == 0)
        send_specific_code(child_socket, 214);
}

void    noop(int child_socket, read_t  *read)
{
    if (read->buff_array_size == 2 &&
        strcmp("NOOP", read->buff_array[0]) == 0)
        send_specific_code(child_socket, 200);
}

void    retr(int child_socket, read_t  *read)
{
    if (read->buff_array_size == 2 &&
        strcmp("RETR", read->buff_array[0]) == 0)
        send_specific_code(child_socket, 150);
}

void    stor(int child_socket, read_t  *read)
{
    if (read->buff_array_size == 2 &&
        strcmp("STOR", read->buff_array[0]) == 0)
        send_specific_code(child_socket, 150);
}

void    list(int child_socket, read_t  *read)
{
    if (read->buff_array_size == 2 &&
        strcmp("LIST", read->buff_array[0]) == 0)
        send_specific_code(child_socket, 150);
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

int    try_options(int child_socket, read_t  *read, void (*options[LEN_OPTIONS])(int child_socket, read_t  *read))
{
    if (read == NULL)
        return (-1);
    for(int i = 0; read->buff_array[i] != NULL; i++) {
        printf("s:%s\n", read->buff_array[i]);
    }
    for (int i = 0; options[i] != NULL; i++) {
        (options[i])(child_socket, read);
    }
    return (0);
}

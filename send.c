/*
** EPITECH PROJECT, 2019
** send
** File description:
** bur ooipol
*/

#include "list.h"

int    chose_and_send_code(int child_socket, int specific_code, read_t *read)
{
    if (read->is_autentificated == 0) {
        send_specific_code(child_socket, 530);
        return (-1);
    }
    send_specific_code(child_socket, specific_code);
    return (0);
}

void    user_authentification(int child_socket, read_t  *read)
{
    if (read->buff_array_size == 2 &&
        strcmp("USER", read->buff_array[0]) == 0)
            chose_and_send_code(child_socket, 331, read);

}

void    password_authentification(int child_socket, read_t *read)
{
    if (read->buff_array_size == 2 &&
        strcmp("PASS", read->buff_array[0]) == 0)
            chose_and_send_code(child_socket, 230, read);
    
}

void    cwd(int child_socket, read_t *read)
{
    if (read->buff_array_size == 2 &&
        strcmp("CWD", read->buff_array[0]) == 0) {
        if (chose_and_send_code(child_socket, 250, read) == 0)
            read->dir = read->buff_array[1];
    }
}

void    cdup(int child_socket, read_t *read)
{
    if (read->buff_array_size == 1 &&
        strcmp("CDUP", read->buff_array[0]) == 0) {
        if (chose_and_send_code(child_socket, 200, read) == 0)
            read->dir = get_parent_dir(read->dir);    
    }
}

void    quit(int child_socket, read_t *read)
{
    if (read->buff_array_size == 1 &&
        strcmp("QUIT", read->buff_array[0]) == 0) {
        chose_and_send_code(child_socket, 221, read);
        exit(0);
    }
}

void    delete(int child_socket, read_t *read)
{
    if (read->buff_array_size == 2 &&
        strcmp("DELETE", read->buff_array[0]) == 0) {
        if (read->is_autentificated == 0)
            send_specific_code(child_socket, 530);
        else if (remove(read->buff_array[0]) == 0) 
            send_specific_code(child_socket, 250);
        else
            send_specific_code(child_socket, 550);  
    }
}

void    pwd(int child_socket, read_t *read)
{
    char *result;

    if (read->buff_array_size == 1 &&
        strcmp("PWD", read->buff_array[0]) == 0) {
        result = "257 ";
        strcat(result, read->dir);
        strcat(result, " created.\n");
        if (read->is_autentificated == 0)
            send_specific_code(child_socket, 530);
        else
            write(child_socket, result, strlen(result));
    } 
}

void    pasv(int child_socket, read_t *read)
{
    if (read->buff_array_size == 1 &&
        strcmp("PASV", read->buff_array[0]) == 0)
            chose_and_send_code(child_socket, 227, read);
}

void    port(int child_socket, read_t *read)
{
    if (read->buff_array_size == 2 &&
        strcmp("PORT", read->buff_array[0]) == 0)
            chose_and_send_code(child_socket, 200, read);
}

void    help(int child_socket, read_t *read)
{
    if (read->buff_array_size == 2 &&
        strcmp("HELP", read->buff_array[0]) == 0)
        chose_and_send_code(child_socket, 214, read);
}

void    noop(int child_socket, read_t *read)
{
    if (read->buff_array_size == 1 &&
        strcmp("NOOP", read->buff_array[0]) == 0)
            chose_and_send_code(child_socket, 200, read);
}

void    retr(int child_socket, read_t *read)
{
    if (read->buff_array_size == 2 &&
        strcmp("RETR", read->buff_array[0]) == 0)
            chose_and_send_code(child_socket, 150, read);
}

void    stor(int child_socket, read_t *read)
{
    if (read->buff_array_size == 2 &&
        strcmp("STOR", read->buff_array[0]) == 0)
        chose_and_send_code(child_socket, 150, read);
}

void    list(int child_socket, read_t *read)
{
    if (read->buff_array_size == 2 &&
        strcmp("LIST", read->buff_array[0]) == 0)
        chose_and_send_code(child_socket, 150, read);
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

int    try_options(int child_socket, read_t  *read, void (*options[LEN_OPTIONS])(int child_socket, read_t *read))
{
    if (read == NULL)
        return (-1);
    for(int i = 0; read->buff_array[i] != NULL; i++) {
        printf("s:%s, dir:%s\n", read->buff_array[i],read->dir);
    }
    for (int i = 0; options[i] != NULL; i++) {
        printf("doing option\n");
        (options[i])(child_socket, read);
        printf("dir:%s\n", read->dir);

    }
    return (0);
}

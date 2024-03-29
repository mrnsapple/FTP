/*
** EPITECH PROJECT, 2019
** send
** File description:
** bur ooipol
*/

#include "list.h"

int chose_and_send_code(int child_socket, int specific_code, read_t *read)
{
    read->any_instruction_sent = 1;
    if (read->is_autentificated == 0 || read->is_autentificated == 1) {
        send_specific_code(child_socket, 530);
        return (-1);
    }
    send_specific_code(child_socket, specific_code);
    return (0);
}

void user_authentification(int child_socket, read_t  *read)
{
    if (read->buff_array_size == 2 &&
        strcmp("USER", read->buff_array[0]) == 0) {
        send_specific_code(child_socket, 331);
        read->is_autentificated = 1;
        read->any_instruction_sent = 1;
        if (strcmp("Anonymous", read->buff_array[1]) == 0)
            read->is_anonimous = 1;
    }
}

void password_authentification(int child_socket, read_t *read)
{
    if ((read->buff_array_size == 2  || (read->buff_array_size == 1 && read->is_anonimous == 1)) &&
        strcmp("PASS", read->buff_array[0]) == 0) {
        if (read->is_autentificated == 0 || read->is_autentificated == 1)
            read->any_instruction_sent = 1;
        if (read->is_autentificated == 0)
            send_specific_code(child_socket, 530);
        else if (read->is_autentificated == 1) {
            send_specific_code(child_socket, 230);
            read->is_autentificated = 2;
        } 
    }
}

void cwd(int child_socket, read_t *read)
{
    if (read->buff_array_size == 2 &&
        strcmp("CWD", read->buff_array[0]) == 0)
        if (chose_and_send_code(child_socket, 250, read) == 0)
            read->dir = read->buff_array[1];
}

void cdup(int child_socket, read_t *read)
{
    if (read->buff_array_size == 1 &&
        strcmp("CDUP", read->buff_array[0]) == 0)
        if (chose_and_send_code(child_socket, 200, read) == 0)
            read->dir = get_parent_dir(read->dir);    
}

void quit(int child_socket, read_t *read)
{
    if (read->buff_array_size == 1 &&
        strcmp("QUIT", read->buff_array[0]) == 0) {
        chose_and_send_code(child_socket, 221, read);
        exit(0);
    }
}

void delete(int child_socket, read_t *read)
{
    if (read->buff_array_size == 2 &&
        strcmp("DELETE", read->buff_array[0]) == 0) {
        read->any_instruction_sent = 1;
        if (read->is_autentificated == 0 || read->is_autentificated == 1)
            send_specific_code(child_socket, 530);
        else if (remove(read->buff_array[0]) == 0) 
            send_specific_code(child_socket, 250);
        else
            send_specific_code(child_socket, 550);  
    }
}

void pwd(int child_socket, read_t *read)
{
    char result[200];

    if (read->buff_array_size == 1 &&
        strcmp("PWD", read->buff_array[0]) == 0) {
        read->any_instruction_sent = 1;
        if (read->is_autentificated == 0 || read->is_autentificated == 1)
            send_specific_code(child_socket, 530);
        else {
            strcpy(result,"257 ");
            strcat(result,read->dir );
            strcat(result, " created.\n");        
            write(child_socket, result, strlen(result));
        }
    } 
}

void pasv(int child_socket, read_t *read)
{
    if (read->buff_array_size == 1 &&
        strcmp("PASV", read->buff_array[0]) == 0)
        chose_and_send_code(child_socket, 227, read);
}

void port(int child_socket, read_t *read)
{
    if (read->buff_array_size == 2 &&
        strcmp("PORT", read->buff_array[0]) == 0)
        chose_and_send_code(child_socket, 200, read);
}

void help(int child_socket, read_t *read)
{
    if (read->buff_array_size == 1 &&
        strcmp("HELP", read->buff_array[0]) == 0)
        chose_and_send_code(child_socket, 214, read);
}

void noop(int child_socket, read_t *read)
{
    if (read->buff_array_size == 1 &&
        strcmp("NOOP", read->buff_array[0]) == 0)
        chose_and_send_code(child_socket, 200, read);
}

void retr(int child_socket, read_t *read)
{
    if (read->buff_array_size == 2 &&
        strcmp("RETR", read->buff_array[0]) == 0)
        chose_and_send_code(child_socket, 150, read);
}

void stor(int child_socket, read_t *read)
{
    if (read->buff_array_size == 2 &&
        strcmp("STOR", read->buff_array[0]) == 0)
        chose_and_send_code(child_socket, 150, read);
}

void list(int child_socket, read_t *read)
{
    if (read->buff_array_size == 2 &&
        strcmp("LIST", read->buff_array[0]) == 0)
        chose_and_send_code(child_socket, 150, read);
}

void syntax_error(int child_socket, read_t *read)
{
    if (read->buff_array == NULL || strcmp("", read->buff_array[0]) == 0 ||
        read->any_instruction_sent == 0)
        send_specific_code(child_socket, 500);
}

void set_options(list_t *my_var)
{
    my_var->options[0] = &user_authentification;
    my_var->options[1] = &password_authentification;
    my_var->options[2] = &cwd;
    my_var->options[3] = &cdup;
    my_var->options[4] = &quit;
    my_var->options[5] = &delete;
    my_var->options[6] = &pwd;
    my_var->options[7] = &pasv;
    my_var->options[8] = &port;
    my_var->options[9] = &help;
    my_var->options[10] = &noop;
    my_var->options[11] = &retr;
    my_var->options[12] = &stor;
    my_var->options[12] = &list;
    my_var->options[13] = &syntax_error;
    my_var->options[14] = NULL;
}

int try_options(int child_socket, read_t  *read,
                void (*options[LEN_OPTIONS])(int child_socket,
                                             read_t *read))
{
    if (read == NULL)
        return (-1);
    read->any_instruction_sent = 0;
    for (int i = 0; options[i] != NULL; i++)
        (options[i])(child_socket, read);
    read->any_instruction_sent = 0;
    return (0);
}

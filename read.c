/*
** EPITECH PROJECT, 2019
** read
** File description:
** by oriol
*/

#include "list.h"

char   **delete_spaces(char **av)
{
    if (av == NULL)
        return (NULL);
    for (int i = 0; av[i] != NULL; i++)
        for (int g = 0; av[i][g] != '\0'; g++)
            if (av[i][g] == '\n' || av[i][g] == '\t')
                av[i][g] = '\0';
    return (av);
}

read_t  *read_stuff(int child_socket, read_t *reader)
{
    int result;
    char *av;

    if (reader == NULL)
        return (NULL);
    bzero(reader->buff, 2000);
    result = read(child_socket, reader->buff, 2000);
    if (result <= 0) {
        free(reader);
        return (NULL);
    }
    reader->buff[result - 2] = ' ';
    reader->buff[result - 1] = '\n';
    reader->buff[result] = '\0';
    av = strcat(reader->buff, "");
    reader->buff_array = my_str_to_wordtab(av, ' ');
    reader->buff_array = delete_spaces(reader->buff_array);
    reader->buff_array_size = len_array(reader->buff_array);
    return (reader);
}

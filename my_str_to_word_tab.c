/*
** EPITECH PROJECT, 2019
** me
** File description:
** e
*/

#include "list.h"

int count_space(char *str, char x)
{
    int	a = 0;
    int	b = 0;

    while (str[a]) {
        while (str[a] == x)
            a++;
        while (str[a] != x && str[a] != '\0')
            a++;
        b++;
    }
    return (b);
}

char **my_str_to_wordtab(char *str, char x)
{
    int	a = 0;
    int	b;
    int c = 0;
    char    **tab;

    tab = malloc(sizeof(char *) * (count_space(str, x) + 1));
    while (str[c]) {
        b = 0;
        tab[a] = malloc(sizeof(char) * (strlen(str) + 1));
        while(str[c] == x)
            c++;
        while (str[c] != x && str[c] != '\0')
            tab[a][b++] = str[c++];
        tab[a][b] = '\0';
        a++;
    }
    tab[a] = NULL;
    return (tab);
}

int len_array(char **av)
{
    int result = 0;

    for (result = 0; av != NULL && av[result] != NULL; result++);
    if (result <= 0)
        return 0;
    result = result - 1;
    return (result);
}

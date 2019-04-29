/*
** EPITECH PROJECT, 2019
** get_pwd
** File description:
** by oriol
*/

#include "../list.h"
#include <stdio.h>
#include <string.h>

char *get_parent_dir(char *dir)
{
    int i = 0;
    int size;
	char *result;

    if (dir == NULL)
        return (NULL);
    size = strlen(dir);
    for (i = 0; dir[i] != '\0'; i++);

    for (i = i; i >= 0 && dir[i] != '/' ; i--);
    if (i == 0)
        return ("/");
    result = malloc(sizeof(char) * (size - i + 1));
    printf("ula:%d\n", i);
    for (int g = 0; g != size - i; g++)
        result[g] = dir[g];
    result[size - i - 1] = '\0';
    return (result);
    
}
/*
int main()
{
    printf("dir:%s\n", get_parent_dir("/home/oriol/"));
        printf("dir:%s\n", get_parent_dir("/home"));
                printf("dir:%s\n", get_parent_dir("/"));
}*/
/*char    *get_working_dir(void)
{
	char	cwd[1024];

	if (getcwd(cwd, 1024) != NULL)
        return (cwd);
    return (NULL);
}
*/
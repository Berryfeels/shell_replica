#include "../include/minishell.h"

int execute_command(char **av, bld_in *builtins)
{
    bld_in  *builtin;
    
    if (av[0] == NULL)
        return (1);
    builtin = find_builtin(builtins, av[0]);
    if (builtin)
        builtin->func(av);
    else
    {
        if (execvp(av[0], av) == -1)
            perror("Mestepum> ");
    }
    return (0);
}

bld_in  *find_buidtin(bld_in *head, const char *command)
{
    while (head != NULL)
    {
        if (strcmp (head->name, command) == 0)
            return (head);
        head = head->next;
    }
    return (NULL);
}

int is_bltin(char *command)
{
    const char  *bltins[] = {"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL};
    int         i;

    i = 0;
    while (bltins[i])
    {
        if (ft_strcmp (command, bltins[i]) == 0)
            return (1);
    }
    return (0);
}
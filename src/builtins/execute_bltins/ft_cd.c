#include "../include/minishell.h"

void    update_env(const char *key, const char *value)
{
    if (value)
        setenv(key, value, 1);
}

void    handle_cd(char **av)
{
    char    cwd[1024];
    char    *home;
    char    *oldpwd;

    home = getenv("HOME");
    if (!av[1])
    {
        if (!home)
        {
            fprintf (stderr, "cd: HOME not set\n");
            return ;
        }
        if (chdir (home) == 0)
            update_env ("OLDPWD", cwd);
    }
    else if (strcmp(av[1], "-") == 0)
    {
        oldpwd = getenv("OLDPWD");
        if (!oldpwd)
        {
            fprintf (stderr, "cd: OLDPWD not set\n");
            return ;
        }
    }
    else
    {
        if (chdir(av[1]) == 0)
            update_env("OLDPWD", cwd);
        else
            perror ("cd");
    }
    if (getcwd (cwd, sizeof(cwd)))
        update_env ("PWD", cwd);
}
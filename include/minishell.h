/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdi-pum <stdi-pum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 15:49:08 by stdi-pum          #+#    #+#             */
/*   Updated: 2024/10/04 15:25:14 by stdi-pum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <unistd.h>
# include "../lib/dprintf/ft_dprintf.h"
# include <stdlib.h>
# include <stdio.h>
# include <sys/wait.h>
# include <string.h>
# include "../lib/libft/libft.h"
# include "../lib/printf/ft_printf.h"


/******************************************************************************
*								MACROS										  *
******************************************************************************/

# define EXIT_ERROR 1
# define EXIT_SUCCESS 0
# define PATH_MAX 4096
# define MAX_TOKENS 128
# define MAX_BUFFER 1024

/******************************************************************************
*								TOKENS										  *
******************************************************************************/
//give a definition to the different tokens
# define PIPE '|'

//DEFINE STRUCTURES

//pipes
typedef struct s_pipe
{
	struct s_pipe	*left;
	struct s_pipe	*right;
	int				typecode;
}		t_pipe;


//cmd
typedef struct s_cmd
{
	int		typecode;
}		t_cmd;

//execcmd
typedef struct s_exec
{
	int		typecode;
	char	**eargv;
	char	**argv;
}		t_exec;

//redirectcmd
typedef struct s_redir
{
	int		typecode;
	char	*file;
	char	*efile;
	int		mode;
	int		fd;
	char	*cmd;
}			t_redir;

//prompt call
// typedef struct s_call
// {
// 	char *promptstart;
// 	char *promptend;
// 	char 	;
// 	end cmd;
// 	typetoken;
	
// };

//token struct

typedef struct s_token
{
	char token;
} t_token;

//me11

typedef struct bld_in {
	char	*name;
	void	(*func)(char **ac);
	struct bld_in *next;
} bld_in;

typedef struct	s_tokenizer {
	char	token_buffer[MAX_BUFFER];
	int		buf_idx;
	int		i;
	int		in_singles;
	int		in_doubes;
} t_tokenizer;


//funtions
void shell_loop(bld_in *builtins);
char *read_input(void);
char **tokenize_input(char *line);
bld_in *create_builtin_list(void);
bld_in *find_builtin(bld_in *head, const char *command);
void    handle_cd(char **av);
void    handle_echo(char **av);
void    handle_pwd(void);
void    handle_export(char **av);
void    handle_unset(char **av);
void    handle_env(char **av);
void    free_builtin_list(bld_in *head);

#endif
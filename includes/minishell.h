#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <errno.h>
# include <signal.h>
# include <termios.h>
# include <fcntl.h>

# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_global
{
	int		status;
	char	**env;
} t_global;

# include "../libft/libft.h"

# define LOOP 1

# define ON 1
# define OFF 0

# define SUCCESS 0
# define ERROR -1

void	rl_replace_line (const char *text, int clear_undo);

#endif

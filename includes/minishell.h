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

# include "../libft/libft.h"

# define LOOP 1

# define ON 1
# define OFF 0

# define SUCCESS 0
# define ERROR -1

/* TOEKN TYPES */
# define T_NULL 0
# define T_COND 1
# define T_PIPE 2
# define T_CMND 3

# define T_NDND 11
# define T_OROR 12

# define T_WORD 31
# define T_RDIR 32

# define T_LPAR 311
# define T_RPAR 312

#endif

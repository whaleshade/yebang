# ================ Color Variables ================ #

BLACK			= 	"\033[0;30m"
GRAY			= 	"\033[1;30m"
RED				=	"\033[0;31m"
GREEN			=	"\033[0;32m"
YELLOW			=	"\033[1;33m"
PURPLE			=	"\033[0;35m"
CYAN			=	"\033[0;36m"
WHITE			=	"\033[1;37m"
EOC				=	"\033[0;0m"
LINE_CLEAR		=	"\x1b[1A\x1b[M"

# ================================================= #

NAME			= minishell

CC				= cc
CFLAGS			= -Wall -Wextra -Werror
RM				= rm -rf

LIB_READ		= readline
LDFLAGS			= -L$(shell brew --prefix readline)/lib
CPPFLAGS		= -I$(shell brew --prefix readline)/include

HEADERS			= includes
LIBFT			= -L./libft -lft
DIR_O			= obj
DIR_S 			= srcs

SOURCES			= 			\
				minishell.c

SRCS			= $(addprefix $(DIR_S)/,$(SOURCES))
OBJS			= $(addprefix $(DIR_O)/,$(SOURCES:.c=.o))

$(DIR_O)/%.o: $(DIR_S)/%.c $(HEADERS)/$(NAME).h
	@echo $(YELLOW) "Compiling...\t" $< $(EOC) $(LINE_CLEAR)
	@mkdir -p $(DIR_O)
	@$(CC) $(CFLAGS) -I $(HEADERS) -c $< -o $@

$(NAME): $(OBJS)
	@echo $(GREEN) "Source files are compiled!\n" $(EOC)
	@make -C libft
	@$(CC) $(CFLAGS) -o $@ $^ $(LIBFT) -l $(LIB_READ) $(LDFLAGS) $(CPPFLAGS)
	@echo $(GREEN) "$(NAME) is created!\n" $(EOC)

all: $(NAME)

clean:
	@echo $(YELLOW) "Cleaning object files..." $(EOC)
	@$(RM) $(DIR_O)
	@make clean -C libft
	@echo $(RED) "Object files are cleaned!\n" $(EOC)

fclean:	clean
	@echo $(YELLOW) "Removing $(NAME)..." $(EOC)
	@$(RM) $(NAME) $(BONUS)
	@make fclean -C libft
	@echo $(RED) "$(NAME) is removed!\n\n" $(EOC)

re:
	@make fclean
	@make all

.PHONY: all clean fclean re

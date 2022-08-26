#include "../includes/minishell.h"

/* to be organized */
#include "welcome_screen.c"
#include "get_tokens.c"
#include "token_lst_func.c"

void	ft_perror(char *str)
{
	printf("%s %s\n", str, strerror(errno));
}

//use tcsetattr and tcgetattr to modify your terminal settings.
//clear the ECHOCTL bit flag to suppress output from Ctrl-based signals.
void	ft_nodisplay_ctrlx_set(void)
{
	struct termios settings;

	if (tcgetattr(STDIN_FILENO, &settings) == ERROR)
		ft_perror("minsh: tcgetattr");
	settings.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &settings) == ERROR)
		ft_perror("minsh: tcsetattr");
}

void	sig_handler(int	signo)
{
	if (signo == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();		 //make new prompt line
		rl_replace_line("", ON); //replace the contents of rl_line_buffer with text in line, If clear_undo is non-zero, the undo list associated with the current line is cleared.
		rl_redisplay();			 //show the current content of rl_line_buffer;
	}
	return ;
}

void	show_list_contents(t_token *list)
{
	t_token	*tmp;

	tmp = list;
	while (tmp)
	{
		// printf("[%s {type : %d}]", (char *)tmp->data, (int)tmp->type);
		printf("[%s]", (char *)tmp->data);
		tmp = tmp->next;
	}
	printf("\n");
}

void	shell_loop()
{
	char	*cli_str;
	char	**line;
	int		i;
	t_token	*token_list;

	while (LOOP)
	{
		signal(SIGINT, sig_handler); // ctrl + c ... before fork(), set default
		signal(SIGQUIT, SIG_IGN); // ctrl +'\'
		cli_str = readline("minsh$ ");
		if (cli_str)
		{
			//if 끝에 백슬래시
			line = ft_split(cli_str, ';');
			i = 0;
			while (line[i])
			{
				token_list = get_token_list(line[i]);
				show_list_contents(token_list);
				i++;
			}

			add_history(cli_str); //shows the history of lines, by pressing arrows
			free(cli_str);
			//free(token_list);
			//free(line);
			cli_str = NULL;
		} //line[0] = '\0'일 경우도 처리 해줘야 하나?
		else
		{
			printf("\033[1A");
			printf("\033[7C");
			printf("exit\n");
			free(line);
			exit(1);
		}
	}
}

t_global	g_var;

int	main(int ac, char **av, char **envp)
{
	/* START SCREEN */
	welcome_screen();

	/* READ ENV */
	(void)ac;
	(void)av;
	g_var.status = 0;
	g_var.env = envp;

	/* TERMINAL INIT SETTINGS */
	//ft_nodisplay_ctrlx_set();

	/* CMD LOOP */
	shell_loop(); //READ, PARSE, EXEC
	/* TERMINATE PROC */
	//YOUR CODE HERE
	return (0);
}

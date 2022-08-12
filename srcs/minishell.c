#include "../includes/minishell.h"

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
		// rl_replace_line("", ON); //replace the contents of rl_line_buffer with text in line, If clear_undo is non-zero, the undo list associated with the current line is cleared.
		rl_redisplay();			 //show the current content of rl_line_buffer;
	}
	return ;
}


// char	**get_parse(char *line)
// {
// 	//get_next_line() to be used
// }


void	shell_loop()
{
	char	*line;
	// char	**args;

	while (LOOP)
	{
		signal(SIGINT, sig_handler); // ctrl + c
		signal(SIGQUIT, SIG_IGN); // ctrl +'\'
		line = readline("minsh$ ");
		if (line)
		{
			printf("you typed : %s\n", line); //to be deleted
			// args = get_parse(line);
			add_history(line); //shows the history of lines, by pressing arrows
			free(line);
			//free(args);
			line = NULL;
		} //line[0] = '\0'일 경우도 처리 해줘야 하나?
		else
		{
			printf("\033[1A");
			printf("\033[7C");
			printf("exit\n");
			free(line);
			exit(-1);
		}
	}
}

static void	ft_art(void)
{
	int		i;
	int		fd;
	char	*line;
	int		color;

	i = 0;
	color = 31;
	fd = open("yebang_shell.txt", O_RDONLY);
	// fd = open("vaccine_shell.txt", O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		if (++i % 8 == 0)
			color++;
		printf("\033[0;%dm%s", color, line);
		free(line);
	}
	free(line);
	printf("\n\033[0;0m\x1b[1A\x1b[M");
}

int	main()
{
	/* START SCREEN */
	ft_art();

	/* READ ENV */
	//YOUR CODE HERE

	/* TERMINAL INIT SETTINGS */
	ft_nodisplay_ctrlx_set();

	/* CMD LOOP */
	shell_loop(); //READ, PASE, EXEC
	/* TERMINATE PROC */
	//YOUR CODE HERE
	return (0);
}

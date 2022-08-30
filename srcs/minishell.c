/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibang <jibang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 15:22:05 by jibang            #+#    #+#             */
/*   Updated: 2022/08/30 21:10:49 by jibang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	show_tokens_data(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	printf("\033[0;33m");
	printf("token : \n");
	while (tmp)
	{
		printf("\033[0;33m");
		printf("[%s]", tmp->data);
		tmp = tmp->next;
	}
	printf("\n");
	printf("\n\033[0;0m\x1b[1A\x1b[M");
}

void	shell_loop()
{
	char	*cmd_line;
	t_token	*token_list;

	while (LOOP)
	{
		signal(SIGINT, sig_handler); // ctrl + c ... before fork(), set default
		signal(SIGQUIT, SIG_IGN); // ctrl +'\'
		cmd_line = readline("minsh$ ");
		if (cmd_line)
		{
			token_list = get_token_list(cmd_line);
			// show_list_contents(token_list);
			show_tokens_data(token_list);
			add_history(cmd_line); //shows the history of lines, by pressing arrows
			free(cmd_line);
			//free(token_list);
			//free(line);
			cmd_line = NULL;
		} // line[0] = '\0'일 경우도 처리 해줘야 하나?
		else
		{
			printf("\033[1A");
			printf("\033[7C");
			printf("exit\n");
			free(cmd_line);
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

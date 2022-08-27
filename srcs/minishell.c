/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeblee <yeblee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 01:24:52 by yeblee            #+#    #+#             */
/*   Updated: 2022/08/27 23:42:56 by yeblee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	shell_loop(void);
static void	sig_handler(int	signo);
// static void	show_list_contents(t_list *list);
// static void	ft_nodisplay_ctrlx_set(void);
// static void	ft_perror(char *str);

t_global	g_var;
// /* to be organized */
// #include "start_screen.c"
// #include "get_tokens.c"

int	main(int ac, char **av, char **envp)
{
	/* START SCREEN */
	ft_start_screen();

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

static void	shell_loop()
{
	char		*cli_str;
	char		**line;
	int			i;
	t_minishell	*sh;
	
	sh = ft_calloc(1, sizeof(t_minishell));
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
				ft_lstadd_back(&sh->list,  get_token_list(line[i]));
				// show_list_contents(token_list);
				/*
				* yeblee - tokenizer(sh, list);
				* : token_list를 t_token형식에 맞게 적용
				*   따옴표를 제외한 token_list 화이트 스페이스 제거, type 적용 
				*/
				tokenizer(sh);
				
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

static void	sig_handler(int	signo)
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

/*
static void	show_list_contents(t_list *list)
{
	t_list	*tmp;

	tmp = list;
	while (tmp)
	{
		printf("[%s]", (char *)tmp->content);
		tmp = tmp->next;
	}
	printf("\n");
}
*/
//use tcsetattr and tcgetattr to modify your terminal settings.
//clear the ECHOCTL bit flag to suppress output from Ctrl-based signals.
/*
static void	ft_nodisplay_ctrlx_set(void)
{
	struct termios settings;

	if (tcgetattr(STDIN_FILENO, &settings) == ERROR)
		ft_perror("minsh: tcgetattr");
	settings.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &settings) == ERROR)
		ft_perror("minsh: tcsetattr");
}
*/

/*
static void	ft_perror(char *str)
{
	printf("%s %s\n", str, strerror(errno));
}
*/
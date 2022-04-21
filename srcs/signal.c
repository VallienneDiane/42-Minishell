/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 13:46:49 by dvallien          #+#    #+#             */
/*   Updated: 2022/04/21 11:43:22 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <sys/ioctl.h>

void	ft_signal_handler(int signal)
{
	// if (signal == SIGINT)
	// {
	// 	errno = 130;
	// 	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	// 	rl_replace_line("", 0);
	// 	rl_on_new_line();
	// }
	
	if (signal == SIGINT)
	{
		printf("la\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	ft_signal_exec_handler(int signal)
{
	if (signal == SIGINT)
		printf("ici\n");
}

void	ft_term_handler(int x)
{
	static struct termios t_save;
	struct termios t_new;
	int term;

	term = 0;
	if (x)
		tcsetattr(0, 0, &t_save);
	else
	{
		term = ttyslot();
		tcgetattr(term, &t_save);
		t_new = t_save;
		t_new.c_lflag &= ~(ICANON | ECHOCTL);
		t_new.c_cc[VQUIT] = 0;
		tcsetattr(term, TCSANOW, &t_new);
	}
}

// int	ft_get_pid(int pid)
// {
// 	static int parent_pid;

// 	if (pid > 0)
// 		parent_pid = pid;
// 	return (parent_pid);
// }

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 13:46:49 by dvallien          #+#    #+#             */
/*   Updated: 2022/04/28 10:19:30 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	ft_signal_exec_handler(int signal)
{
	if(signal == SIGINT)
		return ;
	if (signal == SIGQUIT)
		return ;
}

void	ft_term_handler(int x)
{
	static struct termios t_old;
	struct termios t_new;
	int term;

	term = 0;
	if (x)
	{
		// printf("RESET TERM\n");
		tcsetattr(0, 0, &t_old);
	}
	else
	{
		// printf("CHANGE TERM\n");
		term = ttyslot();
		tcgetattr(term, &t_old);
		t_new = t_old;
		t_new.c_lflag &= ~(ICANON | ECHOCTL); //  
		t_new.c_cc[VQUIT] = 0;
		tcsetattr(term, TCSANOW, &t_new);
	}
}

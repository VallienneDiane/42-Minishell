/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 13:46:49 by dvallien          #+#    #+#             */
/*   Updated: 2022/05/03 15:26:10 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	if (signal == SIGINT)
		return ;
	if (signal == SIGQUIT)
		return ;
}

void	ft_term_handler(int x)
{
	static struct termios	t_old;
	struct termios			t_new;
	int						term;

	term = 0;
	if (x)
	{
		tcsetattr(0, 0, &t_old);
	}
	else
	{
		term = ttyslot();
		tcgetattr(term, &t_old);
		t_new = t_old;
		t_new.c_lflag &= ~(ICANON | ECHOCTL);
		t_new.c_cc[VQUIT] = 0;
		tcsetattr(term, TCSANOW, &t_new);
	}
}

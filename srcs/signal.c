/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 13:46:49 by dvallien          #+#    #+#             */
/*   Updated: 2022/04/19 17:59:08 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_signal(int signal)
{
	// ctrl C
	if (signal == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	ft_signal_exec(int signal)
{
	if (signal == SIGINT)
		printf("\n");
}

void	ft_term_handler(int x)
{
	static struct termios t_save;
	struct termios t_new;
	int term;

	term = 0;
	if (x)
	{
		tcsetattr(0, 0, &t_save); //reset term
	}
	else
	{
		term = ttyslot();
		tcgetattr(term, &t_save);
		t_new = t_save;
		t_new.c_lflag &= ~(ICANON | ECHOCTL);
		t_new.c_cc[VQUIT] = 0;
		signal(SIGINT, ft_signal);
		tcsetattr(term, TCSANOW, &t_new);
	}
}
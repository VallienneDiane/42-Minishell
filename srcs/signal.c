/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 13:46:49 by dvallien          #+#    #+#             */
/*   Updated: 2022/04/18 17:38:08 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_signal(int signal)
{
	(void)signal;

	// segfault avec ctrl D deja existant
	
	// // Ctrl C : nouveau prompt sur nouvelle ligne
	// if (signal == SIGINT)
	// {
	// 	printf("\n");
	// 	rl_on_new_line(); // bouge sur une nouvelle ligne vide
	// 	// rl_replace_line("", 0); // remplace contenu de rl_line_buffer par le texte ""
	// 	rl_redisplay(); // change l'affichage en mettant ce que contient le rl_line_bufer
	// }
	// Ctrl D : quitte le shell
	// if (signal == SIGQUIT)
	// {
	// 	printf("exit\n");
	// 	// rl_on_new_line();
	// 	// // rl_replace_line("exit", 0); // remplace contenu de rl_line_buffer par le texte ""
	// 	// rl_redisplay();
	// 	exit(0);
	// }
}

//OU

// if (signal == SIGINT)
	// appeler ft_prompt()
// if (signal == SIGQUIT)
	// appeler ft_exit()
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 10:42:43 by amarchal          #+#    #+#             */
/*   Updated: 2022/04/22 17:04:48 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_redir_out(char *line, t_pars_info *p_info)
{
	int	j;

	j = p_info->i + 1;
	p_info->current_type = REDIR_OUT;
	if (line[j] && line[j] == '>')
	{
		p_info->current_type = REDIR_CONC;
		p_info->i += 1;
		j++;
	}
	while (line[j] == ' ')
		j++;
	if (!line[j] || line[j] == '|' || line[j] == '<' || line[j] == '>')
	{
		if (!p_info->error)
		{
			if (!line[j])
				printf("miniHell: syntax error near unexpected token `newline'\n");
			else
				printf("miniHell: syntax error near unexpected token `%c'\n", line[j]);
		}
		p_info->error = 1;
		// return ;
		// exit(258);
	}
	p_info->i += 1;
}

void	ft_redir_in(char *line, t_pars_info *p_info)
{
	int	j;

	j = p_info->i + 1;
	if (line[j] && line[j] == '<')
	{
		if (line[j + 1] && line[j + 1] == '<')
		{
			if (!p_info->error)
				printf("miniHell: syntax error near unexpected token `<'\n");
			p_info->error = 1;
			// return ;
			// exit(258);
		}
		p_info->current_type = HEREDOC;
		p_info->i += 1;
	}
	else
	{
		p_info->current_type = REDIR_IN;
		while (line[j] == ' ')
			j++;
		if (!line[j] || line[j] == '|' || line[j] == '<' || line[j] == '>')
		{
			if (!p_info->error)
			{
				if (!line[j])
					printf("miniHell: syntax error near unexpected token `newline'\n");
				else
					printf("miniHell: syntax error near unexpected token `%c'\n", line[j]);
			}
			p_info->error = 1;
			// return ;
			// exit(258);
		}	
	}
	p_info->i += 1;
}

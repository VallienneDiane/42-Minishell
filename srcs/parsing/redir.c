/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 10:42:43 by amarchal          #+#    #+#             */
/*   Updated: 2022/04/28 17:39:55 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
				printf("miniHell: syntax error near \
unexpected token `newline'\n");
			else
				printf("miniHell: syntax error near \
unexpected token `%c'\n", line[j]);
		}
		p_info->error = 1;
		g_status = 258;
	}
	p_info->i += 1;
}

void	ft_manage_heredoc(char *line, int j, t_pars_info *p_info)
{
	if (line[j + 1] && line[j + 1] == '<')
	{
		if (!p_info->error)
			printf("miniHell: syntax error near unexpected token `<'\n");
		p_info->error = 1;
		g_status = 258;
	}
	else if (!line[j + 1])
	{
		if (!p_info->error)
			printf("miniHell: syntax error near unexpected token `newline'\n");
		p_info->error = 1;
		g_status = 258;
	}
	p_info->current_type = HEREDOC;
	p_info->i += 1;
}

void	ft_redir_in(char *line, t_pars_info *p_info)
{
	int	j;

	j = p_info->i + 1;
	if (line[j] && line[j] == '<')
		ft_manage_heredoc(line, j, p_info);
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
					printf("miniHell: syntax error near \
unexpected token `newline'\n");
				else
					printf("miniHell: syntax error near \
unexpected token `%c'\n", line[j]);
			}
			p_info->error = 1;
			g_status = 258;
		}	
	}
	p_info->i += 1;
}

void	ft_pipe(char *line, t_pars_info *p_info)
{
	int	j;

	j = p_info->i + 1;
	while (line[j] == ' ')
		j++;
	if (!line[j] || line[j] == '|')
	{
		if (!p_info->error)
		{
			printf("miniHell: syntax error near unexpected token `|'\n");
			g_status = 258;
		}
		p_info->error = 1;
	}
	p_info->current_block++;
	p_info->i += 1;
}

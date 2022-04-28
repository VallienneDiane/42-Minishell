/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 13:57:47 by amarchal          #+#    #+#             */
/*   Updated: 2022/04/28 17:40:39 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_s_quote_size(char *line, t_pars_info *p_info)
{
	int	k;

	k = 0;
	p_info->j += 1;
	while (line[p_info->j] && line[p_info->j] != '\'')
	{
		p_info->j += 1;
		k++;
	}
	if (line[p_info->j] == '\'')
		p_info->j += 1;
	return (k);
}

char	*ft_join_s_quote(char *line, char *content, t_pars_info *p_info)
{
	p_info->i += 1;
	while (line[p_info->i] && line[p_info->i] != '\'')
	{
		content[p_info->j] = line[p_info->i];
		p_info->j += 1;
		p_info->i += 1;
	}
	if (line[p_info->i] == '\'')
		p_info->i += 1;
	return (content);
}

int	ft_d_quote_size(char *line, t_pars_info *p_info)
{
	int	k;

	k = 0;
	p_info->j += 1;
	while (line[p_info->j] && line[p_info->j] != '\"')
	{
		if (line[p_info->j] == '$')
			k += ft_env_size(line, p_info);
		else
		{
			p_info->j += 1;
			k++;
		}
	}
	if (line[p_info->j] == '\"')
		p_info->j += 1;
	return (k);
}

char	*ft_join_d_quote(char *line, char *content,
	t_list **list, t_pars_info *p_info)
{
	p_info->d_quote = 1;
	p_info->i += 1;
	while (line[p_info->i] && line[p_info->i] != '\"')
	{
		if (line[p_info->i] == '$')
			content = ft_join_env(line, content, list, p_info);
		else
		{
			content[p_info->j] = line[p_info->i];
			p_info->j += 1;
			p_info->i += 1;
		}
	}
	if (line[p_info->i] == '\"')
		p_info->i += 1;
	p_info->d_quote = 0;
	return (content);
}

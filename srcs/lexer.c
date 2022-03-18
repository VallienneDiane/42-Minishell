/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 10:56:24 by amarchal          #+#    #+#             */
/*   Updated: 2022/03/18 17:50:07 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_simple_quote(t_list **list, char *line, int i)
{
	int		j;
	char	*content;

	j = i;
	while (line[j] && line[j] != '\'')
		j++;
	// content = malloc(sizeof(char))
	(void)content;
	(void)list;
}
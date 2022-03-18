/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 15:16:11 by amarchal          #+#    #+#             */
/*   Updated: 2022/02/18 11:19:18 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*buff;
	size_t	i;

	i = count * size;
	buff = malloc(sizeof(char) * i);
	if (!buff)
		return (NULL);
	ft_bzero(buff, i);
	return (buff);
}

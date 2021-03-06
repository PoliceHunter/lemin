/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmyrcell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 16:41:47 by tmyrcell          #+#    #+#             */
/*   Updated: 2019/09/21 15:03:20 by tmyrcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int		ft_strnequ(char const *s1, char const *s2, size_t n)
{
	int i;

	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (0);
	if (!n)
		return (1);
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0' && --n)
		i++;
	if ((s1[i] == '\0' && s2[i] == '\0') || s1[i] == s2[i])
		return (1);
	return (0);
}

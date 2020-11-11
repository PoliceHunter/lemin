/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmyrcell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 18:48:06 by tmyrcell          #+#    #+#             */
/*   Updated: 2020/02/23 19:40:36 by tmyrcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*tmp;

	if (s1 && s2)
		tmp = (char *)malloc((sizeof(char)) * (ft_strlen(s1) +
					ft_strlen(s2) + 1));
	else if (s1)
		tmp = (char *)malloc((sizeof(char)) * (ft_strlen(s1) + 1));
	else if (s2)
		tmp = (char *)malloc((sizeof(char)) * (ft_strlen(s2) + 1));
	else
		return (NULL);
	if (!tmp)
		return (NULL);
	if (s1)
		tmp = ft_strcpy(tmp, s1);
	else
		tmp = ft_strcpy(tmp, s2);
	if (s1 && s2)
		tmp = ft_strcat(tmp, s2);
	return (tmp);
}

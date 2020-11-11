/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmyrcell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 19:49:04 by tmyrcell          #+#    #+#             */
/*   Updated: 2019/09/24 19:53:36 by tmyrcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int		ft_isspace(int c)
{
	if (c == '\f' || c == '\n' || c == '\r' ||
			c == '\t' || c == '\v' || c == ' ')
		return (1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmyrcell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 18:58:12 by tmyrcell          #+#    #+#             */
/*   Updated: 2019/09/14 15:18:10 by tmyrcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int		ft_toupper(int c)
{
	if (c >= 65 && c <= 90)
		return (c);
	if (c >= 97 && c <= 122)
		return (c - 97 + 65);
	return (c);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmyrcell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 19:13:01 by tmyrcell          #+#    #+#             */
/*   Updated: 2020/11/29 16:25:01 by tmyrcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	ft_memmove_less(register char *dst, register const char *src,
						size_t length)
{
	register size_t t;

	t = (int)src;
	if ((t | (int)dst) & WMASK)
	{
		if ((t ^ (int)dst) & WMASK || length < WSIZE)
			t = length;
		else
			t = WSIZE - (t & WMASK);
		length -= t;
		while (t-- != 0)
			*dst++ = *src++;
	}
	t = length / WSIZE;
	while (t-- != 0)
	{
		*(int *)dst = *(int *)src;
		src += WSIZE;
		dst += WSIZE;
	}
	t = length & WMASK;
	while (t-- != 0)
		*dst++ = *src++;
}

void	ft_memmove_greater(register char *dst, register const char *src,
								size_t length)
{
	register size_t t;

	src += length;
	dst += length;
	t = (int)src;
	if ((t | (int)dst) & WMASK)
	{
		if ((t ^ (int)dst) & WMASK || length <= WSIZE)
			t = length;
		else
			t &= WMASK;
		length -= t;
		while (t-- != 0)
			*--dst = *--src;
	}
	t = length / WSIZE;
	while (t-- != 0)
	{
		src -= WSIZE;
		dst -= WSIZE;
		*(int *)dst = *(int *)src;
	}
	t = length & WMASK;
	while (t-- != 0)
		*--dst = *--src;
}

void	*ft_memmove(void *dst0, const void *src0, size_t length)
{
	register char		*dst;
	register const char	*src;

	src = src0;
	dst = dst0;
	if (length == 0 || dst == src)
		return (dst0);
	if ((unsigned long)dst < (unsigned long)src)
		ft_memmove_less(dst, src, length);
	else
		ft_memmove_greater(dst, src, length);
	return (dst0);
}

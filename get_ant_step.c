/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ant_step.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmyrcell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 13:32:52 by tmyrcell          #+#    #+#             */
/*   Updated: 2020/11/14 13:32:53 by tmyrcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_node_ptr	get_node_from_way_const(const t_way *way, size_t index)
{
	return (const t_node_ptr)get_from_vec_const(&way->nodes, index);
}

char		*ft_strjoin_free3(char *s1, char *s2)
{
	char	*str;

	str = ft_strjoin(s1, s2);
	if (s2 != NULL)
		free(s2);
	if (s1 != NULL)
		free(s1);
	return (str);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksean <ksean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 12:37:03 by ksean             #+#    #+#             */
/*   Updated: 2020/11/18 12:44:40 by ksean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

char			*solve(t_node_ptr src, t_node_ptr dst)
{
	t_vector	ways;
	char		*result;
	t_vector 	qoue;

	qoue = new_vector(10, sizeof(t_node *));
	push_back_vec(&qoue, &src);
	src->bfs = 0;
	dst->r_bfs = 0;
	result = NULL;
	//set_bfs1(qoue, dst);
	set_bfs(src);
	free_vec(&qoue);
	set_r_bfs(dst);



	// delete_useles_links(src, dst);
	ways = new_vector(10, sizeof(t_way));



	find_ways(src, dst, NULL, &ways);
	printf("\n\n\n%d \n\n\n", ways.size);
	result = write_ants_in_line(&ways, src->n_ants);
	printf_ways(ways);
	if (ways.size == 0)
	{
		ft_printf("Error\n");
		free(result);
		free_vec_ways(ways);
		return (NULL);
	}
	free_vec_ways(ways);
	return (result);
}
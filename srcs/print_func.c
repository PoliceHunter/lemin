/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmyrcell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 13:46:38 by tmyrcell          #+#    #+#             */
/*   Updated: 2020/11/29 13:46:40 by tmyrcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	print_way(t_way *way)
{
	t_node_ptr	*ptr;
	int			i;

	i = -1;
	while (++i != way->nodes.size)
	{
		ptr = get_from_vec(&way->nodes, i);
		ft_printf("%s->", (*ptr)->name);
	}
	ft_printf("\n");
}

void	printf_ways(t_vector ways)
{
	int i;

	i = -1;
	while (++i != ways.size)
	{
		print_way((t_way *)get_from_vec(&ways, i));
	}
}

void	print_by_helper(t_main_helper *helper, t_args *args)
{
	if (args->flag_way)
	{
		ft_printf("\n");
		printf_ways(helper->ways);
	}
	if (args->flag_steps)
		ft_printf("\n%d\n", helper->ants);
}

int		print_help(void)
{
	ft_printf("Usage: ./lem-in maps.txt "
		"-flags{-h --help, -w --ways, -s --steps}\n");
	exit(0);
}

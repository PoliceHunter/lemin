/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmyrcell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 16:11:45 by tmyrcell          #+#    #+#             */
/*   Updated: 2020/11/10 16:12:22 by tmyrcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		check_room(char *line, t_help *help)
{
	char	**room;

	room = NULL;
	room = ft_strsplit(line, ' ');
	if (!(help->name = malloc(sizeof(char *) * (ft_strlen(room[0]) + 1))))
		help->errors++;
	if ((!(room[1]) || !(room[2]) || !(room[0])))
	{
		free_array(room);
		help->errors++;
		return (1);
	}
	ft_strcpy(help->name, room[0]);
	if (!ft_is_digitstr(room[1]) || !ft_is_digitstr(room[2]))
	{
		free_array(room);
		return (help->errors++);
	}
	if ((!(help->x = ft_atoi(room[1])) && help->x != 0) ||
		(!(help->y = ft_atoi(room[2])) && help->y != 0))
		help->errors++;
	free_array(room);
	return (help->errors);
}

void	parse_line(char *line, t_help *help, t_vector *vec)
{
	if (this_start(line, help))
		return ;
	if (this_end(line, help))
		return ;
	if ((!(it_is_link(line))) && ((!(check_room(line, help)))))
	{
		if (find_in_vec(vec, help->name) >= 0)
		{
			help->errors++;
			return ;
		}
		insert_with_sort_node(vec, init_and_write_node(help));
		free(help->name);
		help->name = NULL;
		help->start = 0;
		help->end = 0;
	}
	if (it_is_link(line))
		help->errors += write_link(line, vec);
}

void set_backward_edge(t_node_ptr src, t_edge * edge)
{
	int candidate_index;

	if (edge->backward != NULL)
		return;

	candidate_index = -1;
	while(++candidate_index < edge->dst->links.size)
	{
		t_edge * candidate = get_from_vec(&edge->dst->links, candidate_index);
		if (candidate->dst != src)
			continue;

		edge->backward = candidate;
		edge->backward->backward = edge;
		break;
	}
}

void set_backward_edges(t_vector * nodes)
{
	int node_index;
	int edge_index;

	node_index = -1;
	while (++node_index < nodes->size)
	{
		t_node_ptr node = get_from_vec(nodes, node_index);
		edge_index = -1;
		while (++edge_index < node->links.size)
			set_backward_edge(node, get_from_vec(&node->links, edge_index));
	}
}

void	*parse_file2(int fd, char *map, t_help *help, t_vector *vec)
{
	char *line;

	line = NULL;
	while (get_next_line(fd, &line))
	{
		if (empty_string(line, help))
		{
			free(line);
			return (map);
		}
		map = ft_strjoin_free(ft_strjoin_free(map, line), "\n");
		if (find_comment(line))
		{
			free(line);
			continue;
		}
		parse_line(line, help, vec);
		free(line);
		line = NULL;
		if (help->errors != 0)
			return (map);
	}
	set_backward_edges(vec);
	return (map);
}

void	*parse_file(int fd, char *line, t_help *help, t_vector *vec)
{
	char *map;

	map = NULL;
	while (get_next_line(fd, &line))
	{
		if (!line)
		{
			help->errors++;
			return (map);
		}
		map = ft_strjoin_free(ft_strjoin_free(map, line), "\n");
		if (find_comment(line))
			free(line);
		else
		{
			if ((!(help->ants = ft_atoi(line))) || help->ants < 0
				|| (!(ft_is_digitstr(line))))
				help->errors++;
			break ;
		}
	}
	free(line);
	if (help->errors != 0)
		return (map);
	return (parse_file2(fd, map, help, vec));
}

char	*process_file(const char *filename, t_vector *vec)
{
	t_help	help;
	int		fd;
	char	*line;
	char	*map;

	line = NULL;
	help = init_help();
	fd = open(filename, O_RDONLY, 0);
	map = parse_file(fd, line, &help, vec);
	if (help.errors != 0)
	{
		free(map);
		ft_error_if_help_and_vec("Error\n", &help, vec);
		exit(5);
	}
	return (map);
}

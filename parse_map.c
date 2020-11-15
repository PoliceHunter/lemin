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
	if (!(help->name = malloc(sizeof(char *) * (ft_strlen(room[0]) + 1)))
		|| room[3])
		help->errors++;
	if ((!(room[1]) || !(room[2]) || !(room[0])))
	{
		free_array(room);
		return (help->errors++);
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
			help->errors++;
		insert_with_sort_node(vec, init_and_write_node(help));
		free(help->name);
		help->name = NULL;
		help->start = 0;
		help->end = 0;
	}
	if (it_is_link(line))
		help->errors += write_link(line, vec);
}

void	*parse_file2(int fd, char *map, t_help *help, t_vector *vec)
{
	char *line;

	line = NULL;
	while (get_next_line(fd, &line))
	{
		map = ft_strjoin_free(ft_strjoin_free(map, line), "\n");
		if (find_comment(line))
		{
			free(line);
			continue;
		}
		if (empty_string(line, help))
		{
			free(line);
			return (map);
		}
		parse_line(line, help, vec);
		free(line);
		line = NULL;
		if (help->errors != 0)
			return (map);
	}
	return (map);
}

void	*parse_file(int fd, char *line, t_help *help, t_vector *vec)
{
	char *map;

	map = NULL;
	while (get_next_line(fd, &line))
	{
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
	if (help->errors != 0)
	{
		free(line);
		return (map);
	}
	free(line);
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

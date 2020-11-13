/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksean <ksean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 15:06:05 by ksean             #+#    #+#             */
/*   Updated: 2020/11/10 02:31:14 by ksean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# define VECTOR_INIT_CAPACITY 5

# include "libft/inc/libft.h"
# include "libft/inc/ft_printf.h"
# include "libft/inc/get_next_line.h"
# include "vector.h"

# include <limits.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>

typedef struct			s_ants
{
	char				**ants;
}						t_ants;

typedef struct s_node	t_node;
struct					s_node
{
	char				*name;
	int					x;
	int					y;
	int					n_ants;
	int					is_start_node;
	int					is_end_node;
	int					bfs;
	int					visited;

	t_vector			links;
};

typedef t_node			*t_node_ptr;

typedef struct s_help	t_help;

struct					s_help
{
	int					ants;
	int					errors;
	int					x;
	int					y;
	char				*name;
	int					end;
	int					start;
};

typedef struct s_ways	t_way;

struct					s_ways
{
	char				**way_nodes;
	unsigned int		way_len;

	unsigned short		*ants;
};

typedef struct			s_character
{
	t_node				*root;
	t_node				*target;
}						t_character;

typedef struct s_group_helper	t_group_handler;
struct 							s_group_helper
{
	t_vector candidate_group;
	t_vector min_group;
	unsigned int min_group_step;
	char * result;
};

typedef struct s_ants_tracker
{
	unsigned int finished;
	unsigned int in_path;
	unsigned int count;
}	t_ants_tracker;


char					*solve(t_node_ptr src, t_node_ptr dst);
void					insert_way(t_way *way, char *line);
t_way					*init_way();
t_group_handler			init_group_handler();
int						write_link(const char *line, t_vector *node_vec);
void					free_vec_node(t_vector *vec);
void					free_vec_ways(t_vector ways);
void					free_array(char **array);

t_node					init_node();
void					free_node(t_node *node);
t_help					init_help();
t_node					init_and_write_node(t_help *help);

t_node					*find_or_insert(t_vector *vec, const char *new_node);
int						find_in_vec(t_vector *vec, const char *name);
t_node					*find_and_get(t_vector *vec, char *name);
int						find_in_vec_internal(t_vector *vec, size_t start,
						size_t end, char *name);

t_vector				new_node_vec(size_t capacity);
t_node					*get_from_node_vec(t_vector *vec, size_t index);
t_character				get_character(t_vector *vec);
void					push_back_node_vec(t_vector *vec, t_node node);
void					push_front_node_vec(t_vector *vec, t_node node);
void					emplace_back_node_vec(t_vector *vec, t_node node);

void					printf_node_vec(t_vector *vec);
void					emplace_front_node_vec(t_vector *vec, t_node node);
int						insert_into_node_vec(t_vector *vec, size_t index,
						t_node node);

int						cmp_node(t_vector *vec, size_t index1,
						t_node *new_node);
int						insert_with_sort_node_internal(t_vector *vec,
						size_t start, size_t end, t_node new_node);
int						insert_with_sort_node(t_vector *vec, t_node new_node);
int						is_sorted(t_vector vec);
int						ft_is_digitstr(const char *str);
void					parse_line(char *line, t_help *help, t_vector *vec);

char					*process_file(const char *filename, t_vector *vec);
int						check_room(char *line, t_help *help);
int						check_duplicate_links(t_node_ptr src, t_node_ptr dst);
int						it_is_link(const char *line);
int						empty_string(const char *line, t_help *help);
int						find_comment(const char *line);
void					ft_error_if_help_and_vec(char *txt, t_help *help,
						t_vector *vec);
void					ft_error_if_vec(char *txt, t_vector *vec);

int						this_start(char *line, t_help *help);
int						this_end(char *line, t_help *help);
int						error_map_and_vec(t_character *character);
void					free_map_and_vec(t_vector *vec,
						char *map, int error_num);
char *write_ants_in_line(t_vector *ways, int ants);
int				is_group_identical(const t_vector left_group,
									  const t_vector right_group);
t_vector		get_non_crossing_group(t_vector *ways, t_way *init_way);
unsigned int	get_ant_step(t_vector ways, const unsigned int ants_count,
							 char **history, unsigned int min_step_count);
int				make_way_step(t_way *way);
char			*get_ant_pos(const t_vector *ways);
int				cmp_way(void *left_way, void *right_way);
void			find_ways(t_node_ptr src, t_node_ptr dst, char *tmp_buffer,
						  t_vector *ways);
char				*ft_strjoin_free3(char *s1, char *s2);

#endif

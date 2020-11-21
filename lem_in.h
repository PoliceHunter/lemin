/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksean <ksean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 15:06:05 by ksean             #+#    #+#             */
/*   Updated: 2020/11/14 11:28:52 by tmyrcell         ###   ########.fr       */
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

#define STATE_NONE INT_MAX
#define STATE_NO_INVOLVED -1
#define STATE_IN_QUEUE 0
#define STATE_VISITED 1
#define STATE_IN_PATH 2

#define NO_ANT 0

#define MARK_NONE 0
#define MARK_FORWARD_PATH 1
#define MARK_BACKWARD_PATH 2
#define MARK_DISABLE 3

#define IS_CORRECTED 1 // if path not cross
#define IS_UNCORRECTED -1 //if path cross

typedef struct			s_ants
{
	char				**ants;
}						t_ants;

struct s_node;
typedef struct s_node	t_node;
typedef t_node			*t_node_ptr;

typedef struct s_edge	t_edge;
struct s_edge
{
	t_node_ptr	    dst;
	int		        capacity;
	int 			original_capacity;
	struct s_edge * backward;
	int             mark;
};


struct					s_node
{
	char				*name;
	int					x;
	int					y;
	int 				ant_number;
	int					is_start_node;
	int					is_end_node;
	int					bfs;
	int 				r_bfs;
	int					traversal_state;
	int					r_visited;

	t_vector			links; // vector<t_edge>
};


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
	int					multi_st_end;
};

typedef struct s_ways	t_way;

struct					s_ways
{
	t_vector            nodes; // vector<t_node_ptr>
	t_vector 			edges;
	int 				state;
};

t_node_ptr get_node_from_way_const(const t_way * way, size_t index);

typedef struct			s_character
{
	t_node				*root;
	t_node				*target;
}						t_character;


char					*solve(t_node_ptr src, t_node_ptr dst, t_vector * nodes);
void					insert_way(t_way *way, char *line);
t_way					init_way();
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
int						find_in_vec_internal(t_vector *vec, int start,
						int end, char *name);

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
t_vector		get_non_crossing_group(t_vector *ways, t_way *init_way);
size_t get_ant_step(t_node_ptr src, t_vector ways,
					char **way_history);
int make_way_step(t_way *way);
int				cmp_way(void *left_way, void *right_way);
void			find_ways(t_node_ptr src, t_node_ptr dst, char *tmp_buffer,
						  t_vector *ways);
char				*ft_strjoin_free3(char *s1, char *s2);
void	free_ways(t_way *way);
void			printf_ways(t_vector ways);

void ft_assert(int result, const char *);

#endif

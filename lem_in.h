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

#define TRUE 1
#define FALSE 0

# define STATE_NONE INT_MAX
# define STATE_NO_INVOLVED -1
# define STATE_IN_QUEUE 0
# define STATE_VISITED 1
# define STATE_IN_PATH 2
# define STATE_IN_CROSS 3

# define MARK_NONE 0
# define MARK_FORWARD_PATH 1
# define MARK_BACKWARD_PATH 2
# define MARK_DISABLE 3

# define IS_CORRECTED 1 // if path not cross
# define IS_CROSS -1 //if path cross

typedef struct			s_ants
{
	char				**ants;
}						t_ants;

struct s_node;
typedef struct s_node	t_node;
typedef t_node			*t_node_ptr;

typedef struct s_edge	t_edge;
struct					s_edge
{
	t_node_ptr			dst;
	int					capacity;
	int					original_capacity;
	struct s_edge		*backward;
	int					mark;
};

typedef struct			s_character
{
	t_node				*root;
	t_node				*target;
}						t_character;

typedef struct s_main_helper t_main_helper;
struct s_main_helper
{
	t_character	character;
	char		*result;
	t_vector	nodes_vec;
	char		*map;
	int			ants;
	t_vector	ways;
};

struct s_node
{
	char * name;
	int x;
	int y;
	int is_start_node;
	int is_end_node;
	int bfs;
	int traversal_state;
	int is_cross;

	t_vector ants;
	t_vector links;
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
	t_vector			nodes; // vector<t_node_ptr>
	t_vector			edges;
	int					is_have_backward_edges;
};


typedef struct s_args	t_args;
struct					s_args
{
	int 				flag_way;
	int 				flag_steps;
	int 				flag_help;
};

typedef struct s_track	t_track;
struct					s_track
{
	int finished;
	int ready_to_go;
	int all;
	int ants_in_way;
};

typedef struct s_solver_helper t_solver_helper;
struct s_solver_helper
{
	char * best_history;
	size_t best_ant_step;

	char * current_history;
	size_t current_ant_step;

	int is_history_need;
	t_vector best_ways;
};

typedef struct s_queue
{
	t_node_ptr	val;
	struct s_queue	*next;
} t_queue;

t_vector solve(t_node_ptr src, int * ants_count, t_vector * nodes, char ** history);

void insert_way(t_way * way, char * line);
t_way					init_way();
int						write_link(const char *line, t_vector *node_vec);
void					free_vec_node(t_vector *vec);
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

char					*process_file(t_vector *vec);
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
size_t					get_ant_step(t_node_ptr src, int ants_count,
						t_vector ways, char **way_history);
int						make_way_step(t_way *way, int * ants_in_way);
int						cmp_way(void *left_way, void *right_way);

char * ft_strjoin_free3(char * s1, char * s2);


void printf_ways(t_vector ways);

void					ft_assert(int result, const char *error);

void remove_all_not_free(t_vector * ants);

int refresh_state(t_vector * ways, t_way * way, t_vector * nodes);

void reset_state(t_vector * nodes, int except_mark);
t_solver_helper init_helper(void);
t_track init_tracker(size_t count);
void			write_history(t_vector ways, char **history);
int 			find_by_bfs(t_node_ptr src, t_way * way, t_vector * nodes);
void queue_up(t_queue ** queue, t_node_ptr node, int new_bfs);
int			is_in_path(t_edge * edge, t_node_ptr src);
int		finish_reconstruct(t_way *way, t_edge *edge, t_vector *nodes);
void		direct_and_mark_way_edges(t_way * way);
t_way *get_last_way(t_vector * vec);

t_way * get_place_for_way(t_vector * vec);

t_vector try_candidate(t_solver_helper * helper, t_node_ptr src, int ants_count, t_vector ways);

char * calculate_best_history(t_solver_helper * helper, t_node_ptr src, int ants_count);

int is_cross(t_vector * ways);
int					process_way(t_way *way, t_track *tracker,
								   int *previous_ways_len, const int index);
t_edge * get_reverse_edge(t_node_ptr node, int expect_state);
t_node_ptr dequeue(t_queue **head);
void clear_queue(t_queue *queue);
void	set_backward_edge(t_node_ptr src, t_edge *edge);
void	set_backward_edges(t_vector *nodes);
void	free_way(t_way *way);
void	free_ways(t_vector *ways);
void print_by_helper(t_main_helper *helper, t_args *args);
int		print_help(void);
t_main_helper	init_main_helper(void);

#endif

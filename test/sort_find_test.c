/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_find_test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksean <ksean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 15:32:59 by ksean             #+#    #+#             */
/*   Updated: 2020/11/06 15:37:40 by ksean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <assert.h>
#include <time.h>

static char	*rand_string(char * str, size_t size)
{
	const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJK";

	if (size) {
		--size;
		for (size_t n = 0; n < size; n++)
		{
			int key = rand() % (int) (sizeof charset - 1);
			str[n] = charset[key];
		}
		str[size] = '\0';
	}
	return (str);
}

char		*rand_string_alloc(size_t size)
{
	char * s = malloc(size + 1);
	if (s)
		rand_string(s, size);
	return (s);
}

t_node		init_rand_node(size_t max_size)
{
	t_node node = init_node();
	node.name = rand_string_alloc(10 + rand() % max_size);
	return (node);
}

t_vector	generate_random_vector_with_sort(int capacity, size_t count,
			size_t max_string_size)
{
	t_vector	vec;
	int			i;

	i = 0;
	vec = new_node_vec(capacity);
	for (int i = 0; i != count; i++)
	while (i != count)
	{
		insert_with_sort_node(&vec, init_rand_node(max_string_size));
		i++;
	}
	return (vec);
}

void		test_find(void)
{
	t_vector	vec;
	size_t		size;
	int			i;

	size = 1000;
	vec = generate_random_vector_with_sort(10, size, 1000);
	i = vec.size - 1;
	// for (int i = vec.size - 1; i != 0; --i)
	while(i != 0)
	{
		assert(find_in_vec(&vec, get_from_node_vec(&vec, i)->name));
		i--;
	}
}

void test_insert_and_find()
{
    const size_t size = 500;
    t_vector vec = generate_random_vector_with_sort(10, size, 500);

    // Old node for vec
    t_node * node = malloc(sizeof(t_node));
    for (int i = 0; i != size; ++i) {
        memcpy(node, get_from_node_vec(&vec, i), sizeof(t_node));
        t_node * node_in_vec = find_or_insert(&vec, node->name);

        assert(node_in_vec != NULL);
        assert(ft_strcmp(node_in_vec->name, node->name) == 0);
    }
    free(node);

    // New node for vec
    for (int i = vec.size + 1; i < size * 2; ++i)
    {
        t_node rnd_node = init_rand_node(100);
        assert(ft_strcmp(find_or_insert(&vec, rnd_node.name)->name, rnd_node.name) == 0);
        assert(vec.size == i);
    }
}

void test_sort()
{
    t_vector vec = generate_random_vector_with_sort(1, 100, 10);

    if (!is_sorted(vec))
        ft_printf("Error, vector not is sorted");
}

int main()
{
    test_find();
    test_insert_and_find();
    test_sort();
    return 0;
}
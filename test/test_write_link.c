//
// Created by Taisha Myrcella on 10/15/20.
//
#include <assert.h>
#include "lem_in.h"


int write_link_test(char *line, t_vector * node_vec)
{
    char **link;

    link = ft_strsplit(line, '-');
    char * src = link[0];
    char * dst = link[1];


    t_node_ptr src_node = find_or_insert(node_vec, src);
    t_node_ptr dst_node = find_or_insert(node_vec, dst);
    push_back_vec(&src_node->links, &dst_node); // POINTER TO NODE;
    return 0;
}
void print_traversal(t_node_ptr node) {
    for (int index = 0; index != node->links.size; ++index) {
        t_node_ptr *child = get_from_vec(&node->links, index);
        print_traversal(*child);
    }

    ft_printf("%s\n", node->name);
}

void test_write_link()
{
    t_vector node_vec = new_node_vec(100);
    write_link_test("0-1", &node_vec);
    write_link_test("0-2", &node_vec);
    write_link_test("0-3", &node_vec);
    write_link_test("1-3", &node_vec);

    assert(node_vec.size == 4);

    t_node * src = get_from_node_vec(&node_vec, 0);
    t_node * dst = get_from_node_vec(&node_vec, 1);

    assert(ft_strcmp(src->name, "0") == 0);
    assert(ft_strcmp(dst->name, "1") == 0);

    assert(src->links.size == 3);
    assert(dst->links.size == 1);

    t_node_ptr * link = (t_node_ptr*)get_from_vec(&src->links, 0);
    assert(ft_strcmp((*link)->name, dst->name) == 0);
    //print_traversal(get_from_node_vec(&node_vec, 0));
}

int main()
{
    test_write_link();

}
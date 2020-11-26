#include <stdlib.h>
#include "../vector.h"
#include "../lem_in.h"

size_t count_of_lines(char * buffer) {
    size_t result;
    size_t offset = 0;
    while (1) {
        char * ptr = ft_strchr(buffer, '\n');
        if (ptr == NULL) {
            return result;
        }
        offset += ptr - buffer;
        buffer = ptr + 1;
        ++result;
    }

}
// Maps p analog maps b = big
//Maps bo = big-superposition
// Maps f = 1 ant maps
// Maps ft = 10 ant maps
// Maps fth = 1000 ant maps

const unsigned int size = 27;
const char * maps[size] = {"b.txt", "b1.txt", "b2.txt", "b3.txt", "b4.txt", "b5.txt",
						   "p1.txt", "p2.txt", "p3.txt", "p4.txt", "p5.txt", "p6.txt",
			    "b6.txt", "bo1.txt", "bo2.txt", "bo3.txt", "bo4.txt", "bo5.txt", "bo6.txt",
			    "bo7.txt", "bo8.txt", "bo9.txt", "f1.txt", "f2.txt", "ft.txt", "ft1.txt", "fth1.txt"};

void solve_map(size_t index) {
    t_vector nodes = new_vector(100, sizeof(t_node));
    char * map = process_file(maps[index], &nodes);

    t_character character = get_character(&nodes);
    if (!(error_map_and_vec(&character)))
        free_map_and_vec(&nodes, map, 5);
    int  result = solve(character.root, *(int *) get_from_vec(&character.root->ants, 0), &nodes);
    char *ptr = ft_strchr(map, '\n');
    while (++ptr) {
		if (*ptr == '\n')
			break;
		printf("%c", *ptr);
	}

    printf("<--%d\n", result);
}

int main() {

    for (int index = 0; index != size; ++index) {
        printf("%s\n", maps[index]);
        solve_map(index);
    }
}

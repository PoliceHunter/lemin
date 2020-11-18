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

int main() {
    const unsigned int size = 14;
    const char * maps[size] = {"txt.txt", "b1.txt", "has_comments.map", "long_Chloe", "long_haaaaaaaaaaaaaaaaaaaardtest",
                               "long_hardmap", "no_possible.map",
                               "no_possible_solution.map", "subject-1.map",
                               "subject-2.map", "subject-3.map", "subject-4.map", "subject-5.map"};

    for (int index = 0; index != 13; ++index) {
    	printf("%s\n", maps[index]);
        t_vector vec = new_vector(100, sizeof(t_node));
        char * map = process_file(maps[index], &vec);

        t_character character = get_character(&vec);
        if (!(error_map_and_vec(&character)))
            free_map_and_vec(&vec, map, 5);
        char * result = solve(character.root, character.target);
        printf("\n");
    }
}

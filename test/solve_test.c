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
    const unsigned int size = 13;
    const char * maps[size] = {"txt.txt", "b1.txt", "has_comments.map", "long_Chloe", "long_haaaaaaaaaaaaaaaaaaaardtest",
                               "long_hardmap", "subject-1.map",
                               "subject-2.map", "subject-3.map",
                               "subject-4.map", "subject-5.map"};

    for (int index = 6; index != 7; ++index) {
    	printf("%s\n", maps[index]);
        t_vector nodes = new_vector(100, sizeof(t_node));
        char * map = process_file(maps[index], &nodes);

        t_character character = get_character(&nodes);
        if (!(error_map_and_vec(&character)))
            free_map_and_vec(&nodes, map, 5);
        char * result = solve(character.root, *(int *) get_from_vec(&character.root->ants, 0), &nodes);
		printf("%s", result);
        printf("\n");
    }
}

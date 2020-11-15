#include <stdlib.h>
#include "../vector.h"
#include "../lem_in.h"

int main() {
    const unsigned int size = 14;
    const char * maps[size] = {"pb.map", "42", "has_comments.map", "long_Chloe", "long_haaaaaaaaaaaaaaaaaaaardtest",
                               "long_hardmap", "no_mandatory_comments.map", "no_possible.map",
                               "no_possible_solution.map", "subject-1.map",
                               "subject-2.map", "subject-3.map", "subject-4.map", "subject-5.map"};

    for (int index = 0; index != 1; ++index) {
        printf("%s\n", maps[index]);
        t_vector vec = new_vector(100, sizeof(t_node));
        char * map = process_file(maps[index], &vec);

        t_character character = get_character(&vec);
        if (!(error_map_and_vec(&character)))
            free_map_and_vec(&vec, map, 5);
        char * result = solve(character.root, character.target);

        printf("%s\n", map);
        printf("%s\n", result);
        printf("\n");
        free(map);
        free_vec_node(&vec);
    }
}

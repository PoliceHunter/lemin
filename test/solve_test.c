#include "lem_in.h"

int main() {
    const unsigned int size = 13;
    const char * maps[size] = {"42", "has_comments.map", "long_Chloe", "long_haaaaaaaaaaaaaaaaaaaardtest",
                               "long_hardmap", "no_mandatory_comments.map", "no_possible.map",
                               "no_possible_solution.map", "subject-1.map",
                               "subject-2.map", "subject-3.map", "subject-4.map", "subject-5.map"};

    for (int index = 0; index != size; ++index) {
        printf("%s\n", maps[index]);
        t_vector vec = new_vector(100, sizeof(t_node));
        printf("%s\n", process_file(ft_strjoin("./maps/", maps[index]), &vec));
    }
}
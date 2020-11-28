#include <stdlib.h>
#include "../vector.h"
#include "../lem_in.h"

// Maps p analog maps b = big
//Maps bo = big-superposition
// Maps f = 1 ant maps
// Maps ft = 10 ant maps
// Maps fth = 1000 ant maps
#include <sys/time.h>

typedef unsigned long long timestamp_t;

static timestamp_t
get_timestamp() {
    struct timeval now;
    gettimeofday(&now, NULL);
    return now.tv_usec + (timestamp_t) now.tv_sec * 1000000;
}
static int i = 0;
int solve_map(const char * filename) {
    t_vector nodes = new_vector(100, sizeof(t_node));

    timestamp_t start = get_timestamp();
    char * map = process_file(filename, &nodes);
    t_character character = get_character(&nodes);
    if (!(error_map_and_vec(&character)))
        free_map_and_vec(&nodes, map, 5);
    char * history = "";
    int result = solve(character.root, *(int *) get_from_vec(&character.root->ants, 0), &nodes, &history);
    float secs = (get_timestamp() - start) / 1000000.0L;

    char * ptr = ft_strchr(map, '\n');
    int cmp = 0;
    char * res;

    while (++ptr) {
        if (ft_isdigit(*ptr)) {
            cmp = ft_atoi(--ptr);
            break;
        }
    }
    i++;
    printf("%d %s time is - [%f] NEED [%d] - OUR [%d] - delta is %d\n", i, filename, secs, cmp, result, result - cmp);
    return 1;
}

void solve_maps() {
    const unsigned int size = 27;//8; //27
    const char * maps[size] = {"b.txt", "b1.txt", "b2.txt", "b3.txt", "b4.txt", "b5.txt",
                               "p1.txt", "p2.txt", "p3.txt", "p4.txt", "p5.txt", "p6.txt",
                               "b6.txt", "bo1.txt", "bo2.txt", "bo3.txt", "bo4.txt", "bo5.txt", "bo6.txt",
                               "bo7.txt", "bo8.txt", "bo9.txt", "f1.txt", "f2.txt", "ft.txt", "ft1.txt", "fth1.txt"};
    for (int index = 1; index != size; ++index)
    {
        solve_map(ft_strjoin("./test/", maps[index]));
    }
}

int solve_superposition_map(int i)
{
    return solve_map(ft_strjoin_free2("./supermaps/", ft_itoa(i)));
}

void solve_superposition_maps() {
    const size_t size = 250;

    size_t failed = 0;
    for (int i = 1; i != size; ++i) {
        failed += solve_superposition_map(i);
    }
    printf("Failed %f\n", failed / size * 100.0);
}

int main() {
    solve_maps();
    solve_superposition_maps();
    printf("%d", i /= 1000);
}

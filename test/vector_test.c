#include <assert.h>
#include "vector.h"

void test_create() {
    t_vector vec = new_vector(100, 1);
    assert(vec.capacity == 100);
    assert(vec.elem_size == 1);
    free_vec(&vec);
}

void test_push() {
    t_vector vec = new_vector(5, sizeof(int));
    int val = 10;
    push_back_vec(&vec, (void *) &val);
    assert(*((int *) get_from_vec(&vec, 0)) == val);
    assert(vec.size == 1);

    val = 11;
    push_back_vec(&vec, (void *) &val);
    assert(*((int *) get_from_vec(&vec, 1)) == val);
    assert(vec.size == 2);

    free_vec(&vec);
}

void test_push_with_expand() {
    t_vector vec = new_vector(1, sizeof(int));

    for (int index = 0; index != 1000; ++index) {
        int value = rand();
        push_back_vec(&vec, (void *) &value);
        assert(*((int *) get_from_vec(&vec, index)) == value);
        assert(vec.size == (index + 1));
    }

    free_vec(&vec);
}

void test_for_pop_back_simple() {
    t_vector vec = new_vector(1, sizeof(int));

    int value = rand();
    push_back_vec(&vec, &value);

    int * popped = pop_back_vec(&vec);
    assert(value == *popped);

    free(popped);
    free_vec(&vec);
}

void test_for_pop_back() {
    t_vector vec = new_vector(1, sizeof(int));

    const int size = 1000000;
    for (int i = 0; i != size; ++i) {
        push_back_vec(&vec, &i);
    }

    {
        int value = rand();
        push_back_vec(&vec, &value);
        int * popped = (int *) pop_back_vec(&vec);
        assert(value == *popped);
        free(popped);
    }

    for (int i = size - 1; i >= 0; --i) {
        int * popped = pop_back_vec(&vec);
        assert(*popped == i);
        free(popped);
    }

    free_vec(&vec);
}


void test_for_pop_front_simple() {
    t_vector vec = new_vector(1, sizeof(int));

    int value = rand();
    push_back_vec(&vec, &value);
    int * popped = pop_front_vec(&vec);
    assert(value == *popped);

    free(popped);
    free_vec(&vec);
}

void test_for_pop_front() {
    t_vector vec = new_vector(1, sizeof(int));

    const int size = 100000;
    for (int i = 0; i != size; ++i) {
        push_back_vec(&vec, &i);
    }

    for (int i = 0; i != size; ++i) {
        int * popped = pop_front_vec(&vec);
        assert(*popped == i);
        free(popped);
    }

    free_vec(&vec);
}

void test_push_front_vec_simple() {
    t_vector vec = new_vector(1, sizeof(int));
    int first = rand();
    push_front_vec(&vec, (void *) &first);
    assert(*((int *) get_from_vec(&vec, 0)) == first);
    assert(vec.size == 1);

    int second = rand();
    push_front_vec(&vec, (void *) &second);
    assert(*((int *) get_from_vec(&vec, 0)) == second);
    assert(*((int *) get_from_vec(&vec, 1)) == first);
    assert(vec.size == 2);

    free_vec(&vec);
}

void test_insert_into_vec_back_and_front() { // Push front and back by insert
    t_vector vec = new_vector(1, sizeof(int));

    const int size = 100;
    for (int i = 0; i != size; ++i) {
        insert_into_vec(&vec, i, &i); // Push back
    }

    for (int i = 0; i != size; ++i) {
        insert_into_vec(&vec, 0, &i); // Push front
    }

    for (int i = 0; i != size; ++i) {
        assert(*(int *) get_from_vec(&vec, i) == size - 1 - i);
        int * element = (int *) get_from_vec(&vec, i + size);
        assert(*element == i);
    }
}

void test_insert_vec_middle_simple() {
    t_vector vec = new_vector(1, sizeof(int));

    const int size = 10;
    for (int i = 0; i != size; ++i) {
        push_back_vec(&vec, &i); // Push back
    }

    int value = rand();
    insert_into_vec(&vec, size / 2, &value);

    for (int i = 0; i != size / 2; ++i) {
        const int * element = (int*)get_from_vec(&vec, i);
        assert(*element == i);
    }

    const int * element = (int*)get_from_vec(&vec, size/2);
    assert(*element == value);

    for (int i = size / 2 + 1; i != size; ++i) {
        const int * element = (int*)get_from_vec(&vec, i);
        assert(*element == i - 1);
    }
}

void test_insert_vec_middle() {
    t_vector vec = new_vector(1, sizeof(int));

    const int size = 10;
    for (int i = 0; i != size; ++i) {
        insert_into_vec(&vec, i, &i); // Push back
    }

    for (int i = 0; i != size; ++i) {
        insert_into_vec(&vec, i, &i); // Push front
    }

    for (int i = 0; i != size; ++i) {
        insert_into_vec(&vec, size + i, &i); // Push middle
    }

    for (int i = 0; i != size; ++i) {
        assert(*(int *) get_from_vec(&vec, i) == (*(int *) get_from_vec(&vec, i + size)));
        int * element = (int *) get_from_vec(&vec, i + size);
        assert(*element == i);
    }
}
void test_swap_simple() {
    t_vector vec = new_vector(1, sizeof(int));

    const int size = 10;
    for (int i = 0; i != size; ++i) {
        insert_into_vec(&vec, i, &i); // Push back
    }
    int index1 = rand() % size;
    int index2 = rand() % size;
    int first = (* (int *) get_from_vec(&vec, index1));
    int second = (*(int *) get_from_vec(&vec, index2));

    swap_vec(&vec, index1, index2);
    assert(first == (*(int *) get_from_vec(&vec, index2)));
    assert(second == (*(int *) get_from_vec(&vec, index1)));
}

void test_remove_simple() {
    t_vector vec = new_vector(1, sizeof(int));

    const int size = 10;
    for (int i = 0; i != size; ++i) {
        insert_into_vec(&vec, i, &i); // Push back
    }

    const int index = 5;
    remove_from_vec(&vec, index);

    for (int i = 0; i != 5; i++)
    {
        assert((*(int *)get_from_vec(&vec, i)) == i);
    }

    for (int i = 5; i != size - 1; i++)
    {
        int * ptr = get_from_vec(&vec, i);
        assert(ptr != NULL && *ptr == i + 1);
    }

    assert(vec.size != size);
}

int main() {
    test_create();
    test_push();
    test_push_with_expand();
    test_for_pop_back_simple();
    test_for_pop_back();
    test_for_pop_front_simple();
    test_for_pop_front();
    test_push_front_vec_simple();
    test_insert_into_vec_back_and_front();
    test_insert_vec_middle_simple();
    test_insert_vec_middle();
    test_swap_simple();
    test_remove_simple();
    return 0;
}
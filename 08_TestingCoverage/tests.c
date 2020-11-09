#include <stdint.h>
#include <assert.h>

#include "src/buf.h"

static void test_initialization(){
	float *a = NULL;

	assert(buf_capacity(a) == 0);
	assert(buf_size(a) == 0);
}

static void test_push_clear_free(){
	float *a = NULL;

	buf_push(a, 1.3f);
	assert(buf_size(a) == 1);
	assert(a[0] == 1.3f);

	buf_clear(a);
	assert(buf_size(a) == 0);
	assert(a != NULL);

	buf_free(a);
	assert(a == NULL);
}

static void test_clear_empty(){
	float *a = NULL;

	buf_clear(a);
	assert(buf_size(a) == 0);
	assert(a == NULL);
}

static void test_push(){
	int size = 10000;
	int *a = NULL;

	for(int i = 0; i < size; i++){
		buf_push(a, i);
	}
	assert(buf_size(a) == size);

	int match = 0;
	for(int i = 0; i < size; i++){
		match += a[i]== i;
	}

	assert(match == size);

	buf_free(a);
	assert(a == NULL);
}

static void test_grow_trucn(){
	int size = 1000;
	int* a = NULL;

	buf_grow(a, size);
	assert(buf_capacity(a) == size);
	assert(buf_size(a) == 0); 

	buf_trunc(a, size / 10);
	assert(buf_capacity(a) == size / 10);

	buf_free(a);
	assert(a == NULL);
}

static void test_pop(){
	float* a = NULL;

	buf_push(a, 1.1);
	buf_push(a, 1.2);
	buf_push(a, 1.3);
	buf_push(a, 1.4);
	assert(buf_size(a) == 4);
	assert(buf_pop(a) == 1.4f);

	buf_trunc(a, 3);
	assert(buf_size(a) == 3);
	assert(buf_pop(a) == 1.3f);
	assert(buf_pop(a) == 1.2f);
	assert(buf_pop(a) == 1.1f);
	assert(buf_size(a) == 0);

	buf_free(a);
	assert(a == NULL);
}

typedef void (*test_type)(void);

int main(int argc, char** argv){
	test_type tests[] = {
		test_initialization,
		test_push_clear_free,
		test_clear_empty,
		test_push,
		test_grow_trucn,
		test_pop,
	};

	for (int i = 1; i < argc; i++){
		int test_num = atoi(argv[i]);
		assert(test_num < sizeof(tests) / sizeof(test_type));
		tests[test_num]();
	}
	return 0;
}

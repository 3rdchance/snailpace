#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "libpmemobj.h"

#define POOL_LAYOUT "test_pool"

struct test_root {
	int open_cnt;
};

void process_fn(void* arg)
{
	const char* pool_name = arg;
	PMEMobjpool *pop = NULL;
	int new_create = 0;

	if ((pop = pmemobj_open(pool_name, POOL_LAYOUT)) == NULL) {
		pop = pmemobj_create(pool_name, POOL_LAYOUT, PMEMOBJ_MIN_POOL, 0666);
		new_create = 1;
	}

	if (pop == NULL) {
		printf("\033[1;31mError %m\033[0m\n");
		exit(EXIT_FAILURE);
	}

	struct test_root* root = pmemobj_direct(pmemobj_root(pop, sizeof(*root)));

	if (new_create) {
		root->open_cnt = 0;
	} else {
		root->open_cnt += 1;
	}
	
	printf("\033[1;32mpool open time %d\033[0m\n", root->open_cnt);
	pmemobj_persist(pop, root, sizeof(*root));

	pmemobj_close(pop);

}

void wait_new_process(void (*f)(void*), void* arg)
{
	pid_t child;

	child = fork();
	if (child < 0) {
		printf("\033[1;31mError %m\033[0m\n");
		exit(EXIT_FAILURE);
	}

	if (child == 0) {
	// child
		f(arg);
		exit(EXIT_SUCCESS);
	} else {
	// parent
		wait(NULL);
	}

}



int main(int argc, char** argv)
{
	if (argc != 2) {
		printf("\033[1;31mUsage: %s pool\033[0m\n", argv[0]);
		return -1;
	}

	for (int i = 0; i < 10; i++) {
		wait_new_process(process_fn, argv[1]);
        }

	return 0;
}

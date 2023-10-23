#include <stdio.h>
#include "libpmemobj.h"

#define  POOL_LAYOUT "test_pool"

/*
 * How pmemobj_pool create and open
 */
struct pool_root {
	char msg[15];
	int cnt;
};

int main(int argc, char** argv)
{
	struct pool_root *root = NULL;

	if (argc != 2) {
		printf("Usage %s pool_file\n", argv[1]);
		return -1;
	}

	PMEMobjpool *pop = pmemobj_open(argv[1], POOL_LAYOUT);
	if (pop == NULL) {
		pop = pmemobj_create(argv[1], POOL_LAYOUT, PMEMOBJ_MIN_POOL, 0x666);
		if (pop == NULL) {
			printf("\033[1;31mpool create failed: %s\033[0m\n", pmemobj_errormsg());
			return -1;
		}
		/* create the pool root */
		/* Q1  pmemobj_root return error ? */
		root = pmemobj_direct(pmemobj_root(pop, sizeof(*root)));
		strcpy(root->msg, "helloworld");
		root->cnt = 0;
		pmemobj_persist(pop, root, sizeof(root));
		printf("\033[1;32mfirst open pool success\033[0m\n");
	
	} else {
		/* incr the pool root count */
		root = pmemobj_direct(pmemobj_root(pop, sizeof(*root)));
		root->cnt++;
		printf("\033[1;32mopen pool %d times\033[0m\n", root->cnt);
		pmemobj_persist(pop, root, sizeof(root));
	}

	pmemobj_close(pop);
	return 0;
}

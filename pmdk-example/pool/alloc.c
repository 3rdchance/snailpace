#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <libpmemobj.h>
/*
 * 
 * if paintball empty reload it, or shoot it
 */


#define LAYOUT "PALLOCATE"
#define BULLET_CNT 6

typedef int bullet;

int init_paintball(PMEMobjpool *pop, void  *ptr, void *arg)
{
	*(int*)ptr = rand();
	pmemobj_persist(pop, ptr, sizeof(bullet));
	return 0;
}

int main(int argc, char** argv) 
{
	PMEMobjpool *pop  = NULL;
	int ret;

	if (argc < 2) {
		exit(EXIT_FAILURE);
		printf("\033[1;31mUsage %s pool\033[0m\n");
	}

	pop = pmemobj_open(argv[1], LAYOUT);
	if (pop == NULL) {
		pop = pmemobj_create(argv[1], LAYOUT, PMEMOBJ_MIN_POOL, 0x066);
		if (pop == NULL) {
			printf("\033[1;31mpool create failed: %s \033[0m\n", pmemobj_errormsg());
			exit(EXIT_FAILURE);
		}
	}

	//TODO: new root will set to ZERO ?
	PMEMoid *root = pmemobj_direct(pmemobj_root(pop, sizeof(PMEMoid) * BULLET_CNT));

	int ind = getpid() % BULLET_CNT;
	if (OID_IS_NULL(root[ind])) {
		printf("\033[1;32mReloading %d bullet\033[0m\n", ind);
		if(pmemobj_alloc(pop, &root[ind], sizeof(bullet), 0, init_paintball, NULL) != 0) {
			printf("\033[1;31mAllocate Memory Failed %s\n", pmemobj_errormsg());
			goto out;
		}
	} else {
		printf("\033[1;32mShooting %d color %d\033[0m\n", ind, *(int*)pmemobj_direct(root[ind]));
		pmemobj_free(&root[ind]);
	}


out:
	pmemobj_close(pop);
	return 0;
}

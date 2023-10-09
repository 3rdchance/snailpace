#include <stdio.h>

struct bst_node {
	int key, value;
	struct bst_node *left, *right;
};

static struct bst_node *root = NULL;

struct bst_node *bst_create()
{
	return NULL;
}

void bst_destroy(struct bst_node *root)
{
}

int bst_get(struct bst_node *root)
{
	return 0;
}

int bst_put(struct bst_node *root, int key, int value)
{
	return 0;
}

/* return 0, continue traverse, return -1, stop the traverse */
typedef int (*callback) (struct node *n);
int traverse(struct node *root, callback c)
{
	return 0;
}

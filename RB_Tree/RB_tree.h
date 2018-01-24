#ifndef __RB_TREE_H__
#define __RB_TREE_H__

#define RB_NULL 0
#define RB_BLACK 0
#define RB_RED 1

typedef struct RB_TREE_s RB_TREE;

RB_TREE* RB_insert_fixup(RB_TREE *T, RB_TREE *z);

struct RB_TREE_s
{
	unsigned char color;
	unsigned int key;
	RB_TREE *left;
	RB_TREE *right;
	RB_TREE *p;
	void *data;
};

#endif
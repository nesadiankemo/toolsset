#include "RB_tree.h"

RB_TREE *BR_root(RB_TREE *T) {
	RB_TREE *p = T;
	if (T == RB_NULL) {
		return RB_NULL;
	}
	while (p->p != RB_NULL) {
		p = p->p;
	}
	return p;
}

RB_TREE* RB_left_rotate(RB_TREE *T, RB_TREE *x) {
	RB_TREE *y;
	y = x->right;
	x->right = y->left;

	if (y->left != RB_NULL) {
		y->left->p = x; // y->left can be Null
	}
	y->p = x->p;
	if (x->p == RB_NULL) {
		T = y;
	} else if (x == x->p->left) {
		x->p->left = y;
	} else {
		x->p->right = y;
	}
	y->left = x;
	x->p = y;
	return T;
}
RB_TREE* RB_right_rotate(RB_TREE *T, RB_TREE *x) {
	RB_TREE *y;
	y = x->left;
	x->left = y->right;

	if (y->right != RB_NULL) {
		y->right->p = x; // y->right can be Null
	}
	y->p = x->p;
	if (x->p == RB_NULL) {
		T = y;
	} else if (x == x->p->left) {
		x->p->left = y;
	} else {
		x->p->right = y;
	}
	y->right = x;
	x->p = y;
	return T;
}

RB_TREE* RB_insert(RB_TREE *T, RB_TREE *z) {
	RB_TREE *y = RB_NULL;
	RB_TREE *x = BR_root(T);

	while (x != RB_NULL) {
		y = x;
		if (z->key < y->key) {
			x = x->left;
		} else {
			x = x->right;
		}
	}
	z->p = y;
	if (y == RB_NULL) {
		// 树为空
		T = z;
	} else if (z->key < y->key) {
		y->left = z;
	} else {
		y->right = z;
	}

	z->left = RB_NULL;
	z->right = RB_NULL;
	z->color = RB_RED;
	T = RB_insert_fixup(T, z);
	return BR_root(T);
}

RB_TREE* RB_insert_fixup(RB_TREE *T, RB_TREE *z) {
	RB_TREE *y = RB_NULL;
	if (T == z) {
		//原树为空树
		T->color = RB_BLACK;
		return T;
	} else if (z->p->color == RB_BLACK) {
		// 红黑树没有破坏
		return T;
	}

	// 3种情况
	while (z->p->color == RB_RED) {

		// 当前节点的父节点为红色
		// 且父节点为祖父节点左节点
		if (z->p == z->p->p->left) {
			// 取叔叔节点
			y = z->p->p->right;

			if (y != RB_NULL && y->color == RB_RED) { // 叔叔节点为红色
				z->p->color = RB_BLACK;
				y->color = RB_BLACK;
				z->p->p->color = RB_RED;
				z = z->p->p;
			} else if (z == z->p->right) { 	 // 叔叔节点为黑色且当前节点为其父节点的右子节点
				z = z->p;
				T = RB_left_rotate(T, z);
			} else {						// 叔叔节点为黑色且当前节点为其父节点的左子节点
				z->p->color = RB_BLACK;
				z->p->p->color = RB_RED;
				T = RB_right_rotate(T, z->p->p);
			}
			
		} else {
			// 取叔叔节点
			y = z->p->p->left;
			if (y != RB_NULL && y->color == RB_RED) {
				z->p->color = RB_BLACK;
				y->color = RB_BLACK;
				z->p->p->color = RB_RED;
				z = z->p->p;
			} else if (z == z->p->left) {
				z = z->p;
				T = RB_right_rotate(T, z);
			} else {
				z->p->color = RB_BLACK;
				z->p->p->color = RB_RED;
				T = RB_left_rotate(T, z->p->p);
			}
		}
	}
	BR_root(T)->color = RB_BLACK;
	return T;
}

void RB_delete(RB_TREE *T, RB_TREE *z) {

}

void RB_delete_fixup(RB_TREE *T, RB_TREE *z) {

}

RB_TREE *RB_get(RB_TREE *T, unsigned int key) {
	RB_TREE *p;
	int count = 0;
	p = T;
	while (p != RB_NULL) {
		count++;
		if (p->key == key) {
			return p;
		} else if (key < p->key) {
			p = p->left;
		} else {
			p = p->right;
		}
	}
	
	return RB_NULL;
}
#include "circular_buffer.h"
/*
 说明：
 由于本环形缓冲区判断是否为满的方法限制，
 初始化时，缓冲区的大小要设置为2的幂，
 否则会导致 cbIsFull() 函数判断错误。
*/

/*
 初始化环形缓冲区
*/
void cbInit(CircularBuffer *cb, int size) {
	cb->size = size;
	cb->start = 0;
	cb->end = 0;
	cb->peek = cb->start;
	cb->elems = (char *)malloc(size * sizeof(char));
}

/*
 清空缓冲区
*/
 void cbClear(CircularBuffer *cb) {
	cb->end = cb->start = 0;
}

/*
 缓冲区是否已满
*/
int cbIsFull(CircularBuffer *cb) {
	return cb->end == (cb->start ^ cb->size);
}

/*
 缓冲区是否为空
*/
int cbIsEmpty(CircularBuffer *cb) {
	return cb->end == cb->start;
}

/*
 缓冲区相对与peek 指针是否为空
*/
int cbIsPeekEmpty(CircularBuffer *cb) {
	return cb->end == cb->peek;
}

/*
 指针自增
*/
int cbIncr(CircularBuffer *cb, int p) {
	return (p + 1) & (2 * cb->size - 1);
}

/*
 写
*/
void cbWrite_(CircularBuffer *cb, char elem) {
	cb->elems[cb->end & (cb->size - 1)] = elem;
	if (cbIsFull(cb)) {
		cb->start = cbIncr(cb, cb->start);
	}
	cb->end = cbIncr(cb, cb->end);
}
void cbWrite(CircularBuffer *cb, char *elem, int count) {
	int i;
	for (i = 0; i < count; i++) {
		cbWrite_(cb, elem[i]);
	}
}

/*
 读
*/
int cbRead_(CircularBuffer *cb, char *elem) {
	if (cbIsEmpty(cb)) {
		return 0;
	}
	*elem = cb->elems[cb->start & (cb->size - 1)];
	cb->start = cbIncr(cb, cb->start);
	return 1;
}

unsigned char cbRead(CircularBuffer *cb) {
	unsigned char elem;
	if (cbIsEmpty(cb)) {
		return -1;
	}
	elem = cb->elems[cb->start & (cb->size - 1)];
	cb->start = cbIncr(cb, cb->start);
	return elem;
}


/**/
int cbGetUsed(CircularBuffer *cb) {
	int size;
	if (cb->end >= cb->start) {
		size = cb->end - cb->start;
	} else {
		// ?
		size = 2 * cb->size - cb->start + cb->end;
	}
	return size;
}

/*
 同步peek 和读指针
*/
void cbResetPeek(CircularBuffer *cb) {
	cb->peek = cb->start;
}
void cbUpdateToPeek(CircularBuffer *cb) {
	cb->start = cb->peek;
}

/*
 peek
*/
int cbPeek(CircularBuffer *cb, char *elem) {
	if (cbIsPeekEmpty(cb)) {
		return 0;
	}
	*elem = cb->elems[cb->peek & (cb->size - 1)];
	cb->peek = cbIncr(cb, cb->peek);
	return 1;
}

int cbPeekCount(CircularBuffer *cb, char *buf, int count) {
	int size, i;
	if (cb->end >= cb->peek) {
		size = cb->end - cb->peek;
	} else {
		// ?
		size = 2 * cb->size - cb->peek + cb->end;
	}
	if (count < size) {
		size = count;
	}
	for (i = 0; i < size; i++) {
		cbPeek(cb, &buf[i]);
	}
	return size;
}
#ifndef __CIRCULAR_BUFFER_H__

#define __CIRCULAR_BUFFER_H__
#include "stdlib.h"

/**
 环形缓冲区结构体
*/
typedef struct
{
	int size; // 缓冲区大小
	int start; // 读指针
	int end; // 写指针
	int peek; // peek 指针
	char *elems; // 缓冲区
} CircularBuffer;

/*
 初始化环形缓冲区
*/
void cbInit(CircularBuffer *cb, int size);

/*
 清空缓冲区
*/
void cbClear(CircularBuffer *cb);

/*
 缓冲区是否已满
*/
int cbIsFull(CircularBuffer *cb);

/*
 缓冲区是否为空
*/
int cbIsEmpty(CircularBuffer *cb);

/*
 缓冲区相对与peek 指针是否为空
*/
int cbIsPeekEmpty(CircularBuffer *cb);

/*
 指针自增
*/
int cbIncr(CircularBuffer *cb, int p);

/*
 写
*/
void cbWrite_(CircularBuffer *cb, char elem);
void cbWrite(CircularBuffer *cb, char *elem, int count);

/*
 读
*/
int cbRead_(CircularBuffer *cb, char *elem);

unsigned char cbRead(CircularBuffer *cb);

int cbGetUsed(CircularBuffer *cb);

/*
 同步peek 和读指针
*/
void cbResetPeek(CircularBuffer *cb);
void cbUpdateToPeek(CircularBuffer *cb);

/*
 peek
*/
int cbPeek(CircularBuffer *cb, char *elem);

int cbPeekCount(CircularBuffer *cb, char *buf, int count);
#endif
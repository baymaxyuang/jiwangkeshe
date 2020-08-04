#pragma once
#include "util.h"

MyQueue Create_Queue(int MaxSize);
void Delete_Queue(MyQueue Q);
int In_Queue(MyQueue Q, DataGramInfo datagram_info);
int Out_Queue(MyQueue Q, DataGramInfo* datagram_info_ptr);
int QIs_full(MyQueue Q);
int QIs_empty(MyQueue Q);
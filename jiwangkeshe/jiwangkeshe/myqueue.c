#include "util.h"
#include "queue.h"
#include "dnsProtocol.h"

//信息队列相关操作,共六个
MyQueue Create_Queue(int MaxSize)
{
	MyQueue Q = (MyQueue)malloc(sizeof(struct queue));
	Q->Front = Q->Rear = NULL;
	Q->MaxSize = MaxSize;
	Q->CurrentSize = 0;

	return Q;
}

void Delete_Queue(MyQueue Q)
{
	DataGramInfo temp;
	while (!QIs_empty(Q))
	{
		Out_Queue(Q, &temp);
	}
	free(Q);
}

int In_Queue(MyQueue Q, DataGramInfo datagram_info)
{
	if (QIs_full(Q))
	{
		return 0;//表示入队失败
	}
	else
	{
		PtrToQNode temp = (PtrToQNode)malloc(sizeof(struct QNode));
		temp->datagram_info = datagram_info;
		temp->Next = NULL;
		Q->CurrentSize += 1;

		if (QIs_empty(Q))
		{
			Q->Front = temp;
			Q->Rear = temp;

		}
		else
		{
			Q->Rear->Next = temp;
			Q->Rear = temp;
		}
		return 1;
	}

}
int Out_Queue(MyQueue Q, DataGramInfo* datagram_info_ptr)
{
	if (QIs_empty(Q))
	{
		return 0;//表示出队失败
	}
	else
	{
		*datagram_info_ptr = Q->Front->datagram_info;
		Q->CurrentSize -= 1;
		if (Q->Front == Q->Rear)
		{
			free(Q->Front);
			Q->Front = Q->Rear = NULL;
		}
		else
		{
			PtrToQNode temp = Q->Front;
			Q->Front = Q->Front->Next;
			free(temp);
		}
		return 1;
	}
}

int QIs_full(MyQueue Q)
{
	return (Q->CurrentSize == Q->MaxSize) ? 1 : 0;
}

int QIs_empty(MyQueue Q)
{
	return (Q->Front == NULL) ? 1 : 0;
}
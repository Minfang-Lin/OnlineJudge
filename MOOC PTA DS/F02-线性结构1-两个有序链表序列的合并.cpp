#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct Node *PtrToNode;
struct Node {
    ElementType Data;
    PtrToNode   Next;
};
typedef PtrToNode List;

List Read(); /* 细节在此不表 */
void Print( List L ); /* 细节在此不表；空链表将输出NULL */

List Merge( List L1, List L2 );

int main()
{
    List L1, L2, L;
    L1 = Read();
    L2 = Read();
    L = Merge(L1, L2);
    Print(L);
    Print(L1);
    Print(L2);
    return 0;
}

List Read() {
	int N;
	scanf("%d", &N);
	List L = (PtrToNode)malloc(sizeof(struct Node));
	L->Next = NULL;
	PtrToNode Head = L;
	while(N--) {
		L->Next = (PtrToNode)malloc(sizeof(struct Node));
		L = L->Next;
		scanf("%d", &(L->Data));
		L->Next = NULL;
	}
	return Head;
}

void Print( List L ) {
	if (L->Next) {
		L = L->Next;
		while (L) {
			printf("%d ", L->Data);
			L = L->Next;
		}
		printf("\n");
	} else {
		printf("NULL\n");
	}
}

List Merge( List L1, List L2 ) {
	List L = (PtrToNode)malloc(sizeof(struct Node));
	PtrToNode Head = L, p1 = L1->Next, p2 = L2->Next;
	while (p1 && p2) {
		if (p1->Data < p2->Data) {
			L->Next = p1;
			p1 = p1->Next;
			L = L->Next;
		} else {
			L->Next = p2;
			p2 = p2->Next;
			L = L->Next;
		}
	}
	while (p1) {
		L->Next = p1;
		p1 = p1->Next;
		L = L->Next;
	}
	while (p2) {
		L->Next = p2;
		p2 = p2->Next;
		L = L->Next;		
	}
	L->Next = NULL;
	L1->Next = NULL;
	L2->Next = NULL;
	return Head;
}

#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct Node *PtrToNode;
struct Node {
    ElementType coef;
    ElementType expon;
    PtrToNode   next = nullptr;
    Node (const PtrToNode other);
    Node () = default;
    Node (int c, int e) : coef(c), expon(e) { }
};
typedef PtrToNode List;

inline Node::Node(const PtrToNode other) {
	coef = other->coef;
	expon = other->expon;
	next = new Node();
}

List Read(); 
void Print( List L ); 
List Multi( List L1, List L2 );
List Add( List L1, List L2 );

int main()
{
    List L1, L2;
    L1 = Read();
    L2 = Read();
    Print(Multi(L1, L2));
    Print(Add(L1, L2));
    return 0;
}

List Read() {
	int N;
	scanf("%d", &N);
	List L = new Node();
	L->next = NULL;
	PtrToNode Head = L;
	while(N--) {
		int c, e;
		scanf("%d %d", &c, &e);
		L->next = new Node(c, e);
		L = L->next;
	}
	return Head;
}

void Print( List L ) {
	L = L->next;
	if (!L) {
		printf("0 0\n");
		return;
	}
	bool isFirst = true;
	while (L) {
		if (isFirst) isFirst = false;
		else printf(" ");
		printf("%d %d", L->coef, L->expon);
		L = L->next;
	}
	printf("\n");
}

List Add( List L1, List L2 ) {
	List L = new Node();
	PtrToNode Head = L, p1 = L1->next, p2 = L2->next;
	while (p1 && p2) {
		if (p1->expon < p2->expon) {
			L->next = new Node(p2);
			L = L->next;
			p2 = p2->next;
		} else if (p1->expon == p2->expon) {
			int c = p1->coef + p2->coef;
			if (c) {
				L->next = new Node (c, p1->expon);
				L = L->next;
			}
			p1 = p1->next;
			p2 = p2->next;
		} else {
			L->next = new Node(p1);
			L = L->next;
			p1 = p1->next;
		}
	}
	while (p1) {
		L->next = new Node(p1);
		L = L->next;
		p1 = p1->next;		
	}
	while (p2) {
		L->next = new Node(p2);
		L = L->next;
		p2 = p2->next;				
	}
	L->next = nullptr;
	return Head;
}

List Multi( List L1, List L2 )  {
	List L = new Node();
	PtrToNode Head = L, p1 = L1->next, p2 = L2->next;
	// 先用算式2的第一项与算式1相乘 
	while (p1) {
		L->next = new Node(p1->coef * p2->coef, p1->expon + p2->expon);
		L = L->next;
		p1 = p1->next;
	}
	p1 = L1->next;
	p2 = p2->next;
	while (p2) {
		PtrToNode preNode = Head, curNode = preNode->next;
		while (p1) {
			PtrToNode temp = new Node(p1->coef * p2->coef, p1->expon + p2->expon);
			bool isInsert = false;
			while (curNode) {
				if (temp->expon < curNode->expon) {
					preNode = curNode;
					curNode = curNode->next;
				} else if (temp->expon == curNode->expon) {
					int c = temp->coef + curNode->coef;
					if (c) {						
						curNode->coef = c;
						preNode = curNode;
						curNode = curNode->next;
					} else {
						preNode->next = curNode->next;
						// 当要删除的不是尾节点的时候 
						if(curNode->next) {							
							preNode = curNode->next;
						}	
						curNode = preNode->next;	
					}
					isInsert = true;
				} else {
					preNode->next = temp;
					temp->next = curNode;
					preNode = curNode;
					curNode = curNode->next;					
					isInsert = true;
				}
				if (isInsert)  break;
			}
			if (!isInsert) {
				preNode->next = temp;
				curNode = preNode->next;
			} 
			p1 = p1->next;
		}
		p1 = L1->next;
		p2 = p2->next;
	}
	return Head;
}

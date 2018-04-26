#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct Node *PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;
struct Node {
    ElementType Element;
    Position Next;
};

List Read()
{
	PtrToNode head=NULL,tail=NULL,temp;
	int i,n;
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		temp=(PtrToNode)malloc(sizeof(struct Node));
		scanf("%d",&(temp->Element));
		temp->Next=NULL;
		if(head==NULL)
		{
			head=temp;
		}
		else
		{
			tail->Next=temp;
		}
		tail=temp;
	}
	return head;
}
void Print( List L )
{
	if(L==NULL)
		return ;
	printf("%d",L->Element);
	L=L->Next;
	while(L!=NULL)
	{
		printf(" %d",L->Element);
		L=L->Next;
	}
	return ;
}
List Reverse( List L )
{
	PtrToNode head=NULL,temp,tail=NULL;
	while(L!=NULL)
	{
		temp=(PtrToNode)malloc(sizeof(struct Node));
		temp->Element=L->Element;
		if(head==NULL)
		{
			head=temp;
			temp->Next=NULL;
		}
		else
		{
			temp->Next=head;
		}
		L=L->Next;
	}
}

int main()
{
    List L1, L2;
    L1 = Read();
    L2 = Reverse(L1);
    Print(L1);
    Print(L2);
    return 0;
}
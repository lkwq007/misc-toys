#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
typedef struct Node *PtrToNode;
struct Node  {
    int Coefficient;
    int Exponent;
    PtrToNode Next;
};
typedef PtrToNode Polynomial;


Polynomial Read()
{
	Polynomial head=NULL,tail,temp;
	int i,n;
	scanf("%d",&n);
	head=(Polynomial)malloc(sizeof(struct Node));
	tail=head;
	for(i=0;i<n;i++)
	{
		temp=(Polynomial)malloc(sizeof(struct Node));
		scanf("%d%d",&(temp->Coefficient),&(temp->Exponent));
		temp->Next=NULL;
		tail->Next=temp;
		tail=temp;
	}
	return head;
}

void Print( Polynomial p )
{
	p=p->Next;
	if(p==NULL)
		return ;
	printf("%d %d",p->Coefficient,p->Exponent);
	p=p->Next;
	while(p!=NULL)
	{
		printf(" %d %d",p->Coefficient,p->Exponent);
		p=p->Next;
	}
	return ;
}

Polynomial Add( Polynomial a, Polynomial b )
{
	Polynomial head,temp,tail;
	head=(Polynomial)malloc(sizeof(struct Node));
	head->Coefficient=a->Coefficient;
	head->Exponent=a->Exponent;
	head->Next=NULL;
	tail=head;
	a=a->Next;
	b=b->Next;
	while(a!=NULL&&b!=NULL)
	{
		if(a->Exponent<b->Exponent)
		{
			temp=a;
			a=b;
			b=temp;
		}
		temp=(Polynomial)malloc(sizeof(struct Node));
		temp->Coefficient=a->Coefficient;
		temp->Exponent=a->Exponent;
		temp->Next=NULL;
		tail->Next=temp;
		tail=temp;
		if(b->Exponent==a->Exponent)
		{
			temp->Coefficient+=b->Coefficient;
			b=b->Next;
		}
		if(temp->Coefficient==0)
		{
			free(temp);
			tail->Next=NULL;
		}
		else
		{
			tail=temp;
		}
		a=a->Next;
	}
	if(a==NULL)
		a=b;
	while(a!=NULL)
	{
		temp=(Polynomial)malloc(sizeof(struct Node));
		temp->Coefficient=a->Coefficient;
		temp->Exponent=a->Exponent;
		temp->Next=NULL;
		tail->Next=temp;
		tail=temp;
	}
	return head;
}

int main()
{
    Polynomial a, b, s;
    a = Read();
    b = Read();
    s = Add(a, b);
    Print(s);
    return 0;
}
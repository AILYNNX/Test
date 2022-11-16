#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node *next;
}LNode;

LNode *CreateLinkList()
{
    LNode *head,*p,*q;
    int i,n;
    head=(LNode*)malloc(sizeof(LNode));
    head->next=NULL;
    p=head;
    q=p;
    scanf("%d",&n);

    for(i=1;i<=n;i++)
    {
        p=(LNode*)malloc(sizeof(LNode));
        scanf("%d",&p->data);
        p->next=NULL;
        q->next=p;
        q=p;
    }
    return head;

}

void Merge(LNode *La,LNode *Lb,LNode **Lc)
{
    LNode *p,*q,*s;
    p=La->next;
    q=Lb->next;
    *Lc=La;
    (*Lc)->next=NULL;
    free(Lb);

    while(p!=NULL&&q!=NULL)
    {
        if(p->data>q->data)
        {
            s=p;
            p=p->next;
        }

        else
        {
            s=q;
            q=q->next;
        }
        s->next=(*Lc)->next;
        (*Lc)->next=s;
    }

    if(p==NULL)
        p=q;

    while(p!=NULL)
    {
        s=p;
        p=p->next;
        s->next=(*Lc)->next;
        (*Lc)->next=s;
    }
}

void print(LNode *p)
{
    int first=1;
    p=p->next;
    while(p!=NULL)
    {
        if(first)
            first=0;

        else
            printf(",");
        printf("%d",p->data);
        p=p->next;

    }
    printf("\n");
}

int main()
{
    printf("���ǰ�����������ϲ��ĳ���\n");
    printf("���������ݱ�1��Ԫ�ظ������������������ݱ�1��Ԫ��ֵ��\n");
    printf("�����������ݱ�2��Ԫ�ظ������������������ݱ�2��Ԫ��ֵ��\n");
    printf("���ó��������ϲ����Ԫ��ֵ��\n");
    printf("���������롿\n"
           "\n"
           "   3       //���ݱ�1Ԫ�ظ���\n"
           "\n"
           "   22 21 19  //���ݱ�1��Ԫ��ֵ������\n"
           "\n"
           "   4         //���ݱ�2Ԫ�ظ���\n"
           "\n"
           "   92 91 31 2  //���ݱ�2��Ԫ��ֵ������\n");
    printf("�����������\n"
           "\n"
           "   The current List is:\n"
           "\n"
           "   2,19,21,22,31,91,92\n");
    printf("�뿪ʼ��\n");
    LNode *La,*Lb,*Lc;
    La=CreateLinkList();
    Lb=CreateLinkList();
    Merge(La,Lb,&Lc);
    printf("The current List is:\n");
    print(Lc);
}
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
    printf("这是包含有序链表合并的程序\n");
    printf("请输入数据表1的元素个数，按逆序输入数据表1的元素值；\n");
    printf("接着输入数据表2的元素个数，按逆序输入数据表2的元素值；\n");
    printf("最后该程序会输出合并后的元素值。\n");
    printf("【样例输入】\n"
           "\n"
           "   3       //数据表1元素个数\n"
           "\n"
           "   22 21 19  //数据表1的元素值（逆序）\n"
           "\n"
           "   4         //数据表2元素个数\n"
           "\n"
           "   92 91 31 2  //数据表2的元素值（逆序）\n");
    printf("【样例输出】\n"
           "\n"
           "   The current List is:\n"
           "\n"
           "   2,19,21,22,31,91,92\n");
    printf("请开始：\n");
    LNode *La,*Lb,*Lc;
    La=CreateLinkList();
    Lb=CreateLinkList();
    Merge(La,Lb,&Lc);
    printf("The current List is:\n");
    print(Lc);
}
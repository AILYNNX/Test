#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <Windows.h>
#include <iostream>
using namespace std;
#define LEN sizeof(struct node)
#define LEN1 sizeof(struct L_aim_node)
struct node
{
    int floor;
    int want_go;
    node *next;
};
//乘客节点
struct L_aim_node
{
    int n_floor;
    L_aim_node *next;
};
struct compare_distant
{
    int num;
    int distance;
} dist[4];
//距离比较
struct pessanger
{
    int request; //请求楼层
    int want_go; //目标楼层
    int state;   //状态，离开-1，处于请求楼层0，处于电梯内1
};
//乘客信息
struct Liftsign
{
    char state[5];
    char direction[3];
} Lsign_one, Lsign_two, Lsign_three, Lsign_four;
//电梯标志
struct Lift
{
    int number;    //电梯号
    int floor;     //楼层
    int state;     //状态 空闲0，运行1
    int direction; //行进方向，向上1，向下-1；
    int weight;    //电梯承重
} Lift_one, Lift_two, Lift_three, Lift_four;
//电梯信息
/*电梯一：可服务全部楼层，最大乘客数量10，最大载重量800kg
  电梯二：只服务单层，最大乘客数10，最大载重量800kg
  电梯三：只服务双层，最大乘客数量10，最大载重量800kg
  电梯四：可服务全部楼层，最大乘客数量20，最大载重量2000kg
*/
int sec = 0;
int first = 0, second = 0, third = 0, forth = 0;
node *Request_list = NULL;           //请求队列
L_aim_node *L_WG_one = NULL;         //电梯一目标楼层
L_aim_node *L_WG_two = NULL;         //电梯二目标楼层
L_aim_node *L_WG_three = NULL;       //电梯三目标楼层
L_aim_node *L_WG_four = NULL;        //电梯四目标楼层
L_aim_node *L_Request = NULL;        //乘客请求楼层
node *Tempointer_one = NULL;         //临时变量1
node *Tempointer_two = NULL;         //临时变量2
L_aim_node *Tempointer_three = NULL; //临时变量3
L_aim_node *Tempointer_five = NULL;  //临时变量5
L_aim_node *Tempointer_six = NULL;   //临时变量6
compare_distant Tempointer_four;     //临时变量4
//变量定义
void Initial()
{
    Lift_one.number = 1;
    Lift_one.floor = 15;
    Lift_one.state = 0;
    Lift_one.direction = 0;
    Lift_two.number = 2;
    Lift_two.floor = 11;
    Lift_two.state = 0;
    Lift_two.direction = 0;
    Lift_three.number = 3;
    Lift_three.floor = 6;
    Lift_three.state = 0;
    Lift_three.direction = 0;
    Lift_four.number = 4;
    Lift_four.floor = 1;
    Lift_four.state = 0;
    Lift_four.direction = 0;
    //电梯数值初始化
    strcpy_s(Lsign_one.state, "空闲");
    strcpy_s(Lsign_two.state, "空闲");
    strcpy_s(Lsign_three.state, "空闲");
    strcpy_s(Lsign_four.state, "空闲");
    strcpy_s(Lsign_one.direction, "无");
    strcpy_s(Lsign_two.direction, "无");
    strcpy_s(Lsign_three.direction, "无");
    strcpy_s(Lsign_four.direction, "无");
    //电梯标识初始化
}
//初始化函数
void print()
{
    printf("		-------------------------------------------------------------------------------      \n");
    printf("	    	                  电梯一          电梯二          电梯三          电梯四         \n");
    printf("		    所在楼层        %d              %d              %d               %d              \n", Lift_one.floor, Lift_two.floor, Lift_three.floor, Lift_four.floor);
    printf("		    使用状态       %s            %s            %s            %s                      \n", Lsign_one.state, Lsign_two.state, Lsign_three.state, Lsign_four.state);
    printf("		    运行方向       %s               %s              %s              %s               \n", Lsign_one.direction, Lsign_two.direction, Lsign_three.direction, Lsign_four.direction);
    printf("		                                                                                     \n");
    printf("		    乘客目标楼层                                                                     \n");
    printf("		    电梯一:");
    for (Tempointer_three = L_WG_one;; Tempointer_three = Tempointer_three->next)
    {
        if (Tempointer_three != NULL)
            printf("%d ", Tempointer_three->n_floor);
        else
        {
            printf("\n");
            break;
        }
    }

    printf("		    电梯二:");
    for (Tempointer_three = L_WG_two;; Tempointer_three = Tempointer_three->next)
    {
        if (Tempointer_three != NULL)
            printf("%d ", Tempointer_three->n_floor);
        else
        {
            printf("\n");
            break;
        }
    }
    printf("		    电梯三:");
    for (Tempointer_three = L_WG_three;; Tempointer_three = Tempointer_three->next)
    {
        if (Tempointer_three != NULL)
            printf("%d ", Tempointer_three->n_floor);
        else
        {
            printf("\n");
            break;
        }
    }
    printf("		    电梯四:");
    for (Tempointer_three = L_WG_four;; Tempointer_three = Tempointer_three->next)
    {
        if (Tempointer_three != NULL)
            printf("%d ", Tempointer_three->n_floor);
        else
        {
            printf("\n");
            break;
        }
    }
    printf("		                                                                                     \n");
    printf("		    乘客等待楼层:");
    for (Tempointer_one = Request_list;; Tempointer_one = Tempointer_one->next)
    {
        if (Tempointer_one != NULL)
            printf("%d ", Tempointer_one->floor);
        else
        {
            printf("\n");
            break;
        }
    }
    printf("		-------------------------------------------------------------------------------      \n");
}
//打印函数
void Delay()
{
    Sleep(2000);
    sec++;
}
//延时函数
void In()
{
    switch (sec)
    {
    case 2:
    {
        Tempointer_one = (struct node *)malloc(LEN);
        Tempointer_one->floor = 2;
        Tempointer_one->want_go = 16;
        Tempointer_one->next = NULL;
        if (Request_list == NULL)
        {
            Request_list = Tempointer_one;
        }
        else
        {
            for (Tempointer_two = Request_list;; Tempointer_two = Tempointer_two->next)
            {
                if (Tempointer_two->next == NULL)
                    break;
            }
            Tempointer_two->next = Tempointer_one;
        }
        break;
    }
    case 3:
    {
        Tempointer_one = (struct node *)malloc(LEN);
        Tempointer_one->floor = 4;
        Tempointer_one->want_go = 6;
        Tempointer_one->next = NULL;
        if (Request_list == NULL)
        {
            Request_list = Tempointer_one;
        }
        else
        {
            for (Tempointer_two = Request_list;; Tempointer_two = Tempointer_two->next)
            {
                if (Tempointer_two->next == NULL)
                    break;
            }
            Tempointer_two->next = Tempointer_one;
        }
        break;
    }
    case 5:
    {
        Tempointer_one = (struct node *)malloc(LEN);
        Tempointer_one->floor = 20;
        Tempointer_one->want_go = 1;
        Tempointer_one->next = NULL;
        if (Request_list == NULL)
        {
            Request_list = Tempointer_one;
        }
        else
        {
            for (Tempointer_two = Request_list;; Tempointer_two = Tempointer_two->next)
            {
                if (Tempointer_two->next == NULL)
                    break;
            }
            Tempointer_two->next = Tempointer_one;
        }
        break;
    }
    }
}
//此函数用于模拟实时用户请求输入
void move(int num, int aim)
{
    if (num == 1)
    {
        if (Lift_one.floor > aim)
            Lift_one.floor--;
        if (Lift_one.floor < aim)
            Lift_one.floor++;
    }
    if (num == 2)
    {
        if (Lift_two.floor > aim)
            Lift_two.floor--;
        if (Lift_two.floor < aim)
            Lift_two.floor++;
    }
    if (num == 3)
    {
        if (Lift_three.floor > aim)
            Lift_three.floor--;
        if (Lift_three.floor < aim)
            Lift_three.floor++;
    }
    if (num == 4)
    {
        if (Lift_four.floor > aim)
            Lift_four.floor--;
        if (Lift_four.floor < aim)
            Lift_four.floor++;
    }
}
//电梯基础移动函数
void homeing_one()
{
    if (Lift_one.state == 0)
        move(1, 15);
}
//电梯1空闲归位函数
void homeing_two()
{
    if (Lift_two.state == 0)
        move(2, 11);
}
//电梯2空闲归位函数
void homeing_three()
{
    if (Lift_three.state == 0)
        move(3, 6);
}
//电梯3空闲归位函数
void homeing_four()
{
    if (Lift_four.state == 0)
        move(4, 1);
}
//电梯4空闲归位函数
int Caldistance(int num, int floor)
{
    dist[0].distance = abs(Lift_one.floor - floor);
    dist[0].num = 1;
    dist[1].distance = abs(Lift_two.floor - floor);
    dist[1].num = 2;
    dist[2].distance = abs(Lift_three.floor - floor);
    dist[2].num = 3;
    dist[3].distance = abs(Lift_four.floor - floor);
    dist[3].num = 4;
    for (int i = 0; i < 4; i++)
    {
        for (int j = i; j < 4; j++)
        {
            if (dist[i].distance > dist[j].distance)
            {
                Tempointer_four = dist[i];
                dist[i] = dist[j];
                dist[j] = Tempointer_four;
            }
        }
    }
    return dist[num - 1].num;
}
//计算楼层与电梯的距离，返回num级别的距离，1最近，4最远
int judge(int lift_num, node *pasenger)
{
    int flag = 0;
    if (pasenger != NULL)
    {
        if (lift_num == 2 && pasenger->floor % 2 != 1 && pasenger->want_go % 2 != 1 || lift_num == 3 && pasenger->floor % 2 != 0 && pasenger->want_go % 2 != 0)
        {
            flag = 0;
        }
        else
        {
            if (lift_num == 1)
            {
                if (Lift_one.state == 0 || Lift_one.state == 1 && Lift_one.direction == -1 && pasenger->floor < Lift_one.floor && pasenger->want_go < Lift_one.floor && pasenger->floor > pasenger->want_go || Lift_one.state == 1 && Lift_one.direction == 1 && pasenger->floor > Lift_one.floor && pasenger->want_go > Lift_one.floor && pasenger->floor < pasenger->want_go)
                {
                    flag = 1;
                }
                else
                {
                    flag = 0;
                }
            }
            if (lift_num == 2)
            {
                if (Lift_two.state == 0 || Lift_two.state == 1 && Lift_two.direction == -1 && pasenger->floor < Lift_two.floor && pasenger->want_go < Lift_two.floor && pasenger->floor > pasenger->want_go || Lift_two.state == 1 && Lift_two.direction == 1 && pasenger->floor > Lift_two.floor && pasenger->want_go > Lift_two.floor && pasenger->floor < pasenger->want_go)
                {
                    flag = 1;
                }
                else
                {
                    flag = 0;
                }
            }
            if (lift_num == 3)
            {
                if (Lift_three.state == 0 || Lift_three.state == 1 && Lift_three.direction == -1 && pasenger->floor < Lift_three.floor && pasenger->want_go < Lift_three.floor && pasenger->floor > pasenger->want_go || Lift_three.state == 1 && Lift_three.direction == 1 && pasenger->floor > Lift_three.floor && pasenger->want_go > Lift_three.floor && pasenger->floor < pasenger->want_go)
                {
                    flag = 1;
                }
                else
                {
                    flag = 0;
                }
            }
            if (lift_num == 4)
            {
                if (Lift_four.state == 0 || Lift_four.state == 1 && Lift_four.direction == -1 && pasenger->floor < Lift_four.floor && pasenger->want_go < Lift_four.floor && pasenger->floor > pasenger->want_go || Lift_four.state == 1 && Lift_four.direction == 1 && pasenger->floor > Lift_four.floor && pasenger->want_go > Lift_four.floor && pasenger->floor < pasenger->want_go)
                {
                    flag = 1;
                }
                else
                {
                    flag = 0;
                }
            }
        }
    }
    else
    {
        flag = 0;
    }
    return flag;
}
//判断乘客能是否能乘坐相应电梯
void Lift_movements()
{
    if (Lift_one.state == 0)
        homeing_one();
    else if (Lift_one.state == 1)
    {
        if (L_WG_one != NULL)
        {
            move(1, L_WG_one->n_floor);
        }
    }
    if (Lift_two.state == 0)
        homeing_two();
    else if (Lift_two.state == 1)
    {
        if (L_WG_two != NULL)
        {
            move(2, L_WG_two->n_floor);
        }
    }
    if (Lift_three.state == 0)
        homeing_three();
    else if (Lift_three.state == 1)
    {
        if (L_WG_three != NULL)
        {
            move(3, L_WG_three->n_floor);
        }
    }
    if (Lift_four.state == 0)
        homeing_four();
    else if (Lift_four.state == 1)
    {
        if (L_WG_four != NULL)
        {
            move(4, L_WG_four->n_floor);
        }
    }
}
//电梯移动函数
void find_allocate(int num)
{
    if (num == 1)
    {
        if (L_WG_one == NULL)
        {
            Tempointer_three = (struct L_aim_node *)malloc(LEN1);
            Tempointer_three->n_floor = Request_list->floor;
            Tempointer_five = (struct L_aim_node *)malloc(LEN1);
            Tempointer_five->n_floor = Request_list->want_go;
            Tempointer_five->next = NULL;
            Tempointer_three->next = Tempointer_five;
            L_WG_one = Tempointer_three;
        }
        else
        {
            Tempointer_three = (struct L_aim_node *)malloc(LEN1);
            Tempointer_three->n_floor = Request_list->floor;
            Tempointer_five = (struct L_aim_node *)malloc(LEN1);
            Tempointer_five->n_floor = Request_list->want_go;
            for (Tempointer_six = L_WG_one;; Tempointer_six = Tempointer_six = Tempointer_six->next)
            {
                if (Tempointer_six->next == NULL || Tempointer_three->n_floor > Tempointer_six->next->n_floor)
                {
                    Tempointer_three->next = Tempointer_six->next;
                    Tempointer_six->next = Tempointer_three;
                    break;
                }
            }
            for (Tempointer_six = L_WG_one;; Tempointer_six = Tempointer_six = Tempointer_six->next)
            {
                if (Tempointer_six->next == NULL || Tempointer_three->n_floor > Tempointer_six->next->n_floor)
                {
                    Tempointer_five->next = Tempointer_six->next;
                    Tempointer_six->next = Tempointer_five;
                    break;
                }
            }
        }
    }
    if (num == 2)
    {
        if (L_WG_two == NULL)
        {
            Tempointer_three = (struct L_aim_node *)malloc(LEN1);
            Tempointer_three->n_floor = Request_list->floor;
            Tempointer_five = (struct L_aim_node *)malloc(LEN1);
            Tempointer_five->n_floor = Request_list->want_go;
            Tempointer_five->next = NULL;
            Tempointer_three->next = Tempointer_five;
            L_WG_two = Tempointer_three;
        }
        else
        {
            Tempointer_three = (struct L_aim_node *)malloc(LEN1);
            Tempointer_three->n_floor = Request_list->floor;
            Tempointer_five = (struct L_aim_node *)malloc(LEN1);
            Tempointer_five->n_floor = Request_list->want_go;
            for (Tempointer_six = L_WG_two;; Tempointer_six = Tempointer_six = Tempointer_six->next)
            {
                if (Tempointer_six->next == NULL || Tempointer_three->n_floor > Tempointer_six->next->n_floor)
                {
                    Tempointer_three->next = Tempointer_six->next;
                    Tempointer_six->next = Tempointer_three;
                    break;
                }
            }
            for (Tempointer_six = L_WG_two;; Tempointer_six = Tempointer_six = Tempointer_six->next)
            {
                if (Tempointer_six->next == NULL || Tempointer_three->n_floor > Tempointer_six->next->n_floor)
                {
                    Tempointer_five->next = Tempointer_six->next;
                    Tempointer_six->next = Tempointer_five;
                    break;
                }
            }
        }
    }
    if (num == 3)
    {
        if (L_WG_three == NULL)
        {
            Tempointer_three = (struct L_aim_node *)malloc(LEN1);
            Tempointer_three->n_floor = Request_list->floor;
            Tempointer_five = (struct L_aim_node *)malloc(LEN1);
            Tempointer_five->n_floor = Request_list->want_go;
            Tempointer_five->next = NULL;
            Tempointer_three->next = Tempointer_five;
            L_WG_three = Tempointer_three;
        }
        else
        {
            Tempointer_three = (struct L_aim_node *)malloc(LEN1);
            Tempointer_three->n_floor = Request_list->floor;
            Tempointer_five = (struct L_aim_node *)malloc(LEN1);
            Tempointer_five->n_floor = Request_list->want_go;
            for (Tempointer_six = L_WG_three;; Tempointer_six = Tempointer_six = Tempointer_six->next)
            {
                if (Tempointer_six->next == NULL || Tempointer_three->n_floor > Tempointer_six->next->n_floor)
                {
                    Tempointer_three->next = Tempointer_six->next;
                    Tempointer_six->next = Tempointer_three;
                    break;
                }
            }
            for (Tempointer_six = L_WG_three;; Tempointer_six = Tempointer_six = Tempointer_six->next)
            {
                if (Tempointer_six->next == NULL || Tempointer_three->n_floor > Tempointer_six->next->n_floor)
                {
                    Tempointer_five->next = Tempointer_six->next;
                    Tempointer_six->next = Tempointer_five;
                    break;
                }
            }
        }
    }
    if (num == 4)
    {
        if (L_WG_four == NULL)
        {
            Tempointer_three = (struct L_aim_node *)malloc(LEN1);
            Tempointer_three->n_floor = Request_list->floor;
            Tempointer_five = (struct L_aim_node *)malloc(LEN1);
            Tempointer_five->n_floor = Request_list->want_go;
            Tempointer_five->next = NULL;
            Tempointer_three->next = Tempointer_five;
            L_WG_four = Tempointer_three;
        }
        else
        {
            Tempointer_three = (struct L_aim_node *)malloc(LEN1);
            Tempointer_three->n_floor = Request_list->floor;
            Tempointer_five = (struct L_aim_node *)malloc(LEN1);
            Tempointer_five->n_floor = Request_list->want_go;
            for (Tempointer_six = L_WG_four;; Tempointer_six = Tempointer_six = Tempointer_six->next)
            {
                if (Tempointer_six->next == NULL && Lift_four.direction == 1 || Tempointer_three->n_floor < Tempointer_six->next->n_floor && Lift_four.direction == 1)
                {
                    Tempointer_three->next = Tempointer_six->next;
                    Tempointer_six->next = Tempointer_three;
                    break;
                }
                if (Tempointer_six->next == NULL && Lift_four.direction == -1 || Tempointer_three->n_floor > Tempointer_six->next->n_floor && Lift_four.direction == -1)
                {
                    Tempointer_three->next = Tempointer_six->next;
                    Tempointer_six->next = Tempointer_three;
                    break;
                }
            }
            for (Tempointer_six = L_WG_four;; Tempointer_six = Tempointer_six = Tempointer_six->next)
            {
                if (Tempointer_six->next == NULL && Lift_four.direction == 1 || Tempointer_five->n_floor < Tempointer_six->next->n_floor && Lift_four.direction == 1)
                {
                    Tempointer_five->next = Tempointer_six->next;
                    Tempointer_six->next = Tempointer_five;
                    break;
                }
                if (Tempointer_six->next == NULL && Lift_four.direction == -1 || Tempointer_five->n_floor > Tempointer_six->next->n_floor && Lift_four.direction == -1)
                {
                    Tempointer_five->next = Tempointer_six->next;
                    Tempointer_six->next = Tempointer_five;
                    break;
                }
            }
        }
    }
}
//寻找分配函数
void already_allocate(int num)
{
    if (num == 1)
    {
        find_allocate(1);
        Request_list = Request_list->next;
    }
    if (num == 2)
    {
        find_allocate(2);
        Request_list = Request_list->next;
    }
    if (num == 3)
    {
        find_allocate(3);
        Request_list = Request_list->next;
    }
    if (num == 4)
    {
        find_allocate(4);
        Request_list = Request_list->next;
    }
}
//将乘客分配给对应电梯，并将此乘客从申请列表中删除
void allocate()
{
    if (Request_list != NULL)
    {
        first = Caldistance(1, Request_list->floor);
        if (judge(first, Request_list))
        {
            already_allocate(first);
        }
        else
        {
            second = Caldistance(2, Request_list->floor);
            if (judge(second, Request_list))
            {
                already_allocate(second);
            }
            else
            {
                third = Caldistance(3, Request_list->floor);
                if (judge(third, Request_list))
                {
                    already_allocate(third);
                }
                else
                {
                    forth = Caldistance(4, Request_list->floor);
                    if (judge(forth, Request_list))
                    {
                        already_allocate(forth);
                    }
                    else
                    {
                        return;
                    }
                }
            }
        }
    }
    else
    {
        return;
    }
}
//分配函数
void fresh()
{
    if (L_WG_one != NULL)
    {
        Lift_one.state = 1;
        strcpy_s(Lsign_one.state, "运行");
        if (Lift_one.floor < L_WG_one->n_floor)
        {
            Lift_one.direction = 1;
            strcpy_s(Lsign_one.direction, "上");
        }
        else if (Lift_one.floor > L_WG_one->n_floor)
        {
            Lift_one.direction = -1;
            strcpy_s(Lsign_one.direction, "下");
        }
        else
            L_WG_one = L_WG_one->next;
    }
    else
    {
        Lift_one.state = 0;
        strcpy_s(Lsign_one.state, "空闲");
        if (Lift_one.floor < 15)
        {
            Lift_one.direction = 1;
            strcpy_s(Lsign_one.direction, "上");
        }
        else if (Lift_one.floor > 15)
        {
            Lift_one.direction = -1;
            strcpy_s(Lsign_one.direction, "下");
        }
        else
        {
            Lift_one.direction = 0;
            strcpy_s(Lsign_one.direction, "无");
        }
    }
    if (L_WG_two != NULL)
    {
        Lift_two.state = 1;
        strcpy_s(Lsign_two.state, "运行");
        if (Lift_two.floor < L_WG_two->n_floor)
        {
            Lift_two.direction = 1;
            strcpy_s(Lsign_two.direction, "上");
        }
        else if (Lift_two.floor > L_WG_two->n_floor)
        {
            Lift_two.direction = -1;
            strcpy_s(Lsign_two.direction, "下");
        }
        else
            L_WG_two = L_WG_two->next;
    }
    else
    {
        Lift_two.state = 0;
        strcpy_s(Lsign_two.state, "空闲");
        if (Lift_two.floor < 11)
        {
            Lift_two.direction = 1;
            strcpy_s(Lsign_two.direction, "上");
        }
        else if (Lift_two.floor > 11)
        {
            Lift_two.direction = -1;
            strcpy_s(Lsign_two.direction, "下");
        }
        else
        {
            Lift_two.direction = 0;
            strcpy_s(Lsign_two.direction, "无");
        }
    }
    if (L_WG_three != NULL)
    {
        Lift_three.state = 1;
        strcpy_s(Lsign_three.state, "运行");
        if (Lift_three.floor < L_WG_three->n_floor)
        {
            Lift_three.direction = 1;
            strcpy_s(Lsign_three.direction, "上");
        }
        else if (Lift_three.floor > L_WG_three->n_floor)
        {
            Lift_three.direction = -1;
            strcpy_s(Lsign_three.direction, "下");
        }
        else
            L_WG_three = L_WG_three->next;
    }
    else
    {
        Lift_three.state = 0;
        strcpy_s(Lsign_three.state, "空闲");
        if (Lift_three.floor < 6)
        {
            Lift_three.direction = 1;
            strcpy_s(Lsign_three.direction, "上");
        }
        else if (Lift_three.floor > 6)
        {
            Lift_three.direction = -1;
            strcpy_s(Lsign_three.direction, "下");
        }
        else
        {
            Lift_three.direction = 0;
            strcpy_s(Lsign_three.direction, "无");
        }
    }
    if (L_WG_four != NULL)
    {
        Lift_four.state = 1;
        strcpy_s(Lsign_four.state, "运行");
        if (Lift_four.floor < L_WG_four->n_floor)
        {
            Lift_four.direction = 1;
            strcpy_s(Lsign_four.direction, "上");
        }
        else if (Lift_four.floor > L_WG_four->n_floor)
        {
            Lift_four.direction = -1;
            strcpy_s(Lsign_four.direction, "下");
        }
        else
            L_WG_four = L_WG_four->next;
    }
    else
    {
        Lift_four.state = 0;
        strcpy_s(Lsign_four.state, "空闲");
        if (Lift_four.floor < 1)
        {
            Lift_four.direction = 1;
            strcpy_s(Lsign_four.direction, "上");
        }
        else if (Lift_four.floor > 1)
        {
            Lift_four.direction = -1;
            strcpy_s(Lsign_four.direction, "下");
        }
        else
        {
            Lift_four.direction = 0;
            strcpy_s(Lsign_four.direction, "无");
        }
    }
}
void clearscreen()
{
    system("cls");
}
//清屏函数
int main(void)
{
    Initial();
    while (1)
    {
        In();
        allocate();
        fresh();
        Lift_movements();
        print();
        Delay();
        clearscreen();
    }
}

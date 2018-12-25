#include "rectangle.h"

// 蛇的身体
struct snakebody{
    int positionx;
    int positiony;
    Rectangle rect;
    struct snakebody *next;
};

class Snake
{
private:
    // 蛇的朝向,第一个元素为正右负左, 第二个元素为正下负上
    int toward[2];

public:
    // 蛇的脑袋(头指针)
    struct snakebody *head;

    // 构造函数
    Snake(int x, int y):
        toward{0,1}
    {
        // 蛇尾巴
        struct snakebody *tail;
        tail=(struct snakebody *)malloc(sizeof *tail);
        tail->positionx=x;
        tail->positiony=y-2;
        tail->next=NULL;
        tail->rect=Rectangle(1,1,0,1,0);
        // 蛇身体
        struct snakebody *body;
        body=(struct snakebody *)malloc(sizeof *body);
        body->positionx=x;
        body->positiony=y-1;
        body->next=tail;
        body->rect=Rectangle(1,1,0,1,0);
        // 蛇脑袋
        head=(struct snakebody *)malloc(sizeof *head);
        head->positionx=x;
        head->positiony=y;
        head->next=body;
        head->rect=Rectangle(1,1,1,0,0);
    }
    
    // 画蛇添足
    // 这么写是错的, 应该把移动和绘制分开来
    void move(int mode)
    {
        struct snakebody *iter;
        if(mode==0)
        {
            // 如果没有吃到豆豆, 那可如何是好
            struct snakebody *tail;
            iter=head;
            while(1)
            {
                if(iter->next->next==NULL)
                {
                    tail=iter->next;
                    iter->next=NULL;
                    break;
                }
                iter=iter->next;
            }
            tail->next=head->next;
            tail->positionx=head->positionx;
            tail->positiony=head->positiony;

            head->next=tail;
            head->positionx+=toward[0];
            head->positiony+=toward[1];
        }
        else if(mode==1)
        {
            // 豆豆吃多了会长胖的
            struct snakebody *body;
            body=(struct snakebody *)malloc(sizeof *body);
            body->positionx=head->positionx;
            body->positiony=head->positiony;
            body->next=head->next;
            body->rect=Rectangle(1,1,0,1,0);
            
            head->next=body;
            head->positionx+=toward[0];
            head->positiony+=toward[1];
        }
    }

    // 绘制
    void draw()
    {
        struct snakebody *iter;
        for(iter=head; iter; iter=iter->next)
        {
            iter->rect.setposition(iter->positionx,iter->positiony);
            iter->rect.draw();
        }
    }

    // 吃豆豆
    int eat(int foodx, int foody)
    {
        if(head->positionx+toward[0]==foodx && head->positiony+toward[1]==foody)
            return 1;
        else
            return 0;
    }

    // 控制方向
    void control(int wasd)
    {
        switch (wasd)
        {
            // 上
            case 0:
                if(toward[1]==0)
                {
                    toward[0]=0;
                    toward[1]=-1;
                }
                break;
            // 左
            case 1:
                if(toward[0]==0)
                {
                    toward[1]=0;
                    toward[0]=-1;
                }
                break;
            // 下
            case 2:
                if(toward[1]==0)
                {
                    toward[0]=0;
                    toward[1]=1;
                }
                break;
            // 右
            case 3:
                if(toward[0]==0)
                {
                    toward[1]=0;
                    toward[0]=1;
                }
                break;
            default:
                break;
        }
    }

    // 判断碰撞
    // 之后再写
};
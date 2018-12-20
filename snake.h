#include "rectangle.h"

// 蛇的身体
struct snakebody{
    struct snakebody *prev;
    int positionx;
    int positiony;
    struct snakebody *next;
};

class Snake
{
private:
    // 蛇的脑袋(头指针)
    struct snakebody *head;
    // 蛇的尾巴(尾指针)
    struct snakebody *tail;
    // 蛇的朝向,第一个元素为正右负左, 第二个元素为正下负上
    int toward[2];
public:
    // 构造函数
    Snake(int x, int y)
    {
        struct snakebody *
    }
    // 蛇的移动
    void move()
    {
        // 首先蛇脑袋
    }
};
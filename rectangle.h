#ifndef RECT_H
#define RECT_H

#include "shader.h"
#include <glad/glad.h>

// 这个头文件声明了一个矩形类, 它调用Shader类的方法来生成一个矩形
// 这个矩形的高和宽, 颜色在初始化时指定, 之后不能再改变
// 这个矩形的位置可以通过uniform变量来指定, 所以是可变的
// 默认的位置坐标为(0, 0), 即中心点位置
class Rectangle
{
private:
    Shader shader;  // 着色器程序
    unsigned int VAO, VBO, EBO; //绑定的各种缓冲区

public:

    int positionx, positiony;

    Rectangle(int width, int height, float r, float g, float b):
        positionx(0),
        positiony(0),
        shader("./rect.vs", "./rect.fs")
    {
        // 默认已知窗口的大小为800*600, 不然还要获取, 太麻烦了.
        // 以20px为一个单位长度. 
        // 浮点数精度就不管了. 我看还行. 
        // 可能会产生一些偏差. 
        float w = width* 0.0500f;
        float h = height*0.0666f;

        // 设置4个顶点的坐标
        float vert[] = {
            // 坐标     颜色
            w, 0,       r, g, b,    // 右上
            w, -h,      r, g, b,    // 右下
            0, -h,      r, g, b,    // 左下
            0, 0,       r, g, b    // 左上
        };

        // 设置绘制顶点的索引
        unsigned int indi[] = {
            0, 1, 3, 
            1, 2, 3
        };

        // 分别创建VAO, VBO, EBO
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        // 绑定VAO, 之后对VBO和EBO的配置都会储存在这个VAO中
        // 一个VAO可以用来管理多个物体, 这里只管理一个, 可以进行优化 
        // 之后可以考虑把这个分离出来
        glBindVertexArray(VAO);

        // 绑定EBO到缓冲类型上, 然后将索引数据从内存复制到显卡内存中
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indi), indi, GL_STREAM_DRAW);

        // 绑定VBO到缓冲类型上, 然后将顶点数据从内存复制到显卡内存中
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vert), vert, GL_STREAM_DRAW);

        // 链接顶点属性
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 
            5 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
            5 * sizeof(float), (void *)(2 * sizeof(float)));
        glEnableVertexAttribArray(1);

        // 解绑VAO, EBO, 在之后使用
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    // 绘制矩阵
    void draw()
    {
        shader.use();
        shader.setFloat("ourX",positionx*0.0500f - 1);
        shader.setFloat("ourY",1 - positiony*0.0666f);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }

    // 设置位置
    void setposition(int x, int y)
    {
        positionx = x;
        positiony = y;
    }

    void clear()
    {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
    }
};

#endif
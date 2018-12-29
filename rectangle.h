#ifndef RECT_H
#define RECT_H

#include "shader.h"
#include <glad/glad.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// 这个头文件声明了一个矩形类, 它调用Shader类的方法来生成一个矩形
// 这个矩形的高和宽, 颜色在初始化时指定, 之后不能再改变
// 这个矩形的位置可以通过uniform变量来指定, 所以是可变的
// 默认的位置坐标为(0, 0), 即中心点位置
class Rectangle
{
private:
    Shader shader;  // 着色器程序
    unsigned int VAO, VBO, EBO; // 绑定的各种缓冲区
    unsigned int texture1, texture2; // 纹理ID, 最多两个 

public:
    int positionx, positiony;
    // 不传递纹理, 而是传递颜色的情况
    // 比较不常用
    Rectangle(int width, int height, float r, float g, float b):
        positionx(0),
        positiony(0),
        texture1(0),
        texture2(0),
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
            w, 0,       r, g, b, 
            w, -h,      r, g, b, 
            0, -h,      r, g, b, 
            0, 0,       r, g, b
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

    // 当载入一个纹理贴图时, 所使用的着色器又有些不同
    Rectangle(int width, int height, const char *image):
        positionx(0),
        positiony(0),
        texture2(0),
        shader("./rect1.vs", "./rect1.fs")
    {
        // 首先, 读入纹理
        int imgw, imgh, nrChannels;
        stbi_set_flip_vertically_on_load(true);
        unsigned char *data = stbi_load(image, &imgw, &imgh, &nrChannels, 0);
        // 生成纹理ID, 并绑定
        glGenTextures(1, &texture1);
        glBindTexture(GL_TEXTURE_2D, texture1);
        // 为纹理设置环绕过滤方式
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);   
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // 使用图片数据来生成纹理, 注意只能是PNG格式的数据
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imgw, imgh, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        // 自動生成多級漸遠紋理
        glGenerateMipmap(GL_TEXTURE_2D);
        // 釋放圖像數據
        stbi_image_free(data);
        // 设置纹理
        shader.use();
        shader.setInt("texture1", 0);

        // 默认已知窗口的大小为800*600, 不然还要获取, 太麻烦了.
        // 以20px为一个单位长度. 
        // 浮点数精度就不管了. 我看还行. 
        // 可能会产生一些偏差. 
        float w = width* 0.0500f;
        float h = height*0.0666f;

        // 设置4个顶点的坐标
        float vert[] = {
            // 坐标   纹理坐标
            w, 0,     1, 1, // 右上
            w, -h,    1, 0, // 右下
            0, -h,    0, 0, // 左下
            0, 0,     0, 1  // 左上
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
            4 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,
            4 * sizeof(float), (void *)(2 * sizeof(float)));
        glEnableVertexAttribArray(1);

        // 解绑VAO, EBO, 在之后使用
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    // 绘制矩阵
    void draw()
    {
        if(texture1)
        {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texture1);
        }
        if(texture2)
        {
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, texture2);
        }
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
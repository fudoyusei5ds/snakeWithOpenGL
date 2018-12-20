#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <math.h>

#include "rectangle.h"

// 按ESC键退出程序
void processInput(GLFWwindow *window);

int main()
{
    // 初始化
    glfwInit();
    // 設置glfw所使用的OpenGL的版本
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // 設置glfw使用OpenGL的一個子集以及啓用OpenGL的核心模式
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // 創建窗體
    GLFWwindow* window = glfwCreateWindow(800, 600, "SnakeWithOpenGL", NULL, NULL);
    // 如果創建失敗, 輸出錯誤信息並釋放資源
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    // 設置窗體上下文爲線程主上下文
    glfwMakeContextCurrent(window);

    // 初始化glad, 用於返回OpenGL函數的地址
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // 設置窗體維度
    glViewport(0, 0, 800, 600);

    /****************************************************************/
    // 创建一个背景板, 宽度为40, 高度为30, 正好覆盖
    // 坐标系原点位于左上角
    // 误差在一个像素左右
    Rectangle background = Rectangle(40, 30, 0.3f, 0.5f, 0.2f);
    background.setposition(0, 0);

    // 绘制蛇


    /****************************************************************/

    // 开始窗体绘制循环
    while(!glfwWindowShouldClose(window))
    {
        // 接收輸入
        processInput(window);  

        // 設置顏色
        glClearColor(0.0f, 0.2f, 0.2f, 1.0f);
        // 清除顏色緩衝區, 並使用上面設置的顏色進行填充 
        glClear(GL_COLOR_BUFFER_BIT);

        // 绘制背景板
        background.draw();

        // 交換緩衝, 繪制屏幕
        glfwSwapBuffers(window);
        // 檢查觸發事件, 調整窗體狀態
        glfwPollEvents(); 
    }

    background.clear();

    // 最後釋放資源
    glfwTerminate();

    return 0;
}

void processInput(GLFWwindow *window)
{
    // 按下esc, 發出窗體退出信號
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
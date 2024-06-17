#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <simpletext.h>
#include <iostream>

class App
{
public:
    App();

    void setup();
    void update();
    void conversion(double &xpos, double &ypos);
    void pause_menu();

    // GLFW callbacks binding
    void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
    void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);
    void scroll_callback(double xoffset, double yoffset);
    void cursor_position_callback(GLFWwindow *window, double xpos, double ypos);
    void size_callback(int width, int height);

private:
    void render();

    int _width{};
    int _height{};
    double _previousTime{};
    float _viewSize{};

    // Add your variables here
    GLuint _texture{};
    GLuint _texturecover{};
    GLuint _currentTexture{};
    float _angle{};

    SimpleText TextRenderer{};
};
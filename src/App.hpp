#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <simpletext.h>
#include <iostream>
#include <unordered_map>

enum class TileType
{
    Path,
    Input,
    Output,
    Empty
};

class App
{
public:
    App();

    void setup();
    void update();
    void conversion(double &xpos, double &ypos);
    void bouton_jouer();
    void bouton_rejouer();
    void bouton_continuer();
    void bouton_pause();
    void pause_menu();
    bool _boutonJouerClicked = false;
    bool _boutonRejouerCliked = false;
    bool _boutonContinuerCliked = false;
    bool _pauseClicked = false;
    bool _uptoplay = false;
    std::vector<TileType> _liste;

    // GLFW callbacks binding
    void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
    void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);
    void scroll_callback(double xoffset, double yoffset);
    void cursor_position_callback(GLFWwindow *window, double xpos, double ypos);
    void size_callback(int width, int height);

    GLuint _texturevide{};
    GLuint _texturepath{};
    GLuint _textureinput{};
    GLuint _textureoutput{};

private:
    void render();

    int _width{};
    int _height{};
    double _previousTime{};
    bool _isPaused{};
    // double _elapsedTime{};
    float _viewSize{};

    // Add your variables here
    GLuint _texture{};
    GLuint _texturecover{};
    GLuint _currentTexture{};
    float _angle{};

    std::unordered_map<TileType, GLuint> _tile_texture_mapping{};

    SimpleText TextRenderer{};
};
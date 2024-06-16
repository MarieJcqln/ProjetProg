#include "App.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <img/img.hpp>

#include <sstream>
#include <fstream>
#include <string>

#include "simpletext.h"
#include "utils.hpp"
#include "GLHelpers.hpp"

App::App() : _previousTime(0.0), _viewSize(2.0)
{
    // load what needs to be loaded here (for example textures)

    img::Image test{img::load(make_absolute_path("images/map.png", true), 3, true)};

    test.data();
    //load charge à partir de en haut à gauche

    _texture = loadTexture(test);
}

void App::setup()
{
    // Set the clear color to a nice blue
    glClearColor(0.0f, 0.0f, 0.4f, 1.0f);

    // Setup the text renderer with blending enabled and white text color
    TextRenderer.ResetFont();
    TextRenderer.SetColor(SimpleText::TEXT_COLOR, SimpleText::Color::WHITE);
    TextRenderer.SetColorf(SimpleText::BACKGROUND_COLOR, 0.f, 0.f, 0.f, 0.f);
    TextRenderer.EnableBlending(true);
}

void App::update()
{

    const double currentTime{glfwGetTime()};
    const double elapsedTime{currentTime - _previousTime};
    _previousTime = currentTime;

    //_angle += 10.0f * elapsedTime;
    // _angle = std::fmod(_angle, 360.0f);

    render();
}

void App::render()
{
    //CARRE ROUGE DERRIERE LA MAP QUI TOURNE
    // Clear the color and depth buffers of the frame buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // render exemple quad
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(-0.5f, -0.5f);
    glVertex2f(0.5f, -0.5f);
    glVertex2f(0.5f, 0.5f);
    glVertex2f(-0.5f, 0.5f);
    glEnd();

    //MAP QUI TOURNE
    glPushMatrix();
    glScalef(0.8f, 0.8f, 0.8f);
    glRotatef(_angle, 0.0f, 0.0f, 1.0f); //SERT POUR LA ROTATION
    draw_quad_with_texture(_texture);
    glPopMatrix();
    //COVER
    img::Image cover;
    cover.loadFromFile("chemin/vers/votre/image.png");
    GLuint textureID = loadTexture(cover);
    draw_quad_with_texture(cover);

    TextRenderer.Label("Example of using SimpleText library", _width / 2, 20, SimpleText::CENTER);
    TextRenderer.Label("JOUER", _width / 2, 20, SimpleText::CENTER);

    // Without set precision
    // const std::string angle_label_text { "Angle: " + std::to_string(_angle) };
    // With c++20 you can use std::format
    // const std::string angle_label_text { std::format("Angle: {:.2f}", _angle) };

    // Using stringstream to format the string with fixed precision
    std::string angle_label_text{};
    std::stringstream stream{};
    //stream << std::fixed << "Angle: " << std::setprecision(2) << _angle;
    angle_label_text = stream.str();

    TextRenderer.Label(angle_label_text.c_str(), _width / 2, _height - 4, SimpleText::CENTER);

    TextRenderer.Render();
}

///// CODE AJOUTE 3)2)//////
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
////// FIN CODE AJOUTE 3)2///////
//void App::key_callback(int key, int scancode, int action, int mods)
{
    // std::cout << key << std::endl; //pour voir si on capte bien que je touche une touche
    if (key == GLFW_KEY_A && action == GLFW_PRESS)   //on met A car en querty A=Q
        glfwSetWindowShouldClose(window, GLFW_TRUE); //GLFW_TRUE ou 1 fonctionne
    //SI P => pause
    //SI fleche du haut : aller en haut
    //SI fleche du bas : aller en bas
    //SI fleche de droite : aller en droite
    //SI fleche de gauche : aller en gauche
}

void App::pause_menu()
{ /* 
    glClearColor(0.0, 0.0, 0.0, 0.5); // on ajoute un filtre noir transparent
                                      // std::cout << "Cursor Position at (" << xpos << " : " << ypos << ")" << std::endl;
    //ADD TEXT*/
}
void App::mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{
    double xpos, ypos;
    //getting cursor position
    glfwGetCursorPos(window, &xpos, &ypos);
    //cursor_position_callback
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS && xpos == 1.0 && ypos == 0.0) //si appuye sur bouton pause
    {
        pause_menu();
    }
}

//FROM TD1 ex3
// void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
// {}
void App::scroll_callback(double /*xoffset*/, double /*yoffset*/)
{
}

//pour utiliser la couche alpha
//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//glEnable(GL_BLEND);
void App::cursor_position_callback(GLFWwindow *window, double xpos, double ypos)
{ //getting cursor position
    glfwGetCursorPos(window, &xpos, &ypos);

    // if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    // {
    // }
}

void App::size_callback(int width, int height)
{
    _width = width;
    _height = height;

    // make sure the viewport matches the new window dimensions
    glViewport(0, 0, _width, _height);

    const float aspectRatio{_width / (float)_height};

    // Change the projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (aspectRatio > 1.0f)
    {
        glOrtho(-_viewSize / 2.0f * aspectRatio, _viewSize / 2.0f * aspectRatio, -_viewSize / 2.0f, _viewSize / 2.0f, -1.0f, 1.0f);
    }
    else
    {
        glOrtho(-_viewSize / 2.0f, _viewSize / 2.0f, -_viewSize / 2.0f / aspectRatio, _viewSize / 2.0f / aspectRatio, -1.0f, 1.0f);
    }
}

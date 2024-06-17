#include "App.hpp"
#include "Draw.cpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <img/img.hpp>

#include <sstream>
#include <fstream>
#include <string>

#include "simpletext.h"
#include "utils.hpp"
#include "GLHelpers.hpp"

//pour utiliser la couche alpha
// #include <GL/glut.h>

// glEnable(GL_BLEND);
// glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

App::App() : _previousTime(0.0), _viewSize(2.0)
{
    // load what needs to be loaded here (for example textures)
    ///////////////mis dans la fonction onclick mouse
    //MAP
    img::Image map{img::load(make_absolute_path("images/map.png", true), 3, true)};
    //COVER
    img::Image cover{img::load(make_absolute_path("images/cover_game_pixel.png", true), 3, true)};

    img::Image vide{img::load(make_absolute_path("images/sable_pixel.png", true), 3, true)};
    img::Image path{img::load(make_absolute_path("images/mer_pixel.png", true), 3, true)};
    img::Image input{img::load(make_absolute_path("images/bouee_pixel.png", true), 3, true)};
    img::Image output{img::load(make_absolute_path("images/nageuse_arrivee.png", true), 3, true)};

    // _texture = loadTexture(test);
    //////////////////////////////
    // Création de la liste de case

    // std::vector<TileType> list_tiles = create_list_tiles(map.data(), map.data_size());

    //load charge à partir de en haut à gauche
    //MAP
    _texture = loadTexture(map);
    _texturevide = loadTexture(vide);
    _texturepath = loadTexture(path);
    _textureinput = loadTexture(input);
    _textureoutput = loadTexture(output);

    _tile_texture_mapping.insert({TileType::Path , _texturepath});
    _tile_texture_mapping.insert({TileType::Input , _textureinput});
    _tile_texture_mapping.insert({TileType::Output , _textureoutput});
    _tile_texture_mapping.insert({TileType::Empty, _texturevide});
    
    //COVER
    _texturecover = loadTexture(cover);
    _currentTexture = _texture;
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
    // glPushMatrix();
    // glScalef(0.8f, 0.8f, 0.8f);
    // glRotatef(_angle, 0.0f, 0.0f, 1.0f); //SERT POUR LA ROTATION
    // draw_quad_with_texture(_texture);
    // glPopMatrix();
    //COVER
    glPushMatrix();
    glScalef(1.0f, 1.0f, 1.0f);
    draw_quad_with_texture(_texturecover);
    glPopMatrix();

    TextRenderer.Label("BITCHARK", _width / 2, _height / 3, SimpleText::CENTER);
    // render exemple quad
    glColor4f(1.0f, 0.0f, 0.0f, 0.5f);
    glBegin(GL_QUADS);
    glVertex2f(-0.3f, -0.25f);
    glVertex2f(0.3f, -0.25f);
    glVertex2f(0.3f, -0.15f);
    glVertex2f(-0.3f, -0.15f);
    glEnd();
    TextRenderer.Label("JOUER", _width / 2, 3.7 * _height / 6, SimpleText::CENTER);

    // Without set precision
    const std::string angle_label_text{"Angle: " + std::to_string(_angle)};
    // With c++20 you can use std::format
    // const std::string angle_label_text { std::format("Angle: {:.2f}", _angle) };

    // Using stringstream to format the string with fixed precision
    // std::string angle_label_text{};
    // std::stringstream stream{};
    // stream << std::fixed << "Angle: " << std::setprecision(2) << _angle;
    // angle_label_text = stream.str();

    TextRenderer.Label(angle_label_text.c_str(), _width / 2, _height - 4, SimpleText::CENTER);

    TextRenderer.Render();
}

void App::pause_menu()
{
    glClearColor(0.0, 0.0, 0.0, 0.5); // on ajoute un filtre noir transparent
    TextRenderer.Label("PARTIE EN PAUSE", _width / 2, 20, SimpleText::CENTER);
}

static const float GL_VIEW_SIZE = 2.0f;

void App::conversion(double &xpos, double &ypos)
{
    xpos = ((xpos - (_width / 2)) * GL_VIEW_SIZE / _height);
    ypos = -((ypos - (_height / 2)) * GL_VIEW_SIZE / _height);
}

///// CODE AJOUTE 3)2)//////
void App::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
////// FIN CODE AJOUTE 3)2///////
{
    // std::cout << key << std::endl; //pour voir si on capte bien que je touche une touche
    if (key == GLFW_KEY_A && action == GLFW_PRESS)
    { //on met A car en querty A=Q

        // void glfwSetWindowShouldClose(GLFWwindow * window, int value);
        glfwSetWindowShouldClose(window, GLFW_TRUE); //GLFW_TRUE ou 1 fonctionne
    }
    if (key == GLFW_KEY_P && action == GLFW_PRESS)
    { //on met A car en querty A=Q

        // void glfwSetWindowShouldClose(GLFWwindow * window, int value);
        pause_menu(); //GLFW_TRUE ou 1 fonctionne
    }
    //SI P => pause
    //SI fleche du haut : aller en haut
    //SI fleche du bas : aller en bas
    //SI fleche de droite : aller en droite
    //SI fleche de gauche : aller en gauche
}

void App::mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        double xpos, ypos;
        //getting cursor position
        glfwGetCursorPos(window, &xpos, &ypos);
        conversion(xpos, ypos);
        std::cout << "Cursor Position at (" << _height << ")" << std::endl;
        std::cout << "Cursor Position at (" << _width << ")" << std::endl;
        std::cout << "Cursor Position at (" << xpos << " : " << ypos << ")" << std::endl;
        cursor_position_callback(window, xpos, ypos);
    }
}

//FROM TD1 ex3
// void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
// {}
void App::scroll_callback(double /*xoffset*/, double /*yoffset*/)
{
}

void App::cursor_position_callback(GLFWwindow *window, double xpos, double ypos)
{

    //cursor_position_callback
    if (xpos <= 0.5f && xpos >= 0.4 && ypos <= 0.5f && ypos >= 0.4) // && xpos == 1.0 && ypos == 0.0) //si appuye sur bouton pause
    {
        pause_menu();
    }

    // float red, green, blue;
    // glGetFloatv(GL_CURRENT_COLOR, &red);       // Récupérer la composante rouge de la couleur actuelle
    // glGetFloatv(GL_CURRENT_COLOR + 1, &green); // Récupérer la composante verte de la couleur actuelle
    // glGetFloatv(GL_CURRENT_COLOR + 2, &blue);  // Récupérer la composante bleue de la couleur actuelle

    // if (red == 1.0f && green == 0.0f && blue == 0.0f) // && xpos == 1.0 && ypos == 0.0) //si appuye sur bouton pause
    if (xpos <= 0.3f && xpos >= -0.3f && ypos <= -0.15f && ypos >= -0.25f)
    {
        glPushMatrix();
        glScalef(1.0f, 1.0f, 1.0f);
        draw_quad_with_texture(_texture);
        glPopMatrix();
    }
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

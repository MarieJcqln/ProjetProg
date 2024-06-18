#include "App.hpp"
#include "Draw.hpp"

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

App::App() : _previousTime(0.0), _viewSize(2.0), _elapsedTime(0.0), _pauseStartTime(0.0), _isPaused(false)
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

    std::cout<<"Map data : "<<map.data()[1]<<std::endl;

    //_liste = create_list_tiles(map.data(), map.data_size());
    _liste = create_list_tiles(map);

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

    _tile_texture_mapping.insert({TileType::Path, _texturepath});
    _tile_texture_mapping.insert({TileType::Input, _textureinput});
    _tile_texture_mapping.insert({TileType::Output, _textureoutput});
    _tile_texture_mapping.insert({TileType::Empty, _texturevide});

    //COVER
    _texturecover = loadTexture(cover);
    _currentTexture = _texturecover;
}

void App::setup()
{
    //fond bleu
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

    if (!_isPaused)
    {
        const double elapsedTime{currentTime - _previousTime};
        _elapsedTime += elapsedTime;
    }
    _previousTime = currentTime;

    //_angle += 10.0f * elapsedTime;
    // _angle = std::fmod(_angle, 360.0f);

    render();
}

void App::render()
{
    _isPaused = true;
    const double currentTime{glfwGetTime()};
    //CARRE ROUGE DERRIERE LA MAP QUI TOURNE
    // on met a jour la couleur et la profoncdeur du buffer dans la frame buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //MAP QUI TOURNE
    // glPushMatrix();
    // glScalef(0.8f, 0.8f, 0.8f);
    // glRotatef(_angle, 0.0f, 0.0f, 1.0f); //SERT POUR LA ROTATION
    // draw_quad_with_texture(_texture);
    // glPopMatrix();
    //COVER
    glPushMatrix();
    glScalef(1.0f, 1.0f, 1.0f);
    draw_quad_with_texture(_currentTexture, -0.5f, -0.5f, 1.0f);
    glPopMatrix();

    TextRenderer.Label("SHARK'ATTACK", _width / 2, _height / 3, SimpleText::CENTER);

    if (!_boutonJouerClicked) //tant que bouton jouer pas cliquer on l'affiche
    {                         // Dessiner le bouton seulement si pas cliqué

        bouton_jouer();
    }

    if (_uptoplay)
    {
        glClearColor(0.0, 0.0, 0.8, 0.5);
        quadrillage(_liste, _tile_texture_mapping);
    }

    if ((!_pauseClicked && _boutonJouerClicked))
    {
        _isPaused = false;
        //on lance le chrono à 0
        const std::string time_label_text{"Temps ecoule : " + std::to_string(_elapsedTime)};
        TextRenderer.Label(time_label_text.c_str(), _width / 2, _height - 4, SimpleText::CENTER);
        bouton_pause();
    }

    if (_boutonRejouerCliked)
    {
        _isPaused = false;
        //on lance le chrono à 0
        const std::string time_label_text{"Temps ecoule : " + std::to_string(_elapsedTime)};
        TextRenderer.Label(time_label_text.c_str(), _width / 2, _height - 4, SimpleText::CENTER);
        bouton_pause();
    }

    double time_pause{0};

    if (_pauseClicked)
    {
        pause_menu();
        //pour transformer le bouton pause en croix
        glColor4f(0.9f, 0.9f, 0.9f, 0.9f);
        glRotatef(45, 0., 0., 1.);
        glTranslatef(0.19f, -0.45f, 0.0f);
        glBegin(GL_QUADS);
        glVertex2f(0.4f, 0.4f);
        glVertex2f(0.43f, 0.4f);
        glVertex2f(0.43f, 0.49f);
        glVertex2f(0.4f, 0.49f);
        glEnd();
        glLoadIdentity();
        glRotatef(-45, 0., 0., 1.);
        glTranslatef(-0.45f, 0.17f, 0.0f);
        glBegin(GL_QUADS);
        glVertex2f(0.48f, 0.4f);
        glVertex2f(0.45f, 0.4f);
        glVertex2f(0.45f, 0.49f);
        glVertex2f(0.48f, 0.49f);
        glEnd();
        glLoadIdentity();

        if (!_isPaused)
        {
            _pauseStartTime = currentTime;
            _isPaused = true;
        }
    }

    if (_boutonContinuerCliked)
    {
        _uptoplay = true;
        // on ajoute la durée de la pause à _previousTime pour que elapsedtime reste fiable
        _previousTime += (glfwGetTime() - _pauseStartTime);
        _isPaused = false;

        const std::string time_label_text{"Temps ecoule : " + std::to_string(_elapsedTime)};
        TextRenderer.Label(time_label_text.c_str(), _width / 2, _height - 4, SimpleText::CENTER);
    }

    TextRenderer.Render();
}

void App::bouton_jouer()
{
    // render exemple quad
    glColor4f(0.0f, 0.0f, 1.0f, 0.5f);
    glBegin(GL_QUADS);
    glVertex2f(-0.3f, -0.25f);
    glVertex2f(0.3f, -0.25f);
    glVertex2f(0.3f, -0.15f);
    glVertex2f(-0.3f, -0.15f);
    glEnd();
    TextRenderer.Label("JOUER", _width / 2, 3.7 * _height / 6, SimpleText::CENTER);
}
void App::bouton_rejouer()
{
    // render exemple quad
    glColor4f(0.0f, 0.0f, 1.0f, 0.5f);
    glBegin(GL_QUADS);
    glVertex2f(-0.3f, -0.0f);
    glVertex2f(0.3f, -0.0f);
    glVertex2f(0.3f, 0.10f);
    glVertex2f(-0.3f, 0.10f);
    glEnd();
    TextRenderer.Label("REJOUER", _width / 2, 3.0 * _height / 6, SimpleText::CENTER);
}

void App::bouton_continuer()
{
    // render exemple quad
    glColor4f(0.0f, 0.0f, 1.0f, 0.5f);
    glColor4f(1.0f, 0.0f, 0.0f, 0.5f);
    glBegin(GL_QUADS);
    glVertex2f(-0.3f, -0.25f);
    glVertex2f(0.3f, -0.25f);
    glVertex2f(0.3f, -0.15f);
    glVertex2f(-0.3f, -0.15f);
    glEnd();
    TextRenderer.Label("CONTINUER", _width / 2, 3.7 * _height / 6, SimpleText::CENTER);
}

void App::bouton_pause()
{
    //dessin du bouton pause
    glColor4f(0.2f, 0.2f, 0.2f, 0.5f);
    glBegin(GL_QUADS);
    glVertex2f(0.4f, 0.4f);
    glVertex2f(0.43f, 0.4f);
    glVertex2f(0.43f, 0.49f);
    glVertex2f(0.4f, 0.49f);
    glEnd();
    // glColor4f(1.0f, 0.8f, 0.2f, 0.5f);
    glBegin(GL_QUADS);
    glVertex2f(0.48f, 0.4f);
    glVertex2f(0.45f, 0.4f);
    glVertex2f(0.45f, 0.49f);
    glVertex2f(0.48f, 0.49f);
    glEnd();
}

void App::pause_menu()
{
    _uptoplay = false;
    glClearColor(0.0f, 0.0f, 0.8f, 0.5f); // on ajoute un filtre noir transparent pour voir la map par transparence
    glColor4f(0.0f, 0.0f, 0.4f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(-0.5f, -0.5f);
    glVertex2f(0.5f, -0.5f);
    glVertex2f(0.5f, 0.5f);
    glVertex2f(-0.5f, 0.5f);
    glEnd();
    TextRenderer.Label("PARTIE EN PAUSE", _width / 2, 2.3 * _height / 6, SimpleText::CENTER);
    bouton_rejouer();
    bouton_continuer();
}

static const float GL_VIEW_SIZE = 2.0f;

void App::conversion(double &xpos, double &ypos) //conversion de la taille de l'ecran
{
    xpos = ((xpos - (_width / 2)) * GL_VIEW_SIZE / _height);
    ypos = -((ypos - (_height / 2)) * GL_VIEW_SIZE / _height);
}

void App::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    // std::cout << key << std::endl; //pour voir si on capte bien que je touche une touche
    //QUITTER
    if (key == GLFW_KEY_A && action == GLFW_PRESS) //on met A car en querty A=Q
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE); //GLFW_TRUE ou 1 fonctionne
    }
    //PAUSE
    if (key == GLFW_KEY_P && action == GLFW_PRESS)
    {

        // void glfwSetWindowShouldClose(GLFWwindow * window, int value);
        _pauseClicked = true;
    }
    //REJOUER
    if (key == GLFW_KEY_R && action == GLFW_PRESS)
    {
        _currentTexture = _texture;
        _pauseClicked = false;
        _elapsedTime = 0.0; //on recommence le chrono a zero
        _boutonRejouerCliked = true;
        _uptoplay = true;
        render();
    }
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

void App::scroll_callback(double /*xoffset*/, double /*yoffset*/)
{
}

void App::cursor_position_callback(GLFWwindow *window, double xpos, double ypos)
{
    //cursor_position_callback
    if (xpos <= 0.5f && xpos >= 0.4 && ypos <= 0.5f && ypos >= 0.4) // && xpos == 1.0 && ypos == 0.0) //si appuye sur bouton pause
    {
        if (_pauseClicked) //si on clic sur la croix dans le menu pause
        {
            _currentTexture = _texture;
            _pauseClicked = false;
            _boutonJouerClicked = true;
            _uptoplay = true;
            render();
        }
        else
        {
            _pauseClicked = true;
        }
    }

    //JOUER
    else if (xpos <= 0.3f && xpos >= -0.3f && ypos <= -0.15f && ypos >= -0.25f)
    {
        _currentTexture = _texture;
        _pauseClicked = false;
        _boutonJouerClicked = true;
        _uptoplay = true;
        render();
    }
    //REJOUER
    else if (xpos <= 0.3f && xpos >= -0.3f && ypos <= 10.0f && ypos >= 0.0f) //si clique sur rejouer
    {
        _currentTexture = _texture;
        _pauseClicked = false;
        _elapsedTime = 0.0; //on recommence le chrono a zero
        _boutonRejouerCliked = true;
        _uptoplay = true;
        render();
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

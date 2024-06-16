#include "App.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <img/img.hpp>

#include <sstream>

#include "simpletext.h"
#include "utils.hpp"
#include "GLHelpers.hpp"

#include <GL/glut.h>

GLuint texture = 0;
///// COVER DU GAME //////
void background()
{
    glBindTexture(GL_TEXTURE_2D, texture);

    // texture width/height
    const int iw = 500;
    const int ih = 500;

    glPushMatrix();
    glLoadIdentity();
    glTranslatef(-iw / 2, -ih / 2, 0);
    glBegin(GL_QUADS);
    //ON DONNE LES 4 coins de l'ecran
    glTexCoord2f(0, 0);
    glVertex2f(0, 0);
    glTexCoord2f(1, 0);
    glVertex2f(iw, 0);
    glTexCoord2f(1, 1);
    glVertex2i(iw, ih);
    glTexCoord2f(0, 1);
    glVertex2f(0, ih);
    glEnd();
    glPopMatrix();
}
//////////////////////////////

// regarder discord sur comment parcourir les pixels d'une image
// c un truc avec rgb ou autre

// void texture()
// {

//     ///// EX2 TD4
//     GLuint textures;
//     glGenTextures(1, &textures); // 1 pour la taille du tableua ///on passe par adresse pour qu'il puisse modifier la texture

//     glBindTexture(GL_TEXTURE_2D, textures);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

//     glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, x, y, 0, GL_RGB, GL_UNSIGNED_BYTE, chargee_image1);
//     glBindTexture(GL_TEXTURE_2D, 0);
//     //////
//     for (int ligne{0}; ligne < largeur; ligne++)
//     {
//         for (int colonne{}; colonne < largeur; colonne++)
//         {
//             if (pixel.color == (1, 1, 1)) //si le pixel est blanc
//             {
//                 // load what needs to be loaded here (for example textures)
//                 img::Image sable{img::load(make_absolute_path("images/sable_pixel.png", true), 3, true)}; //texture sable
//                 //load charge à partir de en haut à gauche
//                 _texture = loadTexture(sable);
//             }
//             else if (pixel.color == (0, 0, 0)) //si le pixel est noir
//             {
//                 // load what needs to be loaded here (for example textures)
//                 img::Image mer{img::load(make_absolute_path("images/mer_pixel.png", true), 3, true)}; //texture mer
//                 //load charge à partir de en haut à gauche
//                 _texture = loadTexture(sable);
//             }
//             else if (pixel.color == (1, 0, 0)) //si le pixel est rouge
//             {
//                 // load what needs to be loaded here (for example textures)
//                 img::Image sable{img::load(make_absolute_path("images/sable_pixel.png", true), 3, true)}; //texture sable
//                 //load charge à partir de en haut à gauche
//                 _texture = loadTexture(sable);
//                 //on ajoute l'image du palmier
//                 img::Image palmier{img::load(make_absolute_path("images/palmier_pixel.png", true), 3, true)};
//                 _texture = loadTexture(palmier);
//             }
//             else if (pixel.color == (0, 0, 1)) //si le pixel est bleu
//             {
//                 // load what needs to be loaded here (for example textures)
//                 img::Image sable{img::load(make_absolute_path("images/sable_pixel.png", true), 3, true)};
//                 //load charge à partir de en haut à gauche
//                 _texture = loadTexture(sable);
//                 //on ajoute l'image de la bouée
//                 img::Image bouee{img::load(make_absolute_path("images/palmier_pixel.png", true), 3, true)};
//             }
//         }
//     }
// }
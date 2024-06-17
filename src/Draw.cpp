#include "App.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <img/img.hpp>

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

#include "simpletext.h"
#include "utils.hpp"
#include "GLHelpers.hpp"

#include <vector>
#include <unordered_map>

enum class TileType {
  Path,
  Input,
  Output,
  Empty
};

std::unordered_map<TileType, GLuint> tile_texture_mapping{};
/* 
// load images
GLuint App::_texture 
tile_texture_mapping[TileType::Path] = loadTexture(img::load(make_absolute_path("images/tile_path.png", true), 3, true));
tile_texture_mapping[TileType::Input] = loadTexture(img::load(make_absolute_path("images/tile_Input.png", true), 3, true));
tile_texture_mapping[TileType::Output] = loadTexture(img::load(make_absolute_path("images/tile_path.png", true), 3, true));
tile_texture_mapping[TileType::Empty] = loadTexture(img::load(make_absolute_path("images/tile_Input.png", true), 3, true));
//...

// Puis au moment de faire le rendu des cases
for(unsigned int i {0}; i < tiles.size(); ++i) {
  Tile const& tile { tiles[i] };

  // Astuce pour récupérer la position x, et y depuis l'id dans un vecteur 1D
  // Vous pouvez aussi faire une double boucle for à la place
  unsigned int pox_x { i % width };
  unsigned int pox_y { i / width };
  glPushMatrix();
  // Je positionne ma tile au bon endroit avec un translate
  glTranslatef(x, y, 0.f);
  // Je récupère l'id de texture openGL dans mon tableau associatif en fonction du type de ma case
  const GLuint tile_texture_id { tile_texture_mapping[tile .type] };

  draw_quad_with_texture(tile_texture_id );
  glPopMatrix();
  // ...
}
 */

/**
 * Crée une liste de cases à partir d'un tableau de pixel (celui de la map de référence)
 */ 
std::vector<TileType> create_list_tiles(uint8_t *map_reference, size_t size) {
  int mapwidth{10};
    std::vector<TileType> tile_list {};
    unsigned int tile_id {0};
    size_t tile_size {size/mapwidth/mapwidth};

    for (size_t i {0}; i < size; i += tile_size) {
        float x {-0.5f + i/tile_size%mapwidth * 0.1f};
        float y {-0.5f + i/tile_size/mapwidth * 0.1f};

        //CASE_TYPE case_type = get_case_type_from_rgb(map_reference[i], map_reference[i+1], map_reference[i+2]);
        if (map_reference[i], map_reference[i+1], map_reference[i+2]){

        }

        //if (case_type == CASE_TYPE::BLANK) tile_list.push_back({tile_id, x, y, case_type, false});
        //else tile_list.push_back({tile_id, x, y, case_type, true});

        tile_id++;
    }
    
    return tile_list;
}
//dessiner quadrillage
void quadrillage() {
    //boucler sur l'image
    //mettre bonne texture sur chaque quad
    int i{0};
    glColor3f(0.0f, 0.0f, 0.0f);
    for (float h = -0.5f; h <= 0.5f; h += 0.1f) {
        for (float w = -0.5f; w <= 0.5f; w += 0.1f) {

            glBegin(GL_QUADS);
            glTexCoord2d(0, 0);
            glVertex2f(w, h);
            glTexCoord2d(1, 0);
            glVertex2f(w + 0.1f, h);
            glTexCoord2d(1, 1);
            glVertex2f(w + 0.1f, h + 0.1f);
            glTexCoord2d(0, 1);
            glVertex2f(w, h + 0.1f);
            glEnd();

           /*  if (App::test.data()[i]=={vide}){
           draw_quad_with_texture(_texturevide);
            } 
            else if (App::test.data()[i]=={entree}){
           draw_quad_with_texture(_textureentree);
            } 
            else if (App::test.data()[i]=={sortie}){
           draw_quad_with_texture(_texturesortie);
            } 
            else if (App::test.data()[i]=={chemin}){
           draw_quad_with_texture(_texturechemin);
            } */

            w= w+0.1f;
            i++;
            }

        h= h+0.1f;

        glPushMatrix();
        glScalef(0.8f, 0.8f, 0.8f);
        //glRotatef(_angle, 0.0f, 0.0f, 1.0f);
        //if
        //draw_quad_with_texture(_texture);
        glPopMatrix();
        //App::App.test.data()
    }

}
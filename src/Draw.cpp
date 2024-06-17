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

/**
 * Crée une liste de cases à partir d'un tableau de pixel (celui de la map de référence)
 */ 
std::vector<TileType> create_list_tiles(uint8_t *map_reference, size_t size) {
    int mapwidth{10};
    std::vector<TileType> tile_list {};
    //unsigned int tile_id {0};
    size_t tile_size {size/mapwidth/mapwidth};

    for (size_t i {0}; i < size; i += tile_size) {
        //float x {-0.5f + i/tile_size%mapwidth * 0.1f};
        //float y {-0.5f + i/tile_size/mapwidth * 0.1f};
        
        if (map_reference[i]== 0 && map_reference[i+1]==0 && map_reference[i+2]==0){
          tile_list.push_back(TileType::Empty);
        }
        else if (map_reference[i]== 1 && map_reference[i+1]==0 && map_reference[i+2]==0){
          tile_list.push_back(TileType::Input);
        }
        else if (map_reference[i]== 0 && map_reference[i+1]==0 && map_reference[i+2]==1){
          tile_list.push_back(TileType::Output);
        }
        else if (map_reference[i]== 1 && map_reference[i+1]==1 && map_reference[i+2]==1){
          tile_list.push_back(TileType::Path);
        }
        //tile_id++;
    }
    
    return tile_list;
}
//dessiner quadrillage
//Grâce à la liste des types de cases de l'image et de l'association texture/type
void quadrillage(std::vector<TileType>& liste, std::unordered_map<TileType, GLuint>& tile_texture_mapping){
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

          if (liste[i]==TileType::Empty){
            draw_quad_with_texture(tile_texture_mapping[TileType::Empty]);
          } 
          else if (liste[i]==TileType::Input){
            draw_quad_with_texture(tile_texture_mapping[TileType::Input]);
          } 
          else if (liste[i]==TileType::Output){
            draw_quad_with_texture(tile_texture_mapping[TileType::Output]);
          }
          else if (liste[i]==TileType::Path){
            draw_quad_with_texture(tile_texture_mapping[TileType::Path]);
          }

          w= w+0.1f;
          i++;
        }
        h= h+0.1f;
        }
}
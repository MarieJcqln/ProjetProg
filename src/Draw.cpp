// #include "App.hpp"
#include "Draw.hpp"

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

TileType get_tile_type_from_rgb(int r, int g, int b) {
    if (r == 255 && g == 0 && b == 0) return TileType::Output;
    if (r == 255 && g == 255 && b == 255) return TileType::Path;
    if (r == 0 && g == 0 && b == 255) return TileType::Input;
    else return TileType::Empty;
}

std::vector<TileType> create_list_tiles(img::Image &baseMap)
{
  std::vector<TileType> listCases;
  int mapwidth{10};
    size_t datasize = size_t(baseMap.data_size());
    int width = baseMap.width();
    int height = baseMap.height();
    int size = width * height;
    size_t tile_size {datasize/mapwidth/mapwidth};

    for (int i = 0; i < datasize; i+=tile_size)
    {
        double x = i % width;
        double y = height - 1 - (i / width);

        glm::vec3 color;
        color.r = baseMap.data()[i];
        color.g = baseMap.data()[i + 1];
        color.b = baseMap.data()[i + 2];

        // On vérifie si la couleur correspond à un type de case
        std::array<float, 3> colorTab = {color.r, color.g, color.b};

        listCases.push_back(get_tile_type_from_rgb(colorTab[0],colorTab[1],colorTab[2]));
      }
    return listCases;
}

//dessiner quadrillage
//Grâce à la liste des types de cases de l'image et de l'association texture/type
void quadrillage(std::vector<TileType> &liste, std::unordered_map<TileType, GLuint> &tile_texture_mapping)
{
  //boucler sur l'image
  //mettre bonne texture sur chaque quad
  int i{0};
  float taille{0.1f};
  glColor3f(0.0f, 0.0f, 0.0f);
  for (float h = -0.5f; h < 0.4f; h += 0.1f)
  {
    for (float w = -0.5f; w < 0.4f; w += 0.1f)
    {
      if (liste[i] == TileType::Empty)
      {
        draw_quad_with_texture(tile_texture_mapping[TileType::Empty], w, h, taille);
      }
      else if (liste[i] == TileType::Input)
      {
        draw_quad_with_texture(tile_texture_mapping[TileType::Input], w, h, taille);
      }
      else if (liste[i] == TileType::Output)
      {
        draw_quad_with_texture(tile_texture_mapping[TileType::Output], w, h, taille);
      }
      else if (liste[i] == TileType::Path)
      {
        draw_quad_with_texture(tile_texture_mapping[TileType::Path], w, h, taille);
      }
      i++;
    }
  }
}
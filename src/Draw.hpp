#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <simpletext.h>
#include <iostream>
#include <unordered_map>
#include <vector>
#include "GLHelpers.hpp"

#include "App.hpp"

TileType get_tile_type_from_rgb(int r, int g, int b);
std::vector<TileType> create_list_tiles(img::Image &baseMap);

void quadrillage(std::vector<TileType> &liste, std::unordered_map<TileType, GLuint> &tile_texture_mapping);
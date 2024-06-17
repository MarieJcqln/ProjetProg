#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <simpletext.h>
#include <iostream>
#include <unordered_map>

#include "App.hpp"

std::vector<TileType> create_list_tiles(uint8_t *map_reference, size_t size);

void quadrillage(std::vector<TileType>& liste, std::unordered_map<TileType, GLuint>& tile_texture_mapping);
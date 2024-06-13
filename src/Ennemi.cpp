#include "App.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <img/img.hpp>

#include <sstream>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <utility>
#include <queue>
#include <functional>
#include <string_view>

#include "simpletext.h"
#include "Ennemi.hpp"
#include "GLHelpers.hpp"

using namespace Graph;

std::unordered_map<int, std::pair<int,float>> dijkstra(std::unordered_map<int, std::vector<WeightedGraphEdge>> adjacency_list, int depart, int arrive){
    //tableau associatif pour associer à chaque sommet visité la distance la plus courte connue pour aller du sommet de départ à ce sommet et d'où on vient pour atteindre cette distance
    std::unordered_map<int, float> distances;
    std::unordered_map<int, int> predecessors;
    std::unordered_map<int, std::pair<int,float>> chemin{};

    // priority queue pour itérer sur les sommets à visiter en choisissant à chaque fois le sommet le plus proche du sommet de départ
    using Element = std::pair<float, int>;
    std::priority_queue<Element, std::vector<Element>, std::greater<Element>> file_a_visiter;

    // initialisation
    file_a_visiter.push({0.0, depart});
    distances[depart] = 0.0;

    while (!file_a_visiter.empty()) {
        int current = file_a_visiter.top().second;
        float current_distance = file_a_visiter.top().first;
        file_a_visiter.pop();

        // Si nous avons atteint le sommet d'arrivée, nous pouvons arrêter la recherche
        if (current == arrive) break;

        // Iteration sur les voisins
        for (const auto& edge : adjacency_list[current]) {
            int neighbor = edge.to;
            float weight = edge.weight;
            float distance_through_current = current_distance + weight;

            // Si un chemin plus court vers le voisin est trouvé
            if (distances.find(neighbor) == distances.end() || distance_through_current < distances[neighbor]) {
                distances[neighbor] = distance_through_current;
                predecessors[neighbor] = current;
                file_a_visiter.push({distance_through_current, neighbor});
            }
        }
    }

    // Construction du chemin
    int current = arrive;
    while (current != depart) {
        chemin[current] = {predecessors[current], distances[current]};
        current = predecessors[current];
    }
    chemin[depart] = {depart, 0};


    return chemin;
}




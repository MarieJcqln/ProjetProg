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
#include "utils.hpp"
#include "GLHelpers.hpp"

class Chemin
{
    struct WeightedGraphEdge
    {
        int to{};
        float weight{1.0f};
        int x{};
        int y{};
        //Couleur
        int r{255};
        int g{255};
        int b{255};

        // default ici permet de définit les opérateurs de comparaison membres à membres automatiquement
        // Cela ne fonction qu'en C++20, si vous n'avez pas accès à cette version je vous donne les implémentations des opérateurs plus bas
        bool operator==(WeightedGraphEdge const &other) const = default;
        bool operator!=(WeightedGraphEdge const &other) const = default;
    };

    struct WeightedGraph
    {
        // L'utilisation d'un tableau associatif permet d'avoir une complexité en O(1) pour l'ajout et la recherche d'un sommet.
        // Cela permet de stocker les sommets dans un ordre quelconque (et pas avoir la contrainte d'avoir des identifiants (entiers) de sommets consécutifs lors de l'ajout de sommets).
        // Cela permet également de pouvoir utiliser des identifiants de sommets de n'importe quel type (string, char, int, ...) et pas seulement des entiers.
        std::unordered_map<int, std::vector<WeightedGraphEdge>> adjacency_list{};

        void add_vertex(int const id);

        void add_directed_edge(int const from, int const to, float const weight = 1.0f);
        void add_undirected_edge(int const from, int const to, float const weight = 1.0f);

        // Même fonctionnement que pour WeightedGraphEdge
        bool operator==(WeightedGraph const &other) const = default;
        bool operator!=(WeightedGraph const &other) const = default;

        void print_DFS(int const start) const;
        void print_BFS(int const start) const;

        WeightedGraph build_from_adjacency_matrix(std::vector<std::vector<float>> const &adjacency_matrix);

        WeightedGraph read_map(std::string lien);
    };
};

void Chemin::WeightedGraph::add_vertex(int const id)
{
    //find
    auto A = adjacency_list.find(id);
    if (A != adjacency_list.end())
    {
        //Ajout du sommet, créer la liste de edges
        // adjacency_list.insert(std::make_pair<int, std::vector<WeightedGraphEdge>>(id,{}));
        adjacency_list[id] = {};
    }
}

void Chemin::WeightedGraph::add_directed_edge(int const from, int const to, float const weight)
{
    //ajout arête et vertex s'il existe pas
    auto A = adjacency_list.find(from);
    auto B = adjacency_list.find(to);
    if (A == adjacency_list.end())
    {
        add_vertex(from);
    }
    if (B == adjacency_list.end())
    {
        add_vertex(to);
    }
    Chemin::WeightedGraphEdge edge{to, weight};
    adjacency_list[from].push_back(edge);
}

void Chemin::WeightedGraph::add_undirected_edge(int const from, int const to, float const weight)
{
    add_directed_edge(from, to, weight);
    add_directed_edge(to, from, weight);
}

Chemin::WeightedGraph Chemin::WeightedGraph::build_from_adjacency_matrix(std::vector<std::vector<float>> const &adjacency_matrix)
{
    Chemin::WeightedGraph graphe{};
    int i{0};
    while (i < adjacency_matrix.size())
    {
        int a{0};
        while (a < adjacency_matrix[i].size())
        {
            if (adjacency_matrix[i][a] != 0)
            {
                graphe.add_directed_edge(i, a, adjacency_matrix[i][a]);
            }
            a++;
        }
        i++;
    }
    return graphe;
}

// Chemin::WeightedGraph Chemin::WeightedGraph::read_map(std::string lien)
// {
//     Chemin::WeightedGraph arbre{};
//     std::ifstream file(lien);
//     std::string line;
//     while (std::getline(file, line))
//     {
//         //lecture itd
//         if (line[0] == 'n')
//         {
//             int from = line[5];
//             int to = line[11];
//             float distance{};
//             int x{line[7]};
//             int y{line[9]};
//             //Couleur
//             int r{};
//             int g{};
//             int b{};
//             if (line[5] == 'O')
//             {
//                 r = 0;
//                 g = 0;
//                 b = 255;
//             }
//             else if (line[11] == ' ')
//             {
//                 r = 255;
//                 g = 0;
//                 b = 0;
//             }
//             //arbre.add_undirected_edge(from,to,distance);

//             auto A = Chemin::WeightedGraph::adjacency_list.find(from);
//             auto B = Chemin::WeightedGraph::adjacency_list.find(to);
//             if (A == Chemin::WeightedGraph::adjacency_list.end())
//             {
//                 Chemin::WeightedGraph::add_vertex(from);
//             }
//             if (B == Chemin::WeightedGraph::adjacency_list.end())
//             {
//                 Chemin::WeightedGraph::add_vertex(to);
//             }
//             Chemin::WeightedGraphEdge edge{to, distance, x, y, r, g, b};
//             Chemin::WeightedGraph::adjacency_list[from].push_back(edge);
//         }
//         else
//         {
//             continue;
//         }
//     }
// }

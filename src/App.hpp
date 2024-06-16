#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <simpletext.h>
#include <iostream>

class App {
public:
    App();

    void setup();
    void update();
    void pause_menu();
    
    // GLFW callbacks binding
    void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
    void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);
    void scroll_callback(double xoffset, double yoffset);
    void cursor_position_callback(GLFWwindow *window, double xpos, double ypos);
    void size_callback(int width, int height);


    struct WeightedGraphEdge {
        int to {};
        float weight {1.0f};
        int x{};
        int y{};
        //Couleur
        int r{255};
        int g{255};
        int b{255};


        // default ici permet de définit les opérateurs de comparaison membres à membres automatiquement
        // Cela ne fonction qu'en C++20, si vous n'avez pas accès à cette version je vous donne les implémentations des opérateurs plus bas
        bool operator==(WeightedGraphEdge const& other) const = default;
        bool operator!=(WeightedGraphEdge const& other) const = default;
    };

    struct WeightedGraph {
        // L'utilisation d'un tableau associatif permet d'avoir une complexité en O(1) pour l'ajout et la recherche d'un sommet.
        // Cela permet de stocker les sommets dans un ordre quelconque (et pas avoir la contrainte d'avoir des identifiants (entiers) de sommets consécutifs lors de l'ajout de sommets).
        // Cela permet également de pouvoir utiliser des identifiants de sommets de n'importe quel type (string, char, int, ...) et pas seulement des entiers.
        std::unordered_map<int, std::vector<WeightedGraphEdge>> adjacency_list {};

        void add_vertex(int const id);

        void add_directed_edge(int const from, int const to, float const weight = 1.0f);
        void add_undirected_edge(int const from, int const to, float const weight = 1.0f);
        
        // Même fonctionnement que pour WeightedGraphEdge
        bool operator==(WeightedGraph const& other) const = default;
        bool operator!=(WeightedGraph const& other) const = default;

        void print_DFS(int const start) const;
        void print_BFS(int const start) const;

    WeightedGraph build_from_adjacency_matrix(std::vector<std::vector<float>> const& adjacency_matrix);
    
    WeightedGraph read_map(std::string lien);
    }; 

    

    

private:
    void render();

    int _width {};
    int _height {};
    double _previousTime {};
    float _viewSize {};

    // Add your variables here
    GLuint _texture {};
    float _angle {};

    SimpleText TextRenderer {};


};
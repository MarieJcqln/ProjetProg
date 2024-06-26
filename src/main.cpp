#include <glad/glad.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <iostream>

#include "App.hpp"
#include "Draw.hpp"

/* Window properties */
static const unsigned int WINDOW_WIDTH = 10;
static const unsigned int WINDOW_HEIGHT = 10;
static const char WINDOW_TITLE[] = "BITCHARK";
static float aspectRatio = 1.0;

namespace
{
    App &window_as_app(GLFWwindow *window)
    {
        return *static_cast<App *>(glfwGetWindowUserPointer(window));
    }
}

// Optional: limit the frame rate
constexpr double TARGET_TIME_FOR_FRAME{1.0 / 60.0};

int main()
{
    //pour connaitre le type d'OS
    std::string _OSType2;

#ifdef IS_MACOS
    _OSType2 = "MAC";
#elif IS_LINUX
    _OSType2 = "LINUX";
#elif IS_WINDOWS
    _OSType2 = "WINDOWS";
#else
    _OSType2 = "UNKNOWN";
#endif

    // Set an error callback to display glfw errors
    glfwSetErrorCallback([](int error, const char *description)
                         { std::cerr << "Error " << error << ": " << description << std::endl; });

    // Initialize glfw
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Not working on apple with those hint for unknown reason
    // #ifdef __APPLE__
    //     // We need to explicitly ask for a 3.3 context on Mac
    //     glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    //     glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    //     glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    //     glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // #endif

    // Create window
    GLFWwindow *window{glfwCreateWindow(1280, 720, "Window", nullptr, nullptr)};
    if (!window)
    {
        std::cerr << "Failed to create window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Intialize glad (loads the OpenGL functions)
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize OpenGL context" << std::endl;
        glfwTerminate();
        return -1;
    }

    App app{};

    app._OSType = _OSType2; //pour donner a la variable dans app.hpp le type d'OS

    glfwSetWindowUserPointer(window, &app);

    glfwSetKeyCallback(window, [](GLFWwindow *window, int key, int scancode, int action, int mods)
                       { window_as_app(window).key_callback(window, key, scancode, action, mods); });
    // //// CODE AJOUTE 3)2)//// Quitter window si touche Q touché
    // glfwSetKeyCallback(window, key_callback);
    // //////////////////
    glfwSetMouseButtonCallback(window, [](GLFWwindow *window, int button, int action, int mods)
                               { window_as_app(window).mouse_button_callback(window, button, action, mods); });
    glfwSetScrollCallback(window, [](GLFWwindow *window, double xoffset, double yoffset)
                          { window_as_app(window).scroll_callback(xoffset, yoffset); });
    glfwSetCursorPosCallback(window, [](GLFWwindow *window, double xpos, double ypos)
                             { window_as_app(window).cursor_position_callback(window, xpos, ypos); });
    glfwSetWindowSizeCallback(window, [](GLFWwindow *window, int width, int height)
                              { window_as_app(window).size_callback(width, height); });

    // Force calling the size_callback of the game to set the right viewport and projection matrix
    {
        int width, height;
        glfwGetWindowSize(window, &width, &height);
        app.size_callback(width, height);
    }

    app.setup();

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window))
    {

        // Get time (in second) at loop beginning
        double startTime{glfwGetTime()};

        app.update();

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();

        // Optional: limit the frame rate
        double elapsedTime{glfwGetTime() - startTime};
        // wait the remaining time to match the target wanted frame rate
        if (elapsedTime < TARGET_TIME_FOR_FRAME)
        {
            glfwWaitEventsTimeout(TARGET_TIME_FOR_FRAME - elapsedTime);
        }
    }

    glfwTerminate();
    return 0;
}

#ifndef CUBO_H
#define CUBO_H

#include "../headers/system/Runnable.h"
#include "data/Mesh.h"
#include "utils/camera.h"
#include <GLM/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class Cubo : public Runnable {

private:
    GLint WIDTH, HEIGHT;
    std::string SCREEN_TITLE;
    vector<glm::vec3*> cubePositions;
    Camera* camera = new Camera(glm::vec3(0.0f, 0.0f, 13.0f));

    Mesh* mesh;

    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	static void processInput(GLFWwindow* window);

public:
    Cubo(int width, int height, std::string screenTitle);
    ~Cubo() override;
    int init(GLFWwindow* window) override;
    void run(GLFWwindow* window) override;
    bool keepRunning(GLFWwindow* window) override;
    void finish() override;
    int width() override;
    int height() override;
    std::string screenTitle() override;
};


#endif

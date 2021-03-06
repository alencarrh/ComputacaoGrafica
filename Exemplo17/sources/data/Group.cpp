#include "../../headers/data/Group.h"

Group::Group(string name) {
    this->name = name;
}

Group::~Group() {
    this->faces.clear();
    this->faces.shrink_to_fit();

    glDeleteVertexArrays(1, &vao);
    for (auto& vbo : this->vbos) {
        glDeleteBuffers(1, &vbo);
    }

    this->vbos.clear();
    this->vbos.shrink_to_fit();
}

int Group::numVertices() {
    int sum = 0;
    for (auto& face : faces) {
        sum += face->getVertices().size();
    }
    return sum;
}

void Group::bindVAO() {
    if (this->vao == NULL) {
        glGenVertexArrays(1, &vao);
    }
    glBindVertexArray(vao);
}


void Group::bindTexture() {
    if (this->texture == NULL) {
        return;
    }
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
}

void Group::bindBuffer(const vector<float>& data, const int vecSize) {
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data.front(), GL_STATIC_DRAW);

    glVertexAttribPointer(shaderLocation, vecSize, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(shaderLocation);

    shaderLocation++;
    this->addVBO(vbo);
}


void Group::setTexture(string filename) {
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;

    unsigned char* imageData = stbi_load(filename.c_str(), &width, &height, &nrChannels, 0);

    if (imageData) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }

    stbi_image_free(imageData);
    this->addVBO(texture);
}

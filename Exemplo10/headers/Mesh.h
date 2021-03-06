#ifndef MESH_H
#define MESH_H

#include <GLM/glm.hpp>
#include <vector>
#include "Group.h"
#include "Shader.h"

using namespace std;

class Mesh {

private:
    string name;
    string material;
    vector<Group*> groups;

	Shader* shader;
	Shader* shaderWhite;

    vector<glm::vec3*> vertices;
    vector<glm::vec3*> normais;
    vector<glm::vec2*> textures;


public:

    Mesh();
    ~Mesh();

    glm::vec3* vertice(int id);
    glm::vec3* normal(int id);
    glm::vec2* texture(int id);

    void setName(string name);
    void setMaterial(string material);
	void setVAO(GLuint* vao);
	void setShader(Shader* shader);
	void setShaderWhite(Shader* shaderWhite);

    int addGroup(Group* group);
    int addVertice(glm::vec3* vertice);
    int addNormal(glm::vec3* normal);
    int addTexture(glm::vec2* texture);


    Shader* getShader() {
		return this->shader;
    }

    Shader* getShaderWhite() {
		return this->shaderWhite;
    }

    vector<Group*>& getGroups() {               
        return groups;
    };
};

#endif

#include "../headers/Cubo.h"

Cubo::Cubo(int width, int height, std::string screenTitle) {
    this->WIDTH = width;
    this->HEIGHT = height;
    this->SCREEN_TITLE = screenTitle;
}

Cubo::~Cubo() {}

Face* createFace(int v0, int v1, int v2, int v3, int normal) {
    Face* face = new Face();
    face->addVerticeId(v0);
    face->addVerticeId(v1);
    face->addVerticeId(v3);

    face->addVerticeId(v1);
    face->addVerticeId(v2);
    face->addVerticeId(v3);
    return face;
}

int Cubo::init(GLFWwindow* window) {
    this->mesh = new Mesh();
    int A = 0, B = 1, C = 2, D = 3, E = 4, F = 5, G = 6, H = 7;
    float escale = 2;

    this->mesh->addVertice(new glm::vec3(1.0f / escale, 1.0f / escale, 1.0f / escale)); //A
    this->mesh->addVertice(new glm::vec3(-1.0f / escale, 1.0f / escale, 1.0f / escale)); //B
    this->mesh->addVertice(new glm::vec3(-1.0f / escale, -1.0f / escale, 1.0f / escale)); //C
    this->mesh->addVertice(new glm::vec3(1.0f / escale, -1.0f / escale, 1.0f / escale)); //D      
    this->mesh->addVertice(new glm::vec3(1.0f / escale, 1.0f / escale, -1.0f / escale)); //E
    this->mesh->addVertice(new glm::vec3(-1.0f / escale, 1.0f / escale, -1.0f / escale)); //F
    this->mesh->addVertice(new glm::vec3(-1.0f / escale, -1.0f / escale, -1.0f / escale)); //G
    this->mesh->addVertice(new glm::vec3(1.0f / escale, -1.0f / escale, -1.0f / escale)); //H

    Group* group = new Group();
    group->addFace(createFace(A, B, C, D, 4));
    group->addFace(createFace(A, D, H, E, 0));
    group->addFace(createFace(A, E, F, B, 2));
    group->addFace(createFace(C, B, F, G, 1));
    group->addFace(createFace(D, C, G, H, 3));
    group->addFace(createFace(H, G, F, E, 5));


    /*      |
            |
       A----|---D
      /+    |  /+
     / +    | / +
    B-------|C  +
    +  +    |+  +
    +  E----|+--H
    + /     |+ /
    +/      |+/
    F-------|G
            |
            |
            |
            |
    */


    this->mesh->addGroup(group);

    this->mesh->setShader(new Shader("./shaders/core/vertex.vert", "./shaders/core/fragment.frag"));
    this->mesh->setShaderWhite(new Shader("./shaders/core/vertex.vert", "./shaders/core/fragment_color.frag"));


    float _width = (float)this->WIDTH;
    float _height = (float)this->HEIGHT;

    glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 100.0f);

    glm::mat4 view(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

    glm::mat4 projection(1.0f);
    projection = glm::perspective(glm::radians(45.0f), _width / _height, 0.1f, 100.0f);

    this->mesh->getShader()->use();
    this->mesh->getShader()->setMatrix4fv("view", view);
    this->mesh->getShader()->setMatrix4fv("projection", projection);

    this->mesh->getShaderWhite()->use();
    this->mesh->getShaderWhite()->setMatrix4fv("view", view);
    this->mesh->getShaderWhite()->setMatrix4fv("projection", projection);


	this->cubePositions.push_back(new glm::vec3(0.0f, 0.0f, 0.0f));
	this->cubePositions.push_back(new glm::vec3(2.0f, 5.0f, -15.0f));
	this->cubePositions.push_back(new glm::vec3(-1.5f, -2.2f, -2.5f));
	this->cubePositions.push_back(new glm::vec3(-3.8f, -2.0f, -12.3f));
	this->cubePositions.push_back(new glm::vec3(2.4f, -0.4f, -3.5f));
	this->cubePositions.push_back(new glm::vec3(-1.7f, 3.0f, -7.5f));
	this->cubePositions.push_back(new glm::vec3(1.3f, -2.0f, -2.5f));
	this->cubePositions.push_back(new glm::vec3(1.5f, 2.0f, -2.5f));
	this->cubePositions.push_back(new glm::vec3(1.5f, 0.2f, -1.5f));
	this->cubePositions.push_back(new glm::vec3(-1.3f, 1.0f, -1.5f));


    for (Group* group : this->mesh->getGroups()) {
        vector<float> vertices;

        for (Face* face : group->getFaces()) {
            for (int verticeID : face->getVertices()) {
                glm::vec3* vertice = this->mesh->vertice(verticeID);
                vertices.push_back(vertice->x);
                vertices.push_back(vertice->y);
                vertices.push_back(vertice->z);

                group->countVertice();
            }
        }

        GLuint VAO, VBOvert;

        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        glGenBuffers(1, &VBOvert);

        glBindBuffer(GL_ARRAY_BUFFER, VBOvert);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices.front(), GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

        glEnableVertexAttribArray(0);

        group->setVAO(&VAO);
    }

    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

    return EXIT_SUCCESS;
}


void Cubo::run(GLFWwindow* window) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (int i = 0; i < cubePositions.size(); i++) {
		glm::vec3 cubePosition = *cubePositions[i];
		glm::mat4 model(1.0f);
		model = glm::translate(model, cubePosition);
		float angle = 20.0f * i;
		model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));

		this->mesh->getShader()->use();
		for (Group* group : this->mesh->getGroups()) {
			this->mesh->getShader()->setMatrix4fv("model", model);
			glBindVertexArray(group->getVAO());
			glDrawArrays(GL_TRIANGLES, 0, group->getNumVertices());
		}

		this->mesh->getShaderWhite()->use();
		for (Group* group : this->mesh->getGroups()) {
			this->mesh->getShaderWhite()->setMatrix4fv("model", model);
			glBindVertexArray(group->getVAO());
			glDrawArrays(GL_LINE_LOOP, 0, group->getNumVertices());
		}

	}

}


bool Cubo::keepRunning(GLFWwindow* window) {
    return !glfwWindowShouldClose(window);
}

void Cubo::finish() {
    delete this->mesh;
}

int Cubo::width() {
    return this->WIDTH;
}

int Cubo::height() {
    return this->HEIGHT;
}

std::string Cubo::screenTitle() {
    return this->SCREEN_TITLE;
}

#include "../../headers/model/Object.h"

Object::Object() {}

Object::Object(string objFile, glm::vec3* position) {
    this->objReader = new ObjReader();
    this->objFile = objFile;
    this->_position = position;
}

Object::~Object() {}

void Object::prepare() {
    this->_mesh = this->objReader->read(this->objFile);
    this->_mesh->prepare();
}

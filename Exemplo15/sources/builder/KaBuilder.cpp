#include "../../headers/builder/KaBuilder.h"

void KaBuilder::process(stringstream& line) {
	float r, g, b;
	line >> r >> g >> b;
	ka.push_back(new glm::vec3(r, g, b));
}

vector<glm::vec3*>& KaBuilder::build() {
	//TODO limpar lista aqui j� que est� classe est� static
	return ka;
}

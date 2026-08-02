#include "Materials.h"

void MaterialType::metal(std::string side, float color[]) {
    this->side = side;
    lightType = "specular";

    GLenum face;

    if (side == "front")
        face = GL_FRONT;
    else if (side == "back")
        face = GL_BACK;
    else if (side == "frontBack")
        face = GL_FRONT_AND_BACK;
    else {
        throwError();
        return;
    }


	glMaterialfv(face, GL_AMBIENT_AND_DIFFUSE, color); // Make the actual surface with the given color

	glMaterialfv(face, GL_SPECULAR, white); // The shiny reflection will be white

	glMaterialf(face, GL_SHININESS, 64.0f); // Control the shape and size of the specular spot
}
void MaterialType::plastic(std::string side, float color[]) {
	this->side = side;
	lightType = "diffuse";

	GLenum face; // Hold GL operation's option

	if (side == "front")
		face = GL_FRONT;
	else if (side == "back")
		face = GL_BACK;
	else if (side == "frontBack")
		face = GL_FRONT_AND_BACK;
	else {
		throwError();
		return;
	}

	float weakWhite[4] = { 0.58f, 0.58f, 0.58f, 1.0f };
	glMaterialfv(face, GL_AMBIENT_AND_DIFFUSE, color); // Make the actual surface with the given color
	glMaterialfv(face, GL_SPECULAR, weakWhite); // The shiny reflection will be weak grey-white
	glMaterialf(face, GL_SHININESS, 20.0f); // Control the shape and size of the specular spot
}
void MaterialType::noMaterial() {
	if (lightType == "specular")
	{
		if (side == "front") { glMaterialfv(GL_FRONT, GL_SPECULAR, black); }
		else if(side == "back") { glMaterialfv(GL_BACK, GL_SPECULAR, black); }
		else{ glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, black); }
	}
	else if (lightType == "diffuse"){
		if (side == "front") { glMaterialfv(GL_FRONT, GL_DIFFUSE, black); }
		else if (side == "back") { glMaterialfv(GL_BACK, GL_DIFFUSE, black); }
		else { glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, black); }
	}
	else if (lightType == "ambient") {
		if (side == "front") { glMaterialfv(GL_FRONT, GL_AMBIENT, black); }
		else if (side == "back") { glMaterialfv(GL_BACK, GL_AMBIENT, black); }
		else { glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, black); }
	}
	else if (lightType == "emmision") {
		if (side == "front") { glMaterialfv(GL_FRONT, GL_EMISSION, black); }
		else if (side == "back") { glMaterialfv(GL_BACK, GL_EMISSION, black); }
		else { glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, black); }
	}
}


void MaterialType::throwError() {
	side = "none";
	throw std::invalid_argument("Input is illegal: the only options are: front, back or frontBack");
}
#pragma once

#include "CommonLibraries.h"

class MaterialType {
private:
	float white[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	std::string side;
	std::string lightType;

	void throwError();
public:
	float black[4] = {0.0f, 0.0f, 0.0f, 1.0f};
	float noShininess = 0.0f;

	void metal(std::string side, float color[]);
	void plastic(std::string side, float color[]);
	void noMaterial();
};
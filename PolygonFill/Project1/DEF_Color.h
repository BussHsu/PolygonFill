#pragma once
#include<glm\glm.hpp>

const glm::vec3 red				(1.0f, 0.0f, 0.0f);
const glm::vec3 green			(0.0f, 1.0f, 0.0f);
const glm::vec3 blue			(0.0f, 0.0f, 1.0f);
const glm::vec3 magenta		= red + blue;
const glm::vec3 cyan		= green + blue;
const glm::vec3 yellow		= red + green;
const glm::vec3 white		= yellow + blue;
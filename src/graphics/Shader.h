#ifndef GRAPHICS_SHADER_H_
#define GRAPHICS_SHADER_H_

#include <string>

class Shader {
public:
	unsigned int id;

	Shader(unsigned int id);
	~Shader();

	void use();
};

extern Shader* load_shader(std::string vertexFile, std::string fragmentFile);

#endif /* GRAPHICS_SHADER_H_ */

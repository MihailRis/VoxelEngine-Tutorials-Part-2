#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "graphics/Shader.h"
#include "graphics/Texture.h"
#include "window/Window.h"
#include "window/Events.h"
#include "loaders/png_loading.h"

int WIDTH = 1280;
int HEIGHT = 720;

float vertices[] = {
		// x    y     z     u     v
	   -1.0f,-1.0f, 0.0f, 0.0f, 0.0f,
		1.0f,-1.0f, 0.0f, 1.0f, 0.0f,
	   -1.0f, 1.0f, 0.0f, 0.0f, 1.0f,

		1.0f,-1.0f, 0.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
	   -1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
};


int main() {
	Window::initialize(WIDTH, HEIGHT, "Window 2.0");
	Events::initialize();

	Shader* shader = load_shader("res/main.glslv", "res/main.glslf");
	if (shader == nullptr){
		std::cerr << "failed to load shader" << std::endl;
		Window::terminate();
		return 1;
	}

	Texture* texture = load_texture("res/img.png");
	if (texture == nullptr){
		std::cerr << "failed to load texture" << std::endl;
		delete shader;
		Window::terminate();
		return 1;
	}

	// Create VAO
	GLuint VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);

	glClearColor(0.6f,0.62f,0.65f,1);

	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	while (!Window::isShouldClose()){
		Events::pullEvents();
		if (Events::jpressed(GLFW_KEY_ESCAPE)){
			Window::setShouldClose(true);
		}
		if (Events::jclicked(GLFW_MOUSE_BUTTON_1)){
			glClearColor(0.8f,0.4f,0.2f,1);
		}

		glClear(GL_COLOR_BUFFER_BIT);


		// Draw VAO
		shader->use();
		texture->bind();
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);

		Window::swapBuffers();
	}

	delete shader;
	delete texture;
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);

	Window::terminate();
	return 0;
}

#ifndef MY_TRIANGLE_H
#define MY_TRIANGLE_H

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class My_Triangle {
private:
	unsigned int VBO;
	unsigned int VAO;

public:
	My_Triangle(float vertices[], unsigned long long size) {
		glGenBuffers(1, &VBO);

		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
	}

	void draw_triangle() {
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
};

#endif

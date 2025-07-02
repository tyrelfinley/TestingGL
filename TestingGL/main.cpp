#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <C:\Users\Tyrel Finley\Desktop\Development\TestingGL\TestingGL\shader_class.h>
#include <C:\Users\Tyrel Finley\Desktop\Development\TestingGL\TestingGL\my_triangle.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void process_input(GLFWwindow* window);

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);

	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, 800, 600);

	Shader new_shader("C:/Users/Tyrel Finley/Desktop/Development/TestingGL/TestingGL/default.vert", "C:/Users/Tyrel Finley/Desktop/Development/TestingGL/TestingGL/default_orange.frag");
	Shader new_shader2("C:/Users/Tyrel Finley/Desktop/Development/TestingGL/TestingGL/default.vert", "C:/Users/Tyrel Finley/Desktop/Development/TestingGL/TestingGL/default_green.frag");
	
	float triangle1_vertices[] = {
		 0.5f,  0.5f, 0.0f,  // top right
		 0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f,  0.5f, 0.0f,  // top left 
	};

	float triangle2_vertices[] = {
		 0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f   // top left
	};

	My_Triangle triangle1(triangle1_vertices, sizeof(triangle1_vertices));
	My_Triangle triangle2(triangle2_vertices, sizeof(triangle2_vertices));

	float middle_tri_vertices[] = {
		 0.0f,  0.5f, 0.0f,  // top right
		 0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // top left 
	};

	My_Triangle middle_tri(middle_tri_vertices, sizeof(middle_tri_vertices));

	while (!glfwWindowShouldClose(window)) {
		process_input(window);

		glClearColor(0.3f, 0.1f, 0.3f, 0.5f);
		glClear(GL_COLOR_BUFFER_BIT);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		new_shader.use();
		//triangle1.draw_triangle();

		//new_shader2.use();
		//triangle2.draw_triangle();

		middle_tri.draw_triangle();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}

void process_input(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
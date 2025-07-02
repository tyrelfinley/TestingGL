#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <string>
#include <glad/glad.h>
#include <fstream>
#include <iostream>
#include <sstream>


class Shader {

public:
	unsigned int ID;

	Shader(const char* vertex_path, const char* fragment_path) {
		std::string vertex_code;
		std::string fragment_code;
		std::ifstream vshader_file;
		std::ifstream fshader_file;

		vshader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fshader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try {
			vshader_file.open(vertex_path);
			fshader_file.open(fragment_path);
			std::stringstream vshader_stream, fshader_stream;

			vshader_stream << vshader_file.rdbuf();
			fshader_stream << fshader_file.rdbuf();

			vshader_file.close();
			fshader_file.close();

			vertex_code = vshader_stream.str();
			fragment_code = fshader_stream.str();
		}
		catch (std::ifstream::failure e) {
			std::cout << "Error shader file not successfully read\n" << std::endl;
		}
		const char* vshader_code = vertex_code.c_str();
		const char* fshader_code = fragment_code.c_str();

		unsigned int vertex, fragment;
		int success;
		char info_log[512];

		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vshader_code, NULL);
		glCompileShader(vertex);
		glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
		check_compile_errors(vertex, "VERTEX");

		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fshader_code, NULL);
		glCompileShader(fragment);
		glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
		check_compile_errors(fragment, "FRAGMENT");

		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);
		check_compile_errors(ID, "PROGRAM");

		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}

	void use() {
		glUseProgram(ID);
	}

	void set_bool(const std::string& name, bool value) const {
		glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
	}

	void set_int(const std::string& name, int value) const {
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	}

	void set_float(const std::string& name, float value) const {
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	}

private:
	void check_compile_errors(unsigned int shader, std::string type) {
		int success;
		char info_log[1024];
		if (type != "PROGRAM") {
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success) {
				glGetShaderInfoLog(shader, 1024, NULL, info_log);
				std::cout << "Error with shader compilation, Type : " << type << "\n" << info_log << "\n -- --------------------------------- --" << std::endl;
			}
		}
		else {
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if (!success) {
				glGetProgramInfoLog(shader, 1024, NULL, info_log);
				std::cout << "Error with shader compilation, Type : " << type << "\n" << info_log << "\n -- --------------------------------- --" << std::endl;
			}
		}
	}
};

#endif

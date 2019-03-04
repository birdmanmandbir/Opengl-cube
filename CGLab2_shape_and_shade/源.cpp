//ע���Ҽ��������������ų�����shader
//����ο�
//https://www.cnblogs.com/--zz/p/9695501.html
#include <glad/glad.h>
#include <glad/glad.c>
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <cstring>
//#include "shaders.h"
using namespace std;
void processInput(GLFWwindow* window);
char* readTheFile(string strSource);
const char* fragmentShaderSource = readTheFile("shader.frag");
const char* vertexShaderSource = readTheFile("shader.vert");
const char* scfragmentShaderSource = readTheFile("someColorShader.frag");
const char* scvertexShaderSource = readTheFile("someColorShader.vert");


void framebuffer_size_callback(GLFWwindow* windows, int width, int height) {
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}
//.frag .vert�ļ���ȡ
char* readTheFile(string strSource) {
	std::ifstream myfile(strSource);
	std::string str((std::istreambuf_iterator<char>(myfile)),
		std::istreambuf_iterator<char>());
	//str���鳤��һ��Ҫ +1,
	/*ԭ��: https://blog.csdn.net/ShiQW5696/article/details/80676290 */
	int len = str.length();
	char* result = new char[len];
	strcpy_s(result, len + 1, str.c_str());
	return result;
}
class Triangle {
public:
	//points in order to make a triangle
	float vertices[9] = {
		-0.5f, -0.5f, 0.0f,
		0.0f, -0.5f, 0.0f,
		0.0f,  0.5f, 0.0f

	};
	//���ɶ��㻺����� ID:VBO
	unsigned int VBO;
	//���ɶ���������� ID:VAO
	unsigned int VAO;
	//���� ������ɫ��
	unsigned int vertexShader;
	//���� Ƭ����ɫ��
	unsigned int fragmentShader;
	//�洢 ��ɫ������
	unsigned int shaderProgram;
	
	void drawMyGraph() {
		FragmentShaderInit();
		vertexShaderInit();

		shaderProgramLinker();
		vertexInput();
	}
private:
	void vertexInput() {
		glGenBuffers(1, &VBO);
		glGenVertexArrays(1, &VAO);

		// 1. ��VAO , VBO
		glBindVertexArray(VAO);

		// 2. ���ƶ������鵽�����й�OpenGLʹ��
		//��������� �󶨵�GL_ARRAY_BUFFERĿ��
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		//���嶥�����ݸ��Ƶ������ڴ�
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		// 3. ���ö�������ָ��
		//������������
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		//���ö�������
		glEnableVertexAttribArray(0);
	}

	void vertexShaderInit() {
		//����һ��������ɫ������
		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		//��ɫ��Դ�븽�ŵ���ɫ��������
		glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
		//������ɫ������
		glCompileShader(vertexShader);

		//�����ɫ�����Ƿ�ɹ�
		int success;
		char infoLog[50];
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		}
	}

	void FragmentShaderInit() {
		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
		glCompileShader(fragmentShader);
		//�����ɫ�����Ƿ�ɹ�
		int success;
		char infoLog[50];
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		}
	}

	void shaderProgramLinker() {
		//������ɫ���������
		shaderProgram = glCreateProgram();
		//������ɫ������ɫ������
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);
		int success;
		char infoLog[50];
		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::LINKE_PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
		}
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}

};
class SomeColorTriangle {
public:
	//points in order to make a triangle
	float vertices[18] = {


		0.0f, -0.5f, 0.0f,1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f,0.0f, 1.0f, 0.0f,
		0.5f,  0.5f, 0.0f,0.0f, 0.0f, 1.0f

	};
	//���ɶ��㻺����� ID:VBO
	unsigned int VBO;
	//���ɶ���������� ID:VAO
	unsigned int VAO;
	//���� ������ɫ��
	unsigned int vertexShader;
	//���� Ƭ����ɫ��
	unsigned int fragmentShader;
	//�洢 ��ɫ������
	unsigned int shaderProgram;

	void drawMyGraph() {
		FragmentShaderInit();
		vertexShaderInit();

		shaderProgramLinker();
		vertexInput();
	}
private:
	void vertexInput() {
		glGenBuffers(1, &VBO);
		glGenVertexArrays(1, &VAO);

		// 1. ��VAO , VBO
		glBindVertexArray(VAO);

		// 2. ���ƶ������鵽�����й�OpenGLʹ��
		//��������� �󶨵�GL_ARRAY_BUFFERĿ��
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		//���嶥�����ݸ��Ƶ������ڴ�
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		// 3. ���ö�������ָ��
		//������������
		//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		// position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		// color attribute
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
	}

	void vertexShaderInit() {
		//����һ��������ɫ������
		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		//��ɫ��Դ�븽�ŵ���ɫ��������
		glShaderSource(vertexShader, 1, &scvertexShaderSource, NULL);
		//������ɫ������
		glCompileShader(vertexShader);

		//�����ɫ�����Ƿ�ɹ�
		int success;
		char infoLog[50];
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		}
	}

	void FragmentShaderInit() {
		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &scfragmentShaderSource, NULL);
		glCompileShader(fragmentShader);
		//�����ɫ�����Ƿ�ɹ�
		int success;
		char infoLog[50];
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		}
	}

	void shaderProgramLinker() {
		//������ɫ���������
		shaderProgram = glCreateProgram();
		//������ɫ������ɫ������
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);
		int success;
		char infoLog[50];
		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::LINKE_PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
		}
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}

};

//1
int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//return 0; ?? 
	//create the window
	GLFWwindow* window = glfwCreateWindow(800, 600, "Zhang Yuefei 11713021", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	//3
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	//4
	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	Triangle myTriangle;
	myTriangle.drawMyGraph();
	SomeColorTriangle myscTriangle;
	myscTriangle.drawMyGraph();
	
	//enter game loop
	while (!glfwWindowShouldClose(window))
	{ //���봦��
		processInput(window);

		//��Ⱦָ��
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// 4. ��������Ⱦһ������ʱҪʹ����ɫ������
		glUseProgram(myTriangle.shaderProgram);
		glBindVertexArray(myTriangle.VAO);
		// 3. ��������
		glDrawArrays(GL_TRIANGLES, 0, 3);
		// 4. ��������Ⱦһ������ʱҪʹ����ɫ������
		glUseProgram(myscTriangle.shaderProgram);
		glBindVertexArray(myscTriangle.VAO);
		// 3. ��������
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &myTriangle.VAO);
	glDeleteBuffers(1, &myTriangle.VBO);
	glfwTerminate();
	return 0;
}


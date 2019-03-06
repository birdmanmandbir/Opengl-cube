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
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp> 
//#include "shaders.h"
using namespace std;
void processInput(GLFWwindow* window);
char* readTheFile(string strSource);
const char* fragmentShaderSource = readTheFile("shader.frag");
const char* vertexShaderSource = readTheFile("shader.vert");
const char* scfragmentShaderSource = readTheFile("someColorShader.frag");
const char* scvertexShaderSource = readTheFile("someColorShader_MVP.vert");


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
	float vertices[216] = {


  -1.0f,-1.0f,-1.0f, 0.583f,  0.771f,  0.014f,// triangle 1 : begin
	-1.0f,-1.0f, 1.0f,  0.609f,  0.115f,  0.436f,
	-1.0f, 1.0f, 1.0f,  0.327f,  0.483f,  0.844f,// triangle 1 : end
	1.0f, 1.0f,-1.0f, 0.822f,  0.569f,  0.201f, // triangle 2 : begin
	-1.0f,-1.0f,-1.0f,    0.435f,  0.602f,  0.223f,
	-1.0f, 1.0f,-1.0f,0.310f,  0.747f,  0.185f, // triangle 2 : end
	1.0f,-1.0f, 1.0f, 0.597f,  0.770f,  0.761f,
	-1.0f,-1.0f,-1.0f,0.559f,  0.436f,  0.730f,
	1.0f,-1.0f,-1.0f,0.359f,  0.583f,  0.152f,
	1.0f, 1.0f,-1.0f,0.483f,  0.596f,  0.789f,
	1.0f,-1.0f,-1.0f,0.559f,  0.861f,  0.639f,
	-1.0f,-1.0f,-1.0f,0.195f,  0.548f,  0.859f,
	-1.0f,-1.0f,-1.0f,0.014f,  0.184f,  0.576f,
	-1.0f, 1.0f, 1.0f,0.771f,  0.328f,  0.970f,
	-1.0f, 1.0f,-1.0f,0.406f,  0.615f,  0.116f,
	1.0f,-1.0f, 1.0f,0.676f,  0.977f,  0.133f,
	-1.0f,-1.0f, 1.0f,0.971f,  0.572f,  0.833f,
	-1.0f,-1.0f,-1.0f,0.140f,  0.616f,  0.489f,
	-1.0f, 1.0f, 1.0f,0.997f,  0.513f,  0.064f,
	-1.0f,-1.0f, 1.0f, 0.945f,  0.719f,  0.592f,
	1.0f,-1.0f, 1.0f,0.543f,  0.021f,  0.978f,
	1.0f, 1.0f, 1.0f, 0.279f,  0.317f,  0.505f, 
	1.0f,-1.0f,-1.0f, 0.167f,  0.620f,  0.077f,
	1.0f, 1.0f,-1.0f,0.347f,  0.857f,  0.137f,
	1.0f,-1.0f,-1.0f,0.055f,  0.953f,  0.042f,
	1.0f, 1.0f, 1.0f,0.714f,  0.505f,  0.345f,
	1.0f,-1.0f, 1.0f,0.783f,  0.290f,  0.734f,
	1.0f, 1.0f, 1.0f,0.722f,  0.645f,  0.174f,
	1.0f, 1.0f,-1.0f,0.302f,  0.455f,  0.848f,
	-1.0f, 1.0f,-1.0f,0.225f,  0.587f,  0.040f,
	1.0f, 1.0f, 1.0f,0.517f,  0.713f,  0.338f,
	-1.0f, 1.0f,-1.0f,0.053f,  0.959f,  0.120f,
	-1.0f, 1.0f, 1.0f,0.393f,  0.621f,  0.362f,
	1.0f, 1.0f, 1.0f,0.673f,  0.211f,  0.457f,
	-1.0f, 1.0f, 1.0f,0.820f,  0.883f,  0.371f,
	1.0f,-1.0f, 1.0f,0.982f,  0.099f,  0.879f

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
		char infoLog[100];
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
		char infoLog[100];
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
	//class
	Triangle myTriangle;
	myTriangle.drawMyGraph();
	SomeColorTriangle myscTriangle;
	myscTriangle.drawMyGraph();
	//MVP
	// Projection matrix : 45�� Field of View, 4 : 3 ratio, display range : 0.1 unit < -> 100 units
	glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);

	// Or, for an ortho camera :
	//glm::mat4 Projection = glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f); // In world coordinates

	// Camera matrix
	glm::mat4 View = glm::lookAt(
		glm::vec3(-4, -4, -4), // Camera is at (4,3,3), in World Space
		glm::vec3(0, 0, 0), // and looks at the origin
		glm::vec3(2, -1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
	);

	// Model matrix : an identity matrix (model will be at the origin)
	glm::mat4 Model = glm::mat4(1.0f);
	// Our ModelViewProjection : multiplication of our 3 matrices
	glm::mat4 mvp = Projection * View * Model; // Remember, matrix multiplication is the other way around
	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);
	// Get a handle for our "MVP" uniform
	// Only during the initialisation
	GLuint MatrixID = glGetUniformLocation(myscTriangle.shaderProgram, "MVP");


	//4
	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


	//enter game loop
	while (!glfwWindowShouldClose(window))
	{ //���봦��
		processInput(window);

		//��Ⱦָ��
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);

		//// 4. ��������Ⱦһ������ʱҪʹ����ɫ������
		//glUseProgram(myTriangle.shaderProgram);

		//glBindVertexArray(myTriangle.VAO);
		//// 3. ��������
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		// 4. ��������Ⱦһ������ʱҪʹ����ɫ������
		glUseProgram(myscTriangle.shaderProgram);
		// Send our transformation to the currently bound shader, in the "MVP" uniform
		// This is done in the main loop since each model will have a different MVP matrix (At least for the M part)
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);
		glBindVertexArray(myscTriangle.VAO);
		// 3. ��������
		glDrawArrays(GL_TRIANGLES, 0, 3*12);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &myTriangle.VAO);
	glDeleteBuffers(1, &myTriangle.VBO);
	glfwTerminate();
	return 0;
}


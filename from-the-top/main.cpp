#include <iostream>
#include <fstream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// forward declaration
void processInput(GLFWwindow* window);
int init(GLFWwindow*& window);
bool loadFile(const char* filename, char*& output);

GLuint simpleProgram;

const int WIDTH = 1280;
const int HEIGHT = 720;

int main() {

	GLFWwindow* window;
	int result = init(window);
	if (result != 0) {
		return result;
	}

	// create viewport
	//glViewport(0, 0, 1280, 720);
	glUseProgram(simpleProgram);
	glUniform2f(glGetUniformLocation(simpleProgram, "iResolution"), WIDTH, HEIGHT);
	

	float vertices[] = {
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f
	};


	// create vertex buffer object
	GLuint VBO;
	glGenBuffers(1, &VBO);

	// bind buffer object to GL_ARRAY_BUFFER target
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// input data into the buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	// create vertex shader
	GLuint vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	// load shader data from file and input into vertex shader object
	char* vertexSrc;
	loadFile("shaders/vertex.shader", vertexSrc);
	glShaderSource(vertexShader, 1, &vertexSrc, nullptr);

	// compile vertex shader and check if compilation was successful
	glCompileShader(vertexShader);

	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// now same thing but for the fragment shader
	GLuint fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	char* fragmentSrc;
	loadFile("shaders/fragment.shader", fragmentSrc);
	glShaderSource(fragmentShader, 1, &fragmentSrc, nullptr);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// create a program and attach the shaders to it
	GLuint shaderProgram;
	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);


	// delete shaders and file paths from memory
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	delete vertexSrc;
	delete fragmentSrc;



	// game render loop
	while (!glfwWindowShouldClose(window)) {

		processInput(window);

		glClearColor(0.0, 0.5, 0.3, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	// terminate
	glfwTerminate();

	return 0;
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

int init(GLFWwindow*& window) {
	glfwInit();

	// tell glfw which profile & openGL version to use
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// make window
	window = glfwCreateWindow(WIDTH, HEIGHT, "hku-graphics", nullptr, nullptr);
	if (window == nullptr) {
		std::cout << "failed to create GLFW window" << std::endl;
		return -1;
	}

	// set context
	glfwMakeContextCurrent(window);

	// GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to load GLAD" << std::endl;
		glfwTerminate();
		return -2;
	}
	return 0;
}


bool loadFile(const char* filename, char*& output) {
	std::ifstream file(filename, std::ios::binary);
	if (!file.is_open()) {
		std::cerr << "Failed to open file: " << filename << std::endl;
		return false;
	}

	// Get the length of the file
	file.seekg(0, file.end);
	int length = file.tellg();
	file.seekg(0, file.beg);

	// Allocate memory for the text
	output = new char[length + 1]; // +1 for null terminator

	// Read the file into the buffer
	file.read(output, length);
	output[length] = '\0'; // Add null terminator

	// Close the file
	file.close();

	return true;
}
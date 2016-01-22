#include <iostream>
#include <iostream>
#include <math.h>
#include <string>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "shader.h"
#include "SOIL.h"

extern glm::mat4 MVP,View,Projection;

class Renderer
{
	private:
		GLfloat vertices[12];
    	GLuint indices[6];
    	float length,width;
	public:
		GLuint VBO,VAO,EBO;
		Renderer(GLfloat Length,GLfloat Width);
		void draw(glm::mat4 Model);
		void initArrays();
		void clearBuffers();
};

Renderer::Renderer(GLfloat Length,GLfloat Width)
{
	length = Length;
	width = Width;
	initArrays();
	glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0); //glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

    glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)
}

void Renderer::initArrays()
{
	vertices[0] =  width/2; vertices[1]  =  length/2; vertices[2]  = 0.0f;
	vertices[3] =  width/2; vertices[4]  = -length/2; vertices[5]  = 0.0f;
	vertices[6] = -width/2; vertices[7]  = -length/2; vertices[8]  = 0.0f;
	vertices[9] = -width/2; vertices[10] =  length/2; vertices[11] = 0.0f;
	
	indices[0] = 0; indices[1] = 1; indices[2] = 3;
	indices[3] = 1; indices[4] = 2; indices[5] = 3;
}

void Renderer::draw(glm::mat4 Model)
{
	Shader ourShader("basic.vs", "basic.frag");
	ourShader.Use();
	glm::mat4 MVP;
	MVP = Projection * View * Model;
    GLint MVPLoc = glGetUniformLocation(ourShader.Program, "MVP");
    glUniformMatrix4fv(MVPLoc, 1, GL_FALSE, glm::value_ptr(MVP));
    GLint vertexColorLocation = glGetUniformLocation(ourShader.Program, "ourColor");
	glUniform4f(vertexColorLocation, 1.0f, 0.8f, 0.4f, 1.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Renderer::clearBuffers()
{
	glDeleteVertexArrays(1,&VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}


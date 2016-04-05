#include <iostream>
#include <iostream>
#include <math.h>
#include <string>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "shader.h"

extern glm::mat4 MVP,View,Projection;

class PedestrianRenderer
{
	private:
		GLfloat vertices[24]={
		 30.00f,  30.0f, 0.0f, 1.0f, 0.0f, 0.0f,
         30.00f, -30.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        -30.00f, -30.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        -30.00f,  30.0f, 0.0f, 1.0f, 1.0f, 0.0f};
    	GLuint indices[6]={
    	0,1,3,
    	1,2,3};
    	float rValue,gValue,bValue;
	public:
		GLuint VBO,VAO,EBO;
		PedestrianRenderer();
		void draw(glm::mat4 Model);
		void clearBuffers();
		Shader *ourShader;
};

PedestrianRenderer::PedestrianRenderer()
{
	rValue = ((float) rand()) / (float) RAND_MAX;
	gValue = ((float) rand()) / (float) RAND_MAX;
	bValue = ((float) rand()) / (float) RAND_MAX;
	glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    
    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)
    ourShader = new Shader("basic.vs", "basic.frag");
}

void PedestrianRenderer::draw(glm::mat4 Model)
{	
	ourShader->Use();
	glm::mat4 MVP;
	MVP = Projection * View * Model;
    GLint MVPLoc = glGetUniformLocation(ourShader->Program, "MVP");
    glUniformMatrix4fv(MVPLoc, 1, GL_FALSE, glm::value_ptr(MVP));
    
    GLint vertexColorLocation = glGetUniformLocation(ourShader->Program, "ourColor");
	glUniform4f(vertexColorLocation, rValue, gValue, bValue, 1.0f);
    glBindVertexArray(VAO);
    
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void PedestrianRenderer::clearBuffers()
{
	glDeleteVertexArrays(1,&VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}


#include <iostream>
#include <iostream>
#include <math.h>
#include <string>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "shader.h"

extern glm::mat4 MVP,View,Projection;

class WallRenderer
{
	private:
		GLfloat vertices[24];
		GLuint indices[6]={0,1,3,	1,2,3};
    	GLfloat length;
	public:
		GLuint VBO,VAO,EBO;
		WallRenderer(GLfloat LENGTH);
		Shader* ourShader;
		void draw(glm::mat4 Model);
		void initArrays();
		void clearBuffers();
};

WallRenderer::WallRenderer(GLfloat LENGTH) : vertices{LENGTH/2,  10.5f, 0.0f, 1.0f, 0.0f, 0.0f,
										         LENGTH/2, -10.5f, 0.0f, 0.0f, 1.0f, 0.0f,
												-LENGTH/2, -10.5f, 0.0f, 0.0f, 0.0f, 1.0f,
										        -LENGTH/2,  10.5f, 0.0f, 1.0f, 1.0f, 0.0f}
{
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

void WallRenderer::draw(glm::mat4 Model)
{
	ourShader->Use();
	glm::mat4 MVP;
	MVP = Projection * View * Model;
    GLint MVPLoc = glGetUniformLocation(ourShader->Program, "MVP");
    glUniformMatrix4fv(MVPLoc, 1, GL_FALSE, glm::value_ptr(MVP));
    
    GLint vertexColorLocation = glGetUniformLocation(ourShader->Program, "ourColor");
	glUniform4f(vertexColorLocation, 1.0f, 0.8f, 0.4f, 1.0f);
    
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void WallRenderer::clearBuffers()
{
	delete ourShader;
	glDeleteVertexArrays(1,&VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}


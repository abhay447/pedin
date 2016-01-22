#version 330 core
layout (location = 0) in vec3 position;

uniform mat4 transform;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 Model;
uniform mat4 MVP;

void main()
{
    gl_Position = MVP * vec4(position, 1.0f);
    //ourColor = color;
}

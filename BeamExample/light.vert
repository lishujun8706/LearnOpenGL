#version 330 core
layout(location = 0) in vec3 aPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 perject;

void main(){
    gl_Position = perject * view * model * vec4(aPos, 1.0f);
}

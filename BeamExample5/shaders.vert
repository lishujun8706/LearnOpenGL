#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal; // 法向量
layout(location = 2) in vec2 aTexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 perject;

out vec3 FragPos;
out vec3 Normal;

out vec2 TexCoords;

void main(){
    gl_Position = perject * view * model * vec4(aPos, 1.0f);
    FragPos = vec3(model * vec4(aPos, 1.0)); // 通过把顶点位置属性乘以模型矩阵来把它变换到世界空间坐标
//    Normal = aNormal;
    Normal = mat3(transpose(inverse(model))) * aNormal;
    TexCoords = aTexCoords;
}

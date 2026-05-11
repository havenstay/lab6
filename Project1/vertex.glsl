#version 460 core
layout (location = 0) in vec3 vp;
layout (location = 1) in vec3 aNormal;
uniform mat4 yPos;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 transform;
out vec3 Normal;
void main()
{
    gl_Position = projection * view * model * transform * vec4(vp.x, vp.y, vp.z, 1.0);
    Normal = aNormal;
} 
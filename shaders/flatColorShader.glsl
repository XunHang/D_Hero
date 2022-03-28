#type vertex
#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;
layout (location = 2) in vec2 a_Tex;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 vp;

out vec4 m_Color;
out vec2 texCoord;

void main () {
    m_Color = a_Color;
    //gl_Position = projection * view * model * vec4(a_Position, 1.0);
    gl_Position = vp * model * vec4(a_Position, 1.0);
    texCoord = a_Tex;
}

#type fragment
#version 330 core
    
in vec4 m_Color;

out vec4 color;

void main () {
    color = m_Color;
}
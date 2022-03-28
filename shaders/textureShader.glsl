#type vertex
#version 330 core
		
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_Tex;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 vp;

out vec2 texCoord;

void main () {
    //gl_Position = projection * view * model * vec4(a_Position, 1.0);
    gl_Position = vp * model * vec4(a_Position, 1.0);
    texCoord = a_Tex;
}

#type fragment
#version 330 core
    
in vec2 texCoord;
uniform sampler2D ourTexture;

out vec4 color;

void main () {
    color = texture(ourTexture, texCoord);
}
#type vertex
#version 330 core
		
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_Tex;

uniform mat4 u_VPmatrix;
uniform vec4 u_Color;
uniform mat4 u_Transform;

out vec2 texCoord;
out vec4 color;

void main () {
    //gl_Position = projection * view * model * vec4(a_Position, 1.0);
    gl_Position = u_VPmatrix * u_Transform * vec4(a_Position, 1.0);
    texCoord = a_Tex;
    color = u_Color;
}

#type fragment
#version 330 core
    
in vec4 color;
in vec2 texCoord;
uniform sampler2D ourTexture;

out vec4 FragmentColor;

void main () {
    FragmentColor = texture(ourTexture, texCoord) * color;
}
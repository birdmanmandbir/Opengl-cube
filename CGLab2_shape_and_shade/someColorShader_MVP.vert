#version 330 core
layout (location = 0) in vec3 aPos;   // the position variable has attribute position 0
layout (location = 1) in vec3 aNormal;
out vec3 Normal;
out vec3 FragPos;
uniform mat4 MVP;
uniform mat4 model;
void main()
{
    FragPos = vec3(model * vec4(aPos, 1.0));//ÎªÊ²Ã´ÊÇvec3
    gl_Position = MVP * vec4(aPos,1.0);
	Normal = aNormal;
}

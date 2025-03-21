#version 460 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;

uniform float time;

out vec3 color;
void main()
{
   gl_Position = vec4(aPos.x,aPos.y,aPos.z, 1.0);
   color = aColor * (cos(time) + 1.0) / 2.0;
}

/*动态分配
#version 460 core
in vec3 aPos;
in vec3 aColor;
out vec3 color;
void main()
{
    gl_Position = vec4(aPos.x,aPos.y,aPos.z, 1.0);
    color = aColor;
}*/
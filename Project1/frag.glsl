#version 460 core
in vec3 Normal;
out vec4 frag_colour;
uniform vec3 lightColor;
void main()
{
    float light = max(dot(normalize(Normal), normalize(vec3(1,1,1))), 0.2);

    vec3 color = lightColor * light;

    frag_colour = vec4(color, 1.0);
}
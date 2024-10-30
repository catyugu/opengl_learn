#version 330 core
in vec3 ourColor;
in vec2 TexCoord;
out vec4 color;
// Texture samplers
uniform sampler2D ourTexture1;

void main()
{
    // Linearly interpolate between both textures (second texture is only slightly combined)
    color = mix(texture(ourTexture1, TexCoord), vec4(ourColor, 1.0), 0.2);
}
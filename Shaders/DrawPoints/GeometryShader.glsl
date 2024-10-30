#version 330 core
layout (points) in;
layout (triangle_strip, max_vertices = 56) out;

uniform float pointRadius;
void draw(vec4 position) {

    int numSegments = 27;
    float angleStep = 2 * 3.1415926535 / numSegments;
    for (int i = 0; i <= numSegments; i++) {
        float angle = i * angleStep;
        gl_Position = position;
        EmitVertex();
        gl_Position = position+vec4(cos(angle) * pointRadius, sin(angle) * pointRadius, 0.0f, 0.0f);
        EmitVertex();
    }

    EndPrimitive();
}
void main(){
    draw(gl_in[0].gl_Position);
}
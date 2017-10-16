#version 150
precision mediump float;

uniform sampler2DRect uImg;

in vec2 vTexCoord;
out vec4 outputColor;

void main() {
    outputColor = texture(uImg, vTexCoord);
    // outputColor = vec4(vTexCoord.x, vTexCoord.y, 0.5, 0.1);
    // outputColor = vec4(1.0);
}

#version 120

uniform mat4 view;
uniform mat4 TM; // Scales coordinates to (-1, 1) range

attribute vec4 vertexCoordinates;
attribute vec2 textureCoordinates;

varying vec2 texturePosition;

void main()
{
   gl_Position = view * vertexCoordinates;
   texturePosition = vec2(TM * vec4(textureCoordinates, 0, 1));
   texturePosition.y = 1.0 - texturePosition.y;
}
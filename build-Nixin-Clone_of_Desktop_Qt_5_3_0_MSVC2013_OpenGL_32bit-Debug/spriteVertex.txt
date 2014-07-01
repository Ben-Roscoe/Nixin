#version 400

in vec3					vertexPosition;
in vec2					texCoords;
in vec4					tint;


out vec2				fragTexCoords;
out vec4				fragTint;

uniform mat4			projection;


//
// main
//
void main()
{
	fragTexCoords = texCoords;
	fragTint = tint;
	gl_Position = projection * vec4( vertexPosition.xy, 0.2f, 1.0f );
}
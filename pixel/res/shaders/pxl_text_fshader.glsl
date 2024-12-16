#version 330 core
out vec4 FragColor;
in vec2 TexCoords;
uniform sampler2D text;
uniform vec4 textColor;

void main()
{
    float alpha = texture(text, TexCoords).r; // Use the red channel for grayscale texture
    FragColor = textColor * alpha; // Apply the text color
    if (alpha < 0.1)
        discard; // Discard transparent pixels
}
#version 330 core
out vec4 FragColor;
uniform vec4 ourColor;
in vec3 ourColor2;
in vec2 textcoord;
uniform sampler2D texture1;
uniform sampler2D texture2;
void main(){
    // FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
    // FragColor = ourColor;
//    FragColor = vec4(ourColor2, 1.0f);
//    FragColor = texture(texture1, textcoord);
//    FragColor = texture(texture2, textcoord)*vec4(1.0f, 0.0f, 0.0f, 1.0f);
    FragColor = mix(texture(texture1, textcoord), texture(texture2, textcoord), 0.2);
}

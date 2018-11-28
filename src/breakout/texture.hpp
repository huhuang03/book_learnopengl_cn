#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Texture2D {
public:
    // Holds the ID of the texture object, used for all texture operations to reference to this particlar texture
    GLuint ID;
    GLuint Width, Height;
    GLuint Internal_Format;
    GLuint Image_Format;
    GLuint Wrap_S;
    GLuint Wrap_T;
    GLuint Filter_Min;
    GLuint Filter_Max;

    Texture2D();
    void Generate(GLuint width, GLuint height, unsigned char *data);
    // Binds the texture as the current active GL_TEXTURE_2D texture object
    void Bind() const;
};

#endif /* TEXTURE_H */

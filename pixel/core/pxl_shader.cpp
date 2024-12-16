#include "pxl_shader.h"

#include <fstream>
#include <sstream>
#include <iostream>

#include "glm/gtc/type_ptr.hpp"

using Shader = pixel::Shader;

bool Shader::Initialize(const char* vshader_path, const char* fshader_path)
{
    GLuint vshader = compileShader(vshader_path, GL_VERTEX_SHADER);
    GLuint fshader = compileShader(fshader_path, GL_FRAGMENT_SHADER);
   
    m_Id = glCreateProgram();

    glAttachShader(m_Id, vshader);
    glAttachShader(m_Id, fshader);
    glLinkProgram(m_Id);

    checkCompileErrors(m_Id, true);
    
    glDeleteShader(vshader);
    glDeleteShader(fshader);

	return true;
}

void Shader::SetVec3(const char* name, const glm::vec3& value) const
{
    glUniform3fv(glGetUniformLocation(m_Id, name), 1, glm::value_ptr(value));
}

void Shader::SetVec4(const char* name, const glm::vec4& value) const
{
    glUniform4fv(glGetUniformLocation(m_Id, name), 1, glm::value_ptr(value));
}

void Shader::SetMat4(const char* name, const glm::mat4& value) const
{
    glUniformMatrix4fv(glGetUniformLocation(m_Id, name), 1, GL_FALSE, glm::value_ptr(value));
}

GLuint Shader::compileShader(const char* shader_path, GLenum shader_type)
{
    std::string shader_code;
    std::ifstream shader_file;

    try
    {
        shader_file.open(std::string(shader_path));

        std::stringstream shaderstream;

        shaderstream << shader_file.rdbuf();

        shader_file.close();

        shader_code = shaderstream.str();
    }
    catch (std::ifstream::failure& e)
    {
        std::cerr << "Error(Shader): Couldn't read shader at " << shader_path << "\n";
        std::cerr << "\t" << e.what() << "\n";
        return false;
    }

    const char* code_cstr = shader_code.c_str();
    GLuint shader = glCreateShader(shader_type);
    glShaderSource(shader, 1, &code_cstr, NULL);
    glCompileShader(shader);

    checkCompileErrors(shader, false);

    return shader;
}

void Shader::checkCompileErrors(GLuint shader, bool is_program)
{
    GLint success;
    GLchar log[1024];

    if (!is_program)
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (success) return;
        
        glGetShaderInfoLog(shader, 1024, NULL, log);
        std::cout << "ERROR(Shader) : " << log << "\n";
        
        return;
    }
    
    glGetProgramiv(shader, GL_LINK_STATUS, &success);
    if (success) return;
        
    glGetProgramInfoLog(shader, 1024, NULL, log);
    std::cout << "ERROR(Shader) : " << log << "\n";
}

void Shader::Use()
{
    glUseProgram(m_Id);
}
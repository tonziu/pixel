#ifndef H_PIXEL_SHADER
#define H_PIXEL_SHADER

#include "glad/glad.h"
#include <glm/glm.hpp>

namespace pixel
{
	class Shader
	{
	public:
		Shader() = default;

		bool Initialize(const char* vshader_path, const char* fshader_path);

		void Use();

		void SetVec3(const char* name, const glm::vec3& value) const;
		void SetVec4(const char* name, const glm::vec4& value) const;

		void SetMat4(const char* name, const glm::mat4& value) const;

	private:
		GLuint m_Id;

		GLuint compileShader(const char* shader_path, GLenum shader_type);
		void checkCompileErrors(GLuint shader, bool is_program);
	};
}

#endif // H_PIXEL_SHADER
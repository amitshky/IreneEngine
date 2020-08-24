#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace irene {

	struct ShaderProgramSource
	{
		std::string VertexSource;
		std::string FragmentSource;
	};

	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		// set uniform
		virtual void SetInt(const std::string & name, int value) = 0;
		virtual void SetIntArray(const std::string & name, int* values, uint32_t) = 0;
		virtual void SetFloat(const std::string & name, float value) = 0;
		virtual void SetFloat2(const std::string & name, const glm::vec2 & value) = 0;
		virtual void SetFloat3(const std::string & name, const glm::vec3 & value) = 0;
		virtual void SetFloat4(const std::string & name, const glm::vec4 & value) = 0;
		virtual void SetMat4(const std::string & name, const glm::mat4 & value) = 0;

		static Ref<Shader> Create(const std::string & filepath);
	};

}

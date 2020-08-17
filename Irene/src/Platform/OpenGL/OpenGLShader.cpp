#include "pch.h"
#include "OpenGLShader.h"

#include <glad/glad.h>

namespace irene {

	OpenGLShader::OpenGLShader(const std::string& filepath)
		: m_Filepath(filepath)
	{
		ShaderProgramSource source = ParseShader(filepath);
		m_RendererID = CreateShader(source.VertexSource, source.FragmentSource);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RendererID);
	}

	ShaderProgramSource OpenGLShader::ParseShader(const std::string& filepath)
	{
		std::ifstream stream(filepath);

		enum class ShaderType
		{
			NONE = -1, VERTEX = 0, FRAGMENT = 1
		};

		std::string line;
		std::stringstream ss[2];	//stringstream array for vertex and fragment shader
		ShaderType type = ShaderType::NONE;
		while (getline(stream, line))
		{
			if (line.find("#shader") != std::string::npos)	//std::string::npos => invalid string position	//returns the position of the string
			{
				if (line.find("vertex") != std::string::npos)
					type = ShaderType::VERTEX;
				else if (line.find("fragment") != std::string::npos)
					type = ShaderType::FRAGMENT;
			}
			else		//for every other line add to the vertex or the fragment shader
			{
				ss[(int)type] << line << '\n';	//move the strings to the buffer
			}
		}

		stream.close();
		return { ss[0].str(), ss[1].str() };
	}

	unsigned int OpenGLShader::CompileShader(unsigned int type, const std::string& source)
	{
		unsigned int id = glCreateShader(type);	// Creates an empty shader object and returns a non-zero value to be referenced
		const char* src = source.c_str();	// returns a pointer to the begining of our data
		glShaderSource(id, 1, &src, nullptr);	//Sets the source code in the shader to the source code in the array of strings
		glCompileShader(id);

		// Error Handling
		int result;	// to check if our shader compiled properly 
		glGetShaderiv(id, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE)		// if(!result)
		{
			// get the error message
			char message[512];
			glGetShaderInfoLog(id, 512, NULL, message);
			std::cout << "Failed To Compile " << (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment") << " Shader!" << std::endl;
			std::cout << message << std::endl;
			glDeleteShader(id);
			return 0;
		}

		return id;
	}

	unsigned int OpenGLShader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
	{
		unsigned int program = glCreateProgram();	// create a shader program	// we can attach the shader object to it
		// compiling
		unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
		unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

		// linking
		glAttachShader(program, vs);
		glAttachShader(program, fs);
		glLinkProgram(program);
		glValidateProgram(program);

		// delete the intermediates
		glDeleteShader(vs);
		glDeleteShader(fs);

		return program;
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(m_RendererID);
	}

	void OpenGLShader::Unbind() const
	{
		glUseProgram(0);
	}

	int OpenGLShader::GetUniformLocation(const std::string& name)
	{
		if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
			return m_UniformLocationCache[name];
		int location = glGetUniformLocation(m_RendererID, name.c_str());
		if (location == -1)
			std::cout << "Warning: uniform '" << name << "' doesn't exist!" << std::endl;

		m_UniformLocationCache[name] = location;
		return location;
	}

	void OpenGLShader::SetInt(const std::string& name, int value)
	{
		UploadUniformInt(name, value);
	}

	void OpenGLShader::SetIntArray(const std::string& name, int* values, uint32_t count)
	{
		UploadUniformIntArray(name, values, count);
	}

	void OpenGLShader::SetFloat(const std::string& name, float value)
	{
		UploadUniformFloat(name, value);
	}

	void OpenGLShader::SetFloat3(const std::string& name, const glm::vec3& value)
	{
		UploadUniformFloat3(name, value);
	}

	void OpenGLShader::SetFloat4(const std::string& name, const glm::vec4& value)
	{
		UploadUniformFloat4(name, value);
	}

	void OpenGLShader::SetMat4(const std::string& name, const glm::mat4& value)
	{
		UploadUniformMat4(name, value);
	}

	void OpenGLShader::UploadUniformInt(const std::string& name, int value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1i(location, value);
	}

	void OpenGLShader::UploadUniformIntArray(const std::string& name, int* values, uint32_t count)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1iv(location, count, values);
	}

	void OpenGLShader::UploadUniformFloat(const std::string& name, float value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1f(location, value);
	}

	void OpenGLShader::UploadUniformFloat2(const std::string& name, const glm::vec2& value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform2f(location, value.x, value.y);
	}

	void OpenGLShader::UploadUniformFloat3(const std::string& name, const glm::vec3& value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform3f(location, value.x, value.y, value.z);
	}

	void OpenGLShader::UploadUniformFloat4(const std::string& name, const glm::vec4& value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform4f(location, value.x, value.y, value.z, value.w);
	}

	void OpenGLShader::UploadUniformMat3(const std::string& name, const glm::mat3& matrix)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix)
	{
		// bind the program before uploading the matrix
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

}

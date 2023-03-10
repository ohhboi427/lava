#include "pch.h"
#include "shader.h"

#include "../resource/resource_manager.h"
#include "../resource/text_file.h"

#include <glad/gl.h>

namespace lava
{
	shader::shader(const std::filesystem::path& path)
		: resource(path)
	{
		static constexpr std::array<shader_stage, 2u> s_stages =
		{
			shader_stage::vertex,
			shader_stage::fragment,
		};

		std::filesystem::path source_path(m_path);
		source_path += ".temp";

		std::unordered_map<shader_stage, std::shared_ptr<text_file>> source_files;
		for(const auto& stage : s_stages)
		{
			source_path.replace_extension(stage_to_extension(stage));
			source_files.insert({ stage, resource_manager::get<text_file>(source_path) });
		}

		m_handle = glCreateProgram();

		std::vector<uint32_t> shaders;
		for(const auto& [stage, source] : source_files)
		{
			uint32_t shader = shaders.emplace_back(glCreateShader((uint32_t)stage));

			const char* source_cstr = source->cdata().c_str();
			glShaderSource(shader, 1, &source_cstr, nullptr);

			glCompileShader(shader);

			glAttachShader(m_handle, shader);
		}

		glLinkProgram(m_handle);

		for(const auto& shader : shaders)
		{
			glDeleteShader(shader);
		}
	}

	shader::~shader()
	{
		glDeleteProgram(m_handle);
	}

	std::filesystem::path shader::stage_to_extension(shader_stage stage)
	{
		switch(stage)
		{
		case shader_stage::vertex:
			return "vert";
		case shader_stage::fragment:
			return "frag";
		}

		return "invalid";
	}
}

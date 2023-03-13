#include "pch.h"
#include "shader_library.h"

#include "shader.h"
#include "../resource/text_file.h"
#include "../resource/resource_manager.h"

#include <glad/gl.h>
#include <nlohmann/json.hpp>

namespace lava
{
	namespace
	{
		enum class shader_stage : uint32_t
		{
			vertex = 35633u,
			fragment = 35632u,
		};

		std::unordered_map<std::filesystem::path, shader*> s_shaders;

		std::string stage_to_str(shader_stage stage)
		{
			switch(stage)
			{
			case shader_stage::vertex:
				return "vertex";
			case shader_stage::fragment:
				return "fragment";
			}

			return "invalid";
		}

		shader* compile_shader(const std::filesystem::path& path)
		{
			static constexpr std::array<shader_stage, 2u> s_stages =
			{
				shader_stage::vertex,
				shader_stage::fragment,
			};

			std::ifstream file(path);
			nlohmann::json shader_description = nlohmann::json::parse(file);
			file.close();

			std::filesystem::path directory = path.parent_path();

			std::unordered_map<shader_stage, std::shared_ptr<text_file>> source_files;
			for(const auto& stage : s_stages)
			{
				source_files.insert({ stage, resource_manager::get<text_file>(directory / shader_description.at(stage_to_str(stage))) });
			}

			uint32_t handle = glCreateProgram();

			std::vector<uint32_t> shaders;
			for(const auto& [stage, source] : source_files)
			{
				uint32_t& shader = shaders.emplace_back(glCreateShader((uint32_t)stage));

				const char* source_cstr = source->cdata().c_str();
				glShaderSource(shader, 1, &source_cstr, nullptr);

				glCompileShader(shader);

				glAttachShader(handle, shader);
			}

			glLinkProgram(handle);

			for(const auto& shader : shaders)
			{
				glDeleteShader(shader);
			}

			return new shader(handle);
		}
	}

	void shader_library::load_all(const std::filesystem::path& directory)
	{
		for(const auto& entry : std::filesystem::directory_iterator(directory))
		{
			std::filesystem::path path = entry.path();
			if(path.has_extension() && path.extension() == ".json")
			{
				load(path);
			}
		}
	}

	void shader_library::load(const std::filesystem::path& path)
	{
		shader* new_shader = compile_shader(path);
		s_shaders.insert({ path, new_shader });
	}

	void shader_library::purge_cache()
	{
		for(const auto& [path, shader] : s_shaders)
		{
			glDeleteProgram(*shader);
			delete shader;
		}

		s_shaders.clear();
	}

	shader& shader_library::get(const std::filesystem::path& path)
	{
		if(s_shaders.contains(path))
		{
			return *(s_shaders.at(path));
		}

		shader* new_shader = compile_shader(path);
		s_shaders.insert({ path, new_shader });

		return *new_shader;
	}
}

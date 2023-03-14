#pragma once

#include "../resource/resource.h"

#include <filesystem>
#include <vector>
#include <cstdint>

#include <glm/glm.hpp>

namespace lava
{
	class buffer;

	class mesh : public resource
	{
	public:
		std::vector<glm::vec3> positions;
		std::vector<glm::vec3> normals;
		std::vector<glm::vec2> uvs;
		std::vector<uint32_t> indices;

		mesh();
		~mesh();

		operator uint32_t () const { return m_vao_handle; }

		void apply();

	private:
		uint32_t m_vao_handle;
		buffer* m_positions_buffer;
		buffer* m_normals_buffer;
		buffer* m_uvs_buffer;
		buffer* m_indices_buffer;
	};
}

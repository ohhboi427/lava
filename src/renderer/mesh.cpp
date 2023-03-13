#include "pch.h"
#include "mesh.h"

#include "buffer.h"

#include <glad/gl.h>

namespace lava
{
	mesh::mesh()
	{
		glCreateVertexArrays(1, &m_vao_handle);

		m_positions_buffer = new buffer();
		glEnableVertexArrayAttrib(m_vao_handle, 0u);
		glVertexArrayAttribBinding(m_vao_handle, 0u, 0u);
		glVertexArrayAttribFormat(m_vao_handle, 0u, 3, GL_FLOAT, GL_FALSE, 0u);
		glVertexArrayVertexBuffer(m_vao_handle, 0u, *m_positions_buffer, 0, sizeof(glm::vec3));

		m_normals_buffer = new buffer();
		glEnableVertexArrayAttrib(m_vao_handle, 1u);
		glVertexArrayAttribBinding(m_vao_handle, 1u, 1u);
		glVertexArrayAttribFormat(m_vao_handle, 1u, 3, GL_FLOAT, GL_FALSE, 0u);
		glVertexArrayVertexBuffer(m_vao_handle, 1u, *m_normals_buffer, 0, sizeof(glm::vec3));

		m_uvs_buffer = new buffer();
		glEnableVertexArrayAttrib(m_vao_handle, 2u);
		glVertexArrayAttribBinding(m_vao_handle, 2u, 2u);
		glVertexArrayAttribFormat(m_vao_handle, 2u, 2, GL_FLOAT, GL_FALSE, 0u);
		glVertexArrayVertexBuffer(m_vao_handle, 2u, *m_uvs_buffer, 0, sizeof(glm::vec2));

		m_indices_buffer = new buffer();
		glVertexArrayElementBuffer(m_vao_handle, *m_indices_buffer);
	}

	mesh::~mesh()
	{
		delete m_indices_buffer;
		delete m_uvs_buffer;
		delete m_normals_buffer;
		delete m_positions_buffer;

		glDeleteVertexArrays(1, &m_vao_handle);
	}

	void mesh::apply()
	{
		m_positions_buffer->set_data(positions.data(), sizeof(glm::vec3) * positions.size(), buffer_usage::static_draw);
		m_normals_buffer->set_data(normals.data(), sizeof(glm::vec3) * normals.size(), buffer_usage::static_draw);
		m_uvs_buffer->set_data(uvs.data(), sizeof(glm::vec2) * uvs.size(), buffer_usage::static_draw);
		m_indices_buffer->set_data(indices.data(), sizeof(uint32_t) * indices.size(), buffer_usage::static_draw);
	}
}

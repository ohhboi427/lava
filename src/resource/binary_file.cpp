#include "pch.h"
#include "binary_file.h"

namespace lava
{
	binary_file::binary_file(const std::filesystem::path& path)
		: resource(path)
	{
		std::ifstream file(m_path, std::ios::in | std::ios::binary);
		if(file)
		{
			file.seekg(0, std::ios::end);
			size_t length = file.tellg();

			if(length != -1)
			{
				m_data.resize(length);
				file.seekg(0, std::ios::beg);
				file.read((char*)m_data.data(), length);
			}
		}
	}

	binary_file::~binary_file()
	{
		if(m_isDirty)
		{
			std::ofstream file(m_path, std::ios::out | std::ios::binary);
			if(file)
			{
				file.write((const char*)m_data.data(), m_data.size());
			}
		}
	}
}

#pragma once
#include "GameObject.h"
#include <fstream>
#include <vector>

namespace engine {
	class File
	{
	private:
		const char* file_name_{};
	public:
		File(const char* file_name) : file_name_(file_name) {}
		File(const File&) = delete;
		File(File&& other) noexcept {
			if (this != &other) {
				if (file_name_) file_name_ = nullptr;
				file_name_ = other.file_name_;
				other.file_name_ = nullptr;
			}
		}
	public:
		File& operator=(const File&) = delete;
		File& operator=(File&& other) noexcept {
			if (this != &other) {
				if (file_name_) file_name_ = nullptr;
				file_name_ = other.file_name_;
				other.file_name_ = nullptr;
			}
			return *this;
		}
	public:
		std::vector<std::shared_ptr<GameObject>> Load() const;
		void Save(const std::vector<std::shared_ptr<GameObject>>& objects);
	};
}


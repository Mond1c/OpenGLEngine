#pragma once

#include "GameObject.h"
#include <fstream>
#include <vector>

namespace engine::parser {
    class File {
    private:
        const char *file_name_{};
    public:
        explicit File(const char *file_name) : file_name_(file_name) {}

        File(const File &) = delete;

        File(File &&other) noexcept {
            if (this != &other) {
                if (file_name_) file_name_ = nullptr;
                file_name_ = other.file_name_;
                other.file_name_ = nullptr;
            }
        }

    public:
        File &operator=(const File &) = delete;

        File &operator=(File &&other) noexcept {
            if (this != &other) {
                if (file_name_) file_name_ = nullptr;
                file_name_ = other.file_name_;
                other.file_name_ = nullptr;
            }
            return *this;
        }

    public:
        [[nodiscard]] std::vector<std::shared_ptr<core::GameObject>> Load() const;

        void Save(const std::vector<std::shared_ptr<core::GameObject>> &objects);
    };
}


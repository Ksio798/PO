#pragma once
#include <vector>
#include <algorithm>

namespace fefu_laboratory_two {

    template <typename T, std::size_t N>
    class ChunkList {
    private:
        struct Chunk {
            std::vector<T> data;

            bool operator==(const Chunk& other) const {
                return data == other.data;
            }
        };

        std::vector<Chunk> chunks;

    public:
        ChunkList() = default;

        void insert(const T& value) {
            for (auto& chunk : chunks) {
                if (chunk.data.size() < N) {
                    chunk.data.push_back(value);
                    return;
                }
            }
            chunks.emplace_back(Chunk{});
            chunks.back().data.push_back(value);
        }

        void erase(const T& value) {
            for (auto& chunk : chunks) {
                auto it = std::find(chunk.data.begin(), chunk.data.end(), value);
                if (it != chunk.data.end()) {
                    chunk.data.erase(it);

                    if (chunk.data.empty()) {
                        chunks.erase(std::remove(chunks.begin(), chunks.end(), chunk), chunks.end());
                    }
                    return;
                }
            }
        }

        auto begin() { return chunks.begin(); }
        auto end() { return chunks.end(); }
        auto cbegin() const { return chunks.cbegin(); }
        auto cend() const { return chunks.cend(); }
    };

} 
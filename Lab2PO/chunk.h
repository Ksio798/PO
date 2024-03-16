#pragma once
#include <algorithm>
#include <cstring>

namespace fefu_laboratory_two {

	template <typename T, std::size_t N>
	class ChunkList {
	private:
		struct Chunk {
			T* data{ new T[N] };
			int count = 0;
			Chunk* Next = nullptr;
			Chunk* Previous = nullptr;
		};

		Chunk* CurrentChunk = nullptr;
		Chunk* FirstChunk = nullptr;
		Chunk* LastChunk = nullptr;
		int chunksCount = 0;

	public:
		ChunkList() = default;
		
		void insert(const T& value) {
			if (chunksCount == 0) {
				FirstChunk = new Chunk;
				chunksCount = 1;
				FirstChunk->data[0] = value;
				FirstChunk->count++;
				LastChunk = FirstChunk;
				return;
			}

			CurrentChunk = FirstChunk;
			for (int i = 0; i < chunksCount; i++)
			{
				if (CurrentChunk->count < N) {
					CurrentChunk->data[CurrentChunk->count] = value;
					CurrentChunk->count++;
					return;
				}
				else if (CurrentChunk->Next != nullptr) {
					CurrentChunk = CurrentChunk->Next;
				}
			}

			CurrentChunk->Next = new Chunk;
			CurrentChunk->Next->Previous = CurrentChunk;
			chunksCount++;
			CurrentChunk = CurrentChunk->Next;
			CurrentChunk->data[0] = value;
			CurrentChunk->count++;
			LastChunk = CurrentChunk;
		}

		void erase(const T& value) {
			CurrentChunk = FirstChunk;
			for (int i = 0; i < chunksCount; i++) {
				for (int j = 0; j < CurrentChunk->count; j++)
				{
					if (CurrentChunk->data[j] == value) {
						CurrentChunk->count--;
						if (CurrentChunk->count == 0) {
							chunksCount--;
							if (i == chunksCount - 1)
								LastChunk = CurrentChunk->Previous;
							if (i == 0)
								FirstChunk = CurrentChunk->Next;
							else if (chunksCount > 0)
								CurrentChunk->Previous->Next = CurrentChunk->Next;
							delete CurrentChunk;
							return;
						}

						T* temp{ new T[N] };
						memmove(temp, CurrentChunk->data, (j + 1) * sizeof(T));
						memmove(temp + j, (CurrentChunk->data) + (j + 1), (N - j) * sizeof(T));
						free(CurrentChunk->data);
						CurrentChunk->data = temp;
					}
				}
				CurrentChunk = CurrentChunk->Next;
			}
		}

		void clear() {
			auto temp = LastChunk->Previous;
			delete LastChunk;
			while (temp != FirstChunk)
			{
				LastChunk = temp;
				temp = LastChunk->Previous;
				delete LastChunk;
				LastChunk = nullptr;
			}
			delete FirstChunk;
			FirstChunk = nullptr;
			chunksCount = 0;
		}

		auto front() { return FirstChunk->data[0]; }
		auto back() { return LastChunk->data[LastChunk->count - 1]; }
		auto begin() { return &FirstChunk->data[0]; }
		auto end() { return &LastChunk->data[LastChunk->count - 1]; }

		auto chbegin() { return &FirstChunk; }
		auto chend() { return &LastChunk; }

		int count() { return chunksCount; }
	};

}
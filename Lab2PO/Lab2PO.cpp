#include "chunk.h"
#include <iostream>
using namespace std;
int main()
{
    fefu_laboratory_two::ChunkList<int, 3> chunkList;

    // Вставка элементов
    for (int i = 1; i <= 10; ++i)
        chunkList.insert(i);


    // Вывод содержимого после вставки
    cout << "ChunkList after insertions:" << endl;
    for (const auto& chunk : chunkList)
    {
        for (const auto& value : chunk.data)
            cout << value << " ";

        cout << endl;
    }

    // Удаление элементов
    chunkList.erase(2);
    chunkList.erase(5);
    chunkList.erase(8);

    // Вывод содержимого после удалений
    cout << "ChunkList after erasures:" << endl;
    for (const auto& chunk : chunkList)
    {
        for (const auto& value : chunk.data)
            cout << value << " ";

        cout << endl;
    }

}
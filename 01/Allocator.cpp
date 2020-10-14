#include <cstddef>
#include <iostream>
#include <cassert>

class Allocator {
public:
    char *memory = nullptr;
    std::size_t free_num;
    char *offset = nullptr;

    void makeAllocator(std::size_t maxSize) {
        if (memory != nullptr) {
            delete[] memory;
            memory = nullptr;
        }
        memory = new char[maxSize];
        free_num = maxSize;
        offset = memory;
    }

    char *alloc(std::size_t size) {
        if ((memory == nullptr) || (size > free_num)) {
            return nullptr;
        }
        char *start = offset;
        offset += size;
        free_num -= size;
        return start;
    }

    void reset() {
        if (memory != nullptr) {
            free_num += offset - memory;
            offset = memory;
        }
    }

    ~Allocator() {
        delete[] memory;
        memory = nullptr;
    }
};

void AllocGoodTest() {
    Allocator al;
    al.makeAllocator(10);
    char *arr = al.alloc(10);
    assert(arr != nullptr);
}

void AllocBadTest() {
    Allocator al;
    al.makeAllocator(10);
    char *arr = al.alloc(11);
    assert(arr == nullptr);
}

void SeveralAllocsGoodTest() {
    Allocator al;
    al.makeAllocator(10);
    char *arr1 = al.alloc(3);
    char *arr2 = al.alloc(7);
    assert((arr1 != nullptr) && (arr2 != nullptr));
}

void SeveralAllocsBadTest() {
    Allocator al;
    al.makeAllocator(10);
    char *arr1 = al.alloc(6);
    char *arr2 = al.alloc(5);
    assert((arr1 != nullptr) && (arr2 == nullptr));
}

void makeAllocatorTest() {
    Allocator al;
    al.makeAllocator(10);
    al.makeAllocator(15);
    assert((al.memory != nullptr) && (al.free_num == 15));
}

void OnlyAllocTest() {
    Allocator al;
    char *arr = al.alloc(10);
    assert(arr == nullptr);
}

void ResetTest() {
    Allocator al;
    al.makeAllocator(10);
    char *arr1 = al.alloc(5);
    al.reset();
    assert((al.free_num == 10) && (al.memory == al.offset));
}

int main() {
    makeAllocatorTest();
    AllocGoodTest();
    AllocBadTest();
    SeveralAllocsGoodTest();
    SeveralAllocsBadTest();
    OnlyAllocTest();
    ResetTest();

    std::cout << "Success!" << std::endl;

    return 0;
}


#include "D-heap.hpp"
#include <gtest/gtest.h>
#include <string>

TEST(DHeapTest, InsertAndPeek) {
    DHeap heap(3);

    heap.insert(std::string("A"), 1.0);
    heap.insert(std::string("B"), 0.3);
    heap.insert(std::string("C"), 0.7);

    auto top = heap.peek();
    EXPECT_EQ(std::any_cast<std::string>(top.first), "B");
    EXPECT_FLOAT_EQ(top.second, 0.3);
}

TEST(DHeapTest, ExtractRootChangesTop) {
    DHeap heap(3);

    heap.insert(std::string("A"), 1.0);
    heap.insert(std::string("B"), 0.3);
    heap.insert(std::string("C"), 0.7);
    heap.extractRoot(); // Remueve "B"

    auto top = heap.peek();
    EXPECT_EQ(std::any_cast<std::string>(top.first), "C");
    EXPECT_FLOAT_EQ(top.second, 0.7);
}

TEST(DHeapTest, IsEmptyAndLength) {
    DHeap heap(3);
    EXPECT_TRUE(heap.isEmpty());

    heap.insert(std::string("X"), 0.1);
    EXPECT_FALSE(heap.isEmpty());
    EXPECT_EQ(heap.len(), 1);

    heap.extractRoot();
    EXPECT_TRUE(heap.isEmpty());
}

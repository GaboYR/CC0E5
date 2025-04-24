#include<iostream>
#include<gtest/gtest.h>
#include "../func1.hpp"
#include "../func2.hpp"


TEST(Func1Test, SumaBasica) {
    EXPECT_EQ(suma(2, 3), 5);  // Suponiendo que `suma` está en func1.hpp
}

TEST(Func2Test, ProductoBasico) {
    EXPECT_EQ(prod(3, 4), 12);  // Suponiendo que `resta` está en func2.hpp
}
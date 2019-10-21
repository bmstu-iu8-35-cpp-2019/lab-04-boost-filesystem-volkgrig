// Copyright 2019 Volkgrig

#include <gtest/gtest.h>

#include "../include/header.hpp"

TEST(processDirectory, DefTest) {
    char* argv[] = { "PATH" };
    EXPECT_EQ(mainVirtual(1, argv), 0);
    char* argv2[] = { "PATH", "../misc/ftp" };
    EXPECT_EQ(mainVirtual(2, argv2), 0);
}

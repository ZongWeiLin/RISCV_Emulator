#include <gtest/gtest.h>
#include"../../include/ALISS.h"

TEST(MyTestSuite, MyTestCase) { 
    ASSERT_TRUE(true);
}

TEST(MyTestSuite, ELFLoaderTest) {
    const char* test = "../RISCV_elf/hello_world.elf";
    ALISS::loadElf(test);
    EXPECT_EQ(ALISS::pc, 0x1014e);
}
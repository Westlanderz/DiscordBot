#include <gtest/gtest.h>
#include "../include/bot.hpp"

TEST(Bot, Create) {
  Bot bot("user", "!");

  EXPECT_EQ("!", bot.isPrefix());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv); 
    return RUN_ALL_TESTS();
}
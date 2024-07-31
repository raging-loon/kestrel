#include <gtest/gtest.h>
#include "libdetutil/string.h"

TEST(StringTests, StringSearchTest)
{
	EXPECT_TRUE(ldu_strsrch("hello","hello",5));
}



int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();

}
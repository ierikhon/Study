#include <string.h>
#include "algorithm.h"
#include "gtest/gtest.h"

class KMPtest
{
    public:
        string P;
        string T;
        vector<int> result;
};

class KMPParamTest : public ::testing::TestWithParam<KMPtest>
{
    public:
        virtual void SetUp() { }
        virtual void TearDown() { }
};

KMPtest KMPTest1 = {"ab", "abab", vector<int> {0, 2}};
KMPtest KMPTest2 = {"ab", "cdef", vector<int> {}};

INSTANTIATE_TEST_CASE_P(KMPTestInstantiation, KMPParamTest, ::testing::Values(KMPTest1, KMPTest2));

TEST_P(KMPParamTest, KMPParamTestTrue)
{
    ASSERT_TRUE(KMP(GetParam().P, GetParam().T) == GetParam().result);
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
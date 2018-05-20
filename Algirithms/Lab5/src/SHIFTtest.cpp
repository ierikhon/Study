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

KMPtest ShiftTest1={"abcdef", "defabc", vector<int> {3}};
KMPtest ShiftTest2={"abababab", "babababa", vector<int> {1, 3, 5, 7}};

INSTANTIATE_TEST_CASE_P(KMPTestInstantiation, KMPParamTest, ::testing::Values(ShiftTest1, ShiftTest2));

TEST_P(KMPParamTest, KMPParamTestTrue)
{
    ASSERT_TRUE(KMP_UPGR(GetParam().P, GetParam().T) == GetParam().result);
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
#include "algorithm.h"
#include "gtest/gtest.h"

vector<Bor> bor;
vector<string> patterns;

class KMPtest
{
    public:
        string T;
        string P;
        vector<int> result;
};

class KMPParamTest : public ::testing::TestWithParam<KMPtest>
{
    public:
        virtual void SetUp() { }
        virtual void TearDown() { }
};

KMPtest KMPTest1 = {"CCCA", {"CC"}, {1, 1, 2 , 1}};
KMPtest KMPTest2 = {"asdf", "cd", {}};

INSTANTIATE_TEST_CASE_P(KMPTestInstantiation, KMPParamTest, ::testing::Values(KMPTest1, KMPTest2));

TEST_P(KMPParamTest, KMPParamTestTrue)
{
    ASSERT_EQ(KMP(GetParam().T, GetParam().P), GetParam().result);
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
#include "algorithm.h"
#include "gtest/gtest.h"

vector<Bor> bor;
vector<string> patterns_NR;
vector<wstring> patterns;

class ACtest
{
    public:
        const string P;
        const string pattern;
        char joker;
        vector<int> result;
};

class ACParamTest : public ::testing::TestWithParam<ACtest>
{
    public:
        virtual void SetUp() { }
        virtual void TearDown() { }
};

ACtest ACTest1 = {"ACT", "A$", '$', {1}};
ACtest ACTest2 = {"asdf", "c$", '$', {}};

INSTANTIATE_TEST_CASE_P(ACTestInstantiation, ACParamTest, ::testing::Values(ACTest1, ACTest2));

TEST_P(ACParamTest, ACParamTestTrue)
{
    ASSERT_EQ(ACtester_UPGR(GetParam().P, GetParam().pattern, GetParam().joker), GetParam().result);
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
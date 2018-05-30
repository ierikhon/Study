#include "algorithm.h"
#include "gtest/gtest.h"

vector<Bor> bor;
vector<string> patterns;

class KMPtest
{
    public:
        const string P;
        const string patterns;
        char joker;
        vector<int> result;
};

class KMPParamTest : public ::testing::TestWithParam<KMPtest>
{
    public:
        virtual void SetUp() { }
        virtual void TearDown() { }
};

KMPtest KMPTest1 = {"ACT", "A$", '$', vector<int> {1}};
KMPtest KMPTest2 = {"asdf", "c$", '$', vector<int> {}};

INSTANTIATE_TEST_CASE_P(KMPTestInstantiation, KMPParamTest, ::testing::Values(KMPTest1, KMPTest2));

TEST_P(KMPParamTest, KMPParamTestTrue)
{
    ASSERT_EQ(KMP_UPGR(GetParam().P, GetParam().patterns, GetParam().joker), GetParam().result);
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
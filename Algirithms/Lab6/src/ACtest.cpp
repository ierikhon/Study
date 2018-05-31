#include "algorithm.h"
#include "gtest/gtest.h"

vector<Bor> bor;
vector<wstring> patterns;
vector<string> patterns_NR;

class ACtest
{
    public:
        wstring T;
        vector <wstring> P;
        vector<int> result;
};

class ACParamTest : public ::testing::TestWithParam<ACtest>
{
    public:
        virtual void SetUp() { }
        virtual void TearDown() { }
};

ACtest ACTest1 = {L"CCCA", {L"CC"}, {1, 1, 2 , 1}};
ACtest ACTest2 = {L"ФКТИ", {L"ФК", L"ТИ"}, {1, 1, 3, 2}};

INSTANTIATE_TEST_CASE_P(ACTestInstantiation, ACParamTest, ::testing::Values(ACTest1, ACTest2));

TEST_P(ACParamTest, ACParamTestTrue)
{
    ASSERT_EQ(ACtester(GetParam().T, GetParam().P), GetParam().result);
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
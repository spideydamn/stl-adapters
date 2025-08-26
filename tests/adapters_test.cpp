#include <lib/adapters.h>
#include <gtest/gtest.h>
#include <map>
#include <vector>

std::vector<int> CreateVector() {
    return {1, 3, 5, 7, 9, 10, 8, 6, 4, 2, 0, -2, -4, -6, -8, -10, -9, -7, -5, -3, -1};
}

std::map<std::string, int> CreateMap() {
    std::map<std::string, int> map;
    map["bread"] = 30;
    map["milk"] = 80;
    map["apple"] = 60;
    map["chicken"] = 360;
    map["cake"] = 680;
    map["cheese"] = 160;
    return map;
}

TEST(AdaptersSuite, TransformTest) {
    std::vector<int> v = CreateVector();

    auto result = v | transform([](int i){return i * i;});

    std::vector<int> expected_result{1, 9, 25, 49, 81, 100, 64, 36, 16, 4, 0, 4, 16, 36, 64, 100, 81, 49, 25, 9, 1};

    auto it = result.begin();
    for (int i : expected_result) {
        ASSERT_EQ(*it, i);
        ++it;
    }
}

TEST(AdaptersSuite, TransformRangeBasedForTest) {
    std::vector<int> v = CreateVector();

    std::vector<int> expected_result{1, 9, 25, 49, 81, 100, 64, 36, 16, 4, 0, 4, 16, 36, 64, 100, 81, 49, 25, 9, 1};

    int i = 0;
    for (int value : v | transform([](int i){return i * i;})) {
        ASSERT_EQ(value, expected_result[i]);
        ++i;
    }
}

TEST(AdaptersSuite, FilterTest) {
    std::vector<int> v = CreateVector();

    auto result = v | filter([](int i){return i % 2 == 0;});

    std::vector<int> expected_result{10, 8, 6, 4, 2, 0, -2, -4, -6, -8, -10};

    auto it = result.begin();
    for (int i : expected_result) {
        ASSERT_EQ(*it, i);
        ++it;
    }
}

TEST(AdaptersSuite, FilterRangeBasedForTest) {
    std::vector<int> v = CreateVector();

    std::vector<int> expected_result{1, 3, 5, 7, 9, -9, -7, -5, -3, -1};

    int i = 0;
    for (int value : v | filter([](int i){return i % 2 == 1;})) {
        ASSERT_EQ(value, expected_result[i]);
        ++i;
    }
}

TEST(AdaptersSuite, TakeTest) {
    std::vector<int> v = CreateVector();

    auto result = v | take(12);

    std::vector<int> expected_result{1, 3, 5, 7, 9, 10, 8, 6, 4, 2, 0, -2};

    auto it = result.begin();
    for (int i : expected_result) {
        ASSERT_EQ(*it, i);
        ++it;
    }
}

TEST(AdaptersSuite, TakeRangeBasedForTest) {
    std::vector<int> v = CreateVector();

    std::vector<int> expected_result{1, 3, 5, 7};

    int i = 0;
    for (int value : v | take(4)) {
        ASSERT_EQ(value, expected_result[i]);
        ++i;
    }
}

TEST(AdaptersSuite, TakeEdgeCasesTest) {
    std::vector<int> v = CreateVector();

    auto result = v | take(123);
    auto result2 = v | take(1);
    auto result3 = v | take(0);

    std::vector<int> expected_result{1, 3, 5, 7, 9, 10, 8, 6, 4, 2, 0, -2, -4, -6, -8, -10, -9, -7, -5, -3, -1};
    std::vector<int> expected_result2{1};
    std::vector<int> expected_result3{};

    auto it = result.begin();
    auto it2 = result2.begin();
    auto it3 = result3.begin();
    for (int i : expected_result) {
        ASSERT_EQ(*it, i);
        ++it;
    }
    for (int i : expected_result2) {
        ASSERT_EQ(*it2, i);
        ++it2;
    }
    for (int i : expected_result3) {
        ASSERT_EQ(*it3, i);
        ++it3;
    }
}

TEST(AdaptersSuite, DropTest) {
    std::vector<int> v = CreateVector();

    auto result = v | drop(12);

    std::vector<int> expected_result{-4, -6, -8, -10, -9, -7, -5, -3, -1};

    auto it = result.begin();
    for (int i : expected_result) {
        ASSERT_EQ(*it, i);
        ++it;
    }
}

TEST(AdaptersSuite, DropRangeBasedForTest) {
    std::vector<int> v = CreateVector();

    std::vector<int> expected_result{9, 10, 8, 6, 4, 2, 0, -2, -4, -6, -8, -10, -9, -7, -5, -3, -1};;

    int i = 0;
    for (int value : v | drop(4)) {
        ASSERT_EQ(value, expected_result[i]);
        ++i;
    }
}

TEST(AdaptersSuite, DropEdgeCasesTest) {
    std::vector<int> v = CreateVector();

    auto result = v | drop(123);
    auto result2 = v | drop(1);
    auto result3 = v | drop(0);

    std::vector<int> expected_result{};
    std::vector<int> expected_result2{3, 5, 7, 9, 10, 8, 6, 4, 2, 0, -2, -4, -6, -8, -10, -9, -7, -5, -3, -1};
    std::vector<int> expected_result3{1, 3, 5, 7, 9, 10, 8, 6, 4, 2, 0, -2, -4, -6, -8, -10, -9, -7, -5, -3, -1};

    auto it = result.begin();
    auto it2 = result2.begin();
    auto it3 = result3.begin();
    for (int i : expected_result) {
        ASSERT_EQ(*it, i);
        ++it;
    }
    for (int i : expected_result2) {
        ASSERT_EQ(*it2, i);
        ++it2;
    }
    for (int i : expected_result3) {
        ASSERT_EQ(*it3, i);
        ++it3;
    }
}

TEST(AdaptersSuite, ReverseTest) {
    std::vector<int> v = CreateVector();

    auto result = v | reverse();

    std::vector<int> expected_result{-1, -3, -5, -7, -9, -10, -8, -6, -4, -2, 0, 2, 4, 6, 8, 10, 9, 7, 5, 3, 1};

    auto it = result.begin();
    for (int i : expected_result) {
        ASSERT_EQ(*it, i);
        ++it;
    }
}

TEST(AdaptersSuite, ReverseRangeBasedForTest) {
    std::vector<int> v = CreateVector();

    std::vector<int> expected_result{-1, -3, -5, -7, -9, -10, -8, -6, -4, -2, 0, 2, 4, 6, 8, 10, 9, 7, 5, 3, 1};

    int i = 0;
    for (int value : v | reverse()) {
        ASSERT_EQ(value, expected_result[i]);
        ++i;
    }
}

TEST(AdaptersSuite, KeysTest) {
     std::map<std::string, int> m = CreateMap();

    auto result = m | keys();

    std::vector<std::string> expected_result{"apple", "bread", "cake", "cheese", "chicken", "milk"};

    auto it = result.begin();
    for (auto s : expected_result) {
        ASSERT_EQ(*it, s);
        ++it;
    }
}

TEST(AdaptersSuite, KeysRangeBasedForTest) {
    std::map<std::string, int> m = CreateMap();

    std::vector<std::string> expected_result{"apple", "bread", "cake", "cheese", "chicken", "milk"};

    int i = 0;
    for (auto value : m | keys()) {
        ASSERT_EQ(value, expected_result[i]);
        ++i;
    }
}

TEST(AdaptersSuite, ValuesTest) {
    std::map<std::string, int> m = CreateMap();

    auto result = m | values();

    std::vector<int> expected_result{60, 30, 680, 160, 360, 80};

    auto it = result.begin();
    for (auto s : expected_result) {
        ASSERT_EQ(*it, s);
        ++it;
    }
}

TEST(AdaptersSuite, ValuesRangeBasedForTest) {
    std::map<std::string, int> m = CreateMap();

    std::vector<int> expected_result{60, 30, 680, 160, 360, 80};

    int i = 0;
    for (auto value : m | values()) {
        ASSERT_EQ(value, expected_result[i]);
        ++i;
    }
}
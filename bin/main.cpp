#include <vector>
#include <iostream>
#include <lib/adapters.h>
#include <map>
#include <string>

int main() {
    std::vector<int> v = {1,2,3,4,5,6};

    for(int i : v | transform([](int i){return i * i;}))
        std::cout << i << " ";

    auto removed = v | filter([](int i){return i % 2;});
    auto result = removed | transform([](int i){return i * i;});

    std::cout << std::endl;

    for(int i : result)
        std::cout << i << " ";

    std::cout << std::endl;

    for(int i : v | filter([](int i){return i % 2;}) | transform([](int i){return i * i;}))
        std::cout << i << " ";

    std::cout << std::endl;

    for(int i : result | take(2))
        std::cout << i << " ";

    std::cout << std::endl;

    for(int i : result | drop(2))
        std::cout << i << " ";

    std::cout << std::endl;

    for(int i : result | reverse())
        std::cout << i << " ";

    std::cout << std::endl;

    std::map<std::string, long long> products;

    products["bread"] = 30;
    products["milk"] = 80;
    products["apple"] = 60;

    for(auto i : products | keys())
        std::cout << i << " ";

    std::cout << std::endl;

    for(auto i : products | values())
        std::cout << i << " ";
}
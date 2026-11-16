#include <iostream>
#include <vector>
#include <string>

int main()
{
    std::vector<std::string> names = {"A", "B", "C", "G1", "Z"};
    std::vector<float> delays = {0.0f, 0.0f, 0.0f, 10.0f, 15.0f};

    std::vector<std::vector<int>> adj(5);

    adj[0] = {3};
    adj[1] = {3};
    adj[2] = {4};
    adj[3] = {4};
    adj[4] = {};
}
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

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

    std::vector<float> arrival_times (5, 0.0f);
    float max_time = 0.0f;

    for (size_t u = 0; u < adj.size(); u++){
        arrival_times[u] += delays[u];

        max_time = std::max(max_time, arrival_times[u]);

        for (int v: adj[u]){
            arrival_times[v] = std::max(arrival_times[v], arrival_times[u]);
        }
    }

    std::cout << "Max Time: " << max_time << std::endl;
}
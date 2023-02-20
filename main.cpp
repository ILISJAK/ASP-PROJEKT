#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
#include <chrono>

using std::multimap;
using std::string;
using std::vector;
using namespace std::literals;
using std::chrono::duration;
using std::chrono::duration_cast;
using std::chrono::high_resolution_clock;
using std::chrono::milliseconds;

template <typename T>
void printVector(vector<T> &data)
{
    for (const auto &it : data)
    {
        std::cout << it << " ";
    }
    std::cout << std::endl;
}

class Fraud
{
public:
    void read_csv()
    {
        std::ifstream file("fraudTest.csv");
        std::string line;

        // preskacemo prvu liniju
        std::getline(file, line);

        // citamo liniju po liniju i spremamo ih u multimapu
        int row = 1;
        while (std::getline(file, line) && data.size() <= 500000)
        {
            std::istringstream iss(line);
            std::string col;
            std::vector<std::string> row_data;

            int col_count = 0;
            while (std::getline(iss, col, ',') && col_count < 4)
            {
                row_data.push_back(col);
                col_count++;
            }

            data.insert(std::make_pair(row, row_data));
            row++;
        }
    }

    void get_top_values(const int n = 1)
    {
        int i = 0;
        for (auto it = data.rbegin(); it != data.rend(); it++)
        {
            if (i >= n)
            {
                return;
            }
            for (const auto &item : it->second)
            {
                std::cout << item << " ";
            }
            std::cout << std::endl;
            i++;
        }
    }
    void get_min_values(const int n = 1)
    {
        int i = 0;
        for (const auto &it : data)
        {
            if (i >= n)
            {
                return;
            }
            for (const auto &item : it.second)
            {
                std::cout << item << " ";
            }
            std::cout << std::endl;
            i++;
        }
    }
    int search_by_key(const int &key)
    {
        auto it = data.find(key);
        if (it != data.end() && it->first == key)
        {
            std::cout << it->first << " ";
            printVector(it->second);
            return it->first;
        }
        std::cout << "Not found." << std::endl;
        return 0;
    }
    void search_by_value(const string &value)
    {
        vector<int> found;
        for (auto const &it : data)
        {
            if (std::find(it.second.begin(), it.second.end(), value) != it.second.end())
            {
                found.push_back(it.first);
            }
        }
        if (found.empty())
        {
            std::cout << "No entries found" << std::endl;
            return;
        }
        std::cout << found.size() << " entries found: " << std::endl;
        for (int key : found)
        {
            search_by_key(key);
        }
    }
    void delete_by_key(const int &key)
    {
        auto it = data.find(key);
        if (it != data.end() && it->first == key)
        {
            std::cout << "Entry no. " << it->first << " erased. " << std::endl;
            data.erase(it);
            return;
        }
        std::cout << "Not found." << std::endl;
    }
    void delete_by_value(const string &value)
    {
        vector<int> to_be_deleted;
        for (auto const &it : data)
        {
            if (std::find(it.second.begin(), it.second.end(), value) != it.second.end())
            {
                to_be_deleted.push_back(it.first);
            }
        }
        if (to_be_deleted.empty())
        {
            std::cout << "No entries found" << std::endl;
            return;
        }
        std::cout << to_be_deleted.size() << " entries erased: " << std::endl;
        for (int key : to_be_deleted)
        {
            search_by_key(key);
            data.erase(key);
        }
    }

    multimap<int, vector<string>> data;
};

void benchmark() // ne radi?
{
    Fraud fraud;
    auto start_read_csv = high_resolution_clock::now();
    fraud.read_csv();
    auto end_read_csv = high_resolution_clock::now();
    auto duration_read_csv = duration_cast<std::chrono::microseconds>(end_read_csv - start_read_csv);
    std::cout << "read_csv: " << duration_read_csv.count() << " μs" << std::endl;

    fraud.data.clear();
    fraud.read_csv();

    auto start_get_top_values = high_resolution_clock::now();
    fraud.get_top_values(5);
    auto end_get_top_values = high_resolution_clock::now();
    auto duration_get_top_values = duration_cast<std::chrono::microseconds>(end_get_top_values - start_get_top_values);
    std::cout << "get_top_values: " << duration_get_top_values.count() << " μs" << std::endl;

    auto start_get_min_values = high_resolution_clock::now();
    fraud.get_min_values();
    auto end_get_min_values = high_resolution_clock::now();
    auto duration_get_min_values = duration_cast<std::chrono::microseconds>(end_get_min_values - start_get_min_values);
    std::cout << "get_min_values: " << duration_get_min_values.count() << " μs" << std::endl;

    auto start_search_by_key = high_resolution_clock::now();
    fraud.search_by_key(500);
    auto end_search_by_key = high_resolution_clock::now();
    auto duration_search_by_key = duration_cast<std::chrono::microseconds>(end_search_by_key - start_search_by_key);
    std::cout << "search_by_key: " << duration_search_by_key.count() << " μs" << std::endl;

    auto start_search_by_value = high_resolution_clock::now();
    fraud.search_by_value("fraud");
    auto end_search_by_value = high_resolution_clock::now();
    auto duration_search_by_value = duration_cast<std::chrono::microseconds>(end_search_by_value - start_search_by_value);
    std::cout << "search_by_value: " << duration_search_by_value.count() << " μs" << std::endl;

    auto start_delete_by_key = high_resolution_clock::now();
    fraud.delete_by_key(10);
    auto end_delete_by_key = high_resolution_clock::now();
    auto duration_delete_by_key = duration_cast<std::chrono::microseconds>(end_delete_by_key - start_delete_by_key);
    std::cout << "delete_by_key: " << duration_delete_by_key.count() << " μs" << std::endl;

    auto start_delete_by_value = high_resolution_clock::now();
    fraud.delete_by_value("fraud");
    auto end_delete_by_value = high_resolution_clock::now();
    auto duration_delete_by_value = duration_cast<std::chrono::microseconds>(end_delete_by_value - start_delete_by_value);
    std::cout << "delete_by_value: " << duration_delete_by_value.count() << " μs" << std::endl;
}

int main()
{
    Fraud fraud;
    fraud.read_csv();
    fraud.search_by_key(2);
    // benchmark();

    return 0;
}

#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <list>
#include <map>

using namespace std;

// function that takes name of a file and returns the array of integers
const int LENGTH = 100;
int *read_data_file(string filename)
{
    int *array = new int[LENGTH];
    int i = 0;
    ifstream file;
    file.open(filename);
    while (file >> array[i])
    {
        i++;
    }
    file.close();
    return array;
}
const int *DATA = read_data_file("data.txt");

string read_index_file(string filename)
{
    string index;
    ifstream file;
    file.open(filename);
    file >> index;
    file.close();
    return index;
}

vector<int> index_to_subset(string index)
{
    vector<int> subset;
    for (int i = 0; i < index.length(); i++)
    {
        if (index[i] == '1')
        {
            subset.push_back(DATA[i]);
        }
    }
    return subset;
}

int subset_sum(string index)
{
    vector<int> subset = index_to_subset(index);
    int sum = 0;
    for (int i = 0; i < subset.size(); i++)
    {
        sum += subset[i];
    }
    // return absoute value of sum
    return abs(sum);
}

string negate_bit(string index, int i)
{
    if (index[i] == '1')
    {
        index[i] = '0';
    }
    else
    {
        index[i] = '1';
    }
    return index;
}

bool character_in_string(string index, char c)
{
    for (int i = 0; i < index.length(); i++)
    {
        if (index[i] == c)
        {
            return true;
        }
    }
    return false;
}

vector<string> generate_neighbors(string index)
{
    vector<string> neighbors;
    for (int i = 0; i < index.length(); i++)
    {
        string neighbor = negate_bit(index, i);
        if (character_in_string(neighbor, '1'))
        {
            neighbors.push_back(neighbor);
        }
    }
    return neighbors;
}

string tabu_search(string index, int iterations_limit)
{
    set<string> tl; // tabu list
    list<string> l; // steps list
    l.push_back(index);
    string best_index = index;
    string current_index = index;
    int i = 0;
    while (i < iterations_limit && subset_sum(best_index) != 0 && l.size() > 0)
    {
        i += 1;
        vector<string> neighbors = generate_neighbors(current_index);
        vector<string> valid_neighbors;
        for (int i = 0; i < neighbors.size(); i++)
        {
            if (!tl.count(neighbors[i]))
            {
                valid_neighbors.push_back(neighbors[i]);
            }
        }

        tl.insert(current_index);
        if (valid_neighbors.size() > 0)
        {
            // find neighbour with the lowest sum
            int min_sum = subset_sum(valid_neighbors[0]);
            string best_local_index = valid_neighbors[0];
            for (int i = 1; i < valid_neighbors.size(); i++)
            {
                int sum = subset_sum(valid_neighbors[i]);
                if (sum < min_sum)
                {
                    min_sum = sum;
                    best_local_index = valid_neighbors[i];
                }
            }

            if (subset_sum(best_local_index) < subset_sum(best_index))
            {
                l.push_back(current_index);
                best_index = best_local_index;
            };
            current_index = best_local_index;
        }
        else
        {
            current_index = l.back();
            l.pop_front();
        }
    }
    cout << "Iterations: " << i << endl;
    return best_index;
}

int main()
{
    string start_index = read_index_file("start_index.txt");
    string best_index = tabu_search(start_index, 1000);
    int best_sum = subset_sum(best_index);
    cout << "Start sum: " << subset_sum(start_index) << endl;
    cout << "Best sum: " << best_sum << endl;
    return 0;
}
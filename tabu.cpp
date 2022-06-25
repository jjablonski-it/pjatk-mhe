#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <list>

using namespace std;

// function that takes name of a file and returns the array of integers
const int LENGTH = 100;
int* read_file(string filename) {
    int* array = new int[LENGTH];
    int i = 0;
    ifstream file;
    file.open(filename);
    while (file >> array[i]) {
        i++;
    }
    file.close();
    return array;
}
const int* DATA = read_file("data.txt");


vector<int> index_to_subset(string index) {
    vector<int> subset;
    for (int i = 0; i < index.length(); i++) {
      if(index[i] == '1') {
        subset.push_back(DATA[i]);
      }
    }
    return subset;
}

int subset_sum(string index) {
    vector<int> subset = index_to_subset(index);
    int sum = 0;
    for (int i = 0; i < subset.size(); i++) {
        sum += subset[i];
    }
    return sum;
}

string negate_bit(string index, int i) {
    if (index[i] == '1') {
        index[i] = '0';
    } else {
        index[i] = '1';
    }
    return index;
}

bool character_in_string(string index, char c) {
    for (int i = 0; i < index.length(); i++) {
        if (index[i] == c) {
            return true;
        }
    }
    return false;
}

vector<string> generate_neighbors(string index) {
    vector<string> neighbors;
    for (int i = 0; i < index.length(); i++) {
      string neighbor = negate_bit(index, i);
      if(character_in_string(neighbor, '1')) {
        neighbors.push_back(neighbor);
      }
    }
    return neighbors;
}

string tabu_search(string index, int iterations_limit) {
  set<string> tl; // tabu list
  list<string> l; // steps list
  string best_index = index;
  string current_index = index;
  int i = 0;
  while(i < iterations_limit && subset_sum(best_index)!=0 && l.size() > 0) {
    i += 1;
    vector<string> neighbors = generate_neighbors(current_index);
    vector<int> neighbour_sum_dict; // {index -> sum} dict
    for (int i = 0; i < neighbors.size(); i++) {
        neighbour_sum_dict.push_back(subset_sum(neighbors[i]));
    }
    vector<int> sorted_neighbors;
    for (int i = 0; i < neighbour_sum_dict.size(); i++) {
        sorted_neighbors.push_back(neighbour_sum_dict[i]);
    }
    sort(sorted_neighbors.begin(), sorted_neighbors.end());
    list<string> valid_neighbors;
    for (int i = 0; i < sorted_neighbors.size(); i++) {
        if(!tl.count(neighbors[i])) {
            valid_neighbors.push_back(neighbors[i]);
        }
    }
    if(valid_neighbors.size() > 0) {
        string best_local_index = valid_neighbors.back();
        valid_neighbors.pop_front();
        if(subset_sum(best_local_index) < subset_sum(best_index)) {
            l.push_back(current_index);
            best_index = best_local_index;
        }
        current_index = best_local_index;
    } else {
        current_index = l.back();
        l.pop_front();
    }
  }
  cout << "Iterations: " << i << endl;
  return best_index;
}

int main() {
  string start_index = "1000010011001000101100000110000100100010101001001000001101011010101011000000101001100111001000100011";
  string best_index = tabu_search(start_index, 1000);
  int best_sum = subset_sum(best_index);
  cout << "Start sum: " << subset_sum(start_index) << endl;
  cout << "Best sum: " << best_sum << endl;
  return 0;
}
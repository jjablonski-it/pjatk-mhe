#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

const int LENGTH = 100;

// function that takes name of a file and returns the array of integers
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

vector<int> index_to_subset(int* array, string index) {
    vector<int> subset;
    for (int i = 0; i < index.length(); i++) {
      if(index[i] == '1') {
        subset.push_back(array[i]);
      }
    }
    return subset;
}

int subset_sum(vector<int> subset) {
    int sum = 0;
    for (int i = 0; i < subset.size(); i++) {
        sum += subset[i];
    }
    return sum;
}

int main()
{
    cout << "Hello World" << endl;
    int* data = read_file("data.txt");
    // print the array
    for (int i = 0; i < LENGTH; i++) {
        cout << data[i] << " ";
    }
   // binary string with length LENGTH and only one 1 in it

    string index = "101";
    vector<int> subset = index_to_subset(data, index);

    cout<< endl << "Subset: ";
    // print the subset
    for (int i = 0; i < subset.size(); i++) {
        cout << subset[i] << " ";
    }

    cout << endl << "Sum: " << subset_sum(subset) << endl;

    return 0;
}
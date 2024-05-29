#include <iostream>
#include <string>
#include <vector>
using namespace std;
struct HashEntry {
    vector<string> words;
};

int hashFunction(const string& str, int numContainers) {
    int sum = 0;
    for (char c : str) {
        sum += static_cast<int>(c);
    }
    return sum % numContainers;
}

void addToHashTable(const string& word, int numContainers, HashEntry* hashTable) {
    int containerIndex = hashFunction(word, numContainers);
    hashTable[containerIndex].words.push_back(word);
}

int main() {
    string input;
    cout << "Enter a string: ";
    getline(cin, input);

    int numContainers = 6;
    HashEntry* hashTable = new HashEntry[numContainers];

    size_t startPos = 0;
    size_t endPos = input.find(' ');

    while (endPos != string::npos) {
        string word = input.substr(startPos, endPos - startPos);
        addToHashTable(word, numContainers, hashTable);
        startPos = endPos + 1;
        endPos = input.find(' ', startPos);
    }

    string word = input.substr(startPos);
    addToHashTable(word, numContainers, hashTable);

    for (int i = 0; i < numContainers; i++) {
        cout << "Container " << i << ": ";
        if (!hashTable[i].words.empty()) {
            cout << "[" << hashTable[i].words.size() << " word(s)] ";
            for (size_t j = 0; j < hashTable[i].words.size(); j++) {
                cout << hashTable[i].words[j];
                if (j != hashTable[i].words.size() - 1) {
                    cout << ", ";
                }
            }
        }
        else {
            cout << "Empty";
        }
        cout << endl;
    }

    delete[] hashTable;

    return 0;
}
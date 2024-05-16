#include <iostream>
#include <fstream>
#include <unordered_set>
#include <string>
#include <algorithm>
std::unordered_set<std::string> loadDictionary(const std::string& filename) {
    std::unordered_set<std::string> dictionary;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open dictionary file '" << filename << "'" << std::endl;
        exit(1);
    }
    std::string word;
    while (file >> word) {
        dictionary.insert(std::move(word));
    }
    return dictionary;
}
void generateAnagrams(const std::string& word, const std::unordered_set<std::string>& dictionary) {
    std::string currentAnagram = word;
    std::sort(currentAnagram.begin(), currentAnagram.end());
    do {
        if (dictionary.find(currentAnagram) != dictionary.end()) {
            std::cout << currentAnagram << std::endl;
        }
    } while (std::next_permutation(currentAnagram.begin(), currentAnagram.end()));
}
int main(int argc, char* argv[]) {
    std::string dictionaryFilename = "dictionary.txt";
    for (int i = 1; i < argc - 1; ++i) {
        if (std::strcmp(argv[i], "--custom-dictionary") == 0) {
            dictionaryFilename = argv[i + 1];
            break;
        }
    }
    std::unordered_set<std::string> dictionary = loadDictionary(dictionaryFilename);
    for (int i = 1; i < argc; ++i) {
        if (std::strcmp(argv[i], "--custom-dictionary") != 0) {
            std::cout << "Anagrams of " << argv[i] << " :- " << std::endl;
            generateAnagrams(argv[i], dictionary);
        } else {
            ++i;
        }
    }
    return 0;
}

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>

std::vector<std::string> loadDictionary(const std::string &filePath) {
    std::vector<std::string> words;
    std::ifstream file(filePath.c_str());
    std::string word;
    while (file >> word) {
        if (word.length() == 5) {
            words.push_back(word);
        }
    }
    return words;
}
std::string getFeedback() {
    std::string feedback;
    std::cout << "Enter data from the guess- (G for Green, Y for Yellow, - for Grey): ";
    std::cin >> feedback;
    return feedback;
}
bool isValidWord(const std::string &word, const std::string &guess, const std::string &feedback) {
    std::vector<bool> used(word.size(), false);
    for (size_t i = 0; i < guess.size(); ++i) {
        if (feedback[i] == 'G') {
            if (word[i] != guess[i]) {
                return false;
            }
            used[i] = true;
        }
    }
    for (size_t i = 0; i < guess.size(); ++i) {
        if (feedback[i] == 'Y') {
            bool found = false;
            for (size_t j = 0; j < word.size(); ++j) {
                if (word[j] == guess[i] && !used[j] && j != i) {
                    found = true;
                    used[j] = true;
                    break;
                }
            }
            if (!found) {
                return false;
            }
        }
    }
    for (size_t i = 0; i < guess.size(); ++i) {
        if (feedback[i] == '-') {
            for (size_t j = 0; j < word.size(); ++j) {
                if (word[j] == guess[i]) {
                    return false;
                }
            }
        }
    }

    return true;
}
std::vector<std::string> filterWords(const std::vector<std::string> &words, const std::string &guess, const std::string &feedback) {
    std::vector<std::string> newWords;
    for (size_t i = 0; i < words.size(); ++i) {
        if (isValidWord(words[i], guess, feedback)) {
            newWords.push_back(words[i]);
        }
    }
    return newWords;
}
std::string makeGuess(const std::vector<std::string> &words) {
    return words[std::rand() % words.size()];
}
int main() {
    std::srand(static_cast<unsigned int>(std::time(0)));
    std::string dictionaryPath = "resources/dictionary.txt";
    std::vector<std::string> words = loadDictionary(dictionaryPath);
    if (words.empty()) {
        std::cerr << "Dictionary is empty or not found!" << std::endl;
        return 1;
    }
    while (true) {
        std::string guess = makeGuess(words);
        std::cout << "Guess: " << guess << std::endl;
        std::string feedback = getFeedback();
        if (feedback == "GGGGG") {
            std::cout << "Congratulations! You've found the word!" << std::endl;
            break;
        }
        words = filterWords(words, guess, feedback);
        if (words.empty()) {
            std::cerr << "No possible words left based on feedback!" << std::endl;
            break;
        }
    }
    return 0;
}
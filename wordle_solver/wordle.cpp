#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#define GREEN_TEXT "\033[1;32m"
#define YELLOW_TEXT "\033[1;33m"
#define RESET_TEXT "\033[0m"
#define CYAN_TEXT "\033[1;36m"
#define RED_TEXT "\033[1;31m"
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
    std::cout << "Enter data from the guess-" << RESET_TEXT << "("<< GREEN_TEXT << "G" << RESET_TEXT << " for Green, "<< YELLOW_TEXT << "Y" << RESET_TEXT << " for Yellow, "<< "-" << " for Grey): ";
    std::cin >> feedback;
    std::transform(feedback.begin(), feedback.end(), feedback.begin(), ::toupper);
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
    int guess_num = 0;
    std::srand(static_cast<unsigned int>(std::time(0)));
    std::string dictionaryPath = "resources/dictionary.txt";
    std::vector<std::string> words = loadDictionary(dictionaryPath);
    if (words.empty()) {
        std::cerr << "Dictionary is empty and/or not found!" << std::endl;
        return 1;
    }
    while (true) {
        guess_num++;
        std::string guess = makeGuess(words);
        std::cout << CYAN_TEXT << "Guess: " << RESET_TEXT << RED_TEXT << guess << RESET_TEXT << std::endl;
        std::string feedback = getFeedback();
        if (feedback == "GGGGG") {
            if (guess_num == 1) {
                std::cout << CYAN_TEXT << "Word has been found in " << RESET_TEXT << RED_TEXT << guess_num << CYAN_TEXT << " attempt." << RESET_TEXT << std::endl;
            } else {
                std::cout << CYAN_TEXT << "Word has been found in " << RESET_TEXT << RED_TEXT << guess_num << CYAN_TEXT << " attempts." << RESET_TEXT << std::endl;
            }
            break;
        }
        words = filterWords(words, guess, feedback);
        if (words.empty()) {
            std::cerr << "No possible words left based on data provided!" << std::endl;
            break;
        }
    }
    return 0;
}
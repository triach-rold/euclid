# Anagram Generator

Generates anagram(s) from a given word. You can customize the dictionary provided giving you full control about potential outputs.

## Features
- Load dictionary from the file specified by you.
- Generate valid anagrams for given words based on the loaded dictionary.
- Command-line interface for specifying custom dictionary and input words.

## Usage

### Command-Line Options
- `--custom-dictionary <filename>`: Specifies a custom dictionary file. If it's not provided, the default dictionary file `../resources/dictionary.txt` is used.
- `<word1> <word2> ... <wordN>`: List of words for which anagrams are to be generated.

### Example
```sh
./anagram --custom-dictionary mydictionary.txt word1 word2
```

This command will load `mydictionary.txt` as the dictionary and generate anagrams for `word1` and `word2`. 

_Note- It will generate word1's potential anagrams first then move on to word2 and so on._

## Compilation
To compile the program, use a C++ compiler such as `g++`:

```sh
g++ -o anagram anagram.cpp
```

## Execution
Run the compiled program with the necessary arguments:

```sh
./anagram --custom-dictionary mydictionary.txt word1 word2
```

This will generate and print anagrams for `word1` and `word2` based on the words found in `mydictionary.txt`. If you don't specify the --custom-dictionary filename, it will use the dictionary from `../resources/dictionary.txt`.
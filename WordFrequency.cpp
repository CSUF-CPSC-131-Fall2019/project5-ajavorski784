#include "WordFrequency.h"
#include "sanitize.h"
#include <algorithm>
#include <fstream>
#include <string>
#include <unordered_map>

WordFrequency::WordFrequency() { numWords = 0; } // default constructor
void WordFrequency::readIn(const string &filename) {
  std::ifstream file(filename);
  std::string currentWord; // Word holder for placing into hash table
  int total = 0;

  while (!file.eof()) {
    getline(file, currentWord, ' ');
    // total++;
    sanitize(currentWord);
    currentWord.erase(std::remove(currentWord.begin(), currentWord.end(), '\n'),
                      currentWord.end());
    for (int i = 0, length = currentWord.size(); i < length; i++) {
      // check whether character is end characters or punctuation
      if (std::ispunct(currentWord[i])) {
        currentWord.erase(i--, 1);
        length = currentWord.size();
      }
    }
    if (frequencyTable.find(currentWord) == frequencyTable.end()) {
      frequencyTable[currentWord] = 1;
      numWords++;
    } else {
      frequencyTable[currentWord] += 1;
    }
    // frequencyTable[currentWord]++;
    // std::cout << currentWord << std::endl;
  }
  // std::cout << frequencyTable.bucket_count() << std::endl;
  // std::cout << total << std::endl;
  std::unordered_map<string, int>::iterator itr;
  for (itr = frequencyTable.begin(); itr != frequencyTable.end(); itr++) {
    if (itr->first == "Ichabod" || itr->first == "Ichabods") {
      std::cout << "true " << itr->second << std::endl;
    }
  }

} // add words from file to hash table
size_t WordFrequency::numberOfWords() {
  return numWords;
} // return the number of unique words
size_t WordFrequency::wordCount(const string &word) {
  std::unordered_map<string, int>::iterator itr = frequencyTable.begin();
  while (itr != frequencyTable.end()) {
    if (word == itr->first) {
      return itr->second;
    }
    itr++;
  }
  return 0;

} // return the number of occurrences of the given word
string WordFrequency::mostFrequentWord() {
  std::string word;
  int freqWord = 0;
  std::unordered_map<string, int>::iterator itr;
  for (itr = frequencyTable.begin(); itr != frequencyTable.end(); itr++) {
    if (itr == frequencyTable.begin()) {
      word = itr->first;
      freqWord = itr->second;
    }
    if (freqWord < itr->second) {
      word = itr->first;
      freqWord = itr->second;
    }
  }
  return word;
} // return the most frequent word
size_t WordFrequency::maxBucketSize() {
  int bigBucket =
      frequencyTable.bucket_size(0); // Variable storing largest bucket size
  for (int i = 0; i < frequencyTable.bucket_count(); i++) {
    if (bigBucket < frequencyTable.bucket_size(i)) {
      bigBucket = frequencyTable.bucket_size(i);
    }
  }
  return bigBucket;
} // return the size of the largest bucket
  // in the hash table

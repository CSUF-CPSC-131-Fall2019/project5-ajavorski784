#include "WordFrequency.h"
#include "sanitize.h"
#include <fstream>
#include <string>
#include <unordered_map>

WordFrequency::WordFrequency() {} // default constructor
void WordFrequency::readIn(const string &filename) {
  std::ifstream file(filename);
  std::string currentWord; // Word holder for placing into hash table

  while (file >> currentWord) {
    sanitize(currentWord);
    char e = currentWord[currentWord.length() - 1]; // stores last character
    if (e == '.' || e == '!' || e == '?') {
      // Checks if last character is end punctuation
      currentWord.pop_back(); // removes end punctuation if exists
    }
    frequencyTable[currentWord]++; // Adds word to hash table
  }

} // add words from file to hash table
size_t WordFrequency::numberOfWords() {
  return frequencyTable.size();
} // return the number of unique words
size_t WordFrequency::wordCount(const string &word) {
  return frequencyTable[word];

} // return the number of occurrences of the given word
string WordFrequency::mostFrequentWord() {
  std::string word; // The current highest frequency word
  int freqWord = 0; // Holds the highest frequency to compare to others
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

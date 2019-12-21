#include "WordFrequency.h"
#include "sanitize.h"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>

WordFrequency::WordFrequency() {} // default constructor
void WordFrequency::readIn(const string &filename) {
  std::ifstream file(filename);
  std::string line;
  std::string currentWord; // Word holder for placing into hash table

  while (!file.eof()) {
    getline(file, line);
    std::stringstream currentLine(line);
    while (!currentLine.eof()) {
      getline(currentLine, currentWord, ' ');
      currentWord.erase(
          std::remove(currentWord.begin(), currentWord.end(), '.'),
          currentWord.end());
      currentWord.erase(
          std::remove(currentWord.begin(), currentWord.end(), '?'),
          currentWord.end());
      currentWord.erase(
          std::remove(currentWord.begin(), currentWord.end(), '!'),
          currentWord.end());
      sanitize(currentWord);
      if (currentWord == "") {
        continue;
      } else {
        frequencyTable[currentWord]++;
      }
    }
  }
} // add words from file to hash table
size_t WordFrequency::numberOfWords() {
  return frequencyTable.size();
} // return the number of unique words
size_t WordFrequency::wordCount(const string &word) {
  return frequencyTable[word];

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

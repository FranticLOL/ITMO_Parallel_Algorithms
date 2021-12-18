#include <iostream>
#include <string>
#include <vector>

using namespace std;

int word_count(const string &s) {
  if (s == "") {
  return 0;
  }
  int count = 1;
  for (char const &c: s) {
      if (c == ' ' || c == '\n' || c == '\t')
        count++;
    }

  return count;
}

int main(int argc, char **argv) {
    string line = argv[1];
    cout << word_count(line) << endl;
    return 0;
}
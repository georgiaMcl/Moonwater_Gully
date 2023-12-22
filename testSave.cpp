#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

class testSave {
 protected:
  std::fstream test;
  int newNumber;

 public:
  testSave(int no) {
    newNumber = no;
    newNumber = 0;
    std::cout << newNumber;
  }
  void save() {
    test.open("test.txt", std::ios::out);
    test << "number:";
    test << 30;
    test.close();
  }
  void load() {
    test.open("test.txt", std::ios::out);
    std::string line;
    std::getline(test, line);
    if (line.find("number:") != std::string::npos) {
      line = line.substr(7);
      newNumber = std::stoi(line);
    }
    std::cout << newNumber;
  }
};

int main() {
  testSave saver(5);
  saver.save();
  saver.load();
}
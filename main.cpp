#include <cstdlib>
#include <iostream>
#include <list>
#include <vector>

#include "HASHtable.h"

int main() {
  std::string str;
  std::string SYSarg;
  std::cout << "enter 'windows' if the program is running on windows\nenter "
               "'linux' if the program is running on linux\nor enter any other "
               "character for a different system\nsystem:";
  std::cin >> str;
  if (SYSTEMis(str) == 1) {
    SYSarg = "cls";
  } else if (SYSTEMis(str) == 2) {
    SYSarg = "clear";
  } else {
    std::cout << "This program only works with windows and linux." << std::endl;
    return 0;
  }
  std::cout << "\nGood afternoon,\nyou have launched a program to output hash "
               "tables to the console.\nSince the main purpose of this program "
               "is to enter data into the console,\nthe simplest modulo hash "
               "function was taken.\nIf you want to see what functions are in "
               "the program,\nwrite HELP or something else to continue.\n"
            << std::endl;
  std::cin >> str;
  out_HELPER(str);
  int SIZE = 0;
  int flag = 0;
  while (flag == 0) {
    std::cout << "Enter upper limit of the size: ";
    std::cin >> str;
    if (inputSIZE(str) == 1) {
      SIZE = std::stoi(str);
      SIZE = std::rand() % SIZE;
      if (SIZE == 0) {
        SIZE = 1;
      }
      flag = 1;
    } else if (inputSIZE(str) == 2) {
      std::cout << "int must be adjacent [2:10]" << std::endl;
    } else if (inputSIZE(str) == 3) {
      std::cout << "wronge date" << std::endl;
    }
  }
  HashTable ht(SIZE);
  flag = 0;
  int command = -1;
  while (flag == 0) {
    out_HashTable(SIZE, ht.get_table_size(), ht.get_deep(), ht.get_table());
    std::cout << "\nwrite command:";
    std::cin >> str;
    command = check_command(str);
    if (command == 1) {
      std::cout << "add number:";
      std::cin >> str;
      if (output_ADD(ht, str) == 1) {
        cleaner(SYSarg);
        ht.insert(std::stoi(str));
      } else if (output_ADD(ht, str) == 2) {
        cleaner(SYSarg);
        std::cout << str << " already in the table" << std::endl;
      } else if (output_ADD(ht, str) == 3) {
        cleaner(SYSarg);
        std::cout << "wronge date" << std::endl;
      }
    } else if (command == 2) {
      std::cout << "remove number:";
      std::cin >> str;
      if (output_REMOVE(ht, str) == 1) {
        cleaner(SYSarg);
        ht.remove(std::stoi(str));
      } else if (output_REMOVE(ht, str) == 2) {
        cleaner(SYSarg);
        std::cout << str << " not in the table" << std::endl;
      } else if (output_REMOVE(ht, str) == 3) {
        cleaner(SYSarg);
        std::cout << "wronge date" << std::endl;
      }
    } else if (command == 3) {
      std::cout << "check number:";
      std::cin >> str;
      if (output_CHECK(ht, str) == 1) {
        cleaner(SYSarg);
        std::cout << str << " find" << std::endl;
      } else if (output_CHECK(ht, str) == 2) {
        cleaner(SYSarg);
        std::cout << str << " not find" << std::endl;
      } else if (output_CHECK(ht, str) == 3) {
        cleaner(SYSarg);
        std::cout << "wronge date" << std::endl;
      }
    } else if (command == 0) {
      cleaner(SYSarg);
      std::cout << "Goodbye" << std::endl;
      flag = 1;
    } else {
      cleaner(SYSarg);
      std::cout << "wronge command" << std::endl;
    }
  }
  return 0;
}
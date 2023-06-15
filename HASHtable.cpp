#include "HASHtable.h"

#include <cstdlib>
#include <iostream>
#include <list>
#include <vector>

int HashTable::hash(int key) { return key % size; }
void HashTable::check_table_size(int key) {
  int index = hash(key);
  int max_len = table_size[index];
  for (auto it = table[index].begin(); it != table[index].end(); ++it) {
    int unit = *it;
    int ruler = 9;
    int len_unit = 1;
    while (ruler < unit) {
      // max_len = len_unit;
      len_unit = len_unit + 1;
      ruler = ruler * 10 + 9;
    }
    if (len_unit > max_len) {
      max_len = len_unit;
    }
  }
  table_size[index] = max_len;
}
void HashTable::change_deep(int key, int mod) {
  int index = hash(key);
  deep[index] = deep[index] + mod;
}

HashTable::HashTable(int size) {
  this->size = size;
  table.resize(size, std::list<int>{-1});
  table_size.resize(size, 0);
  deep.resize(size, 0);
}

void HashTable::insert(int key) {
  int index = hash(key);
  for (auto it = table[index].begin(); it != table[index].end(); ++it) {
    if (*it == -1) {
      *it = key;
      break;
    } else {
      table[index].push_back(key);
      break;
    }
  }
  check_table_size(key);
  change_deep(key, 1);
}

void HashTable::remove(int key) {
  int index = hash(key);
  table[index].remove(key);
  if (table[index].empty()) {
    table[index].push_back(-1);
  }
  check_table_size(key);
  change_deep(key, (-1));
}

bool HashTable::search(int key) {
  int index = hash(key);
  for (auto it = table[index].begin(); it != table[index].end(); ++it) {
    if (*it == key) {
      return true;
    }
  }
  return false;
}

void HashTable::print() {
  for (int i = 0; i < size; i++) {
    std::cout << i << ": ";
    for (auto it = table[i].begin(); it != table[i].end(); ++it) {
      std::cout << *it << " ";
    }
    std::cout << std::endl;
  }
}

void HashTable::print_size() {
  for (int i = 0; i < size; i++) {
    std::cout << table_size[i] << "\n";
  }
}
void HashTable::print_deep() {
  for (int i = 0; i < size; i++) {
    std::cout << deep[i] << "\n";
  }
}
std::vector<int> HashTable::get_table_size() { return table_size; };
std::vector<int> HashTable::get_deep() { return deep; };
std::vector<std::list<int>> HashTable::get_table() { return table; };

void out_HashTable(int size, std::vector<int> table_size, std::vector<int> deep,
                   std::vector<std::list<int>> table) {
  std::string output_table;
  output_table += "\ntable\n";
  for (int i = 1; i <= size;
       i++) {  // traversing the top, that is, the output of all possible hashes
    output_table += std::to_string(i);
    int max_len = table_size[i % size];
    if (i != size) {  // if not last
      int max_len_next = table_size[(i + 1) % size];
      if (i == 1) {  // if first
        for (int j = 1; j < max_len;
             j++) {  // the distance between hashes and separator in "-"
          output_table += "-";
        }
        output_table += "-";  // basic separator
        if (i + 1 != size) {  // if not the penultimate
          for (int j = 1; j <= (max_len_next - 1) / 2; j++) {
            output_table +=
                "-";  // the distance between separator and hashes in "-"
          }
        } else {  // the penultimate
          for (int j = 1; j < max_len_next; j++) {
            output_table +=
                "-";  // the distance between separator and hashes in "-"
          }
        }
      } else if (i < size) {  // if not last and not first
        for (int j = 0; j < ((max_len) / 2); j++) {
          output_table +=
              "-";  // the distance between hashes and separator in "-"
        }
        output_table += "-";  // basic separator
        if (i + 1 != size) {  // if not the penultimate
          for (int j = 1; j <= (max_len_next - 1) / 2; j++) {
            output_table +=
                "-";  // the distance between separator and hashes in "-"
          }
        } else {  // the penultimate
          for (int j = 1; j < max_len_next; j++) {
            output_table +=
                "-";  // the distance between separator and hashes in "-"
          }
        }
      }
    }
  }
  output_table += "\n";             // next line
  int max_deep = 0;                 // max deep of all deep
  for (int v = 0; v < size; v++) {  // find max_deep
    int unit_deep = deep[v];
    if (max_deep < unit_deep) {
      max_deep = unit_deep;
    }
  }
  for (int u = 0; u < max_deep; u++) {  // traversing data by levels
    for (int i = 1; i <= size; i++) {   // print linkers
      if (u < deep[i % size] or
          u == 0) {  // existing links and empty links with empty hashes
        output_table += "|";  // link
      } else {  // if deep hash <max_deep and deep hash< iterated deep
        output_table += " ";  // nothing
      }
      int max_len = table_size[i % size];
      if (i != size) {  // not last
        int max_len_next = table_size[(i + 1) % size];
        if (i == 1) {  // first
          for (int j = 1; j < max_len; j++) {
            output_table += " ";  // the distance between link(or nothing) and
                                  // separator in " "
          }
          output_table += " ";  // the basic separator
          if (i + 1 != size) {  // not the penultimate
            for (int j = 1; j <= (max_len_next - 1) / 2; j++) {
              output_table += " ";  // the distance between separator and
                                    // link(or nothing) in " "
            }
          } else {  // the penultimate
            for (int j = 1; j < max_len_next; j++) {
              output_table += " ";  // the distance between separator and
                                    // link(or nothing) in " "
            }
          }
        } else if (i < size) {  // not last and not first
          for (int j = 0; j < ((max_len) / 2); j++) {
            output_table += " ";  // the distance between link(or nothing) and
                                  // separator in " "
          }
          output_table += " ";  // the basic separator
          if (i + 1 != size) {  // not the penultimate
            for (int j = 1; j <= (max_len_next - 1) / 2; j++) {
              output_table += " ";  // the distance between separator and
                                    // link(or nothing) in " "
            }
          } else {  // the penultimate
            for (int j = 1; j < max_len_next; j++) {
              output_table += " ";  // the distance between separator and
                                    // link(or nothing) in " "
            }
          }
        }
      }
    }
    output_table += "\n";              // next line
    for (int i = 1; i <= size; i++) {  // data traversal
      int max_len = table_size[i % size];
      auto it = table[i % size].begin();
      if (u < deep[i % size]) {  // if so deep
        std::advance(it, u);
        int element = *it;
        int len_unit = 1;
        if (element != (-1)) {                      // not empty hash check
          output_table += std::to_string(element);  // data
          int ruler = 9;
          while (ruler < element) {  // find lenth data
            len_unit = len_unit + 1;
            ruler = ruler * 10 + 9;
          }
        } else {                // empty hash check
          output_table += " ";  // empty data
        }
        if (i != size) {  // not last
          int max_len_next = table_size[(i + 1) % size];
          auto jt = table[(i + 1) % size].begin();
          if (u < deep[(i + 1) % size]) {  // if so deep next hash
            std::advance(jt, u);
            int element_next = *jt;
            int len_next_unit = 1;
            int ruler = 9;
            while (ruler < element_next) {  // find len data next hash
              len_next_unit = len_next_unit + 1;
              ruler = ruler * 10 + 9;
            }
            if (i == 1) {  // if first
              for (int j = 1; j < (max_len - len_unit + 1);
                   j++) {  // the distance between data and separator in " "
                output_table += " ";
              }
              output_table += " ";  // basic separator
              if (i + 1 != size) {  // not the penultimate
                for (int j = 1;
                     j <= ((max_len_next - 1) / 2) - ((len_next_unit - 1) / 2);
                     j++) {  // the distance between separator and next data in
                             // " "
                  output_table += " ";
                }
              } else {  // the penultimate
                for (int j = 1; j < max_len_next - len_next_unit + 1;
                     j++) {  // the distance between separator and next data in
                             // " "
                  output_table += " ";
                }
              }
            } else if (i < size) {  // if not first and not last
              for (int j = 0; j < ((max_len) / 2) - (len_unit / 2);
                   j++) {  // the distance between data and separator in " "
                output_table += " ";
              }
              output_table += " ";  // basic separator
              if (i + 1 != size) {  // not the penultimate
                for (int j = 1;
                     j <= (max_len_next - 1) / 2 - (len_next_unit - 1) / 2;
                     j++) {  // the distance between separator and next data in
                             // " "
                  output_table += " ";
                }
              } else {  // the penultimate
                for (int j = 1; j < max_len_next - len_next_unit + 1;
                     j++) {  // the distance between separator and next data in
                             // " "
                  output_table += " ";
                }
              }
            } else {
              output_table += " ";  // basic separator
            }
          } else {         // if not so deep next hash
            if (i == 1) {  // if first
              for (int j = 0; j < max_len - len_unit;
                   j++) {  // the distance between data and separator in " "
                output_table += " ";
              }
            } else {  // not first
              for (int j = 0; j < (max_len / 2) - (len_unit / 2);
                   j++) {  // the distance between data and separator in " "
                output_table += " ";
              }
            }
            output_table += " ";  // basic separator
            if (i + 1 != size) {  // not the penultimate
              for (int j = 0; j < (max_len_next - 1) / 2;
                   j++) {  // the distance between separator and next empty data
                           // in " "
                output_table += " ";
              }
            } else {  // the penultimate
              for (int j = 0; j < (max_len_next - 1);
                   j++) {  // the distance between separator and next empty data
                           // in " "
                output_table += " ";
              }
            }
          }
        }
      } else {  // if not so deep
        int len_next = 1;
        int ruler = 9;
        if (u < deep[(i + 1) % size]) {  // if next so deep
          auto jt = table[(i + 1) % size].begin();
          std::advance(jt, u);
          int element_next = *jt;
          while (ruler < element_next) {  // find lenth next
            ruler = ruler * 10 + 9;
            len_next = len_next + 1;
          }
        }
        output_table += " ";  // basic separator
        int max_len = table_size[i % size];
        if (i != size) {  // not last
          int max_len_next = table_size[(i + 1) % size];
          if (i == 1) {  // first
            for (int j = 1; j < max_len;
                 j++) {  // the distance between empty data and separator in " "
              output_table += " ";
            }
            output_table += " ";  // basic separator
            if (i + 1 != size) {  // not the penultimate
              for (int j = 1; j <= (max_len_next - 1) / 2 - (len_next - 1) / 2;
                   j++) {  // the distance between separator and next data(or
                           // empty data) in " "
                output_table += " ";
              }
            } else {  // the penultimate
              for (int j = 1; j < max_len_next - (len_next - 1) / 2;
                   j++) {  // the distance between separator and next data(or
                           // empty data) in " "
                output_table += " ";
              }
            }
          } else if (i < size) {  // if not first
            for (int j = 0; j < ((max_len) / 2);
                 j++) {  // the distance between empty data and separator in " "
              output_table += " ";
            }
            output_table += " ";  // basic separator
            if (i + 1 != size) {
              for (int j = 1; j <= (max_len_next - 1) / 2 - (len_next - 1) / 2;
                   j++) {  // the distance between separator and next data(or
                           // empty data) in " "
                output_table += " ";
              }
            }
          }
        }
      }
    }
    output_table += "\n";  // next line
  }
  std::cout << output_table;  // out the table
}

int check_command(const std::string& str) {
  if (str == "add") {
    return 1;
  } else if (str == "remove") {
    return 2;
  } else if (str == "check") {
    return 3;
  } else if (str == "exit") {
    return 0;
  } else {
    return -1;
  }
}
bool isInt(const std::string& str) {
  try {
    int i = std::stoi(str);             // Convert string to integer
  } catch (std::invalid_argument& e) {  // Catch invalid argument exception
    return false;
  } catch (std::out_of_range& e) {  // Catch out of range exception
    return false;
  }
  return true;
}
int SYSTEMis(const std::string& str) {
  if (str == "windows") {  // Check if str is "windows"
    return 1;
  } else if (str == "linux") {  // Check if str is "linux"
    return 2;
  } else {  // Return 0 if str is not "windows" or "linux"
    return 0;
  }
}
void cleaner(const std::string& str) {
  if (str == "clear") {  // Check if str is "clear"
    system("clear");     // Clear console for Linux/Unix based systems
  } else {               // If str is not "clear"
    system("cls");       // Clear console for Windows based systems
  }
}
void out_HELPER(const std::string& str) {
  if (str == "HELP") {
    std::cout
        << "\nThis program implements the output of a hash table\nTo do this, "
           "the program first accepts the upper size limit (the limit can take "
           "values from 2 to 10)\nAfter that, the program switches to its main "
           "table output mode\nThe program understands the following "
           "commands:\nadd-adds an element to the table.\nremove-removes an "
           "item from the table.\ncheck-checks the presence of an element in "
           "the table, after which the result is displayed on top of the "
           "table.\nexit-terminates the program.\n\n";
  }
}

int inputSIZE(const std::string& str) {
  if (isInt(str)) {
    int SIZE = std::stoi(str);
    if (SIZE > 1 and SIZE < 11) {
      return 1;
    } else {
      return 2;
    }
  } else {
    return 3;
  }
}

int output_ADD(HashTable ht, const std::string& str) {
  if (isInt(str)) {
    if (std::stoi(str) < 0) {
      return 3;
    } else if (ht.search(std::stoi(str))) {
      return 2;
    } else {
      return 1;
    }
  } else {
    return 3;
  }
}

int output_REMOVE(HashTable ht, const std::string& str) {
  if (isInt(str)) {
    if (std::stoi(str) < 0) {
      return 3;
    } else if (ht.search(std::stoi(str))) {
      return 1;
    } else {
      return 2;
    }
  } else {
    return 3;
  }
}
int output_CHECK(HashTable ht, const std::string& str) {
  if (isInt(str)) {
    if (std::stoi(str) < 0) {
      return 3;
    } else if (ht.search(std::stoi(str))) {
      return 1;
    } else {
      return 2;
    }
  } else {
    return 3;
  }
}

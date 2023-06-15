/**
 * @file HashTable.h
 * @brief This is a hash table implementation using separate chaining
 * @author [Your Name]
 * @date [Date]
 */

#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <cstdlib>
#include <iostream>
#include <list>
#include <vector>

/**
 * @class HashTable
 * @brief This is a hash table implementation using separate chaining
 */
class HashTable {
 private:
  int size;                          /**< Size of the hash table */
  std::vector<std::list<int>> table; /**< Hash table */
  std::vector<int>
      table_size; /**< Maximum size of the integers stored in each bucket */
  std::vector<int> deep; /**< Depth of each bucket */

  /**
   * @brief Computes the hash value of the given key
   * @param key An integer value
   * @return The hash value of the key
   */
  int hash(int key);

  /**
   * @brief Checks the maximum size of the integers stored in a bucket and
   * updates the table_size vector
   * @param key An integer value
   */
  void check_table_size(int key);

  /**
   * @brief Updates the depth of a bucket
   * @param key An integer value
   * @param mod A modifier value to add or subtract from the current depth
   */
  void change_deep(int key, int mod);

 public:
  /**
   * @brief Constructor for HashTable class
   * @param size The size of the hash table
   */
  HashTable(int size);

  /**
   * @brief Destructor for HashTable class
   */
  ~HashTable() = default;

  /**
   * @brief Inserts a key into the hash table
   * @param key An integer value to be inserted
   */
  void insert(int key);

  /**
   * @brief Removes a key from the hash table
   * @param key An integer value to be removed
   */
  void remove(int key);

  /**
   * @brief Searches for a key in the hash table
   * @param key An integer value to be searched
   * @return True if the key is found, false otherwise
   */
  bool search(int key);

  /**
   * @brief Prints the contents of the hash table
   */
  void print();

  /**
   * @brief Prints the maximum size of the integers stored in each bucket
   */
  void print_size();

  /**
   * @brief Prints the depth of each bucket
   */
  void print_deep();

  /**
   * @brief Returns the maximum size of the integers stored in each bucket
   * @return A vector of integers representing the maximum size of the integers
   * stored in each bucket
   */
  std::vector<int> get_table_size();

  /**
   * @brief Returns the depth of each bucket
   * @return A vector of integers representing the depth of each bucket
   */
  std::vector<int> get_deep();

  /**
   * @brief Returns the hash table
   * @return A vector of lists representing the hash table
   */
  std::vector<std::list<int>> get_table();
};

/**
 * @brief Prints the contents of the hash table in a readable format.
 *
 * @param size The size of the hash table.
 * @param table_size The maximum length of data for each hash.
 * @param deep The number of elements for each hash.
 * @param table The hash table itself.
 *
 * The function takes in the size of the hash table, the maximum length of data
 * for each hash, the number of elements for each hash, and the hash table
 * itself. Its task is to output the contents of the hash table in a readable
 * format. The function does not return anything.
 *
 * The function makes use of the following variables:
 * - std::string output_table: a string that will store all the elements for
 * output. It is printed to the console at the end.
 * - int max_len: the maximum length of an element stored in the current hash.
 * - int max_len_next: the same as max_len, but for the next hash.
 * - int max_deep: the maximum number of values for one hash among all hashes
 * (determines the number of levels in the table).
 * - int unit_deep: an iterable object for finding max_deep.
 * - int element: a single value stored in the table.
 * - int ruler: a measure for determining the length of element.
 * - int element_next: the same as element, but for elements at a different hash
 * level.
 */

void out_HashTable(int size, std::vector<int> table_size, std::vector<int> deep,
                   std::vector<std::list<int>> table);

/**
 * @brief Checks the command entered by the user.
 *
 * This function takes a string as input and checks if it matches with any of
 * the predefined commands. If the string matches with any of the commands, it
 * returns a corresponding integer value. If the string does not match with any
 * of the commands, it returns -1.
 *
 * @param str The input string to be checked.
 * @return Returns an integer value based on the input string.
 *          1 - If the string matches with "add".
 *          2 - If the string matches with "remove".
 *          3 - If the string matches with "check".
 *          0 - If the string matches with "exit".
 *         -1 - If the string does not match with any of the predefined
 * commands.
 */
int check_command(const std::string& str);

/**
 * @brief Checks if a given string can be converted to an integer
 *
 * @param str The string to be checked
 * @return true if str can be converted to an integer, false otherwise
 */
bool isInt(const std::string& str);

/**
 * @brief Determines the operating system based on a given string
 *
 * @param str The string to be checked
 * @return 1 if str is "windows", 2 if str is "linux", 0 otherwise
 */
int SYSTEMis(const std::string& str);

/**
 * @brief Clears the console based on a given string
 *
 * @param str The string to be checked
 */
void cleaner(const std::string& str);

/**
 * @brief Helper function for printing program instructions.
 *
 * This function prints the instructions for using the hash table program.
 * The program first accepts the upper size limit (the limit can take values
 * from 2 to 10). After that, the program switches to its main table output
 * mode. The program understands the following commands:
 *  - add: adds an element to the table.
 *  - remove: removes an item from the table.
 *  - check: checks the presence of an element in the table, after which the
 * result is displayed on top of the table.
 *  - exit: terminates the program.
 *
 * @param str The input string to check if it matches "HELP".
 * @return void
 */
void out_HELPER(const std::string& str);

/**
 * @brief Function for checking and validating input size limit.
 *
 * This function checks if the input string is an integer and validates it as
 * the size limit for the hash table. The input limit should be between 2 and
 * 10, inclusive.
 *
 * @param str The input string to be checked and validated.
 * @return An integer value indicating the validation result:
 *  - 1: the input string is a valid integer within the allowed size limit.
 *  - 2: the input string is a valid integer, but outside the allowed size
 * limit.
 *  - 3: the input string is not a valid integer.
 */
int inputSIZE(const std::string& str);

/**
 * @brief Function for adding an element to the hash table.
 *
 * This function adds an element to the hash table if the input string is a
 * valid integer and the element is not already in the table.
 *
 * @param ht The HashTable object to which the element will be added.
 * @param str The input string to be checked and added as an element to the hash
 * table.
 * @return An integer value indicating the result of the operation:
 *  - 1: the element was successfully added to the table.
 *  - 2: the element is already in the table.
 *  - 3: the input string is not a valid integer.
 */
int output_ADD(HashTable ht, const std::string& str);

/**
 * @brief Function for removing an element from the hash table.
 *
 * This function removes an element from the hash table if the input string is a
 * valid integer and the element is in the table.
 *
 * @param ht The HashTable object from which the element will be removed.
 * @param str The input string to be checked and removed as an element from the
 * hash table.
 * @return An integer value indicating the result of the operation:
 *  - 1: the element was successfully removed from the table.
 *  - 2: the element is not in the table.
 *  - 3: the input string is not a valid integer.
 */
int output_REMOVE(HashTable ht, const std::string& str);

/**
 * @brief Function for checking an element in the hash table.
 *
 * This function checks if an element is in the hash table if the input string
 * is a valid integer.
 *
 * @param ht The HashTable object to check the presence of the element.
 * @param str The input string to be checked as an element in the hash table.
 * @return An integer value indicating the result of the operation:
 *  - 1: the element is in the table.
 *  - 2: the element is not in the table.
 *  - 3: the input string is not a valid integer.
 */
int output_CHECK(HashTable ht, const std::string& str);

#endif  // HASH_TABLE_H
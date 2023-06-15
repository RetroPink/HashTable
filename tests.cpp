#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "HASHtable.h"
#include "doctest.h"

TEST_CASE("check_command function") {
  SUBCASE("Valid input - add") { CHECK(check_command("add") == 1); }
  SUBCASE("Valid input - remove") { CHECK(check_command("remove") == 2); }
  SUBCASE("Valid input - check") { CHECK(check_command("check") == 3); }
  SUBCASE("Valid input - exit") { CHECK(check_command("exit") == 0); }
  SUBCASE("Invalid input") { CHECK(check_command("abc") == -1); }
}

TEST_CASE("HashTable class") {
    HashTable ht(5);
    ht.insert(5);
    ht.insert(10);
    ht.insert(15);

    SUBCASE("Insert function") {
        CHECK(ht.search(5) == true);
        CHECK(ht.search(10) == true);
        CHECK(ht.search(15) == true);
    }

    SUBCASE("Remove function") {
        ht.remove(10);
        CHECK(ht.search(10) == false);
        CHECK(ht.search(5) == true);
        CHECK(ht.search(15) == true);
    }

    SUBCASE("Search function") {
        CHECK(ht.search(5) == true);
        CHECK(ht.search(10) == true);
        CHECK(ht.search(15) == true);
        CHECK(ht.search(20) == false);
    }


}

TEST_CASE("isInt function") {
  SUBCASE("Valid input - 5") {
    std::string str = "5";
    CHECK(isInt(str) == true);
  }
  SUBCASE("Valid input - -10") {
    std::string str = "-10";
    CHECK(isInt(str) == true);
  }
  SUBCASE("Valid input - 0.5") {
    std::string str = "0.5";
    CHECK(isInt(str) == true);
  }
  SUBCASE("Invalid input - abc") {
    std::string str = "abc";
    CHECK(isInt(str) == false);
  }
}

TEST_CASE("SYSTEMis function") {
  SUBCASE("Valid input - windows") {
    std::string str = "windows";
    CHECK(SYSTEMis(str) == 1);
  }
  SUBCASE("Valid input - linux") {
    std::string str = "linux";
    CHECK(SYSTEMis(str) == 2);
  }
  SUBCASE("Invalid input - abc") {
    std::string str = "abc";
    CHECK(SYSTEMis(str) == 0);
  }
  SUBCASE("Invalid input - empty string") {
    std::string str = "";
    CHECK(SYSTEMis(str) == 0);
  }
}

TEST_CASE("out_HELPER function") {
  SUBCASE("Valid input - HELP") {
    std::string str = "HELP";
    std::stringstream output;
    auto old_cout_buf = std::cout.rdbuf(
        output.rdbuf());  // Redirect cout to output stringstream
    out_HELPER(str);
    std::cout.rdbuf(old_cout_buf);  // Reset cout to old buffer
    CHECK(output.str() ==
          "\nThis program implements the output of a hash table\nTo do this, "
          "the program first accepts the upper size limit (the limit can take "
          "values from 2 to 10)\nAfter that, the program switches to its main "
          "table output mode\nThe program understands the following "
          "commands:\nadd-adds an element to the table.\nremove-removes an "
          "item from the table.\ncheck-checks the presence of an element in "
          "the table, after which the result is displayed on top of the "
          "table.\nexit-terminates the program.\n\n");
  }
  SUBCASE("Invalid input") {
    std::string str = "abc";
    std::stringstream output;
    auto old_cout_buf = std::cout.rdbuf(
        output.rdbuf());  // Redirect cout to output stringstream
    out_HELPER(str);
    std::cout.rdbuf(old_cout_buf);  // Reset cout to old buffer
    CHECK(output.str() == "");
  }
}

TEST_CASE("inputSIZE function") {
  SUBCASE("Valid input - 5") {
    std::string str = "5";
    CHECK(inputSIZE(str) == 1);
  }
  SUBCASE("Valid input - 10") {
    std::string str = "10";
    CHECK(inputSIZE(str) == 1);
  }
  SUBCASE("Invalid input - 0") {
    std::string str = "0";
    CHECK(inputSIZE(str) == 2);
  }
  SUBCASE("Invalid input - 11") {
    std::string str = "11";
    CHECK(inputSIZE(str) == 2);
  }
  SUBCASE("Invalid input - abc") {
    std::string str = "abc";
    CHECK(inputSIZE(str) == 3);
  }
}

TEST_CASE("output_ADD function") {
  HashTable ht(10);
  SUBCASE("Valid input") { CHECK(output_ADD(ht, "5") == 1); }
  SUBCASE("Value already in table") {
    ht.insert(5);
    CHECK(output_ADD(ht, "5") == 2);
  }
  SUBCASE("Invalid input") {
    CHECK(output_ADD(ht, "-5") == 3);
    CHECK(output_ADD(ht, "abc") == 3);
  }
}

TEST_CASE("output_REMOVE function") {
  HashTable ht(5);
  ht.insert(5);
  ht.insert(10);
  ht.insert(15);

  SUBCASE("Valid input - 5") {
    std::string str = "5";
    CHECK(output_REMOVE(ht, str) == 1);
  }
  SUBCASE("Invalid input - -10") {
    std::string str = "-10";
    CHECK(output_REMOVE(ht, str) == 3);
  }
  SUBCASE("Invalid input - abc") {
    std::string str = "abc";
    CHECK(output_REMOVE(ht, str) == 3);
  }
  SUBCASE("Not found in hash table") {
    std::string str = "20";
    CHECK(output_REMOVE(ht, str) == 2);
  }
}

TEST_CASE("output_CHECK function") {
  HashTable ht(10);
  ht.insert(5);
  SUBCASE("Valid input - value in table") { CHECK(output_CHECK(ht, "5") == 1); }
  SUBCASE("Valid input - value not in table") {
    CHECK(output_CHECK(ht, "10") == 2);
  }
  SUBCASE("Invalid input") {
    CHECK(output_CHECK(ht, "-5") == 3);
    CHECK(output_CHECK(ht, "abc") == 3);
  }
}

TEST_CASE("output_CHECK function") {
  // Creates an instance of the HashTable class and inserts three values to it
  HashTable ht(5);
  ht.insert(10);
  ht.insert(15);

  // Redirects the standard output stream to a stringstream object to
  // capture the output of the out_HashTable function
  std::stringstream ss;
  std::streambuf* old_cout = std::cout.rdbuf(ss.rdbuf());

  // Calls the out_HashTable function with the hash table size, table size,
  // deep, and table as arguments
  out_HashTable(5, ht.get_table_size(), ht.get_deep(), ht.get_table());

  // Restores the standard output stream
  std::cout.rdbuf(old_cout);

  // Defines the expected and actual output strings and checks if they match
  std::string expected_output = "\ntable\n1-2-3-4--5\n| | | |  |\n        10\n         |\n        15\n";
  std::string actual_output = ss.str();
  CHECK(actual_output == expected_output);
}
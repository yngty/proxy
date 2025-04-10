///////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2002 - 2011.
//  Copyright 2011 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_
//
// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#include "setup.hpp"
#include "table_type.hpp"

#include <boost/math/special_functions/bessel.hpp>
#include "test_bessel_j.hpp"

void expected_results()
{
   //
   // Define the max and mean errors expected for
   // various compilers and platforms.
   //

   add_expected_result(
      ".*",                          // compiler
      ".*",                          // stdlib
      ".*",                          // platform
      ".*",                  // test type(s)
      ".*J0.*Tricky.*",              // test data group
      ".*", 400000000, 400000000);   // test function
   add_expected_result(
      ".*",                          // compiler
      ".*",                          // stdlib
      ".*",                          // platform
      ".*",                  // test type(s)
      ".*J1.*Tricky.*",              // test data group
      ".*", 10000000, 5000000);       // test function
   add_expected_result(
      ".*",                          // compiler
      ".*",                          // stdlib
      ".*",                          // platform
      ".*",                  // test type(s)
      ".*JN.*Integer.*",              // test data group
      ".*", 50000, 15000);       // test function
   add_expected_result(
      ".*",                          // compiler
      ".*",                          // stdlib
      ".*",                          // platform
      ".*",                  // test type(s)
      ".*(JN|j).*|.*Tricky.*",       // test data group
      ".*", 7000, 3000);               // test function
   add_expected_result(
      ".*",                          // compiler
      ".*",                          // stdlib
      ".*",                          // platform
      ".*",                  // test type(s)
      ".*",                          // test data group
      ".*", 40, 20);                 // test function
   //
   // Finish off by printing out the compiler/stdlib/platform names,
   // we do this to make it easier to mark up expected error rates.
   //
   std::cout << "Tests run with " << BOOST_COMPILER << ", "
      << BOOST_STDLIB << ", " << BOOST_PLATFORM << std::endl;
}

template <class T>
void test(T t, const char* p)
{
   test_bessel(t, p);
}


BOOST_AUTO_TEST_CASE( test_main )
{
   expected_results();
   ALL_TESTS
}




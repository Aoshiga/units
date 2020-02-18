#include "Units.h"

#include <iostream>

#include <gtest/gtest.h>

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST(DEBUG, DEBUG) {
  using namespace phy::literals;

  // auto velocity = 100000_metres / 3600_seconds; // 100 km/h
  phy::Length length = 100_metres;

//   auto test = phy::Qty<phy::Metre>(0);
//   auto test2 = phy::Qty<phy::Metre>(2);

//   auto test3 = test += test2;

// std::cout<<test3.value;

  //auto velocity = 100000_metres / 3600_seconds; // 100 km/h
  /*phy::Qty<Metre, std ::milli> mm(32);
  auto nm = phy ::qtyCast<phy ::Qty<Metre, std ::nano>>(mm);*/
}

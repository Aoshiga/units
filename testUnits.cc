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
  auto length = 100_metres + 10_metres;
  /*phy::Qty<Metre, std ::milli> mm(32);
  auto nm = phy ::qtyCast<phy ::Qty<Metre, std ::nano>>(mm);*/
}

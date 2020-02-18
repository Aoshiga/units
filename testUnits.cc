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
  phy::Length length = 1000_metres;
  phy::Length length2 = 100_metres;

  auto result = length2 + length;

  std::cout << result.value << std::endl;
  auto result2 = length2 - length;
  std::cout << result2.value << std::endl;

  auto result3 = length2 * length;
  std::cout << result3.value << std::endl;

  //   auto test = phy::Qty<phy::Metre>(0);
  //   auto test2 = phy::Qty<phy::Metre>(2);

  //   auto test3 = test += test2;

  // std::cout<<test3.value;

  // auto velocity = 100000_metres / 3600_seconds; // 100 km/h
  /*phy::Qty<Metre, std ::milli> mm(32);
  auto nm = phy ::qtyCast<phy ::Qty<Metre, std ::nano>>(mm);*/
}

TEST(Metres, AddTwoMetres) {
  using namespace phy::literals;

  // auto velocity = 100000_metres / 3600_seconds; // 100 km/h
  phy::Length length = 1000_metres;
  phy::Length length2 = 100_metres;

  auto result = length2 + length;

  std::cout << result.value << std::endl;

  EXPECT_EQ(result.value, 1100);
}

TEST(Metres, SubstractTwoMetres) {
  using namespace phy::literals;

  // auto velocity = 100000_metres / 3600_seconds; // 100 km/h
  phy::Length length = 1000_metres;
  phy::Length length2 = 100_metres;
  auto result = length2 - length;

  std::cout << result.value << std::endl;

  EXPECT_EQ(result.value, -900);
}

TEST(Metres, MultiplyLengths) {
  using namespace phy::literals;

  // auto velocity = 100000_metres / 3600_seconds; // 100 km/h
  phy::Length length = 24_metres;
  phy::Length length2 = 84_metres;
  auto expected = 24 * 84;
  auto result = length2 * length;

  std::cout << result.value << std::endl;

  EXPECT_EQ(result.value, expected);
}


TEST(Metres, MilliAdd) {
  using namespace phy::literals;
  
  // auto velocity = 100000_metres / 3600_seconds; // 100 km/h
  phy::Length length = 5_metres;
  phy::Qty<phy::Metre, std::milli> length2(3); // 3 mm
  auto result = length + length2;
  std::cout << result.value << std::endl;
  EXPECT_EQ(result.value, 5003);
}

TEST(Metres, MilliMult) {
  using namespace phy::literals;
  
  // auto velocity = 100000_metres / 3600_seconds; // 100 km/h
  phy::Length length = 5_metres;
  phy::Qty<phy::Metre, std::milli> length2(3); // 3 mm
  auto result = length * length2;

  std::cout << result.value << std::endl;
  EXPECT_EQ(result.value, 15000);
}
TEST(Metres, Millidivide) {
  using namespace phy::literals;
  
  // auto velocity = 100000_metres / 3600_seconds; // 100 km/h
  phy::Length length = 5_metres;
  phy::Qty<phy::Metre, std::milli> length2(3); // 3 mm
  auto result = length / length2;

  std::cout << result.value << std::endl;
 // EXPECT_EQ(result.value, 15000);
}
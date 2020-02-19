#include "Units.h"

#include <iostream>

#include <gtest/gtest.h>
using namespace phy;

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST(Add, Metres) {
  using namespace phy::literals;
  auto length = 100_metres + 10_metres;
  auto resLenght = 110_metres;
  ASSERT_EQ(length.value, resLenght.value);
}

TEST(Add, Metres2) {
  using namespace phy::literals;

  auto val1 = phy::Qty<phy::Metre>(10);
  auto val2 = phy::Qty<phy::Metre>(24);
  auto val3 = val1 + val2;

  std::cout<<val3.value<<"\n";


  auto resVal = phy::Qty<phy::Metre>(34);

  ASSERT_EQ(val3, resVal);
}

TEST(Add, Metres3) {
  using namespace phy::literals;

  phy::Qty<phy::Metre>val1(10);
  phy::Qty<phy::Metre>val2(24);
  val1 += val2;

  std::cout<<val1.value<<"\n";


  phy::Qty<phy::Metre>resVal(34);

  ASSERT_EQ(val1, resVal);
}

// TEST(Add, OtherRatio) {
//   using namespace phy::literals;
//
//   phy::Qty <Metre, std::milli > val1(10);
//   phy::Qty <Metre, std::milli > val2(24);
//   val1 += val2;
//
//   phy::Qty<Metre,std::milli>resVal(34);
//
//   ASSERT_EQ(val1, resVal);
// }

TEST(DEBUG, Test1) {
  phy::Qty <phy::Metre, std::milli> mm (32);
  auto nm = phy::qtyCast <phy::Qty <phy::Metre , std::kilo >>(mm);

  std::cout<<nm.value<<"\n";

  // ASSERT_EQ(length, 110);
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

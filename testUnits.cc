#include "Units.h"

#include <iostream>

#include <gtest/gtest.h>
using namespace phy;

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST(Cast, DeciToKilo) {
  phy::Qty <phy::Metre, std::deci> mm (101245);
  auto nm = phy::qtyCast <phy::Qty <phy::Metre , std::kilo >>(mm);

  std::cout << nm.value << "\n";

  ASSERT_EQ(nm.value, 10);
}


TEST(Cast, FootToMeter){
  phy::Qty <phy::Metre, phy::Foot::Ratio> foot(42);
  auto m = phy::qtyCast <phy::Qty <phy::Metre>>(foot);
  EXPECT_EQ(m.value, 12);
}

TEST(Cast, MeterToMilli){
  phy::Qty <phy::Metre> m(1);
  auto mm = phy::qtyCast <phy::Qty <phy::Metre, std::milli>>(m);
  EXPECT_EQ(mm.value, 1000);
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

TEST(Metres, AddTwoMetres2) {
  using namespace phy::literals;

  auto val1 = phy::Qty<phy::Metre>(10);
  auto val2 = phy::Qty<phy::Metre>(24);
  auto val3 = val1 + val2;

  auto resVal = phy::Qty<phy::Metre>(34);

  ASSERT_EQ(val3.value, resVal.value);
}

TEST(Metres, AddEqual) {
  using namespace phy::literals;

  phy::Qty<phy::Metre> val1(10);
  phy::Qty<phy::Metre> val2(24);
  val1 += val2;

  phy::Qty<phy::Metre> resVal(34);

  ASSERT_EQ(val1.value, resVal.value);
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

TEST(Metres, SubstractEqual) {
  using namespace phy::literals;

  phy::Qty<phy::Metre> val1(30);
  phy::Qty<phy::Metre> val2(24);
  val1 -= val2;

  phy::Qty<phy::Metre> resVal(6);

  ASSERT_EQ(val1.value, resVal.value);
}


TEST(Metres, SubstractMetreMilli) {
  using namespace phy::literals;

  phy::Qty<phy::Metre> val1(30);
  phy::Qty<phy::Metre,std::milli> val2(24);
  auto res = val1 - val2;

  phy::Qty<phy::Metre,std::milli> resVal(29976);

  ASSERT_EQ(res.value, resVal.value);
   auto res2 = val2 - val1;

  ASSERT_EQ(res2.value, -resVal.value);
}

TEST(Metres, SubstractFootMilli) {
  using namespace phy::literals;

  phy::Qty<phy::Metre,Foot::Ratio> val1(30);
  phy::Qty<phy::Metre,std::milli> val2(24);
  auto res = val1 - val2;

  phy::Qty<phy::Metre,std::milli> resVal(9120);

  ASSERT_EQ(res.value, resVal.value);

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

  phy::Length length = 5_metres;
  phy::Qty<phy::Metre, std::milli> length2(3); // 3 mm
  auto result = length * length2; //15000mm2

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

TEST(Ampere, CentiPlusDeci) {
  using namespace phy::literals;

  // auto velocity = 100000_metres / 3600_seconds; // 100 km/h
  phy::Qty<phy::Ampere, std::milli> mm(50); // 50 mm
  phy::Qty<phy::Ampere, std::centi> cm(2);  // 2 cm
  auto result = mm + cm;

  std::cout << result.value << std::endl;
  EXPECT_EQ(result.value, 70);
}

TEST(Units, OperatorPlus) {
  phy ::Qty<phy::Metre, phy::Foot::Ratio> foot(42);
  phy ::Qty<phy::Metre, std ::milli> mm(32);
  phy ::Qty<phy::Metre, std ::milli> mm2(32);
  phy ::Qty<phy::Metre, std ::milli> mm3(42);
  phy ::Qty<phy::Metre> m(10);
  phy ::Qty<phy::Metre, std ::nano> nm(32000000);
  phy ::Qty<phy::Metre, std ::nano> nm2(42000000);
  auto resmm = (mm + mm2);
  EXPECT_EQ(resmm.value, 64);
  auto resmm2 = mm2 + mm;
  EXPECT_EQ(resmm2.value, 64);
  auto resmm3 = foot + m;
  EXPECT_EQ(resmm3.value, 74);
}

// will fail if incorrect ratio operator is used in the implementation
TEST(Units, reusingTheSameQuantity) {
  phy ::Qty<phy::Metre, phy::Foot::Ratio> foot(42);
  phy ::Qty<phy::Metre> m(10);
  phy ::Qty<phy::Metre, std::milli> mm(52);

  auto footMetre = foot + m;
  auto footMetreMetre = footMetre + m;
  auto res3 = footMetre + foot;

  EXPECT_EQ(footMetre.value, 74);
  EXPECT_EQ(footMetreMetre.value, 106);
  EXPECT_EQ(res3.value, 116);
}

TEST(Length, addDiffrentRatios) {
  using namespace phy::literals;

  phy ::Qty<phy::Metre, phy::Foot::Ratio> foot(42);
  phy ::Qty<phy::Metre, std::milli> mm(52);
  auto res = foot + mm;
  EXPECT_EQ(res.value, 12853);


}

TEST(Units, MultipleAdd){
  phy :: Qty <phy::Metre , std :: centi > cm (15);
  phy :: Qty <phy::Metre , std :: milli > mm (123);
  phy :: Qty <phy::Metre > m (1);
  auto res1 = cm + mm; //15cm + 123mm = 273mm
  EXPECT_EQ(res1.value, 273);
  auto res2 = res1 + m; //273mm + 1m = 1273mm
  EXPECT_EQ(res2.value, 1273);
}

TEST(Units, MultipleSubstract){
  phy :: Qty <phy::Metre , std::kilo > km (15);
  phy :: Qty <phy::Metre , std::hecto > hm (100);
  phy :: Qty <phy::Metre > m1 (2000);
  phy :: Qty <phy::Metre > m2 (1500);
  auto res1 = km - hm; //15km - 100hm = 50hm
  EXPECT_EQ(res1.value, 50);
  auto res2 = res1 - m1; // 50hm - 2000m = 3000m
  EXPECT_EQ(res2.value, 3000);
  res2 -= m2; // 3000m - 1500m = 1500m
  EXPECT_EQ(res2.value, 1500);
}

TEST(Units, MultipleMultiplicate){
  phy :: Qty <phy::Metre  > m1 (2);
  phy :: Qty <phy::Metre > m2 (10);
  auto res1 = m1 * m2; //2m * 10 m = 20m2
  EXPECT_EQ(res1.value, 20);
  auto res3 = res1 * m1; // 20m2 * 2m = 40 000 liters = 40 m3
  EXPECT_EQ(res3.value, 40); //Cubed meters
}

TEST(Units, MultipleMultiplicateFoot){
  phy :: Qty <phy::Metre , phy::Foot::Ratio > foot (1);
  phy :: Qty <phy::Metre , std::centi > cm (60);
  phy :: Qty <phy::Metre ,std::milli> mm (1);
  auto res1 = cm * foot; //1 foot * 60cm = 1800cm2
  EXPECT_EQ(res1.value, 1800);
  auto res3 = res1 * mm; // 1800cm2 * 1mm = 4000m
  EXPECT_EQ(res3.value, 621);

}

TEST(Units, MultipleDivide){
  phy :: Qty <phy::Metre , std::kilo > km (12);
  phy :: Qty <phy::Metre , std::hecto > hm (20);
  phy :: Qty <phy::Metre > m (200);
  auto res1 = km / hm; //12km * 20hm = 6hm
  EXPECT_EQ(res1.value, 6);
  //auto res2 = res1 - m; // 6hm * 200m = 3m
  //EXPECT_EQ(res2.value, 3);
}

TEST(Metres, MilliMultiAdd) {
  using namespace phy::literals;

  // auto velocity = 100000_metres / 3600_seconds; // 100 km/h
  phy::Length length = 5_metres;
  phy::Qty<phy::Metre, std::milli> length2(3); // 3 mm
  auto result = length + length2;
  auto result2 = result + length2;
  std::cout << result.value << std::endl;
  std::cout << result2.value << std::endl;

  EXPECT_EQ(result.value, 5003);
 EXPECT_EQ(result2.value, 5006);
}



TEST(Metres, MilliMultiAdd2) {
  using namespace phy::literals;

  // auto velocity = 100000_metres / 3600_seconds; // 100 km/h
  phy::Length length = 5_metres;
  phy::Qty<phy::Metre, std::milli> length2(3); // 3 mm
  auto result =  length2 + length;
  auto result2 =  length2 + result;

  std::cout << result.value << std::endl;
  std::cout << result2.value << std::endl;

  EXPECT_EQ(result.value, 5003);
}
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

TEST(Units, Add) {
  using namespace phy::literals;

  phy::Length length = 1000_metres;
  phy::Length length2 = 100_metres;

  auto result = length2 + length;

  EXPECT_EQ(result.value, 1100);
}

TEST(Units, AddEqual) {
  phy::Qty<phy::Metre> val1(10);
  phy::Qty<phy::Metre> val2(24);
  val1 += val2;

  phy::Qty<phy::Metre> resVal(34);

  ASSERT_EQ(val1.value, resVal.value);
}

TEST(Units, Substract) {
  using namespace phy::literals;

  phy::Length length = 1000_metres;
  phy::Length length2 = 100_metres;
  auto result = length2 - length;

  EXPECT_EQ(result.value, -900);
}

TEST(Units, SubstractEqual) {
  phy::Qty<phy::Metre> val1(30);
  phy::Qty<phy::Metre> val2(24);
  val1 -= val2;

  phy::Qty<phy::Metre> resVal(6);

  ASSERT_EQ(val1.value, resVal.value);
}

TEST(Units, Multiply) {
  using namespace phy::literals;

  phy::Length length = 24_metres;
  phy::Length length2 = 84_metres;
  auto expected = 24 * 84;
  auto result = length2 * length;

  EXPECT_EQ(result.value, expected);
}

TEST(Units, Divide) {
  using namespace phy::literals;

  phy::Length length = 100_metres;
  phy::Length length2 = 25_metres;
  auto expected = 4;
  auto result = length / length2;

  EXPECT_EQ(result.value, expected);
}

TEST(Units, MilliSubstract) {
  phy::Qty<phy::Metre> val1(30);
  phy::Qty<phy::Metre,std::milli> val2(24);
  auto res = val1 - val2;

  phy::Qty<phy::Metre,std::milli> resVal(29976);

  ASSERT_EQ(res.value, resVal.value);
  auto res2 = val2 - val1;

  ASSERT_EQ(res2.value, -resVal.value);
}

TEST(Units, MilliAdd) {
  using namespace phy::literals;

  phy::Length length = 5_metres;
  phy::Qty<phy::Metre, std::milli> length2(3); // 3 mm
  auto result = length + length2;

  EXPECT_EQ(result.value, 5003);
}

TEST(Units, MilliMult) {
  using namespace phy::literals;

  phy::Length length = 5_metres;
  phy::Qty<phy::Metre, std::milli> length2(3); // 3 mm
  auto result = length * length2; //15000mm2

  EXPECT_EQ(result.value, 15000);
}

TEST(Units, Millidivide) {
  using namespace phy::literals;

  phy::Length length = 6_metres;
  phy::Qty<phy::Metre, std::milli> length2(3); // =2000 without unit (ratio = 1/1000)
  auto result = length / length2;

  EXPECT_EQ(result.value, 2000);
}

TEST(Units, SubstractFootMilli) {
  phy::Qty<phy::Metre,Foot::Ratio> val1(30);
  phy::Qty<phy::Metre,std::milli> val2(24);
  auto res = val1 - val2;

  phy::Qty<phy::Metre,std::milli> resVal(9120);

  ASSERT_EQ(res.value, resVal.value);
}

TEST(Units, CentiPlusDeci) {
  phy::Qty<phy::Ampere, std::milli> mm(50); // 50 mm
  phy::Qty<phy::Ampere, std::centi> cm(2);  // 2 cm
  auto result = mm + cm;

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

  auto footMetre = foot + m; //= 74foot
  auto footMetreMetre = footMetre + m; //= 106foot
  auto res3 = footMetre + foot; //= 116foot

  EXPECT_EQ(footMetre.value, 74);
  EXPECT_EQ(footMetreMetre.value, 106);
  EXPECT_EQ(res3.value, 116);
}

TEST(Units, addDiffrentRatios) {
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
  phy :: Qty <phy::Metre > m1 (2);
  phy :: Qty <phy::Metre > m2 (10);
  auto res1 = m1 * m2; //2m * 10 m = 20m2
  EXPECT_EQ(res1.value, 20);
  auto res3 = res1 * m1; // 20m2 * 2m = 40 000 liters = 40 m3
  EXPECT_EQ(res3.value, 40); //Cubed meters
}

TEST(Units, MultipleMultiplicateFoot){
  phy :: Qty <phy::Metre , phy::Foot::Ratio > foot (1);
  phy :: Qty <phy::Metre , std::centi > cm (60);
  phy :: Qty <phy::Metre ,std::milli> mm (2);
  auto res1 = cm * foot; //1 foot * 60cm = 1800cm2
  EXPECT_EQ(res1.value, 1800);
  auto res3 = res1 * mm; // 1800cm2 * 2mm = 36000mm3
  EXPECT_EQ(res3.value, 36000);
}

TEST(Units, MultipleDivide){
  phy :: Qty <phy::Metre , std::kilo > km (12);
  phy :: Qty <phy::Metre , std::hecto > hm (20);
  phy :: Qty <phy::Metre > m (3);
  auto res1 = km / hm; //12km / 20hm = 6 Without Unit
  EXPECT_EQ(res1.value, 6);
  auto res2 = res1 / m; // 6 / 3m = 2m-1
  EXPECT_EQ(res2.value, 2);
}

TEST(Units, MultipleDivideFoot){
  phy :: Qty <phy::Metre , phy::Foot::Ratio > foot (1);
  phy :: Qty <phy::Metre , std::centi > cm (3);
  phy :: Qty <phy::Metre ,std::milli> mm (5);
  auto res1 = foot / cm; //1 foot / 3cm = 10
  EXPECT_EQ(res1.value, 10);
  auto res3 = res1 / mm; // 10 / 5mm = 2mm-1
  EXPECT_EQ(res3.value, 2);
}

TEST(Units, MilliMultiAdd) {
  using namespace phy::literals;

  phy::Length length = 5_metres;
  phy::Qty<phy::Metre, std::milli> length2(3); // 3 mm
  auto result = length + length2;
  auto result2 = result + length2;

  EXPECT_EQ(result.value, 5003);
  EXPECT_EQ(result2.value, 5006);
}

TEST(Units, MilliMultiAdd2) {
  using namespace phy::literals;

  phy::Length length = 5_metres;
  phy::Qty<phy::Metre, std::milli> length2(3); // 3 mm
  auto result =  length2 + length;
  auto result2 =  length2 + result;

  EXPECT_EQ(result.value, 5003);
  EXPECT_EQ(result2.value, 5006);
}

TEST(Units, Speed_MPerS) {
  using namespace phy::literals;

  auto velocity = 100000_metres / 3600_seconds; // 100 km/h = 27m/s

  EXPECT_EQ(velocity.value, 27);
}

TEST(Units, Speed_KmPerH) {
  using namespace phy::literals;

  phy::Qty<phy::Metre, std::kilo> km(100); // 100km
  phy::Qty<phy::Second, std::ratio<3600, 1>> h(1); // 1h

  auto velocity = km/h; // 100 km/h
  EXPECT_EQ(velocity.value, 100);
}

/* check the validity of the units */
TEST(ValidUnit, DivideNoUnitPerMeter){
  phy :: Qty <phy::Unit<0,0,0,0,0,0,0> > noUnit (10);
  phy :: Qty <phy::Metre > m (5);
  phy :: Qty <phy::Unit<-1,0,0,0,0,0,0> > res2(2);
  auto res1 = noUnit / m; //10 / 5m = 2m-1
  EXPECT_EQ(typeid(res1), typeid(res2));
}

TEST(ValidUnit, Velocity){
  using namespace phy::literals;
  phy::Qty<phy::Metre, std::kilo> km(100); // 100km
  phy::Qty<phy::Second, std::ratio<3600, 1>> h(1); // 1h

  auto velocity = km/h; // 100 km/h

  const std::type_info& typeKm = typeid(phy::Qty<phy::Metre, std::kilo>(0));
  const std::type_info& typeSecond = typeid(phy::Qty<phy::Second, std::ratio<3600, 1>>(0));
  const std::type_info& typeVelocity = typeid(phy::Qty<phy::Unit<1,0,-1,0,0,0,0>, std::ratio<5, 18> >(0)); //= std::ratio<1000, 3600>

  EXPECT_EQ(typeid(km), typeKm);
  EXPECT_EQ(typeid(h), typeSecond);
  EXPECT_EQ(typeid(velocity), typeVelocity);
}

#ifndef UNITS_H
#define UNITS_H

#include <cstdint>
#include <ratio>
#include <stdio.h>

//*
namespace phy {

/*
 * A unit defined in terms of the base units
 */
template <int Metre, int Kilogram, int Second, int Ampere, int Kelvin, int Mole,
          int Candela>
struct Unit {
  static constexpr int metre = Metre;
  static constexpr int kilogram = Kilogram;
  static constexpr int second = Second;
  static constexpr int ampere = Ampere;
  static constexpr int kelvin = Kelvin;
  static constexpr int mole = Mole;
  static constexpr int candela = Candela;
};

/*
 * Various type aliases
 */

using Metre = Unit<1, 0, 0, 0, 0, 0, 0>;
using Kilogram = Unit<0, 1, 0, 0, 0, 0, 0>;
using Second = Unit<0, 0, 1, 0, 0, 0, 0>;
using Ampere = Unit<0, 0, 0, 1, 0, 0, 0>;
using Kelvin = Unit<0, 0, 0, 0, 1, 0, 0>;
using Mole = Unit<0, 0, 0, 0, 0, 1, 0>;
using Candela = Unit<0, 0, 0, 0, 0, 0, 1>;
using Radian = Unit<0, 0, 0, 0, 0, 0, 0>;

/*
 * A quantity is a value associated with a unit and a ratio
 */
template <class U, class R = std::ratio<1>> struct Qty {
  using Unit = U;
  using Ratio = R;

  intmax_t value;

  Qty(intmax_t v) { this->value = v; };

  template <typename ROther> Qty &operator+=(Qty<U, ROther> other) {
    this->value = (R::num * this->value * ROther::den) +
                  (ROther::num * other.value * R::den);
    return *this;
  }

  template <typename ROther> Qty &operator-=(Qty<U, ROther> other) {
    this->value = (R::num * this->value * ROther::den) -
                  (ROther::num * other.value * R::den);
    return *this;
  }
};

/*
 * Various quantities
 */

using Length = Qty<Metre>;
using Mass = Qty<Kilogram>;
using Time = Qty<Second>;
using Current = Qty<Ampere>;
using Temperature = Qty<Kelvin>;
using Amount = Qty<Mole>;
using LuminousIntensity = Qty<Candela>;

/*
 * Some weird quantities
 */

using Mile = Qty<Metre, std::ratio<100, 160934>> /* implementation defined */;
using Yard = Qty<Metre, std::ratio<10000, 10936>> /* implementation defined */;
using Foot = Qty<Metre, std::ratio<10000, 32808>> /* implementation defined */;
using Inch = Qty<Metre, std::ratio<10000, 393700>> /* implementation defined */;

/*
 * Cast function between two quantities
 */
template <typename ResQty, typename U, typename R>
ResQty qtyCast(Qty<U, R> &other) {
  return Qty<U, typename ResQty::Ratio>(
      (other.value * R::num * ResQty::Ratio::den) /
      (R::den * ResQty::Ratio::num));
}

/*
 * Comparison operators
 */

template <typename U, typename R1, typename R2>
bool operator==(Qty<U, R1> q1, Qty<U, R2> q2) {
  auto q2_convert = qtyCast<Qty<U, R1>>(q2);
  return q2_convert.value == q1.value;
}

template <typename U, typename R1, typename R2>
bool operator!=(Qty<U, R1> q1, Qty<U, R2> q2) {
  auto q2_convert = qtyCast<Qty<U, R1>>(q2);
  return q2_convert.value != q1.value;
}

template <typename U, typename R1, typename R2>
bool operator<(Qty<U, R1> q1, Qty<U, R2> q2) {
  auto q2_convert = qtyCast<Qty<U, R1>>(q2);
  return q2_convert.value < q1.value;
}

template <typename U, typename R1, typename R2>
bool operator<=(Qty<U, R1> q1, Qty<U, R2> q2) {
  auto q2_convert = qtyCast<Qty<U, R1>>(q2);
  return q2_convert.value <= q1.value;
}

template <typename U, typename R1, typename R2>
bool operator>(Qty<U, R1> q1, Qty<U, R2> q2) {
  auto q2_convert = qtyCast<Qty<U, R1>>(q2);
  return q2_convert.value > q1.value;
}

template <typename U, typename R1, typename R2>
bool operator>=(Qty<U, R1> q1, Qty<U, R2> q2) {
  auto q2_convert = qtyCast<Qty<U, R1>>(q2);
  return q2_convert.value >= q1.value;
}

/*
 * Arithmetic operators
 */

/*
 * to generate the new ratio on compilation
 */
template <typename U, typename R1, typename R2>
using AdditionReturnRatio =
    typename std::conditional<std::ratio_less<R1, R2>::value, R1, R2>::type;

template <typename U, typename R1, typename R2>
Qty<U, AdditionReturnRatio<U, R1, R2>> operator+(Qty<U, R1> q1, Qty<U, R2> q2) {
  intmax_t sum = q1.value + q2.value;

  if (std::ratio_greater<R1, R2>::value) {
    auto q1_convert = qtyCast<Qty<U, R2>>(q1);
    sum = q1_convert.value + q2.value;
  } else if (std::ratio_less<R1, R2>::value) {
    auto q2_convert = qtyCast<Qty<U, R1>>(q2);
    sum = q2_convert.value + q1.value;
  }

  return Qty<U, AdditionReturnRatio<U, R1, R2>>(sum);
}

/*
 * to generate the new ratio on compilation
 */
template <typename R1, typename R2>
using SubReturnRatio =
    typename std::conditional<std::ratio_less<R1, R2>::value, R1, R2>::type;

template <typename U, typename R1, typename R2>
Qty<U, SubReturnRatio<R1, R2>> operator-(Qty<U, R1> q1, Qty<U, R2> q2) {

  intmax_t sub = q1.value - q2.value;

  if (std::ratio_greater<R1, R2>::value) {
    auto q1_convert = qtyCast<Qty<U, R2>>(q1);
    sub = q1_convert.value - q2.value;
  } else if (std::ratio_less<R1, R2>::value) {
    auto q2_convert = qtyCast<Qty<U, R1>>(q2);
    sub = q1.value - q2_convert.value;
  }

  return Qty<U, SubReturnRatio<R1, R2>>(sub);
}

/*
 * Calculate the return Unit on compilation
 */
template <typename U1, typename U2>
using MultiReturnUnit = Unit<U1::metre + U2::metre, U1::kilogram + U2::kilogram,
                             U1::second + U2::second, U1::ampere + U2::ampere,
                             U1::kelvin + U2::kelvin, U1::mole + U2::mole,
                             U1::candela + U2::candela>;

/*
 * If U1 == U2 we convert the unit in the smaller ratio and apply the multiplication
 * Else we combine the ratio of the two value
*/

template <typename R1, typename R2>
using MultiReturnRatio =
    typename std::conditional<std::ratio_less<R1, R2>::value, R1, R2>::type;

template <typename U1, typename R1, typename U2, typename R2>
Qty<MultiReturnUnit<U1, U2>, MultiReturnRatio<R1, R2>>
operator*(Qty<U1, R1> q1, Qty<U2, R2> q2) {

  intmax_t mul = q1.value * q2.value;

  if (std::ratio_greater<R1, R2>::value) {

    auto q1_convert = qtyCast<Qty<U1, R2>>(q1);
    mul = q1_convert.value * q2.value;

  } else if (std::ratio_less<R1, R2>::value) {

    auto q2_convert = qtyCast<Qty<U2, R1>>(q2);
    mul = q1.value * q2_convert.value;
  }

  return Qty<MultiReturnUnit<U1,U2>, MultiReturnRatio<R1, R2>>(mul);
}

template <typename U1,typename U2>
using DivideReturnUnit = Unit<U1::metre - U2::metre, U1::kilogram - U2::kilogram,
                             U1::second - U2::second, U1::ampere - U2::ampere,
                             U1::kelvin - U2::kelvin, U1::mole - U2::mole,
                             U1::candela - U2::candela>;

/*
  * If DivideReturnUnit is composed with only 0, the division is without unit.
  * In this case the ratio is 0, else it's a combine of the ratio of the 2 number.
*/
template <typename R1, typename R2>
using DivideReturnRatio =
    typename std::conditional<std::ratio_less<R1, R2>::value, R1, R2>::type;

template <typename U1, typename R1, typename U2, typename R2>
Qty<DivideReturnUnit<U1,U2>, typename std::conditional<
      (DivideReturnUnit<U1, U2>::metre == 0 && DivideReturnUnit<U1, U2>::kilogram == 0 &&
        DivideReturnUnit<U1, U2>::second == 0 && DivideReturnUnit<U1, U2>::ampere == 0 &&
        DivideReturnUnit<U1, U2>::kelvin == 0 && DivideReturnUnit<U1, U2>::mole == 0 &&
        DivideReturnUnit<U1, U2>::candela == 0), std::ratio<1>, std::ratio_divide<R1, R2>>::type>
operator/(Qty<U1, R1> q1, Qty<U2, R2> q2) {

  const bool condition = (DivideReturnUnit<U1, U2>::metre == 0 && DivideReturnUnit<U1, U2>::kilogram == 0 &&
                              DivideReturnUnit<U1, U2>::second == 0 && DivideReturnUnit<U1, U2>::ampere == 0 &&
                              DivideReturnUnit<U1, U2>::kelvin == 0 && DivideReturnUnit<U1, U2>::mole == 0 &&
                              DivideReturnUnit<U1, U2>::candela == 0);

  typedef
    typename std::conditional<condition, std::ratio<1>, std::ratio_divide<R1, R2>>::type newRatio;

  intmax_t div = (q1.value / q2.value);// * (R1::num*R2::den)/(R1::den*R2::num);

  if (condition && std::ratio_greater<R1, R2>::value) {
    auto q1_convert = qtyCast<Qty<U1 , R2>>(q1);
    div = q1_convert.value / q2.value;
  } else if (condition && std::ratio_less<R1, R2>::value) {
    auto q2_convert = qtyCast<Qty<U2, R1>>(q2);
    div = q1.value / q2_convert.value;
  }

  return Qty<DivideReturnUnit<U1,U2>, newRatio>(div);
}

namespace literals {
  /*
   * Some user-defined literals
   */

  Length operator"" _metres(unsigned long long int val) {
    return Qty<Metre, std::ratio<1, 1>>(val);
  }
  Mass operator"" _kilograms(unsigned long long int val) {
    return Qty<Kilogram, std::ratio<1, 1>>(val);
  }
  Time operator"" _seconds(unsigned long long int val) {
    return Qty<Second, std::ratio<1, 1>>(val);
  }
  Current operator"" _amperes(unsigned long long int val) {
    return Qty<Ampere, std::ratio<1, 1>>(val);
  }
  Temperature operator"" _kelvins(unsigned long long int val) {
    return Qty<Kelvin, std::ratio<1, 1>>(val);
  }
  Amount operator"" _moles(unsigned long long int val) {
    return Qty<Mole, std::ratio<1, 1>>(val);
  }
  LuminousIntensity operator"" _candelas(unsigned long long int val) {
    return Qty<Candela, std::ratio<1, 1>>(val);
  }

} // namespace literals

namespace details {
  // Unit < Metre , Kilo, Second, Amperere, Kelvin, Mole, Candela>
  // https://fr.wikipedia.org/wiki/Unit%C3%A9s_d%C3%A9riv%C3%A9es_du_Syst%C3%A8me_international
  using Acceleration = Unit<1, 0, -2, 0, 0, 0, 0>; //m.s-2
  using AngularAcceleration = Unit<0, 0, -2, 0, 0, 0, 0>; //rad.s-2
  using AngularSpeed = Unit<0, 0, -1, 0, 0, 0, 0>; //rad.s-2
  using ElectricCapacity = Unit<-2, -1, 4, 2, 0, 0, 0>; //Farad
  using ThermicCapacity = Unit<2, 1, -2, 0, -1, 0, 0>; //Joule par kelvin
  using MagneticField = Unit<0, 1, -2, -1, 0, 0, 0>; //Tesla
  using ElectricCharge = Unit<0, 0, 1, 1, 0, 0, 0>; //Coulomb
  using MolarConcentration = Unit<-3, 0, 0, 0, 0, 1, 0>; //mol.m-3
  using Couple = Unit<2, 1, -2, 0, 0, 0, 0>; //Newton.m-1
  using VolumetricFlowRate = Unit<3, 0, -1, 0, 0, 0, 0>; //m3.s-1
  using Energy = Unit<2, 1, -2, 0, 0, 0, 0>; //Joule
  using Force = Unit<1, 1, -2, 0, 0, 0, 0>; //Newton
  using Frequency = Unit<0, 0, -1, 0, 0, 0, 0>; //Hertz
  using Density = Unit<-3, 1, 0, 0, 0, 0, 0>; //kg.m-3
  using Pressure = Unit<-1, 1, -2, 0, 0, 0, 0>; //Pascal
  using Power = Unit<2, 1, -3, 0, 0, 0, 0>; //Watt
  using ElectricalResistance = Unit<2, 1, -3, -2, 0, 0, 0>; //Ohm
  using Superficie = Unit<2, 0, 0, 0, 0, 0, 0>; //m2
  using Speed = Unit<1, 0, -1, 0, 0, 0, 0>; //m.s-1
  using Voltage = Unit<2, 1, -3, -1, 0, 0, 0>; //Volt
  using Volume = Unit<3, 0, 0, 0, 0, 0, 0>; //m3


} // namespace details

} // namespace phy

#endif // UNITS_H

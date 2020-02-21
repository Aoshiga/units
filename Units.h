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
// using Radian    = /* implementation defined */;

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
template <typename U, typename R1, typename R2>
using SubReturnRatio =
    typename std::conditional<std::ratio_less<R1, R2>::value, R1, R2>::type;

template <typename U, typename R1, typename R2>
Qty<U, SubReturnRatio<U, R1, R2>> operator-(Qty<U, R1> q1, Qty<U, R2> q2) {

  intmax_t sub = q1.value - q2.value;

  if (std::ratio_greater<R1, R2>::value) {
    auto q1_convert = qtyCast<Qty<U, R2>>(q1);
    sub = q1_convert.value - q2.value;
  } else if (std::ratio_less<R1, R2>::value) {
    auto q2_convert = qtyCast<Qty<U, R1>>(q2);
    sub = q1.value - q2_convert.value;
  }

  return Qty<U, SubReturnRatio<U, R1, R2>>(sub);
}

/*
 * Calculate the return Unit on compilation
 */
template <typename U1, typename U2>
using MultiReturnUnit = Unit<U1::metre + U2::metre, U1::kilogram + U2::kilogram,
                             U1::second + U2::second, U1::ampere + U2::ampere,
                             U1::kelvin + U2::kelvin, U1::mole + U2::mole,
                             U1::candela + U2::candela>;

template <typename U1, typename R1, typename U2, typename R2>
Qty<MultiReturnUnit<U1, U2>, std::ratio_divide<R1, R2>>
operator*(Qty<U1, R1> q1, Qty<U2, R2> q2) {

  typedef std::ratio_divide<R1, R2> newRatio;

  intmax_t mul = q1.value * q2.value;
  if (std::ratio_greater<R1, R2>::value) {

    auto q1_convert = qtyCast<Qty<U1, R2>>(q1);
    mul = q1_convert.value * q2.value;

  } else if (std::ratio_less<R1, R2>::value) {

    auto q2_convert = qtyCast<Qty<U2, R1>>(q2);
    mul = q1.value * q2_convert.value;
  }

  return Qty<MultiReturnUnit<U1,U2>, newRatio>(mul);
}

template <typename U1,typename U2>
using DivideReturnUnit = Unit<U1::metre - U2::metre, U1::kilogram - U2::kilogram,
                             U1::second - U2::second, U1::ampere - U2::ampere,
                             U1::kelvin - U2::kelvin, U1::mole - U2::mole,
                             U1::candela - U2::candela>;

template <typename U1, typename R1, typename U2, typename R2>
Qty<DivideReturnUnit<U1,U2>, typename std::conditional<std::ratio_less<R1, R2>::value, R1, R2>::type>
operator/(Qty<U1, R1> q1, Qty<U2, R2> q2) {

  typedef
      typename std::conditional<std::ratio_less<R1, R2>::value, R1, R2>::type
          newRatio;

  intmax_t div = q1.value * q2.value;

  if (std::ratio_greater<R1, R2>::value) {
    auto q1_convert = qtyCast<Qty<U1, R2>>(q1);
    div = q1_convert.value / q2.value;
  } else if (std::ratio_less<R1, R2>::value) {
    auto q2_convert = qtyCast<Qty<U1, R1>>(q2);
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
using Velocity = Unit<1, 0, -1, 0, 0, 0, 0>;
using Litre = Unit<3, 0, 0, 0, 0, 0, 0>;
} // namespace details

} // namespace phy

#endif // UNITS_H

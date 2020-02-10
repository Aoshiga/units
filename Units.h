#ifndef UNITS_H
#define UNITS_H

#include <cstdint>
#include <ratio>

namespace phy {

  /*
   * A unit defined in terms of the base units
   */
  template<int Metre, int Kilogram, int Second, int Ampere, int Kelvin, int Mole, int Candela>
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

  using Metre     = Unit<1,0,0,0,0,0,0>;
  using Kilogram  = Unit<0,1,0,0,0,0,0>;
  using Second    = Unit<0,0,1,0,0,0,0>;
  using Ampere    = Unit<0,0,0,1,0,0,0>;
  using Kelvin    = Unit<0,0,0,0,1,0,0>;
  using Mole      = Unit<0,0,0,0,0,1,0>;
  using Candela   = Unit<0,0,0,0,0,0,1>;
  using Radian    = /* implementation defined */;

  /*
   * A quantity is a value associated with a unit and a ratio
   */
  template<class U, class R = std::ratio<1>>
  struct Qty {
    using Unit = U;
    using Ratio = R;

    intmax_t value;

    Qty(intmax_t v);

    template<typename ROther>
    Qty& operator+=(Qty<U, ROther> other);

    template<typename ROther>
    Qty& operator-=(Qty<U, ROther> other);

  };

  /*
   * Various quantities
   */

  using Length = Qty<Metre>;
  using Mass =Qty<Kilogram>;
  using Time = Qty<Second>;
  using Current = Qty<Ampere>;
  using Temperature = Qty<Kelvin>;
  using Amount = Qty<Mole>;
  using LuminousIntensity = Qty<Candela>;

  /*
   * Some weird quantities
   */

  using Mile = /* implementation defined */;
  using Yard = /* implementation defined */;
  using Foot = /* implementation defined */;
  using Inch = /* implementation defined */;

  /*
   * Comparison operators
   */

  template<typename U, typename R1, typename R2>
  bool operator==(Qty<U, R1> q1, Qty<U, R2> q2);

  template<typename U, typename R1, typename R2>
  bool operator!=(Qty<U, R1> q1, Qty<U, R2> q2);

  template<typename U, typename R1, typename R2>
  bool operator<(Qty<U, R1> q1, Qty<U, R2> q2);

  template<typename U, typename R1, typename R2>
  bool operator<=(Qty<U, R1> q1, Qty<U, R2> q2);

  template<typename U, typename R1, typename R2>
  bool operator>(Qty<U, R1> q1, Qty<U, R2> q2);

  template<typename U, typename R1, typename R2>
  bool operator>=(Qty<U, R1> q1, Qty<U, R2> q2);

  /*
   * Arithmetic operators
   */

  template<typename U, typename R1, typename R2>
  /* implementation defined */ operator+(Qty<U, R1> q1, Qty<U, R2> q2);

  template<typename U, typename R1, typename R2>
  /* implementation defined */ operator-(Qty<U, R1> q1, Qty<U, R2> q2);

  template<typename U1, typename R1, typename U2, typename R2>
  /* implementation defined */ operator*(Qty<U1, R1> q1, Qty<U2, R2> q2);

  template<typename U1, typename R1, typename U2, typename R2>
  /* implementation defined */ operator/(Qty<U1, R1> q1, Qty<U2, R2> q2);


  /*
   * Cast function between two quantities
   */
  template<ResQty, U, R>
  ResQty qtyCast(Qty<U,R>);

  namespace literals {

    /*
     * Some user-defined literals
     */

    Length operator "" _metres(unsigned long int val);
    Mass operator "" _kilograms(unsigned long int val);
    Time operator "" _seconds(unsigned long int val);
    Current operator "" _amperes(unsigned long int val);
    Temperature operator "" _kelvins(unsigned long int val);
    Amount operator "" _moles(unsigned long int val);
    LuminousIntensity operator "" _candelas(unsigned long int val);

  }

}

#endif // UNITS_H

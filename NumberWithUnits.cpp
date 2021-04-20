#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <map>
#include <string.h>
#include "NumberWithUnits.hpp"
// #define BOOL true

using namespace std;
//m -> cm
//cm -> m
//km -> m
//m -> km
namespace ariel
{
    static map<string, map<string, double>> convertor; // convertor O(3)

    double convertHelp(const string &from, const string &to, double fromVal)
    {
        if (from == to)
        {
            return fromVal;
        }
        if (convertor.at(from).count(to) != 0)
        {
            return fromVal * convertor.at(from).at(to);
        }
        __throw_invalid_argument("Not valid convertion");
        
    }

    double convert(const string &from, const string &to, double fromVal)
    {
        if (from == to)
        {
            return fromVal;
        }
        if (convertor.at(from).count(to) != 0)
        {
            return fromVal * convertor.at(from).at(to);
        }
        map<string, double> m = convertor.at(from);
        string s;
        for (map<string, double>::iterator it = m.begin(); it != m.end(); ++it)
        {
            s = it->first;
        }
        return convertHelp(s, to, convert(from, s, fromVal));
    }

    void NumberWithUnits::read_units(ifstream &file)
    {
        double Dunit1 = 0;
        double Dunit2 = 0;
        string Munit1;
        string Munit2;
        string none;
        string line;
        while (getline(file, line))
        {
            istringstream Sstream(line);
            if (!(Sstream >> Dunit1 >> Munit1 >> none >> Dunit2 >> Munit2))
            {
                break;
            }

            convertor[Munit1][Munit2] = Dunit2;     //from
            convertor[Munit2][Munit1] = 1 / Dunit2; //to
        }
    }

    NumberWithUnits operator+(const NumberWithUnits &unit1, const NumberWithUnits &unit2)
    {
        double converted = convert(unit2._unit, unit1._unit, unit2._value);
        return NumberWithUnits(unit1._value + converted, unit1._unit);
    }
    NumberWithUnits operator+=(NumberWithUnits &unit1, const NumberWithUnits &unit2)
    {
        unit1._value += convert(unit2._unit, unit1._unit, unit2._value);
        return unit1;
    }
    NumberWithUnits operator+(const NumberWithUnits &unit, double num)
    {
        return NumberWithUnits(unit._value + num, unit._unit);
    }
    NumberWithUnits operator-(const NumberWithUnits &unit1, const NumberWithUnits &unit2)
    {
        double converted = convert(unit2._unit, unit1._unit, unit2._value);
        return NumberWithUnits(unit1._value - converted, unit1._unit);
    }
    NumberWithUnits operator-=(NumberWithUnits &unit1, const NumberWithUnits &unit2)
    {
        unit1._value -= convert(unit2._unit, unit1._unit, unit2._value);
        return unit1;
    }
    NumberWithUnits operator-(const NumberWithUnits &unit)
    {
        return NumberWithUnits(-unit._value, unit._unit);
    }
    int compare(const NumberWithUnits &n1, const NumberWithUnits &n2)
    {
        double x = n1._value - convert(n2._unit, n1._unit, n2._value);
        double y = convert(n2._unit, n1._unit, n2._value) - n1._value;
        const double epsilon = 0.00001;
        if (x > epsilon)
        {
            return 1;
        }
        if (y > epsilon)
        {
            return -1;
        }
        return 0;
    }

    bool operator>(const NumberWithUnits &unit1, const NumberWithUnits &unit2) { return compare(unit1, unit2) > 0; }
    bool operator>=(const NumberWithUnits &unit1, const NumberWithUnits &unit2) { return compare(unit1, unit2) >= 0; }
    bool operator<(const NumberWithUnits &unit1, const NumberWithUnits &unit2) { return compare(unit1, unit2) < 0; }
    bool operator<=(const NumberWithUnits &unit1, const NumberWithUnits &unit2) { return compare(unit1, unit2) <= 0; }
    bool operator==(const NumberWithUnits &unit1, const NumberWithUnits &unit2) { return compare(unit1, unit2) == 0; }
    bool operator!=(const NumberWithUnits &unit1, const NumberWithUnits &unit2) { return compare(unit1, unit2) != 0; }
    NumberWithUnits operator++(NumberWithUnits &unit) { return NumberWithUnits(++unit._value, unit._unit); }      //Prefix
    NumberWithUnits operator++(NumberWithUnits &unit, int) { return NumberWithUnits(unit._value++, unit._unit); } //Postfix
    NumberWithUnits operator--(NumberWithUnits &unit) { return NumberWithUnits(--unit._value, unit._unit); }      //Prefix
    NumberWithUnits operator--(NumberWithUnits &unit, int) { return NumberWithUnits(unit._value++, unit._unit); } //Postfix
    NumberWithUnits operator*(const NumberWithUnits &unit, double num) { return NumberWithUnits(num * unit._value, unit._unit); }
    NumberWithUnits operator*(double num, const NumberWithUnits &unit) { return NumberWithUnits(num * unit._value, unit._unit); }
    ostream &operator<<(const ostream &os, const NumberWithUnits &unit) { return cout << unit._value << "[" << unit._unit << "]" << endl; }
    istream &operator>>(std::istream &in, NumberWithUnits &unit)
    {
        string s;
        in >> unit._value >> s >> unit._unit;
        return in;
    }
}

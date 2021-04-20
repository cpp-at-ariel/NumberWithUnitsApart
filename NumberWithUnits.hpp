#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

namespace ariel{
    class NumberWithUnits{
            private:
                double _value;
                string _unit;
            public:
                const bool BOOL = true;
                NumberWithUnits(double value, string unit){
                    _value=value;
                    _unit=unit;
                }
                NumberWithUnits(){}
                ~NumberWithUnits(){}
                static void read_units(const ifstream& file);
                friend NumberWithUnits operator+(const NumberWithUnits& unit1, const NumberWithUnits& unit2);
                friend NumberWithUnits operator+=(const NumberWithUnits& unit1, const NumberWithUnits& unit2);
                friend NumberWithUnits operator+(const NumberWithUnits& unit);
                friend NumberWithUnits operator-(const NumberWithUnits& unit1, const NumberWithUnits& unit2);
                friend NumberWithUnits operator-=(const NumberWithUnits& unit1, const NumberWithUnits& unit2);
                friend NumberWithUnits operator-(const NumberWithUnits& unit);
                friend bool operator>(const NumberWithUnits& unit1, const NumberWithUnits& unit2);
                friend bool operator>=(const NumberWithUnits& unit1, const NumberWithUnits& unit2);
                friend bool operator<(const NumberWithUnits& unit1, const NumberWithUnits& unit2);
                friend bool operator<=(const NumberWithUnits& unit1, const NumberWithUnits& unit2);
                friend bool operator==(const NumberWithUnits& unit1, const NumberWithUnits& unit2);
                friend bool operator!=(const NumberWithUnits& unit1, const NumberWithUnits& unit2);
                friend NumberWithUnits operator++(const NumberWithUnits& unit);       //Prefix
                friend NumberWithUnits operator++(const NumberWithUnits& unit, int);     //Postfix
                friend NumberWithUnits operator--(const NumberWithUnits& unit);       //Prefix
                friend NumberWithUnits operator--(const NumberWithUnits& unit, int);     //Postfix
                friend NumberWithUnits operator*(const NumberWithUnits& unit, double num);
                friend NumberWithUnits operator*(double num, const NumberWithUnits& unit);
                friend ostream& operator<<(const ostream& os, const NumberWithUnits& unit);
                friend istream& operator>>(istream& in, NumberWithUnits& unit);
    };
}
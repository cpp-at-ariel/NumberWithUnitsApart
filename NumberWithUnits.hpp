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
                NumberWithUnits(double value, string unit){
                    _value=value;
                    _unit=unit;
                }
                NumberWithUnits(){}
                ~NumberWithUnits(){}
               
                friend int compare(const NumberWithUnits& n1, const NumberWithUnits& n2);
                static double convert(const std::string &from, const std::string &to, double fromVal);
                static void read_units(ifstream& file);

                friend NumberWithUnits operator+(const NumberWithUnits& unit1, const NumberWithUnits& unit2);
                friend NumberWithUnits operator+(const NumberWithUnits& unit, double num);
                NumberWithUnits& operator+=(const NumberWithUnits& unit2);
                friend NumberWithUnits operator-(const NumberWithUnits& unit1, const NumberWithUnits& unit2);
                friend NumberWithUnits operator-(const NumberWithUnits& unit1, double num);
                NumberWithUnits& operator-=(const NumberWithUnits& unit2);

                const NumberWithUnits operator-() const{
                    return NumberWithUnits(-_value, _unit);
                } 
                const NumberWithUnits operator+() const{
                    return NumberWithUnits(+_value, _unit);
                }

                friend bool operator>(const NumberWithUnits& unit1, const NumberWithUnits& unit2);
                friend bool operator<(const NumberWithUnits& unit1, const NumberWithUnits& unit2);
                friend bool operator>=(const NumberWithUnits& unit1, const NumberWithUnits& unit2);
                friend bool operator<=(const NumberWithUnits& unit1, const NumberWithUnits& unit2);
                friend bool operator==(const NumberWithUnits& unit1, const NumberWithUnits& unit2);
                friend bool operator!=(const NumberWithUnits& unit1, const NumberWithUnits& unit2);

                friend NumberWithUnits& operator++( NumberWithUnits& unit);       //Prefix
                friend NumberWithUnits& operator++( NumberWithUnits& unit, int);     //Postfix
                friend NumberWithUnits& operator--( NumberWithUnits& unit);       //Prefix
                friend NumberWithUnits& operator--( NumberWithUnits& unit, int);     //Postfix
                friend NumberWithUnits operator*(const NumberWithUnits& unit, double num);
                friend NumberWithUnits operator*(double num, const NumberWithUnits& unit);

                friend ostream& operator<<(const ostream& os, const NumberWithUnits& unit);
                friend istream& operator>>(istream& in, NumberWithUnits& unit);
    };
}
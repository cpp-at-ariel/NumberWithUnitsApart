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
                NumberWithUnits(const double& value, const string& unit);                 
                NumberWithUnits(){}
                ~NumberWithUnits(){}
               
                friend int compare(const NumberWithUnits& left, const NumberWithUnits& right);
                static double convert(const std::string &src, const std::string &dst, double srcVal);
                static void read_units(ifstream& file);

                friend NumberWithUnits operator+(const NumberWithUnits& src, const NumberWithUnits& dst);
                friend NumberWithUnits operator+(const NumberWithUnits& src, double num);
                NumberWithUnits& operator+=(const NumberWithUnits& dst);
                friend NumberWithUnits operator-(const NumberWithUnits& src, const NumberWithUnits& dst);
                friend NumberWithUnits operator-(const NumberWithUnits& src, double num);
                NumberWithUnits& operator-=(const NumberWithUnits& dst);

                const NumberWithUnits operator-() const{
                    return NumberWithUnits(-_value, _unit);
                } 
                const NumberWithUnits operator+() const{
                    return NumberWithUnits(+_value, _unit);
                }

                friend bool operator>(const NumberWithUnits& src, const NumberWithUnits& dst);
                friend bool operator<(const NumberWithUnits& src, const NumberWithUnits& dst);
                friend bool operator>=(const NumberWithUnits& src, const NumberWithUnits& dst);
                friend bool operator<=(const NumberWithUnits& src, const NumberWithUnits& dst);
                friend bool operator==(const NumberWithUnits& src, const NumberWithUnits& dst);
                friend bool operator!=(const NumberWithUnits& src, const NumberWithUnits& dst);

                friend NumberWithUnits& operator++( NumberWithUnits& unit);       //Prefix
                friend NumberWithUnits operator++( NumberWithUnits& unit, int);     //Postfix
                friend NumberWithUnits& operator--( NumberWithUnits& unit);       //Prefix
                friend NumberWithUnits operator--( NumberWithUnits& unit, int);     //Postfix
                friend NumberWithUnits operator*(const NumberWithUnits& unit, double num);
                friend NumberWithUnits operator*(double num, const NumberWithUnits& unit);

                friend ostream& operator<<(ostream& os, const NumberWithUnits& unit);
                friend istream& operator>>(istream& in, NumberWithUnits& unit);
    };
}
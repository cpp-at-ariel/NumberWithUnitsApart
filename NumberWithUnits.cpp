
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "NumberWithUnits.hpp"
// #define BOOL true 

// using namespace std;

namespace ariel{
            void NumberWithUnits::read_units(const ifstream& file){}
            NumberWithUnits operator+(const NumberWithUnits& unit1, const NumberWithUnits& unit2){return NumberWithUnits();}
            NumberWithUnits operator+=(const NumberWithUnits& unit1, const NumberWithUnits& unit2){return NumberWithUnits();}
            NumberWithUnits operator+(const NumberWithUnits& unit){return NumberWithUnits();}
            NumberWithUnits operator-(const NumberWithUnits& unit1, const NumberWithUnits& unit2){return NumberWithUnits();}
            NumberWithUnits operator-=(const NumberWithUnits& unit1, const NumberWithUnits& unit2){return NumberWithUnits();}
            NumberWithUnits operator-(const NumberWithUnits& unit){return NumberWithUnits();}
            bool operator>(const NumberWithUnits& unit1, const NumberWithUnits& unit2){return unit1.BOOL;}
            bool operator>=(const NumberWithUnits& unit1, const NumberWithUnits& unit2){return unit1.BOOL;}
            bool operator<(const NumberWithUnits& unit1, const NumberWithUnits& unit2){return unit1.BOOL;}
            bool operator<=(const NumberWithUnits& unit1, const NumberWithUnits& unit2){return unit1.BOOL;}
            bool operator==(const NumberWithUnits& unit1, const NumberWithUnits& unit2){return unit1.BOOL;}
            bool operator!=(const NumberWithUnits& unit1, const NumberWithUnits& unit2){return unit1.BOOL;}
            NumberWithUnits operator++(const NumberWithUnits& unit){return NumberWithUnits();}      //Prefix
            NumberWithUnits operator++(const NumberWithUnits& unit, int){return NumberWithUnits();}     //Postfix
            NumberWithUnits operator--(const NumberWithUnits& unit){return NumberWithUnits();}      //Prefix
            NumberWithUnits operator--(const NumberWithUnits& unit, int){return NumberWithUnits();}     //Postfix
            NumberWithUnits operator*(const NumberWithUnits& unit, double num){return NumberWithUnits();}
            NumberWithUnits operator*(double num, const NumberWithUnits& unit){return NumberWithUnits();}
            ostream& operator<<(const ostream& os, const NumberWithUnits& unit){return cout << unit._value << "[" << unit._unit << "]" << endl;}
            istream& operator>>(std::istream& in, NumberWithUnits& unit){
                string s;
                in >> unit._value >> s >> unit._unit;
                return in;
            }
}


#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <map>
#include <string.h>
#include "graph.cpp"
#include "NumberWithUnits.hpp"

using namespace std;

namespace ariel
{
    static graph g;

    double NumberWithUnits::convert(const string &from, const string &to, double fromVal){
        if(from == to){
            return fromVal;
        }
        double retVal = g.getConv(from, to);
        if(retVal > -1){
            return fromVal*retVal;
        }
         __throw_invalid_argument("Not valid convertion");
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
            g.addEdge(Munit1 ,Munit2, (Dunit2/Dunit1)); 
        }
    }
    int compare(const NumberWithUnits& n1, const NumberWithUnits& n2)
    {
        double x = n1._value - NumberWithUnits::convert(n2._unit, n1._unit, n2._value);
        double y = NumberWithUnits::convert(n2._unit, n1._unit, n2._value) - n1._value;
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



    
    NumberWithUnits operator+(const NumberWithUnits &unit1, const NumberWithUnits &unit2)
    {
        double converted = NumberWithUnits::convert(unit2._unit, unit1._unit, unit2._value);
        return NumberWithUnits(unit1._value + converted, unit1._unit);
    }
    NumberWithUnits operator+(const NumberWithUnits& unit1, double num) {
        return NumberWithUnits(unit1._value + num, unit1._unit);
    }
    NumberWithUnits& NumberWithUnits::operator+=(const NumberWithUnits &unit2)
    {
        double con = convert(unit2._unit, this->_unit, unit2._value);
        this->_value += con; 
        return *this;
    }
    NumberWithUnits operator-(const NumberWithUnits &unit1, const NumberWithUnits &unit2)
    {
        double converted = NumberWithUnits::convert(unit2._unit, unit1._unit, unit2._value);
        return NumberWithUnits(unit1._value - converted, unit1._unit);
    }
    NumberWithUnits operator-(const NumberWithUnits& unit1, double num){
        return NumberWithUnits(unit1._value - num, unit1._unit);
    }   
    NumberWithUnits& NumberWithUnits::operator-=(const NumberWithUnits &unit2)
    {
        double con = convert(unit2._unit, this->_unit, unit2._value);
        this->_value -= con; 
        return *this;
    }
    


    //bool
    bool operator>(const NumberWithUnits &unit1, const NumberWithUnits &unit2) { return compare(unit1, unit2) > 0; }
    bool operator>=(const NumberWithUnits &unit1, const NumberWithUnits &unit2) { return compare(unit1, unit2) >= 0; }
    bool operator<(const NumberWithUnits &unit1, const NumberWithUnits &unit2) { return compare(unit1, unit2) < 0; }
    bool operator<=(const NumberWithUnits &unit1, const NumberWithUnits &unit2) { return compare(unit1, unit2) <= 0; }
    bool operator==(const NumberWithUnits &unit1, const NumberWithUnits &unit2) { return compare(unit1, unit2) == 0; }
    bool operator!=(const NumberWithUnits &unit1, const NumberWithUnits &unit2) { return compare(unit1, unit2) != 0; }
    
    
    //unary
    NumberWithUnits& operator++(NumberWithUnits &unit) { 
        ++unit._value;
        return unit; 
    }      //Prefix
    NumberWithUnits& operator++(NumberWithUnits &unit, int) { 
        unit._value++;
        return unit; 
    } //Postfix 
    NumberWithUnits& operator--(NumberWithUnits &unit) {
        --unit._value;
        return unit;
    }      //Prefix
    NumberWithUnits& operator--(NumberWithUnits &unit, int) {
        unit._value--;
        return unit;
    } //Postfix
    NumberWithUnits operator*(const NumberWithUnits &unit, double num) {
        return NumberWithUnits{unit._value*num, unit._unit};
    }
    NumberWithUnits operator*(double num, const NumberWithUnits &unit) {
        return NumberWithUnits{unit._value*num, unit._unit};
    }
    
    //stream
    ostream &operator<<(const ostream &os, const NumberWithUnits &unit) { return cout << unit._value << "[" << unit._unit << "]" << endl; }
    istream &operator>>(std::istream &in, NumberWithUnits &unit)
    {
        string s;
        in >> unit._value >> s >> unit._unit;
        return in;
    }
}

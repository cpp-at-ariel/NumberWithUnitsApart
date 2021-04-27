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

    double NumberWithUnits::convert(const string &src, const string &dst, double srcVal){
        if(src == dst){
            return srcVal;
        }
        double retVal = g.getConv(src, dst);
        if(retVal > -1){
            return srcVal*retVal;
        }
         __throw_invalid_argument("Not valid convertion");
    }

    void NumberWithUnits::read_units(ifstream &file)
    {
        double D1 = 0;
        double D2 = 0;
        string MU1;
        string MU2;
        string none;
        string line;
        while (getline(file, line))
        {
            istringstream Sstream(line);
            if (!(Sstream >> D1 >> MU1 >> none >> D2 >> MU2))
            {
                break;
            }
            g.addEdge(MU1 ,MU2, (D2/D1)); 
        }
    }
    NumberWithUnits::NumberWithUnits(const double& value, const string &unit){ 
        if (!g.checkExist(unit))
        {
           __throw_invalid_argument("Not valid unit");
        }
        _value=value;
        _unit=unit;
    }
    int compare(const NumberWithUnits& left, const NumberWithUnits& right)
    {
        double x = left._value - NumberWithUnits::convert(right._unit, left._unit, right._value);
        double y = NumberWithUnits::convert(right._unit, left._unit, right._value) - left._value;
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



    
    NumberWithUnits operator+(const NumberWithUnits &src, const NumberWithUnits &dst)
    {
        double converted = NumberWithUnits::convert(dst._unit, src._unit, dst._value);
        return NumberWithUnits(src._value + converted, src._unit);
    }
    NumberWithUnits operator+(const NumberWithUnits& src, double num) {
        return NumberWithUnits(src._value + num, src._unit);
    }
    NumberWithUnits& NumberWithUnits::operator+=(const NumberWithUnits &dst)
    {
        double con = convert(dst._unit, this->_unit, dst._value);
        this->_value += con; 
        return *this;
    }
    NumberWithUnits operator-(const NumberWithUnits &src, const NumberWithUnits &dst)
    {
        double converted = NumberWithUnits::convert(dst._unit, src._unit, dst._value);
        return NumberWithUnits(src._value - converted, src._unit);
    }
    NumberWithUnits operator-(const NumberWithUnits& src, double num){
        return NumberWithUnits(src._value - num, src._unit);
    }   
    NumberWithUnits& NumberWithUnits::operator-=(const NumberWithUnits &dst)
    {
        double con = convert(dst._unit, this->_unit, dst._value);
        this->_value -= con; 
        return *this;
    }
    


    //bool
    bool operator>(const NumberWithUnits &src, const NumberWithUnits &dst) { return compare(src, dst) > 0; }
    bool operator>=(const NumberWithUnits &src, const NumberWithUnits &dst) { return compare(src, dst) >= 0; }
    bool operator<(const NumberWithUnits &src, const NumberWithUnits &dst) { return compare(src, dst) < 0; }
    bool operator<=(const NumberWithUnits &src, const NumberWithUnits &dst) { return compare(src, dst) <= 0; }
    bool operator==(const NumberWithUnits &src, const NumberWithUnits &dst) { return compare(src, dst) == 0; }
    bool operator!=(const NumberWithUnits &src, const NumberWithUnits &dst) { return compare(src, dst) != 0; }
    
    
    //unary
    NumberWithUnits& operator++(NumberWithUnits &unit) { 
        ++unit._value;
        return unit; 
    }      //Prefix
    NumberWithUnits operator++(NumberWithUnits &unit, int) { 
        NumberWithUnits temp = unit; 
        unit._value++;
        return temp; 
    } //Postfix 
    NumberWithUnits& operator--(NumberWithUnits &unit) {
        --unit._value;
        return unit;
    }      //Prefix
    NumberWithUnits operator--(NumberWithUnits &unit, int) {
        NumberWithUnits temp = unit; 
        unit._value--;
        return temp; 
    } //Postfix
    NumberWithUnits operator*(const NumberWithUnits &unit, double num) {
        return NumberWithUnits{unit._value*num, unit._unit};
    }
    NumberWithUnits operator*(double num, const NumberWithUnits &unit) {
        return NumberWithUnits{unit._value*num, unit._unit};
    }
    
    //stream
    ostream &operator<<(ostream &os, const NumberWithUnits &unit) {
        return (os <<  unit._value << '[' << unit._unit << ']'); 
    }
    istream &operator>>(std::istream &in, NumberWithUnits &unit)
    {
        string u;
        double value = 0;
        char ch = ']';
        in >> value >> ch;
        while(ch != ']'){
            if(ch != '['){
                u.insert(u.end(), ch);
            }
            in >> ch;
        }
        unit._value = value;
        unit._unit = u;
        if(!g.checkExist(unit._unit)){
            __throw_invalid_argument("not in the anaaref");
        }
        return in;
    }
}

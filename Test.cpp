#include "NumberWithUnits.hpp"
#include "doctest.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <ctime>
#include <stdexcept>
#include <vector>

using namespace ariel;
static vector<string> units = {"m"};
ifstream units_file{"units.txt"};

TEST_CASE("km/m"){
    NumberWithUnits::read_units(units_file);
    NumberWithUnits unit1{1, "km"};
    NumberWithUnits unit2{500, "m"};
    NumberWithUnits unitC1{1500, "m"};
    CHECK((unit2+unit1)==unitC1);
    NumberWithUnits unitC2{1.5, "km"};
    CHECK((unit1+unit2)==unitC1);
    CHECK((unit2+=unit1)==unitC1);
    CHECK_FALSE((unit2+=unit1)==unitC2);
    NumberWithUnits unitC3{-1.5, "km"};
    CHECK((unit1-unit2)==unitC3);
    NumberWithUnits unitC4{1500, "m"};
    CHECK((unit2-unit1)==unitC4);
    CHECK((unit2-unit1)!=unitC3);
}
TEST_CASE("boolean"){
    NumberWithUnits unit1{101, "cm"};
    NumberWithUnits unit2{1, "m"};
    CHECK(unit1>unit2);
    CHECK(unit1>=unit2);
    CHECK(unit2<=unit1);
    CHECK(unit2<unit1);

    NumberWithUnits unitB1{1, "hour"};
    NumberWithUnits unitB2{3601, "sec"};
    NumberWithUnits unitB3{60, "min"};
    CHECK(unitB2>unitB1);
    CHECK(unitB2>=unitB1);
    CHECK(unitB1>=unitB3);
    CHECK(unitB3>=unitB1);
    CHECK(unitB1<unitB2);

    NumberWithUnits unitC1{1, "kg"};
    NumberWithUnits unitC2{1000, "g"};
    CHECK_FALSE(unitC2!=unitC1);
    CHECK(unitC2==unitC1);
    CHECK(unitC2<=unitC1);

    NumberWithUnits unitD1{0.001, "ton"};
    CHECK(unitC1==unitD1);
    CHECK(unitC1==unitC2);

    NumberWithUnits unitD2{0.002, "ton"};
    CHECK(unitC1!=unitD2);
    CHECK(unitC2!=unitD2);
}
TEST_CASE("postfix/prefix"){
    NumberWithUnits unit1{1, "hour"};
    NumberWithUnits unit2{2, "hour"};
    NumberWithUnits unit3{180, "min"};
    CHECK(++unit1==unit2);
    CHECK(++unit1==unit3);
    NumberWithUnits unit4{4, "hour"};
    CHECK_FALSE(unit1++==unit4);
    CHECK(--unit1==unit3); //Now it's 3 hours
    CHECK(unit1--==unit3);
}

TEST_CASE("Multiply"){
    NumberWithUnits unit1{2, "kg"};
    NumberWithUnits unit2{10, "kg"};
    NumberWithUnits unit3{10000, "g"};
    double num = 5;
    CHECK(unit1*num==unit2);
    CHECK(unit1*num==unit3);
    CHECK(num*unit1==unit2);
    CHECK(num*unit1==unit3);
    double number = 3;
    CHECK_FALSE(unit1*number==unit2);
    CHECK_FALSE(unit1*number==unit3);
    CHECK(number*unit1!=unit2);
    CHECK(number*unit1!=unit3);
}
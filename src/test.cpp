#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "utility.h"

TEST_CASE("Student Comparison") {
    Student s1("Quentin", "Tarantino", 4.54), 
            s2("Quarantin", "Tarantulino", 1.12),
            s3("X Æ A-12", "Musk", 10),
            s4("X Æ A-12", "Musk", 10);

    SECTION("All data") {
        REQUIRE( (s1 == s2) == false );
        REQUIRE( (s3 == s4) == true );
    }
    SECTION("Names (1st < 2nd)") {
        REQUIRE( compareNames(s1, s2) == false );
        REQUIRE( compareNames(s2, s3) == true );
    }
    SECTION("Surnames (1st < 2nd)") {
        REQUIRE( compareSurnames(s1, s2) == true );
        REQUIRE( compareSurnames(s2, s3) == false );
    }
    SECTION("Final Grades (1st < 2nd)") {
        REQUIRE( compareFinals(s1, s2) == false );
        REQUIRE( compareFinals(s2, s3) == true );
    }
}

TEST_CASE("Student operators") {
    Student s1("Quentin", "Tarantino", 5.54), 
            s2("X Æ A-12", "Musk", 2);

    SECTION("Copy assignment") {
        Student s3 = s2;
        REQUIRE( (s3 == s2) == true );
    }
    SECTION("Final arithmetics") {
        REQUIRE( (s1 + s2) == 7.54 );
        REQUIRE( (s1 - s2) == 3.54 );
        REQUIRE( (s1 / s2) == 2.77 );
    }
}

TEST_CASE("Grade calculations") {
    std::vector<int> hw1{1, 5, 8, 4}, hw2{4, 4}, hw3{10}, hw4{1, 2, 3}, hw5;

    SECTION("Average") {
        REQUIRE( average(hw1) == 4.5 );
        REQUIRE( average(hw2) == 4 );
        REQUIRE( average(hw3) == 10 );
    }
    SECTION("Median") {
        REQUIRE( median(hw1) == 4.5);
        REQUIRE( median(hw4) == 2 );
        REQUIRE( median(hw3) == 10 );
    }
    SECTION("Final Grade") {
        // Use approx for toleration of rounding errors
        REQUIRE( finalGrade(hw5, 9, 'v') == Approx(5.4) );
        REQUIRE( finalGrade(hw4, 4, 'v') == Approx(3.2) );
        REQUIRE( finalGrade(hw3, 1, 'm') == Approx(4.6) );
    }
}
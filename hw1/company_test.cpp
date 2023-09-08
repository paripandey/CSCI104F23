#include <iostream>
#include <iomanip>
#include "company.hpp"

int main() {

    // Declares the 1st CompanyTracker object with 5 students/companies
    CompanyTracker* no1 = new CompanyTracker(5); 

    std::cout << std::endl << "CompanyTracker* no1 (5 COMPANIES):" << std::endl;

    // Test 1 (NORMAL)
    std::cout << "merge(0, 1) -> BEFORE: " << std::boolalpha << no1->inSameCompany(0, 1); // false
    no1->merge(0, 1);
    std::cout << ", AFTER: " << std::boolalpha << no1->inSameCompany(0, 1) << ". RESULT: PASS!" << std::endl; // true

    // Test 2 (EDGE CASE, MERGING SAME STUDENT)
    std::cout << "merge(1, 1) -> BEFORE: " << std::boolalpha << no1->inSameCompany(1, 1); // true
    no1->merge(1, 1);
    std::cout << ", AFTER: " << std::boolalpha << no1->inSameCompany(1, 1) << ". RESULT: FAIL! Cannot merge student 1 with itself." << std::endl; // true

    // Test 3 (EDGE CASE, INVALID STUDENT)
    std::cout << "merge(-1, 4) -> BEFORE: " << std::boolalpha << no1->inSameCompany(-1, 4); // false
    no1->merge(-1, 4);
    std::cout << ", AFTER: " << std::boolalpha << no1->inSameCompany(-1, 4) << ". RESULT: FAIL! Student -1 doesn't exist." << std::endl; // false

    // Test 4 (NORMAL)
    std::cout << "merge(2, 3) -> BEFORE: " << std::boolalpha << no1->inSameCompany(2, 3); // false
    no1->merge(2, 3);
    std::cout << ", AFTER: " << std::boolalpha << no1->inSameCompany(2, 3) << ". RESULT: PASS!" << std::endl; // true

    // Test 5 (NORMAL)
    std::cout << "merge(0, 3) -> BEFORE: " << std::boolalpha << no1->inSameCompany(0, 3); // false
    no1->merge(0, 3);
    std::cout << ", AFTER: " << std::boolalpha << no1->inSameCompany(0, 3) << ". RESULT: PASS!" << std::endl; // true
   
    // Test 6 (NORMAL)
    std::cout << "split(2) -> BEFORE: " << std::boolalpha << no1->inSameCompany(1, 2); // true
    no1->split(2);
    std::cout << ", AFTER: " << std::boolalpha << no1->inSameCompany(1, 2) << ". RESULT: PASS!" << std::endl; // false

    // Test 7 (NORMAL)
    std::cout << "split(2) -> BEFORE: " << std::boolalpha << no1->inSameCompany(2, 3); // true
    no1->split(2);
    std::cout << ", AFTER: " << std::boolalpha << no1->inSameCompany(2, 3) << ". RESULT: PASS!" << std::endl; // false
    
    // Test 8 (EDGE CASE, SPLITTING FROM ITSELF)
    std::cout << "split(2) -> BEFORE: " << std::boolalpha << no1->inSameCompany(2, 2); // true
    no1->split(2);
    std::cout << ", AFTER: " << std::boolalpha << no1->inSameCompany(2, 2) << ". RESULT: FAIL! Cannot split student 2 from itself." << std::endl; // true

    // Test 9 (EDGE CASE, ALREADY MERGED)
    std::cout << "merge(0, 1) -> BEFORE: " << std::boolalpha << no1->inSameCompany(0, 1); // true
    no1->merge(0, 1);
    std::cout << ", AFTER: " << std::boolalpha << no1->inSameCompany(0, 1) << ". RESULT: FAIL! Students 0 and 1 are already merged." << std::endl; // true

    // Test 10 (EDGE CASE, INVALID STUDENT)
    std::cout << "split(-7) -> BEFORE: " << std::boolalpha << no1->inSameCompany(-7, -7); // false
    no1->split(-7);
    std::cout << ", AFTER: " << std::boolalpha << no1->inSameCompany(-7, -7) << ". RESULT: FAIL! Student -7 doesn't exist." << std::endl; // false

    // Test 11 (NORMAL)
    std::cout << "merge(2, 4) -> BEFORE: " << std::boolalpha << no1->inSameCompany(2, 4); // false
    no1->merge(2, 4);
    std::cout << ", AFTER: " << std::boolalpha << no1->inSameCompany(2, 4) << ". RESULT: PASS!" << std::endl; // true
   
    // Test 12 (NORMAL)
    std::cout << "split(0) -> BEFORE: " << std::boolalpha << no1->inSameCompany(0, 1); // true
    no1->split(0);
    std::cout << ", AFTER: " << std::boolalpha << no1->inSameCompany(0, 1) << ". RESULT: PASS!" << std::endl; // false
 
    // Test 13 (EDGE CASE, INVALID STUDENT)
    std::cout << "merge(0, 7) -> BEFORE: " << std::boolalpha << no1->inSameCompany(0, 7); // false
    no1->merge(0, 7);
    std::cout << ", AFTER: " << std::boolalpha << no1->inSameCompany(0, 7) << ". RESULT: FAIL! Student 7 doesn't exist." << std::endl; // false

    // Test 14 (NORMAL)
    std::cout << "split(4) -> BEFORE: " << std::boolalpha << no1->inSameCompany(2, 4); // true
    no1->split(4);
    std::cout << ", AFTER: " << std::boolalpha << no1->inSameCompany(2, 4) << ". RESULT: PASS!" << std::endl; // false

     // Test 15 (EDGE CASE, INVALID STUDENT)
    std::cout << "split(10) -> BEFORE: " << std::boolalpha << no1->inSameCompany(10, 10); // false
    no1->split(10);
    std::cout << ", AFTER: " << std::boolalpha << no1->inSameCompany(10, 10) << ". RESULT: FAIL! Student 10 doesn't exist." << std::endl << std::endl; // false

    // Deletes the 1st CompanyTracker object
    delete no1;

    // Declares the 2nd CompanyTracker object with 0 students/companies
    CompanyTracker* no2 = new CompanyTracker(0);

    // Test 16 (2 EDGE CASES DUE TO 0 STUDENTS)
    std::cout << "CompanyTracker* no2 (0 COMPANIES):" << std::endl;
    std::cout << "merge(0, 5) -> BEFORE: " << std::boolalpha << no2->inSameCompany(0, 5); // false
    no2->merge(0, 5);
    std::cout << ", AFTER: " << std::boolalpha << no2->inSameCompany(0, 5) << ". RESULT: FAIL! There are no companies!" << std::endl; // false

    std::cout << "split(9) -> BEFORE: " << std::boolalpha << no2->inSameCompany(9, 9); // false
    no2->split(9);
    std::cout << ", AFTER: " << std::boolalpha << no2->inSameCompany(9, 9) << ". RESULT: FAIL! There are no companies!" << std::endl << std::endl; // false
    
    // Deletes the 2nd CompanyTracker object
    delete no2;

    // Declares the 3rd CompanyTracker object
    std::cout << "CompanyTracker* no3 (-9 COMPANIES):" << std::endl;

    // Test 17 (2 EDGE CASES DUE TO NEGATIVE NUMBER OF COMPANIES)
    CompanyTracker* no3 = new CompanyTracker(-9);
    std::cout << "merge(0, -9) -> BEFORE: " << std::boolalpha << no3->inSameCompany(0, -9); // false
    no3->merge(0, -9);
    std::cout << ", AFTER: " << std::boolalpha << no3->inSameCompany(0, -9) << ". RESULT: FAIL! There are no companies!" << std::endl; // false
    
    std::cout << "split(-4) -> BEFORE: " << std::boolalpha << no3->inSameCompany(-4, -4); // false
    no3->split(-4);
    std::cout << ", AFTER: " << std::boolalpha << no3->inSameCompany(-4, -4) << ". RESULT: FAIL! There are no companies!" << std::endl << std::endl; // false

    // Deletes the 3rd CompanyTracker object
    delete no3;
    
    return 0;
}
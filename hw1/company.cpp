#include <vector>
#include <iostream>
#include "company.hpp"

// Initializes the tracker with n students and their 1-person companies.
CompanyTracker::CompanyTracker(int n)
{
  numCompanies = n;

  // Doesn't allocate any memory for 0 or a negative number of companies
  if (numCompanies <= 0) {  
    return;
  }

  // Only allocates memory for a positive number of companies 
  else {
    companies = new Company* [numCompanies];
    for (int i = 0; i < numCompanies; ++i) {
      companies[i] = new Company ();
    }
  }
}
// Deallocates all dynamically allocated memory.
CompanyTracker::~CompanyTracker()
{
  // your implementation goes here
  for (int i = 0; i < numCompanies; ++i) {
    // Splits the student from all companies until he/she is in his/her own company
    while (companies[i]->parent != nullptr) {
      split(i);
    }
    // Deletes the student's company
    delete companies[i];
  }

  // Deletes the list of companies (only) if it was allocated
  if (numCompanies > 0) {
    delete[] companies;
  } 
}

void CompanyTracker::merge(int i, int j)
{
  // your implementation goes here

  // Checks for invalid students/inputs and/or whether the 2 students have already been merged
  if (i < 0 || i >= numCompanies || j < 0 || j >=numCompanies || findLargest(i) == findLargest(j)) {
    return;
  }

  // Finds the biggest company that each student is in
  Company* ancestor1 = findLargest(i);
  Company* ancestor2 = findLargest(j);

  // Creates a new merger company consisting of these 2 "sub-companies"
  Company* merger = new Company(ancestor1, ancestor2);

  // Sets the merger as the parent of each of these 2 sub-companies
  ancestor1->parent = merger;
  ancestor2->parent = merger;
}

void CompanyTracker::split(int i)
{
  // your implementation goes here

  // Checks for invalid inputs and/or if the student is already in his/her own company
  if (i < 0 || i >= numCompanies || companies[i]->parent == nullptr) {
    return;
  }
  
  // Find the largest company the student is in
  Company* ancestor = findLargest(i);

  // Breaks up the merger company into its 2 sub-companies
  ancestor->merge1->parent = nullptr;
  ancestor->merge2->parent = nullptr;

  // Deletes the merger company
  delete ancestor;
}

bool CompanyTracker::inSameCompany(int i, int j)
{
  // your implementation goes here

  // Checks for invalid inputs/students
  if (i < 0 || i >= numCompanies || j < 0 || j >=numCompanies) {
    return false;
  }

  return findLargest(i) == findLargest(j);
}

Company* CompanyTracker::findLargest(int i) {
  // Checks for invalid inputs/students
  if (i < 0 || i >= numCompanies) {
    return nullptr;
  }

  // Starts with the current student's company
  Company* curr = companies[i];

  // The student must have an "ancestor" merger company (parent, grandparent, etc.)
  while (curr->parent != nullptr) {
    curr = curr->parent; // Assigns that ancestor to the "current" company being tracked
  }

  // Returns the largest merger company that has no parent (could be the same student/company itself)
  return curr;
}
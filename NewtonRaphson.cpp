#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
using namespace std;

double f(const vector<double>& coeffs, double x) {
    int n = coeffs.size() -1;
    double result =0.0;
    for(int i=0; i<n; i++){

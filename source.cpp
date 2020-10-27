#include <Rcpp.h>
#include <iterator>
#include <numeric>
#include <algorithm>
#include <math.h>
using namespace Rcpp;


// [[Rcpp::export]]
NumericVector winsorize(NumericVector x, double tr=0.2) {
    int n=x.size();
    NumericVector out(n);
    int d = floor(n*tr);
    int lower_index = d;
    int upper_index = n-d;
    NumericVector x_sorted = std::sort(x.begin(), x.end()) 
    int lower_bound = x_sorted[lower_index];
    int upper_bound = x_sorted[upper_index];

    
    for(int i=0; i<n; i++){
        if (x[i] < lower_bound) {
            out[i] = lower_bound;
        } else if (x[i] > upper_bound) {
            out[i] = upper_bound;
        } else {
            out[i] = x[i];
        }
    }
    return out;
}

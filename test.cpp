#include <Rcpp.h>
#include <iterator>
#include <numeric>
#include <algorithm>
using namespace Rcpp;


// double meanC(NumericVector x) {
//   int n = x.size();
//    double total = 0;
//   
//    for (int i=0;i<n;i++) {
//    total += x[i];
//    }
    
//    return total/n;

//}

// /*** R
//library(microbenchmark)
//x <- runif(1e6)

//microbenchmark(
// mean(x),
// meanC(x)
//)
// */


// [[Rcpp::export]]
bool allC(LogicalVector x) {
    int n = x.size();
    int counter = 0;
    bool res;
    
    for (int i=0; i<n; i++){
    if (x[i]== true) {
    counter += 1;
    }
    
    if (counter == n) {
    res= true;
    } else {
    res= false;
    }
    }
    return res;
    
}



// [[Rcpp::export]]
NumericVector cumprodC(NumericVector x) {
    int n = x.size();
    NumericVector res(n);
    double prod;
    
    prod = x[0];
    for (int i=0; i<n; i++){
    prod = prod * x[i];
    res[i] = prod;
    }
    
    return res;
}


/*** R
library(microbenchmark)
x <- runif(1e6)

microbenchmark(
 cumprod(x),
 cumprodC(x)
)
*/


// [[Rcpp::export]]
NumericVector cumminC(NumericVector x) {
    int n = x.size();
    NumericVector res(n);
    int m = x[0];
    res[0] = x[0];

    for (int i=1; i<n; i++){
    if (x[i] < m){
    m = x[i];
    res[i] = m;
    } else {
    res[i] = m;
    }
    }
    
    return res;
}


/*** R
library(microbenchmark)
x <- runif(1e6)

microbenchmark(
 cummin(x),
 cumminC(x)
)
*/




// [[Rcpp::export]]
NumericVector cummaxC(NumericVector x) {
    int n = x.size();
    NumericVector res(n);
    int m = x[0];
    res[0] = x[0];

    for (int i=1; i<n; i++){
    if (x[i] > m){
    m = x[i];
    res[i] = m;
    } else {
    res[i] = m;
    }
    }
    
    return res;
}


/*** R
library(microbenchmark)
x <- runif(1e6)

microbenchmark(
 cummax(x),
 cummaxC(x)
)
*/


// [[Rcpp::export]]
NumericVector rangeC(NumericVector x) {
    int n = x.size();
    NumericVector res(2);
    double minimum;
    double maximum;

    minimum = x[0];
    maximum = x[0];
    for (int i=1; i<n; i++){
        if (x[i] < minimum) {
        minimum = x[i];
        }
    }

    for (int i=1; i<n; i++){
        if (x[i] > maximum) {
        maximum = x[i];
        }
    }


    res[0] = minimum;
    res[1] = maximum;
    
    return res;
}


/*** R
library(microbenchmark)
x <- runif(1e6)

microbenchmark(
 range(x),
 rangeC(x)
)
*/


// [[Rcpp::export]]
NumericVector attribs() {
    NumericVector out = NumericVector::create(1, 2, 3);
    
    out.names() = CharacterVector::create("a", "b", "c");
    out.attr("my-attr") = "my-value";
    out.attr("class") = "my-class";
    
    return out;
}

// working with S3 classes

// extracting mean percentage error from an lm() object
// using .inherits() and stops() to check certain criteria
// as() is used to convert extracted R components to their C++ equivalents

// [[Rcpp::export]]
double mpe(List mod) {
    if (!mod.inherits("lm")) stop("Input must be a linear model");

    NumericVector resid = as<NumericVector>(mod["residuals"]);
    NumericVector fitted = as<NumericVector>(mod["fitted.values"]);

    int n = resid.size();
    double err = 0;

    for (int i=0; i<n; ++i) {
    err += resid[i] / (fitted[i] + resid[i]);
    }
    return err / n;
}


// using functions with Rcpp
// using with the Function keyword, R function can be referenced from C++
// RObject is a catchall type 
// [[Rcpp::export]]
RObject callC(Function f, NumericVector x) {
    return f(x);
}



// [[Rcpp::export]]
List lapplyC(List input, Function f){
    int n = input.size();
    List out(n);

    for(int i=0; i<n; i++){
        out[i] = f(input[i]);
    }

    return out;
}


//missing values
// check for missing values in a vector with is_na()
// [[Rcpp::export]]

LogicalVector is_naC(NumericVector x){
    int n = x.size();
    LogicalVector out(n);

    for (int i=0; i<n; i++){
        out[i] = NumericVector::is_na(x[i]);
    }

    return out;
}

// exercises
// na.rm parameter
// [[Rcpp::export]]
NumericVector treat_missing(NumericVector x, bool narm) {
    int n=x.size();
    LogicalVector missing_vector(n);
    missing_vector = is_naC(x);
    int missing=0;

    for (int i=0; i<n; i++){
        if (missing_vector[i] == true) {
            missing = missing + 1;
        }
    }

    if (narm == true) {
        int new_n;
        new_n = n - missing;
        NumericVector new_x(new_n);
        int c=-1;
        for (int i=0; i<n; i++){
            if (missing_vector[i] == false) {
            c = c+1;
            new_x[c] = x[i];
            }
        }
        return new_x;
    } else {
        NumericVector new_x(n);
        new_x = x;
        return new_x;
    } 
}

// [[Rcpp::export]]
double meanC(NumericVector x, bool narm) {
    double total = 0;
    x = treat_missing(x, narm=narm); 
    int n = x.size();

    for (int i=0;i<n;i++) {
    total += x[i];
    }
    
    return total/n;

}

// [[Rcpp::export]]
double varC(NumericVector x, bool narm) {
    x = treat_missing(x, narm=narm); 
    int n = x.size();
    double var;
    
    //estimate mean
    double mean;

    for (int i=0; i<n; i++){
        mean += x[i];
    }
    mean = mean / n;
    
    //estimate difference
    NumericVector diff(n);

    for (int i=0; i<n; i++){
        diff[i] = pow(x[i] - mean, 2.0); 
    }
    
    //estimate sum of squared differences

    for (int i=0; i<n; i++){
        var += diff[i];
    }
    var = var / n;

    return var;

}

// [[Rcpp::export]]
NumericVector diffC(NumericVector x, int lag=1, bool narm=true) {
    x = treat_missing(x, narm=narm); 
    int n = x.size();
    NumericVector res(n-lag);
    double d;


    for (int i=0; i<n-lag; i++){
        d = x[i+lag] - x[i];
        res[i] = d; 
    }
    
    return res;
}


// [[Rcpp::export]]
NumericVector cumsumC(NumericVector x, bool narm=true) {
    x = treat_missing(x, narm=narm); 
    int n = x.size();
    NumericVector res(n);
    double sum;
    
    sum = x[0];
    for (int i=0; i<n; i++){
    sum = sum + x[i];
    res[i] = sum;
    }
    
    return res;
}

//Rcpp sugar

// [[Rcpp::export]]
bool any_naC(NumericVector x) {
    // performs lazy evaluation, checks first value and stops if NA
    return is_true(any(is_na(x)));
}


//STL
//standard template library
//using iterators

// [[Rcpp::export]]
double sumC2(NumericVector x) {
    double total = 0;


    NumericVector::iterator it;
    for(it = x.begin(); it != x.end(); ++it) {
    total += *it;
    }
    return total;
}

// apply functions can also be used by STL
// it needs the 'numeric' header!
// [[Rcpp::export]]
double sumc3(NumericVector x) {
    return std::accumulate(x.begin(), x.end(), 0.0) // third parameter format gives output and operation format!!!
}


// [[Rcpp::export]]
IntegerVector findinterval2(NumericVector x, NumericVector breaks) {
    IntegerVector out(x.size());

    NumericVector::iterator it, pos;
    IntegerVector::iterator out_it;

    for(it = x.begin(), out_it = out.begin(); it != x.end(); ++it, ++out_it) {
        pos = std::upper_bound(breaks.begin(), breaks.end(), *it);
        *out_it = std::distance(breaks.begin(), pos);
    }
    return out; 
}

//STL vectors: templated, need to specify object type
// accepts [] filtering and .push_back() for adding new element
// .reserve() is used for storage allocation

#include <Rcpp.h>
using namespace Rcpp;


// [[Rcpp::export]]
double meanC(NumericVector x) {
    int n = x.size();
    double total = 0;
   
    for (int i=0;i<n;i++) {
    total += x[i];
    }
    
    return total/n;

}

/*** R
library(microbenchmark)
x <- runif(1e6)

microbenchmark(
 mean(x),
 meanC(x)
)
*/


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
NumericVector diffC(NumericVector x, int lag=1) {
    int n = x.size();
    NumericVector res(n-lag);
    double d;


    for (int i=0; i<n-lag; i++){
        d = x[i+lag] - x[i];
        res[i] = d; 
    }
    
    return res;
}


/*** R
library(microbenchmark)
x <- runif(1e6)

microbenchmark(
 diff(x),
 diffC(x,1)
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
double varC(NumericVector x) {
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


/*** R
library(microbenchmark)
x <- runif(1e6)

microbenchmark(
 var(x),
 varC(x)
)
*/

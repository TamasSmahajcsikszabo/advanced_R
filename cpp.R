library(Rcpp)

sourceCpp("./test.cpp")

# all implementation in C++/R
x <- c(TRUE, TRUE, FALSE)
allC(x)

y <- c(1,1,1,1)
allC(y)


# cumprod implementation in C++/R
x <- c(1,2,3,2,3,2,2)
cumprod(x)
cumprodC(x)



# cummin implementation in C++/R
x <- c(-1,6,2,0,2,6,2,2,-2)
cummin(x)
cumminC(x)



# cummax implementation in C++/R
x <- c(-1,6,2,0,2,6,2,2,-2)
cummax(x)
cummaxC(x)


# diff implementation in C++/R
x <- c(-1,6,2,0,2,6,2,2,-2)
diff(x, 2)
diffC(x, 2)
diffC(1:10)
diff(1:10)


# range implementation in C++/R
x <- rnorm(1e8)
range(x)
rangeC(x)


# var implementation in C++/R
x <- rnorm(1e2)
x <- 1:100
var(x)
varC(x)

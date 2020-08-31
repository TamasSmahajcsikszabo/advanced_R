library(Rcpp)
data(mtcars)

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

attribs()

mod  <- lm(mpg ~ wt, data = mtcars)
mpe(mod)

# calling functions from C++
x <- rnorm(100)
callC(mean, x)
lapplyC(x, function(x) x+1)

# check for missing values
x <- c(1, 2, 3, 4, NA)
is_naC(x)


# exercises
x  <-  c(NA, 1, 2, NA, 4, 5, NA)
is_naC(x)
treat_missing(x, narm = TRUE)
treat_missing(x, narm = FALSE)

meanC(x, narm=FALSE)
meanC(x, narm=TRUE)


x <-  rnorm(100)
mask <- sample(c(TRUE, FALSE), 100, replace=TRUE)
x[mask] <- NA
varC(x, narm=TRUE)
varC(x, narm=FALSE)
var(x)
var(x, na.rm = TRUE)


x <- c(-1,6,2,0,2,6,2,2,-2, NA, NA)
diff(x, 2)
diffC(x, 2)



x <-  rnorm(100)
mask <- sample(c(TRUE, FALSE), 100, replace=TRUE)
x[mask] <- NA
cumsum(x)
cumsumC(x)

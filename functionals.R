########################## lapply ########################################
lapply2 <- function(x, f, ...) {
    out  <- vector("list", length(x)) 
    for (i in seq_along(x)){
        out[[i]]  <- f(x[[i]], ...)
    }
    out
} 

x <- c(4, 5, 6, 7, 8, 9, 0, 10) 
fun <- function(x){
    x * 10
}

lapply2(x, fun)

#plain version
l <- replicate(20, runif(sample(1:10, 1)), simplify=FALSE)
out <- vector("list", length(l))

for(i in seq_along(l)){
    out[[i]] <- length(l[[i]])
}
unlist(out)

#the same with lapply
unlist(lapply(l, length))

#lapply is good for dataframes, too
unlist(lapply(mtcars, min))

# replacing all cells with x/mean(x)
mtcars[] <- lapply(mtcars, function(x) x / mean(x))

# varying a different argument, by using an anonymous function
trims <- c(0, 0.1, 0.2, 0.5)
x <- rcauchy(1000)

unlist(lapply(trims, function(trim) mean(x, trim=trim)))

#looping
#don't combine, it's slow
x <- runif(1e3)
res <- c()
for (i in seq_along(x)){
    res <- c(res, sqrt(x[i]))
}

#create the needed space and fill in, it's better
res <- numeric(length(x))
for (i in seq_along(x)) {
    res[[i]] <- sqrt(x[[i]])
}


#just as in looping, lappy can also be used three ways:
lapply(x, sqrt)
lapply(seq_along(x), function(i) {sqrt(x[[i]])})
names(x) <- seq_along(x)
lapply(names(x), function(name) sqrt(x[name]))


## EXERCISES

#1. 
trims <- c(0, 0.1, 0.2, 0.5)
x <- rcauchy(1e3)

lapply(trims, function(trim) mean(x, trim))
lapply(trims, mean, x=x)


#2.
scale01 <- function(x){
    rng <- range(x, na.rm=TRUE)
    (x - rng[1]) / (rng[2] - rng[1])
}

lapply(mtcars, scale01)
mask <- unlist(lapply(mtcars, is.numeric))
lapply(mtcars[, mask], scale01)

#3.
formulas <- list(
                 mpg ~ disp,
                 mpg ~ I(1/disp),
                 mpg ~ disp + wt,
                 mpg ~I(1/disp) + wt
)
for (f in formulas) {
    fit <- lm(f, mtcars)
    print(fit)
}

models1 <- lapply(formulas, lm, mtcars)


#4.
bootstraps <- lapply(1:10, function(i) {
                         rows <- sample(1:nrow(mtcars), rep=TRUE)
                         mtcars[rows,]
})

models2 <- lapply(bootstraps, lm, formula = mpg~disp)


lapply(X=seq(1,10), FUN=lm, data = mtcars[sample(1:nrow(mtcars), rep = TRUE),], formula = mpg ~ disp)


#5.
rsq <- function(mod) summary(mod)$r.squared
lapply(models1, rsq)
lapply(models2, rsq)

library(Rcpp)
library(microbenchmark)

cppFunction('int one () {
            return 1;
}')

one()

cppFunction('int signC(int x) {
            if (x > 0) {
                return 1;
            } else if (x == 0) {
                return 0;
            } else {
                return -1;
            }
}')

signC(-10)



sumR <- function(x){
    total <- 0;
    for (i in seq_along(x)){
        total <- total + x[[i]]
    }

    total
}

cppFunction('double sumC(NumericVector x) {
            int n = x.size();
            double total = 0;
            for(int i=0; i<n; ++i){
                total += x[i];
            }
            return total;
}')

x  <- rnorm(10000)


sumC(x)
sumR(x)

microbenchmark(sumR(x), sumC(x))


pdistR <- function(x, ys){
    sqrt((x - ys)^2)
}

cppFunction('NumericVector pdistC(double x, NumericVector ys) {
            int n = ys.size();
            NumericVector out(n);

            for(int i =0; i < n; ++i){
                out[i] = sqrt(pow(ys[i] -x, 2.0));
            }

            return out;
}')

x <- .5
ys <- rnorm(1e6)

microbenchmark(
               pdistR(x, ys),
               pdistC(x, ys)
)

pdistC(x, ys)
pdistR(x, ys)


cppFunction('NumericVector rowSumC(NumericMatrix x) {
            int nrow = x.nrow(), ncol = x.ncol();
            NumericVector out(nrow);

            for (int i = 0; i< nrow; i++) {
                double total = 0;
                for (int j = 0; j<ncol; j++){
                    total += x(i,j);
                }
                out[i] = total;
            }
            return out;

}')

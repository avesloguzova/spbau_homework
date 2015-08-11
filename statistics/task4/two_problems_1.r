k = 10
n = 1000
lambdas = runif(k,0,1)
experiments = array(data = rep_len(0.1,k*n),dim = c(n,k))
for (i in seq(1,k)){
    gadget_work_times = rexp(n,lambdas[i])
    for(j in seq(1,n)){
      experiments[j,i] = gadget_work_times[j]
    }
}
result_experiments = apply(experiments,1,min)
h <- hist(result_experiments,plot=FALSE)
h$counts=h$counts/sum(h$counts)
plot(h)
x <- seq(0,3, length = 1000)
lines(x,dexp(x,sum(lambdas)),type = "l",col = "red")
d=density(result_experiments)
lines(d,col="blue")

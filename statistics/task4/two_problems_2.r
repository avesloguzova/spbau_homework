k = 100
n = 10^5
pose = 1
experiments = array(data = runif(k*n),dim = c(n,k))
result_experiments_min = apply(experiments,1,min)
result_experiments_max = apply(experiments,1,max)

x <- seq(0,3, length = 1000)
plot(x,dbeta(x,1,k),type = "l",col = "red")
h <- hist(result_experiments_min,plot=FALSE)
h$counts=h$counts/sum(h$counts)
lines(h)
d=density(result_experiments_min)
lines(d,col="blue")

plot(x,dbeta(x,k,1),type = "l",col = "red")
h <- hist(result_experiments_max,plot=FALSE)
h$counts=h$counts/sum(h$counts)
lines(h)
d=density(result_experiments_max)
lines(d,col="blue")

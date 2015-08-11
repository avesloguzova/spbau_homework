require(hydroGOF)

x <- seq(0, 1, length = 1000)
f = function(x){
  return(sin(x)^(3/4))
}
palpha = 1
pbeta = 1/4
plambda= 3

plot(x, f(x), xlab = "x-values", ylab = "f(x)", type = "l")
lines(x,dbeta(x,palpha,pbeta),type = "l",col = "red")


eta_generate_beta = function(x){
  return(f(x)/dbeta(x,palpha,pbeta))
}


eta_generate_exp = function(x){
  return(f(x)/(plambda*exp(-plambda*x)))
}


experiment = function(N){
  eta = eta_generate_beta (rbeta(N,palpha,pbeta))
  return (mean(eta))
}

max_pow = 6
part_size = 1000
RMSE = vector("numeric",max_pow)
I = rep_len(integrate(f,0,1)$value,part_size)
for( i in seq(1,max_pow)){
  x = array(data=rep_len(10^i,part_size),part_size)
  gammas = apply(X = x,MARGIN = 1,experiment)
  RMSE[i] = rmse(gammas,I)
}
plot(x = seq(1,max_pow),y = RMSE,main="RMSE/N",type = "p",xlab = "logN",ylab = "RMSE")

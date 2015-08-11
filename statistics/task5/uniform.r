require (stats)
require(hydroGOF)

est1 = function(sample){
  return (2*mean(sample))
}
est2 = function(sample){
  return (max(sample))
}
est3 = function(sample){
  return((N+1)/N*max(sample))
}
est4 = function(sample){
  return(2*median(sample))
}
est5 = function(sample){
  return(4*quantile(sample, probs = 0.25, names = FALSE))
}
est6 = function(sample){
  return(3/4*quantile(sample, probs = (0.75), names = FALSE))
}
param = 1
N_min = 100
N_max = 10000
M = 1000
n_seq = 10^seq(2, 4)
param_vec = rep_len(param,M)
plot(N_min,0.001,type = "p",col = "white",xlim=c(N_min,N_max*100),ylim = c(0.0001,1),log="xy",xlab = "N", ylab="RMSE")

for( N in n_seq){
  experiments = array(data = runif(N*M,0,param),dim = c(M,N))
  result_est1 = rmse(apply(X = experiments,MARGIN = 1,est1),param_vec)
  points(N,result_est1,type="p",col = "black")
  result_est2 = rmse(apply(X = experiments,MARGIN = 1,est2),param_vec)
  points(N,result_est2,type="p",col = "red")
  result_est3 = rmse(apply(X = experiments,MARGIN = 1,est3),param_vec)
  points(N,result_est3,type="p",col = "blue")
  result_est4 = rmse(apply(X = experiments,MARGIN = 1,est4),param_vec)
  points(N,result_est4,type="p",col = "pink")
  result_est5 = rmse(apply(X = experiments,MARGIN = 1,est5),param_vec)
  points(N,result_est1,type="p",col = "yellow")
  result_est6 = rmse(apply(X = experiments,MARGIN = 1,est6),param_vec)
  points(N,result_est1,type="p",col = "green")
}

legend(2000*10,0.3,  
       c("2*mean","max X_i", "n+1/n*max X_i","2*median","4q.25","3/4q.75"), 
       lty=c(1,1,1,1,1,1),
       lwd=c(2.5,2.5),col=c("black","red","blue","pink","yellow","green")) # gives the legend lines the correct color and width
require (stats)
require(hydroGOF)

est1 = function(sample){
  return (median(sample))
}
est2 = function(sample){
  sample1 = sample[-c(which.max(sample),which.min(sample))]
  return (mean(sample1))
}
est3 = function(sample){
  return (mean(sample,trim=0.05))
}
param = 0
N_min = 100
N_max = 10^4
M = 1000
n_seq = 10^seq(2, 4)
param_vec = rep_len(param,M)
plot(N_min,0.0001,type = "p",col = "white",xlim=c(N_min,N_max*100),ylim=c(0.000001,2),log="xy",xlab = "N", ylab="RMSE")

for( N in n_seq){
  experiments = array(data = rcauchy(N*M,param),dim = c(M,N))
  result_est1 = rmse(apply(X = experiments,MARGIN = 1,est1),param_vec)
  points(N,result_est1,type="p",col = "black")
  result_est2 = rmse(apply(X = experiments,MARGIN = 1,est2),param_vec)
  points(N,result_est2,type="p",col = "red")
  result_est3 = rmse(apply(X = experiments,MARGIN = 1,est3),param_vec)
  points(N,result_est3,type="p",col = "blue")
}
legend(2*N_max,0.3, # places a legend at the appropriate place 
       c("median","mean'", "trimmed mean"), # puts text in the legend 
       
       lty=c(1,1,1), # gives the legend appropriate symbols (lines)
       
       lwd=c(1,1),col=c("black","red","blue","pink","yellow","green")) # gives the legend lines the correct color and width
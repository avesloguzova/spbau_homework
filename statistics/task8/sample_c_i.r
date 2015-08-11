require (stats)
require(hydroGOF)

ciwidth = function(interval){
  return(interval[2]-interval[1])
}
trustylevel = function(X, interval){
  check = function(x){
    if(x < interval[2] && x > interval[1]){
      return(1)
    } else {
      return(0)
    }
  }
  
  res = apply(array(X,dim=length(X)),MARGIN = 1,FUN = check)
  return (sum(res)/length(X))
}
norm =  function(ci,a,s,M,len){
  qlevel = c((1-ci)/2,(1+ci)/2)
  
  RMSE_ql_nonpar = array(0.0,dim = len)
  RMSE_qr_nonpar = array(0.0,dim = len)
  
  RMSE_ql_par = array(0.0,dim = len)
  RMSE_qr_par = array(0.0,dim = len)
  
  realq = qnorm(qlevel, mean = a, sd = s)
  n_seq = 10**seq(1,len)
  
  for(j in seq(1,len)){
    N = n_seq[j]
    w_nonpar = array(0.0,dim = M)
    trusty_level_nonpar = array(0.0,dim = M)
    q_nonpar  = array(0.0,dim = c(2,M))
    
    
    w_par = array(0.0,dim = M)
    trusty_level_par = array(0.0,dim = M)
    q_par  = array(0.0,dim = c(2,M))
    
    for(i in seq(M)) {
        x <- rnorm(N, mean = a, sd = s)
        q_nonpar[,i] = quantile(x, probs = qlevel)
        w_nonpar[i] = ciwidth(q_nonpar[,i])
        trusty_level_nonpar[i] = trustylevel(x,q_nonpar[,i])
        
        q_par[,i] = qnorm(qlevel, mean = mean(x), sd = sd(x))
        w_par[i] = ciwidth(q_par[,i])
        trusty_level_par[i] = trustylevel(x,q_par[,i])
      
    }
    ql_real = rep_len(realq[1],M)
    RMSE_ql_nonpar[j] = rmse(q_nonpar[1,],ql_real)
    RMSE_ql_par[j] = rmse(q_par[1,],ql_real)
    
    qr_real = rep_len(realq[2],M)
    RMSE_qr_nonpar[j] = rmse(q_nonpar[2,],qr_real)
    RMSE_qr_par[j] = rmse(q_par[2,],qr_real)
    
    print("N:")
    print(N)
    
    print("Non paramethric")
    print("CI width:")
    print(mean(w_nonpar),digits=4)
    print(sd(w_nonpar)/sqrt(M),digits=4)
    print("CI trusty level:")
    print(mean(trusty_level_nonpar),digits=4)
    print(sd(trusty_level_nonpar)/sqrt(M),digits=4)
    
    print("Paramethric")
    print("CI width:")
    print(mean(w_par),digits=4)
    print(sd(w_par)/sqrt(M),digits=4)
    print("CI trusty level:")
    print(mean(trusty_level_par),digits=4)
    print(sd(trusty_level_par)/sqrt(M),digits=4)
  }
  plot(x = n_seq,y = RMSE_ql_nonpar, xlim=c(10,10^(len+1)),ylim = c(0.00001,1),log="xy",xlab = "N", ylab="RMSE non-parametric",col="red")
  points(x = n_seq,y = RMSE_qr_nonpar, col = "blue")
  
  plot(x = n_seq,y = RMSE_ql_par, type = "p", xlim=c(10,10^(len+1)),ylim = c(0.00001,1),log="xy",xlab = "N", ylab="RMSE parametric",col="red")
  points(x = n_seq,y = RMSE_qr_par, col = "blue")
}
student =  function(ci,df,M,len){
  qlevel = c((1-ci)/2,(1+ci)/2)
  
  RMSE_ql_nonpar = array(0.0,dim = len)
  RMSE_qr_nonpar = array(0.0,dim = len)
  
  RMSE_ql_par = array(0.0,dim = len)
  RMSE_qr_par = array(0.0,dim = len)
  
  realq = qt(qlevel, df = df)
  n_seq = 10**seq(1,len)
  
  for(j in seq(1,len)){
    N = n_seq[j]
    w_nonpar = array(0.0,dim = M)
    trusty_level_nonpar = array(0.0,dim = M)
    q_nonpar  = array(0.0,dim = c(2,M))
    
    
    w_par = array(0.0,dim = M)
    trusty_level_par = array(0.0,dim = M)
    q_par  = array(0.0,dim = c(2,M))
    
    for(i in seq(M)) {
      x <- rt(N,df = df)
      q_nonpar[,i] = quantile(x, probs = qlevel)
      w_nonpar[i] = ciwidth(q_nonpar[,i])
      trusty_level_nonpar[i] = trustylevel(x,q_nonpar[,i])
      
      q_par[,i] = qnorm(qlevel, mean = mean(x), sd = sd(x))
      w_par[i] = ciwidth(q_nonpar[,i])
      trusty_level_par[i] = trustylevel(x,q_par[,i])
      
    }
    ql_real = rep_len(realq[1],M)
    RMSE_ql_nonpar[j] = rmse(q_nonpar[1,],ql_real)
    RMSE_ql_par[j] = rmse(q_par[1,],ql_real)
    
    qr_real = rep_len(realq[2],M)
    RMSE_qr_nonpar[j] = rmse(q_nonpar[2,],qr_real)
    RMSE_qr_par[j] = rmse(q_par[2,],qr_real)
    
    print("N:")
    print(N)
    
    print("Non paramethric")
    print("CI width:")
    print(mean(w_nonpar),digits=4)
    print(sd(w_nonpar)/sqrt(M),digits=4)
    print("CI trusty level:")
    print(mean(trusty_level_nonpar),digits=4)
    print(sd(trusty_level_nonpar)/sqrt(M),digits=4)
    
    print("Paramethric")
    print("CI width:")
    print(mean(w_par),digits=4)
    print(sd(w_par)/sqrt(M),digits=4)
    print("CI trusty level:")
    print(mean(trusty_level_par),digits=4)
    print(sd(trusty_level_par)/sqrt(M),digits=4)
  }
  plot(x = n_seq,y = RMSE_ql_nonpar, xlim=c(10,10^(len+1)),ylim = c(0.00001,1),log="xy",xlab = "N", ylab="RMSE non-parametric",col="red")
  points(x = n_seq,y = RMSE_qr_nonpar, col = "blue")
  
  plot(x = n_seq,y = RMSE_ql_par, type = "p", xlim=c(10,10^(len+1)),ylim = c(0.00001,1),log="xy",xlab = "N", ylab="RMSE parametric",col="red")
  points(x = n_seq,y = RMSE_qr_par, col = "blue")
}
print(0.95)
print("Normal")
norm(ci = 0.95,a = 0,s = 1,M = 1000,len = 5)
print("t,df=5")
student(ci = 0.95,df = 5,M = 1000,len = 5)
print("t,df=20")
student(ci = 0.95,df = 20,M = 1000,len = 5)
print("=========")
print(0.99)
print("Normal")
norm(ci = 0.99,a = 0,s = 1,M = 1000,len = 5)
print("t,df=5")
student(ci = 0.99,df = 5,M = 1000,len = 5)
print("t,df=20")
student(ci = 0.99,df = 20,M = 1000,len = 5)

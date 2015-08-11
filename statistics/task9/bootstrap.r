get_npbootsrap_sample = function(x, size = 999, obs_len = length(x),  FUNC ){
  resample = array(sample(x,obs_len*size,TRUE), c(size,obs_len))
  return(apply(resample,MARGIN = 1, FUNC))
}
get_pbootstrap_sample = function(x, size = 999, obs_len = length(x),  FUNC){
  a = mean(x)
  s = sd(x)
  resample = array(rnorm(n = size*obs_len,mean = a, sd = s), c(size,obs_len))
  return(apply(resample,MARGIN = 1, FUNC))
}
get_pbootstrap_sample_median = function(x, size = 999, obs_len = length(x),  FUNC){
  a = median(x)
  s = mad(x, constant = 1)
  resample = array(rnorm(n = size*obs_len,mean = a, sd = s), c(size,obs_len))
  return(apply(resample,MARGIN = 1, FUNC))
}
bootstrap_basic_ci = function(bootstrap_sample,t.hat, alpha = 0.95){
    ci.lower <- 2*t.hat - quantile(bootstrap_sample,1-alpha/2)
    ci.upper <- 2*t.hat - quantile(bootstrap_sample,alpha/2)
    return(c(ci.lower,ci.upper))
}
bootstrap_normal_ci = function(bootstrap_sample, alpha = 0.95){
  s = sd(bootstrap_sample)
  ci.lower <- mean(bootstrap_sample) - qt(1-alpha/2,length(bootstrap_sample))*s
  ci.upper <- mean(bootstrap_sample) - qt(alpha/2,length(bootstrap_sample))*s
  return(c(ci.lower,ci.upper))
}

x = rnorm(25,mean = 2,sd = 3)



print("NORMAL NON_PAR")
bootstrap_sample = get_npbootsrap_sample(x, FUNC = mean)
print("Bootstrap CI(mean):")
print(bootstrap_basic_ci(bootstrap_sample,mean(x)))
print(bootstrap_normal_ci(bootstrap_sample))
print("CI:")
print(mean(x) + qnorm(c(0.025, 0.975), sd = sd(x) / sqrt(length(x))))
bootstrap_sample = get_npbootsrap_sample(x, FUNC = var)
print("Bootstrap CI(var):")
print(bootstrap_basic_ci(bootstrap_sample,sd(x)))
print(bootstrap_normal_ci(bootstrap_sample))
print("CI")
print(var(x) * (length(x) - 1) / qchisq(c(0.975, 0.025), df = length(x) - 1))

print("NORMAl PAR")
bootstrap_sample = get_pbootstrap_sample(x, FUNC = mean)
print("Bootstrap CI(mean):")
print(bootstrap_basic_ci(bootstrap_sample,mean(x)))
print(bootstrap_normal_ci(bootstrap_sample))
print("CI:")
print(mean(x) + qnorm(c(0.025, 0.975), sd = sd(x) / sqrt(length(x))))

bootstrap_sample = get_pbootstrap_sample(x, FUNC = var)
print("Bootstrap CI(var):")
print(bootstrap_basic_ci(bootstrap_sample,var(x)))
print(bootstrap_normal_ci(bootstrap_sample))
print("CI")
print(var(x) * (length(x) - 1) / qchisq(c(0.975, 0.025), df = length(x) - 1))

print("CAUCHY NON_PAR")
x = rcauchy(25,location = 3,scale = 4)

bootstrap_sample = get_npbootsrap_sample(x, FUNC = median)
plot(density(bootstrap_sample))
print("Bootstrap CI(a = median):")
print(bootstrap_basic_ci(bootstrap_sample,median(x)))
print(bootstrap_normal_ci(bootstrap_sample))

my_mad = function(x){
  return(mad(x,constant=1))
}

bootstrap_sample = get_npbootsrap_sample(x, FUNC = my_mad)
plot(density(bootstrap_sample))
print("Bootstrap CI(scale = mad):")
print(bootstrap_basic_ci(bootstrap_sample,mad(x,constant=1)))
print(bootstrap_normal_ci(bootstrap_sample))

print("CAUCHY PAR")
bootstrap_sample = get_pbootstrap_sample_median(x, FUNC = median)
plot(density(bootstrap_sample))
print("Bootstrap CI(a = median):")
print(bootstrap_basic_ci(bootstrap_sample,median(x)))
print(bootstrap_normal_ci(bootstrap_sample))

bootstrap_sample = get_pbootstrap_sample_median(x, FUNC = my_mad)
plot(density(bootstrap_sample))
print("Bootstrap CI(scale = mad):")
print(bootstrap_basic_ci(bootstrap_sample,mad(x,constant=1)))
print(bootstrap_normal_ci(bootstrap_sample))


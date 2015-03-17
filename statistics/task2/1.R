n = 3
size = 100000
get = function(){
  result = runif(n-1)
  return( c(result, sum(result)%%1))
}
spheresCenter = rep_len(0.5, n)
smallsphereCentre = rep_len(0.5,n-1)
isInSphere= function(spheresCenter,x){  
  vec = rbind(spheresCenter, x)
  d = dist(vec)
  return(d<0.5)
}
Vectorize(isInSphere)
m=replicate(size,get())

plot(x = m[1,],y = m[2,],main="Plot of distribution of two independent random var",type = "p")
library(scatterplot3d)
library(plotrix)
scatterplot3d(x= m[1,],y=m[2,],z=m[3,],main="Plot of distribution of three dependent random var",color="royalblue4")
scatterplot3d(x=m[1,],y=m[2,],z=runif(size),main="Plot of distribution of three independent random var",color="royalblue4")

n = 5
spheresCenter = rep_len(0.5, n)
smallsphereCentre = rep_len(0.5,n-1)
count_in_n_sphere = 0
volume_n_sphere = array(dim=size)
count_in_nm1_sphere = 0
volume_nm1_sphere = array(dim=size)
for (i in seq(1,size)){
  point = get()
  count_in_n_sphere = count_in_n_sphere + isInSphere(spheresCenter,point)
  volume_n_sphere[i] = count_in_n_sphere/i
  count_in_nm1_sphere = count_in_nm1_sphere + isInSphere(smallsphereCentre,point[1:n-1])
  volume_nm1_sphere[i] = count_in_nm1_sphere/i
}
plot(seq(1,size), volume_n_sphere, main="Plot of volume with MK method for depend vars. n=5", 
     xlab="Count of poins ", ylab="Volume ", pch=1)
print(volume_n_sphere[size])
plot(seq(1,size), volume_nm1_sphere, main="Plot of volume with MK method for independ vars. n=4", 
     xlab="Count of poins ", ylab="Volume ", pch=1)
print(volume_nm1_sphere[size])

n = 10
spheresCenter = rep_len(0.5, n)
smallsphereCentre = rep_len(0.5,n-1)
count_in_n_sphere = 0
volume_n_sphere = array(dim=size)
count_in_nm1_sphere = 0
volume_nm1_sphere = array(dim=size)
for (i in seq(1,size)){
  point = get()
  count_in_n_sphere = count_in_n_sphere + isInSphere(spheresCenter,point)
  volume_n_sphere[i] = count_in_n_sphere/i
  count_in_nm1_sphere = count_in_nm1_sphere + isInSphere(smallsphereCentre,point[1:n-1])
  volume_nm1_sphere[i] = count_in_nm1_sphere/i
}
plot(seq(1,size), volume_n_sphere, main="Plot of volume with MK method for depend vars. n=10", 
     xlab="Count of poins ", ylab="Volume ")
print(volume_n_sphere[size])
plot(seq(1,size), volume_nm1_sphere, main="Plot of volume with MK method for independ vars. n=9", 
     xlab="Count of poins ", ylab="Volume ")
print(volume_nm1_sphere[size])

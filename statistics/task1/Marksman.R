isInCircle =  function(points) {
  fn <- function(x, y) (dist(rbind(c(0.5,0.5), c(x,y)))<0.5)
  return (mapply(fn, points[,1], points[,2]))
}
geomseq = (10**(2:8))
for(i in geomseq) {
  pts <- cbind(runif(i),runif(i))
  print(sum((isInCircle(pts))/length(pts[,1])))
}
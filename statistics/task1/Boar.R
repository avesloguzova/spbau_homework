v=sample(c(0,1, 2, 3),10^4,replace=TRUE,prob=c(0.548,0.224,0.144,0.084))
all = v[v!=0]
print (table(all)/length(all))

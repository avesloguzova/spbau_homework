train_test_split = function(dataset, ratio){
  index <- 1:nrow(dataset)
  trainindex <- sample(index, trunc(length(index)*ratio))
  trainset <- dataset[trainindex, ]
  testset <- dataset[-trainindex, ]
  return (list(trainY = trainset[,1],trainX = trainset[,-1],testY = testset[,1],testX=testset[,-1]))
}

knn = function(X_train,Y_train,X_test,dist,k){
  y_test <- vector(length = nrow(X_test))
  for (i in seq(from <- 1, to <- nrow(X_test))){
    distances <- vector(length = nrow(X_train))
    for( j in seq(from <- 1, to <- nrow(X_train))){
      distances[j] <- dist (X_train[j,],X_test[i,])    
    }
    zipped = mapply(c,distances,Y_train)
    sorted = zipped[,order(distances)]
    kmin = sorted[,1:k]
    y_test[i]=names(which.max(table(kmin[2,])))
  }
  return (y_test)
}
euclidian_distance = function(train,test){
  return(dist(rbind(train, test),method = "euclidian"))
}
other_distance = function(train,test){
  return(dist(rbind(train,test),"maximum"))
}
print_precision_recall = function(y_pred, y_test) {
  nclasses = unique(y_pred)
  
  for (class in nclasses) {
    TP = 0
    FP = 0
    FN = 0 
    for (i in seq(1,length(y_pred))) {
      if (y_test[i] == class) {
        if (y_test[i] == y_pred[i]) {
          TP = TP + 1
        }
        else{
          FP = FP+1
        }
      }else{
        if (y_test[i] != y_pred[i]) {
          FN = FN + 1
        }
      }
    }
    presision = TP/(TP+FP)
    recall = TP/(TP+FN)
    print("Class:")
    print(class)
    print("presision")
    print(presision)
    print("recall")
    print(recall)
    
  }
}
loocv = function(X_train, y_train, X_test, y_test, dist) {
  opt_k = 0
  opt_measure = length(y_train)+length(y_test)
  x = rbind(X_train,X_test)
  y = c(y_train,y_test)
  for(k in seq (from = 2, to = length(y)/3)){
    measure=0
    for (i in seq(1,length(y))){
      measure = (knn(x[-i,],y[-i],x[i,],dist,k)[1] != y[i])+measure
    }
    if (measure<opt_measure) {
      opt_k = k
      opt_measure = measure
    }
  }
  return (opt_k)
}

test = function(dataset, distance, ratio) {
  s = train_test_split(dataset,ratio)
  opt_k = loocv(s$trainX, y_train = s$trainY,X_test = s$testX, y_test = s$testY,distance)
  print (opt_k)
  y_pred = knn (s$trainX, Y_train = s$trainY,X_test = s$testX,distance,opt_k)
  print_precision_recall(y_pred,s$testY)  
}

all_vine <- read.csv(file = "/home/av/spbau_homework/maching_learning/task2(vine)/wine.csv",sep = ',')
ratio <- 0.7

test(all_vine,euclidian_distance,ratio)
test(all_vine, other_distance, ratio)




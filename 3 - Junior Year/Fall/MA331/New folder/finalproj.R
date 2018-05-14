fm <- lm(ds[,"teq"] ~ ds[,"teqpcb"] + ds[,"teqdioxin"] + ds[,"teqfuran"])
fm
summary(fm)

res <- residuals(fm)
res
stem(res)
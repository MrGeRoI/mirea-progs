library("lmtest")
library(car)

# Практическая работа №2. Множественная регрессия. Вариант 19
  
  # Данные были взяты из американского журнала Motor Trend за 1974 год и
  # включают расход топлива и 10 аспектов автомобильного дизайна и
  # эксплуатационных характеристик для 32 автомобилей (1973-74 моделей).

  # mpg -	Miles/(US) gallon
  # wt - Weight (1000 lbs)
  # qsec - 1/4 mile time
  # hp - Gross horsepower
  # drat - Rear axle ratio

  help(mtcars)
  data = mtcars
  help(mtcars)

#1. Проверяю отсутствие линейной зависимости между регрессорами
  summary(lm(wt~qsec, data))  # R^2 = 0%
  summary(lm(wt~drat, data))  # R^2 ~= 50%
  summary(lm(wt~hp, data))    # R^2 ~= 42%
  
  summary(lm(drat~qsec, data))  # R^2 = 0%
  summary(lm(drat~wt, data))    # R^2 ~= 50%
  summary(lm(drat~hp, data))    # R^2 ~= 17%
  
  summary(lm(qsec~drat, data))  # R^2 = 0%
  summary(lm(qsec~wt, data))    # R^2 = 0%
  summary(lm(qsec~hp, data))    # R^2 ~= 49%
  
  summary(lm(hp~qsec, data))  # R^2 = 49%
  summary(lm(hp~drat, data))  # R^2 ~= 17%
  summary(lm(hp~wt, data))    # R^2 ~= 42%
  
  # Итого:
  # wt и hp, wt и drat между собой имеют линейные зависимости (***)
  # drat и hp маловероятно имеют между собой линейную зависимость (** )
  # Ставить эти регрессоры вместе в модели не имеет смысла
#2. Строю модель, которую необходимо проверить
  summary(lm(mpg~wt, data))   # R^2 ~= 75%
  summary(lm(mpg~qsec, data)) # R^2 ~= 15%
  summary(lm(mpg~hp, data))   # R^2 ~= 59%
  summary(lm(mpg~drat, data)) # R^2 ~= 44%
  
  # Из этих моделей лучше всего:
  model1 = lm(mpg~wt, data)
  summary(model1) # R^2 ~= 74%
  
  # Добавляю ещё регрессоры, которые не зависят от wt:
  summary(lm(drat~wt, data))  # (***)
  summary(lm(qsec~wt, data))  # (   ) <- лучший вариант
  summary(lm(hp~wt, data))    # (***)
  
  # Модель стала лучше, когда добавлил qsec в модель:
  model2 = lm(mpg~wt+qsec, data)
  summary(model2) # R^2 ~= 81%
  
  # Показатели vif характеристики модели model2 хорошие (< 1.05)
  vif(model2)
  
#3. Ввожу в модели логарифмы регрессоров:
  summary(lm(mpg~log(wt), data))    # R^2 ~= 80%
  summary(lm(mpg~log(qsec), data))  # R^2 ~= 15%
  summary(lm(mpg~log(hp), data))    # R^2 ~= 71%
  summary(lm(mpg~log(drat), data))  # R^2 ~= 44%
  
  summary(lm(log(wt)~wt, data))     # (***)
  summary(lm(log(qsec)~wt, data))   # (   )
  summary(lm(log(hp)~wt, data))     # (***)
  summary(lm(log(drat)~wt, data))   # (***)
  
  summary(lm(log(wt)~qsec, data))     # (   )
  summary(lm(log(qsec)~qsec, data))   # (***)
  summary(lm(log(hp)~qsec, data))     # (***)
  summary(lm(log(drat)~qsec, data))   # (   )
  
  # Все логарифмы регрессоров зависят от регрессоров модели.
  # ln(hp) зависит от обоих регрессоров, а ln(drat) имеет плохую зависимость, так что не рассматриваю такие модели
  # ln(wt), ln(drat) зависят от wt, а ln(qsec) от qsec, так что есть возможность заменить регрессоры на их логарифмы:
  model31 = lm(mpg~log(wt)+qsec, data)      # R^2 = 87.0%
  model32 = lm(mpg~wt+log(qsec), data)      # R^2 = 81.8%
  model33 = lm(mpg~log(wt)+log(qsec), data) # R^2 = 87.1%
  
  summary(model31) # R^2 = 87.0%
  summary(model32) # R^2 = 81.8%
  summary(model33) # R^2 = 87.1%
  
  # Показатели vif характеристики промежуточных моделей model31, model32 и model33 хорошие (< 1.05)
  vif(model31)
  vif(model32)
  vif(model33)
  
  # Модель стала лучше, когда заменил: wt -> ln(wt), а qsec -> ln(qsec)
  model3 = lm(mpg~log(wt)+log(qsec), data) # R^2 = 87%
  summary(model3)
  
  # Показатели vif характеристики модели model3 хорошие (< 1.05)
  vif(model3)
  
#4. Ввожу в модель всевозможные произведения пар регрессоров (включая квадраты)
  summary( lm(mpg~I(wt^2), data) )    # R^2 ~= 63%
  summary( lm(mpg~I(qsec^2), data) )  # R^2 ~= 15%
  summary( lm(mpg~I(hp^2), data) )    # R^2 ~= 43%
  summary( lm(mpg~I(drat^2), data) )  # R^2 ~= 45%
  
  summary(lm(I(wt^2)~wt, data))     # (***)
  summary(lm(I(qsec^2)~wt, data))   # (   )
  summary(lm(I(hp^2)~wt, data))     # (** )
  summary(lm(I(drat^2)~wt, data))   # (***)
  
  summary(lm(I(wt^2)~qsec, data))     # (   )
  summary(lm(I(qsec^2)~qsec, data))   # (***)
  summary(lm(I(hp^2)~qsec, data))     # (***)
  summary(lm(I(drat^2)~qsec, data))   # (   )
  
  # Все квадраты регрессоров зависят от регрессоров модели.
  # hp^2 зависит от обоих регрессоров, а drat^2 имеет плохую зависимость, так что не рассматриваю модели с ними
  # но wt^2 зависит от wt, а qsec^2 от qsec, так что есть возможность заменить логарифмы регрессоров на их квадраты:
  model41 = lm(mpg~I(wt^2)+I(qsec^2), data) # R^2 ~= 70.5%
  model42 = lm(mpg~log(wt)+I(qsec^2), data) # R^2 ~= 86.7%
  model43 = lm(mpg~I(wt^2)+log(qsec), data) # R^2 ~= 70.9%

  summary(model41)
  summary(model42)
  summary(model43)
  
  # Показатели vif характеристики промежуточных моделей model41, model42 и model43 хорошие (< 1.05)
  vif(model41)
  vif(model42)
  vif(model43)
  
  # Модели стали хуже, когда заменил: ln(wt) -> wt^2 и ln(qsec) -> qsec^2
  # Следует вернуться к модели model3: mpg~ln(wt)+ln(qsec)

  summary( lm(mpg~I(drat*wt), data) )   # R^2 ~= 59%
  summary( lm(mpg~I(drat*qsec), data) ) # R^2 ~= 58%
  summary( lm(mpg~I(drat*hp), data) )   # R^2 ~= 40%
  summary( lm(mpg~I(qsec*wt), data) )   # R^2 ~= 54%
  summary( lm(mpg~I(qsec*hp), data) )   # R^2 ~= 69%
  summary( lm(mpg~I(wt*hp), data) )     # R^2 ~= 70%
  
  summary(lm(I(drat*wt)~wt, data))    # (***)
  summary(lm(I(drat*qsec)~wt, data))  # (***)
  summary(lm(I(drat*hp)~wt, data))    # (** )
  summary(lm(I(qsec*wt)~wt, data))    # (***)
  summary(lm(I(qsec*hp)~wt, data))    # (***)
  summary(lm(I(wt*hp)~wt, data))      # (***)
  
  summary(lm(I(drat*wt)~qsec, data))    # (   )
  summary(lm(I(drat*qsec)~qsec, data))  # (***)
  summary(lm(I(drat*hp)~qsec, data))    # (***)
  summary(lm(I(qsec*wt)~wt, data))      # (***)
  summary(lm(I(qsec*hp)~wt, data))      # (***)
  summary(lm(I(wt*hp)~wt, data))        # (***)
  
  # Все произведения регрессоров зависят от регрессоров модели.
  # drat*qsec, qsec*wt, qsec*hp и wt*hp зависит от обоих регрессоров, а сами по себе имеют слабую зависимость. Их не рассматриваю.
  # wt*drat зависит от wt, а hp*drat от qsec, так что есть возможность заменить логарифмы регрессоров на их произведение:
  model51 = lm(mpg~I(wt*drat)+log(qsec), data)  # R^2 ~= 65%
  model52 = lm(mpg~log(wt)+I(hp*drat), data)    # R^2 ~= 85%
  
  summary(model51)
  summary(model52)
  
  # Показатели vif характеристики промежуточных моделей model51 и model52 хорошие (< 1.05)
  vif(model51)
  vif(model52)

  # Модель стала хуже, когда заменил: ln(wt) -> wt*drat и ln(qsec) -> hp*drat
  # Следует вернуться к модели model3: mpg~ln(wt)+ln(qsec)
  
  # Итого, наилучшая модель:
    summary( model3 )
    # С такой зависимостью
    # model: mgp = -8.368 - 16.167 * ln(wt) + 16.195 * ln(qsec)
    # R^2 ~= 87%, p-вероятность: < 10^(-13) 
  
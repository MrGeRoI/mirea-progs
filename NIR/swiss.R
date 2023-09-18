library("lmtest")

# Практическая работа №1. Парная регрессия. Вариант 19

help(swiss)
data = swiss
help(data)

#1. Оцениваю среднее значение, дисперсию и СКО переменных:
  plot(data$Catholic,data$Fertility)
  
  plot(data$Catholic,data$Examination)
  
  # Catholic - процент католического населения в Французско-говорящих провинциях Швейцарии в 1888
  # Fertility - рождаемость в Французско-говорящих провинциях Швейцарии в 1888
  # Examination - процент отлично сдавших экзамены призывников в Французско-говорящих провинциях Швейцарии в 1888
  
  # Среднее значение
  data["Catholic_Mean"] = mean(data$Catholic)       # ~= 41 %
  data["Examination_Mean"] = mean(data$Examination) # ~= 16.5 %
  data["Fertility_Mean"] = mean(data$Fertility)     # ~= 70 Ig

  # Дисперсия
  data["Catholic_Variance"] = var(data$Catholic)        # ~= 1739 %
  data["Examination_Variance"] = var(data$Examination)  # ~= 64 %
  data["Fertility_Variance"] = var(data$Fertility)      # ~= 156 Ig

  # Среднее квадратическое отлконение
  data["Catholic_StandardDeviation"] = sd(data$Catholic)        # ~= 42 %
  data["Examination_StandardDeviation"] = sd(data$Examination)  # ~= 8 %
  data["Fertility_StandardDeviation"] = sd(data$Fertility)      # ~= 12.5 Ig

  # Проверяю линейную зависимость
  
  model0 = lm(Fertility~Examination, data)
  summary(model0)
  
#2. Строю зависимости вида y = a + bx, где y – Catholic, x – Fertility, Examination (регрессоры).
  
  #2.1 Примерная линейная зависимость католоического населения от рождаемости
  
  model1 = lm(Catholic~Fertility, data)
  summary(model1)
  
  # Catholic = - 67.441 + 1.548 * Fertility
  
  #2.2 Примерная линейная зависимость католоического населения от отлично сдавших экзамены призывников

  model2 = lm(Catholic~Examination, data)
  summary(model2)
  
  # Catholic = 90.5137 - 2.9940 * Examination
  
#3. Оцениваю, насколько «хороша» модель по коэффициенту детерминации R^2
  
  #3.1 коэффициент детерминации R^2 < 20%
  # Значит модель "плоха" и линейной зависимости нет
  
  plot(data$Catholic,data$Fertility) + abline(a = -67.441, b = 1.548,col = "red")
  
  #3.2 коэффициент детерминации R^2 ~= 30%
  # Значит модель "средняя" и линейная зависимость минимальна
  
  plot(data$Catholic,data$Examination) + abline(a = 90.5137, b = -2.9940,col = "blue")
  
#4. Оцениваю, есть ли взаимосвязь между объясняемой переменной и объясняющей переменной (по значению p-статистики, «количеству звездочек» у регрессора в модели).
  
  #4.1 кол-во звёздочек 2, линейной зависимости католоического населения от экзаминации призывников нет ( p-вероятность: ~ 10^(-3) )
  # Процент католического населения в Французско-говорящих провинциях Швейцарии в 1888 году почти не зависит от рождаемости
  
  #4.2 кол-во звёздочек 3, линейная зависимость присутсвует ( p-вероятность: < 10^(-4) )
  # Процент католического населения имеет слабую отрицательную линейную зависимость от образованности, это может быть связанно с тем что, среди отлично сдавших экзамены призывников мало католиков
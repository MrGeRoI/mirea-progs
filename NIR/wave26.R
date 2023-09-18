install.packages("devtools")
devtools::install_github("bdemeshev/rlms")
install.packages("foreign")

library("lmtest")
library("rlms")
library("dplyr")
library("GGally")
library(car)
library(sandwich)

#r15i_os26c <- rlms_read("r15i_os26c.sav")
r15i_os26c <- read.csv("r15i_os26c.csv")
glimpse(r15i_os26c)

data = select(r15i_os26c,
              # Минимальный набор параметров:
              
              kj13.2,  #зарплата
              k_age,   #возраст
              kh5,     #пол
              k_educ,  #образование
              status,  #тип населённого пункта
              kj6.2,   #длительность рабочей недели
              k_marst, #семейное положение
              ki3,     #Вы родились в городе, поселке городского типа или в селе, деревне, кишлаке, ауле?
              
              #Расширеный набор параметров:
              
              kj1.1.2, # Насколько Вы удовлетворены или не удовлетворены условиями Вашего труда?
              kj32.1,  # Возможно, у Вас есть еще работа по совместительству, временная работа по срочномуконтракту, трудовому соглашению, договору подряда, гранту, или индивидуальная работа по лицензии или без нее? 
              kj23,    # Является государство владельцем или совладельцем Вашего предприятия, организации? 
              kj24,    #вляются владельцами или совладельцами Вашего предприятия, организации иностранные фирмы или иностранные частные лица?
              kj6,      #У Вас есть подчиненные на этой работе?
              kj66.1   #Насколько Вы удовлетворены своим материальным положением в настоящее время?
              )

# Отсеивание неадекватных значений
data$kj13.2[which(data$kj13.2>99999990)] <- NA
data$kj6.2[which(data$kj6.2>99999990)] <- NA
data$kj1.1.2[which(data$kj1.1.2>99999990)] <- NA
data = na.omit(data)

# Нормализация данных

  # Семейное положение
    
    #1) переменная wed1 имеет значение 1 в случае, если респондент женат, 0 – в противном случае
    data$wed1 = data$k_marst
    data$wed1 = 0                             # По умолчанию
    data$wed1[which(data$k_marst=='1')] <- 1
    data$wed1[which(data$k_marst=='6')] <- 1
    data$wed1 = as.numeric(data$wed1)
    
    #2) wed2 = 1, если респондент разведён или вдовец
    data$wed2 = data$k_marst
    data$wed2 = 0                          # По умолчанию
    data$wed2[which(data$k_marst=='2')] <- 1  # Респондент разведён
    data$wed2[which(data$k_marst=='3')] <- 1  # Респондент - вдовец
    data$wed2 = as.numeric(data$wed2)

    #3) wed3 = 1, если респондент никогда не состоял в браке
    data$wed3 = data$k_marst
    data$wed3 = 0                          # По умолчанию
    data$wed3[which(data$k_marst=='4')] <- 1  # Респондент никогда не состоял в браке
    data$wed3 = as.numeric(data$wed3)

    model_wed = lm(kj13.2~wed1+wed2+wed3,data)
    summary(model_wed)
    # По коэффиценту вздутия дисперсии, видно что линейной зависимости между регрессорами нет
    vif(model_wed)
    #    wed1     wed2     wed3 
    # 2.397190 3.340558 2.284804 
    
  #Пол
  data$sex = data$kh5
  data$sex[which(data$kh5=='2')] <- 0 # Женщина
  data$sex[which(data$kh5=='1')] <- 1 # Мужчина
  data$sex = as.numeric(data$sex)

  #Удовлетворённость условиями труда
  data$satisfy = data$kj1.1.2
  data$satisfy = 0
  data$satisfy[which(data$kj1.1.2=='1')] <- 1
  data$satisfy[which(data$kj1.1.2=='2')] <- 1
  data$satisfy = as.numeric(data$satisfy)
  
  #Удовлетворённость материальным положением
  data$situation = data$kj66.1
  data$situation = 0
  data$situation[which(data$kj66.1=='1')] <- 1
  data$situation[which(data$kj66.1=='2')] <- 1
  data$situation = as.numeric(data$situation)

  #Тип населённого пункта
  data$city_status = data$status
  data$city_status = 0
  data$city_status[which(data$status=='1')] <- 1
  data$city_status[which(data$status=='2')] <- 1
  data$city_status = as.numeric(data$city_status)
  
  #наличие полного высшего образования
  data$higher_educ = data$k_educ
  data$higher_educ = 0                            # По умолчанию
  data$higher_educ[which(data$k_educ=='21')] <- 1 # Есть диплом о высшем образовании
  data$higher_educ[which(data$k_educ=='22')] <- 1 # Аспирантура и т.п. без диплома
  data$higher_educ[which(data$k_educ=='23')] <- 1 # Аспирантура и т.п. с дипломом
  
  #Наличие подчинённых
  data$subordinates = data$kj6
  data$subordinates = 0
  data$subordinates[which(data$kj6=='1')] <- 1
  data$subordinates = as.numeric(data$subordinates)

  #Вторая работа
  data$second_job = data$kj32.1
  data$second_job = 0
  data$second_job[which(data$kj32.1=='1')] <- 1
  data$second_job = as.numeric(data$second_job)

  #Иностранная компания
  data$foreign_owner = data$kj24
  data$foreign_owner = 0
  data$foreign_owner[which(data$kj24=='1')] <- 1
  data$foreign_owner = as.numeric(data$foreign_owner)

  #Государственная организация
  data$state_owner = data$kj23
  data$state_owner = 0
  data$state_owner[which(data$kj23=='1')] <- 1
  data$state_owner = as.numeric(data$state_owner)
  
  #Зарплата
  salary = data$kj13.2
  mean(salary)
  data$salary = (salary - mean(salary)) / sqrt(var(salary))
 
  #Возраст
  age = data$k_age
  mean(age)
  data$age = (age - mean(age)) / sqrt(var(age))
  
  #Длительность рабочей недели
  duration = data$kj6.2
  mean(duration)
  data$duration = (duration - mean(duration)) / sqrt(var(duration))
  
#1. Постройте линейную регрессию зарплаты на все параметры, которые Вы выделили
#   из данных мониторинга. Не забудьте оценить коэффициент вздутия дисперсии VIF.
  model11 = lm(data = data,salary~
              wed1+wed2+wed3+
              age+
              sex+
              duration+
              satisfy+
              city_status+
              higher_educ+
              state_owner+
              foreign_owner+
              second_job+
              subordinates+
              situation
             )
  
  summary(model11)
  # Итого модель:
  #
  # model11: salary = - 0.7 - 0.13 * wed1 + 0.07 * wed2 + 0.22 * wed3 - 0.12 * age + 0.34 * sex + 0.1 * duration + 0.3 * satisfy + 0.32 * city_status +
  # + 0.4 * higher_educ - 0.24 * state_owner + 0.46 * foreign_owner + 0.42 * second_job + 0.4 * subordinates + 0.39 * actual
  #
  # R^2 ~= 30.71%, p-вероятность < 10^(-15)
  
  # vif характеристика модели model1 имеет плохие показатели для wed1, wed2 и wed3
  vif(model11)
  
  # second_job, wed1 и wed2 имеют малую значимость (нет звёздочек), так что исключаю их из модели
  model12 = lm(data = data,salary~
                 wed3+
                 age+
                 sex+
                 duration+
                 satisfy+
                 city_status+
                 higher_educ+
                 state_owner+
                 foreign_owner+
                 subordinates+
                 situation
  )
  
  summary(model12)
  # В модели model12 исключены лишние регрессоры
  # Замечаю, что у wed3 теперь больше значимость (** )
  # R^2 ~= 30.45%, p-вероятность < 10^(-15)
  
  # vif характеристика модели model12 имеет хорошие показатели (< 1.15)
  vif(model12)
  
  #2. Поэкспериментируйте с функциями вещественных параметров: используйте
  # логарифмы, степени (хотя бы от 0.1 до 2 с шагом 0.1), произведения вещественных
  # регрессоров
  
  # Логарифмы вещественных регрессооров:

    model21 = lm(data = data,salary~wed3+sex+satisfy+city_status+higher_educ+state_owner+foreign_owner+subordinates+situation+
                 age+log(duration + 5)) # R^2 ~= 30.58%
   
    model22 = lm(data = data,salary~wed3+sex+satisfy+city_status+higher_educ+state_owner+foreign_owner+subordinates+situation+
                 log(age + 5)+duration) # R^2 ~= 30.23%
      
    model23 = lm(data = data,salary~wed3+sex+satisfy+city_status+higher_educ+state_owner+foreign_owner+subordinates+situation+
                   log(age + 5)+log(duration + 5)) # R^2 ~= 30.21%
      
    summary(model21)
    summary(model22)
    summary(model23)
    
    vif(model21)
    vif(model22)
    vif(model23)
    
    # Модели model21, model22 и model23 имеет невысокие показатели R^2, меньше чем у model12, так что возвращаюсь к модели model12
    # vif характеристика этих моделей имеет хорошие показатели (< 1.25)
    
  # Произведения вещественных регрессоров:
      summary(lm(data = data,I(age*duration)~age))      # (*  )
      summary(lm(data = data,I(age*duration)~duration)) # (***)
      
      # Произведение age*duration зависит от duration, но не сильно зависит от age, так что
      #   проверяю варианты с заменой на duration с регрессором age и без него:
      
      model31 = lm(data = data,salary~wed3+sex+satisfy+city_status+higher_educ+state_owner+foreign_owner+subordinates+situation+
                     I(age*duration)) # R^2 ~= 27.7%
      
      model32 = lm(data = data,salary~wed3+sex+satisfy+city_status+higher_educ+state_owner+foreign_owner+subordinates+situation+
                   age+I(age*duration)) # R^2 ~= 29.5%
      
      summary(model31)
      summary(model32)
      
      vif(model31)
      vif(model32)
      
      # Модели model31, model32 имеет невысокие показатели R^2, меньше чем у model12, так что остаюсь с моделью model12
      # vif характеристика этих моделей имеет хорошие показатели (< 1.25)
      
  # Степени вещественных регрессоров:
      
    # Набор значений R^2 моделей вида:
    # salary = age ^ n + duration ^ m + ...
    models4 <- data.frame(n = numeric(),m = numeric(),R = numeric())

    # Перебираю показатели степеней n,m от 0.1 до 2 с шагом 0.1:
    for (n in seq(0.1, 2, by=0.1))
      for (m in seq(0.1, 2, by=0.1))
      {
        models4[nrow(models4)+1,] = c(n=n,m=m,R=
          summary(lm(data = data,salary~wed3+sex+satisfy+city_status+higher_educ+state_owner+foreign_owner+subordinates+situation+
            I((age+5)^n)+I((duration+5)^m)))$adj.r.squared)
      }
    
    # Сортирую наборы степеней по убыванию R^2 соотвествующей модели
    models4[order(-models4$R), ]
    
    #Итого лучший набор степеней переменных: n = 2.0, m = 0.9
    # salary = age ^ 2 + duration ^ 0.9 + ...
  
    # Заменяю вещественные регрессоры на их степени:    
    model41 = lm(data = data,salary~wed3+sex+satisfy+city_status+higher_educ+state_owner+foreign_owner+subordinates+situation+
                I((age+5)^2)+I((duration+5)^0.9))

    summary(model41)

  # Итого модель model41 оказалась лучше:
  # model41: -0.95 - 0.014 * (age + 5) ^ 2 + 0.14 * (duration + 5) ^ 0.9 + ... , где далее идут дамми-переменные
  # R^2 ~= 30.79%, p-вероятность < 10^(-15)
  vif(model41)
  # vif характеристика модели model41 имеет хорошие показатели (< 1.15)
  
  # Рассмотрим эту модель со всеми регрессорами
  model42 = lm(data = data,salary~wed1+wed2+second_job+wed3+sex+satisfy+city_status+higher_educ+state_owner+foreign_owner+subordinates+situation+
                 I((age+5)^2)+I((duration+5)^0.9))
  
  summary(model42)
  vif(model42)
  # R^2 ~= 31.03%, p-вероятность < 10^(-15)
  # vif характеристика модели model42 имеет плохие значения (> 3.0)
  # Если учитывать все переменные, то R^2 будет больше чем у model42: 31.0% > 30.8%
  
#3. Выделите наилучшие модели из построенных: по значимости параметров,
# включённых в зависимости, и по объяснённому с помощью построенных
# зависимостей разбросу adjusted R^2
    
    # Наилучшая модель и по значимости параметров:
    # model41: salary = -0.95 - 0.014 * (age + 5) ^ 2 + 0.14 * (duration + 5) ^ 0.9 + 
    # R^2 ~= 30.8%, p-вероятность < 10^(-15)
    # У всех параметров высокая значимость (***), кроме wed3 (** )

    # А по разбросу R^2 лушая модель это model42
    # R^2 ~= 31.03%, p-вероятность < 10^(-15)
    # Она не сильно нас интересует, так как R^2 возрастает не значительно
    
#4. Сделайте вывод о том, какие индивиды получают наибольшую зарплату.
    
    # Рассматриваю model41, где значимость параметров достаточная, так как нам нужно анализировать их влияние на обьясняемую переменную
    # Коэффециенты при параметрах:
   
    # Значительное влияние
      #state_owner			    -0.235044	(***) < 0
      #satisfy			        0.308710	(***) > 0
      #city_status			    0.308989	(***) > 0
      #situation			      0.387964	(***) > 0
      #subordinates			    0.398010	(***) > 0
      #sex			            0.407649	(***) > 0
      #higher_educ			    0.415693	(***) > 0
      #foreign_owner			  0.433168	(***) > 0
      
    # Из этих данных видно, что наибольшую зарплату получают мужчины с высшим образованием, проживающие в городах.
    # Их работа - в иностранных негосударственных компаниях и они там имеют подчинённых.
    # Тем самым они удовлетворены своими условиями работой и достатком.
    
    
    # Слабое влияние (Коэффециенты малые по модулю)
      #I((age+5)^2)	        -0.013818	(***) <~ 0
      #I((duration+5)^0.9)	0.135074	(***) >~ 0 
      #wed3			            0.181463	(** ) >~ 0
    
    # Из менее значимых параметров, можно предположить, что:
    # Вероятно, что индивиды с наибольшей зарплатой немолоды и никогда не состояли в браке (наверное занимались бизнесом а не партнёрами)
    # И, что очевидно, они работают дольше в течении недели.
    
#5. Оцените лучшие модели для подмножества индивидов, указанных в варианте.
#   Сделайте вывод о том, какие индивиды получают наибольшую зарплату.
  
  #Женатые, не из города:
    subdata1 = subset(data,wed1 == 1 & city_status == 1)
    
    # Убираю уже заранее отобранные параметры wed и city_status:
    submodel1 = lm(data = subdata1,salary~sex+satisfy+higher_educ+state_owner+foreign_owner+subordinates+situation+
                   I((age+5)^2)+I((duration+5)^0.9))
    
    summary(submodel1)
    vif(submodel1)
    # Модель довольно плоха, почти нет значимых переменных и по ней не сделать особых выводов
    # R^2 ~= 18.03%, p-вероятность < 10^(-4)
    # vif характеристика модели submodel1 имеет неплохие показатели (< 1.3)

  #Разведённые или не вступавшие в брак, с высшим образованием:
    subdata2 = subset(data,(wed2 == 1 | wed3 == 1) & higher_educ == 1)
    
    # Убираю уже заранее отобранные параметры wed и higher_educ:
    submodel2 = lm(data = subdata2,salary~sex+satisfy+city_status+state_owner+foreign_owner+subordinates+situation+
                     I((age+5)^2)+I((duration+5)^0.9))
    
    summary(submodel2)
    vif(submodel2)
    # Модель неплохая, с такой уже можно анализировать коэффициенты параметров
    # R^2 ~= 29%, p-вероятность < 10^(-15)
    # vif характеристика модели submodel2 имеет хорошие показатели (< 1.25)
    
    # Отбрасываю незначительные регрессоры:
    submodel3 = lm(data = subdata2,salary~sex+satisfy+city_status+state_owner+subordinates+situation+
                     I((age+5)^2))
    
    summary(submodel3)
    vif(submodel3)
    # Модель неплохая, с такой уже можно анализировать коэффициенты параметров
    # R^2 ~= 28.8%, p-вероятность < 10^(-15)
    # vif характеристика модели submodel3 имеет хорошие показатели (< 1.15)

    # Коэффиценты:
      #sex		      0.283488	(*  )
      #satisfy			0.256690	(*  )
      #situation		0.414736	(** )
      #I((age+5)^2)	-0.017106	(** )
      #city_status	0.488934	(***)
      #state_owner	-0.700860	(***)
      #subordinates	0.650319	(***)
      
    # Разведённые или невступавшие в брак люди с высшим образованием имеют наибольшую зарплату,
    # если они живут в городе, имеют подчинённых на своей негосударственной работе.
    # Большинство из них будут мужчины в возрасте

    


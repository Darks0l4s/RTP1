# RTP1
Справочные данные
MAC адрес машинки 10:06:1C:41:9F:18
Mac адрес манипулятора A0:A3:B3:2B:EC:64
Команды:
	send - отправить данные
	x=int - передвинуть на координате x
	y=int - передвинуть на координате y
	w=int - повернуть на w
	fast - активация быстрого режима 
	slow - выключение быстрого режима, нужно писать send
#define MottorA1 32 //левое заднее, HIGH вперёд
#define MottorB1 33 

#define MottorA2 25 //левое переднее, HIGH вперёд
#define MottorB2 26

#define MottorA3 13 //правое заднее, HIGH вперёд
#define MottorB3 12

#define MottorA4 17 //правое переднее, HIGH вперёд
#define MottorB4 16
#include <IRremote.h>
int key=7;//设置LED的数字IO脚
IRsend irsend;

void setup()
{
  pinMode(key,OUTPUT);//设置数字IO引脚为输出模式
}
void loop()
{
  int i;//定义变量
  while(1)
  {
    i=analogRead(5);//读取模拟5口电压值
    if(i>1000)//如果电压值大于1000（即4.88V）
      {
        irsend.sendNEC(0x00FDB04F, 32);//开始发送开机信号开机
     
      digitalWrite(key,HIGH);//设置第七引脚为高电平，点亮led灯
      }
    else
      {
        irsend.sendNEC(0x00FDB04F, 32);//开始发送开机信号开机
      
      digitalWrite(key,LOW);//设置第七引脚为低电平，熄灭led灯
      }
  }
}

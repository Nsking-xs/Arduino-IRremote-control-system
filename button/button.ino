#include <IRremote.h>
int key=7;//����LED������IO��
IRsend irsend;

void setup()
{
  pinMode(key,OUTPUT);//��������IO����Ϊ���ģʽ
}
void loop()
{
  int i;//�������
  while(1)
  {
    i=analogRead(5);//��ȡģ��5�ڵ�ѹֵ
    if(i>1000)//�����ѹֵ����1000����4.88V��
      {
        irsend.sendNEC(0x00FDB04F, 32);//��ʼ���Ϳ����źſ���
     
      digitalWrite(key,HIGH);//���õ�������Ϊ�ߵ�ƽ������led��
      }
    else
      {
        irsend.sendNEC(0x00FDB04F, 32);//��ʼ���Ϳ����źſ���
      
      digitalWrite(key,LOW);//���õ�������Ϊ�͵�ƽ��Ϩ��led��
      }
  }
}

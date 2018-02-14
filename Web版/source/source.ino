#include <boarddefs.h>
#include <IRremote.h>
#include <IRremoteInt.h>
#include <ir_Lego_PF_BitStreamEncoder.h>
#include <SPI.h>
#include <Ethernet.h>


byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
EthernetServer server(80);
EthernetClient client;
String POST = "";
IRsend irsend;

void setup() {
	Serial.begin(9600);
	//��ʼ������
	Ethernet.begin(mac);
	server.begin();
	Serial.print("Server is at ");
	Serial.println(Ethernet.localIP());
}

void loop() {
	// ��������Ŀͻ���
	client = server.available();
	SendHTML();
	if (client) {
		Serial.println("new client");
		boolean currentLineIsBlank = false;
		while (client.connected()) {
			if (client.available()) {
				char c = client.read();
				POST += c;
				if (c == "\n") {
					Serial.println(POST);
					//����յ�����Ϣ���Ƿ��С�on���������Ϳ����ź�
					if (POST.indexOf("?on") > 0) {
						irsend.sendNEC(0x00FDB04F, 32);
						Serial.println("send On");
						break;
						//����HTML�ı�
						SendHTML();
					}
				}
			}
		}
		delay(1);
		client.stop();
		Serial.println("client disonnected");
		POST = "";
	}
}

// �������HTML�ı��ĺ���
void SendHTML()
{
	client.println("HTTP/1.1 200 OK");
	client.println("Content-Type: text/html");
	client.println("Connection: close");
	client.println();
	client.println("<!DOCTYPE HTML>");
	client.println("<html><head><meta charset=\"UTF-8\"><title>OpenJumper!Arduino Web Server</title>");
	client.println("</head><body><div align=\"center\"><h1>Arduino Web Server</h1><div>brightness:</div><div id=\"brightness\">");
	client.println("</div><form action=\"\" method=\"post\"><label>�����룺</label><input type=\"text\" placeholder=\"on\"><input type=\"submit\" value=\"�ύ\"></form></div></body></html>");
}


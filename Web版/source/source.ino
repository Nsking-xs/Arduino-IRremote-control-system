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
	//初始化串口
	Ethernet.begin(mac);
	server.begin();
	Serial.print("Server is at ");
	Serial.println(Ethernet.localIP());
}

void loop() {
	// 监听连入的客户端
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
					//检查收到的信息中是否有”on”，有则发送开机信号
					if (POST.indexOf("?on") > 0) {
						irsend.sendNEC(0x00FDB04F, 32);
						Serial.println("send On");
						break;
						//发送HTML文本
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

// 用于输出HTML文本的函数
void SendHTML()
{
	client.println("HTTP/1.1 200 OK");
	client.println("Content-Type: text/html");
	client.println("Connection: close");
	client.println();
	client.println("<!DOCTYPE HTML>");
	client.println("<html><head><meta charset=\"UTF-8\"><title>OpenJumper!Arduino Web Server</title>");
	client.println("</head><body><div align=\"center\"><h1>Arduino Web Server</h1><div>brightness:</div><div id=\"brightness\">");
	client.println("</div><form action=\"\" method=\"post\"><label>请输入：</label><input type=\"text\" placeholder=\"on\"><input type=\"submit\" value=\"提交\"></form></div></body></html>");
}


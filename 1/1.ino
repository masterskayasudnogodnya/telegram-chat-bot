#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#define WIFI_SSID "SSID"
#define WIFI_PASSWORD "PASSWORD"
#define BOT_TOKEN "HTTP API"

const unsigned long BOT_MTBS = 50;
const int ledPin = LED_BUILTIN;

X509List cert(TELEGRAM_CERTIFICATE_ROOT);
WiFiClientSecure secured_client;
UniversalTelegramBot bot(BOT_TOKEN, secured_client);
unsigned long bot_lasttime;
int ledStatus = 0;

void handleNewMessages(int numNewMessages)
{
	Serial.println("handleNewMessages");
	Serial.println(String(numNewMessages));

	for (int i = 0; i < numNewMessages; i++)
	{
		String chat_id = bot.messages[i].chat_id;
		String text = bot.messages[i].text;
		String from_name = bot.messages[i].from_name;
		
		if(from_name == "")from_name = "Guest";

		if(text == "/программирование")
		{
			String keyboardJson = "[[\"/Python\", \"/C или C++\"],[\"/HTML\"]]";
			bot.sendMessageWithReplyKeyboard(chat_id, "В какой среде программирования ты хочешь работать?", "", keyboardJson, true);
			continue;

	}
if(text == "/Python"){
  bot.sendMessage(chat_id, "начинаю поиск команды, нуждающейся в Python разработчике...", "");
  }
if(text == "/C или C++"){
  bot.sendMessage(chat_id, "начинаю поиск команды, нуждающейся в C или C++ разработчике...", "");
  }
if(text == "/HTML"){
  bot.sendMessage(chat_id, "начинаю поиск команды, нуждающейся в HTML разработчике...", "");
  }
    if (text == "/дизайн"){
	String keyboardJson = "[[\"/Paint 3D\", \"/Photoshop\"],[\"/Canva\"]]";
	bot.sendMessageWithReplyKeyboard(chat_id, "В какой программе ты хочешь работать?", "", keyboardJson, true);
  }
if (text == "/Photoshop"){
  bot.sendMessage(chat_id, "ишу команду, нуждающуюся в Photoshop-дизайнере...", "");
  }
if (text == "/Paint 3D"){
  bot.sendMessage(chat_id, "ишу команду, нуждающуюся в Paint 3D-дизайнере...", "");
  }
 if (text == "/Canva"){
  bot.sendMessage(chat_id, "ишу команду, нуждающуюся в Canva-дизайнере...", "");
 }
    if (text == "/3D дизайн"){
	String keyboardJson = "[[\"/Fusion 360\", \"/Компас 3D\"],[\"/Blender\"]]";
	bot.sendMessageWithReplyKeyboard(chat_id, "В какой программе ты хочешь зоздавать 3D модели?", "", keyboardJson, true); 
}
if (text == "/Fusion 360"){
  bot.sendMessage(chat_id, "ишу команду, в которой нужен Fusion-360 3D-дизайнер...", "");
  }
if (text == "/Компас 3D"){
  bot.sendMessage(chat_id, "ишу команнду, в которой нужен Компас 3D-дизайнер...", "");
  }
 if (text == "/Blender"){
  bot.sendMessage(chat_id, "ишу команду, в которой нужен 3D-дизайнер...", "");
 }
    if (text == "/маркетолог"){
  bot.sendMessage(chat_id, "ишу команду, нуждающуюся в маркетологе...", ""); 
    }
     if (text == "/экономист"){
  bot.sendMessage(chat_id, "ишу команду, нуждающуюся в экономисте...", ""); 
    }
    if (text == "/логист"){
  bot.sendMessage(chat_id, "ишу команду, нуждающуюся в логисте...", ""); 
    }
		if (text == "/platforms")
		{
		  String keyboardJson = "[[\"/программирование\"], [\"/дизайн\"],[\"/3D дизайн\",] [\"/маркетолог\"], [\"/экономист\"], [\"/логист\"]]";
			bot.sendMessageWithReplyKeyboard(chat_id, "Выберите направление", "", keyboardJson, true);
			String welcome;
			continue;
		}

		if (text == "/start")
		{
			String welcome = "привет, " + from_name +  ", я - бот Аркадий, который поможет подобрать тебе команду в соответствии с твоими умениями и интересами  " +  + ".\n";
			bot.sendMessage (chat_id, "привет, " + from_name +  ", я - бот Аркадий, который поможет подобрать команду в соответствии с твоими умениями и интересами  " +  + ".\n");
			bot.sendMessage(chat_id, "сколько тебе лет?", "");
			continue;
		}

		for (int i = 0; i < numNewMessages; i++)
		{
			String chat_id = bot.messages[i].chat_id;
			String text = bot.messages[i].text;
			int ic = text.toInt();
			Serial.println(ic);
			if (ic > 99)
			{
				bot.sendMessage(chat_id, "не правильное значение, введи свой настоящий возраст"); 
			}
			else
			{
				String keyboardJson = "[[\"/программирование\", \"/дизайн\"],[\"/3D дизайн\"],[\"/логист\", \"/экономист\"],[\"/маркетолог\"]]";
				bot.sendMessageWithReplyKeyboard(chat_id, "Выберите направление", "", keyboardJson, true);
			}
		}
	}
}
//----------------------------------------------------------------------------------------
void setup()
{
	Serial.begin(115200);
	Serial.println();
	configTime(0, 0, "pool.ntp.org");      // get UTC time via NTP
	secured_client.setTrustAnchors(&cert); // Add root certificate for api.telegram.org
	// attempt to connect to Wifi network:
	Serial.print("Connecting to Wifi SSID ");
	Serial.print(WIFI_SSID);
	WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
	while (WiFi.status() != WL_CONNECTED)
	{
		Serial.print(".");
		delay(500);
	}
	Serial.print("\nWiFi connected. IP address: ");
	Serial.println(WiFi.localIP());

// Check NTP/Time, usually it is instantaneous and you can delete the code below.
	Serial.print("Retrieving time: ");
	time_t now = time(nullptr);
	while (now < 24 * 3600)
	{
		Serial.print(".");
		delay(100);
		now = time(nullptr);
	}
	Serial.println(now);
	
	pinMode(ledPin, OUTPUT); // initialize digital ledPin as an output.
	delay(10);
	digitalWrite(ledPin, HIGH); // initialize pin as off
 
}
//-------------------------------------------------------------------------
void loop()
{
	if (millis() - bot_lasttime > BOT_MTBS)
	{
		int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

		while (numNewMessages)
		{
			Serial.println("got response");
			handleNewMessages(numNewMessages);
			numNewMessages = bot.getUpdates(bot.last_message_received + 1);
		}

		bot_lasttime = millis();
	}
}

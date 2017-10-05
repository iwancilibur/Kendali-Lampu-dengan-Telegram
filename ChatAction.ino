/*******************************************************************
*  An example of bot that show bot action message.                *
*                                                                 *
*                                                                 *
*                                                                 *
*  written by Vadim Sinitski                                      *
 *******************************************************************/
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

// Initialize Wifi connection to the router
char ssid[] = "interactive robotics";     // your network SSID (name)
char password[] = "cilibur2017"; // your network key

// Initialize Telegram BOT
#define BOTtoken "430781965:AAEeqG9e2w-JN5Oy9jVyO2z-3TMbY9BLAxM"  // your Bot Token (Get from Botfather)

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

int Bot_mtbs = 100; //mean time between scan messages
long Bot_lasttime;   //last time messages' scan has been done
bool Start = false;

void handleNewMessages(int numNewMessages) {
  Serial.println("handleNewMessages");
  Serial.println(String(numNewMessages));

  for (int i=0; i<numNewMessages; i++) {
    String chat_id = String(bot.messages[i].chat_id);
    String text = bot.messages[i].text;

    String from_name = bot.messages[i].from_name;
    if (from_name == "") from_name = "Guest";

    if (text == "Halo") {
        bot.sendChatAction(chat_id, "Typing");
        delay(10);
        bot.sendMessage(chat_id, "Halo Juga, Ayul Bot Siap menerima perintah dari anda!");

        // You can't use own message, just choose from one of bellow

        //typing for text messages
        //upload_photo for photos
        //record_video or upload_video for videos
        //record_audio or upload_audio for audio files
        //upload_document for general files
        //find_location for location data

        //more info here - https://core.telegram.org/bots/api#sendchataction
    }

    if (text == "/start") {
      String welcome = "Selamat Datang di Ayul Bot, Hallo " + from_name + ".\n";
      welcome += "Chat ini dibalas otomatis Loh oleh Ayul Bot\n\n";
      welcome += "Halo : untuk menyapa\n";
      welcome += "Nyalakanlampu1 : untuk menyalakan lampu 1\n";
      welcome += "Silahkan di Add yaa @AyuLBOT nya\n";
      bot.sendMessage(chat_id, welcome);
    }

    if (text == "Nyalakan lampu 1") {
      bot.sendChatAction(chat_id, "Typing");
      delay(10);
      String Lampu1 = "Lampu satu telah dinyalakan";
      bot.sendMessage(chat_id, Lampu1);
    }

    if (text == "Matikan lampu 1") {
      bot.sendChatAction(chat_id, "Typing");
      delay(10);
      String Lampu1 = "Lampu satu telah dimatikan";
      bot.sendMessage(chat_id, Lampu1);
    }

    if (text == "Sayang") {
      bot.sendChatAction(chat_id, "Typing");
      delay(10);
      String Lampu1 = "iyah sayang, kenapa ?";
      bot.sendMessage(chat_id, Lampu1);
    }

    if (text == "Hari ini kita kemana") {
      bot.sendChatAction(chat_id, "Typing");
      delay(10);
      String Lampu1 = "katanya kamu lagi ngoprek, lanjutin aja gih !";
      bot.sendMessage(chat_id, Lampu1);
    } 
    if (text == "Wxwxwx") {
      bot.sendChatAction(chat_id, "Typing");
      delay(10);
      String Lampu1 = "Bodo Amat ! ^_^";
      bot.sendMessage(chat_id, Lampu1);
    }
    
  }
}


void setup() {
  Serial.begin(9600);

  // Set WiFi to station mode and disconnect from an AP if it was Previously
  // connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  // attempt to connect to Wifi network:
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  if (millis() > Bot_lasttime + Bot_mtbs)  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    while(numNewMessages) {
      Serial.println("got response");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }

    Bot_lasttime = millis();
  }
}

#include <ESP8266WiFi.h>
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>

// WiFi 정보 설정
const char *ssid = "your_wifi_ssid";
const char *password = "your_wifi_password";

// AWS RDS MySQL 서버 정보 설정
char host[] = "jongsul.cumkjf8xpcah.ap-northeast-2.rds.amazonaws.com"; // AWS RDS 엔드포인트
char user[] = "imhyuk98";
char password[] = "limjaehyuk98";
char db[] = "jongsul";

// 초음파 센서 핀 설정
const int trigPin = D2; // 초음파 센서 Trig 핀
const int echoPin = D3; // 초음파 센서 Echo 핀

void setup()
{
  Serial.begin(115200);

  // WiFi 연결
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(250);
    Serial.print('.');
  }
  Serial.println();
  Serial.println("WiFi connected");
}

void loop()
{
  long duration, distance;

  // (초음파 센서에서 거리를 읽어오는 코드)

  // MySQL 서버 연결
  MySQL_Connection conn((Client *)&Serial);
  if (conn.connect(host, 3306, user, password, db))
  {
    Serial.println("Connected to MySQL server");

    MySQL_Cursor *cursor = new MySQL_Cursor(&conn);

    // 거리 값을 MySQL 데이터베이스에 삽입
    char query[256];
    sprintf(query, "INSERT INTO park (area_1, area_2, area_3, area_4) VALUES ('%ld', 'empty', 'empty', 'empty')",
            distance);
    cursor->execute(query);

    delete cursor;
    conn.close();
  }
  else
  {
    Serial.println("Connection failed");
  }

  delay(1000); // 1초마다 반복
}
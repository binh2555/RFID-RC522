#include <SPI.h>
#include <string.h>
#include <util.h>
#include <deprecated.h>
#include <MFRC522.h>
#include <MFRC522Extended.h>
#include <require_cpp11.h>

#define RST_PIN         5
#define SS_PIN          53


typedef struct ttcar{
  String uid;
  int statuss;
  int vitri;
}xe;

xe plc[30];

void f_setup_1(void)
{
  plc[0].uid = "351498622";
  plc[0].statuss = 0;
  plc[0].vitri = 0;

  plc[1].uid = "10210418141";
  plc[1].statuss = 0;
  plc[1].vitri = 0;

  plc[2].uid = "1821106133";
  plc[2].statuss = 0;
  plc[2].vitri = 0;

  plc[3].uid = "18213525433";
  plc[3].statuss = 0;
  plc[3].vitri = 0;

  plc[4].uid = "181197575";
  plc[4].statuss = 0;
  plc[4].vitri = 0;

  plc[5].uid = "197341145";
  plc[5].statuss = 0;
  plc[5].vitri = 0;

  plc[6].uid = "181229385";
  plc[6].statuss = 0;
  plc[6].vitri = 0;
}
 int cnte = 0;
int UID[4], i ,j;
unsigned long uid1=0;

int _max = 6;//bien the hien so luong uid cua xe da dang ki trong database,so luong xe bang _max + 1

String database_uid[30];
int mang_guixe[30];
byte status_uid[30];


MFRC522 mfrc522(SS_PIN, RST_PIN);


 //doan nay dell biet quen con mia no roi
void gan_gia_tri_vao_database()
{
  database_uid[0] = "10210418141";
  database_uid[1] = "351498622";
  database_uid[2] = "1821106133";
  database_uid[3] = "18213525433";
  database_uid[4] = "181197575";
  database_uid[5] = "197341145";
  database_uid[6] = "181229385";
}
//end cua doan dell biet


void setup() 
{
  
    Serial.begin(9600);

    f_setup_1();
     
    digitalWrite(8,HIGH);
    digitalWrite(9,HIGH);    
    pinMode(8,OUTPUT);
    pinMode(9,OUTPUT);
    
    SPI.begin();    
    mfrc522.PCD_Init();

    gan_gia_tri_vao_database();

}

void _menu()
{
  Serial.println("   ");
  Serial.println("===HE THONG GUI XE TU DONG XIN KINH CHAO QUY KHACH====");
  Serial.println("===LUA CHON 1 : GUI XE");
  Serial.println("===LUA CHON 2 : LAY XE");
}


void loop() 
{
  if(cnte > 1000)
  {
    cnte = 0;
  }
  else cnte++;
   Serial.println(cnte);
  //tim the moi
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  { 
    return; 
  }
 
  //doc the
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {  
    
    return;  
  }
 
  Serial.print("UID của thẻ: ");   
  
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  { 
    //Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
       
    UID[i] = mfrc522.uid.uidByte[i];
    
    Serial.print(UID[i]); 
  }
 
  //=====BEGIN : chuyen uid quet duoc thanh String
  uid1 = 0;
  String total="";
  for(j=0;j<mfrc522.uid.size;j++)
  { 
    int sp = UID[j];
    String ol = String(sp);
    total += ol;
  }
  Serial.println("   ");
  Serial.println(total);
  //=====END========================================

  for(int i=0;i<=_max;i++)
  {
    if(total == plc[i].uid)
    {
      Serial.println("uay cai cmm no");
      if(plc[i].statuss == 0)
      {
        plc[i].statuss = 1;
        for(int j = 1;j < 30;j++)
        {
          if(mang_guixe[j] == 0)
          {
            plc[i].vitri = j;
            mang_guixe[j] = 1;
            guivitri(j);
            break;
          }
        }
      }
      else if(plc[i].statuss == 1)
      {
        Serial.println("ma chu lam chi bo ai biet");
        plc[i].statuss = 0;
        guivitri(((plc[i].vitri)+6));
        mang_guixe[plc[i].vitri] = 0;
        break;
      }
    }
  }
  total = "";
  
  Serial.println("   ");
  
  mfrc522.PICC_HaltA();  //dung lai
  mfrc522.PCD_StopCrypto1();  //
  Serial.println("==========END===========   ");
  delay(5500);

}

void guivitri(int x0)
{
 
  for (int i=0;i<x0;i++)
  {
    digitalWrite(8,LOW);
    delay(70);
    digitalWrite(8,HIGH);
    delay(70);
  }
  digitalWrite(9,LOW);
  delay(70);
  digitalWrite(9,HIGH);
  delay(70);
}

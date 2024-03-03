#include <Firebase_ESP_Client.h>
#include <WiFi.h>
#include <addons/TokenHelper.h>
#include <ArduinoJson.h>
#define FIREBASE_USE_PSRAM

//Conectar a una red WiFi 
const char* WIFI_SSID = "celu";//el nombre de la red
const char* WIFI_PASSWORD = "123456789";//la contraseña de la red
//Recursos de Firebase
const char* API_KEY = "AIzaSyDLDMVG2YPoAUnx6or_TkaF9GLRePal2fE";
const char* FIREBASE_PROJECT_ID = "pokeappi-leds";
//CONFIGURAR UN EMAIL Y CONTRASEÑA EN AUTHENTICATION de Firebase
const char* USER_EMAIL = "markzuckerberg@esp.com";
const char* USER_PASSWORD = "123456";
//Define Firebase Data object
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

const int LEDR = 23;
const int LEDG = 22;
const int LEDB = 21;
const int LED = 19;

//Funcion para configuara WiFi
void setupWiFi() {
  Serial.print("Connecting to Wi-Fi");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
}

void setupFirebase() {
  config.api_key = API_KEY;
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;
  config.token_status_callback = tokenStatusCallback;  // Ver addons/TokenHelper.h
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void setup() {
  Serial.begin(115200);
  Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);//Verificamos la version
  setupWiFi();//Llamamos la funcion de configuración wifi
  setupFirebase();//Llamamos la funcion de configuración Firebase
  pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT);
  pinMode(LEDB, OUTPUT);
  pinMode(LED, OUTPUT);
}

void loop(){
    String path = "tipopokemon";//RUTA DE COLECCION
    FirebaseJson json;

  if (Firebase.Firestore.getDocument(&fbdo, FIREBASE_PROJECT_ID, "", path.c_str(), "")) {

    StaticJsonDocument<1024> doc;
    DeserializationError error = deserializeJson(doc, fbdo.payload().c_str());

    if (!error) {
      for (JsonObject document : doc["documents"].as<JsonArray>()) {
        const char* document_name = document["name"];//PARAMETRO NOMBRE //Serial.print(document_name);
        const char* state = document["fields"]["tipo"]["stringValue"]; //PARAMETRO DE CAMPOS A REVISAR
        Serial.print(":");
        if (strstr(document_name, "tipo") != nullptr) {//COMPARAR NOMBRE CON RESULTADO ESPERADO LED1
          if(strstr(state,"steel")!= nullptr){
            setColor(159, 93, 70); // Invertido: (96, 162, 185)
          }
          //---------------------------------
          else if(strstr(state,"water")!= nullptr){
              setColor(219, 126, 15); // Invertido: (36, 129, 240)
          }
          //---------------------------------
          else if(strstr(state,"bug")!= nullptr){
              setColor(104, 89, 226); // Invertido: (151, 166, 29)
          }
          //---------------------------------
          else if(strstr(state,"dragon")!= nullptr){
              setColor(255, 255, 0); // Invertido: (79, 96, 226)
          }
          //---------------------------------
          else if(strstr(state,"electric")!= nullptr){
              setColor(5, 62, 255); // Invertido: (250, 193, 0)
          }
          //---------------------------------
          else if(strstr(state,"ghost")!= nullptr){
              setColor(218, 215, 175); // Invertido: (111, 63, 112)
          }
          //---------------------------------
          else if(strstr(state,"fire")!= nullptr){
              setColor(0, 255, 255); // Invertido: (230, 34, 35)
          }
          //---------------------------------
          else if(strstr(state,"fairy")!= nullptr){
              setColor(16, 143, 15); // Invertido: (239, 112, 240)
          }
          //---------------------------------
          else if(strstr(state,"ice")!= nullptr){
              setColor(194, 38, 0); // Invertido: (61, 217, 255)
          }
          //---------------------------------
          else if(strstr(state,"fight")!= nullptr){
              setColor(161, 222, 214); // Invertido: (255, 129, 0)
          }
          //---------------------------------
          else if(strstr(state,"normal")!= nullptr){
              setColor(95, 93, 95); // Invertido: (160, 162, 160)
          }
          //---------------------------------
          else if(strstr(state,"grass")!= nullptr){
              setColor(255, 0, 255); // Invertido: (0, 255, 0)
          }
          //---------------------------------
          else if(strstr(state,"psychic")!= nullptr){
              setColor(16, 192, 243); // Invertido: (239, 63, 12)
          }
          //---------------------------------
          else if(strstr(state,"rock")!= nullptr){
              setColor(80, 85, 126); // Invertido: (175, 170, 129)
          }
          //---------------------------------
          else if(strstr(state,"dark")!= nullptr){
              setColor(25, 25, 25); // Invertido: (78, 63, 60)
          }
          //---------------------------------
          else if(strstr(state,"ground")!= nullptr){
              setColor(42, 207, 193); // Invertido: (145, 79, 26)
          }
          //---------------------------------
          else if(strstr(state,"poison")!= nullptr){
              setColor(110, 193, 52); // Invertido: (145, 62, 203)
          }
          //---------------------------------
          else if(strstr(state,"flying")!= nullptr){
              setColor(125, 69, 231); // Invertido: (130, 186, 24)
          }
          //---------------------------------
          else{
              setColor(255,255,255); // Invertido: (0,0,0)
          }

          //---------------------------------aaaaa

        }
          delay(1000); // Esperar 500 MILIS antes de la próxima lectura
      }
    }
	}
}
void setColor(int red, int green, int blue) {
  analogWrite(LEDR, red);
  analogWrite(LEDG, green);
  analogWrite(LEDB, blue);
}
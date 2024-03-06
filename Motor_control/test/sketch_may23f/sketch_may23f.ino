#define USE_WIFI_NINA         false
#define USE_WIFI101           true
#include <WiFiWebServer.h>

const char ssid[] = "EEERover";
const char pass[] = "exhibition";
const int groupNumber = 2; // Set your group number to make the IP address constant - only do this on the EEERover network

//Webpage to return when root is requested
const char webpage[] = \
"<html><head>\
<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\
<style>\
.slider-container { position: fixed; bottom: 100px; display: flex; justify-content: space-between; align-items: flex-end; padding: 20px; width: 100%; }\
.slider { -webkit-appearance: none; appearance: none; width: 250px; height: 50px; background: #d3d3d3; outline: none; opacity: 0.7; transition: opacity 0.2s; writing-mode: bt-lr; transform: rotate(-90deg); cursor: pointer; }\
.slider::-webkit-slider-thumb { -webkit-appearance: none; appearance: none; width: 60px; height: 60px; border-radius: 50%; background: #04AA6D; cursor: pointer; }\
.slider::-moz-range-thumb { width: 60px; height: 60px; border-radius: 50%; background: #04AA6D; cursor: pointer;}\
.slider-value { color: #000; font-size: 14px; text-align: center; margin-top: 100px; }\
.slider-container > div { flex-basis: 50%; display: flex; flex-direction: column; align-items: center; }\
</style> </head>\
<body>\
<h1>MOTOR CONTROL</h1> \
<div class=\"slider-container\">\
<div>\
<input type=\"range\" min=\"-10\" max=\"10\" value=\"0\" step=\"5\" class=\"slider\" id=\"leftRange\" onchange=\"sendSpeed()\">\
<div class=\"slider-value\" id=\"leftValue\">0</div>\ 
</div><div>\ 
<input type=\"range\" min=\"-10\" max=\"10\" value=\"0\" step=\"5\" class=\"slider\" id=\"rightRange\" onchange=\"sendSpeed()\">\
<div class=\"slider-value\" id=\"rightValue\">0</div>\
</div><script>\
var leftSlider = document.getElementById(\"leftRange\");\
var leftValueDisplay = document.getElementById(\"leftValue\");\
var rightSlider = document.getElementById(\"rightRange\");\
var rightValueDisplay = document.getElementById(\"rightValue\");\
leftSlider.addEventListener(\"input\", function() {leftValueDisplay.textContent = this.value;});\
rightSlider.addEventListener(\"input\", function() {rightValueDisplay.textContent = this.value;});\
function sendSpeed() {\
  var leftSpeed = document.getElementById('leftRange').value;\
  var rightSpeed = document.getElementById('rightRange').value;\
  var xhr = new XMLHttpRequest();\
  xhr.open('GET', '/speed?left=' + leftSpeed + '&right=' + rightSpeed, true);\
  xhr.send();\
}\
</script>\
</body></html>";




// //Webpage to return when root is requested
// const char webpage[] = \
// "<html> <head> <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\
// <style>\
// .slidecontainer {width: 100%;}\
// .slider {-webkit-appearance: none; width: 100%; height: 25px; background: #d3d3d3; outline: none; opacity: 0.7; -webkit-transition: .2s; transition: opacity .2s;}\
// .slider:hover {opacity: 1;}\
// .slider::-webkit-slider-thumb {-webkit-appearance: none; appearance: none; width: 25px; height: 25px; background: #04AA6D; cursor: pointer;}\
// .slider::-moz-range-thumb {width: 25px; height: 25px; background: #04AA6D; cursor: pointer;}\
// </style> </head>\
// <body>\
// <h1>Control the Car</h1>\
// <div class=\"slidecontainer\">\
// <p>Left Motor:</p>\
// <input type=\"range\" min=\"-200\" max=\"200\" value=\"0\" class=\"slider\" id=\"leftMotorSlider\" onchange=\"sendSpeed()\">\
// <p>Right Motor:</p>\
// <input type=\"range\" min=\"-200\" max=\"200\" value=\"0\" class=\"slider\" id=\"rightMotorSlider\" onchange=\"sendSpeed()\">\
// </div>\
// <script>\
// function sendSpeed() {\
//   var leftSpeed = document.getElementById('leftMotorSlider').value;\
//   var rightSpeed = document.getElementById('rightMotorSlider').value;\
//   var xhr = new XMLHttpRequest();\
//   xhr.open('GET', '/speed?left=' + leftSpeed + '&right=' + rightSpeed, true);\
//   xhr.send();\
// }\
// </script>\
// </body></html>";


// "<html><head><style>\
// .btn {background-color: inherit;padding: 14px 28px;font-size: 16px;}\
// .btn:hover {background: #eee;}\
// </style></head>\
// <body>\
// <button class=\"btn\" onclick=\"Forward()\">Forward</button>\
// <button class=\"btn\" onclick=\"Backward()\">Backward</button>\
// <button class=\"btn\" onclick=\"TurnLeft()\">Turn Left</button>\
// <button class=\"btn\" onclick=\"TurnRight()\">Turn Right</button>\
// <button class=\"btn\" onclick=\"STOP()\">STOP</button>\
// <br>MOTOR STATE: <span id=\"state\">OFF</span>\
// </body>\
// <script>\
// var xhttp = new XMLHttpRequest();\
// xhttp.onreadystatechange = function() {if (this.readyState == 4 && this.status == 200) {document.getElementById(\"state\").innerHTML = this.responseText;}};\
// function Forward() {xhttp.open(\"GET\", \"/F\"); xhttp.send();}\
// function Backward() {xhttp.open(\"GET\", \"/B\"); xhttp.send();}\
// function TurnLeft() {xhttp.open(\"GET\", \"/L\"); xhttp.send();}\
// function TurnRight() {xhttp.open(\"GET\", \"/R\"); xhttp.send();}\
// function STOP() {xhttp.open(\"GET\", \"/S\"); xhttp.send();}\
// </script></html>";

int leftMotorPin1 = 1;
int leftMotorPin2 = 3;
int RightMotorPin1 = 2;
int RightMotorPin2 = 4;

WiFiWebServer server(80);

void handleRoot()
{
  server.send(200, F("text/html"), webpage);
}
//Return the web page
void handleSpeed() {
  String leftMotorValue = server.arg("left");
  String rightMotorValue = server.arg("right");
  int leftMotorSpeed = leftMotorValue.toInt();
  int rightMotorSpeed = rightMotorValue.toInt();
  
  server.sendHeader("Access-Control-Allow-Origin", "*");
  // Control the left motor based on the left motor speed value
  if (leftMotorSpeed > 0) {
    // Forward Turn 
    analogWrite(leftMotorPin1,255);
    //analogWrite(RightMotorPin1,0);
    digitalWrite(leftMotorPin2,LOW);
    digitalWrite(RightMotorPin2,HIGH);
    server.send(200, F("text/plain"), F("Motor Control Engaged"));
  } else if (leftMotorSpeed < 5) {
    // forward Turn left
    analogWrite(leftMotorPin1,120);
    //analogWrite(RightMotorPin1,0);
    digitalWrite(leftMotorPin2,HIGH);
    digitalWrite(RightMotorPin2,LOW);
    server.send(200, F("text/plain"), F("Motor Control Engaged"));
  } else {
    // Stop
    analogWrite(leftMotorPin1, 0);
    analogWrite(leftMotorPin2, 0);
    server.send(200, F("text/plain"), F("Motor Control Engaged"));
  }

  // Control the right motor based on the right motor speed value
  if (rightMotorSpeed > 0) {
    //Forward Turn left
    analogWrite(leftMotorPin1,0);
    analogWrite(RightMotorPin1,200);
    digitalWrite(leftMotorPin2,LOW);
    digitalWrite(RightMotorPin2,HIGH);
    server.send(200, F("text/plain"), F("Motor Control Engaged"));
  } else if (rightMotorSpeed < 0) {
    // Backward Turn right
    analogWrite(leftMotorPin1,0);
    analogWrite(RightMotorPin1,200);
    digitalWrite(leftMotorPin2,HIGH);
    digitalWrite(RightMotorPin2,LOW);
    server.send(200, F("text/plain"), F("Motor Control Engaged"));
  } else {
    // Stop
    analogWrite(RightMotorPin1, 0);
    analogWrite(RightMotorPin2, 0);
    server.send(200, F("text/plain"), F("Motor Control Engaged"));
  }

}


//Go forward and acknowledge

// void Forward()
// {
//   analogWrite(1,200);
//   analogWrite(2,200);
//   digitalWrite(3,LOW);
//   digitalWrite(4,HIGH);
  
//   server.send(200, F("text/plain"), F("FORWARD"));
// }

// //Go backwards and acknowledge
// void Backward()
// {
//   analogWrite(1,200);
//   analogWrite(2,200);
//   digitalWrite(3,HIGH);
//   digitalWrite(4,LOW);

//   server.send(200, F("text/plain"), F("BACKWARDS"));
// }

// //Turn Left and acknowledge
// void TurnLeft()
// {
//   analogWrite(1,200);
//   analogWrite(2,0);
//   digitalWrite(3,LOW);
//   digitalWrite(4,HIGH);
//   server.send(200, F("text/plain"), F("TURNING LEFT"));
// }

// //Turn right and acknowledge
// void TurnRight()
// {
//   analogWrite(1,0);
//   analogWrite(2,200);
//   digitalWrite(3,LOW);
//   digitalWrite(4,HIGH);
//   server.send(200, F("text/plain"), F("TURNING RIGHT"));
// }

// //STOP moving and acknowledge
// void STOP()
// {
//   analogWrite(1,0);
//   analogWrite(2,0);

//   server.send(200, F("text/plain"), F("STOP"));
// }

//Generate a 404 response with details of the failed request
void handleNotFound()
{
  String message = F("File Not Found\n\n"); 
  message += F("URI: ");
  message += server.uri();
  message += F("\nMethod: ");
  message += (server.method() == HTTP_GET) ? F("GET") : F("POST");
  message += F("\nArguments: ");
  message += server.args();
  message += F("\n");
  for (uint8_t i = 0; i < server.args(); i++)
  {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, F("text/plain"), message);
}

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, 0);
  pinMode(leftMotorPin1,OUTPUT);
  pinMode(leftMotorPin2,OUTPUT);
  pinMode(RightMotorPin1,OUTPUT);
  pinMode(RightMotorPin2,OUTPUT);

  digitalWrite(leftMotorPin2, LOW);
  digitalWrite(RightMotorPin2, LOW);


  Serial.begin(9600);

  //Wait 10s for the serial connection before proceeding
  //This ensures you can see messages from startup() on the monitor
  //Remove this for faster startup when the USB host isn't attached
  while (!Serial && millis() < 10000);  

  Serial.println(F("\nStarting Web Server"));

  //Check WiFi shield is present
  if (WiFi.status() == WL_NO_SHIELD)
  {
    Serial.println(F("WiFi shield not present"));
    while (true);
  }

  //Configure the static IP address if group number is set
  //if (groupNumber)
    //WiFi.config(IPAddress(192,168,0,groupNumber+1));

  // attempt to connect to WiFi network
  Serial.print(F("Connecting to WPA SSID: "));
  Serial.println(ssid);
  while (WiFi.begin(ssid, pass) != WL_CONNECTED)
  {
    delay(500);
    Serial.print('.');
  }

  //Register the callbacks to respond to HTTP requests
  server.on("/", HTTP_GET, handleRoot);
  server.on("/speed", HTTP_GET, handleSpeed);
  //server.on("/STOP", HTTP_GET, STOP);
  server.onNotFound(handleNotFound);
  
  server.begin();
  
  Serial.print(F("HTTP server started @ "));
  Serial.println(static_cast<IPAddress>(WiFi.localIP()));
}

//Call the server polling function in the main loop
void loop()
{
  server.handleClient();
}

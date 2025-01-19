#include <WiFi.h>
#include <WebServer.h>
#include <TB6612_ESP32.h>

// WiFi credentials
const char *ssid = "your_ssid";     // WiFi SSID
const char *password = "your_password"; // WiFi password

// Motor controller pins
#define AIN1 13   // Motor 1 input pin 1
#define BIN1 12   // Motor 2 input pin 1
#define AIN2 14   // Motor 1 input pin 2
#define BIN2 27   // Motor 2 input pin 2
#define PWMA 26   // Motor 1 PWM control pin
#define PWMB 25   // Motor 2 PWM control pin
#define STBY 33   // Standby pin for motor controller (active high)

// Motor driver frequency, resolution, and channel pin (values based on your setup)
#define PWM_FREQ 1000
#define PWM_RESOLUTION 8
#define PWM_CHANNEL_A 0
#define PWM_CHANNEL_B 1

// Create Motor objects for motor 1 and motor 2
Motor motor1 = Motor(AIN1, AIN2, PWMA, 1, STBY, PWM_FREQ, PWM_RESOLUTION, PWM_CHANNEL_A);
Motor motor2 = Motor(BIN1, BIN2, PWMB, 1, STBY, PWM_FREQ, PWM_RESOLUTION, PWM_CHANNEL_B);

// Web server object to handle HTTP requests
WebServer server(80);

// Variables to hold the speed values for each motor
int speedLeft = 0;    // Speed of left motor (-255 to 255)
int speedRight = 0;   // Speed of right motor (-255 to 255)

void setup() {
  // Start serial communication for debugging
  Serial.begin(115200);
  
  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.println();
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi");

  // Setup the server with routes for controlling the car
  server.on("/", HTTP_GET, handleRoot);           // Home page route
  server.on("/set_speed", HTTP_GET, setSpeed);    // Set speed route
  server.on("/move", HTTP_GET, moveCar);          // Move the car route
  server.on("/break", HTTP_GET, breakCar);        // Break the car route

  // Start the web server
  server.begin();
  Serial.println("Server started");

  // Set up motor control pins
  pinMode(STBY, OUTPUT);    // Set Standby pin as output
  digitalWrite(STBY, HIGH); // Enable the motor driver
}

void loop() {
  // Handle incoming client requests
  server.handleClient();
}

void handleRoot() {
  String html = "<html><head><style>"
                "body {font-family: Arial, sans-serif; text-align: center; padding: 20px;} "
                "h1 {color: #333;} "
                "button {font-size: 20px; padding: 10px 20px; margin: 10px; border: none; cursor: pointer;} "
                "button:hover {background-color: #ddd;} "
                ".controls {display: flex; justify-content: center; align-items: center; flex-wrap: wrap;} "
                "</style></head><body>"
                "<h1>ESP32 RC Car Control</h1>"
                "<div class='controls'>"
                "<h2>Left Motor Speed (-255 to 255)</h2>"
                "<input type='range' min='-255' max='255' value='" + String(speedLeft) + "' id='leftSpeedSlider' onchange='setSpeed()'><br><br>"
                "<h2>Right Motor Speed (-255 to 255)</h2>"
                "<input type='range' min='-255' max='255' value='" + String(speedRight) + "' id='rightSpeedSlider' onchange='setSpeed()'><br><br>"
                "</div>"
                "<button onclick='breakCar()'>Break</button><br><br>"
                "<script>"
                "function setSpeed() {"
                "  var leftSpeed = document.getElementById('leftSpeedSlider').value;"
                "  var rightSpeed = document.getElementById('rightSpeedSlider').value;"
                "  var xhr = new XMLHttpRequest();"
                "  xhr.open('GET', '/set_speed?left=' + leftSpeed + '&right=' + rightSpeed, true);"
                "  xhr.send();"
                "} "
                "function breakCar() {"
                "  var xhr = new XMLHttpRequest();"
                "  xhr.open('GET', '/break', true);"
                "  xhr.send();"
                "} "
                "</script>"
                "</body></html>";
  
  // Send HTML to the client
  server.send(200, "text/html", html);
}

void setSpeed() {
  if (server.hasArg("left") && server.hasArg("right")) {
    speedLeft = server.arg("left").toInt();    // Left motor speed (-255 to 255)
    speedRight = server.arg("right").toInt();  // Right motor speed (-255 to 255)
    Serial.print("Left Speed: ");
    Serial.print(speedLeft);
    Serial.print(", Right Speed: ");
    Serial.println(speedRight);
  }
  moveCar();  // Automatically update the car's movement when speed changes
  server.send(200, "text/html", "Speed set to: Left = " + String(speedLeft) + ", Right = " + String(speedRight));
}

void moveCar() {
  // Debugging output to monitor speed
  Serial.print("Moving Left Motor: ");
  Serial.println(speedLeft);
  motor1.drive(speedLeft);  // This handles both forward and reverse based on speed value

  // Debugging output to monitor speed
  Serial.print("Moving Right Motor: ");
  Serial.println(speedRight);
  motor2.drive(speedRight);  // This handles both forward and reverse based on speed value
}

void breakCar() {
  speedLeft = 0;
  speedRight = 0;
  motor1.drive(0);  // Stop left motor
  motor2.drive(0);  // Stop right motor
  Serial.println("Car Braked!");
  server.send(200, "text/html", "Car has been braked.");
}

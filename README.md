# MessageDevice (ESP8266)
This project can be used to stay in contact with people you care about. You can send messages via a web application to a device including a quick drawing on a 8x8 LED Matrix (check out the pictures).
## Required Parts
* ESP8266
* AZDelivery HD44780 2004 LCD
* AZDelivery MAX7219 8x8 Dot Matrix MCU 64
* AZDelivery KY-004 Taster
## Building Instructions
I build this project for myself. Therefore, I don't provide a ready to use solution. It is a project from a developer to developers. Theferore, don't be afraid to dig down into the source code to figure things out.
## Web application
In order to use HTTPS I would run the Webapplication behind an proxy (I use the nginx proxy manager). Just start the nginx proxy manager in a seperate docker container and use an external network `proxy_net`.  
Then just run `docker-compose up -d` in the repository root. After that setup an proxy host which points to `message-device:80`. Make sure to create an TLS Certificate and disallow plain HTTP connections to stay secure.
## Device
| Component  | Component Pin | NodeMCU Pin |
|------------|---------------|-------------|
| Button     | S             | RX          |
| LED Matrix | DIN           | D7          |
| LED Matrix | CS            | D8          |
| LED Matrix | CLK           | D5          |
| LCD        | SDA           | D2          |
| LCD        | SCL           | D1          |

The project is build via `platform.io`. There are certain settings that can be configured in the platformio.ini file:
* WIFI_SSID: The WIFI SSID
* WIFI_PASSWORD: The WIFI Password
* DEVICE_ID: The Device ID for which the device can receive messages. A new Device ID can be added in the web application under `application/ClientApp/src/app/new-message/new-message.component.ts` in the `receivers` array.
* API_USER: The API User for the HTTP Basic Authentication
* API_PASSWORD: The API Password for the HTTP Basic Authentication
* DOMAIN: The Domain where the API is hosted
* MATRIX_TYPE: The used Matrix type. See `majicdesigns/MD_MAX72XX` library for more details.

## Pictures / Screenshots
![web application](doc/web_application.png?raw=true)
![good night message](doc/good_night.jpeg?raw=true)
![device front](doc/device_front.jpeg?raw=true)
![device back](doc/device_back.jpeg?raw=true)
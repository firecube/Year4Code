#include <user_config.h>
#include <SmingCore/SmingCore.h>
#include <Adafruit_NeoPixel/Adafruit_NeoPixel.h>


#define PIN 5
#define NUMPIXELS 24

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int red = strip.Color(255, 0, 0);
int green = strip.Color(0, 255, 0);
int blue = strip.Color(0, 0, 255);

Timer loopTimer;

int stripNo = 0;
int colour = red;

HttpServer server;

void ColourChangeRGB() 
{
	if (stripNo < strip.numPixels())
	{
		strip.setPixelColor(stripNo, colour);
		strip.show();
		stripNo++;
	}
	else
	{
		loopTimer.stop();
		
		stripNo = 0;

		if (colour == red)
		{
			colour = green;
		}
		else if(colour == green)
		{
			colour = blue;
		}
		else if(colour == blue)
		{
			colour = red;
		}

		loopTimer.initializeMs(50, ColourChangeRGB).start(true);
	}
}

void onIndex(HttpRequest &request, HttpResponse &response)
{
	response.sendString("Hello Year 4!");
}

void startWebServer()
{
	server.listen(80);
	server.addPath("/", onIndex);
}

void init()
{
	Serial.begin(SERIAL_BAUD_RATE);
	Serial.systemDebugOutput(false);

	Serial.print("Year 4 demo... start");

	strip.begin();
	loopTimer.initializeMs(50, ColourChangeRGB).start(true);

	WifiAccessPoint.enable(true);
	WifiAccessPoint.config("Year4", "", AUTH_OPEN);
	WifiAccessPoint.setIP(IPAddress(192, 168, 2, 1));

	startWebServer();
}
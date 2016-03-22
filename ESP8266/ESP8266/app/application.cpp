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
int userColour = 0;

HttpServer server;


void sendColour()
{
	WebSocketsList &clients = server.getActiveWebSockets();
	for (int i = 0; i < clients.count(); i++)
	{
		clients[i].sendString(String(colour));
	}
}


void colourChangeRGB()
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
		else if (colour == green)
		{
			colour = blue;
		}
		else if (colour == blue)
		{
			colour = red;
		}

		sendColour();

		loopTimer.initializeMs(50, colourChangeRGB).start(true);
	}
}

void doColourChangeRGB()
{
	stripNo = 0;
	colour = red;
	loopTimer.initializeMs(50, colourChangeRGB).start(true);
}


void colourChange()
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

		if (colour == userColour)
		{
			colour = strip.Color(0, 0, 0);
		}
		else
		{
			colour = userColour;
		}

		sendColour();

		loopTimer.initializeMs(50, colourChange).start(true);
	}
}

void doColourChange()
{
	stripNo = 0;
	loopTimer.initializeMs(50, colourChange).start(true);
}

void onIndex(HttpRequest &request, HttpResponse &response)
{
	response.sendString("Hello Year 4!");
}

void onReset(HttpRequest &request, HttpResponse &response)
{
	response.sendString("OK");
	doColourChangeRGB();
}

void onSetColour(HttpRequest &request, HttpResponse &response)
{
	response.sendString("OK");

	int r = atoi(request.getQueryParameter("r").c_str());
	int g = atoi(request.getQueryParameter("g").c_str());
	int b = atoi(request.getQueryParameter("b").c_str());

	colour = strip.Color(r, g, b);
	userColour = colour;

	doColourChange();
}

void onGetColour(HttpRequest &request, HttpResponse &response)
{
	TemplateFileStream *tmpl = new TemplateFileStream("colour.html");
	auto &vars = tmpl->variables();
	vars["colour"] = String(colour);
	response.sendTemplate(tmpl);
}

void startWebServer()
{
	server.listen(80);

	server.addPath("/", onIndex);
	server.addPath("/reset", onReset);
	server.addPath("/colour", onGetColour);
	server.addPath("/setcolour", onSetColour);

	server.enableWebSockets(true);
}

void init()
{
	spiffs_mount();

	Serial.begin(SERIAL_BAUD_RATE);
	Serial.systemDebugOutput(false);

	Serial.print("Year 4 demo... start");

	WifiAccessPoint.enable(true);
	WifiAccessPoint.config("Year4", "", AUTH_OPEN);
	WifiAccessPoint.setIP(IPAddress(192, 168, 2, 1));

	startWebServer();

	strip.begin();
	doColourChangeRGB();
}
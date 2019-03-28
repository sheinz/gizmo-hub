#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <unistd.h>

#include <RF24/RF24.h>
#include "MqttClient.h"

#define mqtt_host "localhost"
#define mqtt_port 1883

using namespace std;

// CE - PA02 of OrangePI
// CSN - PA13/SPI1_CS of OrangePI
// 10 means /dev/spidev1.0
RF24 radio(2, 10);

bool radioNumber = 1;


// Radio pipe addresses for the 2 nodes to communicate.
const uint8_t pipes[][6] = {"1Node","2Node"};


int main(int argc, char** argv)
{
  bool role_ping_out = true, role_pong_back = false;
  bool role = role_pong_back;

  MqttClient mqtt("localhost", 1883);

  radio.begin();

  // optionally, increase the delay between retries & # of retries
  radio.setRetries(15, 15);

  // Dump the configuration of the rf unit for debugging
  radio.printDetails();


/********* Role chooser ***********/

  printf("\n ************ Role Setup ***********\n");
  string input = "";
  char myChar = {0};
  cout << "Choose a role: Enter 0 for pong_back, 1 for ping_out (CTRL+C to exit) \n>";
  getline(cin,input);

  if(input.length() == 1) {
	myChar = input[0];
	if(myChar == '0'){
		cout << "Role: Pong Back, awaiting transmission " << endl << endl;
	}else{  cout << "Role: Ping Out, starting transmission " << endl << endl;
		role = role_ping_out;
	}
  }
/***********************************/
  // This simple sketch opens two pipes for these two nodes to communicate
  // back and forth.

    if ( !radioNumber )    {
      radio.openWritingPipe(pipes[0]);
      radio.openReadingPipe(1,pipes[1]);
    } else {
      radio.openWritingPipe(pipes[1]);
      radio.openReadingPipe(1,pipes[0]);
    }

	radio.startListening();

	// forever loop
	while (1)
	{
		if (role == role_ping_out)
		{
			// First, stop listening so we can talk.
			radio.stopListening();

			// Take the time, and send it.  This will block until complete

			printf("Now sending...\n");
			unsigned long time = millis();

			bool ok = radio.write( &time, sizeof(unsigned long) );

			if (!ok){
				printf("failed.\n");
			}
			// Now, continue listening
			radio.startListening();

			// Wait here until we get a response, or timeout (250ms)
			unsigned long started_waiting_at = millis();
			bool timeout = false;
			while ( ! radio.available() && ! timeout ) {
				if (millis() - started_waiting_at > 200 )
					timeout = true;
			}


			// Describe the results
			if ( timeout )
			{
				printf("Failed, response timed out.\n");
			}
			else
			{
				// Grab the response, compare, and send to debugging spew
				unsigned long got_time;
				radio.read( &got_time, sizeof(unsigned long) );

				// Spew it
				printf("Got response %lu, round-trip delay: %lu\n",got_time,millis()-got_time);
			}
			sleep(1);
		}

		//
		// Pong back role.  Receive each packet, dump it out, and send it back
		//

		if ( role == role_pong_back )
		{

			// if there is data ready
			if ( radio.available() )
			{
				// Dump the payloads until we've gotten everything
				unsigned long got_time;

				// Fetch the payload, and see if this was the last one.
				while(radio.available()){
					radio.read( &got_time, sizeof(unsigned long) );
				}
				radio.stopListening();

				radio.write( &got_time, sizeof(unsigned long) );

				// Now, resume listening so we catch the next packets.
				radio.startListening();

				// Spew it
				printf("Got payload(%d) %lu...\n",sizeof(unsigned long), got_time);

				delay(925); //Delay after payload responded to, minimize RPi CPU time

			}

		}
        mqtt.loop();

	} // forever loop

  return 0;
}


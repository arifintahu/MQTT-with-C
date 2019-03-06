//
//  main.c
//  mqtt_publisher
// Current Assumes
// QoS 0
// All messages < 127 bytes
// ./mqttpub -c <client name> -i <ip address> -p <port> -t <topic> -n <loop count>
// e.g.
// ./mqttpub -i 192.168.1.38 -t mbed/fishtank -c MacBook -n 5

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mqtt.h"

#include <unistd.h> // for sleep function
#define MAX 50
char buf[MAX];
int jumlah_buf;

const char *client_name = "default_pub"; 	// -c
const char *ip_addr     = "127.0.0.1";		// -i
uint32_t    port        = 1883;			// -p
const char *topic       = "sensorwarna";	// -t
uint32_t    count       = 10;			// -n
FILE *inputFile;
const char *inputFileName = "sensorwarna.json";

void parse_options(int argc, char** argv);

int main (int argc, char** argv)
{
    puts("MQTT PUB Test Code");
    if(argc > 1) {
	parse_options(argc, argv);
    }

    //reading file JSON
    inputFile = fopen(inputFileName, "rb");
    int i=0;
    while(1) {
      char c = fgetc(inputFile);
      if( feof(inputFile) ) {
         break ;
      }
      buf[i]=c;
      printf("%c", c);
      i++;
   }
   fclose(inputFile);

   jumlah_buf=i;
   printf("nilai jumlah_buf %d \n", jumlah_buf);
   for (int i = 0; i < jumlah_buf; i++) {
     printf("%c", buf[jumlah_buf]);
   }

//  mqtt_broker_handle_t *broker = mqtt_connect("default_pub","127.0.0.1", 1883);
    mqtt_broker_handle_t *broker = mqtt_connect(client_name, ip_addr, port);


    if(broker == 0) {
        puts("Failed to connect");
        exit(1);
    }

        printf("Buf %s\n",buf);
        if(mqtt_publish(broker, topic, buf, QoS1) == -1) {
            printf("publish failed\n");
        }
        else {
            printf("Sent %d messages\n", i);
        }
        sleep(1);


    // for(int i = 1; i <= count; ++i) {
    //     sprintf(msg, "Warna ke-%d", i);
    //     if(mqtt_publish(broker, topic, msg, QoS1) == -1) {
    //         printf("publish failed\n");
    //     }
    //     else {
    //         printf("Sent %d messages\n", i);
    //     }
    //     sleep(1);
    // }
    mqtt_disconnect(broker);
}

void parse_options(int argc, char** argv)
{
   for(int i = 1; i < argc; ++i) {
	if(strcmp("-c",argv[i]) == 0) {
		printf("client:%s ",argv[++i]);
		client_name = argv[i];
	}
	if(strcmp("-i",argv[i]) == 0) {
		printf("ip:%s ",argv[++i]);
		ip_addr = argv[i];
	}
	if(strcmp("-p",argv[i]) == 0) {
		printf("port:%s ", argv[++i]);
		port = atoi(argv[i]);
	}
	if(strcmp("-t",argv[i]) == 0) {
		printf("topic:%s ",argv[++i]);
		topic = argv[i];
	}
	if(strcmp("-n",argv[i]) == 0) {
		printf("count:%s ",argv[++i]);
		count = atoi(argv[i]);
	}
   }
   puts("");
}

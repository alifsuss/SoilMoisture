#include "mbed.h"  
#include "DHT22.h" //this is the moisture sensor 

//------------------------------------
// Hyperterminal configuration
// 9600 bauds, 8-bit data, no parity
//------------------------------------

//Serial pc(SERIAL_TX, SERIAL_RX);    //this is to pc if you connect your ST to PC via USB
Serial pc(PA_11, PA_12, 9600);        // this from pins to RPi3

DigitalOut myled(LED1);              //this to turn on light
AnalogIn analogRead(PA_0);           // declare the analog signal which is Air Humidity Sensor
DHT22 dhtSensor(PA_1);              //This is the DHT22 port

int main()
{
    float humidityVal = 0;         //All to set initial values
    float temperatureVal = 0;
    float moistureVal = 0;
    float moistcalib = 0;
    
    int i = 1;
    while(1) {
        wait(600);                                                  //this the wait time that the sensor needs
        //printf("This program runs since %d seconds.\n\n", i);
        //i++;
        i = i + 1;                                                  
        myled = !myled;
        
        //print time
        //time_t my_time = time(NULL);                      // I didnt print time, but use the time from RPi3 instead
        //pc.printf("%s", ctime(&my_time));
               
        
        // DHT22 Humidity
        dhtSensor.readData();                              //calling the sensor
        humidityVal = dhtSensor.getHumidity();             //recording air humidity.. see DHT22 manual
        //pc.printf("Humidity: %f.\n", humidityVal);
        pc.printf("%.1f,", humidityVal);                    //printing humidity
        
        //DHT22 temperature
        temperatureVal = dhtSensor.getTemperatureC();           //declaring new temperature value
        //pc.printf("Temperature: %f.\n", temperatureVal); 
        pc.printf("%.1f,", temperatureVal);                     //printing temperature
        
        //MHS moisture
        moistureVal = analogRead;                       //declaring soil moisture
        moistcalib = (1 - moistureVal)*100;             // moisture was measured in fraction of Voltage detected (Here I use 3.5V port) then multiplied by 100,
        pc.printf("%.1f", moistcalib);              // declaring the moisture
    }
}

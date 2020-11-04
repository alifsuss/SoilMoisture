#include "mbed.h"
#include "DHT22.h"

//------------------------------------
// Hyperterminal configuration
// 9600 bauds, 8-bit data, no parity
//------------------------------------

//Serial pc(SERIAL_TX, SERIAL_RX); //this is to pc
Serial pc(PA_11, PA_12, 9600); // this from pins to RPi3

DigitalOut myled(LED1);
AnalogIn analogRead(PA_0);
DHT22 dhtSensor(PA_1);

int main()
{
    float humidityVal = 0;
    float temperatureVal = 0;
    float moistureVal = 0;
    float moistcalib = 0;
    
    int i = 1;
    while(1) {
        wait(600);
        //printf("This program runs since %d seconds.\n\n", i);
        //i++;
        i = i + 1;
        myled = !myled;
        
        //print time
        //time_t my_time = time(NULL);
        //pc.printf("%s", ctime(&my_time));
               
        
        // DHT22 Humidity
        dhtSensor.readData();
        humidityVal = dhtSensor.getHumidity();
        //pc.printf("Humidity: %f.\n", humidityVal);
        pc.printf("%.1f,", humidityVal);
        
        //DHT22 temperature
        temperatureVal = dhtSensor.getTemperatureC();
        //pc.printf("Temperature: %f.\n", temperatureVal); 
        pc.printf("%.1f,", temperatureVal); 
        
        //MHS moisture
        moistureVal = analogRead;
        moistcalib = (1 - moistureVal)*100;
        pc.printf("%.1f", moistcalib); 
    }
}

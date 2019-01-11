#include <SPI.h>
SPIClass * vspi = NULL;
static const int spiClk = 1000000;

uint8_t data1 = 0b00000000; // junk data to illustrate usage
uint8_t received_data;

void setup() 
{
  vspi = new SPIClass(VSPI);
  
  //initialise vspi with default pins
  //SCLK = 18, MISO = 19, MOSI = 23, SS = 5
  vspi->begin();
  //alternatively route through GPIO pins of your choice
  //hspi->begin(0, 2, 4, 33); //SCLK, MISO, MOSI, SS

   pinMode(5, OUTPUT); 
   Serial.begin(115200);
}

void loop() 
{
   received_data = vspiCommand(data1);
   Serial.print(received_data);
   Serial.print("\t");
   Serial.println(data1);
   delay(1000);
   data1 = data1 + 1;
}

uint8_t vspiCommand(uint8_t send_data) 
{
  uint8_t receive_data;
  vspi->beginTransaction(SPISettings(spiClk, MSBFIRST, SPI_MODE0));
  digitalWrite(5, LOW); //pull SS slow to prep other end for transfer
  receive_data = vspi->transfer(send_data);  
  digitalWrite(5, HIGH); //pull ss high to signify end of data transfer
  vspi->endTransaction();
  return receive_data;
}
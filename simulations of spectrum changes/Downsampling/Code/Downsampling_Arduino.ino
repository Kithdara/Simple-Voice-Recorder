#include <SPI.h>
#include <SD.h>


void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
   //Serial.print("Initializing SD card...");

  if (!SD.begin(4)) {
    //Serial.println("initialization failed!");
    while (1);
  }
  //Serial.println("initialization done.");




  downsample("male.wav","male_out.wav");
  //downsample("uuu.wav","uuu_out.wav");
  
}

void loop() {
  // put your main code here, to run repeatedly:

}





void downsample(char* filename,char* out_name){
File myFile;
File outputFile;

unsigned long  i=0;
unsigned long  fileSize;
char *buff;

 //remove exsiting files 
 SD.remove(out_name);
    
 // open the file for reading and Writing:
 myFile = SD.open(filename);
 fileSize=myFile.size();
 outputFile = SD.open(out_name, FILE_WRITE);
 buff=(char*)malloc(128);
//copy header file data to new wav file header 
      while (i!=80) {
      outputFile.write(myFile.read());
      i+=1;
      }
   
 //start downsampling   

 myFile.read(buff,128);
Serial.println("Downsampling.........");
    while (fileSize-i>128) {
      
      i+=128;
      for (int j=0;j<64;j++){
        buff[j]=buff[2*j];
        
      }
      outputFile.write(buff,64);
     
     
      myFile.read(buff,128);
    }
    
    // close the file:
    myFile.close();
   outputFile.close();
   Serial.println("______***Successfully C ompleted!****_________");
  
}

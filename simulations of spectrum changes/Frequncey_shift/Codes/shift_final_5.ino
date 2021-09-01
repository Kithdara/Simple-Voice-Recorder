#include <SPI.h>
#include <SD.h>
//This fillter enhance the High frequency(>2kHZ) range by increasing its amplitude by a factor of 8, and reducing the amplitude of Low Frequency (<2KHZ)range by a factor of 1/8.

double h[]={0.0217 ,  -0.0023 ,  -0.0358 ,  -0.0842 ,  -0.1276 ,   0.4567 ,  -0.1276 ,  -0.0842 ,  -0.0358 ,  -0.0023   , 0.0217};

File myFile;
File outputFile;
const int h_length = 11;  //length of filter
double Data[h_length];   // array to save sample values that need to convolution
unsigned long counter=0;         // counter varible
double temp;             // The values read from the wav file are temporarily sretained by this variable
double sum=0;            //result of convolution by this variable Y[n] = x[n]*h[n]
char buffer1[256];
int bu=0;
float pi=22/7;
int shift =2000;
void setup() {

  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
   Serial.print("Initializing SD card...");

  if (!SD.begin(4)) {
    //Serial.println("initialization failed!");
    while (1);
  }
  //Serial.println("initialization done.");

 //remove  existing files   
 SD.remove("male_out.wav");   
 // open the file for reading and Writing
 myFile = SD.open("male.wav");
 outputFile = SD.open("male_out.wav",FILE_WRITE);
unsigned long len=myFile.size();
 
 // copy header data of wave file to new wav file
while (counter!=78) {
    temp=myFile.read();
    outputFile.write(temp);
    counter++;
    }


//load samaple values to Data array
for (int j=0;j<h_length;j++){
  temp=myFile.read();
  Data[h_length-j-1]=temp*cos(2*pi*shift*(counter)/len);
  counter++;
  }



  
Serial.println("processing.........");
//---------------------------find the maximum and the minimum values---------------


//---------------start Shifting and filtering--------------------
counter=78;
myFile.seek(counter);
int temp2;
//load samaple values to Data array
for (int j=0;j<h_length;j++){
  temp=myFile.read()*cos(2*pi*shift*(counter)/len);
  counter++;
  Data[h_length-j-1]=temp;
  }

Serial.println("processing.........");
// start convoltion
// Number of overlapping is less than length of array "h" and overlaping is increasing in this part.
for (int i=0;i<h_length;i++){
  sum=0;
  for (int j=0;j<i+1;j++){
    sum+=h[j]*Data[h_length-1-i+j];
  }
  temp2=sum+125;
outputFile.write(temp2);
  }
  



//Number of overlapping is similar to length of "h".
  while(myFile.available()){
    for(int k =h_length -1;k>0;k--){
      Data[k]=Data[k-1];
    }
    Data[0]=myFile.read()*cos(2*pi*shift*(counter)/len);
    counter++;
    sum=0;
    for(int i =0;i<h_length;i++){
      sum += Data[i]*h[i];
    }
    temp2=sum+125;
      buffer1[bu]=temp2;
      bu++;
      if (bu >=255){
        outputFile.write(buffer1,255);
        bu=0;
      }
       
       
    }
// number of overlapping is decreasing.
  for (int i=0;i<h_length -1;i++){
    sum=0;
    for(int j;j<h_length - i-1;j++){
      sum += Data[h_length-i-j-2]*h[h_length-1-j];
    }
    temp2=sum+125;
    outputFile.write(temp2);
  }
  Serial.println("_________Done_____________");
//close files
myFile.close();
outputFile.close();

}
void loop() {
  // put your main code here, to run repeatedly:

}

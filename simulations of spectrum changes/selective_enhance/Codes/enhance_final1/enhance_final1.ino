#include <SPI.h>
#include <SD.h>
//This fillter enhance the High frequency(>2.5kHZ) range by increasing its amplitude by a factor of 8, and reducing the amplitude of Low Frequency (<2.5KHZ)range by a factor of 1/8.
 double h[]={0  , -0.0029 ,  -0.0049  ,  0.0054 ,   0.0262 ,   0.0177 ,  -0.0594   ,-0.1730 ,   0.3816 ,  -0.1706  , -0.0508  ,  0.0343  ,  0.0465 ,   0.0220 ,   0.0037 ,-0.0005  ,  0.0005};
File myFile;
File outputFile;
const int h_length = 17;  //length of filter
double Data[h_length];   // array to save sample values that need to convolution
int   counter=0;         // counter varible
int temp;             // The values read from the wav file are temporarily sretained by this variable
double sum=0;            //result of convolution by this variable Y[n] = x[n]*h[n]
char buffer1[256];



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

 
Serial.println("processing.........");

 // copy header data of wave file to new wav file
while (counter!=78) {
    outputFile.write(myFile.read());
    counter++;
    }



//---------------convoltion--------------------


//load samaple values to Data array
for (int j=0;j<h_length;j++){
  Data[h_length-j-1]=myFile.read();
  }


// start convoltion

// Number of overlapping is less than length of array "h" and overlaping is increasing in this part.
for (int i=0;i<h_length;i++){
  sum=0;
  for (int j=0;j<i+1;j++){
    sum+=h[j]*Data[h_length-1-i+j];
  }
  temp=sum+125;
  outputFile.write(temp);
  }
  



//Number of overlapping is similar to length of "h".
counter=0;
  while(myFile.available()){
    for(int k =h_length -1;k>0;k--){
      Data[k]=Data[k-1];
    }
    Data[0]=myFile.read();
    sum=0;
    for(int i =0;i<h_length;i++){
      sum += Data[i]*h[i];
    }
    temp=sum+125;
      buffer1[counter]=temp;
      counter++;
      if (counter >=255){
        outputFile.write(buffer1,255);
        counter=0;
      }  
    }

    
// number of overlapping is decreasing.
  for (int i=0;i<h_length -1;i++){
    sum=0;
    for(int j;j<h_length - i-1;j++){
      sum += Data[h_length-i-j-2]*h[h_length-1-j];
    }
    temp=sum+125;
    outputFile.write(temp);
  }
 
Serial.println("_________Done_____________");


//close files
myFile.close();
outputFile.close();
}



void loop() {
  

}

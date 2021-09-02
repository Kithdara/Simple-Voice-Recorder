#include <SD.h>
#include <SPI.h>
#include <TMRpcm.h>
#define SD_ChipSelectPin 10
#include <LiquidCrystal.h>
LiquidCrystal lcd(6, 5, 4, 3, 2, 0);
TMRpcm audio,player;
unsigned long i=0;
int upButton=A1;
int downButton=A2;
int selectButton=A3;
int backButton=A4;
int audiofile=0;
int menu=1;
int menu2=1;
int menuInside=0;
void setup() {
  lcd.begin(16, 2);
  pinMode(upButton, INPUT_PULLUP);
  pinMode(downButton, INPUT_PULLUP);
  pinMode(selectButton, INPUT_PULLUP);
  pinMode(backButton, INPUT_PULLUP);

  updateMenu();
  pinMode(A0, INPUT);
  SD.begin(SD_ChipSelectPin);
  audio.CSPin = SD_ChipSelectPin;
  audio.speakerPin = 9;

}

void loop() {
  if (!digitalRead(downButton) and menuInside==0){ // decrease 'menu' to go down in main menu
    menu++;
    updateMenu();
    delay(500);
    while (!digitalRead(downButton));
  }
  if (!digitalRead(downButton) and menuInside==2 and audiofile and menu2<4){ // decrease 'menu2' to go down in saved recordings
    menu2++;
    recordHistory();
    delay(500);
    while (!digitalRead(downButton));
  }
  if (!digitalRead(upButton) and menuInside==0){ // increase 'menu' to go up in main menu
    menu--;
    updateMenu();
    delay(500);
    while (!digitalRead(upButton));
  }
  if (!digitalRead(upButton) and menuInside==2 and audiofile and menu2>1){ // increase 'menu2' to go up in saved recordings
    menu2--;
    recordHistory();
    delay(500);
    while (!digitalRead(upButton));
  }
  if (!digitalRead(selectButton) and menuInside==0 and menu==1){ // go to record action from main menu and start recording
    button();
    menuInside=1;
    updateMenu1();
    delay(500);
    while (!digitalRead(selectButton));
  }
  if (!digitalRead(selectButton) and menuInside==1){ //go to recording display from 'record' in main menu and stop recording
    button();
    menuInside=0;
    updateMenu();
    delay(500);
    while (!digitalRead(selectButton));
  }
  if (!digitalRead(selectButton) and menuInside==0 and menu==2){ //go to saved recordings from 'recordings' in main menu
    menuInside=2;
    recordHistory();
    delay(500);
    while (!digitalRead(selectButton));
  }
  if (!digitalRead(backButton) and menuInside==2){ // go back from saved recordings to 'recordings' in main meny
    if (audiofile){
      menu2=audiofile; 
    }
    menuInside=0;
    updateMenu();
    delay(500);
    while (!digitalRead(backButton));
  }
  if (!digitalRead(selectButton) and menuInside==2 and audiofile){ //select a saved audio file from saved recordings and play it
    menuInside=3;
    playmenu();
    delay(500);
    while (!digitalRead(selectButton));
  }
  if (!digitalRead(selectButton) and menuInside==3){ // stop playing the recording and go back to saved recording list
    menuInside=2;
    lcd.clear();
    lcd.print("Playing Stopped");
    delay(1000);
    //audio.pause();// stop playing
    recordHistory();
    delay(500);
    while (!digitalRead(selectButton));
  }
}
void updateMenu() {
  if (menu == 0) {
      menu = 1;
  }
   if (menu == 1) {
      lcd.clear();
      lcd.print(">>Record");
      lcd.setCursor(0, 1);
      lcd.print("  Recordings");
  }
   if (menu == 2) {
      lcd.clear();
      lcd.print("  Record");
      lcd.setCursor(0, 1);
      lcd.print(">>Recordings");
  }
   if (menu == 3) {
      menu=2;
   }
}
void updateMenu1() {
  if (menu2<=4){
    lcd.clear();
    lcd.print("----Recording---");
    lcd.setCursor(0, 1);
    lcd.print(">>Stop Recording");
  }
  else{
    menu2=4;
    lcd.clear();
    lcd.print("Capacity exceed");
    lcd.setCursor(0, 1);
    lcd.print(">>Back");
  }
}
void button() {
  while (i < 300000) {
    i++;
  }
  i = 0;
  if (menuInside==0) {
    audiofile++;
    menu2=2*audiofile-1;
    switch (audiofile) {
      case 1: audio.startRecording("1.wav", 16000, A0); break;
    }
  }
  else {
    switch (audiofile) {
      case 1: audio.stopRecording("1.wav"); break;
    }
  }
}


void recordHistory(){
  if (audiofile==0){
    lcd.clear();
    lcd.print("No Recordings");
  }
  if (menu2==1 and menu2<=2*audiofile) {
    lcd.clear();
    lcd.print("play>>---1.wav--");
    lcd.setCursor(0, 1);
    lcd.print("    >>-1mod.wav-");
  }
  if (menu2==2 and menu2<=2*audiofile ){
    lcd.clear();
    lcd.print("    >>---1.wav--");
    lcd.setCursor(0, 1);
    lcd.print("play>>-1mod.wav-");
  }
//  if (menu2==3 and menu2<=2*audiofile) {
//    lcd.clear();
//    lcd.print("play>>---2.wav--");
//    lcd.setCursor(0, 1);
//    lcd.print("    >>-2mod.wav-");
//  }
//  if (menu2==4 and menu2<=2*audiofile ){
//    lcd.clear();
//    lcd.print("   >>---2.wav--");
//    lcd.setCursor(0, 1);
//    lcd.print("play>>-2mod.wav-");
//  }
  if (menu2>3){
    menu2=2;
  }
  if (menu2>2*audiofile){
    menu2=2*audiofile-1;
  }
}


void playmenu(){
  if (menu2 == 1 and menu2<=2*audiofile) {
    lcd.clear();
    lcd.print("1.wav playing");
    lcd.setCursor(0, 1);
    lcd.print(">>>back");
    //player.setVolume(6);
    //player.play("1.wav");
  }
  if (menu2 == 2 and menu2<=2*audiofile ){
    downsample("1.wav","1mod.wav");
    lcd.clear();
    lcd.print("1mod.wav playing");
    lcd.setCursor(0, 1);
    lcd.print(">>>back");
    //player.setVolume(6);
    //player.play("1mod.wav");
  }
//  if (menu2 == 3 and menu2<=2*audiofile) {
//    lcd.clear();
//    lcd.print("2.wav playing");
//    lcd.setCursor(0, 1);
//    lcd.print(">>>back");
//    //player.setVolume(6);
//    //player.play("2.wav");
//  }
//  if (menu2 == 4 and menu2<=2*audiofile ){
//    downsample("2.wav","2mod.wav");
//    lcd.clear();
//    lcd.print("2mod.wav playing");
//    lcd.setCursor(0, 1);
//    lcd.print(">>>back");
//    //player.setVolume(6);
//    //player.play("2mod.wav");
//  }
}
void downsample(char* filename,char* out_name){
File myFile;
File outputFile;
unsigned long  i=0;
unsigned long  fileSize;
char *buff; 
SD.remove(out_name);
myFile = SD.open(filename);
fileSize=myFile.size();
outputFile = SD.open(out_name, FILE_WRITE);
buff=(char*)malloc(128); 
while (i!=80) {
  outputFile.write(myFile.read());
  i+=1;
}   
myFile.read(buff,128);
lcd.clear();
lcd.print("--Down Sampling-");
delay(500);
while (myFile.available()) {
  i+=128;
  for (int j=0;j<64;j++){
    buff[j]=buff[2*j];       
  }
  outputFile.write(buff,64);
  if(fileSize-i<128){
    break;
    }
   myFile.read(buff,128);
}
myFile.close();
outputFile.close();
lcd.clear();
lcd.print("--Down Sampled--");
delay(500);  
}

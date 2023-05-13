float lat = 3018.871986 ;
float lon = 3143.354092 ; 
void setup(){

    Serial.begin(9600);
    Serial2.begin(9600);
}

void loop(){

// lat = lat + .001 ;
// lon = lon + .001 ;
// Serial.println(String(lat)+","+String(lon));
// delay(1000);    
    while(Serial.available()){
        Serial2.write(Serial.read());
    }
    while(Serial2.available()){
        Serial.write(Serial2.read());
    }
}
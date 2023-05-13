#include "../inc/gps.h"
#include "../inc/lcd.h"
#include "../inc/uart.h"
#include "../inc/gpio.h"
#include "../inc/delay.h"
#include "../inc/distance.h"



int main(void){

    // intializations
    uart5_init();
    uart2_init();
    systick_init();
    portF_init();
    lcd_init();


    double lat ;  // current lat 
    double lon ;  // current lon
 
    double total_distance = 0 ; 

    char total_dis[10] ;
    char slat[6] ;
    char slon[6] ;

    double lon_end = 0 , lat_end = 0;
    double lon_start = 0 , lat_start = 0;
    double temp_lat = 0 , temp_lon = 0 ;
    int counter = 0 ;
    while(1){

        filter_incomings(&lat , &lon);
        if (lat == 0 || lon == 0){
            lcd_set_cursor(0,0);
            lcd_print("loading...");
        }
        else{

            lcd_clean();
            counter ++ ;

            if (!is_SW1_pressed()){
                // uart2_send_string("end saved \n");
                lon_end = lon ;
                lat_end = lat ;

                lcd_set_cursor(1,15);
                lcd_print("e");
                delay(200);
            }

            if (!is_SW2_pressed()){
                // uart2_send_string("start saved\n ");
                lon_start = lon ;
                lat_start = lat ;

                temp_lat = lat_start ; 
                temp_lon = lon_start ; 

                total_distance = 0 ;

                lcd_set_cursor(1,14);
                lcd_print("s");
                delay(200);
            }

            // update the total distance every 3 readings
            if (counter == 3){
                total_distance +=  compute_distance_haversine(temp_lat, temp_lon ,lat, lon );
                counter = 0 ;
                // shift the start 
                temp_lon = lon ; 
                temp_lat = lat ; 
            }

            double remaining_distance = compute_distance_haversine(lat , lon , lat_end, lon_end);

            // convert double to string 
            gcvt(total_distance , 10 , total_dis  ) ; 
            gcvt(lat            , 6  , slat       ) ; 
            gcvt(lon            , 6  , slon       ) ;
 
            // error due to drift
            if ( remaining_distance <= 3){

                set_led_value(GREEN_LED, LED_ON);
                set_led_value(BLUE_LED, LED_OFF);
                set_led_value(RED_LED, LED_OFF);
            }

            else if ( remaining_distance >= 3 &&  remaining_distance <= 7){

                set_led_value(BLUE_LED, LED_OFF);
                set_led_value(RED_LED, LED_ON);
                set_led_value(GREEN_LED, LED_ON);

                lcd_set_cursor(0,0);
                lcd_print(slat); 
                // delay(100);
        
                lcd_set_cursor(0,8);
                lcd_print(slon); 
                // delay(100);

            }

            else if (remaining_distance > 7){

                set_led_value(RED_LED, LED_ON);
                set_led_value(BLUE_LED, LED_OFF);
                set_led_value(GREEN_LED, LED_OFF);


                lcd_set_cursor(0,0);
                lcd_print(slat); 
                delay(100);
    
                lcd_set_cursor(0,8);
                lcd_print(slon); 
                delay(100);

            }

            lcd_set_cursor(1,0);
            lcd_print(total_dis); 
            delay(300);

        }

        delay(500);

    }

}

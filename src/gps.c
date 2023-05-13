#include "../inc/gps.h"

_Bool  stop = 1;
char gp[100];
int verbose = 1 ; 
// as stated above the protocol was 80 charachters we made it 100 for unexpexted situitions
// filter protocols to only get GGPGA and GPRMC
// 123456,UTC time,1latitude,2d,3Longitude,4D,5 ( for gps),7,8 ,9altit,10
//$GPGGA,202530.00,3003.919398,N,3116.71078,E,5,40,0.5,1097.36,M,-17.00,M,18,TSTR*61 //80 charachters
// 012345,time,vld,lat + Dir  ,long +dir   ,
//$GPRMC,210230,A,3855.4487,N,09446.0071,W,0.0,076.2,130495,003.8,E*69
void filter_incomings(double *lon,double* lat){

    int cnt = 0;
    char h;
    stop = 1  ;
    while (stop){

        h = uart5_receive();
        if (verbose) 
            uart2_send(h);
        gp[cnt++] = h;
        if (cnt == 6){

            if (gp[cnt - 2] == 'G' && gp[cnt - 1] == 'A'){

                // dummy function
                // uart2_send_string("first");
                stop=0;
                
                
            }

            else if (gp[cnt - 1] == 'C' && gp[cnt - 2] == 'M' ) {

                // dummy function 
                    // uart2_send_string("second");
                    stop=0;
                
            }

            else {
                // not the sentance we want 
                //     uart2_send_string("third");
                cnt = 0;
            }
        }
    }
    
    return;
}
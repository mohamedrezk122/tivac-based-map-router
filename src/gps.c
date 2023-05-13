#include "../inc/gps.h"
#include "../inc/distance.h"
#include "../inc/delay.h"

_Bool f = 1, stop = 1;
char gp[100]; 
double longr = 0 ,latit = 0;
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
    f = 1 ; 
    while (stop){

        h = uart5_receive();
        if (verbose) 
            uart2_send(h);
        gp[cnt++] = h;
        if (cnt == 6){

            if (gp[cnt - 2] == 'G' && gp[cnt - 1] == 'A'){

                // if (verbose) 
                    // uart2_send_string("first");
                get_sentence('A');
                *lon=longr;
                *lat=latit;
                return ;
            }

            else if (gp[cnt - 1] == 'C' && gp[cnt - 2] == 'M' ) {

                // if (verbose) 
                    // uart2_send_string("second");
                get_sentence('C');
                *lon=longr;
                *lat=latit;
                return ;
            }

            else {
                // if (verbose) 
                //     uart2_send_string("third");
                cnt = 0;
            }
        }
    }
    return;
}
void get_sentence(char c){

    int idx = 6;
    gp[idx] = uart5_receive();
    // if (verbose) 
        // uart2_send(gp[idx]);
    while (gp[idx] != '*'){

        idx++;
        gp[idx] = uart5_receive();
        // if (verbose) 
            // uart2_send(gp[idx]);
    }
    parse_sentence(c);
}
// we need idx : 2,3,4,5,9
/*
 *1=latitude
 *3=longitude
 *8=altitude
 */
void parse_sentence(char c){

    char values[14][20];
    int idx = 0,comidx=0,charidx=0;;
    while(gp[idx] != '*'){

        if(gp[idx]==','){

            comidx++;
            charidx=0;
            idx++;
        }
        values[comidx][charidx]=gp[idx];
        idx++;
        charidx++;
    }
    memset(gp ,  NULL , 100);

    if (c == 'A'){
        //check it's gps data
        if (values[6][0] == '1'){
            // getting values
            latit = atof(values[2]);
            latit = (values[3][0] == 'S') ? -1 * (latit) : (latit);
            longr = atof(values[4]);
            longr = (values[5][0] == 'W') ? -1 * (longr) : (longr);
        }
        f = 0;
    }
    else{
        //check if it's valid 
        if (values[2][0] == 'A'){

            // getting values
            latit = atof(values[3]);
            longr = (values[4][0] == 'S') ? -1 * (latit) : (latit);
            longr = atof(values[5]);
            longr = (values[6][0] == 'W') ? -1 * (longr) : (longr);
        }

        f = 0;
    }
}


// $GPRMC,210230,A,3004.90274 ,N,3114.75944,E,0.0,076.2,130495,003.8,E*69
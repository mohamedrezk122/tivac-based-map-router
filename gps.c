#include "./gps.h"
// dummy until implemented
_Bool f = 1, stop = 1;
char getChar()
{
    char c;
    return c;
}
char gp[100]; 
// as stated above the protocol was 80 charachters we made it 100 for unexpexted situitions
// filter protocols to only get GGPGA and GPRMC
// 123456,UTC time,1latitude,2d,3Longitude,4D,5 ( for gps),7,8 ,9altit,10
//$GPGGA,[0]202530.00,[1]5109.0262,[2]N,[3]11401.8407,[4]W,[5]5,[6]40,[7]0.5,[8]1097.36,[9]M,[10]-17.00,[11]M,[12]18,[13]TSTR*61 //80 charachters
// 012345,time,vld,lat + Dir  ,long +dir   ,
//$GPRMC,210230,A,3855.4487,N,09446.0071,W,0.0,076.2,130495,003.8,E*69
void filterGA(void)
{
    int cnt = 0;
    char c;
    while (stop)
    {
        c = getChar();
        gp[cnt++] = c;
        if (cnt == 6)
        {
            if (gp[cnt - 2] == 'G' && gp[cnt - 1] == 'A')
            {
                getStr('A');
                stop = f ? 1 : 0;
            }
            else if (gp[cnt - 1] == 'C')
            {
                getStr('C');
                stop = f ? 1 : 0;
            }
            else
            {
                cnt = 0;
            }
        }
    }
}
void getStr(char c)
{

    int idx = 6;
    gp[idx] = getChar();
    while (gp[idx] != '*')
    {
        idx++;
        gp[idx] = getChar();
    }
    params(c);
}
// we need idx : 2,3,4,5,9
/*
 *1=latitude
 *3=longitude
 *8=altitude
 */
void params(char c)
{
    char values[14][20];
    int idx = 0;
    char *token = strtok(gp, ",");
    while (token != NULL)
    {
        strcpy(values[idx++], token); // may change based on realtime using
        token = strtok(NULL, ",");
    }
    if (c == 'A')
    {
        if (values[6][0] == '1')//check it's gps data
        {
            // getting values
            latit = atof(values[2]);
            latit = (values[3][0] == 'S') ? -1 * latit : latit;
            lon = atof(values[4]);
            lon = (values[5][0] == 'W') ? -1 * lon : lon;
            altit = atof(values[9]);

            // dividing into degrees and minutes
            latit /= 100;
            degt = (latit - (int)latit) * 100;
            lon /= 100;
            degl = (lon - (int)lon) * 100;
        }
        else
            f = 0;
    }
    else
    {
        if (values[2][0] == 'A')//check if it's valid
        {
            // getting values
            latit = atof(values[3]);
            latit = (values[4][0] == 'S') ? -1 * latit : latit;
            lon = atof(values[5]);
            lon = (values[6][0] == 'W') ? -1 * lon : lon;
            altit = 0;

            // dividing into degrees and minutes
            latit /= 100;
            degt = (latit - (int)latit) * 100;
            lon /= 100;
            degl = (lon - (int)lon) * 100;
        }
        else
            f = 0;
    }
}

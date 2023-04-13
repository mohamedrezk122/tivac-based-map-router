#include"./gps.h"
//dummy until implemented
_Bool f=1;
int j=0;
char send[80]="$GPGGA,202530.00,5109.0262,N,11401.8407,W,1,40,0.5,1097.36,M,-17.00,M,18,TSTR*61";
//filter protocols to only get GGPGA
//123456,UTC time,1latitude,2d,3Longitude,4D,5,7,8 ,9altit,10
//$GPGGA,[0]202530.00,[1]5109.0262,[2]N,[3]11401.8407,[4]W,[5]5,[6]40,[7]0.5,[8]1097.36,[9]M,[10]-17.00,[11]M,[12]18,[13]TSTR*61 //80 charachters
void filterGA(void){
    int cnt=0;
    while(cnt != 7){
        char c=send[j];
        j++;
        switch (c)
        {
            case '$':
                cnt++;
                printf("%d%c\n",j,c);
                break;
            case 'G':
                cnt = (cnt==1 ? 2 : (cnt==3 ? 4: (cnt==4 ? 5:0))) ;//G appears at idx 2,4,5 as shown above
                printf("%d%c\n",j,c);
                break;
            case 'P':
                cnt = cnt==2?3:0;
                printf("%d%c\n",j,c);
                break;
            case 'A':
                cnt = cnt==5?6:0;
                printf("%d%c\n",j,c);
                break;
            case ',':
                printf("%d%c%d\n",j,c,cnt);
                if(cnt==6) getStr();

                if(f==1) cnt=7;
                break;

        }
        if(j>7)break;
    }
}
void getStr(){
    char gp[100];//as stated above the protocol was 80 charachters we made it 100 for unexpexted situitions
    int idx=0;
    char c=send[j++];
    gp[idx]=c;
    while(c !='*'){
        idx++;
        c=send[j];j++;
       // printf("%d",idx);
        gp[idx]=c;
        
        
    }
    params(gp);
}
//we need idx : 1,2,3,4,8
/*
*1=latitude
*3=longitude
*8=altitude
*/
void params(char gp[]){
    char values[13][20];int idx=0;
    char * token = strtok(gp,",");
    while (token != NULL)
    {
        strcpy(values[idx++] ,token);//may change based on realtime using
        token=strtok(NULL,",");
    }
    if(*values[5]=='1'){
        //getting values
        latit=atof(values[1]);
        lon=atof(values[3]);
        altit=atof(values[8]);
        //dividing into degrees and minutes
        latit/=100;
        degt=(latit-(int)latit)*100;
        lon/=100;
        degl=(lon-(int)lon)*100;
    }else f=0;
    
}
int main(void){
    filterGA();
    printf("%lf\n",lon);


}
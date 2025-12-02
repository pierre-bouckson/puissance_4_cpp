#include "ia_easy.h"

static int victory(int id, int buffer[6][7]);


int ia_easy::check_V_in_1(int buffer[6][7])
{

    for(int k=0;k<7;k++)
    {
        for(int i=5;i>=0;--i){
                if(buffer[i][k] == 0){
                        buffer[i][k] = 2;
                        int q = i;

                        int V_ia = victory(2, buffer);
                        if(V_ia!=0){
                                buffer[q][k] = 0;
                                return k;                       
                        }
                        buffer[q][k] = 0;
                }
        }
    }
    for(int k=0;k<7;k++)
   {
        for(int i=5;i>=0;--i){
                if(buffer[i][k] == 0){
                        buffer[i][k] = 1;
                        int q = i;

                        int V_ia = victory(1, buffer);
                        if(V_ia!=0){
                                buffer[q][k] = 0;
                                return k;                       
                        }
                        buffer[q][k] = 0;
                }
        }
    }
    srand(time(NULL));
    return int(rand()%7);
}


static int victory(int id,int buffer[6][7]) {
        int cons_h = 0;
        int cons_v = 0;
        //Hozizontal O
        for(int i=0;i<6;i++)
        {
                for(int j=0;j<7;j++){
                        if(buffer[i][j] == id){
                                cons_h++;
                        }else{cons_h=0;}
                        if(cons_h==4){
                                return 1;
                        }
                }
                cons_h = 0;
        }
        //Vertical O
        for(int j=0;j<7;j++)
        {
                for(int i=0;i<6;i++){
                        if(buffer[i][j] == id){
                                cons_v++;
                        }else{cons_v=0;}
                        if(cons_v==4){
                                return 1;
                        }
                }
                cons_v = 0;
        }
        //Diagonal '/' O
        for(int i=3;i<=6;i++)
        {
                for(int j=0;j<=7-4;j++){
                        if(buffer[i][j]==id){
                                if(buffer[i-1][j+1]==id && buffer[i-2][j+2]==id
                                && buffer[i-3][j+3]==id)
                                {return 1;}
                        }
                }
        }
        //Diagonal '\' O
        for(int i=0;i<=6-4;i++)
        {
                for(int j=0;j<=7-4;j++){
                        if(buffer[i][j]==id){
                                if(buffer[i+1][j+1]==id && buffer[i+2][j+2]==id
                                && buffer[i+3][j+3]==id)
                                {return 1;}
                        }
                }
        }
        return 0;
}

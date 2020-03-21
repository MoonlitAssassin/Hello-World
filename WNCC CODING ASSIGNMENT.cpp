#include <simplecpp>
#include <stdio.h>
#include <stdlib.h>

int main(){
FILE *fil;                      //opening the timestat file
fil=fopen("timestat.txt","r");
if(fil==NULL) {                 //report error if file not found
    printf("error in opening file\n");
    exit(EXIT_FAILURE);}
char line[20];                  //to get each line of the document
int i=0,l=i/3, coun[3]={0};        //i will keep track of number of runs, l will keep track of array indices and coun will be used at the end.
double s[3]={0},d[3]={0},sd[3]={0},avg[3]={0};  // s=sum,d is an array used to clculate deviation, sd is the array rep standard deviation
double time[3][100];                           //multi dimensional matrix, first row will store real , 2nd-user and 3rd-system times
while(fgets(line,20,fil)!=NULL) {              //extracting lines from file one by one
    if(i%3==2) time[i%3][l]=(line[4]-48)*60+line[6]-48+(line[8]-48)*0.1+(line[9]-48)*0.01+(line[10]-48)*0.001; // getting value of time
    else time[i%3][l]=(line[5]-48)*60+line[7]-48+(line[9]-48)*0.1+(line[10]-48)*0.01+(line[11]-48)*0.001;
    //cout<<time[i%3][l]<<endl;
    s[i%3]+=time[i%3][l];      // finding sum and sum of squares simultaneously to help find avg and std deviation.
    d[i%3]+=pow(time[i%3][l],2);
    i++;
    }

for(int n=0;n<3;n++){
    avg[n]=s[n]/10;   // finding mean value
    float x= d[n]/10;
    float y= pow(avg[n],2);
    sd[n]=pow(x-y,0.5); // finding standard deviation using reduced formula.
    }
for(int j=0; j<(3*i);j++){
    int l=j/3;
    int k= j%3;
    if(time[k][l]<=(avg[k]+sd[k])&&time[k][l]>=(avg[k]-d[k]))   //finding no. of values within given limits for eah of the three times
        coun[k]++;
    }
cout<<"number of runs:"<<i<<endl<<"Average Time Statistics"<<endl;
cout<<"real "<<avg[0]<<" user "<<avg[1]<<" sys "<<avg[2]<<endl<<"Standard deviation of Time Statistics"<<endl;
cout<<"real "<<sd[0]<<" user "<<sd[1]<<" sys "<<sd[2]<<endl<<"Number of runs within given limits"<<endl;
cout<<"real "<<coun[0]<<" user "<<coun[1]<<" sys "<<coun[2]<<endl;

}



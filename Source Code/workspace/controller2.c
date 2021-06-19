#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include <sys/types.h>
#include <sys/file.h>
#include <unistd.h>
#include <string.h>

#define MEM_SIZE 100

 
int Random(int m){
     srand((unsigned)time(NULL));
     return rand()%m;
}
void minuxSlashN(char data[]) { 
char *find = strchr(data, '\n'); 
if(find) *find = '\0'; 

}

int readChipID(int chipID[]){
	FILE *fp_in;
    	int int_chipID;
    	char ch_chipID[3];
	int i=0;
	if((fp_in = fopen("chipID.txt", "r")) == NULL)
		return -1;
	if (0 == flock(fileno(fp_in), LOCK_EX)){
		 while(!feof(fp_in)){
     			fgets(ch_chipID,10,fp_in);
			minuxSlashN(ch_chipID);
			int_chipID=atoi(ch_chipID);
			chipID[i]=int_chipID;
			++i;
		}
		fclose(fp_in); 		
     		flock(fileno(fp_in), LOCK_UN);
	}
    


}
int bench_WriteFile(char *fileName,char*stringLine){
	
	FILE * fp_out;
	if((fp_out = fopen(fileName, "a+")) == NULL)
		return -1;
	if (0 == flock(fileno(fp_out), LOCK_EX)){
		
     		fputs(stringLine, fp_out);	
     		fputs("\n", fp_out);
     		fclose(fp_out);
	     	flock(fileno(fp_out), LOCK_UN);
	}
}
inline int popnet_traceTransfer(int numOfChip){
	
	int chipID[numOfChip];	
	readChipID(chipID);

	FILE *fp_in;
    	int x,y;
    	char ch_eachLine[30];
	
	char delim[2] = " ";

	if((fp_in = fopen("bench", "r")) == NULL)
		return -1;
	if (0 == flock(fileno(fp_in), LOCK_EX)){
	
		system("mkdir -p benchtrace");
		 while(!feof(fp_in)){
			
			fgets(ch_eachLine,30,fp_in);
			minuxSlashN(ch_eachLine);
			char ch_eachLine_bak[30];
			strcpy (ch_eachLine_bak,ch_eachLine);
			char *s = strdup(ch_eachLine);
			char *token;
			int count=0;
			for (token = strsep(&s, delim); token != NULL;token = strsep(&s, delim)) {        
				if(count==1){
					x=atoi(token);
				}
				else if(count==2){
					y=atoi(token);
					char ch_eachBenchName[20]="./benchtrace/bench.";
					char string_x[4];
					char string_y[4];
					sprintf(string_x, "%d", x);
					sprintf(string_y, "%d", y);
					strcat(ch_eachBenchName,string_x);
					strcat(ch_eachBenchName,".");
					strcat(ch_eachBenchName,string_y);
					bench_WriteFile(ch_eachBenchName,ch_eachLine_bak);
				}
				++count;
    			}
		}
		
		system("sort -n -k 1 bench -o bench");
		system("cp bench ./benchtrace/ && cp -r ./benchtrace ../popnet-master && ../popnet-master/popnet -A 4 -c 2 -V 3 -B 12 -O 12 -F 4 -L 1000 -T 20000 -r 1 -I ../popnet-master/benchtrace/bench -R 0");
		
		system("rm -rf ../workspace/benchtrace");
		
		fclose(fp_in);
	     	flock(fileno(fp_in), LOCK_UN);
	}
    	
}
int fileRowCount(char * file_name){
  FILE *fp;
  int flag = 0, file_row = 0, count = 0;

  if((fp = fopen(file_name, "r")) == NULL)
    return -1;
if (0 == flock(fileno(fp), LOCK_EX)){
  while(!feof(fp))
  {
    flag = fgetc(fp);
    if(flag == '\n')
      count++;
  }
  file_row = count ; 
  fclose(fp);
  flock(fileno(fp), LOCK_UN);
}
  return file_row;
}

int syn_fileSearch(char  file_name[], char *chip_ID){
     FILE *fp_in;
     
     if((fp_in=fopen(file_name,"r"))==NULL){
          printf("cannot open\n");
          exit(0);
     }
      int exist_flag=0;
	
     while(!feof(fp_in))
    {	
	char chipID_syn[10];
        fgets(chipID_syn,10,fp_in);
	minuxSlashN(chipID_syn);
	
        if(strcmp(chip_ID,chipID_syn)==0)
        {	
		exist_flag=1;break;	
	}
    }
     fclose(fp_in);
     return exist_flag;
}
int syn_fileReadFirstLine(char * file_name){
     FILE *fp_in;
     int int_time_syn;
     char ch_time_syn[10];
     if((fp_in = fopen(file_name, "r")) == NULL)
    	return -1;
if (0 == flock(fileno(fp_in), LOCK_EX)){
     fgets(ch_time_syn,10,fp_in);
     int_time_syn=atoi(ch_time_syn);	
     fclose(fp_in);
     flock(fileno(fp_in), LOCK_UN);
}
     return int_time_syn;

}
int synchronization(float time,char * chipID,int numOfChip){

	int time_int=(int)time;

	char filename_string[64];
	strcpy (filename_string,"../workspace/synchronization/");
	strcat (filename_string,"synchronization.txt");

	int syn_time=syn_fileReadFirstLine(filename_string);
	
	int exist_flag=syn_fileSearch(filename_string,chipID);
	int writeFail_flag=0;

	if(exist_flag==1){}
	else{/*write the file*/
		FILE *fp_out;
		if ((fp_out = fopen((filename_string), "aw+")) == NULL)
      			writeFail_flag=1;
   		if (0 == flock(fileno(fp_out), LOCK_EX)){
			
			fputs(chipID, fp_out);
			fputs("\n", fp_out);
			fclose(fp_out);
			flock(fileno(fp_out), LOCK_UN);
		}
		else{
      			printf("lock failed\n");
    		}
	}


	if(time_int<syn_time)return 0;
	else {

		int row=fileRowCount(filename_string);

		if(row-1<numOfChip)return 0;
		else {
			system("cd ../workspace/synchronization && rm ../workspace/synchronization/synchronization.txt && touch ../workspace/synchronization/synchronization.txt");
			char string_newSynTime[10];
			sprintf(string_newSynTime, "%d", syn_time+2000);
			FILE *fp_out = NULL;
  			fp_out = fopen(filename_string, "w+");
			fputs(string_newSynTime, fp_out);
			fputs("\n", fp_out);
			fclose(fp_out);
			return 1;
		
		}
	
	}
}

int numOfChip_readFile(){
     FILE *fp_in;
     int numOfChip;
     char ch_numOfChip[10];
     if((fp_in=fopen("numOfChip.txt","r"))==NULL){
          printf("cannot open numOfChip.txt\n");
          exit(0);
     }
     fgets(ch_numOfChip,2,fp_in);
     numOfChip=atoi(ch_numOfChip);
     fclose(fp_in);
     return numOfChip;
}

void IOFormatTransfer(int num,int  xy[2]){
xy[0]=num/10;
xy[1]=num%10;
}

void stringFormatTransfer(int xy_i[2],int xy_o[2],int time,char traceString[]){
	char string_xy_i[5];
	char string_xy_o[5];
	
	char time_string[10];
	string_xy_i[0]=' ';
	string_xy_i[1]=(char)(xy_i[0]+'0');
	string_xy_i[2]=' ';
	string_xy_i[3]=(char)(xy_i[1]+'0');
	string_xy_i[4]='\0';	

	string_xy_o[0]=' ';
	string_xy_o[1]=(char)(xy_o[0]+'0');
	string_xy_o[2]=' ';
	string_xy_o[3]=(char)(xy_o[1]+'0');
	string_xy_o[4]='\0';
	
	char blank[]=" ";
	char fv[]="5";
	sprintf(time_string, "%d", time);
	sprintf(traceString,"%s%s%s%s%s",time_string,string_xy_i,string_xy_o,blank,fv);
}

int trace_writeFile(int inputChipID, int outputChipID,int time,char * file_name){
	FILE * fp_out;
	int writeFail_flag;
	if ((fp_out = fopen((file_name), "a")) == NULL)
      			writeFail_flag=1;
	if (0 == flock(fileno(fp_out), LOCK_EX)){
		int xy_i[2];
		IOFormatTransfer(inputChipID,xy_i);
		int xy_o[2];
		IOFormatTransfer(outputChipID,xy_o);
		char traceString[30];
		stringFormatTransfer(xy_i,xy_o,time,traceString);
		
     		fputs(traceString, fp_out);
			
		fputs("\n", fp_out);
		fclose(fp_out);
		flock(fileno(fp_out), LOCK_UN);
	}
}



/*argv[1] is the chip ID, argv[2] is the time, argv[3] is read or write*/
/*The chip ID is obtained by the process ID*/
int main(int argc,char * argv[]){
   	
    
	
	int time=atoi(argv[2]);
	int readOrWrite=atoi(argv[3]);

	int numOfChip=numOfChip_readFile();
	int chipID[numOfChip];	
	readChipID(chipID);

	int inputChipID,outputChipID;
	
	if(readOrWrite==1){
		inputChipID=atoi(argv[1]);
		int i=Random(numOfChip);
		if(outputChipID==inputChipID){
			i=(i+1)%numOfChip;
		}
		outputChipID=chipID[i];
	}
	else{			
		inputChipID=atoi(argv[4]);
		outputChipID=atoi(argv[1]);
	}
	
	int syn_symbol=synchronization(time,argv[1],numOfChip);

	char bench[20]="bench";	
	char pre_bench[20]="pre_bench";
	
	if(!syn_symbol)	
		trace_writeFile(inputChipID,outputChipID,time,bench);
	else{
		trace_writeFile(inputChipID,outputChipID,time,pre_bench);
		system("cat pre_bench > bench && rm pre_bench");
		popnet_traceTransfer(numOfChip);
	}
	
	system("sort -n -k 1 bench -o bench");
	char cmd[256];
	if(readOrWrite==1){
		system("tail -1 bench >> pre_memory.txt");
	}
	sprintf(cmd,"tail -%d pre_memory.txt > memory.txt", MEM_SIZE);
	system(cmd);
	int pop_mark;    
	
	
    
}

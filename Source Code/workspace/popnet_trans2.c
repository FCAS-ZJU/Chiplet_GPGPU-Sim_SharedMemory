#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include <sys/types.h>
#include <sys/file.h>
#include <unistd.h>
#include <string.h>
#define MEM_SIZE 1000
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




inline int bench_WriteFile(char *fileName,char*stringLine){
	
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
		system("cp bench ./benchtrace/ && cp -r ./benchtrace ../popnet-master && ../popnet-master/popnet -A 9 -c 2 -V 3 -B 12 -O 12 -F 4 -L 1000 -T 2000000 -r 1 -I ../popnet-master/benchtrace/bench -R 0");
		
		system("rm -rf ../workspace/benchtrace");
		
		fclose(fp_in);
	     	flock(fileno(fp_in), LOCK_UN);
	}
    	
}

int main(int argc,char * argv[]){
		system("sort -n -k 1 bench -o bench");
		popnet_traceTransfer(9);
	
}

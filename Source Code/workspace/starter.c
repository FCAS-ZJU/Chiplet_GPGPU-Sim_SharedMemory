#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include <sys/types.h>
#include <dirent.h>
inline void popnet_trans(int argc,char * argv[]){
	char cmd[512]="nohup ./P ";
	int i;
	
	for(i=1;i<argc;++i){
		strcat(cmd,argv[i]);
		strcat(cmd," ");
	}
	strcat(cmd," &");
	system(cmd);	
	
}
inline void Mesh_chipID_writeFile(int size){
	FILE * fp_out;
	if((fp_out=fopen("chipID.txt","a"))==NULL){
		printf("Cannot open this file");
		exit(0);
	}
     
	     
	char pid_t_i_string[4];
	sprintf(pid_t_i_string, "%d%d\n", (size-1)/2,(size-1)/2);
	fputs(pid_t_i_string,fp_out);
	int i;
	for(i=0;i<size;++i){
		int j;
		for(j=0;j<size;++j){
			if((i==(size-1)/2)&&(j==(size-1)/2))continue;

			char pid_t_i_string_i[4];
			sprintf(pid_t_i_string_i, "%d%d\n", i,j);
			fputs(pid_t_i_string_i,fp_out);
		}	
	}
	fclose(fp_out); 

}

inline void One_punch_chipID_writeFile(int size){
	FILE * fp_out;
	if((fp_out=fopen("chipID.txt","a"))==NULL){
		printf("Cannot open this file");
		exit(0);
	}
     
	     
	
	int i;
	for(i=0;i<size;++i){
		int j;
		for(j=0;j<size;++j){
			if((i==(size-1)/2)&&(j==(size-1)/2))continue;

			char pid_t_i_string_i[4];
			sprintf(pid_t_i_string_i, "%d%d\n", i,j);
			fputs(pid_t_i_string_i,fp_out);
		}	
	}
	char pid_t_i_string[4];
	sprintf(pid_t_i_string, "%d%d\n", (size-1)/2,size);
	fputs(pid_t_i_string,fp_out);

	fclose(fp_out); 

}

void topology(char * topo_type,int argc){
	system ("rm chipID.txt");
	if (strcmp("mesh",topo_type)==0){
		switch(argc){
			case 1:{
				Mesh_chipID_writeFile(1);
			break;
			}
			case 2 ... 4:{
				Mesh_chipID_writeFile(2);
			break;
			}
			case 5 ... 9:{
				Mesh_chipID_writeFile(3);
			break;
			}
			case 10 ... 16:{
				Mesh_chipID_writeFile(4);
			break;
			}
			case 17 ... 25:{
				Mesh_chipID_writeFile(5);
			break;
			}
			case 26 ... 36:{
				Mesh_chipID_writeFile(6);
			break;
			}
			case 37 ... 49:{
				Mesh_chipID_writeFile(7);
			break;
			}
			case 50 ... 64:{
				Mesh_chipID_writeFile(8);
			break;
			}
			case 65 ... 81:{
				Mesh_chipID_writeFile(9);
			break;
			}
			case 82 ... 100:{
				Mesh_chipID_writeFile(10);
			break;
			}	
		}		
	}
	else if (strcmp("one_punch",topo_type)==0){
		switch(argc){
			case 1:{
				One_punch_chipID_writeFile(1);
			break;
			}
			case 2 ... 4:{
				One_punch_chipID_writeFile(2);
			break;
			}
			case 5 ... 9:{
				One_punch_chipID_writeFile(3);
			break;
			}
			case 10 ... 16:{
				One_punch_chipID_writeFile(4);
			break;
			}
			case 17 ... 25:{
				One_punch_chipID_writeFile(5);
			break;
			}
			case 26 ... 36:{
				One_punch_chipID_writeFile(6);
			break;
			}
			case 37 ... 49:{
				One_punch_chipID_writeFile(7);
			break;
			}
			case 50 ... 64:{
				One_punch_chipID_writeFile(8);
			break;
			}
			case 65 ... 81:{
				One_punch_chipID_writeFile(9);
			break;
			}
			case 82 ... 100:{
				One_punch_chipID_writeFile(10);
			break;
			}	
		}		
	}

}
int find_pid_by_name( char* ProcName, int* foundpid);
int benchmarks [64];
void createProcess(int argc,char * argv[]){
int i=1;


 for (; i < argc; i++){
	if (strcmp("AES",argv[i])==0)
        system("cd ../ispass2009-benchmarks-master/AES &&  nohup ../ispass2009-benchmarks-master/bin/release/AES e 256 ../ispass2009-benchmarks-master/AES/data/key256.txt ../ispass2009-benchmarks-master/AES/data/key256.txt &");
	else if(strcmp("BFS",argv[i])==0)
        system("cd ../ispass2009-benchmarks-master/BFS && nohup ../ispass2009-benchmarks-master/bin/release/BFS ../ispass2009-benchmarks-master/BFS/data/graph65536.txt &");
	else if(strcmp("CP",argv[i])==0)
        system("cd ../ispass2009-benchmarks-master/CP && nohup ../ispass2009-benchmarks-master/CP/benchmarks/cp/build/cuda_short/cp &");
        else if(strcmp("DG",argv[i])==0)
        system("cd ../ispass2009-benchmarks-master/DG && nohup ../ispass2009-benchmarks-master/bin/release/DG ../ispass2009-benchmarks-master/data/cubeK268.neu &");
        else if(strcmp("LIB",argv[i])==0)
        system("cd ../ispass2009-benchmarks-master/LIB && nohup ../ispass2009-benchmarks-master/bin/release/LIB &");
        else if(strcmp("LPS",argv[i])==0)
        system("cd ../ispass2009-benchmarks-master/LPS && nohup ../ispass2009-benchmarks-master/bin/release/LPS &");
        else if(strcmp("MUM",argv[i])==0)
        system(" cd ../ispass2009-benchmarks-master/MUM && nohup ../ispass2009-benchmarks-master/bin/release/MUM ../ispass2009-benchmarks-master/MUM/data/NC_003997.20k.fna home/xu/ispass2009-benchmarks-master/MUM/data/NC_003997_q25bp.50k.fna &");
        else if(strcmp("NN",argv[i])==0)
        system("cd ../ispass2009-benchmarks-master/NN && nohup ../ispass2009-benchmarks-master/bin/release/NN 28 &");
        else if(strcmp("NQU",argv[i])==0)
        system("cd ../ispass2009-benchmarks-master/NQU && nohup ../ispass2009-benchmarks-master/bin/release/NQU &");
        else if(strcmp("RAY",argv[i])==0)
        system("cd ../ispass2009-benchmarks-master/RAY && nohup ../ispass2009-benchmarks-master/bin/release/RAY 256 256 &");
        else if(strcmp("STO",argv[i])==0)
        system("cd ../ispass2009-benchmarks-master/STO && nohup ../ispass2009-benchmarks-master/bin/release/STO &");
        else if(strcmp("WP",argv[i])==0)
        system("cd ../ispass2009-benchmarks-master/WP && nohup echo \"10 ./data/\" | ../bin/release/WP &");
		else if(strcmp("MM",argv[i])==0)
        system("cd ../ispass2009-benchmarks-master/MM && nohup  ../ispass2009-benchmarks-master/bin/release/MM &");
	
	
    }


}
inline void pidChipID_writeFile(int pid_t_i,int benchmark){
     FILE * fp_out;
     if((fp_out=fopen("pidChipMap.txt","a"))==NULL){
          printf("Cannot open this file");
          exit(0);
     }
     char pid_t_i_string[4];
     sprintf(pid_t_i_string, "%d\n", pid_t_i);
     fputs(pid_t_i_string,fp_out);
     fclose(fp_out); 

}

/*void pidChipID_map(int argc,char * argv[]){
   int i=1;

  sleep(argc*5);
    for (; i < argc; i++){
	int k=i-1,mark=0;
	for(;k>0;--k){
		if(strcmp(argv[k],argv[i])==0){
			mark=1;	
		}	
	}	

	if(mark==0){
		printf("%s\n",argv[i]);
		int  rv;
		int pid_t[128];	
		rv = find_pid_by_name(argv[i],pid_t);
		
		if(!rv) {
			int j=0;
			for(; pid_t[j] != 0; j++){
			
   		             	pidChipID_writeFile(pid_t[j],benchmarks[i-1]);
				printf("%d\t%s\n",pid_t[j],argv[i]);
			}
        	}
    	}
    }

}*/

void pidChipID_map(int argc,char * argv[]){
	system("rm pidChipMap.txt");
	int i;	
	for (i=1; i < argc; i++){
		
		int k=i-1,mark=0;
		for(;k>0;--k){
			if(strcmp(argv[k],argv[i])==0){
				mark=1;	
			}	
		}
		if(mark==0){	
			char cmd[256];
			//char cmd2[256];
			sprintf(cmd, "ps -ef | grep \"%s\" |grep -v grep | grep -v \"./S\" |awk '{print $2}' >>pidChipMap.txt", argv[i]);
			//sprintf(cmd2, "ps -ef | grep \"%s\" |grep -v grep | grep -v \"./S\"", argv[i]);
			system(cmd);
			//system(cmd2);
		}
	}
}


void initial_synchronization(){
	
	system("cd ../workspace/synchronization && rm ../workspace/synchronization/synchronization.txt && touch ../workspace/synchronization/synchronization.txt");
	char filename_string[64];
	strcpy (filename_string,"../workspace/synchronization/");
	strcat (filename_string,"synchronization.txt");	
	char string_newSynTime[10];
	sprintf(string_newSynTime, "%d", 2000);
	FILE *fp_out = NULL;
  	fp_out = fopen(filename_string, "w+");
	fputs(string_newSynTime, fp_out);
	fputs("\n", fp_out);
	fclose(fp_out);

}

inline void numOfChip_writeFile(int numOfChip){
     
     FILE * fp_out;
     if((fp_out=fopen("numOfChip.txt","w"))==NULL){
          printf("Cannot open this file");
          exit(0);
     }
     char numOfChip_string[2];
     sprintf(numOfChip_string, "%d", numOfChip);
     fputs(numOfChip_string,fp_out);
     fclose(fp_out); 
}
/*argv[1] is the number of chips, the other argv are the benchmark names.
1.AES 2.BFS 3.CP 4.DG 5.LIB 6.LPS 7.MUM 8.NN 9.NQU 10.RAY 11.STO 12.WP
*/
int main(int argc,char * argv[]){
    system("rm bench memory.txt pre_memory.txt");
    int i=0;
    for (; i < 64; i++){
        benchmarks[i] = 0;  
    }
    i=1;
    for (; i < argc-1; i++){
	if (strcmp("AES",argv[i])==0)
        benchmarks[i-1]=1;
	else if(strcmp("BFS",argv[i])==0)
        benchmarks[i-1]=2;
	else if(strcmp("CP",argv[i])==0)
        benchmarks[i-1]=3;
        else if(strcmp("DG",argv[i])==0)
        benchmarks[i-1]=4;
        else if(strcmp("LIB",argv[i])==0)
        benchmarks[i-1]=5;
        else if(strcmp("LPS",argv[i])==0)
        benchmarks[i-1]=6;
        else if(strcmp("MUM",argv[i])==0)
        benchmarks[i-1]=7;
        else if(strcmp("NN",argv[i])==0)
        benchmarks[i-1]=8;
        else if(strcmp("NQU",argv[i])==0)
        benchmarks[i-1]=9;
        else if(strcmp("RAY",argv[i])==0)
        benchmarks[i-1]=10;
        else if(strcmp("STO",argv[i])==0)
        benchmarks[i-1]=11;
        else if(strcmp("WP",argv[i])==0)
        benchmarks[i-1]=12;
		else if(strcmp("MM",argv[i])==0)
        benchmarks[i-1]=13;
	else benchmarks[i-1]=0;
    }
    system("touch delay_of_chiplet.txt");
    system("echo 0 > delay_of_chiplet.txt");
    numOfChip_writeFile(argc-2);
    createProcess(argc-1,argv);
    pidChipID_map(argc-1,argv);
    topology(argv[argc-1],argc-1);
    initial_synchronization();
   // popnet_trans(argc-1,argv);
}

int find_pid_by_name( char* ProcName, int* foundpid)
{
        DIR             *dir;
        struct dirent   *d;
        int             pid, i;
        char            *s;
        int pnlen;
 
        i = 0;
        foundpid[0] = 0;
        pnlen = strlen(ProcName);
 
        /* Open the /proc directory. */
        dir = opendir("/proc");
        if (!dir)
        {
                printf("cannot open /proc");
                return -1;
        }
 
        /* Walk through the directory. */
        while ((d = readdir(dir)) != NULL) {
 
                char exe [PATH_MAX+1];
                char path[PATH_MAX+1];
                int len;
                int namelen;
 
                /* See if this is a process */
                if ((pid = atoi(d->d_name)) == 0)       continue;
 
                snprintf(exe, sizeof(exe), "/proc/%s/exe", d->d_name);
                if ((len = readlink(exe, path, PATH_MAX)) < 0)
                        continue;
                path[len] = '\0';
 
                /* Find ProcName */
                s = strrchr(path, '/');
                if(s == NULL) continue;
                s++;
 
                /* we don't need small name len */
                namelen = strlen(s);
                if(namelen < pnlen)     continue;
 
                if(!strncmp(ProcName, s, pnlen)) {
                        /* to avoid subname like search proc tao but proc taolinke matched */
                        if(s[pnlen] == ' ' || s[pnlen] == '\0') {
                                foundpid[i] = pid;
                                i++;
                        }
                }
        }
 
        foundpid[i] = 0;
        closedir(dir);
 
        return  0;
 
}

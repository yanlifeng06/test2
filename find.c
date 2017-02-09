#include <stdio.h>  
#include <stdlib.h>  
#include <dirent.h>  
#include <string.h>  
#include <sys/stat.h>  
#include <errno.h>       //for errno  
#include <fcntl.h> 

void readdir_fun(char *path,int classlevel);

int main(int argc, char **argv)
{
	char *pathvar;  
  
        pathvar = getenv( "HOME" );  //获取环境变量HOME路径  
        if( pathvar != NULL )  
        {  
            printf("Home path variable is: %s\n",pathvar);  
	    printf("getclose\n");
        }  
        readdir_fun("/data/ccos",0);  
        return 0; 	
}

void readdir_fun(char *path,int classlevel)  
{  
        DIR *dirp;//主目录  
        char longpath[128];  
        struct dirent *dp;  
        struct stat buff;  
  
        if((dirp=opendir(path)) == NULL){
		    exit(-1);  	
		}
  
        while((dp=readdir(dirp))!=NULL)//一级  
        {  
                if (dp->d_name[0]=='.')  
                        continue;  
                memset(longpath,'\0',sizeof(longpath));  
          /*strncpy(longpath,path,strlen(path));  
                strncat(longpath,"/",1);  
                strncat(longpath,dp->d_name,strlen(dp->d_name));*/  
                sprintf(longpath,"%s/%s",path,dp->d_name);  
                if (lstat(longpath,&buff)<0)  
                {  
                        printf("Error lstat %s,errno code is %d,err message is '%s'\n",dp->d_name,errno,strerror(errno));  
                        continue;  
                }  
                if (S_ISREG(buff.st_mode)){  
                        printf("第%d级目录结构是:%s, \n",classlevel,dp->d_name);  
                        continue;  
                        }  
                if (S_ISDIR(buff.st_mode))  
                {  
                                if (classlevel > 0 )  
                                        {  
                                                int i;  
                                                for(i=0; i<classlevel; i++){  
                                                printf("yes\n");
                                                        }  
                                        }  
                                printf("第%d级目录结构是%s,文件类型是%d,文件索引是%d,文件偏移是%d  \n",classlevel,dp->d_name,dp->d_type,dp->d_ino,dp->d_off);  
                                ++classlevel;  
                        readdir_fun(longpath,classlevel);  
                        --classlevel;  
                        usleep(100);  
                 }  
        }  
        closedir(dirp);  
}  

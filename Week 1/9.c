#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc , char * argv[])
{
	int f_rd = 0;
	int f_wrt = 0;

	char buf = '\0';

	if((f_rd = open(argv[1] , O_RDONLY)) < 0){
		perror("file error:");
		exit(1);
	}else{
		if((f_wrt = open(argv[2] , O_CREAT|O_WRONLY|O_EXCL , S_IRWXU)) < 0){
			perror("output file already exists :\n");
			exit(1);
		}else{
			printf("%d\n",f_wrt);
			while(read(f_rd , &buf , 1) > 0){
				if(-1 == write(f_wrt , &buf , 1)){
					perror("write error\n");
					exit(1);
				}
			}
		}
	}
	close(f_rd);
	close(f_wrt);

	return 0;
}
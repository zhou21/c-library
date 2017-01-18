#include<stdio.h>
#include<string.h>
int size = 2048;

char *read_line(FILE *fp, char *username)
{
	char line[2048] = "";
	char *stop = fgets(line, size, fp);
	sscanf(line,"%[^,]", username);
	return stop;
}
FILE * open_file(char *path)
{
	FILE *fp = fopen(path, "r");
	return fp;
}

int main(int agrc, char *agrv[])
{
	if (agrc <= 1){
		printf("<sorry, you have not input user list file>\n");
		return -1;
	}
	char *user_path = agrv[1];
	FILE *fp = open_file(user_path);
	char username[1024] = "";
	char *stop = NULL;

	do{
		stop = read_line(fp, username);
		if (stop != NULL){
			printf("<username>:%s\n", username);
		}
	}while(stop != NULL);
}

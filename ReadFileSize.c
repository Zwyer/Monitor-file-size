#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ENTRIES 1000
int num_entries = 0;
char *entries[MAX_ENTRIES];
void ChooseFile();
void delay(long int time);
int main() {
	DIR *dir;
	struct dirent *entry;
	printf("WRITE BY ZWY\n说明：请确保本软件位于你要监控的文件所在目录\n使用时请输入要监控的文件序号并按下回车\n可用于：监控zlibrary桌面端下载进度\n按下回车开始读取当前文件目录");
	fflush(stdin);
	char c=getchar();
	dir = opendir(".");
	if (dir == NULL) {
		perror("opendir");
		return 1;
	}

	while ((entry = readdir(dir)) != NULL) {
		if (num_entries >= MAX_ENTRIES) {
			fprintf(stderr, "Too many entries\n");
			break;
		}
		if (!strcmp(entry->d_name , ".") || !strcmp(entry->d_name , ".."))
		{//.和..符号不处理
			continue;
		}
		entries[num_entries] = malloc(strlen(entry->d_name) + 1);
		if (entries[num_entries] == NULL) {
			fprintf(stderr, "Out of memory\n");
			break;
		}
		strcpy(entries[num_entries], entry->d_name);
		num_entries++;
	}

	closedir(dir);

	for (int i = 0; i < num_entries; i++) {
		printf("文件序号：%d 文件名：%s\n", i,entries[i]);
		free(entries[i]);
	}
	ChooseFile();
	return 0;
}

void ChooseFile(){
	printf("\n请输入要监视的文件序号：");
	int choice;
	fflush(stdin);
	scanf("%d",&choice);
	while(choice>=num_entries||choice<0){
		printf("\n请重试，序号不正确：");
		fflush(stdin);
		scanf("%d",&choice);
	}
	FILE* fp=fopen(entries[choice],"r");
	int num[5],m;
	memset(num,0,sizeof(num));
	for(;;){
		fseek(fp,0,SEEK_SET);
		fseek(fp,0,SEEK_END);
		long int size=ftell(fp);
		printf("当前文件大小：%ld字节\n",size);
		delay(9999999999);
		if(num[0]==0){
			num[0]=size;
		}
		if(size!=num[m]){
			num[0]=size;
			m=0;
		}else if(size==num[m]){
			m++;
			num[m]=size;
		}
		if(m==5){
			printf("下载完毕！\n按回车键退出");
			fflush(stdin);
			char x=getchar();
			return 0;
		}
}
}
void delay(long int time){
	for(time;time>0;time--){
		int i=0;
		for(i;i++;i<1000){

		}
	}
}

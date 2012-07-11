/**
 * File: main.c
 * Description: about.pkg file generator.
 * Date: 05.07.2012
 * Author: thg2oo6
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "package/package.h"

#define SPK_VERSION "0.1.1"

void error_cmd(const char* msg, int error);
void create_by_cmd(int argc, char* argv[]);

void usage();
int position_cmd(char* cmd, int argc, char* argv[]);

int main(int argc, char* argv[]){
	if(argc==3 && strcmp(argv[1],"-r")==0){
		pkg p;
		read_file(argv[2],&p);
		print_package(p);
		exit(0);
	}
	if(argc==2 && strcmp(argv[1],"-#")==0){
		printf("[apkg] Version: %s\n",SPK_VERSION);
		exit(0);
	}

	if(argc>=2){
		create_by_cmd(argc,argv);
		exit(0);
	}

	usage();
	return 0;
}

void usage(){
	printf("apkg - about.pkg file generator\n");
	printf("Version: %s\n",SPK_VERSION);
	printf("[usage]: apkg -p package -v version -t type [-h header]\n");
	printf("         apkg -r about.pkg\n\n");
	printf("Options:\n");
	printf("      -p package   = defines the name of the package\n");
	printf("      -v version   = defines the version of the package\n");
	printf("      -t type      = defines the type of the package (read TYPES)\n");
	printf("      -h header    = defines the header of the package (read HEADERS)\n");
	printf("      -r about.pkg = reads an about.pkg file\n\n");
	printf("Other options:\n");
	printf("      -? = displays the usage\n");
	printf("      -# = version\n");
}

int position_cmd(char* cmd, int argc, char* argv[]){
	int i;
	for(i=1;i<argc;i++)
		if(strcmp(argv[i],cmd)==0)
			return i;
	return -1;
}

void error_cmd(const char* msg, int error){
	printf("%s\n",msg);
	exit(error);
}

void create_by_cmd(int argc, char* argv[]){
	printf("...about.pkg generation started...\n");

	int pp;		//Package position
	int vp;		//Version position
	int tp;		//Type position
	int hp;		//Header position

	pp=position_cmd("-p",argc,argv);
	if(pp==-1) error_cmd("Package not defined",1);

	vp=position_cmd("-v",argc,argv);
	if(vp==-1) error_cmd("Version not defined",2);

	tp=position_cmd("-t",argc,argv);
	if(tp==-1) error_cmd("Type not defined",3);

	hp=position_cmd("-h",argc,argv);

	if(pp+1==vp||pp+1==tp||pp+1==hp||pp+1==argc) error_cmd("Package name not defined",4);
	if(vp+1==pp||vp+1==tp||vp+1==hp||vp+1==argc) error_cmd("Version number not defined",5);
	if(tp+1==pp||tp+1==vp||tp+1==hp||tp+1==argc) error_cmd("Package type not defined",6);

	char header[40];
	if(hp==-1) strcpy(header,"SPK");
	if(hp+1==pp||hp+1==vp||hp+1==tp||hp+1==argc) strcpy(header,"SPK");
	strcpy(header,argv[hp+1]);

	pkg p = create_package(argv[pp+1],argv[vp+1],argv[tp+1],header);
	print_package(p);
	create_file("about.pkg",p);

	printf("...about.pkg generation done...\n");

}

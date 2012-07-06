/**
 * File: package.c
 * Description: Contains the definition for the pkg element.
 * Data: 05.07.2012
 * Author: thg2oo6
 */

#include "package.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

#define TEST_HEADER_KEY "4n4@M3r3"

header_t header_type(const char* header){
	if(strcmp(header,"SCPK")==0) return SCPK;
	if(strcmp(header,"SDPK")==0) return SDPK;
	if(strcmp(header,"SRPK")==0) return SRPK;
	if(strcmp(header,"SIPK")==0) return SIPK;
	if(strcmp(header,"SSPK")==0) return SSPK;

	if(strcmp(header,"SDCPK")==0) return SDCPK;
	if(strcmp(header,"SDRPK")==0) return SDRPK;
	if(strcmp(header,"SDIPK")==0) return SDIPK;
	if(strcmp(header,"SDSPK")==0) return SDSPK;

	return SPK;
}

const header_s header_string(const int header){
	switch(header){
		case SCPK: return "SCPK"; break;
		case SDPK: return "SDPK"; break;
		case SRPK: return "SRPK"; break;
		case SIPK: return "SIPK"; break;
		case SSPK: return "SSPK"; break;

		case SDCPK: return "SDCPK"; break;
		case SDRPK: return "SDRPK"; break;
		case SDIPK: return "SDIPK"; break;
		case SDSPK: return "SDSPK"; break;
	}

	return "SPK";
}

pkg create_package(const char* package, const char* version, const char* type, const char* header){
	pkg ret;

	strcpy(ret.package,package);
	strcpy(ret.version,version);
	strcpy(ret.type,type);
	ret.header=header_type(header);

	return ret;
}

char* write_package(pkg package){
	char* s=(char*)malloc(1000*sizeof(char));
	sprintf(s,"%s\n%s|%s|%s\n",header_string(package.header),package.package,package.version,package.type);
	return s;
}

void create_file(const char* filename, pkg p){
	int fd=open(filename,O_WRONLY|O_CREAT,0644);
	char hdr[20]; strcpy(hdr,TEST_HEADER_KEY);
	write(fd,&hdr,sizeof(hdr));
	write(fd,&p,sizeof(pkg));
	close(fd);
}

void read_file(const char* filename, pkg* p){
	int fd=open(filename,O_RDONLY);

	char hdr[20];
	read(fd,&hdr,sizeof(hdr));
	if(strcmp(hdr,TEST_HEADER_KEY)!=0){
		printf("Error reading file!\n");
		exit(9);
	}

	read(fd,p,sizeof(pkg));
	close(fd);
}

header_b compare_packages(pkg A,pkg B){
	if(A.header!=B.header) return 0;
	if(strcmp(A.package,B.package)!=0) return 0;
	if(strcmp(A.version,B.version)!=0) return 0;
	if(strcmp(A.type,B.type)!=0) return 0;

	return 1;
}

void print_package(pkg p){
	printf("Package: %s\n",p.package);
	printf("Version: %s\n",p.version);
	printf("Type:    %s\n",p.type);
	printf("Header:  %s\n",header_string(p.header));
}

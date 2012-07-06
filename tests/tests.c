/**
 * File: tests.c
 * Description: The testing program for package library.
 * Date: 05.07.2012
 * Author: thg2oo6
 */
#include "../package/package.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>

pkg kernel_test_pkg();
pkg gcc_test_pkg();
pkg spm_test_pkg();
pkg spk_test_pkg();

int main(){
	pkg a_test, b_test, c_test, d_test;

	a_test=kernel_test_pkg();
	b_test=gcc_test_pkg();
	c_test=spm_test_pkg();
	d_test=spk_test_pkg();

	create_file("tests/kernel.pkg",a_test);
	create_file("tests/gcc.pkg",b_test);
	create_file("tests/spm.pkg",c_test);
	create_file("tests/spk.pkg",d_test);

	read_file("tests/kernel.pkg",&a_test);
	read_file("tests/gcc.pkg",&b_test);
	read_file("tests/spm.pkg",&c_test);
	read_file("tests/spk.pkg",&d_test);

	assert(compare_packages(a_test,kernel_test_pkg())==1);
	assert(compare_packages(b_test,gcc_test_pkg())==1);
	assert(compare_packages(c_test,spm_test_pkg())==1);
	assert(compare_packages(d_test,spk_test_pkg())==1);

	return 0;
}

pkg kernel_test_pkg(){
	pkg p;

	strcpy(p.package,"Kernel");
	strcpy(p.version,"3.2.1");
	strcpy(p.type,"kernel");
	p.header=header_type("SSPK");

	return p;
}

pkg gcc_test_pkg(){
	pkg p;

	strcpy(p.package,"GCC");
	strcpy(p.version,"4.6.1");
	strcpy(p.type,"core");
	p.header=header_type("SCPK");

	return p;
}

pkg spm_test_pkg(){
	pkg p;

	strcpy(p.package,"Spark Packet Manager");
	strcpy(p.version,"1.0.1");
	strcpy(p.type,"core");
	p.header=header_type("SIPK");

	return p;
}

pkg spk_test_pkg(){
	pkg p;

	strcpy(p.package,"Test Package");
	strcpy(p.version,"1001");
	strcpy(p.type,"others");
	p.header=header_type("SPK");

	return p;
}

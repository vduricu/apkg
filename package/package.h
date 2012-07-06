/**
 * File: package.h
 * Description: Contains the prototypes of the pkg element.
 * Data: 05.07.2012
 * Author: thg2oo6
 */

#ifndef PACKAGE_H_
#define PACKAGE_H_

#define SPKGLIB_VERSION "0.1.1"

typedef int header_t;
typedef char* header_s;
typedef int header_b;

/**
 * The structure used to describe a package.
 *
 * package - the name of the package
 * version - the version of the package
 * type - the type of the content (see TYPES)
 * header - the header of the package (see HEADERS)
 */
typedef struct{
	char package[255];	//Package
	char version[64];	//Version of the package
	char type[32];		//The type of the package
	header_t header;
}pkg;

#define SPK 0			//Default package
#define SCPK 1			//Core package
#define SDPK 2			//Downloadable package
#define SRPK 3			//Runnable package
#define SIPK 4			//Installable package
#define SSPK 5			//Source package

#define SDCPK 6			//Downloadable + Core Package
#define SDRPK 7			//Downloadable + Runnable Package
#define SDIPK 8			//Downloadable + Installable package
#define SDSPK 9			//Downloadable + Source package

/**
 * Returns the type of the header as header_t type.
 *
 * header - the header defined as string
 */
extern header_t header_type(const char*);

/**
 * Returns the type of the header as header_s type.
 *
 * header - the header defined as integer
 */
extern const header_s header_string(const int);

/**
 * Creates a pkg element describing a package.
 *
 * package - the name of the package
 * version - the version of the package
 * type - the type of the package
 * header - the header of the package (as string)
 */
extern pkg create_package(const char*,
						  const char*,
						  const char*,
						  const char*);

/**
 * Returns the string representation of a pkg element.
 *
 * package - the package to be represented
 */
extern char* write_package(pkg);


/**
 * Creates the about.pkg file describing the package.
 *
 * filename - the filename to be created
 * package - the package to be written
 */
extern void create_file(const char*, pkg);

/**
 * Reads the about.pkg file describing the package.
 *
 * filename - the filename to be read
 * package - the package where to data to be put
 */
extern void read_file(const char*, pkg*);

/**
 * Compares 2 packages. Returns 0 if A != b, 1 otherwise.
 *
 * A - the first package to be compared
 * B - the second package to be compared
 */
extern header_b compare_packages(pkg,pkg);

/**
 * Displays informations about a package.
 *
 * p - the package to be displayed
 */
void print_package(pkg);

#endif /* PACKAGE_H_ */

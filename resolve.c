/* 
 * Name: Adam Van Hine
 * Description: This program performs the resolution task of a linker.
 *              It takes as input a list of .o files and archive files
 *              and keeps track of undefined and defined symbols.  All
 *              symbols in a .o file are added to one of the two lists.
 *              Archived object files are handled a little differently.
 *              If there is a symbol that is currently undefined, but defined
 *              in a object file within an archive, then all symbols in that
 *              archived object file are added to one of the two lists; 
 *              otherwise, no symbols from that archive member are added.  
 *              Members of an archive are visited repeatedly until there are 
 *              no changes in the lists of defined and undefined symbols.
 *
 *              If at some point there is an attempt to add a second strong
 *              symbol to the defined symbols list, then an error message is
 *              displayed indicating the multiple definition.
 *
 *              At the end of the process, the program looks to make sure that
 *              the main function is defined and if not, an error message is
 *              displayed.  Next, the program prints out the entries of the 
 *              undefined symbols list with an error message for each one.
 */

#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bool.h"

static bool isArchive(char * filename);
static bool isObjectFile(char * filename);
static void handleObjectFile(char * filename);
static void handleArchive(char * filename);

int main(int argc, char * argv[])
{
    int i, istat; 
    struct stat stFileInfo;

    if (argc <= 1)
    {
       printf("resolve: no input files\n");
       exit(1);
    }
    for (i = 1; i < argc; i++)
    {
        istat = stat(argv[i], &stFileInfo);
        //if istat is 0 then file exists
        if (istat == 0)
        {
            if (!isObjectFile(argv[i]) && !isArchive(argv[i]))
            {
                printf("%s: file not recognized\n", argv[i]);
            } else {
                if (isArchive(argv[i])) handleArchive(argv[i]);
                if (isObjectFile(argv[i])) handleObjectFile(argv[i]);
            }
        } else {
            printf("%s: file not found\n", argv[i]);
        }
    }
}

void handleObjectFile(char * filename)
{
    //you need to write the code to handle an object file
    //take this printf out 
    printf("object file: %s\n", filename);
}


void handleArchive(char * filename)
{
    //you need to write the code to handle an archive file
    //take this printf out 
    printf("archive file: %s\n", filename);
}

/* 
 * function: isArchive
 * description: This function takes as input a c-string and returns
 *              true if the c-string ends with a .a extension.
 * input: filename 
 * returns: 1 or 0
 */
bool isArchive(char * filename)
{
    int len = strlen(filename);
    if (len < 3) 
        return false;
    if (filename[len - 2] != '.')
        return false;
    if (filename[len-1] != 'a')
        return false;
    return true;
}

/* 
 * function: isObjectFile
 * description: This function takes as input a c-string and returns
 *              true if the c-string ends with a .o extension.
 * input: filename 
 * returns: 1 or 0
 */
bool isObjectFile(char * filename)
{
    int len = strlen(filename);
    if (len < 3) 
        return false;
    if (filename[len - 2] != '.')
        return false;
    if (filename[len-1] != 'o')
        return false;
    return true;
}

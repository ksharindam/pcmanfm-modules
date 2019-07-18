#include <stdlib.h>
#include <arpa/inet.h>  // ntohl function
#include "imagesize.h"


#define readbyte(a,b) do if(((a)=getc((b))) == EOF) return 0; while (0)
#define readword(a,b) do { int cc_=0,dd_=0; \
                          if((cc_=getc((b))) == EOF \
        		  || (dd_=getc((b))) == EOF) return 0; \
                          (a) = (cc_<<8) + (dd_); \
                          } while(0)


int jpegsize(FILE * infile, int *image_width, int *image_height) {
    int marker=0;
    int dummy=0;
    fseek(infile, 0, SEEK_SET);
    if ( getc(infile) != 0xFF || getc(infile) != 0xD8 )
        return 0;

    for (;;)
    {
        int discarded_bytes=0;
        readbyte(marker,infile);
        while (marker != 0xFF) {
            discarded_bytes++;
            readbyte(marker,infile);
        }
        do readbyte(marker,infile); while (marker == 0xFF);

        if (discarded_bytes != 0) return 0;

        switch (marker) {
            case 0xC0:
            case 0xC1:
            case 0xC2:
            case 0xC3:
            case 0xC5:
            case 0xC6:
            case 0xC7:
            case 0xC9:
            case 0xCA:
            case 0xCB:
            case 0xCD:
            case 0xCE:
            case 0xCF: {
                readword(dummy,infile);	/* usual parameter length count */
                readbyte(dummy,infile);
                readword((*image_height),infile);
                readword((*image_width),infile);
                readbyte(dummy,infile);
                return 1;
            }
            case 0xDA:
            case 0xD9:
                return 0;
            default: {
                int length;
                readword(length,infile);

                if (length < 2) return 0;
                length -= 2;
                while (length > 0) {
                  readbyte(dummy, infile);
                  length--;
                }
            }
            break;
        }   // end switch
    }
}


int pngsize(FILE *file, int *width, int *height)
{
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    if (size < 24) return 0;
    char imgW[4];
    char imgH[4];
    fseek(file, 16, SEEK_SET);
    fread(imgW,4,1,file);
    fseek(file, 20, SEEK_SET);
    fread(imgH,4,1,file);
    *width = ntohl(*((int*)imgW));
    *height = ntohl(*((int*)imgH));
    return 1;
}

int isJpeg(FILE *file)
{
    fseek(file, 0, SEEK_SET);
    return (getc(file)== 0xFF && getc(file) == 0xD8);
}

int isPng(FILE *file)
{
    fseek(file, 0, SEEK_SET);
    return (getc(file)== 0x89 && getc(file) == 0x50 &&
            getc(file)== 0x4E && getc(file) == 0x47);
}

int imgsize(FILE *file, int *width, int *height)
{
    if (isJpeg(file))
        return jpegsize(file, width, height);
    else if (isPng(file))
        return pngsize(file, width, height);
    else return 0;
}

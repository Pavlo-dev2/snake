#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <stdint.h>

int drawrect(unsigned char r, unsigned char g, unsigned char b, char x, char y, int un, int fb0);
int* info(int fb0);


//info struckts
static struct fb_var_screeninfo vinfo;
static struct fb_fix_screeninfo finfo;

int main() {
    int fb = open("/dev/fb0", O_RDWR);
    if (fb == -1) {
        perror("Не вдалося відкрити /dev/fb0");
        return 1;
    }
    
    info(fb);

    sleep(1);
    int a = 1;
    /*drawrect(255, 0, 0, 0, 0, a, fb);
    drawrect(0, 255, 0, 1, 0, a, fb);
    drawrect(0, 0, 255, 2, 0, a, fb);
    drawrect(255, 255, 0, 0, 1, a, fb);
    drawrect(255, 0, 255, 1, 1, a, fb);
    drawrect(0, 255, 255, 2, 1, a, fb);
    drawrect(255, 255, 255, 0, 2, a, fb);
    drawrect(0, 0, 0, 1, 2, a, fb);
    drawrect(128, 128, 128, 2, 2, a, fb);*/

    drawrect(0, 0, 255, 0, 0, a, fb);
    //drawrect(0, 255, 0, 1, 0, a, fb);
    //drawrect(255, 255, 0, 0, 1, a, fb);
    //drawrect(255, 0, 0, 1, 1, a, fb);

    close(fb);
    return 0;
}


//funktion to draw a square
int drawrect(unsigned char r, unsigned char g, unsigned char b, char x, char y, int un, int fb0)
{

	//get infos
	if (ioctl(fb0, FBIOGET_VSCREENINFO, &vinfo) == -1 || ioctl(fb0, FBIOGET_FSCREENINFO, &finfo) == -1)
	{
		perror("Error while opening fb0");
		close(fb0);
		return 1;
	}

	//make fb0 a pointer
	long screensize = finfo.smem_len;
	uint8_t *fbp = (uint8_t*)mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fb0, 0);
	if (fbp == MAP_FAILED)
	{
		perror("Mmap failed");
		close(fb0);
		return 1;
	}

	long xdif, ydif;
	xdif = (vinfo.xres - ((float)((x+1.0)/un)*vinfo.yres))/2;//diferense x
	ydif = (vinfo.yres - ((float)(y+1)/un*vinfo.yres))/2;//diferense y
	
	long feldcords[4] = {0};//xstart, xend, ystart, yend, in the midle of the screan;
	feldcords[0] = (vinfo.xres - (float)vinfo.yres)/2.0;
	feldcords[1] = feldcords[0] + vinfo.yres;
	feldcords[3] = (vinfo.yres - (float)vinfo.yres)/2.0;
	feldcords[4] = feldcords[3] + vinfo.yres;
	printf("3: %lu\n4: %lu\n", feldcords[3], feldcords[4]);
	sleep(0.5);


	for (float ay = (float)y/un * vinfo.yres + ydif; ay < (float)(y+1)/un*vinfo.yres + ydif; ay++)
	{
		for (float ax = ((float)x/un) * vinfo.yres + xdif; ax < (float)(x+1)/un * vinfo.yres + xdif; ax++)
		{
            		long location = (ax + vinfo.xoffset) * (vinfo.bits_per_pixel / 8)
			+ (ay + vinfo.yoffset) * finfo.line_length;
			
			if (vinfo.bits_per_pixel == 32)
			{
				fbp[location] = b;
				fbp[location+1] = g;
				fbp[location+2] = r;
				fbp[location+3] = 0;
			}
		}
	}
	munmap(fbp, screensize);
}

int* info(int fb0)
{
	//get infos
	if (ioctl(fb0, FBIOGET_VSCREENINFO, &vinfo) == -1 || ioctl(fb0, FBIOGET_FSCREENINFO, &finfo) == -1)
	{
		perror("Error while opening fb0");
		close(fb0);
		return NULL;
	}
	
	printf("vinfo.xres: %f\nvinfo.yres: %f\n", (float) vinfo.xres, (float) vinfo.yres);
	printf("finfo.smem_len: %f\n", (float) finfo.smem_len);
	printf("vinfo.xoffset: %f\nvinfo.yoffset: %f\n", (float) vinfo.xoffset, (float) vinfo.yoffset);
	printf("vinfo.xbits_per_pixel: %f\nvinfo.byts_per_pixel: %f\n", (float) vinfo.bits_per_pixel, (float) vinfo.bits_per_pixel/8);
	printf("finfo.line_length: %f\n\n", (float) finfo.line_length);
}

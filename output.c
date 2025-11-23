#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <stdint.h>

int drawrect(unsigned char r, unsigned char g, unsigned char b, char x, char y, int un, int fb0);
int clear(unsigned char r, unsigned char g, unsigned char b, int fb0);

//info struckts
static struct fb_var_screeninfo vinfo;
static struct fb_fix_screeninfo finfo;

/*int main() {
    int fb = open("/dev/fb0", O_RDWR);
    if (fb == -1) {
        perror("Не вдалося відкрити /dev/fb0");
        return 1;
    }
    
    int a = 5;
    drawrect(255, 0, 0, 0, 0, a, fb);
    drawrect(0, 255, 0, 1, 0, a, fb);
    drawrect(0, 0, 255, 2, 0, a, fb);
    drawrect(255, 255, 0, 0, 1, a, fb);
    drawrect(255, 0, 255, 1, 1, a, fb);
    drawrect(0, 255, 255, 2, 1, a, fb);
    drawrect(255, 255, 255, 0, 2, a, fb);
    drawrect(0, 0, 0, 1, 2, a, fb);
    drawrect(128, 128, 128, 2, 2, a, fb);
    sleep(1);

    close(fb);
    return 0;
}*/


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

	float sty = (float)y/un * vinfo.yres;
	float edy = (float)y/un * vinfo.yres + vinfo.yres/(float)un;
	
	float stx = (float)x/un * vinfo.yres;
	//float stx = (float)x/un * vinfo.yres;
	float edx = (float)x/un * vinfo.yres + vinfo.yres/(float)un;
	//float dif = (edx-stx)/2;
	//stx = stx + (screensize/2-dif);
	//edx = edx + (screensize/2-dif);

	//for (float ay = (float)y/un * vinfo.yres; ay < (float)y/un*vinfo.yres + vinfo.yres/(float)un; ay++)
	for (float ay = sty; ay < edy; ay++)
	{
		//for (float ax = (float)x/un* vinfo.yres; ax < (float)x/un*vinfo.yres + vinfo.yres/(float)un; ax++)
		for (float ax = stx; ax < edx; ax++)
		{
			//printf("In cycle 2\n");	
            		long location = (ax + vinfo.xoffset) * (vinfo.bits_per_pixel / 8)
			+ (ay + vinfo.yoffset) * finfo.line_length;
			
			if (vinfo.bits_per_pixel == 32)
			{
				//printf("lol\n");
				//printf("in condition\n");
				fbp[location] = b;
				fbp[location+1] = g;
				fbp[location+2] = r;
				fbp[location+3] = 0;
			}
		}
	}
	munmap(fbp, screensize);
	return 0;
}

int clear(unsigned char r, unsigned char g, unsigned char b, int fb0)
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
	
	for (long ap = 0; ap < screensize; ap+=vinfo.bits_per_pixel/8)
	{
		fbp[ap] = b;
		fbp[ap+1] = g;
		fbp[ap+2] = r;
		fbp[ap+3] = 0;
	}
	munmap(fbp, screensize);
	return 0;

}

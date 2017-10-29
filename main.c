#include <stdarg.h>
#include "include/libswscale/swscale.h"
#include <stdio.h>     /* for printf */
#include <stdlib.h>    /* for exit */
#include <unistd.h>    /* for getopt */
#include <getopt.h>

/**
 * Helper functions for testing
 */
void check_inputs(char* src_file, char* dst_file, int src_width, int src_height, int dst_width, int dst_height);


int main(int argc, char **argv) 
{
	static struct option long_options[] =
	{
		{"src",  required_argument, 0, 's'},
		{"dst",  required_argument, 0, 'd'},
		{"sw",   required_argument, 0, 'a'},
		{"sh",   required_argument, 0, 'b'},
		{"dw",   required_argument, 0, 'c'},
		{"dh",   required_argument, 0, 'f'},
		{0, 0, 0, 0}
	};
	int c;
	
	char* src_file = NULL;
	char* dst_file = NULL;
	int src_width = 0, src_height = 0;
	int dst_width = 0, dst_height = 0;

	/* getopt_long stores the option index here. */
	int option_index = 0;
	while ( (c = getopt_long (argc, argv, "abc:d:f:s:", long_options, &option_index)) != -1 ) {
		switch (c)
		{
			case 0:
				break;
			case 's':
				src_file = optarg;
				break;
			case 'd':
				dst_file = optarg;
				break;
			case 'a':
				src_width = atoi(optarg);
				break;
			case 'b':
				src_height = atoi(optarg);
				break;
			case 'c':
				dst_width = atoi(optarg);
				break;
			case 'f':
				dst_height = atoi(optarg);
				break;
		}
	}

	// check_inputs(src_file, dst_file, src_width, src_height, dst_width, dst_height);

	// size for yuv buffer
	const int read_size = src_width * src_height * 3 / 2; 
	const int write_size = dst_width * dst_height * 3 / 2; 

	struct SwsContext *img_convert_ctx; 
	uint8_t *inbuf[4]; 
	uint8_t *outbuf[4];

	// setup variables
	int inlinesize[4] = {src_width, src_width/2, src_width/2, 0}; 
	int outlinesize[4] = {dst_width, dst_width/2, dst_width/2, 0};

	uint8_t in[src_width * src_height * 3 >> 1]; 
	uint8_t out[dst_width * dst_height * 3 >> 1];

	FILE *fin = fopen(src_file, "rb"); 
	FILE *fout = fopen(dst_file, "wb");

	if(fin == NULL) { 
		printf("open input file %s error.\n", src_file); 
		return -1; 
	}

	if(fout == NULL) { 
		printf("open output file %s error.\n", dst_file); 
		return -1; 
	}

	inbuf[0] = malloc(src_width * src_height); 
	inbuf[1] = malloc(src_width * src_height >> 2); 
	inbuf[2] = malloc(src_width * src_height >> 2); 
	inbuf[3] = NULL;

	outbuf[0] = malloc(dst_width * dst_height); 
	outbuf[1] = malloc(dst_width * dst_height >> 2); 
	outbuf[2] = malloc(dst_width * dst_height >> 2); 
	outbuf[3] = NULL;

	// Initialize convert context
	img_convert_ctx = sws_getContext(
		src_width,
		src_height,
		AV_PIX_FMT_YUV420P, 
		dst_width,
		dst_height,
		AV_PIX_FMT_YUV420P,
		SWS_POINT, 
		NULL, NULL, NULL
	);

	if(img_convert_ctx == NULL) { 
		fprintf(stderr, "Cannot initialize the conversion context!\n"); 
		return -1; 
	}

	fread(in, 1, read_size, fin);

	memcpy(inbuf[0], in, src_width * src_height); 
	memcpy(inbuf[1], in + src_width * src_height, src_width * src_height >> 2); 
	memcpy(inbuf[2], in + (src_width * src_height * 5 >> 2), src_width * src_height >> 2);

	// start sws_scale 
	sws_scale(
		img_convert_ctx,
		(const uint8_t * const*) inbuf,
		inlinesize,
		0,
		src_height,
		outbuf,
		outlinesize
	);

	memcpy(out, outbuf[0], dst_width * dst_height); 
	memcpy(out + dst_width * dst_height, outbuf[1], dst_width * dst_height >> 2); 
	memcpy(out + (dst_width * dst_height * 5 >> 2), outbuf[2], dst_width * dst_height >> 2);

	fwrite(out, 1, write_size, fout);

	// release the ConvertContext
	sws_freeContext(img_convert_ctx);

	fclose(fin); 
	fclose(fout);

	return 0;
}

void check_inputs(char* src_file, char* dst_file, int src_width, int src_height, int dst_width, int dst_height)
{
	printf("Read src_file: %s\n", src_file);
	printf("Read dst_file: %s\n", dst_file);
	printf("Read src_width: %i\n", src_width);
	printf("Read src_height: %i\n", src_height);
	printf("Read dst_width: %i\n", dst_width);
	printf("Read dst_height: %i\n", dst_height);
}
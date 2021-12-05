#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>

// Thanks to Nathanfenner on Reddit for helping with the array access part.

typedef enum {false, true} bool;

int main(int argc, char* argv[])
{
	bool quit = false;

	// Little or Big Endian?
	int Endian_test = 1;
	if (*(char*)&Endian_test == 1)
	{
		printf("Little-Endian\n\n");
	}
	else
	{
		printf("Big-Endian\n\n");
	}

	// The easiest way to delve into separating a Uint32 into four Uint 8 "sub variables", independently initialized.
	Uint32 main_variable = 0;  // Create the Uint32 variable
	Uint32* ptr_main_variable = &main_variable; // Get a pointer to the Uint32 variable
	Uint8* channels = (Uint8*)ptr_main_variable; // Create a Uint8 pointer to the address of the first byte of the Uint32
	
	// These "channels" will now act as an array of four bytes to the Uint32

	channels[0] = 0x3D;
	channels[1] = 0xF1;
	channels[2] = 0x0A;
	channels[3] = 0x2B;

	printf("channel 0      : 0x%02x\n", channels[0]);
	printf("channel 1      : 0x%02x\n", channels[1]);
	printf("channel 2      : 0x%02x\n", channels[2]);
	printf("channel 3      : 0x%02x\n", channels[3]);
	printf("Concatenated to: 0x%08x\n\n", main_variable);

	// Now, the same thing for an array. To make it interesting, a dynamically allocated array. Fixed arrays handled the same way.
	bool array_created = false;
	int array_size = 5;
	int i = 0;
	Uint32* dynamic_main_variable = NULL;
	dynamic_main_variable = calloc(array_size, sizeof(Uint32));
	Uint8* dynamic_channels = NULL;

	// Always error check these suckers...
	if (dynamic_main_variable != NULL)
	{
		array_created = true;
		for (i = 0; i < array_size; i++)
		{
			dynamic_channels = (Uint8*)&dynamic_main_variable[i];
			dynamic_channels[0] = 10 * i + 40;
			dynamic_channels[1] = 20 * 1 + 30;
			dynamic_channels[2] = 30 * i + 20;
			dynamic_channels[3] = 40 * i + 10;

			printf("Dynamic array %d, channel 0          : 0x%02x\n", i, dynamic_channels[0]);
			printf("Dynamic array %d, channel 1          : 0x%02x\n", i, dynamic_channels[1]);
			printf("Dynamic array %d, channel 2          : 0x%02x\n", i, dynamic_channels[2]);
			printf("Dynamic array %d, channel 3          : 0x%02x\n", i, dynamic_channels[3]);
			printf("Concatenated dynamic array element %d: 0x%08x\n\n", i, dynamic_main_variable[i]);
			
		}
	}
	else
	{
		printf("\nWARNING!\nThere was a problem creating the dynamic array.\n");
	}

	SDL_Event loop_event;
	while (quit == false)
	{
		while (SDL_PollEvent(&loop_event) != 0)
		{
			if (loop_event.type == SDL_QUIT)
			{
				quit = true;
			}
		}
	}

	// And always free the dynamic arrays that are created, of course.
	if (array_created == true)
	{
		free(dynamic_main_variable);
	}
	return 0;
}

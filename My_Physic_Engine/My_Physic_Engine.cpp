#include <iostream>
#include <conio.h>
#include "my_class.h"
#include <SDL.h>
#include <Windows.h>
#include <vector>

//Settings
UINT32 FPS = 60;
int water_fluidity = 20;

void MY_INITIALIZATIONS();
void MY_SDL_INITIALIZATIONS();
void Generate_Pixel(int *a);
void PIXEL_PHYSIC_CALCULATOR(); //Main Physic Function
int SAND_PHYSIC(int x, int y, int velocity_y, int* move_amount_x);
int WATER_PHYSIC(int x, int y, int velocity_y, int* move_amount_x);
void Render(SDL_Texture *texture);
void Render_Pixel();
void SIMULATED_RESET();
void EVENT_SDL_HANDLER(SDL_Event* sdl_event);
Uint32 FPS_COUNTER(void *param, SDL_TimerID timerID, Uint32 interval);

//Main pixel variable
my_pixel **mp;
//SDL variables
SDL_Window* win;
SDL_Renderer* ren;
SDL_Event sdl_event;
//Frame variables

bool is_borderless = false;
int frameDelay = 1000.0 / FPS;
UINT32 frame_start_point;
UINT32 frame_time;
UINT32 one_second_frame_count;
//Others
SDL_Texture *texture;
UINT32 *pixels;

bool stop_water = true;

int my_gravity = 1;

int main(int argc, char* args[])
{
	MY_SDL_INITIALIZATIONS();
	MY_INITIALIZATIONS();
	int a = 0;
	SDL_AddTimer(1000, FPS_COUNTER, NULL);
	while (true)
	{
		frame_start_point = SDL_GetTicks();
		EVENT_SDL_HANDLER(&sdl_event);
		
		Generate_Pixel(&a);
		

		PIXEL_PHYSIC_CALCULATOR();

		Render(texture);

		frame_time = SDL_GetTicks() - frame_start_point;
		if (frameDelay > frame_time)
		{
			SDL_Delay(frameDelay - frame_time);
		}
		one_second_frame_count++;
	} 
	return 0;
}

void MY_INITIALIZATIONS()
{
	mp = (my_pixel**) malloc((mp_size_y + 1) * sizeof(my_pixel*));
	for (int i = 0; i < mp_size_y + 1; i++)
	{
		mp[i] = (my_pixel*) malloc((mp_size_x + 1) * sizeof(my_pixel));
	}
	Init_MP(mp);
	texture = SDL_CreateTexture(ren, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, screen_x_size, screen_y_size);
	pixels = (UINT32*)malloc((screen_x_size * screen_y_size) * sizeof(UINT32));
}

void MY_SDL_INITIALIZATIONS()
{
	SDL_Init(SDL_INIT_AUDIO | SDL_INIT_EVENTS | SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer("window title", screen_x_size, screen_y_size, 0, &win, &ren);
	//SDL_SetWindowPosition(win, 0, 0);
	SDL_SetWindowBordered(win, bool(is_borderless));
	SDL_SetRenderDrawColor(ren, 0, 0, 0, 0);
	SDL_RenderClear(ren);
	SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
}

void Generate_Pixel(int *a)
{
	if (stop_water)
	{
		if (*a > 3)
		{
			for (int i = 50; i < 100; i++)
			{
				for (int j = 0; j < 1; j++)
				{
					mp[j][i].filled = true;
					mp[j][i].typeSet(0);
				}
			}
			for (int i = 150; i < 200; i++)
			{
				for (int j = 0; j < 1; j++)
				{
					mp[j][i].filled = true;
					mp[j][i].typeSet(1);
				}
			}
			*a = 0;
		}
		else
		{
			*a += 1;
		}
	}
}

void PIXEL_PHYSIC_CALCULATOR()
{
	for (int i = mp_size_x-1; i < mp_size_x; i++)
		for (int j = mp_size_y - 1; j > -1; j--)
				mp[j][i].filled = true;

	for (int i = 0; i < mp_size_x; i++)
	//for (int i = mp_size_x - 1; i > -1; i--)
	{
		for (int j = mp_size_y - 1; j > -1; j--)
		//for (int j = 0; j < mp_size_y; j++)
		{
			if (mp[j][i].filled && !mp[j][i].simulated)
			{
				int move_amount_y = 0;
				int move_amount_x = 0;
				mp[j][i].vel_y += my_gravity;
				switch (mp[j][i].typeGet())
				{
					case 0:
						move_amount_y = SAND_PHYSIC(i, j, mp[j][i].vel_y, &move_amount_x);
						break;
					case 1:
						move_amount_y = WATER_PHYSIC(i, j, mp[j][i].vel_y, &move_amount_x);
						break;
				}
				if (MY_ABS(move_amount_y) > 0 || MY_ABS(move_amount_x) > 0)
				{
					int next_x, next_y;
					next_x = i + move_amount_x;
					next_y = j + move_amount_y;
					if (mp[next_y][next_x].filled)
					{
						printf("%d %d \n", next_y, j);
						printf("%d %d \n", next_x, i);
					}
					mp[next_y][next_x].filled = true;
					mp[next_y][next_x].simulated = true;
					mp[next_y][next_x].vel_y = mp[j][i].vel_y;
					mp[next_y][next_x].typeSet(mp[j][i].typeGet());
					mp[j][i].filled = false;
					mp[j][i].vel_y = 0;
					mp[j][i].vel_x = 0;
					mp[j][i].typeSet(0);
				}
				else
				{
					mp[j][i].simulated = true;
				}
			}
		}
	}
	SIMULATED_RESET();
}

int SAND_PHYSIC(int x, int y, int velocity_y, int *move_amount_x)
{
	int distance_y = velocity_y;
	int random_x = 0;
	for (int i = y; i < y + velocity_y; i++)
	{
		if (i + 1 >= mp_size_y || mp[i + 1][x].filled)
		{
			distance_y = i - y;
			mp[y][x].vel_y -= 4;
			if(mp[y][x].vel_y < 0)
				mp[y][x].vel_y = 0;
			break;
		}
	}
	if (distance_y < velocity_y)
	{
		if (mp[y][x].vel_x <= 0)
		{
			random_x = rand() % 2;
			if (random_x == 0) 
				mp[y][x].vel_x = 1;
			else 
				mp[y][x].vel_x = -1;
		}
		else
		{
			mp[y][x].vel_x += MY_SIGN(mp[y][x].vel_x);
			if (mp[y][x].vel_x > 5)
				mp[y][x].vel_x = 5;
		}
	}
	if (mp[y][x].vel_x > 0)
	{
		for (int i = x; i < x + mp[y][x].vel_x; i++)
		{
			if (i + 1 >= mp_size_x || mp[y + distance_y][i + 1].filled)
			{
				*move_amount_x = i - x;
				break;
			}
		}
	}
	else if (mp[y][x].vel_x < 0)
	{
		for (int i = x; i > x + mp[y][x].vel_x; i--)
		{
			if (i - 1 < 0 || mp[y + distance_y][i - 1].filled)
			{
				*move_amount_x = i - x;
				break;
			}
		}
	}
	return distance_y;
}

int WATER_PHYSIC(int x, int y, int velocity_y, int *move_amount_x)
{
	int distance_y = velocity_y;
	for (int i = y; i < y + velocity_y; i++)
	{
		if (mp[i + 1][x].filled)
		{
			distance_y = i - y;
			mp[y][x].vel_y -= 4;
			if(mp[y][x].vel_y < 0)
				mp[y][x].vel_y = 0;
			break;
		}
	}
	if (mp[y + 1][x].filled)
	{
		if (mp[y][x].vel_x == 0)
		{
			int random_x = rand() % 2;
			if (random_x == 0) mp[y][x].vel_x = 1;
			else mp[y][x].vel_x = -1;
		}
		mp[y][x].vel_x = 1;
		int for_simulation_time = MY_ABS(mp[y][x].vel_x) + MY_ABS(mp[y][x].vel_y) + water_fluidity;
		for (int speed = 0; speed < for_simulation_time; speed++)
		{
			if (mp[y][x].vel_x > 0)
			{
				if (!mp[y + distance_y][x + *move_amount_x + 1].filled)
				{
					*move_amount_x += 1;
					if (!mp[y + distance_y + 1][x + *move_amount_x + 1].filled)
					{
						distance_y += 1;
					}
				}
				else
				{
					if (x + *move_amount_x - 1 >= 0 && !mp[y + distance_y][x + *move_amount_x - 1].filled)
					{
						*move_amount_x -= 1;
						mp[y][x].vel_x = -mp[y][x].vel_x;
						if (x + *move_amount_x - 1 >= 0 && !mp[y + distance_y + 1][x + *move_amount_x - 1].filled)
						{
							distance_y += 1;
						}
					}
					else
					{
						break;
					}
				}
			}
			else if (mp[y][x].vel_x < 0)
			{
				if (x + *move_amount_x - 1 >= 0 && !mp[y + distance_y][x + *move_amount_x - 1].filled)
				{
					*move_amount_x -= 1;
					if (x + *move_amount_x - 1 >= 0 && !mp[y + distance_y + 1][x + *move_amount_x - 1].filled)
					{
						distance_y += 1;
					}
				}
				else
				{
					if (!mp[y + distance_y][x + *move_amount_x + 1].filled)
					{
						*move_amount_x += 1;
						mp[y][x].vel_x = -mp[y][x].vel_x;
						if (!mp[y + distance_y + 1][x + *move_amount_x + 1].filled)
						{
							distance_y += 1;
						}
					}
					else
					{
						break;
					}
				}
			}
		}
	}
	return distance_y;
}

void Render(SDL_Texture* texture)
{
	Render_Pixel();
	SDL_UpdateTexture(texture, NULL, pixels, screen_x_size * sizeof(UINT32));
	SDL_SetRenderDrawColor(ren, 0,0,0,1);
	SDL_RenderClear(ren);
	SDL_RenderTexture(ren, texture, NULL, NULL);
	SDL_RenderPresent(ren);
}

void Render_Pixel()
{
	switch (pixel_scale)
	{
	case 1:
	{
		for (int j = 0; j < mp_size_y; j++)
		{
			int pixel_j = screen_x_size * j;
			for (int i = 0; i < mp_size_x; i++)
			{
				pixels[pixel_j + i] = mp[j][i].color;
			}
		}
		break;
	}
	case 2:
		for (int j = 0; j < mp_size_y; j++)
		{
			int pixel_j = screen_x_size * j * pixel_scale;
			int pixel_i = 0;
			for (int i = 0; i < mp_size_x; i++)
			{
				pixel_i = i * pixel_scale;
				pixels[pixel_j + pixel_i] = mp[j][i].color;
				pixels[pixel_j + pixel_i + 1] = mp[j][i].color;
			}
			pixel_j += screen_x_size;
			for (int i = 0; i < mp_size_x; i++)
			{
				pixel_i = i * pixel_scale;
				pixels[pixel_j + pixel_i] = mp[j][i].color;
				pixels[pixel_j + pixel_i + 1] = mp[j][i].color;
			}
		}
		break;
	case 4:
		for (int j = 0; j < mp_size_y; j++)
		{
			int pixel_j = screen_x_size * j * pixel_scale;
			int pixel_i = 0;
			for (int i = 0; i < mp_size_x; i++)
			{
				pixel_i = i * pixel_scale;
				pixels[pixel_j + pixel_i] = mp[j][i].color;
				pixels[pixel_j + pixel_i + 1] = mp[j][i].color;
				pixels[pixel_j + pixel_i + 2] = mp[j][i].color;
				pixels[pixel_j + pixel_i + 3] = mp[j][i].color;
			}
			pixel_j += screen_x_size;
			for (int i = 0; i < mp_size_x; i++)
			{
				pixel_i = i * pixel_scale;
				pixels[pixel_j + pixel_i] = mp[j][i].color;
				pixels[pixel_j + pixel_i + 1] = mp[j][i].color;
				pixels[pixel_j + pixel_i + 2] = mp[j][i].color;
				pixels[pixel_j + pixel_i + 3] = mp[j][i].color;
			}
			pixel_j += screen_x_size;
			for (int i = 0; i < mp_size_x; i++)
			{
				pixel_i = i * pixel_scale;
				pixels[pixel_j + pixel_i] = mp[j][i].color;
				pixels[pixel_j + pixel_i + 1] = mp[j][i].color;
				pixels[pixel_j + pixel_i + 2] = mp[j][i].color;
				pixels[pixel_j + pixel_i + 3] = mp[j][i].color;
			}
			pixel_j += screen_x_size;
			for (int i = 0; i < mp_size_x; i++)
			{
				pixel_i = i * pixel_scale;
				pixels[pixel_j + pixel_i] = mp[j][i].color;
				pixels[pixel_j + pixel_i + 1] = mp[j][i].color;
				pixels[pixel_j + pixel_i + 2] = mp[j][i].color;
				pixels[pixel_j + pixel_i + 3] = mp[j][i].color;
			}
			pixel_j += screen_x_size;
		}
		break;
	default:
		for (int j = 0; j < mp_size_y; j++)
		{
			int pixel_j = j * pixel_scale;
			for (int i = 0; i < mp_size_x; i++)
			{
				int pixel_i = i * pixel_scale;
				for (int y = pixel_j; y < pixel_j + pixel_scale; y++)
				{
					int loc_y = y * screen_x_size;
					for (int x = pixel_i; x < pixel_i + pixel_scale; x++)
					{
						pixels[(loc_y)+x] = mp[j][i].color;
					}
				}
			}
		}
	}
}

void SIMULATED_RESET()
{
	for (int i = 0; i < mp_size_x; i++)
	{
		for (int j = 0; j < mp_size_y; j++)
		{
			mp[j][i].simulated = false;
		}
	}
}

void EVENT_SDL_HANDLER(SDL_Event* sdl_event)
{
	while (SDL_PollEvent(sdl_event))
	{
		switch (sdl_event->type)
		{
			case SDL_EVENT_KEY_DOWN:
				stop_water = !stop_water;
				frameDelay = 1000.0 / FPS;
				break;
			default:
				break;
		}
	}
}

Uint32 FPS_COUNTER(void *param, SDL_TimerID timerID, Uint32 interval)
{
	printf("FPS: %d\n", one_second_frame_count);
	one_second_frame_count = 0;
	SDL_AddTimer(1000, FPS_COUNTER, NULL);
	return 0;
}
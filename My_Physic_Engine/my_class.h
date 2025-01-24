#include <Windows.h>

const int screen_x_size = 1280;
const int screen_y_size = 768;

const int pixel_scale = 4;

const int mp_size_x = screen_x_size / pixel_scale;
const int mp_size_y = screen_y_size / pixel_scale;

const UINT32 background_color = 0x00303030;

// Types => 0:Sand - 1:Water
typedef struct my_pix
{
	private:
		int type;

	public:
		bool filled = false;
		int vel_x = 0;
		int vel_y = 0;
		bool simulated = false;
		int color;
		
		void typeSet(int a)
		{
			type = a;
			if (filled)
			{
				switch (type)
				{
					case 0:
						color = 0xFFEACE6A;
						break;
					case 1:
						color = 0xFF00FFFF;
						break;
					default:
						color = background_color;
						break;
				}
			}
			else
			{
				color = background_color;
			}
		}
		int typeGet() { return type; }
} my_pixel;

void Init_MP(my_pixel **coming)
{
	for (int i = 0; i < mp_size_x; i++)
	{
		for (int j = 0; j < mp_size_y; j++)
		{
			coming[j][i].filled = false;
			coming[j][i].vel_x = 0;
			coming[j][i].vel_y = 0;
			coming[j][i].typeSet(0);
		}
	}
	for (int i = 0; i < mp_size_x; i++)
	{
		coming[mp_size_y][i].filled = true;
	}
	for (int i = 0; i < mp_size_y; i++)
	{
		coming[i][mp_size_x].filled = true;
	}
}

void Eq_MP(my_pixel **first, my_pixel **second) //Sets second array equal to first array
{
	for (int i = 0; i < mp_size_x; i++)
	{
		for (int j = 0; j < mp_size_y; j++)
		{
			first[j][i] = second[j][i];
		}
	}
}

int MY_SIGN(int x)
{
	if (x > 0) return 1;
	if (x < 0) return -1;
	return 0;
}

int MY_ABS(int x)
{
	if (x > 0) return x;
	if (x < 0) return -x;
	return 0;
}
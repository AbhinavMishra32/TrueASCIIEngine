#include <stdio.h>
#include <math.h>
#include <windows.h>
#include <conio.h>

#define WIDTH 100
#define HEIGHT 30
#define FPS 60

void disableRawMode()
{
	DWORD dwMode;
	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);

	GetConsoleMode(hStdin, &dwMode);

	dwMode &= ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT);
	SetConsoleMode(hStdin, dwMode);
}

typedef struct Display
{
	char screen[WIDTH][HEIGHT];
	int width;
	int height;
} Display;

Display display;

typedef struct Circle
{
	int radius;
	int width;
	int height;
} Circle;

double dist(int x1, int y1, int x2, int y2)
{
	return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

void createCircle(int radius, int x, int y)
{
	for (int i = y - radius; i <= y + radius; i++)
	{
		for (int j = x - radius; j <= x + radius; j++)
		{
			if (i >= 0 && i < display.height && j >= 0 && j < display.width)
			{
				if (dist(j, i, x, y) <= radius)
				{
					display.screen[j][i] = '*';
				}
			}
		}
	}
}

void clearDisplay()
{
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			display.screen[j][i] = ' ';
		}
	}
}

void renderDisplay()
{
	for (int i = 0; i < display.height; i++)
	{
		for (int j = 0; j < display.width; j++)
		{
			putchar(display.screen[j][i]);
		}
		putchar('\n');
	}
};

void createDisplay(int width, int height)
{
	display.width = width;
	display.height = height;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			display.screen[j][i] = ' ';
		}
	}
}

int main()
{

	disableRawMode();
	createDisplay(WIDTH, HEIGHT);

	while (1)
	{
		createCircle(4, 20, 20);
		renderDisplay();
		// clearDisplay();
		puts("\x1B[2J");
		fflush(stdout);
		Sleep(1000 / FPS);
	}

	return 0;
}

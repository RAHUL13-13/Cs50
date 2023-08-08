#include "helpers.h"
#include<math.h>
#include<cs50.h>

void swap(int a, int b);
int q = 0;

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i <= height - 1; i++)
    {
        for (int j = 0; j <= width - 1; j++)
        {
            int r = image[i][j].rgbtRed;
            int g = image[i][j].rgbtGreen;
            int b = image[i][j].rgbtBlue;

            float k = ((float)r + (float)g + (float)b) / 3;
            int p = round(k);

            image[i][j].rgbtRed = p;
            image[i][j].rgbtGreen = p;
            image[i][j].rgbtBlue = p;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i <= height - 1; i++)
    {
        for (int j = 0; j <= round((float)width / 2) - 1; j++)
        {
            int x = image[i][j].rgbtRed;
            int y = image[i][j].rgbtBlue;
            int z = image[i][j].rgbtGreen;

            image[i][j].rgbtRed = image[i][width - 1 - j].rgbtRed;
            image[i][j].rgbtBlue = image[i][width - 1 - j].rgbtBlue;
            image[i][j].rgbtGreen = image[i][width - 1 - j].rgbtGreen;

            image[i][width - 1 - j].rgbtRed = x;
            image[i][width - 1 - j].rgbtBlue = y;
            image[i][width - 1 - j].rgbtGreen = z;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height + 2][width + 2];

    for (int i = 0; i <= height + 1; i++)
    {
        for (int j = 0; j <= width + 1; j++)
        {
            temp[i][j].rgbtRed = 0;
            temp[i][j].rgbtBlue = 0;
            temp[i][j].rgbtGreen = 0;
        }
    }

    for (int i = 0; i <= height - 1; i++)
    {
        for (int j = 0; j <= width - 1; j++)
        {
            temp[i + 1][j + 1] = image[i][j];
        }
    }

    for (int i = 1; i <= height; i++)
    {
        for (int j = 1; j <= width; j++)
        {
            q = 0;
            for (int k = -1; k <= 1; k++)
            {
                for (int g = -1; g <= 1; g++)
                {
                    if ((temp[i + k][j + g].rgbtRed == 0) && (temp[i + k][j + g].rgbtBlue == 0) && (temp[i + k][j + g].rgbtGreen == 0))
                    {
                        if ((i + k == 0) || (i + k == height + 1) || (j + g == 0) || (j + g == width + 1))
                        {
                            q += 0;
                        }
                        else
                        {
                            q += 1;
                        }
                    }
                    else
                    {
                        q += 1;
                    }
                }
            }

            int x = round(((float)temp[i][j].rgbtRed + (float)temp[i + 1][j + 1].rgbtRed + (float)temp[i - 1][j - 1].rgbtRed + 
                           (float)temp[i - 1][j].rgbtRed + (float)temp[i + 1][j - 1].rgbtRed + (float)temp[i - 1][j + 1].rgbtRed +
                           (float)temp[i][j + 1].rgbtRed + (float)temp[i + 1][j].rgbtRed + (float)temp[i][j - 1].rgbtRed) / q);

            int y = round(((float)temp[i][j].rgbtBlue + (float)temp[i + 1][j + 1].rgbtBlue + (float)temp[i - 1][j - 1].rgbtBlue +
                           (float)temp[i - 1][j].rgbtBlue + (float)temp[i + 1][j - 1].rgbtBlue + (float)temp[i - 1][j + 1].rgbtBlue +
                           (float)temp[i][j + 1].rgbtBlue + (float)temp[i + 1][j].rgbtBlue + (float)temp[i][j - 1].rgbtBlue) / q);

            int z = round(((float)temp[i][j].rgbtGreen + (float)temp[i + 1][j + 1].rgbtGreen + (float)temp[i - 1][j - 1].rgbtGreen +
                           (float)temp[i - 1][j].rgbtGreen + (float)temp[i + 1][j - 1].rgbtGreen + (float)temp[i - 1][j + 1].rgbtGreen + 
                           (float)temp[i][j + 1].rgbtGreen + (float)temp[i + 1][j].rgbtGreen + (float)temp[i][j - 1].rgbtGreen) / q);

            image[i - 1][j - 1].rgbtRed = x;
            image[i - 1][j - 1].rgbtBlue = y;
            image[i - 1][j - 1].rgbtGreen = z;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height + 2][width + 2];

    for (int i = 0; i <= height + 1; i++)
    {
        for (int j = 0; j <= width + 1; j++)
        {
            temp[i][j].rgbtRed = 0;
            temp[i][j].rgbtBlue = 0;
            temp[i][j].rgbtGreen = 0;
        }
    }

    for (int i = 0; i <= height - 1; i++)
    {
        for (int j = 0; j <= width - 1; j++)
        {
            temp[i + 1][j + 1] = image[i][j];
        }
    }
    for (int i = 1; i <= height; i++)
    {
        for (int j = 1; j <= width; j++)
        {
            
            int p = 0, v = 0, r = 0, s = 0, t = 0, u = 0;

            p = (-1) * temp[i - 1][j - 1].rgbtRed + (0) * temp[i - 1][j].rgbtRed + (1) * temp[i - 1][j + 1].rgbtRed +
                (-2) * temp[i][j - 1].rgbtRed + (0) * temp[i][j].rgbtRed + (2) * temp[i][j + 1].rgbtRed +
                (-1) * temp[i + 1][j - 1].rgbtRed + (0) * temp[i + 1][j].rgbtRed + (1) * temp[i + 1][j + 1].rgbtRed;

            v = (-1) * temp[i - 1][j - 1].rgbtBlue + (0) * temp[i - 1][j].rgbtBlue + (1) * temp[i - 1][j + 1].rgbtBlue +
                (-2) * temp[i][j - 1].rgbtBlue + (0) * temp[i][j].rgbtBlue + (2) * temp[i][j + 1].rgbtBlue +
                (-1) * temp[i + 1][j - 1].rgbtBlue + (0) * temp[i + 1][j].rgbtBlue + (1) * temp[i + 1][j + 1].rgbtBlue;

            r = (-1) * temp[i - 1][j - 1].rgbtGreen + (0) * temp[i - 1][j].rgbtGreen + (1) * temp[i - 1][j + 1].rgbtGreen +
                (-2) * temp[i][j - 1].rgbtGreen + (0) * temp[i][j].rgbtGreen + (2) * temp[i][j + 1].rgbtGreen +
                (-1) * temp[i + 1][j - 1].rgbtGreen + (0) * temp[i + 1][j].rgbtGreen + (1) * temp[i + 1][j + 1].rgbtGreen;
             
            s = (-1) * temp[i - 1][j - 1].rgbtRed + (-2) * temp[i - 1][j].rgbtRed + (-1) * temp[i - 1][j + 1].rgbtRed +
                (0) * temp[i][j - 1].rgbtRed + (0) * temp[i][j].rgbtRed + (0) * temp[i][j + 1].rgbtRed +
                (1) * temp[i + 1][j - 1].rgbtRed + (2) * temp[i + 1][j].rgbtRed + (1) * temp[i + 1][j + 1].rgbtRed;

            t = (-1) * temp[i - 1][j - 1].rgbtBlue + (-2) * temp[i - 1][j].rgbtBlue + (-1) * temp[i - 1][j + 1].rgbtBlue +
                (0) * temp[i][j - 1].rgbtBlue + (0) * temp[i][j].rgbtBlue + (0) * temp[i][j + 1].rgbtBlue +
                (1) * temp[i + 1][j - 1].rgbtBlue + (2) * temp[i + 1][j].rgbtBlue + (1) * temp[i + 1][j + 1].rgbtBlue;

            u = (-1) * temp[i - 1][j - 1].rgbtGreen + (-2) * temp[i - 1][j].rgbtGreen + (-1) * temp[i - 1][j + 1].rgbtGreen +
                (0) * temp[i][j - 1].rgbtGreen + (0) * temp[i][j].rgbtGreen + (0) * temp[i][j + 1].rgbtGreen +
                (1) * temp[i + 1][j - 1].rgbtGreen + (2) * temp[i + 1][j].rgbtGreen + (1) * temp[i + 1][j + 1].rgbtGreen;
             
            int f = round((float)sqrt(pow(p, 2) + pow(s, 2)));
            int h = round((float)sqrt(pow(v, 2) + pow(t, 2)));
            int g = round((float)sqrt(pow(r, 2) + pow(u, 2)));
            
            if (f > 255)
            {
                f = 255;
            }
            if (h > 255)
            {
                h = 255;
            }
            if (g > 255)
            {
                g = 255;
            }
            
            image[i - 1][j - 1].rgbtRed = f;
            image[i - 1][j - 1].rgbtBlue = h;
            image[i - 1][j - 1].rgbtGreen = g;
        }
    }
    return;
}

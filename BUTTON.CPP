#include <mem.h>
#include <math.h>
#include "button.h"
#include "mouse.h"

void    putpixel(int x, int y, char c);
void    bar(int x1, int y1, int x2, int y2);
void    drawline(float x1, float y1, float x2, float y2, int col);
void    swap(int* a, int* b);

extern TMouse*  mouse;

void drawline(float zx1, float zy1, float zx2, float zy2, int col)
{
    int x1, y1, x2, y2;
    if (zx1 <= zx2)
    {
        x1 = zx1;
        y1 = zy1;
        x2 = zx2;
        y2 = zy2;
    }
    else
    {
        x2 = zx1;
        y2 = zy1;
        x1 = zx2;
        y1 = zy2;
    }
    if ((x1 == x2) && (y1 == y2))
    {
        return;
    }
    float   dx  = x2 - x1;
    float   dy  = y2 - y1;
    if (fabs(dx) > fabs(dy))
    {
        float   iy  = dy / dx;
        float   cy  = y1;
        if (x1 > x2)
        {
            swap(&x1, &x2);
        }
        for (int x = x1; x <= x2; x++)
        {
            cy += iy;
            putpixel(x, int(cy), col);
        }
    }
    else
    {
        float   ix  = fabs(dx / dy);
        float   cx  = x1;
        if (y1 > y2)
        {
            swap(&y1, &y2);
            ix = -ix;
            cx = x2;
        }
        for (int y = y1; y <= y2; y++)
        {
            cx += ix;
            putpixel(cx, y, col);
        }
    }
}

TButton::TButton()
{
    tag = 1;
    isToggler = 0;
    isDown = 0;
    for (int x = 0; x < 16; x++)
    {
        for (int y = 0; y < 16; y++)
        {
            blitMap[x][y] = 1;
        }
    }
}


void TButton::setBlitMap(void* map)
{
    memcpy(blitMap, map, sizeof(blitMap));
}

void TButton::paint()
{
    mouse->hide();
    if (isDown == 0)
    {
        drawline(x1, y1, x2, y1, 8);
        drawline(x1, y1, x1, y2, 8);
        drawline(x2, y2, x2, y1, 0);
        drawline(x2, y2, x1, y2, 0);
    }
    else
    {
        drawline(x1, y1, x2, y1, 0);
        drawline(x1, y1, x1, y2, 0);
        drawline(x2, y2, x2, y1, 8);
        drawline(x2, y2, x1, y2, 8);
    }
    for (int x = 0; x < 16; x++)
    {
        for (int y = 0; y < 16; y++)
        {
            if (blitMap[x][y] != 16)
            {
                putpixel(x1 + 1 + x, y1 + 1 + y, blitMap[x][y]);
            }
        }
    }
    mouse->show();
}

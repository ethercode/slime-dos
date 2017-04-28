#ifndef BUTTON
#define BUTTON

class TButton
{
public:
            TButton();
    void    setBlitMap(void* map);
    int     x1, y1, x2, y2;
    void    paint();
    int     tag;
    int     isDown;
    int     isToggler;

private:
    char    blitMap[16][16];
};

#endif
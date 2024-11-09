#ifndef FONT_H
#define FONT_H

#include <stdbool.h>
#include <ft2build.h>
#include FT_FREETYPE_H

bool get_character_bitmap(char ch, float font_size, FT_Bitmap* bitmap);

#endif // FONT_H

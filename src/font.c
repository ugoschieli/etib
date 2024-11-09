#include "font.h"

bool get_character_bitmap(char ch, float font_size, FT_Bitmap* bitmap)
{
    FT_Error error;

    FT_Library library;
    error = FT_Init_FreeType(&library);
    if (error) {
        printf("Couldn't init FreeType2\n");
        return false;
    }

    FT_Face face;
    error = FT_New_Face(library, "./JetBrainsMonoNerdFont-Regular.ttf", 0, &face);
    if (error == FT_Err_Unknown_File_Format) {
        printf("Couldn't open font file, unknown file format.\n");
        return false;
    } else if (error) {
        printf("Couldn't open font file.\n");
        return false;
    }

    error = FT_Set_Char_Size(face, 0, (int)(font_size * 64), 300, 300);
    if (error) {
        printf("Couldn't set font size.\n");
        return false;
    }

    FT_UInt glyph_index = FT_Get_Char_Index(face, (FT_UInt32)ch);

    error = FT_Load_Glyph(face, glyph_index, FT_LOAD_DEFAULT);
    if (error) {
        printf("Couldn't load glyph\n");
        return false;
    }

    error = FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL);
    if (error) {
        printf("Couldn't render glyph\n");
        return false;
    }

    *bitmap = face->glyph->bitmap;
    return true;
}

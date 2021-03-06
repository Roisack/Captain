#include "text.hpp"
#include <string>
#include "manager.hpp"
#include "opengl.hpp"
#include <assert.h>

Text::Text()
{
}

// Constructs the text. Params are the dimensions, desired text,
// path to the truetype font file, and the size of the font. Note
// that the size is somewhat important for getting a good looking sprite
Text::Text(int x, int y, std::string input, std::string fontPath, int fontSize)
{
    fprintf(stderr, "New text constructing with: x: %d, y: %d, input: %s, font: %s, size: %d\n", x, y, input.c_str(), fontPath.c_str(), fontSize);
	w = x;
	h = y;
    x = 1;
    y = 1;
	font = TTF_OpenFont( fontPath.c_str(), fontSize );
	id = 0;
	glGenTextures(1, &id);
	assert(id);
	opacity = 1.0f;
    content = input;
	
	glBindTexture(GL_TEXTURE_2D, id);
	
	GLuint target = GL_TEXTURE_2D;
	
	textColor.r = 255.0f;
	textColor.g = 255.0f;
	textColor.b = 255.0f;
    color.x = 1.0f;
    color.y = 1.0f;
    color.z = 1.0f;
	
	assert(font);
	spriteSurface = TTF_RenderText_Blended( font, input.c_str(), textColor );
	assert(spriteSurface);
	format = checkGeneric(spriteSurface);
	assert(spriteSurface->pixels);
	// 8 = 1 channel, alpha
	// 32 = RGBA
	assert(spriteSurface->format->BitsPerPixel == 32);
	glTexImage2D(target,
	0,
	format,
	spriteSurface->w,
	spriteSurface->h,
	0,
	format,
	GL_UNSIGNED_BYTE,
	spriteSurface->pixels);
	
	glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_REPEAT);
	assert(spriteSurface);
    fprintf(stderr, "Text built\n");
}

// Render the text as a 4 vertice plane with the sprite working as a texture
void Text::render()
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, manager.getOpengl()->getScreenX(), 0, manager.getOpengl()->getScreenY(), -1, 1);
	
	glMatrixMode(GL_MODELVIEW);
    glTranslatef(manager.getOpengl()->getScreenX()/10+x, manager.getOpengl()->getScreenY()/10+y, 0);
	glScalef(1.0f, 1.0f, 1.0f);
	
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	// SDL_spriteSurface->glTexImage2D conversion made earlier. We have only the alpha
	// in the original spriteSurface, so we are taking the alpha, blending it to the
	// texture, then colouring the mask
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBlendEquation(GL_FUNC_ADD);
	glDisable(GL_DEPTH_TEST);
	glBindTexture(GL_TEXTURE_2D, id);
	glColor4f(color.x, color.y, color.z, opacity);
	
	glBegin(GL_QUADS);
	glTexCoord2f(0, 1); glVertex2f(-w, -h);
	glTexCoord2f(1, 1); glVertex2f(w, -h);
	glTexCoord2f(1, 0); glVertex2f(w, h);
	glTexCoord2f(0, 0); glVertex2f(-w, h);
	glEnd();
	
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

void Text::setColorR(float f)
{
    color.x = f;
}

void Text::setColorG(float f)
{
    color.y = f;
}

void Text::setColorB(float f)
{
    color.z = f;
}

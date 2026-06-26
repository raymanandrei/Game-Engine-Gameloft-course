#include "stdafx.h"
#include <iostream>
#include "Texture.h"

#include "../Utilities/utilities.h"

void ExtractFace(
    char* dest,
    char* src,
    int startX,
    int startY,
    int faceW,
    int faceH,
    int width,
    int bytesPerPixel)
{
    for (int y = 0; y < faceH; y++)
    {
        memcpy(
            dest + y * faceW * bytesPerPixel,
            src + ((startY + y) * width + startX) * bytesPerPixel,
            faceW * bytesPerPixel
        );
    }
}

Texture::Texture() {
}

Texture::~Texture() {
}

bool Texture::Load() {

	int width, height, bpp;
	char* pixelArray = nullptr;

	pixelArray = LoadTGA((tr->file).c_str(), &width, &height, &bpp);

	glGenTextures(1, &tr->id);
	glBindTexture(tr->type, tr->id);

	GLint format = (bpp == 32) ? GL_RGBA : GL_RGB;

	if (tr->type == GL_TEXTURE_CUBE_MAP) {
			
		std::cout << "Loading sky texture" << "\n";
        int width, height, bpp;
        char* pixelArray = LoadTGA((tr->file).c_str(), &width, &height, &bpp);

        if (!pixelArray)
            return false;

        GLint format = (bpp == 32) ? GL_RGBA : GL_RGB;

        glGenTextures(1, &tr->id);
        glBindTexture(GL_TEXTURE_CUBE_MAP, tr->id);

        int faceW = width / 4;
        int faceH = height / 3;

        char* temp;
        int faceSize = faceW * faceH * (bpp / 8);
        temp = (char*)malloc(faceSize);
        int bytesPerPixel = bpp / 8;

                
        ExtractFace(temp, pixelArray, 2 * faceW, faceH, faceW, faceH, width, bytesPerPixel);
        //std::reverse(temp, temp + strlen(temp));
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, format, faceW, faceH, 0, format, GL_UNSIGNED_BYTE, temp);

        ExtractFace(temp, pixelArray, 0, faceH, faceW, faceH, width, bytesPerPixel);
        //std::reverse(temp, temp + strlen(temp));
        glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, format, faceW, faceH, 0, format, GL_UNSIGNED_BYTE, temp);

        ExtractFace(temp, pixelArray, faceW, 0, faceW, faceH, width, bytesPerPixel);
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, format, faceW, faceH, 0, format, GL_UNSIGNED_BYTE, temp);
        
        ExtractFace(temp, pixelArray, faceW, 2 * faceH, faceW, faceH, width, bytesPerPixel);
        glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, format, faceW, faceH, 0, format, GL_UNSIGNED_BYTE, temp);
        
        ExtractFace(temp, pixelArray, faceW, faceH, faceW, faceH, width, bytesPerPixel);
        //std::reverse(temp, temp + strlen(temp));
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, format, faceW, faceH, 0, format, GL_UNSIGNED_BYTE, temp);
        
        ExtractFace(temp, pixelArray, 3 * faceW, faceH, faceW, faceH, width, bytesPerPixel);
        //std::reverse(temp, temp + strlen(temp));
        glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, format, faceW, faceH, 0, format, GL_UNSIGNED_BYTE, temp);

        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, tr->min_filter);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, tr->mag_filter);

        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, tr->wrap_s);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, tr->wrap_t);

        glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

        return true;
	}
	else {

		std::cout << tr->type << " " << tr->wrap_t << " " << tr->min_filter << " " << '\n';

		glTexImage2D(tr->type, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, pixelArray);

		glTexParameteri(tr->type, GL_TEXTURE_WRAP_S, tr->wrap_s);
		glTexParameteri(tr->type, GL_TEXTURE_WRAP_T, tr->wrap_t);

		glTexParameteri(tr->type, GL_TEXTURE_MIN_FILTER, tr->min_filter);
		glTexParameteri(tr->type, GL_TEXTURE_MAG_FILTER, tr->mag_filter);

		glBindTexture(tr->type, 0);
	}
	return true;
}


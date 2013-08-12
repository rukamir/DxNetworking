#include "Water.h"

Water::Water(int id)
{
	m_mesh	=	NULL;
	m_id = id;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_velocity = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_acceleration = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_target = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_forceAccum = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	orientation = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	damping = 0.98f;
	m_awarnessRad = 0;
	m_targetID=0;
	m_maxAccel = 100;

	LoadHeightMap("Textures/download.bmp");
}

void Water::NormalizeHeightMap()
{
	int i, j;


	for(j=0; j<m_waterHeight; j++)
	{
		for(i=0; i<m_waterWidth; i++)
		{
			m_noiseMap[(m_waterHeight * j) + i].y /= 15.0f;
		}
	}

	return;
}

bool Water::LoadHeightMap(char* filename)
{
	FILE* filePtr;
	int error;
	unsigned int count;
	BITMAPFILEHEADER bitmapFileHeader;
	BITMAPINFOHEADER bitmapInfoHeader;
	int imageSize, i, j, k, index;
	unsigned char* bitmapImage;
	unsigned char height;
//Begin by opening the file and then read it into a unsigned char array. Close the file after we are finished reading the data from it.

	// Open the height map file in binary.
	error = fopen_s(&filePtr, filename, "rb");
	if(error != 0)
	{
		return false;
	}

	// Read in the file header.
	count = fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, filePtr);
	if(count != 1)
	{
		return false;
	}

	// Read in the bitmap info header.
	count = fread(&bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, filePtr);
	if(count != 1)
	{
		return false;
	}
//Store the size of the terrain so we can use these values for building the vertex and index buffers as well as rendering the terrain.

	// Save the dimensions of the terrain.
	m_waterWidth = bitmapInfoHeader.biWidth;
	m_waterHeight = bitmapInfoHeader.biHeight;

	// Calculate the size of the bitmap image data.
	imageSize = m_waterWidth * m_waterHeight * 3;

	// Allocate memory for the bitmap image data.
	bitmapImage = new unsigned char[imageSize];
	if(!bitmapImage)
	{
		return false;
	}

	// Move to the beginning of the bitmap data.
	fseek(filePtr, bitmapFileHeader.bfOffBits, SEEK_SET);

	// Read in the bitmap image data.
	count = fread(bitmapImage, 1, imageSize, filePtr);
	if(count != imageSize)
	{
		return false;
	}

	// Close the file.
	error = fclose(filePtr);
	if(error != 0)
	{
		return false;
	}
//Now that the bitmap has been read in create the two dimensional height map array and read the buffer into it. Note that during the for loop I use the two loop variables (i and j) to be the X (width) and Z (depth) of the terrain. And then I use the bitmap value to be the Y (height) of the terrain. You will also see I increment the index into the bitmap (k) by three since we only need one of the color values (red, green, or blue) to be used as the grey scale value.

	// Create the structure to hold the height map data.
	m_noiseMap = new NoiseMapType[m_waterWidth * m_waterHeight];
	if(!m_noiseMap)
	{
		return false;
	}

	// Initialize the position in the image data buffer.
	k=0;

	// Read the image data into the height map.
	for(j=0; j<m_waterHeight; j++)
	{
		for(i=0; i<m_waterWidth; i++)
		{
			height = bitmapImage[k];
			
			index = (m_waterHeight * j) + i;

			m_noiseMap[index].x = (float)i;
			m_noiseMap[index].y = (float)height;
			m_noiseMap[index].z = (float)j;

			k+=3;
		}
	}
//Now that we have stored the height map data for the terrain in our own array we can release the bitmap array.

	// Release the bitmap image data.
	delete [] bitmapImage;
	bitmapImage = 0;

	return true;
}
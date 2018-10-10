//
//  EdgeDetector.cpp
//  EdgeDetection
//
//  Created by Andy on 24/11/2015.
//
//

#include "EdgeDetector.h"

void EdgeDetector::detectEdges(Image &img)
{
    //Copy image to leave original untouched
    image = img.createCopy();
    
    detectionImage = Image(Image::PixelFormat::ARGB, image.getWidth(), image.getHeight(), true);
    
    //Desaturate image or convert to 8bpp rather than 32bpp (RGBA)
    desaturateImage();
    
    //Perform sobel convolution, filling two arrays with orientation and magnitude data
    Array<double> orientation;
    Array<double> magnitude;
    performSobelConvolution(orientation, magnitude);
    
    convertSobelToImage(orientation, magnitude);
    
    File test (File::getSpecialLocation(File::userDesktopDirectory).getFullPathName() + "/test.png");
    
    if (test.existsAsFile())
        test.deleteFile();
    
    FileOutputStream out(test);
    
    PNGImageFormat png;
    if (!png.writeImageToStream(detectionImage, out))
        DBG("Something went wrong writing");
}

void EdgeDetector::desaturateImage()
{
    Image::BitmapData data (image, Image::BitmapData::readWrite);

    Image::BitmapData detectionData (detectionImage, Image::BitmapData::writeOnly);
    
    for (int pixel = 0; pixel < image.getHeight() * image.getWidth() * data.pixelStride; pixel += data.pixelStride)
    {
        uint32 average = 0;
        
        for (int colour = 0; colour < data.pixelStride; colour++)
        {
            average += data.data[pixel + colour];
        }
        
        for (int colour = 0; colour < detectionData.pixelStride; colour++)
        {
            detectionData.data[pixel + colour] = average/data.pixelStride;
        }
    }
}

void EdgeDetector::performSobelConvolution(Array<double>& orientation, Array<double>& magnitude)
{
    //Create a 3 by 3 window, which is passed around the desaturated image
    uint8 window[9];
    
    int width = detectionImage.getWidth();
    int height = detectionImage.getHeight();
    
    Image::BitmapData detectionData (detectionImage, Image::BitmapData::readOnly);
    
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            //Read the values from the image into the window
            //Only need to read the first value as the desaturation has averaged them to the same value
            
            //TODO: This can obviously read data which isn't the (eg. x = 0, x - 1 = BadAccess)
            window[0] = *detectionData.getPixelPointer(x - 1, y - 1);
            window[1] = *detectionData.getPixelPointer(x, y - 1);
            window[2] = *detectionData.getPixelPointer(x + 1, y - 1);
            window[3] = *detectionData.getPixelPointer(x - 1, y);
            window[4] = *detectionData.getPixelPointer(x, y);
            window[5] = *detectionData.getPixelPointer(x + 1, y);
            window[6] = *detectionData.getPixelPointer(x - 1, y + 1);
            window[7] = *detectionData.getPixelPointer(x, y + 1);
            window[8] = *detectionData.getPixelPointer(x + 1, y + 1);
            
            //Perform sobel operation
            double dx = window[2] + 2 * window[5] + window[8] - window[0] - 2 * window[3] - window[6];
            double dy = window[6] + 2 * window[7] + window[8] - window[0] - 2 * window[1] - window[2];
            
            //Use our values to determine magnitude and orientation
            int index = y * width + x;
            
            magnitude.set(index, sqrt(dx * dx + dy * dy) / 1141); // 1141 is approximately the max sobel response
            orientation.set(index, atan2(dy, dx) + M_PI); // Angle is in radians, now from 0 - 2PI.
        }
    }    
}

void EdgeDetector::convertSobelToImage(Array<double>& orientation, Array<double>& magnitude)
{
    //Use HSV colour to write magnitude and orientation, hue is orientation, saturation is constant (1), value is magnitude
    //Scale our magnitude to be between 0 - 1
    double magnitudeMax = 0;
    
    for (double& m : magnitude)
        magnitudeMax = jmax(magnitudeMax, m);
    
    int width = detectionImage.getWidth();
    int height = detectionImage.getHeight();
    
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            int index = y * width + x;
            
            detectionImage.setPixelAt(x, y, Colour::fromHSV(orientation[index], 1, magnitude[index]/magnitudeMax, 1));
        }
    }
}
#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class EdgeDetector
{
public:
    //Invalid edge detector
    EdgeDetector (){}
    
    void detectEdges (Image& img);
    
    void performSobelConvolution (Array<double>& orientation, Array<double>& magnitude);
    void convertSobelToImage (Array<double>& orientation, Array<double>& magnitude);
    
    Image& getDetectedImage () { return detectionImage; }
private:
    void desaturateImage ();
    
    Image image;
    Image detectionImage;
};

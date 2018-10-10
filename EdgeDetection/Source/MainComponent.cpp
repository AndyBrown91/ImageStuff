/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"


//==============================================================================
MainContentComponent::MainContentComponent (const File& imageFile)
{
    if (imageFile.existsAsFile())
    {
        Image loadImage = ImageFileFormat::loadFrom(imageFile);
        
        edge.detectEdges(loadImage);
        
        drawImage = edge.getDetectedImage();
        
        setSize (loadImage.getWidth(), loadImage.getHeight());
    }
    else
    {
        DBG("Couldnt find image: " + imageFile.getFullPathName());
        setSize(100, 100);
    }
}

MainContentComponent::~MainContentComponent()
{
}

void MainContentComponent::paint (Graphics& g)
{
    g.drawImage(drawImage, 0, 0, getWidth(), getHeight(), 0, 0, drawImage.getWidth(), drawImage.getHeight());
}

void MainContentComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}

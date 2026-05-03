//CS112_A3_Part1_S20_20230734_20230770_20230719
// Author1 : loay talal ahdab 20230734 : black&white , flip image , crop image , resize image , purple
// Author2 : abdulmalek bazara 20230770 : gray scale , darken or lighten image ,merge ,edge detecting,oil painting
// Author3 : alwaleed mahmoud 20230719 : invert image ,rotate image,blur image,add frame to image,Infrared
//
//

//this program will let the user  load an image
//and apply a filter of his choice then save the image

#include <iostream>
#include <string>
#include "image_class.h"
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

void showMenu() {
    cout << "welcome ,,:\n";
    cout << "1. Load a new image\n";
    cout << "2. Apply filters \n";
    cout << "3. Save current image\n";
    cout << "4. Exit\n";
    cout << "Enter your choice:\n";
}


// function that takes dimensions from the user and crop the image with respect to the dimensions
void cropImage(Image &a) {

    int x, y, W, H;
    cout << "Enter the starting x-coordinate:\n";
    cin >> x;
    cout << "Enter the starting y-coordinate:\n";
    cin >> y;
    cout << "Enter the width of the crop area:\n";
    cin >> W;
    cout << "Enter the height of the crop area:\n";
    cin >> H;

    // check if the crop dimensions are valid
    if (x + W > a.width  || y + H > a.height ||  x < 0 ||  y < 0) {
        cout << "Invalid crop dimensions." << endl;
        return;
    }

    // Create a new image with the specified crop dimensions
    Image croppedImage(W, H);

    // Copy the pixel data from the original image to the new cropped image
    for (int i = 0; i < W; ++i) {
        for (int j = 0; j < H; ++j) {
            for (int k = 0; k < 3; ++k) {
                croppedImage(i, j, k) = a(x + i, y + j, k);
            }
        }
    }
    string filename;
    // Ask the user  to save the cropped image under a new name
    cout << "Enter filename to save (include extension like .jpg, .png, .bmp): \n";
    cin >> filename;
    croppedImage.saveImage(filename);
}
// Function to convert an image to black and white based on a threshold
int black_and_white(Image &a) {
    // Iterate over each pixel in the image by its width
    unsigned int threshold = 127;

    for (int i = 0; i < a.width; ++i) {
        for (int j = 0; j < a.height; ++j) {
            unsigned int avg = 0;
            // Calculate the average of the RGB values for the current pixel
            for (int k = 0; k < 3; ++k) {
                avg += a(i, j, k);// Sum the values of all color channels
            }
            avg /= 3;
// Determine the color (black or white) based on the average compared to the threshold
            unsigned int color = (avg > threshold) ? 255 : 0;
// Set the pixel's color to the determined black or white value
            for (int k = 0; k < 3; ++k) {
                // Apply the black or white value to all three RGB channels

                a(i, j, k) = color;
            }
        }
    }

    string filename;
    // Ask the user  to save the cropped image under a new name
    cout << "Enter filename to save (include extension like .jpg, .png, .bmp): \n";
    cin >> filename;
    a.saveImage(filename);

    return 0;
}


void flipHorizontal(Image &a) {
// Store the image's dimensions for easy access
    int width = a.width;
    int height = a.height;
    // Loop through each row of the image
    for (int y = 0; y < height; ++y) {
        // Only iterate through the first half of the columns in each row
        // because we'll be swapping pixels from one side to the other.
        for (int x = 0; x < width / 2; ++x) {
            // Iterate through each of the RGB color channels for the pixel
            for (int channel = 0; channel < 3; ++channel) {
                auto temp = a(x, y, channel);
                // Swap the current pixel's color channel with the corresponding
                // pixel's color channel on the opposite side of the image
                a(x, y, channel) = a(width - 1 - x, y, channel);

// Complete the swap by setting the opposite pixel's color channel
                // to the previously stored current pixel's color channel value
                a(width - 1 - x, y, channel) = temp;
            }
        }
    }
    // Ask the user  to save the cropped image under a new name
    string filename;
    cout << "Enter filename to save (include extension like .jpg, .png, .bmp): \n";
    cin >> filename;
    a.saveImage(filename);

}

void flipVertical(Image &a) {
// Store the image's dimensions for easy access
    int width = a.width;
    int height = a.height;
    // Loop through each row of the image
    for (int y = 0; y < height / 2; ++y) {
        for (int x = 0; x < width; ++x) {
            for (int channel = 0; channel < 3; ++channel) {
                auto temp = a(x, y, channel);
                a(x, y, channel) = a(x, height - 1 - y, channel);
                a(x, height - 1 - y, channel) = temp;
            }
        }
    }
    // Ask the user  to save the cropped image under a new name
    string filename;
    cout << "Enter filename to save (include extension like .jpg, .png, .bmp): \n";
    cin >> filename;
    a.saveImage(filename);
}

int gray(Image &a){
    // Iterate over each pixel in the image
    for (int x = 0; x < a.width; ++x) {
        for (int y = 0; y < a.height; ++y) {
            unsigned int grayScaleValue = 0; // Initialize the grayscale value

            // Sum the RGB values of the pixel
            for (int colorChannel = 0; colorChannel < 3; ++colorChannel) {
                grayScaleValue += a(x, y, colorChannel);
            }

            grayScaleValue /= 3; // Calculate the average to get the grayscale value

            // Assign the grayscale value to all three color channels
            for (int colorChannel = 0; colorChannel < 3; ++colorChannel) {
                a(x, y, colorChannel) = grayScaleValue;
            }
        }
    }

    string outputFilename;
    cout << "Enter filename to save (include extension like .jpg, .png, .bmp): \n";
    cin >> outputFilename;

    // Save the modified image to the specified file
    a.saveImage(outputFilename);

    cout << "The image has been converted to grayscale and saved as " << outputFilename << "." << endl;
    return 0;
}
int invert(Image &a) {



    // Loop through each pixel
    for(int i = 0; i < a.width; i++) {
        for(int j = 0; j < a.height; j++) {
            for (int k = 0; k < a.channels; k++) {
                // Invert the color by subtracting from the max value (255 for 8-bit color)
                unsigned char current = a(i, j, k);
                unsigned char inverted = 255 - current;
                a(i, j, k) = inverted; // Set the inverted value
            }
        }
    }
    string outputFilename;
    cout << "Enter filename to save (include extension like .jpg, .png, .bmp): \n";
    cin >> outputFilename;

    // Save the modified image to the specified file
    a.saveImage(outputFilename);

    cout << "The image has been converted to invert colors and saved as " << outputFilename << "." << endl;
    return 0;
}


void resizeImage(Image &a) {


    int newWidth, newHeight;
    cout << "Enter new width:\n";
    cin >> newWidth;
    cout << "Enter new height:\n";
    cin >> newHeight;

    // Check if new dimensions are valid
    if (newWidth <= 0 || newHeight <= 0) {
        cout << "Invalid dimensions.\n" << endl;
        return;

    }

    // Create a new image with the new dimensions
    Image resizedImage(newWidth, newHeight);


    double scaleX = static_cast<double>(a.width) / newWidth;
    double scaleY = static_cast<double>(a.height) / newHeight;


    for (int y = 0; y < newHeight; ++y) {
        for (int x = 0; x < newWidth; ++x) {
            int srcX = static_cast<int>(x * scaleX);
            int srcY = static_cast<int>(y * scaleY);
            for (int channel = 0; channel < 3; ++channel) { // Assuming RGB channels
                resizedImage.setPixel(x, y, channel, a.getPixel(srcX, srcY, channel));
            }
        }
    }

    string outputFilename;
    cout << "Enter filename to save (include extension like .jpg, .png, .bmp): \n";
    cin >> outputFilename;

    resizedImage.saveImage(outputFilename);

    cout << "The image has been resized and saved as " << outputFilename << "." << endl;

}

int purple(Image &a) {
    // Define the purple tint strength
    const unsigned char tintStrength = 64;

    for (int x = 0; x < a.width; ++x) {
        for (int y = 0; y < a.height; ++y) {
            // Get the current color values of the pixel
            unsigned char red = a(x, y, 0);
            unsigned char green = a(x, y, 1);
            unsigned char blue = a(x, y, 2);

            // calculate the amount by which to increase the red and blue channels
            unsigned char increase = (255 - red < tintStrength || 255 - blue < tintStrength) ?
                                     min(255 - red, 255 - blue) : tintStrength;
            unsigned char decrease = (green < increase) ? green : increase;

            // Increase the red and blue values to add the purple
            a(x, y, 0) = red + increase;
            a(x, y, 2) = blue + increase;

            // Decrease the green value

            a(x, y, 1) = green - decrease;
        }
    }

    string outputFilename;
    cout << "Enter filename to save (include extension like .jpg, .png, .bmp): \n";
    cin >> outputFilename;

    a.saveImage(outputFilename);

    cout << "The image has been resized and saved as " << outputFilename << "." << endl;
    return 0;
}


void rotateImage(Image &a) {
    cout << "Enter rotation degree (90, 180, 270): ";
    int angle;
    cin >> angle;

    if (angle == 90) {
        // Rotate 90 degrees
        Image b = Image(a.height, a.width); // Dimensions are swapped
        for (int y = 0; y < a.height; ++y) {
            for (int x = 0; x < a.width; ++x) {
                for (int channel = 0; channel < 3; ++channel) {
                    b.setPixel(a.height - 1 - y, x, channel, a.getPixel(x, y, channel));
                }
            }
        }
        string outputFilename;
        cout << "Enter filename to save (include extension like .jpg, .png, .bmp): \n";
        cin >> outputFilename;

        a = b;
        a.saveImage(outputFilename);

        cout << "The image has been rotated and saved as " << outputFilename << "." << endl;
    }
    else if (angle == 180) {
        // Rotate 180 degrees
        Image b = Image(a.width, a.height); // Dimensions stay the same
        for (int y = 0; y < a.height; ++y) {
            for (int x = 0; x < a.width; ++x) {
                for (int channel = 0; channel < 3; ++channel) {
                    b.setPixel(a.width - 1 - x, a.height - 1 - y, channel, a.getPixel(x, y, channel));
                }
            }
        }
        string outputFilename;
        cout << "Enter filename to save (include extension like .jpg, .png, .bmp): \n";
        cin >> outputFilename;

        a = b;
        a.saveImage(outputFilename);

        cout << "The image has been rotated and saved as " << outputFilename << "." << endl;
    }
    else if (angle == 270) {
        // Rotate 270 degrees
        Image b = Image(a.height, a.width); // Dimensions are swapped
        for (int y = 0; y < a.height; ++y) {
            for (int x = 0; x < a.width; ++x) {
                for (int channel = 0; channel < 3; ++channel) {
                    b.setPixel(y, a.width - 1 - x, channel, a.getPixel(x, y, channel));
                }
            }
        }
        string outputFilename;
        cout << "Enter filename to save (include extension like .jpg, .png, .bmp): \n";
        cin >> outputFilename;

        a = b;
        a.saveImage(outputFilename);

        cout << "The image has been rotated and saved as " << outputFilename << "." << endl;
    }

}
void blurImage(Image &a) {
    int blurChoice;
    cout << "Choose blur intensity:\n";
    cout << "1 - Weak Blur\n";
    cout << "2 - Normal Blur\n";
    cout << "3 - Strong Blur\n";
    cout << "Enter choice (1-3): ";
    cin >> blurChoice;

    int blurLevel;
    switch (blurChoice) {
        case 1:
            blurLevel = 3;  // Weak blur
            break;
        case 2:
            blurLevel = 5;  // Normal blur
            break;
        case 3:
            blurLevel = 10; // Strong blur
            break;
        default:
            cout << "Invalid choice. Using Normal Blur by default.\n";
            blurLevel = 5;
    }

    Image blurredImage(a.width, a.height);

    for (int y = 0; y < a.height; ++y) {
        for (int x = 0; x < a.width; ++x) {
            int redTotal = 0, greenTotal = 0, blueTotal = 0;
            int count = 0;

            // Sum the pixel values around the pixel (x, y) within the kernel
            for (int ky = -blurLevel; ky <= blurLevel; ++ky) {
                for (int kx = -blurLevel; kx <= blurLevel; ++kx) {
                    int px = x + kx;
                    int py = y + ky;

                    // Check bounds
                    if (px >= 0 && px < a.width && py >= 0 && py < a.height) {
                        redTotal += a.getPixel(px, py, 0);
                        greenTotal += a.getPixel(px, py, 1);
                        blueTotal += a.getPixel(px, py, 2);
                        count++;
                    }
                }
            }

            // Calculate the average and set the pixel value on the new image
            blurredImage.setPixel(x, y, 0, redTotal / count);
            blurredImage.setPixel(x, y, 1, greenTotal / count);
            blurredImage.setPixel(x, y, 2, blueTotal / count);
        }
    }

    string outputFilename;
    cout << "Enter filename to save the blurred image (include extension like .jpg, .png, .bmp): \n";
    cin >> outputFilename;

    if (blurredImage.saveImage(outputFilename)) {
        cout << "The image has been blurred (Intensity: ";
        switch (blurChoice) {
            case 1: cout << "Weak"; break;
            case 2: cout << "Normal"; break;
            case 3: cout << "Strong"; break;
            default: cout << "Normal";  // This should not happen
        }
        cout << ") and saved as " << outputFilename << "." << endl;
    } else {
        cerr << "Failed to save the blurred image." << endl;
    }
}

void addFrameToImage(Image &originalImage) {
    int frameWidth;  // Variable to store user input for frame width
    cout << "Enter the width of the frame: ";
    cin >> frameWidth;  // User inputs the frame width

    int frameType;  // Variable to store user choice of frame type
    cout << "Enter '1' for normal frame, '2' for fancy frame: ";
    cin >> frameType;  // User inputs the frame type

    // Frame color variables
    unsigned char frameRed, frameGreen, frameBlue;

    // Create a new image that will have the frame around the original image
    Image framedImage(originalImage.width + 2 * frameWidth, originalImage.height + 2 * frameWidth);

    // Set all pixels of the new image to the frame color
    for (int y = 0; y < framedImage.height; y++) {
        for (int x = 0; x < framedImage.width; x++) {
            if (x < frameWidth || y < frameWidth || x >= framedImage.width - frameWidth || y >= framedImage.height - frameWidth) {
                if (frameType == 1) {
                    // Normal frame (solid blue)
                    frameRed = 0;
                    frameGreen = 0;
                    frameBlue = 255;
                } else if (frameType == 2) {
                    // Fancy frame (gradient from blue to red)
                    frameRed = (unsigned char)(255 * y / framedImage.height);
                    frameGreen = 0;
                    frameBlue = (unsigned char)(255 * (1 - (double)y / framedImage.height));
                }
                framedImage.setPixel(x, y, 0, frameRed);
                framedImage.setPixel(x, y, 1, frameGreen);
                framedImage.setPixel(x, y, 2, frameBlue);
            } else {
                // Copy the pixel from the original image
                framedImage.setPixel(x, y, 0, originalImage(x - frameWidth, y - frameWidth, 0));
                framedImage.setPixel(x, y, 1, originalImage(x - frameWidth, y - frameWidth, 1));
                framedImage.setPixel(x, y, 2, originalImage(x - frameWidth, y - frameWidth, 2));
            }
        }
    }

    // Prompt the user for the filename where the framed image will be saved
    string saveFilename;
    cout << "Enter the filename to save the framed image (include extension like .jpg, .png, .bmp): ";
    cin >> saveFilename;

    // Save the framed image
    if (framedImage.saveImage(saveFilename)) {
        cout << "The image has been framed and saved as " << saveFilename << "." << endl;
    } else {
        cerr << "Failed to save the framed image." << endl;
    }
}
int Infrared(Image &img) {
    // Iterate over each pixel in the image
    for (int x = 0; x < img.width; ++x) {
        for (int y = 0; y < img.height; ++y) {
            // Get the current color values of the pixel
            unsigned char red = img.getPixel(x, y, 0);
            unsigned char green = img.getPixel(x, y, 1);
            unsigned char blue = img.getPixel(x, y, 2);

            // Infrared effect by increasing the red channel and decreasing green and blue channels
            unsigned char newRed = (red * 1.5 > 255) ? 255 : static_cast<unsigned char>(red * 1.5);
            unsigned char newGreen = (green * 0.5 > green) ? 0 : static_cast<unsigned char>(green - (green * 0.5));
            unsigned char newBlue = (blue * 0.5 > blue) ? 0 : static_cast<unsigned char>(blue - (blue * 0.5));

            // Set the new color values of the pixel
            img.setPixel(x, y, 0, newRed);
            img.setPixel(x, y, 1, newGreen);
            img.setPixel(x, y, 2, newBlue);
        }
    }

    string outputFilename;
    cout << "Enter filename to save (include extension like .jpg, .png, .bmp): ";
    cin >> outputFilename;

    // Save the modified image
    bool saved = img.saveImage(outputFilename);
    if (saved) {
        cout << "The image has been modified to simulate an infrared effect and saved as " << outputFilename << "." << endl;
    } else {
        cout << "Failed to save the image." << endl;
    }

    return 0;
}

int lighten(Image& image1){
    // Iterate over all pixels in the image
    for (int i = 0; i < image1.width; ++i) {
        for (int j = 0; j < image1.height; ++j) {
            // Get the color components of the current pixel
            int red = image1(i, j, 0);
            int green = image1(i, j, 1);
            int blue = image1(i, j, 2);

            red = red + 23;
            green = green  + 27;
            blue = blue + 27;
            if (blue>255)
                blue=255;
            if (red>255)
                red=255;
            if (green>255)
                green=255;


            // Set the new color values back to the image
            image1.setPixel(i, j, 0, red);
            image1.setPixel(i, j, 1, green);
            image1.setPixel(i, j, 2, blue);
        }
    }
    string outputFilename;
    cout << "Enter filename to save (include extension like .jpg, .png, .bmp): \n";
    cin >> outputFilename;

    image1.saveImage(outputFilename);

    cout << "The image has been lightened and saved as " << outputFilename << "." << endl;
    return 0;
}

int darken(Image& image1){
    // Iterate over all pixels in the image
    for (int i = 0; i < image1.width; ++i) {
        for (int j = 0; j < image1.height; ++j) {
            // Get the color components of the current pixel
            int red = image1(i, j, 0);
            int green = image1(i, j, 1);
            int blue = image1(i, j, 2);

            // Make the pixel dimmer
            red = red / 2;
            green = green / 2;
            blue = blue / 2;


            // Set the new color values back to the image
            image1.setPixel(i, j, 0, red);
            image1.setPixel(i, j, 1, green);
            image1.setPixel(i, j, 2, blue);
        }
    }
    string outputFilename;
    cout << "Enter filename to save (include extension like .jpg, .png, .bmp): \n";
    cin >> outputFilename;

    image1.saveImage(outputFilename);

    cout << "The image has been darkened and saved as " << outputFilename << "." << endl;
    return 0;
}

int merge (Image& image) {
    string filen1, filen2;
    cout << "Please enter the first image file name: ";
    cin >> filen1;
    cout << "Please enter the second image file name: ";
    cin >> filen2;

    Image image1(filen1);
    Image image2(filen2);

    // Check if images have the same dimensions

    Image newsize(image1.width, image1.height); // Create a new image object with the dimensions of image1

    if(image1.width > image2.width)
    {
        newsize.width = image2.width;
    }
    else
    {
        newsize.width = image1.width;
    }

    if(image1.height > image2.height)
    {
        newsize.height = image2.height;
    }
    else
    {
        newsize.height = image1.height;
    }

    for (int i = 0; i < newsize.width; ++i) {
        for (int j = 0; j < newsize.height; ++j) {
            for (int k = 0; k < 3; ++k) { // Iterate over each color channel
                // Copy the pixel from the old position in the source image to the new position in the resized image
                newsize(i, j, k) = image2(newsize.width, newsize.height, k);
            }
        }
    }
    //image2 = newsize; // Update image2 to be the resized image

    for (int i = 0; i < newsize.width; ++i) {
        for (int j = 0; j < newsize.height; ++j) {
            for (int k = 0; k < 3; ++k) { // Iterate over each color channel

                int mergedColor = (image1(i, j, k) + image2(i, j, k)) / 2;
                // Set the pixel in the first image to the merged color
                newsize(i, j, k) = mergedColor;
            }
        }
    }
    string outputFilename;
    cout << "Enter filename to save (include extension like .jpg, .png, .bmp): \n";
    cin >> outputFilename;

    image.saveImage(outputFilename);

    cout << "The images have been merged and saved as " << outputFilename << "." << endl;
    return 0;
}

int edge(Image& image1) {

    unsigned int threshold = 127;
    black_and_white(image1);

    for (int i = 1; i < image1.width - 1 ; i++) {
        for (int j = 1; j < image1.height - 1; j++) {
            for (int k = 0; k < 3; ++k) {
                int currentPixel = image1(i, j, k);  // Assuming single channel for B&W image
                //int leftPixel = image1(i - 1, j, k);
                int rightPixel = image1(i + 1, j, k);
                //int topPixel = image1(i, j - 1, k);
                int bottomPixel = image1(i, j + 1, k);

                // Simple edge detection by difference
                if ( abs(currentPixel - rightPixel) > threshold|| abs(currentPixel - bottomPixel) > threshold) {
                    image1(i, j, k) = 0;  // Highlight edge
                } else {
                    image1(i, j, k) = 255;  // Non-edge
                }
            }
        }
    }string outputFilename;
    cout << "Enter filename to save (include extension like .jpg, .png, .bmp): \n";
    cin >> outputFilename;

    image1.saveImage(outputFilename);

    cout << "The image has been edged and saved as " << outputFilename << "." << endl;
    return 0;}


void applyOilPaintingEffect(Image &image1) {
    int radius = 5;  // Radius for effect
    int intensityLevels = 20;  // Number of intensity levels

    // Setup structures to store intensity data and averages
    vector<vector<vector<int>>> intensityCount(image1.width, vector<vector<int>>(image1.height, vector<int>(intensityLevels, 0)));
    vector<vector<vector<int>>> averageR(image1.width, vector<vector<int>>(image1.height, vector<int>(intensityLevels, 0)));
    vector<vector<vector<int>>> averageG(image1.width, vector<vector<int>>(image1.height, vector<int>(intensityLevels, 0)));
    vector<vector<vector<int>>> averageB(image1.width, vector<vector<int>>(image1.height, vector<int>(intensityLevels, 0)));

    // Step 1: Accumulate intensity and color data within the specified radius
    for (int x = 0; x < image1.width; ++x) {
        for (int y = 0; y < image1.height; ++y) {
            for (int dx = -radius; dx <= radius; ++dx) {
                for (int dy = -radius; dy <= radius; ++dy) {
                    int nx = x + dx, ny = y + dy;
                    if (nx >= 0 && nx < image1.width && ny >= 0 && ny < image1.height) {
                        int r = image1(nx, ny, 0);
                        int g = image1(nx, ny, 1);
                        int b = image1(nx, ny, 2);
                        int curIntensity = (r + g + b) / 3 * intensityLevels / 255;
                        intensityCount[x][y][curIntensity]++;
                        averageR[x][y][curIntensity] += r;
                        averageG[x][y][curIntensity] += g;
                        averageB[x][y][curIntensity] += b;
                    }
                }
            }
        }

    }

    // Step 2 & 3: Find dominant intensity and set pixel colors
    for (int x = 0; x < image1.width; ++x) {
        for (int y = 0; y < image1.height; ++y) {
            int maxIntensity = 0;
            int maxIndex = 0;
            for (int i = 0; i < intensityLevels; ++i) {
                if (intensityCount[x][y][i] > maxIntensity) {
                    maxIntensity = intensityCount[x][y][i];
                    maxIndex = i;
                }
            }

            // Apply the most common intensity color to the pixel
            if (maxIntensity > 0) {  // Avoid division by zero
                image1(x, y, 0) = averageR[x][y][maxIndex] / maxIntensity;
                image1(x, y, 1) = averageG[x][y][maxIndex] / maxIntensity;
                image1(x, y, 2) = averageB[x][y][maxIndex] / maxIntensity;
            }
        }
    }
    string outputFilename;
    cout << "Enter filename to save (include extension like .jpg, .png, .bmp): \n";
    cin >> outputFilename;

    image1.saveImage(outputFilename);

    cout << "The image has been oil painted and saved as " << outputFilename << "." << endl;
}

int main() {
    bool running = true;
    string filename;
    Image image,image2;
    while (running) {
        showMenu();
        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter filename to load:\n";
                cin >> filename;
                if (image.loadNewImage(filename)) {
                    cout << "Image loaded successfully.\n";
                } else {
                    cout << "Failed to load image.\n";
                }
                break;
            case 2:
                int choice2;
                cout << "1-Black and white Filter\n";
                cout << "2-Flip image \n";
                cout << "3-Crop image\n";
                cout << "4-gray scale\n";
                cout << "5-invert colors\n";
                cout << "6-resize image \n";
                cout << "7-purple scale \n";
                cout << "8-rotate image \n";
                cout << "9-blur image \n";
                cout << "10-add frame to image \n";
                cout << "11-Infrared the image \n";
                cout << "12-darken or lighten image \n";
                cout << "13-merge \n";
                cout << "14-edge detecting \n";
                cout << "15-oil painting \n";

                cin >> choice2;
                if (choice2==1){
                    black_and_white(image);
                }
                else if (choice2==2) {
                    int choice3;
                    cout << "1-Flip image horizontal\n";
                    cout << "2-Flip image vertical\n";
                    cin >> choice3;
                    if (choice3 == 1) {
                        flipHorizontal(image);

                        cout << "Image has been flipped horizontally .\n";
                    } else if (choice3 == 2) {
                        flipVertical(image);
                        cout << "Image has been flipped vertically.\n";
                    }
                    else;
                    cout <<" invalid choice\n";
                    break;
                }
                else if (choice2==3) {
                    cropImage(image);
                    break;
                }
                else if (choice2==4){
                    gray(image);
                }

                else if (choice2==5){
                    invert(image);
                }

                else if (choice2==6){
                    resizeImage(image);
                }

                else if (choice2==7){
                    purple(image);
                }
                else if (choice2==8){
                    rotateImage(image);
                }
                else if (choice2==9){
                    blurImage(image);
                }
                else if (choice2==10){
                    addFrameToImage(image);
                }
                else if (choice2==11){
                    Infrared(image);
                }
                else if (choice2==12){
                    int choice4;
                    cout << "1-Lighten image\n";
                    cout << "2-Darken image\n";
                    cin >> choice4;
                    if (choice4 == 1) {
                        lighten(image);

                        cout << "Image has been lighten .\n";
                    } else if (choice4 == 2) {
                        darken(image);
                        cout << "Image has been darken.\n";
                    }
                    else;
                    cout <<" invalid choice\n";
                    break;
                }
                else if (choice2==13){
                    merge(image);
                }
                else if (choice2==14){
                    edge(image);
                }
                else if (choice2==15){
                    applyOilPaintingEffect(image);
                }
                break;

            case 3:
                cout << "Enter file name to save:\n";
                cin >> filename;
                if (image.saveImage(filename)) {
                    cout << "Image saved successfully.\n";
                } else {
                    cout << "Failed to save image.\n";
                }
                break;

            case 4:
                running = false;
                break;
            default:
                cout << "Invalid choice, please try again.\n";

        }
    }

    return 0;
}
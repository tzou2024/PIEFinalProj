# PIE Final Project

GREMLIN is a whiteboard traversing robot that converts unser-inputted images to dot-images that are printed onto the whiteboard.

## File Structue

`mostrecent.mlx` contains our image processing, which was done in matlab. Input and image and it saves the rescales it, grayscales it, converts to black and white, and vectorizes it. 

`matlabversion.py` contains a short processing code to reformat the matlab vector.

`mickeydraw.ino` contains code to print the image onto the whiteboard given an image vector and an image height.

The rest of the files are test code for the stepper-motor library.

## How to Use

Put image path into matlab (can change image resolution), take the vector and copy paste it into python to format it, copy and paste reformatted string into arduino along with the image height  (can change print resolution/aspect ratio).
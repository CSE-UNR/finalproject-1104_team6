Data

File pointers
Menu choice
Edit choice - integer to store user's edit selection
Filename 
Image size 
Rows and columns
Brightness levels

Functions

main()
Functionality: Entry point of the program, displays the main menu, and controls program flow
Algorithm:
Initialize image array, file pointer, and other necessary variables
Display the main menu and prompt the user for their choice
Based on the user's choice, call the corresponding function (loadImage(), displayImage(), editImage(), or exitProgram())
Repeat steps 2-3 until the user chooses to exit the program
loadImage()

Functionality: Loads image data from a file specified by the user
Algorithm:
Prompt user for file 
Open file and read image dimensions
Allocate memory for image array based on the dimensions
Read the pixel values from the file into the image array
Close the file
displayImage()

Functionality: Displays the current image to the screen.
Algorithm:
Loop through each pixel in the image array
Map the brightnes sof each pixel to the corresponding character 
Print the characters to the screen row by row

editImage()

Functionality: Allows user to edit the current image
Algorithm:
Display the edit menu and prompt user for their choice
Based on the user's choice, call the corresponding edit function (cropImage(), dimImage(), brightenImage(), or rotateImage())
After editing, prompt the user to save the edited image to a file

cropImage()

Functionality: Allows the user to specify a smaller section of the original image
Algorithm:
Prompt the user for the coordinates for the cropped image 
Copy the specified region from the original image to a new image array
dimImage()

Functionality: Decreases the brightness of each pixel in the image.
Algorithm:
Loop through each pixel in the image array
Decrease the brightness value of each pixel by one
brightenImage()

Functionality: Increases the brightness of each pixel in the image
Algorithm:
Loop through each pixel in the image array
Increase the brightness value of each pixel by one
rotateImage()


Functionality: Rotates the image by 90 degrees
Algorithm:
Create a new image array with dimensions swapped 
Copy each pixel from the original image to the rotated image array in the appropriate position

saveImage()

Functionality: Saves the current image to a fileAlgorithm:
Prompt the user for the filename to save the image
Open file 
Write image dimensions and pixel values to the file
Close the fil




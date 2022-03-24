# 2017 Fall Image Processing (14871-01)
To understand basic concepts and methodologies for digital image processing.

## What is 'Sweko Lens'?
Simple implementation of Office Lens of Microsoft which is a handy capture app that turns your smartphone into a pocket scanner.

## Features
1. Take a picture including receipts, business cards, menus, whiteboards, or sticky notes with user webcam.
2. Pick four corners of a document on the image.
3. SweKo Lens crops, enhances, and shows it to you.

## Desine of a program
The program is a console based application for your computer, it takes four points which is generated from the mouse. The user input a filename or takes a webcam picture and then gives four left-clicks (in a specific order: top-left, top-right, bottom-left, bottom-right) around the desired object in the picture. After the program got four points, it will crop the image to fit the desired object and perform a transformation algorithm to rotate the image to a straight position, resulting in a bird-eye overview. 

The program is built of three components `main`, `myFunc` and `ptr`.

**Main**: To handle input and output from the user and display the original and processed image.

**myFunc**: To Contain image processing functions used by Main.
- Grayscale
- Binarization
- Sobel
- Gaussian
- Corner_response_func: to find the corners
- Calcptm: to calculate a 8x8 projection matrix.  
- Warp: to perform a matrix multiplication to transform the image to a bird-view.
- 
**ptr**: A simple data structure which stores the x, y-coordinates of four points.

## Results
Before-and-after looks of a receipts, notes, and documents captured and processed by SweKo Lens!

<img src="/result1.PNG" height="200"></img>

<img src="/result2.PNG" height="500"></img>

Please refer to [Perspective Projection and Transformations](https://www.cs.cornell.edu/courses/cs4670/2018sp/lec16-image-formn.pdf)

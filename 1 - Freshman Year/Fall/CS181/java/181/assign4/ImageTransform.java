/*
 *
 * assign4/ImageTransform.java
 * (c) 2014  
 *
 */

package assign4;

import java.awt.Point;
import java.awt.Rectangle;

/**
 * The ImageTransform class represents a warping image transform.
 *
 * @author Antonio R. Nicolosi
 * @author Stan Rosenberg
 */

public class ImageTransform {
    /**
     * pixels of the source image (in row-major order)
     */
    int[] srcPixels;

    /**
     * width of the source image
     */
    int width;
    /**
     * height of the source image
     */
    int height;

    /**
     * control point for the warping
     */
    Point controlPt;

    Point midPoint;

    /**
     * Vanilla constructor for the ImageTransform class 
     */
    public ImageTransform(int[] srcPixels, int width, int height, 
			  Point controlPt) {
	this.srcPixels = srcPixels;     // scan-line is width-many pixels
	this.width = width;
	this.height = height;
   	this.controlPt = controlPt;
    this.midPoint = new Point(width/2, height/2);
    }

    public ImageTransform(int[] srcPixels, int width, int height, Point controlPt, Point newMidPoint)
    {
        this.srcPixels = srcPixels;
        this.width = width;
        this.height = height;
        this.controlPt = controlPt;
        this.midPoint = newMidPoint;


    }

    /**
     * The transform method implements the high-level warping logic
     *
     * @return int[] containing the pixels of the warped image.  
     *         Notice that the scan-line for the warped image is the
     *         same as for the original image, that is,
     *         this.width-many pixels.
     */
    public int[] transform() {
	/*
	 * Recall from the assignment handout how the warping works:
	 * The image is split into 4 quadrants (rectangles with the
	 * same dimension). The control point defines 4
	 * quadrilaterals. (Each quadrilateral has one vertex
	 * corresponding to the control points. The remaining vertices
	 * correspond to point on the border of the image, and are the
	 * same as the vertices for the corresponding quadrant.)  For
	 * each quadrant, we invoke warpRegion which maps the
	 * quadrilateral into the rectangle.
	 */

	// create the destination pixel array

	// YOUR CODE HERE

    int[] destinationArray = new int[width*height];

    //actual rectangle is RTZX, with Midpoint V



    Point R = new Point(0,0); //top left
    Point T = new Point(width, 0); //top right
    Point Z = new Point(width, height); //bottom right
    Point X = new Point(0, height); //bottom left

    Point[] mainRectangle = {R, T, Z, X};

    int midpointWidth = midPoint.x;
    int midPointHeight = midPoint.y;  //width and height of midpoint (Point V)

    Point V = midPoint; //control point, defined as center of rectangle



	// Quadrant 1

	// First Quadrant is RSVU, with S and U being new points

    Point S = new Point(midpointWidth, 0);
    Point U = new Point(0, midPointHeight);

    Point[] firstQuadrant = {R, S, V, U};
    Rectangle r1 = new Rectangle(R.x, R.y, (S.x - R.x), (V.y - S.y));

    warpRegion(destinationArray, r1, R, S, controlPt, U);

   //Point[] firstQuadrilateral = {R, S, controlPt, U};





	
	// Quadrant 2

	// Second Quadrant is STWV

    Point W = new Point(width, midPointHeight);

    Point[] secondQuadrant = {S, T, W, V};
    Rectangle r2 = new Rectangle(S.x, S.y, (T.x - S.x), (W.y - S.y));

    warpRegion(destinationArray, r2, S, T, W, controlPt);

   // Point[] secondQuadrilateral = {S,T,W,controlPt};





	// Quadrant 3

	// Third Quadrant is VWZY

    Point Y = new Point(midpointWidth, height);

    Point[] thirdQuadrant = {V, W, Z, Y};
    Rectangle r3 = new Rectangle(V.x, V.y, (W.x - V.x), (Z.y - W.y));

    warpRegion(destinationArray, r3, controlPt, W, Z, Y);

    //Point[] thirdQuadrilateral = {controlPt, W, Z, Y};



	// Quadrant 4

	// Fourth Quadrant is UVYX

    Point[] fourthQuadrant = {U, V, Y, X};
    Rectangle r4 = new Rectangle(U.x, U.y, (V.x - U.x), (Y.y - V.y));

    warpRegion(destinationArray, r4, U, controlPt, Y, X);

    //Point[] fourthQuadrilateral = {U, controlPt, Y, X};

	

	// Return the result of warping transformation
    return destinationArray;

	// YOUR CODE HERE
    }

    

    /**
     * The warpRegion method performs the actual image warping
     * transformation.
     * 
     * @param dstPixels   int[] where the warped image is being stored 
     * @param r           Rectangle defining the (logical) quadrant
     *                    within the destination pixels that is to be
     *                    computed by this invocation of the method
     * @param nw          North-west (upper-left) corner of the
     *                    quadrilater in the original image that is
     *                    being warped
     * @param ne          North-east (upper-right) corner of the
     *                    quadrilater in the original image that is
     *                    being warped
     * @param sw          South-west (lower-left) corner of the
     *                    quadrilater in the original image that is
     *                    being warped
     * @param se          South-east (lower-right) corner of the
     *                    quadrilater in the original image that is
     *                    being warped
     */
    protected void warpRegion(int[] dstPixels, Rectangle rect, 
			      Point nw, Point ne, Point se, Point sw) {
	System.out.println("Warping quadrilateral at ");
	System.out.println(nw);
	System.out.println(ne);
	System.out.println(sw);
	System.out.println(se);
	System.out.println("into rectangle");
	System.out.println(rect);
     
	// YOUR CODE HERE
    double newX;
    double newY;


    double alpha = 0;
    double beta = 0;

    int n = rect.width;
    int m = rect.height;

    int newPixel;

    //P' = D' + (C' - D')alpha + (A' - D')beta +(D' - C' + B' - A')alpha(beta)
    //P' = nw + (ne - nw)alpha + (sw - nw)beta + (nw-ne + se - sw)alpha(beta)

    for(int c = 0; c<rect.width; c++)
    {
        alpha = (double)c/(double)n;
        for(int r = 0; r<rect.height; r++)
        {
            beta = (double)r/(double)m;

            newX = nw.x + (ne.x - nw.x)*alpha + (sw.x - nw.x)*beta + (nw.x - ne.x + se.x - sw.x)*alpha*beta;
            newY = nw.y + (ne.y - nw.y)*alpha + (sw.y - nw.y)*beta + (nw.y - ne.y + se.y - sw.y)*alpha*beta;

            newPixel = getPixel(newX, newY);

            dstPixels[(c+rect.x) + (r+rect.y)*width] = newPixel;

        }


    }

    //return dstPixels[];


  		   
    }

    /**
     * Return the pixel at (x,y)
     */
    public int getPixel(int x, int y) {
	   return srcPixels[x + y*width];
    }

    /** 
     * Better version of the getPixel method with color interpolation 
     * (extra-credit 1).
     */
    public int getPixel(double x, double y) {
	/* 
	 * The idea of color interpolation is the following.  Say that
	 * you want to access the fractionary pixel at coordinates
	 * (3.7,4.4).  The default implementation (no color
	 * interpolation, see below) just truncates things and get the
	 * pixel at (3,4).  This is unsatisfactory, because we are
	 * loosing the information encoded in the fractional part: in
	 * particular, the pixel we wanted had more overlap (42%) with
	 * (4,4) than with (3,4) (18%).
         *
         * Thresholdizing the "fractionary" pixel so that it agrees
         * with the "actual" pixel that maximizes overlap is a better
         * option than the default implementation, but it still is not
         * very "smooth".  Instead, color interpolation averages the
         * four real pixels that have overlap with the fractionary
         * pixel (in the example, these are (3,4), (4,4), (3, 5), and
         * (4,5)), weighting them by their relative overlap ratio
         * (respectively 18%, 42%, 12%, and 28%).
         *
         * A complication with interpolating pixels arises because of
         * the way colors are encode as Java int's.  In the RGB model,
         * the color of each pixel is described by three 8-bit
         * unsigned numbers, respectively for the red, green, and blue
         * components of the color (hence the name).  These three
         * 8-bit unsigned are packed together into a Java int as
         * follows: the "blue" byte is stored in the least-significant
         * 8 bits of the int; the "green" byte is stored in the 8 bits
         * immediately to the left; and the "red" byte is stored in
         * the 8 bits further to the left.  (The 8 most-significant
         * bits of the int do not matter under the RGB color model.)
         * 
         * So in order to do color interpolation, you will have to do
         * bitwise manipulations to get to the right values; scale
         * them by the corresponding weights, yielding a
         * floating-point value; convert back to whole numbers; and
         * pack the three components back into the int.  You might
         * want to define a helper class (or at least some helper
         * static methods) for carrying out this "color arithmetic".
	 * 
	 */

	//Default implementation is no interpolation.	
	   return getPixel ((int) x, (int) y);
    }
}

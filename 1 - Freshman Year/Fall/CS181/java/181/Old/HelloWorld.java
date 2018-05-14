/*
 * HelloWorld.java
 * 
 * Straightforward java class to sanity-check the setup
 *
 * 20100902
 * 
 * (c) 2008--2014 Antonio R. Nicolosi
 *
 */

/**
 * The HelloWorld class in Java 
 */
public class HelloWorld {

    /**
     * The main method prints out a statement on standard output
     * using the System.out predefined object
     */
    public static void main(String[] args) {
	System.out.println(hi());

    }

    public static int derp(int x){
	int y = (int)x*7;
	x = y*y;
	return x;

    }
    
    public static String hi(){
	return "hi";
    }

    public static String DecimalToBinary(int x)
    {
	String result = new String("");
	int r = 0;


	while(x > 1)
        {
	    r = x%2;
	    x /= 2;
	    result += r;
	}
	return "hi";
	//return ReverseString(result);
    }
    
    public static String ReverseString(String derp)
    {
	String result = "";
	for(int i = derp.length() - 1; i>=0; i--){
	    result += derp.charAt(i);
	    
	}
	return result;

    }

}

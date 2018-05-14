/*
     Adam Gincel
     CS181 Lab A
     
     IntSquareRoot.java - takes a string argument of one integer and returns the integer square root in two separate ways.
     

     I pledge my honor that I have abided by the Stevens Honor System.


     Submit as a .tgz with
     tar czvf name.tgz sub-dir/

     extract with
     tar xzvf name.tgz

 */

public class IntSquareRoot{

    public static void main(String[] args)
    {
	String number = args[0];

	
	String regex = "-?[0-9]+"; //string can contain a negative sign at the front, then only digits
	if(!number.matches(regex))
	    {
		System.out.println("That's not an integer!");
		System.exit(0);
	    }


	int numberValue = stringToInt(number);

	long startTime = System.nanoTime(); 
	int sqrtWithSums = sqrtBySums(numberValue);
	long sumTime = System.nanoTime() - startTime;
	System.out.println("Square root by sums: " + sqrtWithSums + ". Time taken: " + sumTime + " nanoseconds.");

	startTime = System.nanoTime();
	int sqrtWithDivs = sqrtByDivs(numberValue);
	long divTime = System.nanoTime() - startTime;
	System.out.println("Square root by divs: " + sqrtWithDivs + ". Time taken: " + divTime + " nanoseconds.");
	
    }

    public static int stringToInt(String s)
    {
	boolean sign = false;

	if(s.charAt(0) == '-') //if there's a negative sign, set sign to true then remove the - from the string for parsing
	    {
		sign = true;
		s = s.substring(1);

	    }
       

	int stringValue = 0;
	for(int i = 0;i < s.length(); i++) //adds current digit after multiplying previous value by ten; takes care of place value.
	    {
		stringValue = (stringValue * 10) + (s.charAt(i) - '0');
	    }

	if(sign)
	    stringValue *= -1; //if there was a negative sign, make the value negative
	
	return stringValue;

    }

    public static int sqrtBySums(int num)
    {
	if(num<0)
	    return -1;

	int bound = 0;

	int result = 0;

	int i = 1;

	while(result < num)
	    {                 //this will finish with result being >= num, and bound being our answer or 1 greater than it.
		bound++;
		result = 0;
		for(i = 1;i <= bound; i++) //summation from i=1 to bound of the equation (2i - 1)
		    {
			result += ((2*i) - 1);
		    }

	    }

	int sqrt = 0;
	
	if(result == num)
	    sqrt = bound;
	else if(result > num)
	    sqrt = bound-1;


	return sqrt;
    }

    public static int sqrtByDivs(int num)
    {
	if(num<0)
	    return -1;

	int x = num;
	int y = 1;

	while(x>y)
	    {
		//System.out.println("x: " + x);
		//System.out.println("y: " + y + "\n");
		
		x = (x+y)/2;
		y = num/x;

		//System.out.println(num + "/" + x);
	    }

	return x;


    }


    







}
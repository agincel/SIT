/*
	Adam Gincel
	Binary Fraction to Decimal - takes 1 arg, accepts 0s, 1s, .s, and _s


	I swear by my honor that I have abided by the Stevens Honor System.
*/

public class BinaryFractionToDecimal
{

    public static void main(String[] args)
    {
	String binary = args[0];

	String regex = "[01._]+";

	if(!binary.matches(regex))
	    {
		System.out.println("You used an invalid character!");
		System.exit(0);
	    }

        int wholeLocation = binary.indexOf(".");
	int antiPeriodLocation = binary.indexOf("_");


	int derp = 0;

	if(wholeLocation != -1)
	    derp -= 1;

	if(antiPeriodLocation != -1)
	    derp -= 1;

	System.out.println(derp);
        

	
	

	String whole = "0";
	if(wholeLocation != -1) //if there's a . the int is from 0 to that .
	    whole = binary.substring(0,wholeLocation);
	else if(antiPeriodLocation != -1) //if there's a _ and no . then the int is from 0 to that
	    whole = binary.substring(0, antiPeriodLocation);
	else //if there's neither then the entire thing is just an int
	    whole = binary;


	
	String antiPeriod = "0";

	if(wholeLocation != -1 && antiPeriodLocation != -1) // if there's both a . and a _ the antiPeriod is between them
	    antiPeriod = binary.substring(wholeLocation+1, antiPeriodLocation);
	else if(wholeLocation != -1 && antiPeriodLocation == -1) //if there's only a . then the antiperiod is everything after it
      	    antiPeriod = binary.substring(wholeLocation+1);


	String period = "0";
	if(antiPeriodLocation != -1) //if there's a _ the antiperiod is everything after it
	    period = binary.substring(antiPeriodLocation+1);

     	if(period.equals(""))
	    period = "0";

	int periodOperandThing = (int)Math.pow(2, antiPeriod.length()); //this is used for a thing
	if(periodOperandThing <= 0)
	    periodOperandThing = 1;

	

	System.out.println(whole);
	System.out.println(antiPeriod);
	System.out.println(period);
	System.out.println("");

	
	int wholeDecimal = BinaryToDecimal(whole);
	double antiPeriodDecimal = BinaryDecimalToDecimalDecimal(antiPeriod);

	double decimalResult = (double)wholeDecimal + antiPeriodDecimal;
	String decimalResult1 = Double.toString(decimalResult);


	int periodInt = BinaryToDecimal(period);
	String herp = Integer.toString(periodInt);
	int periodIntDivision = periodOperandThing*((int)Math.pow(2, period.length()) - 1);
	String herpderp = Integer.toString(periodIntDivision);

	String periodFinal = herp + "/" + herpderp;
	





	
	System.out.println(decimalResult1 + " + " + periodFinal);





	

    }


     public static int BinaryToDecimal(String binaryValue)
    {

	String number = binaryValue;
	
	int decimalResult = 0;
	int base = 2;
	int x = 0;
	int exponent = 0;
	int value = 0;
	int digitValue = 0;


	for(int i = number.length() - 1; i >=0; i--)
	    {
		x = (int)number.charAt(i) - '0'; //get digits from right to left. subtract the char of 0 because chars are annoying
		//System.out.println(x);

		exponent = (number.length() - 1) - i; //get power of base for that digit 
		//	System.out.println(exponent);

		value = (int)Math.pow((int)base, exponent); //raise base^power
		//	System.out.println(negaValue);

		digitValue = x*value; //decimal value for digit

		decimalResult += digitValue; //add decimal value to result
	    }

	return decimalResult;

    }

    public static double BinaryDecimalToDecimalDecimal(String binaryValue)
    {
	double decimalResult = 0;
	int base = 2;
	int x = 0;
	int exponent = 0;
	double value = 0;
	double digitValue = 0;

	for(int i = 0; i<binaryValue.length(); i++)
	    {
		x = (int)binaryValue.charAt(i) - '0';
		//	System.out.println("Digit: " + x);

		exponent = (-1)*(i+1);

		value = Math.pow(base, exponent);

		digitValue = x*value;
		//	System.out.println(digitValue);

		decimalResult += digitValue;
		//	System.out.println("Decimal Result: " + decimalResult);


	    }

	return decimalResult;
    }
    
}

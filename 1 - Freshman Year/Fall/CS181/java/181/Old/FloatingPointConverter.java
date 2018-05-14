/* Floating Point Converter - Adam Gincel
 * CS181 Lab 1
 *
 *
 * I pledge my honor that I have abided by the Stevens Honor System.
 *

 */

public class FloatingPointConverter
{
    
    public static void main(String args[])
    {
	String binary = args[0];


	if(binary.length() != 16) //argument given isn't 16 characters long
	    {
		System.out.println("That isn't 16 bits!");
		System.exit(0);

	    }

	String regex = "[0-1]+"; //check for only 0s and 1s
	if(!binary.matches(regex))
	    {
		System.out.println("That isn't in binary!");
		System.exit(0);

	    }
        

	String sign = binary.substring(0,1);
	String exponent = binary.substring(1,6);

	boolean expZeros = exponent.equals("00000");
	boolean expOnes = exponent.equals("11111");

	String value = "";
	if(!expZeros)
	    value = "1" +  binary.substring(6);
	else
	    value = "0" + binary.substring(6);
	System.out.println(value);

	boolean valZeros = value.equals("10000000000");
	
	
	//System.out.println(sign);
	//System.out.println(exponent);
	//System.out.println(value);

	//	double binaryValue = BinaryDecimalToDecimalDecimal(value);
	double binaryValue = BinaryDecimalToDecimalDecimal(args[0]);

	if(!expZeros)
	    binaryValue += 1;

	int exponentValue = BinaryToDecimal(exponent);
	exponentValue -= 14;

	double almostFinal = binaryValue * Math.pow(10, exponentValue);

	double finalValue = almostFinal;

	if(sign.equals("1"))
	    finalValue *= -1;

	

	if(expZeros && valZeros)
	    System.out.println("0.0");
	else if(sign.equals("0") && expOnes && valZeros)
	    System.out.println("Infinity");
	else if(sign.equals("1") && expOnes && valZeros)
	    System.out.println("-Infinity");
	else if(expOnes && !valZeros)
	    System.out.println("NaN");
	else	
	    System.out.println(finalValue);
	
	
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

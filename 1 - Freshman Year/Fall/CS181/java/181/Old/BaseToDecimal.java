/*
  Adam Gincel CS181 Lab A
  September 5, 2014

  Convert any base number system to Decimal

  Program takes 2 arguments (base, number) in command line.



  I swear by my honor that I have abided by the Stevens Honor System.

//zakram@stevens.edu - TA's Email address
 */

public class BaseToDecimal{

    public static void main(String[] args){
	int base = Integer.parseInt(args[0]);
	String number = args[1];
	//	System.out.println(Negabinary);

	int decimalResult = 0;

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

	System.out.println(decimalResult); //print result

    }




}

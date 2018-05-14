/*
  Adam Gincel CS181 Lab A
  September 4, 2014

  Convert Negabinary (base -2 number system) to Decimal

  Program takes 1 argument in command line.



  I swear by my honor that I have abided by the Stevens Honor System.

//zakram@stevens.edu - TA's Email address
 */

public class NegabinaryToDecimal{

    public static void main(String[] args){
	String negabinary = args[0];
	//	System.out.println(Negabinary);

	int decimalResult = 0;

	int x = 0;
	int exponent = 0;
	int negaValue = 0;
	int digitValue = 0;


	for(int i = negabinary.length() - 1; i >=0; i--)
	    {
		x = (int)negabinary.charAt(i) - '0'; //get digits from right to left. subtract the char of 0 because chars are annoying
		//System.out.println(x);

		exponent = (negabinary.length() - 1) - i; //get power of -2 for that digit 
		//	System.out.println(exponent);

		negaValue = (int)Math.pow((int)-2, exponent); //raise -2^power
		//	System.out.println(negaValue);

		digitValue = x*negaValue; //decimal value for digit

		decimalResult += digitValue; //add decimal value to result
	    }

	System.out.println(decimalResult); //print result

    }




}

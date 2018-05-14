/*
  Adam Gincel
  InfixToPostfix.java

  I pledge my honor I have abided by the Stevens Honor System.
 */

package week8;

/*
  @author Adam Gincel
  @version 1.0
  @since 20141016


  Takes a string of an equation as input, parsing it into a stack then rearranging it into postfix.
 */



public class InfixToPostfix{


	public static void main(String[] args)
	{
		String input = args[0];

		String regex = "[-0-9a-zA-Z+*/()]+";



		if(!input.matches(regex))
		{
			System.out.println("Only alphanumerics and +, -, *, /, (, and ) are allowed.");
			System.exit(0);
		}

		if(operatorValue(input.charAt(0)) > 0 || (operatorValue(input.charAt(input.length() - 1)) > 0 && operatorValue(input.charAt(input.length() - 1)) < 3)) //starts with or ends with operator, is allowed to end with )
		{
			System.out.println("You can't begin with or end with an operator!");
			System.exit(0);
		}

		Stack myStack = new Stack(input.length()); //stack will have capacity = to length of string; will never be too small.

		String finalString = "";
		int value = 0;
		char ourChar = '0';

		for(int i = 0; i<input.length(); i++)//go through the string. Most processing happens here. Might make this its own method.
		{
			ourChar = input.charAt(i);

			value = operatorValue(ourChar);

			if(value == 0) //current char is a non-operator, just add it onto the string.
			{
				finalString += ourChar;
			}else if(value == 1 || value == 2) //current char is a + or -, * or /. Peek with stack, if greater than value of top, add. If < or =, pop from stack and concatenate until it is greater than top.
			{
				if(value > operatorValue(myStack.peek()))
				{
					//add to stack
					myStack.push(ourChar);
					//System.out.println(myStack.debugPrintArray());
				}else if(value <= operatorValue(myStack.peek()))
				{
					//pop from stack while that expression is true
					while(value <= operatorValue(myStack.peek()))
					{
						finalString += myStack.pop();
					}
					//at this point our current character is > than the top of the stack, so we push it to the stack.

					myStack.push(ourChar);
				}
			}else if(value == -1) //current char is an open paren. Automatically add to the top of the stack.
			{
				myStack.push(ourChar);
				//System.out.println(myStack.debugPrintArray());
			}else if(value == 4) //current char is a close paren. Concatenate all parts of stack until reaching an open paren, which we simply get rid of.
			{
				myStack.debugPrintArray();
				while(operatorValue(myStack.peek()) != -1) //while the top of the stack isn't an open paren.
				{
					finalString += myStack.pop();
					//System.out.println(myStack.debugPrintArray());

					if(myStack.empty())
					{
						System.out.println("ERROR: Mismatched Parenthesis."); //if this thing is empty and still searching, there isn't a corresponding open paren.
						System.exit(0);
					}
				}
				//at the end, the top value is an open paren, which we just pop to nothing.
				myStack.pop();
			}

		}

		while(!myStack.empty())
		{

			if(myStack.peek() == '(')
			{
				System.out.println("ERROR: Mismatched Parenthesis."); //if any open parenthesis are in the stack, they weren't closed so parens are not matched.
				System.exit(0);
			}
			finalString += myStack.pop();
		}

		System.out.println(finalString);


	}

	private static int operatorValue(char x) 
	{
		//takes a character and returns its precedence in the form of an integer. 

		/*
			non-operators = 0
			+, - = 1
			*, / = 2
			( = -1 (everything goes above it)
			) = 4
		
		*/
		int derp = 0;

		if(x == '+' || x == '-')
			derp = 1;
		else if(x == '*' || x == '/')
			derp = 2;
		else if(x == '(')
			derp = -1;
		else if(x == ')')
			derp = 4;

		return derp;



	}
    



}

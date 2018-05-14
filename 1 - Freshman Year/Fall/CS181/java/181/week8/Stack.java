/*
  Adam Gincel
  Stack.java

  I pledge my honor that I have abided by the Stevens Honor System.


 */

package week8;


/*
  Uses arrays to emulate the functions of a stack. Only accepts chars.

  @author     Adam Gincel
  @version    1.0
  @since      20141016


  Takes either nothing or an integer upon initialization.

 */


public class Stack{


    private int top = -1;
    private int capacity;
    
    private char[] stack;
    private boolean isEmpty = true;

    public Stack(int c)
    {
        //I was told to make this take an int instead, and make that int the capacity of the array. The array will be filled by using push several times elsewhere.
	capacity = c;
	stack = new char[capacity];

	isEmpty = true;
	
    }

    public Stack()
    {
        capacity = 30;
        stack = new char[capacity];
	

        isEmpty = true;
	
    }

    public int size()
    {
    	return top+1;
    }

    public void push(char pushedValue)
	{
		if(top+1 <= capacity) //pushing won't push past capacity
		{
			stack[top+1] = pushedValue;
			top += 1;
	
			isEmpty = false;
		}
	       
    }
    
    public String debugPrintArray()
    {
    	String returnerS = "";
    	for(int i = 0; i<= top; i++)
    	{
    		returnerS += (stack[i] + "|");
    	}
    	
    	return returnerS;
    	
    	
    	
    }
    
    

    public char pop() //returns 0 if there's nothing to pop
    {
		char r = '0';
	
		if(top-1 >= -1) 
		    {
                //you can't pop past the 0th value, which would set top to -1. -1 is okay, nothing below it.
				r = stack[top];
	
				stack[top] = '0'; //unnecessary but makes me feel better
				top -= 1;
	      	}
		
	
		if(top == -1)
		    isEmpty = true;
	
		return r;	
    }

    public boolean empty()
    {
    	return isEmpty;
    }

    public char peek()
    {
        //returns '0' if stack is empty
        char derp = '0';

        if(top > -1)
            derp = stack[top];


    	return derp;

    }
    


    

    
}

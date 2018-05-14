/*
  Week7.java

  Contains main method for Stack, Queue, and StackWithQueue



  I pledge my honor that I have abided by the Stevens Honor System.



 */

package week7;




/*
Main Method to exemplify Stack.java, Queue.java, and StackFromQueue.java
@author     Adam Gincel
@version    1.0
@since      20141014

Accepts no parameters.

*/



public class Week7
{

    public static void main(String[] args)
    {
	Stack myStack1 = new Stack();
	Queue myQueue1 = new Queue();
	StackFromQueue mySWQ1 = new StackFromQueue();
	

	myStack1.push(3);
	myStack1.push(7);
	myStack1.push(21);

	System.out.println("Stack before popping: " + myStack1.debugPrintArray());
	System.out.println("Stack size before popping: " + myStack1.size());
	System.out.println("Stack empty? " + myStack1.empty());
	System.out.println("Peek at top Stack value: " + myStack1.peek());
	
	System.out.println("Popping stack:");
	System.out.println(myStack1.pop());
	System.out.println(myStack1.pop());
	System.out.println(myStack1.pop());
	
	System.out.println("");
	
	
	System.out.println("Stack size after popping: " + myStack1.size());
	System.out.println("Stack empty? " + myStack1.empty());
	
	System.out.println("------------------------");
	
	
	
	myQueue1.enqueue(3);
	myQueue1.enqueue(7);
	myQueue1.enqueue(21);
	
	System.out.println("Queue before dequeueing: " + myQueue1.debugPrintArray());
	System.out.println("Queue size before dequeueing: " + myQueue1.size());
	System.out.println("Queue empty? " + myQueue1.empty());
	
	System.out.println("Peek at top Queue value: " + myQueue1.peek());
	System.out.println(myQueue1.dequeue());
	System.out.println(myQueue1.dequeue());
	System.out.println(myQueue1.dequeue());
	
	System.out.println("");
	
	System.out.println("Queue size after dequeueing: " + myQueue1.size());
	System.out.println("Queue empty? " + myQueue1.empty());
	
	System.out.println("----------------------------");
	
	mySWQ1.push(3);
	mySWQ1.push(7);
	mySWQ1.push(21);
	
	System.out.println("StackWithQueue before popping: " + mySWQ1.debugPrintArray());
	System.out.println("StackWithQueue size before popping: " + mySWQ1.size());
	System.out.println("StackWithQueue empty? " + mySWQ1.empty());
	System.out.println("Peek at top SWQ value: " + mySWQ1.peek());
	
	System.out.println("Popping SWQ: ");

	System.out.println(mySWQ1.pop());
	System.out.println(mySWQ1.pop());
	System.out.println(mySWQ1.pop());
	
	System.out.println("StackWithQueue size after popping: " + mySWQ1.size());
	System.out.println("StackWithQueue empty? " + mySWQ1.empty());
	
	
	



    }





}

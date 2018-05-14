/*
	Adam Gincel
	StackFromQueue.java
	
	I pledge my honor that I have abided by the Stevens Honor System.

 */

package week7;


public class StackFromQueue{
	
/*
 * Implements a Stack using Two Queues. Requires Queue.java.
 * @author Adam Gincel
 * @version 1.0
 * @since 20141510
 */
	
	
	private int top = -1;
	private int capacity;
	private int defaultCapacity = 10;
	private boolean isEmpty = true;
	
	private Queue mainQueue;
	private Queue sideQueue;
	
	public StackFromQueue(int c)
	{
		mainQueue = new Queue(c); //both queues must have capacity of full Stack.
		sideQueue = new Queue(c);
		
		isEmpty = true;
	}
	
	public StackFromQueue()
	{
		mainQueue = new Queue(defaultCapacity);
		sideQueue = new Queue(defaultCapacity);
		
		isEmpty = true;
	}
	
	public int size()
	{
		return top+1;
	}
	
	public void push(int x)
	{
		mainQueue.enqueue(x);
		//System.out.println(mainQueue.debugPrintArray());
		top++;
		isEmpty = false;
	}
	
	public int pop()
	{
		int returner = -1; //returns -1 if the stack is empty.
		
		if(top-1 >= -1)
		{
			for(int i = 0; i<top; i++) //pushes every value in mainQueue into sideQueue, except for the last one. That last one is the value we want to pop.
			{
				sideQueue.enqueue(mainQueue.dequeue());
			
			}
			
			//System.out.println(sideQueue.debugPrintArray());
			
			returner = mainQueue.dequeue();
			top--;
			for(int i=0; i<=top; i++) //push all of sideQueue back into mainQueue, which is the real representation of our Stack.
			{
				mainQueue.enqueue(sideQueue.dequeue());
				//System.out.println(mainQueue.debugPrintArray());
			}
			
			if(top == -1)
				isEmpty = true;
		}
		
		
		
		return returner;
		
		
	}
	
	public boolean empty()
	{
		return isEmpty;
		
	}
	
	public int peek()
	{
		int returner = -1; //return -1 if this returns nothing
		
		if(!isEmpty) //if the array isn't empty
		{
			for(int i=0; i<top; i++) //pushes every value into sideQueue except the last one, which will be read then also queued into sideQueue.
			{
				sideQueue.enqueue(mainQueue.dequeue());
			}
			
			returner = mainQueue.dequeue();
			sideQueue.enqueue(returner); //put the peeked value back into the queue
			
			for(int i=0; i<=top; i++) //put all of sideQueue back into mainQueue
			{
				mainQueue.enqueue(sideQueue.dequeue());
			}
			
			
		}
		
		return returner;
	}
	
	public String debugPrintArray(){
		return mainQueue.debugPrintArray();
		
	}
	

	
	
	
	
	
	
	
}
	
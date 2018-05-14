/*
  Adam Gincel
  Queue.java

    I pledge my honor I've abided by the Stevens Honor System.
 */

package assign5;




public class Queue extends QueueException implements QueueInterface{
	
	/*
	 * Uses arrays to emulate a Queue.
	 * @author Adam Gincel
	 * @version 1.0
	 * @since 20141510
	 */
    
    private int top = -1;
    private int capacity;

    private int[] queue;
    private boolean isEmpty = true;

    private int defaultCapacity = 10;
    

    public Queue(int c)
    {
	   capacity = c;
	   queue = new int[capacity];

	   isEmpty = true;
    }

    public Queue()
    {
	   capacity = defaultCapacity;
	   queue = new int[capacity];

	   isEmpty = true;
    }

    public int size()
    {
	   return top+1;
    }

    public void enqueue(int x) throws QueueException
    {
        	if(top+1 < capacity)//enqueueing won't exceed capacity
            {
           
        		//push everything in the array forward by one, leaving an empty space at the beginning. Then set that to our value.
        		for(int i = top; i>=0; i--)
        		    {
        			if(i>=0)
        			    queue[i+1]=queue[i];

        		    }

        		queue[0] = x;
        		top++;
        		isEmpty = false;
            }else
                throw new QueueException("Surpassed Queue capacity!");
        
    	
            

    }

    public int dequeue() throws QueueException
    {
    	int returner = -1;
        
        	if(top-1>=-1) //as long as there's something to dequeue
            {
            
        		returner = queue[top];
        		
        		
        		top--;
            }else
                throw new QueueException("Queue out of bounds.");


    	
            

    	if(top == -1)
    	    isEmpty = true;

	
	   return returner;

    }

    public boolean empty()
    {
	   return isEmpty;

    }

    public int peek() throws QueueException
    {
	   
        if(!empty())
            return queue[top];
        else
            throw new QueueException("Cannot peek an empty queue!");
        
      

       
    }
    
    public String debugPrintArray()
    {
    	String returnerS = "";
    	for(int i = 0; i<= top; i++)
    	{
    		returnerS += (queue[i] + "|");
    	}
    	
    	return returnerS;
    	
    	
    	
    }



}

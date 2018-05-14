/*
  Adam Gincel
  Queue.java


 */

package assign3;




public class RingBuffer{
	
	/*
	 * Uses previously written Queue to emulate a RingBuffer, which is a cyclical Queue.
	 * @author Adam Gincel
	 * @version 1.0
	 * @since 201429 10
	 */
    
    private int first, last = 0;
    private int capacity;
    private int size = 0;

    private double[] queue;
    private boolean isEmpty = true;

    private int defaultCapacity = 10;
    

    public RingBuffer(int c)
    {
    	capacity = c;
    	queue = new double[capacity];

    	isEmpty = true;
    }

    public RingBuffer()
    {
    	capacity = defaultCapacity;
    	queue = new double[capacity];

    	isEmpty = true;
    }

    public int getSize()
    {
	   return size;
    }

    public void enqueue(double x)
    {//adds something to the "end" of the queue.
    	if(size < capacity)//enqueueing won't exceed capacity
        {

            queue[last] = x;
    	    

    		

            if(last + 1 == capacity)
                last = 0;
            else
                last++;


            isEmpty = false;

            size++;
        }else
            System.out.println("The array is at capacity.");

   }

    public double dequeue() 
    {   //removes first thing entered.
    	double returner = -1.0;
    	if(size > 0) //as long as there's something to dequeue
    	    {
        		returner = queue[first];
        		
        		if(first + 1 == capacity)
                    first = 0;
                else
                    first++;

                size--;
    	    }
            else
                System.out.println("There's nothing to dequeue.");

    	if(size == 0)
    	    isEmpty = true;

    	
    	return returner;
    }

    public boolean isEmpty()
    {
	   return isEmpty;

    }

    public boolean isFull()
    {
        return (size == capacity);
    }

    public double peek()
    {
	   return queue[first];

    }
    
    public String debugPrintArray()
    {   //returns the array in string form
    	String returnerS = "";
    	for(int i = 0; i< capacity; i++)
    	{
    		returnerS += (queue[i] + "|");
    	}
    	
    	return returnerS;
    }

    public double[] getArray()
    {   //returns the RingBuffer as a normal double array
        double[] thing = new double[getSize()];

        for(int i = 0; i < getSize(); i++)
        {
            thing[i] = queue[(first + i)%getSize()];
        }

        return thing;


    }



}

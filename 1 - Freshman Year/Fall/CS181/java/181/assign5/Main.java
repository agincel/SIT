/*
	Adam Gincel
	Main.java

	A class to test Queue.java implementing an interface and throwing exceptions.

	I pledge my honor I've abided by the Stevens Honor System.

*/

package assign5;

public class Main
{

	public static void main(String[] args)
	{
		Queue q = new Queue(5);

		System.out.println("Dequeue until exception: ");
		
		try
		{
			q.dequeue();

		}catch(QueueException qe)
		{
			qe.printStackTrace();
		}

		System.out.println("Peek for exception: ");

		try{
			q.peek();
		}catch(QueueException qe)
		{
			qe.printStackTrace();
		}
		

		System.out.println("Enqueue until exception:");

		try{
			q.enqueue(1);
			q.enqueue(2);
			q.enqueue(2);
			q.enqueue(2);
			q.enqueue(2);
			q.enqueue(2);	
		}catch(QueueException qe)
		{
			qe.printStackTrace();
		}

		



	}



}
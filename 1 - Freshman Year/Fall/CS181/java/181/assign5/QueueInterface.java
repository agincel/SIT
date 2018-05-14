/*
	Adam Gincel
	QueueInterface.java

	An Interface for Queue.java.

	I pledge my honor I've abided by the Stevens Honor System.

*/

package assign5;

public interface QueueInterface
{

	public void enqueue(int number) throws QueueException;

	public int dequeue() throws QueueException;

	public int size();

	public boolean empty();

	public int peek() throws QueueException;




}
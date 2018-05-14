/*
	Adam Gincel
	QueueException.java

	A class that defines the different exceptions a Queue can run into.

	I pledge my honor I've abided by the Stevens Honor System.

*/

package assign5;

public class QueueException extends Exception
{
	public QueueException()
	{
		super();


	}

	public QueueException(String message)
	{
		super(message);

	}

	public String getMessage()
    {
        return super.getMessage();
    }



}
/*
	Adam Gincel
	GuitarString.java


	I pledge my honor I have abided by the Stevens Honor System.
*/


package assign3;

import assign3.RingBuffer;
/*
	@author Adam Gincel
	@version 1.0
	@since 20142310


	Simulates a guitar string. Can be instantiated with a double array of frequencies for debugging, or a single double representing one frequency.
*/

public class GuitarString{

	private static int samplingRate = 44100;

	RingBuffer ourBuffer;
	private int bufferCapacity;
	private int timesTicWasCalled;

	public GuitarString(double frequency)
	{
		bufferCapacity = (int)Math.round((double)samplingRate/frequency);

		ourBuffer = new RingBuffer(bufferCapacity);

		for(int i = 0; i<bufferCapacity; i++) //fill the RingBuffer with zeroes.
			ourBuffer.enqueue(0.0);






	}

	public GuitarString(double[] init)
	{
		bufferCapacity = init.length;

		ourBuffer = new RingBuffer(bufferCapacity);

		for(int i = 0; i<bufferCapacity; i++)
		{
			ourBuffer.enqueue(init[i]);
		}


	}

	public void pluck()
	{
		int x = ourBuffer.getSize();

		for(int i = 0; i<x; i++)
		{
			ourBuffer.dequeue(); //empty entire RingBuffer
		}

		for(int i = 0; i<bufferCapacity; i++)
		{
			double rand = Math.random() - .5;

			if(rand >= .495) //.5 is inclusive.
				rand = .5;

			ourBuffer.enqueue(rand);

		}

	}

	public double sample()
	{
		return ourBuffer.peek();

	}

	public void tic()
	{
		double value1 = ourBuffer.dequeue();
		double value2 = ourBuffer.peek();

		double result = .996*(.5*(value1 + value2));

		ourBuffer.enqueue(result);

		timesTicWasCalled++;
	}

	public int time()
	{
		return timesTicWasCalled;

	}






}
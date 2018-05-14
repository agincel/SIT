/*
	Adam Gincel
	GuitarHero.java


	I pledge my honor I have abided by the Stevens Honor System.
*/


package assign3;


import cos126.StdDraw;
import cos126.StdAudio;
import assign3.RingBuffer;
import java.util.*;
import java.io.*;

/*
	@author Adam Gincel
	@version 1.0
	@since 20142310

*/

public class GuitarHero{

	public static String keyboard = "1234567890qwertyuiopasdfghjklzxcvbnm,";
	public static Scanner inFile1;
	public static final int sampleDelay = 3;
	public static final int sampleAmount = 500;


	public static void main(String[] args)
	{
		int l = keyboard.length();

		GuitarString[] notes = fillGuitarStringArray(l);

		boolean playingFromFile = false;
		String[] sequencedNotes = {};
		if(args.length > 1) //(prevent crash if no command line given, needs both -play_from_file and a filename to work)
		{
			if(args[0].equals("-play_from_file")) //using option play from file
			{
				playingFromFile = true;

				try{
					initScanner(args[1]);
				}catch(IOException ioe){
				  ioe.printStackTrace();
				}

				ArrayList<String> theNotes = new ArrayList<String>();
				while (inFile1.hasNext())
				{
  				  theNotes.add(inFile1.nextLine());
				}

				sequencedNotes = new String[theNotes.size()];

				for(int i = 0; i < sequencedNotes.length; i++) {
				    sequencedNotes[i] = theNotes.get(i);
				}

			}
				 
		}



		if(!playingFromFile)
			freePlay(notes);
		else
			playFromFile(notes, sequencedNotes);
		
		



		



	}

	public static void initScanner(String fileName) throws java.io.IOException
	{
		inFile1 = new Scanner(new File("songs/" + fileName));

	}

	public static void freePlay(GuitarString[] notes)
	{	
		RingBuffer samples = new RingBuffer(sampleAmount);



		System.out.println("Press ESC to quit!");
		int keyPressed = -1;
		double[] sampleArray;

		StdDraw.show(0);
		while(true) //checking for input and playing sounds
		{
			if (StdDraw.hasNextKeyTyped()) 
			{
                char key = StdDraw.nextKeyTyped();

                if(key == 0x001B) //pressed escape
                {
                	System.out.println("Thanks for playing!");
                	System.exit(0);

                }

                keyPressed = keyboard.indexOf(key);
               // System.out.println(keyPressed);
                if(keyPressed != -1)
                	notes[keyPressed].pluck();

            }

            //create superposition of samples by adding up samples of entire array
            double sample = 0;
            for(int i = 0; i<keyboard.length(); i++)
            {
            	sample += notes[i].sample();
            }


            if(notes[0].time()%sampleDelay == 0) //once a specified number of tics have passed, enqueue the current sample
            {
            	if(samples.isFull())
            	{
            		samples.dequeue();
            	}

            	samples.enqueue(sample);
            }

            if(notes[0].time()%(sampleDelay*sampleAmount) == 0) //draw to screen once sampleAmount new samples have been added
            {
            	StdDraw.clear();

            	sampleArray = samples.getArray();

            	for(int i = 0; i < samples.getSize() - 1; i++)
            	{
            		StdDraw.line((double)i/sampleAmount, ((sampleArray[i]+.5)/2)+.25, (double)(i+1)/sampleAmount, ((sampleArray[i+1]+.5)/2)+.25);
            	}

            	StdDraw.show(0);

            }


            //play sample on sound card
            StdAudio.play(sample);
            //System.out.print(sample);

            for(int i = 0; i<keyboard.length(); i++) //tic each note
            {
            	notes[i].tic();
            }
		}
	}

	public static void playFromFile(GuitarString[] notes, String[]sequencedNotes)
	{
		RingBuffer samples = new RingBuffer(sampleAmount);
		StdDraw.show(0);


		int x = sequencedNotes.length;
		int iterator = 0;
		int derp = -1;
		char key;
		int keyPressed = 0;
		int i = 0;
		double[] sampleArray;

		long startTime = System.nanoTime();
		while(true)
		{


			long sumTime = System.nanoTime() - startTime;

			if (StdDraw.hasNextKeyTyped()) 
			{
                key = StdDraw.nextKeyTyped();

                if(key == 0x001B) //pressed escape
                {
                	System.out.println("Thanks for playing!");
                	System.exit(0);

                }
            }
            
				

            if((sumTime)>331000000) //if 331 milliseconds have passed, pluck a new string.
            {
            	if(derp < x-1) //hasn't exceeded file
            	{	
            		//System.out.println(System.nanoTime() - startTime);
            		startTime = System.nanoTime();

	            	derp++;

	            	for(int why = 0; why < sequencedNotes[derp].length(); why++)
	            	{
						key = sequencedNotes[derp].charAt(why);
						keyPressed = keyboard.indexOf(key);
						
						if(keyPressed > -1)
						{
							System.out.print(keyPressed + " ");
							notes[keyPressed].pluck();
						}
					}
					System.out.println("");


				}else //end of file reached.
				{
					System.out.println("Yay!");
					System.exit(0);
				}



			}

		
			


			double sample = 0;
	        for(i = 0; i<keyboard.length(); i++)
	        {
	         	sample += notes[i].sample();

	        }	

	        if(notes[0].time()%sampleDelay == 0) //once a specified number of tics have passed, enqueue the current sample
            {
            	if(samples.isFull())
            	{
            		samples.dequeue();
            	}

            	samples.enqueue(sample);
            }

            if(notes[0].time()%(sampleDelay*sampleAmount) == 0) //draw to screen once 100 new samples have been added
            {
            	StdDraw.clear();

            	sampleArray = samples.getArray();

            	for(i = 0; i < samples.getSize() - 1; i++)
            	{
            		StdDraw.line((double)i/sampleAmount, ((sampleArray[i]+.5)/2)+.25, (double)(i+1)/sampleAmount, ((sampleArray[i+1]+.5)/2)+.25);
            	}

            	StdDraw.show(0);

            }

	        StdAudio.play(sample);
	        //System.out.println(sample);


			for(i = 0; i<keyboard.length(); i++) //tic each note
	        {
	           	notes[i].tic();
	        }

	    

			
			
			iterator++;

		}

		
	}

	public static GuitarString[] fillGuitarStringArray(int l)
	{
		double thisNote = 0;
		GuitarString[] returner = new GuitarString[l];
		for(int i = 0; i<l;i++) //make an array of GuitarStrings
		{
			thisNote = 440.0 * Math.pow(2.0, (i-24.0)/12.0);

			returner[i] = new GuitarString(thisNote);
		}


		return returner;


	}




}

/*
  Adam Gincel
  Cipher Text - takes either 1 or 2 args: 




import java.util.Random;
byte randomByte = new byte[message.length()];
new Random().nextBytes(randomByte);


 */
import java.util.Random;
import java.lang.Object;


public class CipherText{

    public static void main(String[] args)
    {
	Random random = new Random();
	String message = args[0];


	
	byte[] randomByte = new byte[message.length()];
	random.nextBytes(randomByte);

	int[] x = new int[message.length()];

	for(int i = 0; i < message.length(); i++)
	    {
		//	System.out.print((char)randomByte[i]);

	    }



	for(int i = 0; i < message.length(); i++)
	    {
	        x[i] = message.charAt(i)^randomByte[i];
		//System.out.print((char)x[i]);
	    }



	


	for(int i = 0; i < message.length(); i++)
	    {
		char uniChar = (char)x[i];

		System.out.println("\\u" + Integer.toHexString(uniChar | 0x10000).substring(1));

	    }


	System.out.println("\n");

       	int[] y = new int[message.length()];

	
       	for(int i = 0; i < message.length(); i++)
	    {
	        y[i] = x[i]^randomByte[i];
		System.out.print((char)y[i]);
	    }
		
	    
	

	





    }
    

}

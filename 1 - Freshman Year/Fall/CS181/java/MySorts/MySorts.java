/**
 *  MySorts.java
 * 
 *  @author Adam Gincel
 *  Professor Gabarró
 *  
 *  CS182
 * 
 * 	Implementations of Insert, Merge, and Shell sorts in Java.
 * 
 *  I pledge my honor that I have abided by the Stevens Honor System.
 */


public class MySorts 
{
	/**
	 * @author Adam Gincel
	 * Tests the various sorting algorithms.
	 * 
	 * @param args
	 */
	
	private final static int THRESHOLD = 2;
	
	public static void main(String[] args)
	{
		int i = 0;
		String[] arr = {"zol", "scrub", "yay", "asdf"};
		String[] arr2 = {"Z", "Y", "X", "C", "B", "A"};
		int[] arr3 = {9, 2, 73, 525, 19991, 7, 42, 3486538};
		
		System.out.println("Insertion sort:");
		System.out.print("Unsorted: " + printArray(arr, i));
		insert(arr, 4);
		System.out.print("Sorted: " + printArray(arr, i));
		
		System.out.println("");
		
		System.out.println("Merge sort:");
		System.out.print("Unsorted: " + printArray(arr2, i));
		merge(arr2, arr2.length);
		System.out.print("Sorted: " + printArray(arr2, i));
		
		System.out.println("");
		
		System.out.println("Shell sort:");
		System.out.print("Unsorted: " + printArray(arr3, i));
		shell(arr3, arr3.length);
		System.out.print("Sorted: " + printArray(arr3, i));
		
		System.out.println("");
		
		System.out.println("Error checking:");
		System.out.println("Calling each sort with (null, arr.length)");
		insert(null, arr.length);
		merge(null, arr.length);
		shell(null, arr.length);
		System.out.println("\nCalling each sort with (array, 1)");
		insert(arr, 1);
		merge(arr, 1);
		shell(arr3, 1);
		
		String[] arr4 = {"zol", "scrub", "yay", "asdf"};
		String[] arr5 = {"Z", "Y", "X", "C", "B", "A"};
		int[] arr6 = {9, 2, 73, 525, 19991, 7, 42, 3486538};
		System.out.println("\nCalling each sort with (array, 9999999)");
		
		System.out.println("Insertion sort:");
		System.out.print("Unsorted: " + printArray(arr4, i));
		insert(arr4, 9999999);
		System.out.print("Sorted: " + printArray(arr4, i));
		
		System.out.println("");
		
		System.out.println("Merge sort:");
		System.out.print("Unsorted: " + printArray(arr5, i));
		merge(arr5, 9999999);
		System.out.print("Sorted: " + printArray(arr5, i));
		
		System.out.println("");
		
		System.out.println("Shell sort:");
		System.out.print("Unsorted: " + printArray(arr6, i));
		shell(arr6, 9999999);
		System.out.print("Sorted: " + printArray(arr6, i));
	
		
	}
	
	
	/**
	 * @author Adam Gincel
	 * printArray returns appended string of each element of an array, separated by commas
	 * @param arr String array to be printed.
	 * @param i Iterator.
	 * @return a String with all of the elements of an array appended and separated with commas.
	 */
	private static String printArray(String[] arr, int i)
	{
		String returner = new String("");
		
		for(i = 0; i < arr.length - 1; i++)
			returner += (arr[i] + ", ");
		
		returner += (arr[i] + "\n");
		
		return returner;
	}
	
	private static String printArray(int[] arr, int i)
	{
		String returner = new String("");
		
		for(i = 0; i < arr.length - 1; i++)
			returner += (arr[i] + ", ");
		
		returner += (arr[i] + "\n");
		
		return returner;
	}
	
	
	/**
	 * @author Adam Gincel
	 * Sorts a string array using Insertion Sort. Does not return anything, but the first n items of the array are sorted at the end of the method.
	 * 
	 * @param arr The String array that is to be sorted.
	 * @param n The number of items in the array that are to be sorted. If this is greater than the array's length, it is set to be the length.
	 * 
	 */
	
	public static void insert(String[] arr, int n)
	{
		int i, j;
		
		if(arr != null && n > 1)
		{
			if(n > arr.length)
				n = arr.length;
			
			for(i = 1; i < n; i++)
				for(j = i; j > 0 && arr[j].compareTo(arr[j-1]) < 0; j--)
					swap(arr, j, j - 1);	
			
		}else
			System.out.println("Invalid parameters.");
		
	}
	
	/**
	 * @author Adam Gincel
	 * Sorts a string array using Merge Sort. Does not return anything, but sorts the first n items of the array.
	 * 
	 * @param arr The String array to be sorted.
	 * @param n The number of items in the array that are to be sorted. If this is greater than the array's length, it is set to be the length.
	 */
	
	public static void merge(String[] arr, int n)
	{
		if(arr != null && n > 1)
		{
			if(n > arr.length)
				n = arr.length;
			
			String[] tmp = new String[n];
			merge(arr, 0, n-1, tmp);
		}else
			System.out.println("Invalid parameters.");

	}
	
	
	
	/**
	 * @author Adam Gincel
	 * The recursive portion of Merge Sort. Calls itself upon segmenting the array then merges the results into a sorted array.
	 * 
	 * @param arr Array being sorted.
	 * @param l Leftmost index
	 * @param r	Rightmost index
	 * @param tmp Temporary array used in the final merge step.
	 */
	private static void merge(String[] arr, int l, int r, String[] tmp)
	{
		int m = 0;
		int i = 0;
		int j = 0;
		int k = 0;
		
		if(l < r)
		{
			m = l + (r-l)/2; //gets midpoint without fear of overflow from really big numbers.
			merge(arr, l, m, tmp);
			merge(arr, m+1, r, tmp);		
		
			for(i = l; i <= m; i++)
				tmp[i] = arr[i];
			for(j = r; i <= r; j--, i++)
				tmp[i] = arr[j];
			
			for(i = l, j = r, k = l; k <= r; k++)
			{
				if(tmp[i].compareTo(tmp[j]) < 0)
					arr[k] = tmp[i++];
				else
					arr[k] = tmp[j--];			
			}
		}
	}
	
	
	/**
	 * @author Adam Gincel
	 * Implementation of shell sort. Sorts the first n items of an int array.
	 * @param arr int array to be sorted
	 * @param n number of elements in int array to be sorted
	 */
	public static void shell(int[] arr, int n)
	{
		int incr, start;
		
		if(arr != null && n > 1)
		{
			if(n > arr.length)
				n = arr.length;
			
			for(incr = n/2; incr > THRESHOLD; incr = incr/2 + 1)
				for(start = 0; start < incr; start++)
					insert(arr, n, start, incr);
			
			
			insert(arr, n, 0, 1);
		}else
			System.out.println("Invalid parameters.");
		
	}
	
	
	/**
	 * @author Adam Gincel
	 * Private implementation of insertion sort that takes an increment and starting value; used as part of shell sort.
	 * Sorts subarrays within the array separated by a specific increment.
	 * 
	 * @param arr Array being sorted.
	 * @param size Size of array, could be from 1 < size < arr.length
	 * @param start First point of the array, changes depending on the subarray.
	 * @param increment - Number of spaces between each subarray element.
	 */
	private static void insert(int[] arr, int size, int start, int increment)
	{
		int i, j;
		
		for(i = start+increment; i < size; i += increment)
			for(j = i; j > start; j -= increment)
				if(arr[j - increment] > arr[j])
					swap(arr, j - increment, j);
	}
		
		
		
		
	
	
	
	
	/**
	 * @author Adam Gincel
	 * Swaps two array indexes. 
	 * 
	 * @param arr Array in which swapping is happening.
	 * @param x First index to swap.
	 * @param y Second index to swap.
	 */
	
	private static void swap(String[] arr, int x, int y)
	{
		String temp = arr[x];	
		arr[x] = arr[y];
		arr[y] = temp;
	}
	
	private static void swap(int[] arr, int x, int y)
	{
		int temp = arr[x];	
		arr[x] = arr[y];
		arr[y] = temp;
	}
	
	
	
	
	
	
	
}

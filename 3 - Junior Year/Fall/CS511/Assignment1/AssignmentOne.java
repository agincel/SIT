import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

/**
 * Created by Adam on 9/7/2016.
 * I pledge my honor that I have abided by the Stevens Honor System.
 */

class PrimeFinder implements Runnable {
    private Integer start;
    private Integer end;
    private List<Integer> primes;

    public PrimeFinder(Integer s, Integer e)
    {
        this.start = s;
        this.end = e;
        primes = new ArrayList<>();
    }

    public List<Integer> getPrimesList ()
    {
        return this.primes;
    }

    public Boolean isPrime(int n)
    {
        Boolean isPrime = true;

        for (int i = 2; i < (n / 2) + 1 && isPrime; i++)
        {
            if (n % i == 0)
                isPrime = false;
        }

	if (n <= 1)
		isPrime = false;

        return isPrime;
    }

    public void run()
    {
        for (int i = start; i < end; i++)
        {
            if (this.isPrime(i)) {
                primes.add(i);
            }
        }
        //System.out.println("Thread from " + start.toString() + " to " + end.toString() + " completed.");
    }
}

public class AssignmentOne {
    public static List<Integer> lprimes(List<Integer[]> intervals) throws InterruptedException {
        List<Integer> allPrimes = new ArrayList<>();
        List<PrimeFinder> finders = new ArrayList<>();
        List<Thread> threads = new ArrayList<>();
        for (int i = 0; i < intervals.size(); i++) { //create prime finders and run them as threads
            finders.add(new PrimeFinder(intervals.get(i)[0], intervals.get(i)[1]));
            threads.add(new Thread(finders.get(i)));
            threads.get(i).start();
        }

        for (int i = 0; i < intervals.size(); i++) { //wait for all threads to terminate
            threads.get(i).join();
        }

        for (int i = 0; i < finders.size(); i++) { //create list from each thread
            for (int j = 0; j < finders.get(i).getPrimesList().size(); j++) {
                allPrimes.add(finders.get(i).getPrimesList().get(j));
            }
        }
        return allPrimes;
    }

    public static void main(String[] args) throws InterruptedException {
        for (int i = 0; i < args.length; i++) {
            if (args.length < 2 || !args[i].matches("[0-9]+") || ((i > 0) && ((Integer.valueOf(args[i]) <= Integer.valueOf(args[i - 1]))))) {
                System.out.println(args[i] + ": Please run this program with at least two numbers in increasing order.");
                System.exit(1);
            }
        }
        if (args.length == 0) {
            System.out.println("Please run this program with at least two numbers in increasing order.");
            System.exit(1);
        }

        //System.out.println(Arrays.toString(args));

        List<Integer[]> duples;
        duples = new ArrayList<>();
        for (int i = 0; i < args.length - 1; i++)
        {
            Integer[] duple = {Integer.valueOf(args[i]), Integer.valueOf(args[i+1])};
            duples.add(duple);
        }

        List<Integer> result = lprimes(duples);
        System.out.println(result);
    }
}

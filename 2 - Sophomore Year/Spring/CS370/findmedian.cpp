/*
  Andrew Neurohr, Adam Gincel, Clara Ramos
  We pledge our honor that we have abided by the Stevens honor system.
*/
#include <queue>
#include <vector>
#include <iostream>

int main()
{
    int N;
    double med = 0.0;
    std::priority_queue<int, std::vector<int>, std::greater<int> > min_heap;
    std::priority_queue<int, std::vector<int> > max_heap;

  	/*
     * get the number of numbers the user will give the program
     * check to make sure the provided number is a number and in range
     */
    std::cin >> N;
  	if (std::cin.fail())
	{
    	std::cin.clear();
    	std::cerr << "Error: Only input numbers." << '\n';
      	return -1;
	}

  	if(N < 1 || N > 100000) {
    	std::cerr << "Error: User should give [1, 100000] numbers." << '\n';
      	return -1;
  	}

    //while there are still numbers to be read from the user 1 number at a time
    while (N--)
    {
        int num;
        std::cin >> num;

      	//check to make sure num is within range
      	if (std::cin.fail())
		{
    		std::cin.clear();
    		std::cerr << "Error: Only input numbers." << '\n';
      		return -1;
		}

      	if(num < 0 || num > 100000) {
        	std::cerr << "Error: Numbers should be within the range [0, 100000]." << '\n';
          	return -1;
      	}

        int diff = max_heap.size() - min_heap.size();

        // More elements in max heap
        if (diff > 0)
        {
            if (num < med)
            {
                // swap from max heap to min heap
                int tmp = max_heap.top();
                max_heap.pop();

                min_heap.push(tmp);
                max_heap.push(num);
            }
            else
            {
                min_heap.push(num);
            }

            // median is average of top elements
            med = (static_cast<double>(min_heap.top()) + max_heap.top()) / 2;
        }
        // More elements in min heap
        else if (diff < 0)
        {
            if (num < med)
            {
                max_heap.push(num);
            }
            else
            {
                // swap from min heap to max heap
                int tmp = min_heap.top();
                min_heap.pop();

                max_heap.push(tmp);
                min_heap.push(num);
            }

            // median is average of top elements
            med = (static_cast<double>(min_heap.top()) + max_heap.top()) / 2;
        }
        // Same number of elements
        else
        {
            if (num < med)
            {
                max_heap.push(num);
                // median is top of max heap if max heap has more elements
                med = max_heap.top();
            }
            else
            {
                min_heap.push(num);
                // median is top of min heap if min heap has more elements
                med = min_heap.top();
            }
        }
        std::cout << med << "\n";
    }
}

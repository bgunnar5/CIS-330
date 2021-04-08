#include "numlist.h"

// Partitioning functions
// Serial partition
unsigned int NumList::partition(vector<int>& keys, unsigned int low, 
                                unsigned int high)
{
    // Use the last element as the pivot
    int pivot = keys[high];

    // Index of smaller element
    int low_index = (low - 1);

    for (unsigned int i = low; i < high; i++) {
    	// If the current element is less than or equal to pivot
	if (keys[i] <= pivot) {
	// Increment index of smaller element
	    low_index++;
	// Swap indices
	    int tmp = keys[i];
	    keys[i] = keys[low_index];
	    keys[low_index] = tmp;
	}
    }

    // Swap index of low_index + 1 and high
    int tmp2 = keys[low_index + 1];
    keys[low_index + 1] = keys[high];
    keys[high] = tmp2;

    // Return the low index + 1
    return low_index + 1;
}

// Parallel partition
unsigned int NumList:: partition_par(vector<int>& keys, unsigned int low,
                                     unsigned int high)
{
    // There should be two #pragmas to parallelize the loop
    // First loop is calculating the lt and gt arrays
    // Second is when the integers are copied to the correct position (i.e.,
    // left or right side of the pivot
    
    // Use the last element as the pivot
    int pivot = keys[high];

    // Get the length
    int len = high - low + 1;

    // If there's only one element just return low
    if (len == 1)
	return low;

    // Initialize less than, greater than, and keys copy vectors
    vector<int> lt(len, 0);
    vector<int> gt(len, 0);
    vector<int> keys_copy(len, 0);
    
    #pragma omp parallel for
    for (int i = 0; i < (len-1); i++) {
	// Copy data
        keys_copy[i] = keys[low + i];
	
	// Equal to case
	if (keys_copy[i] == pivot) {
	    lt[i] = 1;
        }
	// Less than case
        else if (keys_copy[i] < pivot) {
	    lt[i] = 1;
        }
	// Greater than case
        else {
	    gt[i] = 1;
        } 
    }
    keys_copy[len - 1] = keys[low + len - 1];

    // Prefix sum	
    for (int i = 1; i < len; i++) {
	lt[i] += lt[i-1];
	gt[i] += gt[i-1]; 
    }

    // Figure out where the pivot should go
    int k = low + lt[len - 1];

    // Insert pivot into new location
    keys[k] = pivot;

    // Rearrange keys vector
    #pragma omp parallel for
    for (int i = 0; i < (len - 1); i++) {
    	if (keys_copy[i] <= pivot) {
	    keys[low + lt[i] - 1] = keys_copy[i];
	}
	else {
	    keys[k+gt[i]] = keys_copy[i];
	}
    }
    
    return k;
}

// Actual qsort that recursively calls itself with particular partitioning
// strategy to sort the list
void NumList::qsort(vector<int>& keys, int low, int high, ImplType opt)
{
    if(low < high) {
        unsigned int pi;
        if(opt == serial) {
            pi = partition(keys, low, high);
        } else {
            pi = partition_par(keys, low, high);
        }
        qsort(keys, low, pi - 1, opt);
        qsort(keys, pi + 1, high, opt);
    }
}

// wrapper for calling qsort
void NumList::my_qsort(ImplType opt)
{
    /* Initiate the quick sort from this function */
    qsort(list, 0, list.size() - 1, opt);
}
// Default constructor
// This should "create" an empty list
NumList::NumList() {
    /* do nothing */
    /* you will have an empty vector */
}
// Contructor
// Pass in a vector and the partitioning strategy to use
NumList::NumList(vector<int> in, ImplType opt) {
    list = in;
    my_qsort(opt);
}
// Destructor
NumList::~NumList() {
    /* do nothing */
    /* vector will be cleaned up automatically by its destructor */
}
// Get the element at index
int NumList::get_elem(unsigned int index)
{
    return list[index];
}
// Print the list
void NumList::print(ostream& os)
{
    for(unsigned int i = 0; i < list.size(); i++) {
        os << i << ":\t" << list[i] << endl;
    }
}

/**
 * @file quackfun.cpp
 * This is where you will implement the required functions for the
 *  stacks and queues portion of the lab.
 */

namespace QuackFun {

/**
 * Sums items in a stack.
 * @param s A stack holding values to sum.
 * @return The sum of all the elements in the stack, leaving the original
 *  stack in the same state (unchanged).
 *
 * @note You may modify the stack as long as you restore it to its original
 *  values.
 * @note You may use only two local variables of type T in your function.
 *  Note that this function is templatized on the stack's type, so stacks of
 *  objects overloading the + operator can be summed.
 * @note We are using the Standard Template Library (STL) stack in this
 *  problem. Its pop function works a bit differently from the stack we
 *  built. Try searching for "stl stack" to learn how to use it.
 * @hint Think recursively!
 */
template <typename T>
T sum(stack<T>& s)
{
    // Your code here
	T result;
	T temp;
	
	if (s.empty()) return T();
	else{
		temp = s.top();
		s.pop();
		result = sum(s) + temp;
		s.push(temp);
		return result;
	}

//return T(); 
// stub return value (0 for primitive types). Change this!
// Note: T() is the default value for objects, and 0 for primitive types
}

/**
 * Reverses even sized blocks of items in the queue. Blocks start at size
 * one and increase for each subsequent block.
 * @param q A queue of items to be scrambled
 *
 * @note Any "leftover" numbers should be handled as if their block was
 *  complete.
 * @note We are using the Standard Template Library (STL) queue in this
 *  problem. Its pop function works a bit differently from the stack we
 *  built. Try searching for "stl stack" to learn how to use it.
 * @hint You'll want to make a local stack variable.
 */
template <typename T>
void scramble(queue<T>& q)
{
	stack<T> s;
    // optional: queue<T> q2;
	
    // Your code here
	queue<T> q2;
	int counter = 0;

	while (!q.empty()){
		counter++;
		//odd groups
		if(counter%2 == 1){
			for(int i = 0; i<counter; i++){
				//1st reverse
				if(!q.empty()){
					q2.push(q.front());
					q.pop();
				}
			}
		}
		//even groups
		else{
			//1st reverse
			for(int i = 0; i<counter; i++){
				if(!q.empty()){
					s.push(q.front());
					q.pop();
				}
			}
			//2nd reverse
			while(!s.empty()){
				q2.push(s.top());
				s.pop();
			}
		}
	}
	//reverse the whole q2
	//odd groups have total 2 times of reverse
	//even groups have total 3 times of reverse
	while (!q2.empty()){
		q.push(q2.front());
		q2.pop();
	}
}

/**
 * @return true if the parameter stack and queue contain only elements of
 *  exactly the same values in exactly the same order; false, otherwise.
 *
 * @note You may assume the stack and queue contain the same number of items!
 * @note There are restrictions for writing this function.
 * - Your function may not use any loops
 * - In your function you may only declare ONE local boolean variable to use in
 *   your return statement, and you may only declare TWO local variables of
 *   parametrized type T to use however you wish.
 * - No other local variables can be used.
 * - After execution of verifySame, the stack and queue must be unchanged. Be
 *   sure to comment your code VERY well.
 */
template <typename T>
bool verifySame(stack<T>& s, queue<T>& q)
{
	T s1;
	T q1;

	if (s.size() == 0) return true;
	s1 = s.top();
	s.pop();
	bool retval = verifySame(s, q);

	q1 = q.front();
	q.pop();
	q.push(q1);
	s.push(s1);
	
	return (q1 = s1) && retval;
}
};

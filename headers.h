#include <string>
#include <stdlib.h>

using namespace std;

//This function takes two strings as input and returns 
// whether the distance between two words is one or not
// If returns true, then the distance is 1
// If returns false, then the distance is not 1
bool distance(string s1, string s2)
{
  //Get the lengths of two input strings
  int first = s1.length(), second = s2.length();
 
  if (abs(first - second) > 1)
    return false;
 
  int count = 0; 
 
  int i = 0, j = 0;
  while (i < first && j < second)
    {
      if (s1[i] != s2[j])
        {
	  if (count == 1)
	    return false;
 
	  if (first>second)
	    i++;
	  else if (first<second)
	    j++;
	  else 
            {
	      i++;
	      j++;
            }
              
	  count++;
        }
 
      else 
        {
	  i++;
	  j++;
        }
    }
 
  if (i<first ||  j<second)
    count++;
 
  return (count == 1);
}

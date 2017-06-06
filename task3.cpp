// STD Headers
#include <iostream>   // Input/Output
#include <list>       // List Container
#include <vector>     // Vector Container
#include <algorithm>  // std::sort
#include <cassert>    // std::assert

using namespace std;

// Struct with overload
struct comp{
  template <typename T, typename U>
  bool operator() (const pair<T, U> & a, const pair<T, U> & b) const{
    return a.second < b.second;
  }
};

// Function for sorting containers
template<typename T1, typename T2>
void sortWrtContainer2(T1& container1, const T2& container2)
{

  // Check containers have the same size
  if(container1.size() != container2.size()){
    throw invalid_argument("\n\n\tContainers sizes mismatch\n\n");
  }

  // Variable for storaging pairs of values
  typedef std::pair<typename T1::value_type,typename T2::value_type> TPair;

  // Vector of pairs for storing the data
  vector<TPair> data(container1.size());

  // Fill the data vector of pairs with the content of the containers
  for (auto it1 = container1.begin(); it1!=container1.end(); it1++){
    auto pos = distance(container1.begin(), it1);
    auto it2 = container2.begin();
    advance(it2, pos);
    data[pos] = make_pair(*it1, *it2);
  }

  // Sort the data vector
  stable_sort(data.begin(), data.end(), comp());

  // Store sorted values in first container and print the result
  unsigned int pos = 0;
  for (const auto& pair : data){
    pos = &pair-&data[0];
    auto it = container1.begin();
    advance(it, pos);
    (*it) = pair.first;
    cout << "Pos " << pos << " -> " << (*it) << ", " << pair.second << endl;
  }
}


// Main function
int main(){

  // Containers with data
  vector<char> container1 = {'a','b','c'};
  vector<float> container2 = {4,7,1};

  // Sort the containers
  try {
    sortWrtContainer2(container1, container2);
  }
  catch (const std::exception &e) {
      std::cout << e.what() << std::endl;
      return EXIT_FAILURE;
  }
  

  return EXIT_SUCCESS;
}
///\file bmk.cpp
///\author mpv
///\brief Bmk test driver
/// Small benchmarking experiment to (I) measure and (II) compare the look-up performance for find() method on the realized RBTree versus std::map and std::unordered_map.
/// First, some randomly generated int/double numbers have been created and inserted into those three containers, thus increasing linearly nodes' number -in 50 increments- from 50 to 20000. 
/// Secondly, the average time of retreiving different and growing buckets of elements (numbers) from each container has been measured and finally plotted.
/// Expectations were to find a better performance for std::unordered_map (as based on hash table) while the other two (std::map and our RBTree) are based on red-black tree implementations, possibly slower. 

#include <chrono>
#include <fstream>
#include <iostream>
#include <map> 
#include <random>
#include <unordered_map>
#include <vector>
#include "../include/RBT.hpp"

///\brief function to generate random numbers (overloaded).
///\param numbers number of random numbers to be generated.
///\param is_double dummy to choose the type of random numbers (int or double).
///\return a vector filled with random numbers of type chosen.
std::vector<int> generate_random(const int& numbers) {
  std::vector<int> v;
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(0, numbers);
  for (int i=0; i<numbers; i++) {
      v.push_back(dis(gen));
    }
  return v;
}

std::vector<double> generate_random(const int& numbers, const bool& is_double) {
  std::vector<double> v;
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<double> dis(0, numbers);
  for (int i=0; i<numbers; i++) {
      v.push_back(double(dis(gen)));
    }
  return v;
}

///\brief function to measure the average time in microseconds to complete a search.
///\param container container to be searched.
///\param numbers vector of random numbers to be searched.
///\param search_size initial number of elements to be found in the container.
///\return average time in milliseconds.
template <typename T>
double measure_time(T& container, const std::vector<double>& numbers, const int& search_size) {
  auto start = std::chrono::high_resolution_clock::now();
  start = std::chrono::system_clock::now();
  for (int i=0; i<search_size; ++i) {
    container.find(numbers[i]);
  }
  auto end = std::chrono::high_resolution_clock::now();
  auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end-start);
  return elapsed.count()/double(search_size);
}


int main() {
  // output stream and output file
  std::ofstream out;
  out.open("../bmk/bmk_measures_double.txt");

  // define our experimental subjects (containers)
  std::map<double, double> m;
  std::unordered_map<double, double> um;
  RBTree<double> rbt;

  // define the size of the experiment
  int size_experiment{20000};

  // define initial size of the search within the containers
  int size_search{50};

  // define the size of the increment in the size of the search
  int step{50};

  // generate random numbers
  //std::vector<int> numbers = generate_random(size_experiment);
  std::vector<double> numbers = generate_random(size_experiment, 1);

  // insert numbers into containers & measure time elapsed to find them
  for (int i=size_search; i<=size_experiment; i+=step) {
    for(int j=0; j<i; ++j){
      m.insert({numbers[j],numbers[j]});
      um.insert({numbers[j],numbers[j]});
      rbt.insert({numbers[j]});
    }
    // print the output times
    out << i << "\t" << measure_time(m, numbers, i) << "\t" << measure_time(um, numbers, i) << "\t" << measure_time(rbt, numbers, i) << std::endl;
  }

  // close output file
  out.close();

  return 0;
}
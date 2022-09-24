// Bmk test driver

#include <chrono>
#include <fstream>
#include <iostream>
#include <map> 
#include <random>
#include <unordered_map>
#include <vector>
#include "RBT.hpp"

int main() {


    const int N{10000}; // Number of elements to be inserted and found 

    std::ofstream outFile;
    outFile.open("../bmk/bmk_measures.txt");

    //For generating random numbers
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(1,N); 

    std::vector<int> numbers;
    for(int j = 0; j <= N; ++j){
      numbers.push_back(dist(rng));
    }

    RBTree<int> rbt; // RedBlackTree
    std::map<int,int> map_; // STD map
    std::unordered_map<int,int> umap_; // STD unordered map


for (size_t i = 100; i <= N; i+=10)
{
    for(size_t k = 0; k < i; ++k){
        rbt.insert({numbers[k]});
        map_.insert({numbers[k], numbers[k]});
        umap_.insert({numbers[k], numbers[k]});
    }  

    //measuring time to find keys with std::map
  	auto t0_map = std::chrono::steady_clock::now();
   	for(size_t k = 0 ; k < i; ++k){
 		  map_.find(numbers[k]);
  	}
	  auto t1_map = std::chrono::steady_clock::now();
	  auto elapsed_map = std::chrono::duration_cast<std::chrono::microseconds>(t1_map-t0_map);  

    
    //measuring time to find keys with std::unordered_map
  	auto t0_umap = std::chrono::steady_clock::now();
   	for(size_t k = 0; k < i; ++k){
 		  umap_.find(numbers[k]);
  	}
	  auto t1_umap = std::chrono::steady_clock::now();
	  auto elapsed_umap = std::chrono::duration_cast<std::chrono::microseconds>(t1_umap-t0_umap);

    //measuring time to find keys with rbt
  	auto t0_rbt = std::chrono::steady_clock::now();
   	for(size_t k{0}; k < i; ++k){
 		  rbt.contains(numbers[k]);
  	}
	  auto t1_rbt = std::chrono::steady_clock::now();
	  auto elapsed_rbt = std::chrono::duration_cast<std::chrono::microseconds>(t1_rbt-t0_rbt);

    // write results to file
    outFile << i << "\t" << (double(elapsed_map.count()))/((double)N) << "\t" << (double(elapsed_umap.count()))/((double)N) << "\t" << (double(elapsed_rbt.count()))/((double)N) << "\n";
}
	  outFile.close();
	  return 0; 

}
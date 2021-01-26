# include "myDisjointSet_s156d039.hpp"
# include <iostream>
# include <vector>
# include <fstream>
# include <string>
void parseInstance(const std::string& line, std::vector<std::string> & res)
{
    int p = 0, q = 0;
    while(q < line.size())
    {
        if(line[q] ==',')
        {
            res.push_back(line.substr(p,q-p));
            p=q+1;
        }
        q++;
    }
}

int main(int argc, char* argv[])
{
  if(argc != 2)
  {
      std::cout << "You have to provide one test instance file to run the test main!\n";
      return 0;
  }

  std::ifstream fin;
  std::vector<std::string> data;
  fin.open(argv[1]);	    // open file
  if (!fin.is_open())	    // fail to open
  {
      std::cout << "Can't open the test instance file!\n";
      return 0;
  }
  else
  {
    std::string line;
    while(std::getline(fin, line))
    {
      parseInstance(line,data);
    }
  }

  // Declear a disjoint sets object
  myDisjointSet* ds = new  myDisjointSet(std::stoi(data[0]));

  // Test your implementation of getNumberElements, this will be used for later testing.
  std::cout << ds->getNumberElements() << "\n";

  // perform half of the union operations in the given instance
  int number_of_pairs = int((data.size()-1)/2);
  for(int i = 0; i < int(number_of_pairs/2); i++)
  {
    ds->unionSets( ds->find(std::stoi(data[2*i+1])), ds->find(std::stoi(data[2*i+2])) );
  }

  for(int i = 0; i < ds->getNumberElements(); i++)
  {
    /* for each element in the disjoint set,
    * first print the size of the set containing this element,
    * then print the print the element to its root.
    */
    std::cout << ds->getSetSize(i) << "\n";
    ds->print(i);
  }
  // perform the rest half of the union operations
  for(int i = int(number_of_pairs/2); i < number_of_pairs; i++)
  {
    ds->unionSets( ds->find(std::stoi(data[2*i+1])), ds->find(std::stoi(data[2*i+2])) );
  }


  for(int i = 0; i < ds->getNumberElements(); i+=3)
  // for every 3 element in the disjoint sets
  {
    ds->print(i);
    /*
      @Pre  the path from i to its root is contructed by union.
      @Post perform path compression and visualize the path again.
    */
    std::cout<<ds->find(i) << "\n";
    ds->print(i);
  }

  delete ds;
  return 0;
}
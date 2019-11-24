
#include "Factory.h"
#include "TSP.h"

int main(int argc, char* argv[]) {

  TSP* test = Factory::Create(Factory::TSPAlgos::GENETIC);
  test->Load("data/graph.txt");
  test->Execute(1, 10, 20, TSPAlgorithm::Crossover::PARTIALLY_MAPPED, TSPAlgorithm::Mutation::SWAP);

  return 0;
}
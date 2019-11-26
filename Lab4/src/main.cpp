
#include "Factory.h"
#include "TSP.h"
#include "GeneticOperators.h"

int main(int argc, char* argv[]) {

  TSP* test = Factory::Create(Factory::TSPAlgos::GENETIC);
  test->Load("data/graph.txt");
  test->Configure(
	  static_cast<int>(GeneticOperators::Selection::ROULETTE),
	  static_cast<int>(GeneticOperators::Crossover::PARTIALLY_MAPPED),
	  static_cast<int>(GeneticOperators::Mutation::SWAP),
	  40
  );
  test->Execute(1, 6);

  return 0;
}
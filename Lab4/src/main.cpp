
#include "Factory.h"
#include "TSP.h"
#include "GeneticOperators.h"
#include "TabuOperators.h"

int main(int argc, char* argv[]) {

  TSP* genetic = Factory::Create(Factory::TSPAlgos::GENETIC);
  genetic->Load("data/graph.txt");
  genetic->Configure(
	  static_cast<int>(GeneticOperators::Selection::TOURNAMENT),
	  static_cast<int>(GeneticOperators::Crossover::PARTIALLY_MAPPED),
	  static_cast<int>(GeneticOperators::Mutation::SWAP),
	  200
  );

  TSP* tabu = Factory::Create(Factory::TSPAlgos::TABU);
  tabu->Load("data/graph.txt");
  tabu->Configure(
	  static_cast<int>(TabuOperators::Neighborhood::SWAP), 100
  );

  for (int i = 0; i < 10; i++) {
	  tabu->Execute(1, 8);
	  tabu->Stats();
  }

  return 0;
}
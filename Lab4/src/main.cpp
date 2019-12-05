
#include "Factory.h"
#include "TSP.h"
#include "GeneticOperators.h"
#include "TabuOperators.h"

int main(int argc, char* argv[]) {

	TSP* genetic = Factory::Create(Factory::TSPAlgos::GENETIC);
	TSP* tabu = Factory::Create(Factory::TSPAlgos::TABU);

	genetic->Load("data/graph.txt");
	tabu->Load("data/graph.txt");

	for (int sel = GeneticOperators::Selection::ROULETTE; sel < GeneticOperators::Selection::ELITISM; sel++) {
		for (int cross = GeneticOperators::Crossover::PARTIALLY_MAPPED; cross < GeneticOperators::Crossover::ORDER; cross++) {
			for (int mut = GeneticOperators::Mutation::SWAP; mut < GeneticOperators::Mutation::LASTMUT; mut++) {

				for (int i = 4; i <= 20; i++) {
					genetic->Configure(sel, cross, mut, 150);
					genetic->Execute(1, i);
					genetic->Stats();
				}

				std::string fileName("results/genetic");
				fileName += "_" + GeneticOperators::getSelectionName(sel);
				fileName += "_" + GeneticOperators::getCrossoverName(cross);
				fileName += "_" + GeneticOperators::getMutationName(mut);
				fileName += ".csv";

				genetic->Save(fileName.c_str(), 4);
			}
		}
	}

	for (int neighborhood = TabuOperators::Neighborhood::SWAP; neighborhood < TabuOperators::Neighborhood::INVERSION; neighborhood++) {
		for (int size = 100; size <= 200; size += 50) {
			tabu->Configure(neighborhood, size);

			for (int i = 4; i <= 15; i++) {
				tabu->Execute(1, i);
				tabu->Stats();
			}

			std::string fileName("results/tabu");
			fileName += "_" + TabuOperators::getNeighborhoodName(neighborhood);
			fileName += "_" + std::to_string(size);
			fileName += ".csv";

			tabu->Save(fileName.c_str(), 4);
		}
	}

	return 0;
}
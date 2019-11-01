#include "TSP.h"

TSP::TSP(Factory::TSPAlgos algo) {
	switch (algo) {
	case Factory::NAIVEBF:
		algoObj = new NaiveBF();
		break;
	case Factory::DP:
		algoObj = new DynamicP();
		break;
	}
}

int TSP::Load(const char* filePath) {
	Parser::loadGraph(algoObj->getPositions(), filePath);
	return 0;
}

void TSP::Execute(int start, int size) {
	algoObj->start(start, size);
}

void TSP::Select(int type) {

}

void TSP::Display(Factory::TSPAlgos) {

}

void TSP::Stats(Factory::TSPAlgos algo, int type) {

}

void TSP::Save(Factory::TSPAlgos, int, int, int) {

}
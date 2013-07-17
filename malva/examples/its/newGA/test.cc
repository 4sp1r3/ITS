#include "problem.hh"
#include "solution.hh"



namespace newGA {


int main(int argc, char** argv) {

	Problem prob = Problem();
	prob._numnodes = 4;
	prob._maxx = 10;
	prob._minx = -10;
	prob._maxy = 10;
	prob._miny = -10;
	prob._nodes = new Vec2[4];
	prob._nodes[0] = Vec2(10.0,10.0);
	prob._nodes[1] = Vec2(10.0,-10.0);
	prob._nodes[2] = Vec2(-10.0,-10.0);
	prob._nodes[3] = Vec2(-10.0,10.0);
	prob._signal = Vec(4);
	prob._signal[0] = -29.0;
	prob._signal[1] = -29.0;
	prob._signal[2] = -29.0;
	prob._signal[3] = -29.0;

	Solution sol = Solution(prob);
	//sol._coord = Vec2(052.6489,0.634096);
	sol._coord = Vec2(0.0,0.0);
	//sol._decay[0] = 0.000256781 ;
	//sol._decay[1] = 0;
	//sol._decay[2] = 0.0988757;
	//sol._decay[3] = 0.0971013;


	/*
	 * PRUEBA DE FUNCIONES
	 */
	double signal = -29.0;
	double distance = 14.0;

	printf("Signal %f, la distancia da %f \n", signal,  prob.getPercibedDistance(signal));
	printf("Distancia %f, la señal da %f \n", distance ,  prob.getPercibedSignal(distance));
	printf("Signal(Distance(senal=%f) da %f\n", signal,  prob.getPercibedSignal(prob.getPercibedDistance(signal)));
	printf("Distance(Signal(distance=%f) da %f\n", distance , prob.getPercibedDistance(prob.getPercibedSignal(distance)));

	/*
	 * PRUEBA DE FITNES
	 */


	cout << "Fitness: " << sol.fitness() << endl;

	return 0;
};

}








int main(int argc, char** argv) {
	return newGA::main(argc,argv);
}





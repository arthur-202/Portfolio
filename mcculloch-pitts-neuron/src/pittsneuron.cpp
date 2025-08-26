#include <iostream>
#include <vector>

using namespace std;

class McCullochNeuron {
	private:
		  vector<int> pesos;
		  int limiar;

	public:
		  McCullochNeuron(vector<int> p, int l) {
		      pesos = p;
		      limiar = l;
		  }

		  int activate(vector<int> input) {
		      int total = 0;
		      for (int i = 0; i < input.size(); i++) {
		          total += input[i] * pesos[i];
		      }
		      return (total >= limiar) ? 1 : 0;
		  }
};

int main() {
    // Definição dos neurônios
    McCullochNeuron neuron_or({1, 1}, 1);   // OR
    McCullochNeuron neuron_and({1, 1}, 2);  // AND
    McCullochNeuron neuron_not({-1}, 0);    // NOT (entrada única)
    McCullochNeuron neuron_and2({1, 1}, 2); // AND final

    // Testando todas as combinações
    vector<vector<int>> entradas = {{0,0}, {0,1}, {1,0}, {1,1}};

    for (auto in : entradas) {
        int A = in[0];
        int B = in[1];

        int out_or = neuron_or.activate({A, B});
        int out_and = neuron_and.activate({A, B});
        int out_not = neuron_not.activate({out_and});
        int out_xor = neuron_and2.activate({out_or, out_not});

        cout << "Entrada: " << A << "," << B << " -> XOR = " << out_xor << endl;
    }
}


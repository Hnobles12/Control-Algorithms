#include <iostream>
#include <vector>

//Changes...


using namespace std;

class PID{
public:
	int buffer = 10;
	double SP;
	vector<double> PV;
	vector<double> time;
	double err, tot_gain, gain, correction;

	PID(vector<double>* pv, vector<double>* t, double sp = 0,double K=0){
		PV = *pv;
		time = *t;
		SP = sp;
		err = 0;
		gain = K;
		tot_gain = 0;
		correction = 0;
	}

	void set_target(double setpoint){
		SP = setpoint;
	}

	void set_buffer(int buff_size){
		buffer = buff_size;
	}

	void set_gain(double K){
		gain = K;
	}

	double update(vector<double>* dat){
		//Flush Buffer
		vector<double> data = *dat;
		int PV_size = PV.size();
	 	if (PV_size > 10){
			PV.erase(PV.begin(),PV.end()-buffer);
		}
	 	//Calculate Error
		err = SP - PV[PV_size];

		tot_gain = Prop() + Integrate() + Derivative();
		correction = tot_gain*err;

		return correction;
	}


	double test(int t=1){
		switch(t){
		case 1:
			//Prop Test
			return Prop();
		case 2:
			//Integrate Test
			return Integrate();
		case 3:
			//Derivative Test
			return Derivative();
		}
	}
private:

	double Prop(){
		double PV_size = PV.size();
		double val = PV[PV_size]/SP;
		return val;
	}

	double Integrate(){
		double val;
		double num;
		for (int i = 0; i < buffer-1; i++){
			num = (time[i+1]-time[i])*(PV[i+1]+PV[i]);
			val += num;
		}
		val *= 0.5;
		return val;
	}

	double Derivative(){
		vector<double> der;
		double diff, avg;

		for (int i=0; i < buffer; i++){
			diff = (PV[i+1]-PV[i])/(time[i+1]-time[i]);

			cout <<i<< " Diff: "<<diff << endl;
			der.push_back(diff);
		}

		for (int i=0; i <= buffer-1; i++){
			avg += der[i];
		}
		avg = avg/der.size();

		return avg;
	}
};

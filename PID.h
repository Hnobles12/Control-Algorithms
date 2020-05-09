#ifndef PID_H
#define PID_H

#include <vector>

using namespace std;

class PID{
public:
	int buffer;
	double err, prop_gain, correction, SP, ID_gain;
	vector<double> PV,time;

	PID(vector<double>* pv, vector<double>* t, double sp = 0){
		PV = *pv;
		time = *t;
		SP = sp;
		err = 0;
		correction = 0;
		prop_gain=0;
		buffer = 10;
		ID_gain = 0;


	}

	void set_target(double setpoint){
		SP = setpoint;
	}

	void set_buffer(int buff_size){
		buffer = buff_size;
	}

	void set_Pgain(double K){
		prop_gain = K;
	}

	double update(vector<double>* dat){
		//Flush Buffer
		vector<double> data = *dat;
		int PV_size = PV.size();
	 	if (PV_size > 10){
			PV.erase(PV.begin(),PV.end()-buffer);
		}
	 	//Calculate Error
		err = SP - average();

		ID_gain = Integrate() + Derivative();
		correction = prop_gain*(err + ID_gain*err);

		return correction;
	}


	double test(int t=1){
		switch(t){
		case 1:
			//Prop Test
			return 0;
		case 2:
			//Integrate Test
			return Integrate();
		case 3:
			//Derivative Test
			return Derivative();
		}
	}

private:
	double average(){
		double PV_size = PV.size();
		double avg,sum;
		sum = 0;

		for (int i=0; i<PV_size; i++){
			sum += PV[i];
		}

		avg = sum/PV_size;
		return avg;
	}

	double Integrate(){
		double val = 0;
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

			der.push_back(diff);
		}

		for (int i=0; i <= buffer-1; i++){
			avg += der[i];
		}
		avg = avg/der.size();

		return avg;
	}
};

#endif

#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
using namespace std;

double factorials[100];
const double precision = 0.00000001;
const double pi = 4*atan(1);

bool Increment(vector<int>&, int);
double Hero(double, double, double);
double AngleSumExt(double, vector<int>&);
double AngleSumInt(double, vector<int>&);
double ComputeArea(vector<int>&);

int main(){
    factorials[0] = 1;
    for (int i = 1; i < 100; i++)
        factorials[i] = factorials[i-1]*i;
        
    double answer = sqrt(3);
    for (int n = 5; n <= 50; n++){
        int perimeter = 2*n-3;
        double denominator = factorials[2*n-4]/(factorials[n-1]*factorials[n-3]);
        double ev = 0;
        vector<int> lengths(n-2, 1);
        lengths.push_back(0);
        lengths.push_back(n-1);
        while (Increment(lengths, perimeter)){
            double area = ComputeArea(lengths);
            vector<int> freq(50, 0);
            for (int i = 0; i < lengths.size(); i++)
                freq[lengths[i]]++;
            double number = factorials[n];
            for (int i = 0; i < 50; i++)
                number /= factorials[freq[i]];
            double prob = number / denominator;
            ev += prob*area;
        }
        answer += ev;
    }
    cout << "Answer: " << fixed << setprecision(6) << answer << endl;

    return 0;
}

bool Increment(vector<int>&lengths, int perimeter){
    for (int j = lengths.size() - 2; j > 0; j--){
        for (int k = j+1; k < lengths.size(); k++){
            if (lengths[j] + 1 <= lengths[k] - 1){
                lengths[j]++;
                for (int i = j+1; i < lengths.size() - 1; i++)
                    lengths[i] = lengths[j];
                int peri = 0;
                for (int i = 0; i < lengths.size() - 1; i++)
                    peri += lengths[i];
                lengths[lengths.size() - 1] = perimeter - peri;
                return true;
            }
        }
    }
    return false;
}

double Hero(double a, double b, double c){
    double s = (a + b + c) / 2.;
    return sqrt(s*(s-a)*(s-b)*(s-c));
}

double AngleSumExt(double r, vector<int>&lengths){
    double answer = 0;
    for (int i = 0; i < lengths.size() - 1; i++)
        answer += asin(lengths[i]/(2.*r));
    answer -= asin(lengths[lengths.size() - 1] / (2.*r));
    return answer;
}

double AngleSumInt(double r, vector<int>&lengths){
    double answer = 0;
    for (int i = 0; i < lengths.size(); i++)
        answer += asin(lengths[i]/(2.*r));
    return answer;    
}

double ComputeArea(vector<int>&lengths){
    double lowR = lengths[lengths.size() - 1] / 2.;
    double highR = 2*lowR;
    double lowR_angle_sum = 0;
    double highR_angle_sum = 0;
    for (int i = 0; i < lengths.size(); i++)
        lowR_angle_sum += asin(lengths[i]/(lowR*2.));
    double mid;
    double mid_sum;
    
    if (lowR_angle_sum < pi){
        // The center of the circle is exterior to the polygon
        lowR_angle_sum -= 2*asin(lengths[lengths.size() - 1]/(lowR*2.));
        while (AngleSumExt(highR, lengths) < 0)
            highR *= 2;
        highR_angle_sum = AngleSumExt(highR, lengths);
        while (highR - lowR > precision){
            mid = (lowR + highR) / 2.;
            mid_sum = AngleSumExt(mid, lengths);
            if (mid_sum < 0){
                lowR = mid;
                lowR_angle_sum = mid_sum;
            }
            else{
                highR = mid;
                highR_angle_sum = mid_sum;
            }
        }
        double answer = 0;
        for (int i = 0; i < lengths.size() - 1; i++)
            answer += Hero(mid, mid, lengths[i]);
        answer -= Hero(mid, mid, lengths[lengths.size() - 1]);
        return answer;
    }
    else{
        // The center of the circle is interior to the polygon
        while (AngleSumInt(highR, lengths) > pi)
            highR *= 2;
        highR_angle_sum = AngleSumInt(highR, lengths);
        while (highR - lowR > precision){
            mid = (lowR + highR) / 2.;
            mid_sum = AngleSumInt(mid, lengths);
            if (mid_sum < pi){
                highR = mid;
                highR_angle_sum = mid_sum;
            }
            else{
                lowR = mid;
                lowR_angle_sum = mid_sum;
            }
        }
        double answer = 0;
        for (int i = 0; i < lengths.size(); i++)
            answer += Hero(mid, mid, lengths[i]);
        return answer;
    }
}
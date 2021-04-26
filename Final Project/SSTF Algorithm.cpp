#include <bits/stdc++.h>
using namespace std;
void calculateDifference(int *request, int head, int **diff, int n){
    for(int i = 0; i < n; i++){
        diff[i][0] = abs(head - request[i]);
    }
}

int findMIN(int **diff, int n){
    int index = -1;
    int minimum = 1e9;

    for(int i = 0; i < n; i++){
        if (!diff[i][1] && minimum > diff[i][0]){
            minimum = diff[i][0];
            index = i;
        }
    }
    return index;
}

void shortestSeekTimeFirst(int *request,int head, int n){
    if (n == 0){
        return;
    }


    int **diff = new int*[n];
    for (int i = 0; i < n; ++i) {
        diff[i] = new int [2];
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < 2; ++j) {
            diff[i][j] = 0;
        }
    }

    int seekCount = 0;

    int *seekSequence = new int[n+1];
    for (int i = 0; i <= n; ++i) {
        seekSequence[i] = 0;
    }

    for(int i = 0; i < n; i++){
        seekSequence[i] = head;
        calculateDifference(request, head, diff, n);
        int index = findMIN(diff, n);
        diff[index][1] = 1;
        seekCount += diff[index][0];
        head = request[index];
    }
    seekSequence[n] = head;

    cout << "Total number of seek operations = " << seekCount << endl;
    cout << "Seek sequence is : " << "\n";
    
    for(int i = 0; i <= n; i++){
        cout << seekSequence[i] << "\n";
    }
}

int main(){
    int n;
    cin>>n;

    int arr[n];
    for(int i=0;i<n;i++){
        cin>>arr[i];
    }
    
    int head;
    cin>>head;
    shortestSeekTimeFirst(arr, head, n);
}

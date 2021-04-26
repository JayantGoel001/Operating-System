#include <iostream>
using namespace std;

void FCFS(int arr[], int head,int size){
    int seek_count = 0;
    int distance, cur_track;

    for (int i = 0; i < size; i++) {
        cur_track = arr[i];
        distance = abs(cur_track - head);
        seek_count += distance;
        head = cur_track;
    }
    cout << "Total number of seek operations = "<< seek_count << endl;

    cout << "Seek Sequence is" << endl;

    for (int i = 0; i < size; i++) {
        cout << arr[i] << endl;
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

    FCFS(arr, head, n);

    return 0;
}

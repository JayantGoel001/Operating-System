#include <bits/stdc++.h>
using namespace std;
void CLOOK(int arr[], int head,int size){
    int seek_count = 0;
    int distance, cur_track;

    vector<int> left, right;
    vector<int> seek_sequence;

    for (int i = 0; i < size; i++) {
        if (arr[i] < head)
            left.push_back(arr[i]);
        if (arr[i] > head)
            right.push_back(arr[i]);
    }

    sort(left.begin(), left.end());
    sort(right.begin(), right.end());

    for (int i : right) {
        cur_track = i;
        seek_sequence.push_back(cur_track);
        distance = abs(cur_track - head);
        seek_count += distance;
        head = cur_track;
    }

    seek_count += abs(head - left[0]);
    head = left[0];
    for (int i : left) {
        cur_track = i;
        seek_sequence.push_back(cur_track);
        distance = abs(cur_track - head);
        seek_count += distance;
        head = cur_track;
    }

    cout << "Total number of seek operations = "<< seek_count << endl;

    cout << "Seek Sequence is" << endl;

    for (int i : seek_sequence) {
        cout << i << endl;
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

    CLOOK(arr, head,n);
}

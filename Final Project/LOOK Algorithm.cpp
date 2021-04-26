#include <bits/stdc++.h>
using namespace std;
void LOOK(int arr[], int head, string direction,int size){
    int seek_count = 0;
    int distance, cur_track;
    vector<int> downward, upward;
    vector<int> seek_sequence;

    for (int i = 0; i < size; i++) {
        if (arr[i] < head)
            downward.push_back(arr[i]);
        if (arr[i] > head)
            upward.push_back(arr[i]);
    }

    sort(downward.begin(), downward.end());
    sort(upward.begin(), upward.end());

    int run = 2;
    while (run--) {
        if (direction == "downward") {
            for (int i = downward.size() - 1; i >= 0; i--) {
                cur_track = downward[i];
                seek_sequence.push_back(cur_track);
                distance = abs(cur_track - head);
                seek_count += distance;
                head = cur_track;
            }
            direction = "upward";
        }
        else if (direction == "upward") {
            for (int i : upward) {
                cur_track = i;
                seek_sequence.push_back(cur_track);
                distance = abs(cur_track - head);
                seek_count += distance;
                head = cur_track;
            }
            direction = "downward";
        }
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

    string direction = "downward";

    LOOK(arr, head, direction,n);

}
